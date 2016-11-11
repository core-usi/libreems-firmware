/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @brief Table access functions
 *
 * Functions for writing to and reading from all of the different table types.
 */


#define TABLELOOKUP_C
#include "inc/freeEMS.h"
#include "inc/commsISRs.h"
#include "inc/tableLookup.h"
#include "inc/blockDetailsLookup.h"


/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ******* ******* ******* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ******* WARNING ******* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& ******* ******* ******* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&                                                               &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&& These routines rely on the fact that there are no ISRs trying &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&& to access the small tables and other live settings in the RAM &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&& window as specified by the RPAGE value. If they are then bad  &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&& values WILL be occasionally read from random parts of the big &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&& tables instead of the correct place. If that occurs it WILL   &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&& cause unpredictable and VERY hard to find bugs!!              &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&                                                               &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&  *******  *******  YOU HAVE BEEN WARNED!!!  *******  *******  &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&                                                               &&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/


/* Yet to be implemented :

uint8_t lookup8Bit3dUC(
uint8_t lookup8Bit2dUC(
int16_t lookup16Bit3dSS(
int16_t lookup16Bit3dSS(
int8_t lookup8Bit3D( */


/** @brief Main table read function
 *
 * Looks up a value from a main table using interpolation.
 *
 * The process :
 *
 * Take a table with two movable axis sets and two axis lengths,
 * loop to find which pairs of axis values and indexs we are between,
 * interpolate two pairs down to two values,
 * interpolate two values down to one value.
 *
 * Table size :
 *
 * To reduce the table size from 19x24 to something smaller, simply
 * reduce the RPMLength and LoadLength fields to lower values.
 * Increasing the size of either axis is not currently possible.
 *
 * Values outside the table :
 *
 * Given that the axis lists are in order, a data point outside
 * the table will give the value adjacent to it, and one outside
 * one of the four corners will give the corner value. This is a
 * clean and reasonable behaviour in my opinion.
 *
 * Reminder : X/RPM is horizontal, Y/Load is vertical
 *
 * @warning This function relies on the axis values being a sorted
 * list from low to high. If this is not the case behaviour is
 * undefined and could include memory corruption and engine damage.
 *
 * @param realRPM is the current RPM for which a table value is required.
 * @param realLoad is the current load for which a table value is required.
 * @param locationID the ID to use to get the memory information to look up the table.
 *
 * May go back to these:
 * old param RAMPage is the RAM page that the table is stored in.
 * old param Table is a pointer to the table to read from.
 *
 * @return The interpolated value for the location specified.
 */
uint16_t lookupMainTable(uint16_t realRPM, uint16_t realLoad, uint16_t locationID){
  blockDetails mainTableDetails;
  lookupBlockDetails(locationID, &mainTableDetails);
  if(!(mainTableDetails.flags & BLOCK_IS_MAIN_TABLE)){
    return 0; // Safe value, always means no fuel or TDC timing.
  }

  // Leave the rest of the code untouched and keep it more concise
  mainTable* Table = (mainTable*)mainTableDetails.RAMAddress;

  /* Save the RPAGE value for restoration and switch pages. */
  uint8_t oldRPage = RPAGE;
  RPAGE = mainTableDetails.RAMPage;

  /* Find the bounding axis values and indices for RPM */
  uint8_t lowRPMIndex = 0;
  uint8_t highRPMIndex = Table->RPMLength - 1;
  /* If never set in the loop, low value will equal high value and will be on the edge of the map */
  uint16_t lowRPMValue = Table->RPM[0];
  uint16_t highRPMValue = Table->RPM[Table->RPMLength -1];

  uint8_t RPMIndex;
  for(RPMIndex=0;RPMIndex<Table->RPMLength;RPMIndex++){
    if(Table->RPM[RPMIndex] < realRPM){
      lowRPMValue = Table->RPM[RPMIndex];
      lowRPMIndex = RPMIndex;
    }else if(Table->RPM[RPMIndex] > realRPM){
      highRPMValue = Table->RPM[RPMIndex];
      highRPMIndex = RPMIndex;
      break;
    }else if(Table->RPM[RPMIndex] == realRPM){
      lowRPMValue = Table->RPM[RPMIndex];
      highRPMValue = Table->RPM[RPMIndex];
      lowRPMIndex = RPMIndex;
      highRPMIndex = RPMIndex;
      break;
    }
  }

  /* Find the bounding cell values and indices for Load */
  uint8_t lowLoadIndex = 0;
  uint8_t highLoadIndex = Table->LoadLength -1;
  /* If never set in the loop, low value will equal high value and will be on the edge of the map */
  uint16_t lowLoadValue = Table->Load[0];
  uint16_t highLoadValue = Table->Load[Table->LoadLength -1];

  uint8_t LoadIndex;
  for(LoadIndex=0;LoadIndex<Table->LoadLength;LoadIndex++){
    if(Table->Load[LoadIndex] < realLoad){
      lowLoadValue = Table->Load[LoadIndex];
      lowLoadIndex = LoadIndex;
    }else if(Table->Load[LoadIndex] > realLoad){
      highLoadValue = Table->Load[LoadIndex];
      highLoadIndex = LoadIndex;
      break;
    }else if(Table->Load[LoadIndex] == realLoad){
      lowLoadValue = Table->Load[LoadIndex];
      highLoadValue = Table->Load[LoadIndex];
      lowLoadIndex = LoadIndex;
      highLoadIndex = LoadIndex;
      break;
    }
  }

  /* Obtain the four corners surrounding the spot of interest */
  uint16_t lowRPMLowLoad = Table->Table[(Table->RPMLength * lowLoadIndex) + lowRPMIndex];
  uint16_t lowRPMHighLoad = Table->Table[(Table->RPMLength * highLoadIndex) + lowRPMIndex];
  uint16_t highRPMLowLoad = Table->Table[(Table->RPMLength * lowLoadIndex) + highRPMIndex];
  uint16_t highRPMHighLoad = Table->Table[(Table->RPMLength * highLoadIndex) + highRPMIndex];

  /* Restore the RAM page before doing the math */
  RPAGE = oldRPage;

  /* Find the two side values to interpolate between by interpolation */
  uint16_t lowRPMIntLoad = lowRPMLowLoad + (((int32_t)((int32_t)lowRPMHighLoad - lowRPMLowLoad) * (realLoad - lowLoadValue))/ (highLoadValue - lowLoadValue));
  uint16_t highRPMIntLoad = highRPMLowLoad + (((int32_t)((int32_t)highRPMHighLoad - highRPMLowLoad) * (realLoad - lowLoadValue))/ (highLoadValue - lowLoadValue));

  /* Interpolate between the two side values and return the result */
  return lowRPMIntLoad + (((int32_t)((int32_t)highRPMIntLoad - lowRPMIntLoad) * (realRPM - lowRPMValue))/ (highRPMValue - lowRPMValue));
}



/** @brief Validate a main table
 *
 * Check that the configuration of the table is valid. Assumes pages are
 * correctly set. @todo more detail here....
 *
 * @param Table The pointer to the table to be validated.
 *
 * @return An error code. Zero means success, anything else is a failure.
 */
uint16_t validateMainTable(mainTable* Table){
  /* If required and only if required extend this to take r and f pages and check */
  /* any main table, not just a freshly received untrusted ones in linear space   */

  if(Table->RPMLength > MAINTABLE_MAX_RPM_LENGTH){
    return INVALID_MAIN_TABLE_RPM_LENGTH;
  }else if(Table->LoadLength > MAINTABLE_MAX_LOAD_LENGTH){
    return INVALID_MAIN_TABLE_LOAD_LENGTH;
  }else if((Table->RPMLength * Table->LoadLength) > MAINTABLE_MAX_MAIN_LENGTH){
    return INVALID_MAIN_TABLE_MAIN_LENGTH;
  }else{
    /* Check the order of the RPM axis */
    uint8_t i;
    for(i=0;i<(Table->RPMLength - 1);i++){
      if(Table->RPM[i] >= Table->RPM[i+1]){
        return INVALID_MAIN_TABLE_RPM_ORDER;
      }
    }
    /* Check the order of the Load axis */
    uint8_t j;
    for(j=0;j<(Table->LoadLength - 1);j++){
      if(Table->Load[j] >= Table->Load[j+1]){
        return INVALID_MAIN_TABLE_LOAD_ORDER;
      }
    }
    /* If we made it this far all is well */
    return 0;
  }
}


/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
