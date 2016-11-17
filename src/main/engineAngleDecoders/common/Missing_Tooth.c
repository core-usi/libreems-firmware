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

#include "../common/interface.c"


/* Statics */
static ExtendedTime previousPrimaryInputTimeStamp;
static uint16_t     previousPrimaryTicksPerDegree;
static ExtendedTime previousTimePeriod;

static uint8_t      consecutiveEvenTeethFound;


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

	uint16_t  ticksPerDegree = 0;

	/* Get ticksPerDegree so we can calc RPM and schedule events, if we have lock */
	if (decoderStats_g.decoderFlags.bits.previousPrimaryEventValid) {

		uint16_t     ratioBetweenCurrentAndLast;
		ExtendedTime interEventPeriod;

		interEventPeriod.time = diffUint32(timeStamp.time, previousPrimaryInputTimeStamp.time);
		ticksPerDegree = ((uint32_t)(TICKS_PER_DEGREE_MULTIPLIER * interEventPeriod.time)) / ANGLE_BETWEEN_TEETH;

		 /* Check sync and schedule */
		if (decoderStats_g.decoderFlags.bits.crankLock) {
			if (decoderStats_g.requiredSyncCycles) {
				--decoderStats_g.requiredSyncCycles;
			}

			++decoderStats_g.currentPrimaryEvent;
			/* See if we need to roll over */
			if (decoderStats_g.currentPrimaryEvent > TOTAL_ENGINE_CYCLE_INDEXES) {
					decoderStats_g.currentPrimaryEvent = 0;
			}

			uint8_t allowedTolleranceScaler;

			/* If we are expecting a missing tooth adjust period here */
			if ((decoderStats_g.currentPrimaryEvent  == TOTAL_PHYSICAL_CRANK_TEETH) ||
			    (decoderStats_g.currentPrimaryEvent  == 0)) {
				ticksPerDegree = ticksPerDegree / (1 + MISSING_CRANK_TEETH); // Divide by number of missing teeth + 1
				allowedTolleranceScaler = (1 + MISSING_CRANK_TEETH);
			} else {
			  allowedTolleranceScaler = 1;
			}

      /* TODO instead of TPD use current and previous period, less math less jitter */
			ratioBetweenCurrentAndLast = ratio16(previousPrimaryTicksPerDegree, ticksPerDegree, DECODER_STAMP_RATIO_F);
			decoderStats_g.primaryInputVariance = ratioBetweenCurrentAndLast;
			decoderStats_g.instantTicksPerDegree = ticksPerDegree;

			/* Missing teeth are already accounted for, so the math stays the same */
			uint16_t allowedTollerance;
			uint16_t RPM = GET_RPM(decoderStats_g.instantTicksPerDegree);

			decoderStats_g.RPM = RPM;

			//TODO(skeys) make these part of init!
			if (RPM < Config.tachDecoderSettings.maxCrankingRPM) {
				allowedTollerance = Config.tachDecoderSettings.inputEventCrankingTollerance;
			} else {
				allowedTollerance = Config.tachDecoderSettings.inputEventTollerance;
			}

			/* Here we apply an allowed tolerance scaler.
			 * If we go over a missing tooth and our tolerance is say 10%,
			 * then we should allow 20% for the next physical tooth(10+10),
			 * since we moved twice as many crank degrees.
			 */
			allowedTollerance *= allowedTolleranceScaler;

			if (ratioBetweenCurrentAndLast < allowedTollerance) {
				if (decoderStats_g.instantTicksPerDegree < previousPrimaryTicksPerDegree) {
					resetDecoderStatus(PRIMARY_EVENT_TOO_SOON);
				} else {
					resetDecoderStatus(PRIMARY_EVENT_TOO_LATE);
				}
				return;
			}

			/* Do our angle based I/O */
			if (decoderStats_g.requiredSyncCycles == 0) {

				if (decoderStats_g.decoderFlags.bits.minimalSync) {
				  if (decoderStats_g.decoderFlags.bits.phaseLock) {
	          plotOutputs(&decoderStats_g, timeStamp.time, TOTAL_ENGINE_CYCLE_INDEXES);
	          decoderStats_g.syncADCsamples += updateAngleDependantData(&decoderStats_g, Config.mechanicalProperties.cylinderCount,
	                                &(Config.CylinderSetup[0]));
				  } else if (Config.tachDecoderSettings.minimalSyncRequired == CRANK_ONLY) {
				    /* Semi Sequential scheduling */
						uint8_t savedIndex = decoderStats_g.currentPrimaryEvent;
						/* Fairly dirty hack, but its OK on this platform because this ISR is atomic */
						if (decoderStats_g.currentPrimaryEvent < TOTAL_PHYSICAL_CRANK_TEETH) {
							decoderStats_g.currentPrimaryEvent += TOTAL_PHYSICAL_CRANK_TEETH;
						} else {
							decoderStats_g.currentPrimaryEvent -= TOTAL_PHYSICAL_CRANK_TEETH;
						}

						plotOutputs(&decoderStats_g, timeStamp.time, TOTAL_ENGINE_CYCLE_INDEXES);
						decoderStats_g.syncADCsamples += updateAngleDependantData(&decoderStats_g, Config.mechanicalProperties.cylinderCount,
												&(Config.CylinderSetup[0]));
						decoderStats_g.currentPrimaryEvent = savedIndex;

            plotOutputs(&decoderStats_g, timeStamp.time, TOTAL_ENGINE_CYCLE_INDEXES);
            decoderStats_g.syncADCsamples += updateAngleDependantData(&decoderStats_g, Config.mechanicalProperties.cylinderCount,
                                  &(Config.CylinderSetup[0]));
					}

				}
			} else {
			  // Potentially update angle dependent data
			}

		} else { /* Try to find sync */

			ratioBetweenCurrentAndLast = ratio16(previousPrimaryTicksPerDegree, ticksPerDegree, DECODER_STAMP_RATIO_F);
			decoderStats_g.primaryInputVariance  = ratioBetweenCurrentAndLast; /* Record raw when not synced */

			/* Default to cranking tollerance, when not in sync */
			uint16_t allowedTollerance = Config.tachDecoderSettings.inputEventCrankingTollerance;

			//TODO add additional checks for correct TPD direction
			if ((ratioBetweenCurrentAndLast < allowedTollerance) &&
					ticksPerDegree > previousPrimaryTicksPerDegree) {
				/* see if we have seen a min number of skip teeth */
				if (consecutiveEvenTeethFound > 3) {
					ticksPerDegree /= 2; /* mul by num of missing teeth plus 1 */
					ratioBetweenCurrentAndLast = mul16(ratioBetweenCurrentAndLast, 2);

					//TODO correct allowedTollerance by adding total between missing teeth
					if (ratioBetweenCurrentAndLast < allowedTollerance) {
						consecutiveEvenTeethFound = 0;
						if (ticksPerDegree < previousPrimaryTicksPerDegree) {
							resetDecoderStatus(PRIMARY_EVENT_TOO_SOON_UNSYNC);
						} else {
							resetDecoderStatus(PRIMARY_EVENT_TOO_LATE_UNSYNC);
						}
						return;
					} else {
						decoderStats_g.decoderFlags.bits.crankLock = 1;
						decoderStats_g.decoderFlags.bits.minimalSync = 1; /* TODO make a config item */
						decoderStats_g.currentPrimaryEvent = 0;
					}
				} else {
					consecutiveEvenTeethFound = 0;
				}

			} else {
				++consecutiveEvenTeethFound;
			}
			decoderStats_g.instantTicksPerDegree = ticksPerDegree; /* Record for cranking RPM log */
		}
		previousTimePeriod = interEventPeriod;
	} else {

	}

	if (decoderStats_g.decoderFlags.bits.previousPrimaryEventValid) {
		previousPrimaryTicksPerDegree = ticksPerDegree;  /* Always save the raw TPD */
		decoderStats_g.decoderFlags.bits.primaryPeriodValid = 1;
	}

	previousPrimaryInputTimeStamp = timeStamp;
	decoderStats_g.decoderFlags.bits.previousPrimaryEventValid = 1;

}


void SecondaryEngineAngle() {
	++decoderStats_g.secondaryTeethSeen;
	camSyncLogic(&decoderStats_g);
	TFLG1 = C1F;
	return;
}
