/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2012 Fred Cooke
 *
 * This file is part of the FreeEMS project.
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
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief For evenly spaced teeth on the cam or crank with a single second input.
 *
 * Fill out a data reverse header and include this file. Sync is provided by the
 * second input allowing a sequential and/or COP/CNP setup to be used.
 *
 * VR edition with only one edge used!
 */

#include <string.h>

#include "../../inc/outputPlotter.h"
#include "../../inc/dataAcquisition.h"
#include "../../inc/mathFunctions.h"

static uint16_t lastRatio;

void decoderSpecificInit() {
  memset(&decoderStats_g, 0, sizeof(decoderStats_g));
}

void decoderReset(){} // Nothing special to reset for this code

void PrimaryEngineAngle(){

	extern Clock Clocks;
	extern Counter Counters;
	extern KeyUserDebug KeyUserDebugs;

	/* Clear the interrupt flag for this input compare channel */
	TFLG1 = C0F;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT0, PORTB);

	/* Save all relevant available data here */
	uint16_t edgeTimeStamp = TC0;    /* Save the edge time stamp */
	uint8_t PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

	// Prevent main from clearing values before sync is obtained!
	Clocks.timeoutADCreadingClock = 0;

	KeyUserDebugs.primaryTeethSeen++;

	LongTime timeStamp;
	/* Install the low word */
	timeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if(TFLG2 && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		timeStamp.timeShorts[0] = timerExtensionCounter_g + 1;
	}else{
		timeStamp.timeShorts[0] = timerExtensionCounter_g;
	}
	uint32_t thisEventTimeStamp = timeStamp.timeLong;

	uint32_t thisInterEventPeriod = 0;
	uint16_t thisTicksPerDegree = 0;
	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		thisInterEventPeriod = diffUint32(thisEventTimeStamp, lastPrimaryEventTimeStamp);
		thisTicksPerDegree = (uint16_t)((TICKS_PER_DEGREE_MULTIPLIER * thisInterEventPeriod) / inputAngles[1]); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error
	}
	uint16_t ratioBetweenCurrentAndLast;
	if(KeyUserDebugs.decoderFlags & CONFIGURED_SYNC){
		KeyUserDebugs.currentEvent++;
		if(KeyUserDebugs.currentEvent == numberOfRealEvents){
			resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE);
			return;
		}// Can never be greater than without a code error or genuine noise issue, so give it a miss as we can not guarantee where we are now.

		if(KeyUserDebugs.decoderFlags & LAST_PERIOD_VALID){
			ratioBetweenCurrentAndLast = ratio16(lastPrimaryTicksPerDegree, thisTicksPerDegree, DECODER_STAMP_RATIO_F);
			KeyUserDebugs.inputEventTimeTolerance = ratioBetweenCurrentAndLast;

			uint16_t allowedTollerance;
			uint16_t RPM = (uint16_t)(DEGREE_TICKS_PER_MINUTE / thisTicksPerDegree);

			if (RPM < Config.tachDecoderSettings.maxCrankingRPM) {
				allowedTollerance = Config.tachDecoderSettings.inputEventCrankingTollerance;
			} else {
				allowedTollerance = Config.tachDecoderSettings.inputEventTollerance;
			}

			if(ratioBetweenCurrentAndLast < allowedTollerance){
				if (lastRatio > ratioBetweenCurrentAndLast) {
					resetToNonRunningState(PRIMARY_EVENT_ARRIVED_TOO_EARLY);
				} else {
					resetToNonRunningState(PRIMARY_EVENT_ARRIVED_TOO_LATE);
				}
				return;
			} else{
				if(PTITCurrentState & 0x01){
					// TODO Calculate RPM from last primaryLeadingEdgeTimeStamp
				}else{
					// TODO Calculate RPM from last primaryTrailingEdgeTimeStamp
				}
			}
			lastRatio = ratioBetweenCurrentAndLast;
		}/*else*/ if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){ // TODO temp for testing just do rpm this way, fill above out later.
			*ticksPerDegreeRecord = thisTicksPerDegree;

			Counters.syncedADCreadings++;

			// Set flag to say calc required
			coreStatusA |= CALC_FUEL_IGN;

			// Reset the clock for reading timeout
			Clocks.timeoutADCreadingClock = 0;
		}

		plotOutputs(KeyUserDebugs.currentEvent, timeStamp.timeLong, numberOfRealEvents);
		updateAngleDependantData(KeyUserDebugs.currentEvent, Config.mechanicalProperties.cylinderCount, &(Config.CylinderSetup[0]));
	}

	//OUTPUT_COARSE_BBS();

	// do these always at first, and use them with a single 30 degree angle for the first cut
	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		lastPrimaryTicksPerDegree = thisTicksPerDegree;

		KeyUserDebugs.decoderFlags |= LAST_PERIOD_VALID;
	}
	// Always
	lastPrimaryEventTimeStamp = thisEventTimeStamp;
	KeyUserDebugs.decoderFlags |= LAST_TIMESTAMP_VALID;
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT0, PORTB);

}


void SecondaryEngineAngle(){
	extern KeyUserDebug KeyUserDebugs;
	/* Clear the interrupt flag */
	TFLG1 = C1F;

	/* Save all relevant available data here */
	uint16_t edgeTimeStamp = TC1;    /* Save the timestamp */
//	uint8_t PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

	KeyUserDebugs.secondaryTeethSeen++;

	LongTime timeStamp;
	/* Install the low word */
	timeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if(TFLG2 && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		timeStamp.timeShorts[0] = timerExtensionCounter_g + 1;
	}else{
		timeStamp.timeShorts[0] = timerExtensionCounter_g;
	}
	uint32_t thisEventTimeStamp = timeStamp.timeLong;

	uint32_t thisInterEventPeriod = 0;
	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		thisInterEventPeriod = diffUint32(thisEventTimeStamp, lastSecondaryEventTimeStamp);
	}

	// This sets currentEvent to 255 such that when the primary ISR runs it is rolled over to zero!
	if(KeyUserDebugs.decoderFlags & CONFIGURED_SYNC){
		/* If the count is less than 23, then we know that the electrical pulse that triggered
		 * this ISR execution was almost certainly in error and it is NOT valid to stay in sync.
		 *
		 * If the count is greater than 24, then we know that an electrical noise pulse triggered
		 * the other interrupt in between and was missed by the time period checks (unlikely, but
		 * possible) and that, therefore, there could have been a noise pulse on this input too,
		 * and therefore we don't really know where we are.
		 *
		 * In the case where the count is exactly 24 we can only rely on the time period checks in
		 * the other ISR, which should be sufficient unless poorly setup by a user with too wide
		 * of a tolerance level.
		 *
		 * There is zero point adding relative timing checks to this ISR because by nature, the
		 * other N teeth have already checked out good timing wise and therefore the average also
		 * does. Thus if we did check, for it to ever fail it would need to be tighter, and in
		 * reality it must be more loose due to the larger possible variation over the much much
		 * larger time frame.
		 */
		if(KeyUserDebugs.currentEvent < (numberOfRealEvents - 1)){
			resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_LOW_NOISE);
		}else if(KeyUserDebugs.currentEvent > (numberOfRealEvents -1)){
			resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE);
		} // ELSE do nothing, and be happy :-)
	}else{ // If not synced, sync, as this is our reference point.
		SET_SYNC_LEVEL_TO(CONFIGURED_SYNC);
	}
	KeyUserDebugs.currentEvent = 0xFF; // TODO reset always, and catch noise induced errors below, this behavior (now some lines above) may be bad/not fussy enough, or could be good, depending upon determinate nature of the inter event timing between primary and secondary, or not, perhaps move "lose sync or correct sync" as a configuration variable

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT1, PORTB);
}
