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

#include "common/interface.h"



static inline void camSyncLogic(DecoderStats *decoderStats) {

  if (decoderStats->decoderFlags.bits.phaseLock) {
    /* TODO Additional trickery needed, as when the coil on cyl #1 fires, it
     *  causes a false cam sync pulse, even with the MAX chip. This is a known
     *  issue, in the aftermarket ECU community, with the cam sync on the
     *   Hayabuysa.
     */
  } else {
    if (decoderStats->decoderFlags.bits.crankLock) {
      if ((decoderStats->currentPrimaryEvent == 0) ||
          (decoderStats->currentPrimaryEvent == TOTAL_PHYSICAL_CRANK_TEETH)) {
        /* Correct phase if we are out */
        if (decoderStats->currentPrimaryEvent != TOTAL_PHYSICAL_CRANK_TEETH) {
          decoderStats->currentPrimaryEvent = 0;
        }
        decoderStats->decoderFlags.bits.phaseLock = 1;
        decoderStats->decoderFlags.bits.minimalSync = 1;
      } else {
        /* TODO drop sync, missing tooth decoder failed */
        resetDecoderStatus(FALSE_CRANK_SYNC);
      }
      }
  }

}

#include "./common/Missing_Tooth.c"
