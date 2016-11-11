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
 * @ingroup allHeaders
 * @ingroup globalHeaders
 * @ingroup dataStructures
 *
 * @brief Table struct typedefs
 *
 * This file contains all of the tabular struct typedefs.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_TABLE_TYPES_H_SEEN
#define FILE_TABLE_TYPES_H_SEEN


#define TWOD_LUT_LENGTH 8
/// Small LUT for near leaner input sensors
typedef struct {
  uint16_t Axis[TWOD_LUT_LENGTH];
  uint16_t Values[TWOD_LUT_LENGTH];
} twoDLUTTableUS;

#define MAINTABLE_RPM_LENGTH       24 ///< How many cells on the X axis
#define MAINTABLE_LOAD_LENGTH      19 ///< How many cells on the Y axis
#define MAINTABLE_MAX_RPM_LENGTH   27 ///< Max number of cells on the X axis
#define MAINTABLE_MAX_LOAD_LENGTH  21 ///< Max number of cells on the Y axis
#define MAINTABLE_MAX_MAIN_LENGTH 462 ///< 924B 462 shorts maximum main table length


/** Main Table Structure definition
 *
 * Use this table descriptor to manage the
 * - main VE table
 * - Lambda table
 * - Timing tables
 *
 * Tables can be made any size from 1x1 to 27x17 or 22x21 provided that the multiple of
 * the two doesn't exceed the max main length and neither axis exceeds it's
 * specified maximum.
 *
 * For a more detailed discussion of how this structure is actually used...
 *
 * @see lookupPagedMainTableCellValue
 */
typedef struct {
  uint16_t RPMLength;                        ///< The length of the RPM axis array
  uint16_t LoadLength;                       ///< The length of the Load axis array
  uint16_t RPM[MAINTABLE_MAX_RPM_LENGTH];    ///< The array of RPM (X) axis values
  uint16_t Load[MAINTABLE_MAX_LOAD_LENGTH];  ///< The array of Load (Y) axis values
  uint16_t Table[MAINTABLE_MAX_MAIN_LENGTH]; ///< The table as an array of values
} mainTable;


#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
