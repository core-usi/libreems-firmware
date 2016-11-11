/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2013 Fred Cooke
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
 * @ingroup allHeaders
 * @ingroup globalHeaders
 * @ingroup dataStructures
 *
 * @brief Counter struct typedefs
 *
 * This file contains all of the counter and statistic struct typedefs.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_COUNTER_TYPES_H_SEEN
#define FILE_COUNTER_TYPES_H_SEEN

#include <stdint.h>


// Some Fred Cooke cunning inspired by EssEss
#define FLAG_AND_INC_FLAGGABLE(OFFSET)         \
(*(((uint8_t*)&Flaggables) + OFFSET))++; \
KeyUserDebugs.flaggableFlags |= (1 << OFFSET);               // End of macro

/// These should all stay at zero, thus they are incremented through a mechanism that also sets a flag in a special variable
typedef struct {
  // Error conditions
  uint8_t callsToUISRs;                    ///< to ensure we aren't accidentally triggering unused ISRs.
  uint8_t lowVoltageConditions;            ///< low voltage conditions.
#define FLAG_CALLS_TO_UISRS_OFFSET                 0
#define FLAG_LOW_VOLTAGE_CONDITION_OFFSET          1

  // RPM/Position input
  uint8_t decoderSyncLosses;               ///< Number of times cam, crank or combustion sync is lost.
  uint8_t decoderSyncsNotConfirmed;        ///< How many times we cleared sync state without having yet accumulated enough confirmations.
  uint8_t decoderSyncStateClears;          ///< Sync loss called when not synced yet, thus discarding data and preventing sync.
#define FLAG_DECODER_SYNC_LOSSES_OFFSET            2
#define FLAG_DECODER_SYNCS_NOT_CONFIRMED_OFFSET    3
#define FLAG_DECODER_SYNC_STATE_CLEARS_OFFSET      4

  // If you're getting these, then your serial hardware sucks
  uint8_t serialNoiseErrors;               ///< Incremented when noise is detected
  uint8_t serialFramingErrors;             ///< Incremented when a framing error occurs
  uint8_t serialParityErrors;              ///< Incremented when a parity error occurs
#define FLAG_SERIAL_NOISE_ERRORS_OFFSET            5
#define FLAG_SERIAL_FRAMING_ERRORS_OFFSET          6
#define FLAG_SERIAL_PARITY_ERRORS_OFFSET           7

  // This is caused by heavy interrupt load delaying serial servicing, just a fact of life at high RPM.
  uint8_t serialOverrunErrors;             ///< Incremented when overrun occurs (duplicated in KeyUserDebug below)
#define FLAG_SERIAL_OVERRUN_ERRORS_OFFSET          8

  // These can be caused by noise, but if there is no noise, then it's a code issue with the PC side application
  uint8_t serialEscapePairMismatches;      ///< Incremented when an escape is found but not followed by an escapee
  uint8_t serialStartsInsideAPacket;       ///< Incremented when a start byte is found inside a packet
  uint8_t serialPacketsOverLength;         ///< Incremented when the buffer fills up before the end
  uint8_t serialChecksumMismatches;        ///< Incremented when calculated checksum did not match the received one
  uint8_t serialPacketsUnderLength;        ///< Incremented when a packet is found that is too short
#define FLAG_SERIAL_ESCAPE_PAIR_MISMATCHES_OFFSET  9
#define FLAG_SERIAL_STARTS_INSIDE_A_PACKET_OFFSET 10
#define FLAG_SERIAL_PACKETS_OVER_LENGTH_OFFSET    11
#define FLAG_SERIAL_CHECKSUM_MISMATCHES_OFFSET    12
#define FLAG_SERIAL_PACKETS_UNDER_LENGTH_OFFSET   13

  uint8_t phaseLockedLoopLockLost;         ///< Incremented when PLL lock is lost
  uint8_t selfClockModeEntered;            ///< Incremented when the MCU loses main clock
#define FLAG_PHASE_LOCKED_LOOP_LOCK_LOST_OFFSET   14
#define FLAG_SELF_CLOCK_MODE_ENTERED_OFFSET       15
} Flaggable;


// Some more Fred Cooke cunning inspired by EssEss
#define FLAG_AND_INC_FLAGGABLE2(OFFSET)         \
(*(((uint8_t*)&Flaggables2) + OFFSET))++; \
KeyUserDebugs.flaggableFlags2 |= (1 << OFFSET);               // End of macro

/// These should all stay at zero, thus they are incremented through a mechanism that also sets a flag in a special variable
typedef struct {
  // More error conditions
  uint8_t spuriousInterrupts;        ///< ? TODO
  uint8_t unimplementedOpcodes;      ///< ? TODO
  uint8_t RAMAccessViolations;       ///< ? TODO
  uint8_t XGATESoftwareErrors;       ///< ? TODO
#define FLAG_SPURIOUS_INTERRUPTS_OFFSET      0
#define FLAG_UNIMPLEMENTED_OPCODES_OFFSET    1
#define FLAG_RAM_ACCESS_VIOLATIONS_OFFSET    2
#define FLAG_XGATE_SOFTWARE_ERRORS_OFFSET    3

  uint8_t spare4;                    ///< Spare flaggable.
  uint8_t spare5;                    ///< Spare flaggable.
  uint8_t spare6;                    ///< Spare flaggable.
  uint8_t spare7;                    ///< Spare flaggable.
  uint8_t spare8;                    ///< Spare flaggable.
  uint8_t spare9;                    ///< Spare flaggable.
  uint8_t spare10;                   ///< Spare flaggable.
  uint8_t spare11;                   ///< Spare flaggable.
  uint8_t spare12;                   ///< Spare flaggable.
  uint8_t spare13;                   ///< Spare flaggable.
  uint8_t spare14;                   ///< Spare flaggable.
  uint8_t spare15;                   ///< Spare flaggable.
#define FLAG_SPARE_4_OFFSET                  4
#define FLAG_SPARE_5_OFFSET                  5
#define FLAG_SPARE_6_OFFSET                  6
#define FLAG_SPARE_7_OFFSET                  7
#define FLAG_SPARE_8_OFFSET                  8
#define FLAG_SPARE_9_OFFSET                  9
#define FLAG_SPARE_10_OFFSET                10
#define FLAG_SPARE_11_OFFSET                11
#define FLAG_SPARE_12_OFFSET                12
#define FLAG_SPARE_13_OFFSET                13
#define FLAG_SPARE_14_OFFSET                14
#define FLAG_SPARE_15_OFFSET                15
} Flaggable2;


/// Use this block to manage the various clocks kept.
typedef struct {
  /* Real Time and other Clocks (all require init to zero) */
  uint16_t realTimeClockMain;      ///< Variable to count RTI executions, 0.125ms exactly
  uint16_t realTimeClockMillis;    ///< Variable to count milliseconds exactly
  uint16_t realTimeClockTenths;    ///< Variable to count tenths of a second exactly
  uint16_t realTimeClockSeconds;   ///< Variable to count seconds exactly
  uint16_t realTimeClockMinutes;   ///< Variable to count minutes exactly

  uint16_t millisToTenths;         ///< Roll-over variable for counting tenths
  uint16_t tenthsToSeconds;        ///< Roll-over variable for counting seconds
  uint16_t secondsToMinutes;       ///< Roll-over variable for counting minutes

  uint16_t timeoutADCreadingClock; ///< Timeout clock/counter for synced ADC readings
  uint32_t milliSecondTotal;
} Clock;


/// Use this block to manage the execution count of various functions loops and ISRs etc. TODO break this up into smaller chunks
typedef struct {
  // Scheduling
  uint8_t normalSchedule;                  ///< times events were scheduled normally.
  uint8_t timerStretchedToSchedule;        ///< times timer needed to be extended to prevent not scheduling.

  // Decoder scheduling
  uint8_t pinScheduledToGoHigh;            ///< Behaviour chosen from decoder based on register and pin state.
  uint8_t pinScheduledAlready;             ///< @copydoc pinScheduledToGoHigh
  uint8_t pinScheduledToSelfSchedule;      ///< @copydoc pinScheduledToGoHigh
  uint8_t pinScheduledAgainToStayOn;       ///< @copydoc pinScheduledToGoHigh

  uint8_t pinScheduledToToggleError;       ///< @copydoc pinScheduledToGoHigh
  uint8_t pinScheduledToDoNothing;         ///< @copydoc pinScheduledToGoHigh
  uint8_t pinScheduledFromCold;            ///< @copydoc pinScheduledToGoHigh
  uint8_t pinScheduledWithTimerExtension;  ///< @copydoc pinScheduledToGoHigh

  // Outputs, refactor to not say "injector" later.
  uint8_t injectorSwitchOns;               ///< number of times the injector switched on
  uint8_t injectorSwitchOffs;              ///< number of times the injector switched off to stay off
  uint8_t injectorTimerExtensions;         ///< number of times the injector ISR fired and rescheduled itself to fire and do nothing again
  uint8_t injectorTimerExtensionFinals;    ///< number of times the injector ISR fired and scheduled the injector to switch on

  uint8_t injectorSelfSchedules;           ///< number of times the injector switched off and scheduled itself again
  uint8_t injectorSelfScheduleExtensions;  ///< number of times the injector switched off and scheduled itself again with timer extension

  uint8_t syncedADCreadings;               ///< Incremented each time a synchronous ADC reading is taken
  uint8_t timeoutADCreadings;              ///< Incremented for each ADC reading in RTC because of timeout
  uint8_t calculationsPerformed;           ///< Incremented for each time the fuel and ign calcs are done

  uint8_t sparePadding;                    ///< Replace with something useful
} Counter;


#else
  /* let us know if we are being untidy with headers */
  #warning "Header file COUNTER_TYPES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
