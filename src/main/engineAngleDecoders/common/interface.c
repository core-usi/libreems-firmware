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
 * @ingroup Configuration
 *
 */

#include "interface.h"
#include "../../inc/mathFunctions.h"


const uint8_t decoderName[] = BASE_FILE_NAME;

void setCalcRequiredFlag() {
  uint8_t i;

  for (i = 0; i < ENGINE_CYLINDER_COUNT; ++i) {
    Config.CylinderSetup[i].igntionEvent->eventFlags |= EVENT_CALC_REQUIRED;
    Config.CylinderSetup[i].primaryFuelEvent->eventFlags |= EVENT_CALC_REQUIRED;
    Config.CylinderSetup[i].secondaryFuelEvent->eventFlags |= EVENT_CALC_REQUIRED;
  }
}

void resetDecoderStatus(uint8_t reasonCode) {

  decoderStats_g.decoderFlags.var        = 0;
  decoderStats_g.instantTicksPerDegree   = 0;
  decoderStats_g.lastPrimaryTimeStamp.time  = 0;
  decoderStats_g.eventLockWasLost        = decoderStats_g.currentPrimaryEvent;
  decoderStats_g.RPM                     = 0;
  decoderStats_g.lockLossCauseID         = reasonCode;
  ++decoderStats_g.decoderResetCalls;

  if (reasonCode != PRIMARY_INPUT_TIMEOUT) {
    decoderStats_g.requiredSyncCycles      = 2;
  }

  setCalcRequiredFlag();

  decoderReset();
}

//TODO(skeys) revisit this so we can return the data vs pointer
DecoderStats* getDecoderStats() {
  return &decoderStats_g;
}
