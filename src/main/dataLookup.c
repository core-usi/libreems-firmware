/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014 Sean Keys
 *
 * This file is part of the LibreEMS project.
 *
 * LibreEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibreEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any LibreEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * Thank you for choosing LibreEMS to run your engine!
 */


/** @file
 *
 * @ingroup data acquisition
 */

#include "inc/dataLookup.h"
#include "inc/freeEMS.h"
#include "inc/mathFunctions.h"


uint16_t smallTableLookup(twoDLUTTableUS *table, uint16_t lookup){


  /* Find the bounding axis indices, axis values and lookup values */
  uint8_t lowIndex = 0;
  uint8_t highIndex = 8 - 1;

  /* If never set in the loop, low value will equal high value and will be on the edge of the map */
  uint16_t lowAxisValue = table->Axis[0];
  uint16_t highAxisValue = table->Axis[highIndex];
  uint16_t lowLookupValue = table->Values[0];
  uint16_t highLookupValue = table->Values[highIndex];

  uint8_t Index;
  for(Index =0 ; Index < 8; ++Index){
    if(table->Axis[Index] < lookup){
      lowIndex = Index;
      lowAxisValue = table->Axis[Index];
      lowLookupValue = table->Values[Index];
    }else if(table->Axis[Index] > lookup){
      highIndex = Index;
      highAxisValue = table->Axis[Index];
      highLookupValue = table->Values[Index];
      break;
    }else if(table->Axis[Index] == lookup){
      return table->Values[Index];
    }
  }

  /* Interpolate and return the value */
  return lowLookupValue + (((int32_t)((int32_t)highLookupValue - lowLookupValue) * (lookup - lowAxisValue))/ (highAxisValue - lowAxisValue));
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
