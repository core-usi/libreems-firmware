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

#include "common/interface.c"

typedef struct {
	uint8_t lastWindowMatch :1;
	uint8_t expectingSync   :1;
}InternalFlags;

#define EDGE_TOLLERANCE      (3)
#define HIGH_RES_ANGLE_VALUE (2)
#define SYNC_OFFSET          (2)  //This should be in the middle of the emulated count

/* Window counts when capturing on the rising edge */
#define WINDOW_ONE_COUNT     (25)
#define WINDOW_TWO_COUNT     (50)
#define WINDOW_THREE_COUNT   (40)
#define WINDOW_FOUR_COUNT    (55)
#define WINDOW_FIVE_COUNT    (35)
#define WINDOW_SIX_COUNT     (60)
#define WINDOW_SEVEN_COUNT   (30)
#define WINDOW_EIGHT_COUNT   (65)

/* Total window counts when starting from 0 */
#define INDEX_ONE_TOTAL   (WINDOW_ONE_COUNT)
#define INDEX_TWO_TOTAL   (INDEX_ONE_TOTAL   + WINDOW_TWO_COUNT)
#define INDEX_THREE_TOTAL (INDEX_TWO_TOTAL   + WINDOW_THREE_COUNT)
#define INDEX_FOUR_TOTAL  (INDEX_THREE_TOTAL + WINDOW_FOUR_COUNT)
#define INDEX_FIVE_TOTAL  (INDEX_FOUR_TOTAL  + WINDOW_FIVE_COUNT)
#define INDEX_SIX_TOTAL   (INDEX_FIVE_TOTAL  + WINDOW_SIX_COUNT)
#define INDEX_SEVEN_TOTAL (INDEX_SIX_TOTAL   + WINDOW_SEVEN_COUNT)
#define INDEX_EIGHT_TOTAL (INDEX_SEVEN_TOTAL + WINDOW_EIGHT_COUNT)

#define DEGRESS_PER_CYCLE                        (720)
#define HIGH_RES_TEETH_PER_EMULATED_CRANK_TOOTH  ((DEGREES_PER_CRANK_ROTATION / TOTAL_CRANK_TEETH) / HIGH_RES_ANGLE_VALUE)
#define DEGREES_PER_INDEX         (DEGRESS_PER_CYCLE / (TOTAL_CRANK_TEETH * 2))

#define DEGREE_TO_INDEX(degree)   ((uint8_t)(((degree * HIGH_RES_ANGLE_VALUE) % DEGRESS_PER_CYCLE / DEGREES_PER_INDEX)))

volatile uint16_t   timerExtensionCounter_g;

/* Statics */
static uint8_t       internalSyncIndex_s;
static InternalFlags internalFlags_s;
static uint8_t       lastAccumulatorCount_s;
static uint8_t       accumulatorAdder_s;
static uint16_t      previousPrimaryTicksPerDegree;


typedef struct {
  uint8_t windowCount;
  uint8_t primaryEventIndex;
}SyncPosition;

const SyncPosition inputWindows[] = {
    {.windowCount = WINDOW_ONE_COUNT,   .primaryEventIndex = DEGREE_TO_INDEX(INDEX_ONE_TOTAL) },
    {.windowCount = WINDOW_TWO_COUNT,   .primaryEventIndex = DEGREE_TO_INDEX(INDEX_TWO_TOTAL) },
    {.windowCount = WINDOW_THREE_COUNT, .primaryEventIndex = DEGREE_TO_INDEX(INDEX_THREE_TOTAL) },
    {.windowCount = WINDOW_FOUR_COUNT,  .primaryEventIndex = DEGREE_TO_INDEX(INDEX_FOUR_TOTAL) },
    {.windowCount = WINDOW_FIVE_COUNT,  .primaryEventIndex = DEGREE_TO_INDEX(INDEX_FIVE_TOTAL) },
    {.windowCount = WINDOW_SIX_COUNT,   .primaryEventIndex = DEGREE_TO_INDEX(INDEX_SIX_TOTAL) },
    {.windowCount = WINDOW_SEVEN_COUNT, .primaryEventIndex = DEGREE_TO_INDEX(INDEX_SEVEN_TOTAL) },
    {.windowCount = WINDOW_EIGHT_COUNT, .primaryEventIndex = DEGREE_TO_INDEX(INDEX_EIGHT_TOTAL) }
};

void decoderSpecificInit() {
  /* We need to set the pulse accumulator overflow ISR to the highest priority or we run the risk of
   * missing a tooth (and testing shows that it does at > 3500 RPM).
   */
  ROUTE_INTERRUPT(0x6E, S12X_INTERRUPT, S12X_PRIORITY_LEVEL_SEVEN);
  /* Because we have so little time to catch the capture and disable it,
   * we need this interrupt to be a pretty high priority.
   */
  ROUTE_INTERRUPT(0x77, S12X_INTERRUPT, S12X_PRIORITY_LEVEL_SEVEN);

  memset(&decoderStats_g, 0, sizeof(decoderStats_g));
  ICPAR |= (1 << 3); // set the second bit in ICPAR (PAC1) to enable PT1's pulse accumulator
  //Disable capture on TC0 by making it an output
  TIOS |= (1 << 0);
  /* Disable INT on TC0 */
  TIE &= ~(uint8_t)(1 << 0);
  /* CH4 reserved for Xgate, 0-3 5-7 IC */
  //Enable interrupt on 8-bit overflow
  PACTL |= PA0VI;
}

void decoderReset() {
}

/* An alternative to having this run at a high priority would be to have it
 * run on XGATE. No need for marking atomic sections since this section
 * has the highest priority. */
void pulseAccumulatorOverflowISR() {
  /* Enable capture */
  TIOS &= ~(uint8_t)(1 << 0);
  /* Enable INT on TC0 */
  TIE |= (uint8_t)(1 << 0);

  accumulatorAdder_s += (HIGH_RES_TEETH_PER_EMULATED_CRANK_TOOTH);
  // Roll back PA counter so we get another ISR after 10 input edges
  PACN3 = ((uint8_t)0 - (HIGH_RES_TEETH_PER_EMULATED_CRANK_TOOTH));

if (PORTA & BIT0) {
  PORTA &= 0xFE;
} else {
  PORTA |= 1;
}

  PAFLG |= PA0VF;  // Clear interrupt
}

/* Called on every pulse-accumulator overflow */
void PrimaryEngineAngle() {
  //Disable capture on TC0
  TIOS |= (1 << 0);

  /* Disable INT on TC0 */
  TIE &= ~(uint8_t)(1 << 0);

  /* Clear INT flag */
  TFLG1 = C0F;

  ++decoderStats_g.secondaryTeethSeen;

  if (PORTA & BIT0) {
    PORTA &= 0xFB;
  } else {
    PORTA |= BIT2;
  }

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

  if (decoderStats_g.decoderFlags.bits.minimalSync &&
      decoderStats_g.decoderFlags.bits.primaryPeriodValid) {

    if (decoderStats_g.currentPrimaryEvent > TOTAL_ENGINE_CYCLE_INDEXES) {
      decoderStats_g.currentPrimaryEvent = 0;
    } else {
      ++decoderStats_g.currentPrimaryEvent;
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
//TODO fix bug  it will lose sync randomly commenting out the filter code allows it to run OK
      if (decoderStats_g.RPM > Config.tachDecoderSettings.filterBypassRPM) {
        if (ratioBetweenCurrentAndLast < allowedTollerance) {
PORTA |= BIT1;
          if (decoderStats_g.instantTicksPerDegree < previousPrimaryTicksPerDegree) {
            resetDecoderStatus(PACN3);
          } else {
            resetDecoderStatus(PRIMARY_EVENT_TOO_LATE);
          }
          return;
        }
      }
decoderStats_g.capturedAngle = PACN3;
PORTA &= 0xFD;
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
    /* Set all as good to go */
    decoderStats_g.decoderFlags.bits.crankLock = 1;

    if (decoderStats_g.decoderFlags.bits.phaseLock) {
      decoderStats_g.decoderFlags.bits.minimalSync = 1;
    }
    decoderStats_g.requiredSyncCycles = 0;
  }

  decoderStats_g.lastPrimaryTimeStamp = timeStamp;
  decoderStats_g.decoderFlags.bits.previousPrimaryEventValid = 1;
}


void SecondaryEngineAngle() {
	/* Clear the interrupt flag */
  TFLG1 = C1F;

  ATOMIC_START();
  uint8_t currentWindowEdges = diffUint8(PACN3, lastAccumulatorCount_s);
  lastAccumulatorCount_s = PACN3;

  currentWindowEdges += accumulatorAdder_s;
  accumulatorAdder_s = 0;
  ATOMIC_END();

  decoderStats_g.primaryTeethSeen = currentWindowEdges;

  uint8_t i;

  if (decoderStats_g.decoderFlags.bits.phaseLock) {
    /* Verify Sync */
    ++internalSyncIndex_s;

    if (internalSyncIndex_s > (ARRAY_SIZE(inputWindows) - 1)) {
      internalSyncIndex_s = 0;
    }
    uint8_t countDifference = diffUint8(currentWindowEdges, inputWindows[internalSyncIndex_s].windowCount);

    if (countDifference > EDGE_TOLLERANCE) {
      if (currentWindowEdges > inputWindows[internalSyncIndex_s].windowCount){
        resetDecoderStatus(0xFE); // DEFINE errorno
      } else {
        resetDecoderStatus(0xFF); // DEFINE errorno
      }
    }
  } else {
    /* Find Sync */
    for (i = 0; ARRAY_SIZE(inputWindows) > i; ++i) {
      uint8_t countDifference = diffUint8(currentWindowEdges, inputWindows[i].windowCount);
      if (countDifference < EDGE_TOLLERANCE) {
        if (internalFlags_s.lastWindowMatch) {
          decoderStats_g.decoderFlags.bits.phaseLock = 1;
          internalFlags_s.lastWindowMatch = 0;
          internalSyncIndex_s = i;
          decoderStats_g.currentPrimaryEvent = inputWindows[i].primaryEventIndex;
          //We need to set the PA counter to the correct value so our emulated pattern is synced!!!
          ATOMIC_START();
          if ((PACN3 - SYNC_OFFSET) == 0) {

          } else {
            //uint8_t difference = PACN3;
            //TODO use pin state to see if we need to add one to our accumulatorAdder
            PACN3 = ((uint8_t)0 - (HIGH_RES_TEETH_PER_EMULATED_CRANK_TOOTH - SYNC_OFFSET));
            lastAccumulatorCount_s = ((uint8_t)0 - (HIGH_RES_TEETH_PER_EMULATED_CRANK_TOOTH - SYNC_OFFSET));
            //accumulatorAdder_s += difference + (HIGH_RES_TEETH_PER_EMULATED_CRANK_TOOTH - SYNC_OFFSET);
          }
          ATOMIC_END();

        } else {
          internalFlags_s.lastWindowMatch = 1;
        }
        break;
      }
    }
  }

}

