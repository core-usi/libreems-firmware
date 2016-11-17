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

#define TOTAL_CRANK_TEETH             60
#define MISSING_CRANK_TEETH            2

#define TOTAL_PHYSICAL_CRANK_TEETH    (TOTAL_CRANK_TEETH - MISSING_CRANK_TEETH)
#define TOTAL_ENGINE_CYCLE_INDEXES ((TOTAL_PHYSICAL_CRANK_TEETH * 2) - 1)
#define ANGLE_BETWEEN_TEETH            ENGINE_ANGLE_S((360 / TOTAL_CRANK_TEETH))


static inline void camSyncLogic(DecoderStats *decoderStats) {
	if (decoderStats->decoderFlags.bits.crankLock) {
		/* Correct phase if we are out */
		if (decoderStats->currentPrimaryEvent < TOTAL_PHYSICAL_CRANK_TEETH) {
			decoderStats->currentPrimaryEvent += TOTAL_PHYSICAL_CRANK_TEETH;
		}
		decoderStats->decoderFlags.bits.phaseLock = 1;
	}
}

#include "./common/Missing_Tooth.c"
