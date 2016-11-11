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
 * @ingroup allHeaders
 */


#ifndef DATA_ACQUISITION_H_SEEN
#define DATA_ACQUISITION_H_SEEN

#include <stdint.h>
#include "memory.h"
#include "libreMath.h"
#include "systemConfig.h"
#include "outputPlotter.h"
#include "../engineAngleDecoders/common/interface.h"

#define TIMER_OVERFLOWS_PER_SECOND      19  /* Number of times TCNT overflows per second */
#define CONTINENTAL_ERROR_WINDOW         5  /* continental flex fuel sensor minimum frequency 0% Ethalon */
#define CONTINENTAL_FS_RANGE_LOWER      50  /* continental flex fuel sensor minimum frequency 0% Ethalon */
#define CONTINENTAL_FS_RANGE_UPPER     150  /* continental flex fuel sensor maximum frequency 100% Ethanol */

inline void readRTADCValues(SyncedData *buffer) TEXT;
inline uint8_t updateAngleDependantData(DecoderStats *decoderStats, uint8_t numOutputs, CylinderConfig*) TEXT;
void sampleAllSyncData() TEXT;
uint8_t readFlexFuelEth() TEXT;
void updateCapturedInput(uint8_t flags, CapturedInputData *dataStore, ExtendedTime *previousStamp, ExtendedTime *captureStamp) TEXT;

#else

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
