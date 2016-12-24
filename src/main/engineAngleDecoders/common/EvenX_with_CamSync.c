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

#include <string.h>

#include "interface.c"

typedef struct {
	uint8_t expectingSync :1;
}InternalFlags;

volatile uint16_t   timerExtensionCounter_g;

/* Statics */
static uint16_t      previousPrimaryTicksPerDegree;
static InternalFlags internalFlags;


void decoderSpecificInit() {
  /* Raise interrupt priorities for crank and cam capture.
   * These should always be the same priority so that sync does not ever skip a tooth. */
  ROUTE_INTERRUPT(0x76, S12X_INTERRUPT, S12X_PRIORITY_LEVEL_SEVEN);
  ROUTE_INTERRUPT(0x77, S12X_INTERRUPT, S12X_PRIORITY_LEVEL_SEVEN);

  memset(&decoderStats_g, 0, sizeof(decoderStats_g));
  setCalcRequiredFlag();
}

void pulseAccumulatorOverflowISR() {
  PAFLG |= PA0VF;
}

void decoderReset() {
}

void PrimaryEngineAngle() {

	/* Clear the interrupt */
	TFLG1 = C0F;

	++decoderStats_g.primaryTeethSeen;

	/* Get current timestamp taking into account the overflow counter */
	ExtendedTime timeStamp;

	timeStamp.timeWord[1] = TC0;
	if (TFLG2 && !(TC0 & 0x8000)) {
		timeStamp.timeWord[0] = timerExtensionCounter_g + 1;
	} else {
		timeStamp.timeWord[0] = timerExtensionCounter_g;
	}
	/* Get ticksPerDegree so we can calc RPM and schedule events, if we have lock */
	if (decoderStats_g.decoderFlags.bits.previousPrimaryEventValid) {
		ExtendedTime interEventPeriod;
		interEventPeriod.time = diffUint32(timeStamp.time, decoderStats_g.lastPrimaryTimeStamp.time);
		decoderStats_g.instantTicksPerDegree = (uint16_t) ((TICKS_PER_DEGREE_MULTIPLIER * interEventPeriod.time)
				/ ANGLE_BETWEEN_TEETH);
	} else {
		decoderStats_g.instantTicksPerDegree = 0;
	}

	uint16_t ratioBetweenCurrentAndLast;

	if (decoderStats_g.decoderFlags.bits.phaseLock) {

		if (internalFlags.expectingSync) {
			decoderStats_g.currentPrimaryEvent = 0;
			internalFlags.expectingSync = 0;
		} else {
			++decoderStats_g.currentPrimaryEvent;
		}

		if (decoderStats_g.currentPrimaryEvent > TOTAL_ENGINE_CYCLE_INDEXES) {
			resetDecoderStatus(PRIMARY_EVENT_COUNT_TOO_HIGH);
			return;
		}

		if (decoderStats_g.decoderFlags.bits.primaryPeriodValid) {
			ratioBetweenCurrentAndLast = ratio16(previousPrimaryTicksPerDegree, decoderStats_g.instantTicksPerDegree,
					DECODER_STAMP_RATIO_F);
			decoderStats_g.primaryInputVariance = ratioBetweenCurrentAndLast;

			uint16_t allowedTollerance;
      decoderStats_g.RPM = (DEGREE_TICKS_PER_MINUTE / decoderStats_g.instantTicksPerDegree);

			//TODO(skeys) make these part of init!
			if (decoderStats_g.RPM < Config.tachDecoderSettings.maxCrankingRPM) {
				allowedTollerance = Config.tachDecoderSettings.inputEventCrankingTollerance;
			} else {
				allowedTollerance = Config.tachDecoderSettings.inputEventTollerance;
			}

			if (decoderStats_g.RPM > Config.tachDecoderSettings.filterBypassRPM) {
				if (ratioBetweenCurrentAndLast < allowedTollerance) {
					if (decoderStats_g.instantTicksPerDegree < previousPrimaryTicksPerDegree) {
						resetDecoderStatus(PRIMARY_EVENT_TOO_SOON);
					} else {
						resetDecoderStatus(PRIMARY_EVENT_TOO_LATE);
					}
					return;
				}
			}
		}

		/* Not really a recomended mode due to the loss of features, but it works */
		if (SYNCLESS_DIZZY_MODE) {
		  decoderStats_g.requiredSyncCycles = 0;
		  if (decoderStats_g.currentPrimaryEvent > TOTAL_ENGINE_CYCLE_INDEXES) {
		    decoderStats_g.currentPrimaryEvent = 0;
		  }
		}

		if (decoderStats_g.requiredSyncCycles == 0) {
			plotOutputs(&decoderStats_g, timeStamp.time, TOTAL_ENGINE_CYCLE_INDEXES);
			decoderStats_g.syncADCsamples += updateAngleDependantData(&decoderStats_g, Config.mechanicalProperties.cylinderCount,
					&(Config.CylinderSetup[0]));
		}
	}

	if (decoderStats_g.decoderFlags.bits.previousPrimaryEventValid) {
		previousPrimaryTicksPerDegree = decoderStats_g.instantTicksPerDegree;
		decoderStats_g.decoderFlags.bits.primaryPeriodValid = 1;
	}

	decoderStats_g.lastPrimaryTimeStamp = timeStamp;
	decoderStats_g.decoderFlags.bits.previousPrimaryEventValid = 1;

}


void SecondaryEngineAngle() {
	/* Clear the interrupt flag */
	TFLG1 = C1F;

	++decoderStats_g.secondaryTeethSeen;

	if (decoderStats_g.decoderFlags.bits.phaseLock) {
		ExtendedTime currentTimeStamp;
		/* Install the low word */
		currentTimeStamp.timeWord[1] = TC1;
		/* Handle a potential timer roll-over */
		if (TFLG2 && !(TC1 & 0x8000)) {
			currentTimeStamp.timeWord[0] = timerExtensionCounter_g + 1;
		} else {
			currentTimeStamp.timeWord[0] = timerExtensionCounter_g;
		}

		//decoderStats.engineCyclePeriod.time = diffUint32(currentTimeStamp.time, previousSecondaryInputTimeStamp.time);

		if (internalFlags.expectingSync) {
			resetDecoderStatus(PRIMARY_INPUT_DEAD);
		} else if (decoderStats_g.currentPrimaryEvent < TOTAL_ENGINE_CYCLE_INDEXES) {
			resetDecoderStatus(PRIMARY_EVENT_COUNT_TOO_LOW);
		} else if (decoderStats_g.currentPrimaryEvent > TOTAL_ENGINE_CYCLE_INDEXES) {
			resetDecoderStatus(PRIMARY_EVENT_COUNT_TOO_HIGH);
		}
		if (decoderStats_g.requiredSyncCycles) {
			--decoderStats_g.requiredSyncCycles;
		}
	} else {
		/* Set crank and cam/phase locked */
		decoderStats_g.decoderFlags.bits.crankLock = 1;
		decoderStats_g.decoderFlags.bits.phaseLock = 1;
		decoderStats_g.decoderFlags.bits.minimalSync = 1;
	}

	internalFlags.expectingSync = 1;
}

