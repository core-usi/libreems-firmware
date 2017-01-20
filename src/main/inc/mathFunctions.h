/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2015 Sean Keys
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
 * @ingroup communicationsFiles
 *
 * @brief Utilities
 *
 *
 */

#ifndef DATA_MATHFUNCTIONS_H_SEEN
#define DATA_MATHFUNCTIONS_H_SEEN

#include <stdint.h>

#include "Configuration.h"
#include "scalerDefines.h"
#include "tableTypes.h"

static inline uint32_t diffUint32(uint32_t head, uint32_t tail) __attribute__((always_inline));
static inline uint16_t diffUint16(uint16_t head, uint16_t tail) __attribute__((always_inline));
static inline uint16_t ratio16(uint16_t value1, uint16_t value2, uint16_t scaler) __attribute__((always_inline));
static inline uint16_t mul16(uint16_t base, uint16_t multiplier)  __attribute__((always_inline));
static inline uint16_t getTPSpercent(SensorProperties *config, uint16_t TPSadc, uint16_t TPSadcRange) __attribute__((always_inline));
static inline uint16_t offsetAngle(uint16_t startAngle, int16_t offset)  __attribute__((always_inline));

int16_t TableLookupINT16(uint16_t lookupInput, TableEntryINT16 *tablePTR, uint8_t numRows) TEXT;
uint16_t TableLookupUINT16(uint16_t lookupInput, TableEntryUINT16 *tablePTR, uint8_t numRows) TEXT;
uint32_t TableLookupU16U32(uint16_t lookupInput, TableEntryU1632 *tablePTR, uint8_t numRows) TEXT;
uint16_t verify16b16bAxis(TableEntryINT16 *table, uint8_t numRows) TEXT;
uint16_t verify16b32bAxis(TableEntryU1632 *table, uint8_t numRows) TEXT;


static
inline uint16_t diffUint16(uint16_t head, uint16_t tail) {
  if(head >= tail) {
    return head - tail;
  } else {
    return ((0xFFFF - tail) + head + 1);
  }
}

static
inline uint8_t diffUint8(const uint8_t head, const uint8_t tail) {
  if(head >= tail) {
    return head - tail;
  } else {
    return ((0xFF - tail) + head + 1);
  }
}

static
inline uint32_t diffUint32(const uint32_t head, const uint32_t tail) {
  if(head >= tail) {
    return head - tail;
  } else {
    return ((0xFFFFFFFF - tail) + head + 1);
  }
}

static
inline uint16_t angleAdd(const uint16_t angle1, const uint16_t angle2) {
  uint32_t angle = angle1 + angle2;

  if (angle >= ENGINE_ANGLE_S(720)) {
    angle -= ENGINE_ANGLE_S(720);
  }

  return angle;
}

static
inline uint16_t ratio16(const uint16_t value1, const uint16_t value2, const uint16_t scaler) {
  uint16_t scaledPercent;

  if (value1 > value2) {
    scaledPercent = ((uint32_t)value2 * scaler) / value1;
  }else {
    scaledPercent = ((uint32_t)value1 * scaler) / value2;
  }

  return scaledPercent;
}

static
inline uint16_t mul16(uint16_t base, uint16_t multiplier) {

  uint32_t product = base * multiplier;

  if (product > 0xFFFF) {
    return 0xFFFF;
  }

  return product;
}

/*
 * Return TPS in percent taking into account the configured
 * min and max ADC readings.
 */
static
inline uint16_t getTPSpercent(SensorProperties *config, uint16_t TPSadc, uint16_t TPSadcRange) {

  uint16_t boundedTPSADC = 0;
  if(TPSadc > config->TPSMaximum){
    boundedTPSADC = TPSadcRange;
  }else if(TPSadc > config->TPSMinimum){
    boundedTPSADC = TPSadc - config->TPSMinimum;
  }

  return ((uint32_t)boundedTPSADC * PERCENT(100)) / TPSadcRange;
}

/*
 * A positive number will advance the angle while a negative number will
 * retard it.
 */
static inline uint16_t offsetAngle(uint16_t startAngle, int16_t offset) {
  startAngle -= offset;

  if (startAngle >= ((ENGINE_ANGLE_S(360) * CRANKSHAFT_REVS_PER_CYCLE))) {
    if (offset < 0) {
      startAngle -= ((ENGINE_ANGLE_S(360) * CRANKSHAFT_REVS_PER_CYCLE));
    }else {
      startAngle += ((ENGINE_ANGLE_S(360) * CRANKSHAFT_REVS_PER_CYCLE));
    }
  }

  return startAngle;
}

static inline int16_t linearInterpolationI16(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x) {
  int16_t a = (y1 - y0) / (x1 - x0);
  int16_t b = -a*x0 + y0;
  int16_t y = a * x + b;
 return y;
}

static inline uint32_t linearInterpolationU16U32(uint16_t x0, uint32_t y0, uint16_t x1, uint32_t y1, uint32_t x) {
  uint64_t a = (y1 - y0) / (x1 - x0);  // 4,294,967,295 - 4,026,531,840 = 268,435,455  / 20 - 10 = 10  = 26,843,545.5-a
  uint64_t b = (-a * x0) + y0;         // -26,843,545.5 * 10 = -268,435,455 + 4,026,531,840 = 3,758,096,385-b
  uint32_t y = (a * x) + b;            //26,843,545.5 * 10 + 3,758,096,385 +
 return y;
}

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
