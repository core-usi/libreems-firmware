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
 * @brief Prevents main loop from running calculations and finishes quickly
 *
 * The purpose of this "decoder" is purely to listen to the inputs and trick the
 * rest of the code into not running any calculations and just sending as many
 * logs as it can.
 *
 * This is useful to get a smooth logic analyser or other high speed log free
 * of gaps in the stream.
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    666 // This is optimal!
#define NUMBER_OF_REAL_EVENTS      1 // no events really...
#define NUMBER_OF_VIRTUAL_EVENTS   1 // no events really...

#include "../inc/freeEMS.h"
#include "../inc/interrupts_depricated.h"
#include "../inc/decoderInterface_depricated.h"

void decoderSpecificInit(){} // This decoder works with the defaults
void decoderReset(){} // Nothing special to reset for this code

const uint16_t inputAngles[] = {0};           // no events really...
const uint8_t eventValidForCrankSync[] = {0}; // no events really...


/* Keep disabling calcs as often as we can. */
void PrimaryEngineAngle(){
	extern Clock Clocks;
	extern KeyUserDebug KeyUserDebugs;
	/* Clear the interrupt flag for this input compare channel */
	TFLG1 = 0x01;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT0, PORTB);
	// Count the number of both negative and positive going pulses seen.
	KeyUserDebugs.primaryTeethSeen++;
	/* Reset the clock for reading timeout */
	Clocks.timeoutADCreadingClock = 0;
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT0, PORTB);
}


/* Keep disabling calcs as often as we can. */
void SecondaryEngineAngle(){
	extern Clock Clocks;
	extern KeyUserDebug KeyUserDebugs;
	/* Clear the interrupt flag for this input compare channel */
	TFLG1 = 0x02;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT1, PORTB);
	// Count the number of both negative and positive going pulses seen.
	KeyUserDebugs.secondaryTeethSeen++;
	/* Reset the clock for reading timeout */
	Clocks.timeoutADCreadingClock = 0;
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT1, PORTB);
}
