/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2013 Fred Cooke
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


#define DECODER_IMPLEMENTATION_C

#include "../decoders_depricated/inc/MitsiAndMazda-CAS-4and2.h"

void decoderSpecificInit(){} // This decoder works with the defaults
void decoderReset(){
	doubleHighSeen = 0;
}


/** @file
 *
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Reads Mitsi 4 and 2 CAS units
 *
 * Two interrupts share state and cross communicate to
 * find and maintain sync and position information.
 *
 * Development thread: http://forum.diyefi.org/viewtopic.php?f=56&t=1110
 */


void PrimaryEngineAngle(){
	extern Clock Clocks;
	extern Counter Counters;
	extern KeyUserDebug KeyUserDebugs;
	extern const volatile fixedConfig1 fixedConfigs1;                                                                                                
	extern const volatile fixedConfig2 fixedConfigs2;
	/* Clear the interrupt flag for this input compare channel */
	TFLG1 = C0F;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT0, PORTB);

	/* Save all relevant available data here */
	edgeTimeStamp = TC0;                   /* Save the edge time stamp */
	uint8_t PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

	KeyUserDebugs.primaryTeethSeen++;

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
		thisInterEventPeriod = thisEventTimeStamp - lastEventTimeStamp;
	}

	// Always sample in this ISR
	sampleEachADC(ADCBuffers);
	Counters.syncedADCreadings++;

	// Set flag to say calc required
	coreStatusA |= CALC_FUEL_IGN;

	// Reset the clock for reading timeout
	Clocks.timeoutADCreadingClock = 0;

	// Determine the correct event based on post transition state
	uint8_t correctEvent = 0;
	if(PTITCurrentState & 0x01){
		if(!(PTITCurrentState & 0x02)){
			correctEvent = 10;
		}else{ // Occurs three times
			doubleHighSeen = 1;
		}
	}else{
		if(PTITCurrentState & 0x02){
			// Only this one is not intercepted by a clear
			if(doubleHighSeen == 1){
				correctEvent = 6;
			}
		}else{ // Clear on double low
			doubleHighSeen = 0;
		}
	}

	uint8_t lastEvent = 0;
	if(KeyUserDebugs.decoderFlags & CAM_SYNC){
		lastEvent = KeyUserDebugs.currentEvent;
		KeyUserDebugs.currentEvent++;
		if(KeyUserDebugs.currentEvent == numberOfRealEvents){
			KeyUserDebugs.currentEvent = 0;
		}

		// ...and check that it's correct
		if(correctEvent != 0){
			if(KeyUserDebugs.currentEvent != correctEvent){
				resetToNonRunningState(STATE_MISMATCH_IN_PRIMARY_RPM_ISR);
				return;
			}else if(!(KeyUserDebugs.decoderFlags & OK_TO_SCHEDULE)){
				SET_SYNC_LEVEL_TO(CAM_SYNC);
			} // Else do nothing, we're running!
		}
	}else if(correctEvent != 0){
		KeyUserDebugs.currentEvent = correctEvent;
		lastEvent = KeyUserDebugs.currentEvent - 1;
		SET_SYNC_LEVEL_TO(CAM_SYNC);
	}

	uint16_t thisTicksPerDegree = 0;
	if(KeyUserDebugs.decoderFlags & CAM_SYNC){
		uint16_t thisAngle = 0;
		if(KeyUserDebugs.currentEvent == 0){
			thisAngle = inputAngles[KeyUserDebugs.currentEvent] + totalEventAngleRange - inputAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
		}else{
			thisAngle = inputAngles[KeyUserDebugs.currentEvent] - inputAngles[lastEvent];
		}

		thisTicksPerDegree = (uint16_t)((TICKS_PER_DEGREE_MULTIPLIER * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

		if(KeyUserDebugs.decoderFlags & LAST_PERIOD_VALID){
			uint16_t ratioBetweenThisAndLast = (uint16_t)(((uint32_t)lastTicksPerDegree * 1000) / thisTicksPerDegree);
			KeyUserDebugs.inputEventTimeTolerance = ratioBetweenThisAndLast;
			if(ratioBetweenThisAndLast > fixedConfigs2.decoderSettings.decelerationInputEventTimeTolerance){
				resetToNonRunningState(PRIMARY_EVENT_ARRIVED_TOO_LATE);
				return;
			}else if(ratioBetweenThisAndLast < fixedConfigs2.decoderSettings.accelerationInputEventTimeTolerance){
				resetToNonRunningState(PRIMARY_EVENT_ARRIVED_TOO_EARLY);
				return;
			}else{
				if(PTITCurrentState & 0x01){
					// TODO Calculate RPM from last primaryLeadingEdgeTimeStamp
				}else{
					// TODO Calculate RPM from last primaryTrailingEdgeTimeStamp
				}
			}
		}/*else*/ if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){ // TODO temp for testing just do rpm this way, fill above out later.
			*ticksPerDegreeRecord = thisTicksPerDegree;
		}
		plotOutputs(KeyUserDebugs.currentEvent, timeStamp.timeLong, numberOfRealEvents);
		updateAngleDependantData(KeyUserDebugs.currentEvent, fixedConfigs1.engineSettings.cylinderCount, &(CylinderSetup[0]));
	}

	//SCHEDULE_ECT_OUTPUTS();

	OUTPUT_COARSE_BBS();

	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		lastTicksPerDegree = thisTicksPerDegree;
		KeyUserDebugs.decoderFlags |= LAST_PERIOD_VALID;
	}
	// Always
	lastEventTimeStamp = thisEventTimeStamp;
	KeyUserDebugs.decoderFlags |= LAST_TIMESTAMP_VALID;

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT0, PORTB);
}


void SecondaryEngineAngle(){
	extern Clock Clocks;
	extern Counter Counters;
	extern KeyUserDebug KeyUserDebugs;
	extern const volatile fixedConfig1 fixedConfigs1;                                                                                                
	extern const volatile fixedConfig2 fixedConfigs2;
	// Reads the inner slot on the disk.

	/* Clear the interrupt flag for this input compare channel */
	TFLG1 = C1F;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT1, PORTB);

	/* Save all relevant available data here */
	edgeTimeStamp = TC1;                   /* Save the timestamp */
	uint8_t PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

	KeyUserDebugs.secondaryTeethSeen++;
	// remember that this is both edges, though... 8 per cycle, 4 per rev for the outter wheel, 2/1 for this wheel.

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
		thisInterEventPeriod = thisEventTimeStamp - lastEventTimeStamp;
	}

	// Determine the correct event based on post transition state (and toggle debug pins)
	uint8_t correctEvent = 0;
	if(PTITCurrentState & 0x02){
		if(PTITCurrentState & 0x01){
			correctEvent = 11;
		}else{
			correctEvent = 4;
		}
	} // else the leading edge of the slot is ambiguous

	// Only sample if not synced, cleans up readings.
	if(!(KeyUserDebugs.decoderFlags & CAM_SYNC)){
		sampleEachADC(ADCBuffers);
		Counters.syncedADCreadings++;

		// Set flag to say calc required
		coreStatusA |= CALC_FUEL_IGN;

		// Reset the clock for reading timeout
		Clocks.timeoutADCreadingClock = 0;
	}

	uint8_t lastEvent = 0;
	if(KeyUserDebugs.decoderFlags & CAM_SYNC){
		lastEvent = KeyUserDebugs.currentEvent;
		KeyUserDebugs.currentEvent++;

		// ...and check that it's correct
		if(correctEvent != 0){
			if(KeyUserDebugs.currentEvent != correctEvent){
				resetToNonRunningState(STATE_MISMATCH_IN_SECONDARY_RPM_ISR);
				return;
			}else if(!(KeyUserDebugs.decoderFlags & OK_TO_SCHEDULE)){
				SET_SYNC_LEVEL_TO(CAM_SYNC);
			} // Else do nothing, we're running!
		}
	}else if(correctEvent != 0){
		KeyUserDebugs.currentEvent = correctEvent;
		lastEvent = KeyUserDebugs.currentEvent - 1;
		SET_SYNC_LEVEL_TO(CAM_SYNC);
	}

	uint16_t thisTicksPerDegree = 0;
	if(KeyUserDebugs.decoderFlags & CAM_SYNC){
		uint16_t thisAngle = inputAngles[KeyUserDebugs.currentEvent] - inputAngles[lastEvent];

		thisTicksPerDegree = (uint16_t)((TICKS_PER_DEGREE_MULTIPLIER * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

		if(KeyUserDebugs.decoderFlags & LAST_PERIOD_VALID){
			uint16_t ratioBetweenThisAndLast = (uint16_t)(((uint32_t)lastTicksPerDegree * 1000) / thisTicksPerDegree);
			KeyUserDebugs.inputEventTimeTolerance = ratioBetweenThisAndLast;
			if(ratioBetweenThisAndLast > fixedConfigs2.decoderSettings.decelerationInputEventTimeTolerance){
				resetToNonRunningState(SECONDARY_EVENT_ARRIVED_TOO_LATE);
				return;
			}else if(ratioBetweenThisAndLast < fixedConfigs2.decoderSettings.accelerationInputEventTimeTolerance){
				resetToNonRunningState(SECONDARY_EVENT_ARRIVED_TOO_EARLY);
				return;
			}
		}/*else*/ if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
			*ticksPerDegreeRecord = thisTicksPerDegree;
		}
		plotOutputs(KeyUserDebugs.currentEvent, timeStamp.timeLong, numberOfRealEvents);
		updateAngleDependantData(KeyUserDebugs.currentEvent, fixedConfigs1.engineSettings.cylinderCount, &(CylinderSetup[0]));
	}

	//SCHEDULE_ECT_OUTPUTS();

	OUTPUT_COARSE_BBS();

	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		lastTicksPerDegree = thisTicksPerDegree;
		KeyUserDebugs.decoderFlags |= LAST_PERIOD_VALID;
	}
	// Always
	lastEventTimeStamp = thisEventTimeStamp;
	KeyUserDebugs.decoderFlags |= LAST_TIMESTAMP_VALID;

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT1, PORTB);
}
