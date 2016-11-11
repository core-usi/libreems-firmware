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


/** @file
 *
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Echos the input on the first ignition output
 *
 * This decoder is for any 4 tooth/slot hall or optical cam speed sensor and to
 * be used for distributor and/or 4 shot batch injection only.
 *
 * To build a version of this decoder with a specific angle pair for your hall
 * or optical distributor, just define the DECODER_IMPLEMENTATION_C flag,
 * include the four required headers, define the angle for E1, and define the
 * unique decoder name string!
 *
 * To effectively reverse the polarity, just subtract your angle from 180 and
 * it will then be correct, assuming that either angle is correct.
 */


#define ANGLE_OF_SINGLE_ITERATION (180 * ANGLE_FACTOR)

#define E0 0
// Define E1 in your reverse header!
#define E2 (E0 + ANGLE_OF_SINGLE_ITERATION)
#define E3 (E1 + ANGLE_OF_SINGLE_ITERATION)
#define E4 (E0 + (2 * ANGLE_OF_SINGLE_ITERATION))
#define E5 (E1 + (2 * ANGLE_OF_SINGLE_ITERATION))
#define E6 (E0 + (3 * ANGLE_OF_SINGLE_ITERATION))
#define E7 (E1 + (3 * ANGLE_OF_SINGLE_ITERATION))


#if (E1 >= ANGLE_OF_SINGLE_ITERATION)
#error "Angle E1 defined to be larger than the available angle which it is within!"
#endif


const uint16_t inputAngles[] = {E0, E1, E2, E3, E4, E5, E6, E7};
const uint8_t eventValidForCrankSync[] = {0,0,0,0,0,0,0,0}; // Unused in this decoder.


void decoderSpecificInit(){
	TCTL4 = 0x03; /* Capture on both edges of T0 only, capture off for 1,2,3 */
} // This decoder works with the defaults
void decoderReset(){} // Nothing special to reset for this code


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
	uint16_t edgeTimeStamp = TC0;    /* Save the edge time stamp */
	uint8_t PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

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

	uint8_t lastEvent = 0;
	uint16_t thisTicksPerDegree = 0;
	if(PTITCurrentState & 0x01){
		// temporary data from inputs
		uint32_t primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		uint32_t timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastPrimaryEventTimeStamp;
		lastPrimaryEventTimeStamp = primaryLeadingEdgeTimeStamp;


		thisTicksPerDegree = (uint16_t)((TICKS_PER_DEGREE_MULTIPLIER * timeBetweenSuccessivePrimaryPulses) / ANGLE_OF_SINGLE_ITERATION);
		*ticksPerDegreeRecord = thisTicksPerDegree;

		// TODO Once sampling/RPM is configurable, use this tooth for a lower MAP reading.
		sampleEachADC(ADCBuffers);
		Counters.syncedADCreadings++;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		KeyUserDebugs.currentEvent = 1;
		lastEvent = 0;
	}else{
		// temporary data from inputs
		uint32_t secondaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		uint32_t timeBetweenSuccessiveSecondaryPulses = secondaryLeadingEdgeTimeStamp - lastSecondaryEventTimeStamp;
		lastSecondaryEventTimeStamp = secondaryLeadingEdgeTimeStamp;


		thisTicksPerDegree = (uint16_t)((TICKS_PER_DEGREE_MULTIPLIER * timeBetweenSuccessiveSecondaryPulses) / ANGLE_OF_SINGLE_ITERATION);
		*ticksPerDegreeRecord = thisTicksPerDegree;

		// TODO make this stuff behave correctly, this one will only run at startup, and the other will always run, but do it by generic config and split this stuff out into a shared function, soon.
		sampleEachADC(ADCBuffers);
		Counters.syncedADCreadings++;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		KeyUserDebugs.currentEvent = 0;
		lastEvent = 1;
	}

	uint32_t thisInterEventPeriod = 0;
	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		thisInterEventPeriod = thisEventTimeStamp - lastEventTimeStamp;
	}

	// This should check during gain of sync too and prevent gaining sync if the numbers aren't right, however this is a step up for the Hotel at this time.
	if(KeyUserDebugs.decoderFlags & COMBUSTION_SYNC){
		uint16_t thisAngle = 0;
		if(KeyUserDebugs.currentEvent == 0){
			// Fix this to work for all:
			//			thisAngle = eventAngles[KeyUserDebugs.currentEvent] + totalEventAngleRange - eventAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
			thisAngle = inputAngles[KeyUserDebugs.currentEvent] + ANGLE_OF_SINGLE_ITERATION - inputAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
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
			}
		}

		plotOutputs(KeyUserDebugs.currentEvent, timeStamp.timeLong, numberOfRealEvents);
		updateAngleDependantData(KeyUserDebugs.currentEvent, fixedConfigs1.engineSettings.cylinderCount, &(CylinderSetup[0]));
	}
	// SCHEDULE_ECT_OUTPUTS();

	OUTPUT_COARSE_BBS();

	/* TODO this delays outputs until the fourth ISR execution, but we could
	 * get them one execution or 1/8 of a rev sooner if we did a preliminary
	 * calc from the previous edge instead of the previous same edge now, and
	 *
	 * The proper way to do this is set sync when we have it and not set data
	 * as having been recorded until we know the data is good. That way the
	 * scheduler can keep things unscheduled until the time is right.
	 */
	if(KeyUserDebugs.decoderFlags & LAST_PERIOD_VALID){
		SET_SYNC_LEVEL_TO(COMBUSTION_SYNC);
	}

	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		lastTicksPerDegree = thisTicksPerDegree;
		KeyUserDebugs.decoderFlags |= LAST_PERIOD_VALID;
	}
	// Always
	lastEventTimeStamp = thisEventTimeStamp;
	KeyUserDebugs.decoderFlags |= LAST_TIMESTAMP_VALID;

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT0, PORTB);
}


#include "../../decoders_depricated/inc/defaultSecondaryRPMISR.c"
