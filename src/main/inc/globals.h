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
 * @ingroup TODO
 *
 * @brief TODO
 *
 *
 */

#ifndef FILE_GLOBALS_H_SEEN
#define FILE_GLOBALS_H_SEEN

#include "outputPlotter.h"
#include "Configuration.h"
#include "libreTypes.h"

extern uint16_t ticksPerDegree_g;

extern uint8_t dataLogCylinderIndex;
extern uint8_t sharedVar;
extern BTpatternParameters BTpatternParemeterSet;
extern uint16_t timerRegisterFlags;
extern uint16_t TPSrange_g;
extern uint32_t injectorFlowDifference_g;

extern outputEvent outputSchedules[MAX_NUMBER_OF_OUTPUT_EVENTS];
extern uint8_t currentFuelingAlgorithm_g;
extern outputAction* nextEventPTR;
extern XGoutputEvent XGoutputEvents[MAX_NUMBER_OF_OUTPUT_EVENTS];
extern fuelAttributes FuelAttribs;
extern uint8_t currentFuelingAlgorithm_g;
extern SyncedData syncedEngineData[ENGINE_CYLINDER_COUNT];
extern uint16_t nullScratch XG_SHARED;
extern CANflags CANflags_g;
extern CapturedInputData capturedInputData_g[GP_CAPTURE_CHANNELS];
extern CapturedInputData *gpCapture_g;
extern volatile uint16_t timerExtensionCounter_g;

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
