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
 * @brief
 *
 * TODO complete doc after cleaning up
 */


#include "inc/libreMath.h"

inline uint16_t diffUint16(uint16_t head, uint16_t tail) {
  if(head > tail) {
    return head - tail;
  } else {
    return ((0xFFFF - tail) + head + 1);
  }
}

inline uint32_t diffUint32(uint32_t head, uint32_t tail) {
  if(head > tail) {
    return head - tail;
  } else {
    return ((0xFFFFFFFF - tail) + head + 1);
  }
}

inline uint16_t ratio32(uint32_t value1, uint32_t value2, uint16_t scaler) {
  uint16_t scaledPercent;

  if (value1 > value2) {
    scaledPercent = (value2 * scaler) / value1;
  }else {
    scaledPercent = (value1 * scaler) / value2;
  }

  return scaledPercent;
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
