/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014 Sean Keys
 *
 * This file is part of the LibreEMS project.
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
 * along with any LibreEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * Thank you for choosing LibreEMS to run your engine!
 */


/** @file
 *
 * @brief Provide global variables that exist in RAM
 *
 * TODO complete doc after cleaning up
 */

#include "inc/mathFunctions.h"


int16_t TableLookupINT16(uint16_t lookupInput, TableEntryINT16 *tablePTR, uint8_t numRows) {
  int16_t  lowLookupAxies  = 0;
  int16_t  highLookupAxies = 0;
  int16_t  lowScalar       = 0;
  int16_t  highScalar      = 0;

  uint8_t i;

  for (i = 0; i < numRows; ++i, ++tablePTR) {
    if (tablePTR->lookup == lookupInput) {
      return tablePTR->scalar;
    }

    /* If our lookup is smaller than our first scalar, return the first scalar entry */
    if ((i == 0) && (tablePTR->lookup > lookupInput)) {
      return tablePTR->scalar;
    }

    if (tablePTR->lookup < lookupInput) {
      lowLookupAxies = tablePTR->lookup;
      lowScalar = tablePTR->scalar;
    }

    if (tablePTR->lookup > lookupInput) {
      highLookupAxies = tablePTR->lookup;
      highScalar = tablePTR->scalar;
      break;
    }
  }
  /* If we have a lookup that is greater than our highest Rvalue, just return the greatest Rscalar */
  if (lowScalar > highScalar) {
    --tablePTR;
    return tablePTR->scalar;
  }

//TODO potentially handle this issue differently
  if (lowScalar == 0 && highScalar == 0) {
    return 0;
  }
  /* How close are we to the high lookup point */
  int16_t value = linearInterpolationI16(lowLookupAxies, lowScalar,
      highLookupAxies, highScalar, lookupInput);

  return value;
}

uint16_t TableLookupUINT16(uint16_t lookupInput, TableEntryUINT16 *tablePTR, uint8_t numRows) {
  uint16_t  lowLookupAxies  = 0;
  uint16_t  highLookupAxies = 0;
  uint16_t  lowScalar       = 0;
  uint16_t  highScalar      = 0;

  uint8_t i;

  for (i = 0; i < numRows; ++i, ++tablePTR) {
    if (tablePTR->lookup == lookupInput) {
      return tablePTR->scalar;
    }

    /* If our lookup is smaller than our first scalar, return the first scalar entry */
    if ((i == 0) && (tablePTR->lookup > lookupInput)) {
      return tablePTR->scalar;
    }

    if (tablePTR->lookup < lookupInput) {
      lowLookupAxies = tablePTR->lookup;
      lowScalar = tablePTR->scalar;
    }

    if (tablePTR->lookup > lookupInput) {
      highLookupAxies = tablePTR->lookup;
      highScalar = tablePTR->scalar;
      break;
    }
  }
  /* If we have a lookup that is greater than our highest Rvalue, just return the greatest Rscalar */
  if (lowScalar > highScalar) {
    --tablePTR;
    return tablePTR->scalar;
  }

//TODO potentially handle this issue differently
  if (lowScalar == 0 && highScalar == 0) {
    return 0;
  }
  /* How close are we to the high lookup point */
  uint16_t value = linearInterpolationI16(lowLookupAxies, lowScalar,
      highLookupAxies, highScalar, lookupInput);

  return value;
}

uint32_t TableLookupU16U32(uint16_t lookupInput, TableEntryU1632 *tablePTR, uint8_t numRows) {
  uint16_t  lowLookupAxies  = 0;
  uint16_t  highLookupAxies = 0;
  uint32_t  lowScalar       = 0;
  uint32_t  highScalar      = 0;

  uint8_t i;

  for (i = 0; i < numRows; ++i, ++tablePTR) {
    if (tablePTR->lookup == lookupInput) {
      return tablePTR->scalar;
    }

    /* If our lookup is smaller than our first scalar, return the first scalar entry */
    if ((i == 0) && (tablePTR->lookup > lookupInput)) {
      return tablePTR->scalar;
    }

    if (tablePTR->lookup < lookupInput) {
      lowLookupAxies = tablePTR->lookup;
      lowScalar = tablePTR->scalar;
    }

    if (tablePTR->lookup > lookupInput) {
      highLookupAxies = tablePTR->lookup;
      highScalar = tablePTR->scalar;
      break;
    }
  }
  /* If we have a lookup that is greater than our highest Rvalue, just return the greatest Rscalar */
  if (lowScalar > highScalar) {
    --tablePTR;
    return tablePTR->scalar;
  }

  //TODO potentially handle this issue differently
  if (lowScalar == 0 && highScalar == 0) {
    return 0;
  }

  /* How close are we to the high lookup point */
  uint32_t value = linearInterpolationU16U32(lowLookupAxies, lowScalar,
      highLookupAxies, highScalar, lookupInput);

  return value;
}

uint16_t verify16b16bAxis(TableEntryINT16 *table, uint8_t numRows) {
  uint8_t i;

  if (numRows <= 1) {
    return 0;
  }
  --numRows;

  for (i = 0; i < numRows ; ++i) {
    if (table[i].lookup > table[(i + 1)].lookup) {
      return 0x6011;
    }
  }

  return 0;
}

uint16_t verify16b32bAxis(TableEntryU1632 *table, uint8_t numRows) {
  uint8_t i;

  if (numRows <= 1) {
    return 0;
  }

  for (i = 1; i < numRows; ++i) {
    if (table[(i - 1)].lookup >= table[i].lookup) {
      return 0x6011;
    }
  }

  return 0;
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
