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


volatile uint16_t   timerExtensionCounter_g;

/* Statics */
static uint16_t previousPrimaryTicksPerDegree;
static uint8_t  lastPrimaryCount;

typedef struct {
  uint8_t lastWindowMatch :1;
  uint8_t expectingSync   :1;
}InternalFlags;

static InternalFlags internalFlags;
/* We are capturing on both rising and falling edges so our input angles are
 * as follows, starting as close to TDC of #1 as we can.
 */
uint16_t crankAngles[TOTAL_INPUTS] = {
    ENGINE_ANGLE_S(0),
    ENGINE_ANGLE_S(110),
    ENGINE_ANGLE_S(180),
    ENGINE_ANGLE_S(290),
    ENGINE_ANGLE_S(360),
    ENGINE_ANGLE_S(470),
    ENGINE_ANGLE_S(540),
    ENGINE_ANGLE_S(650),
};


struct WindowInfo {
  uint8_t windowCount;
  uint8_t angleIndex;
};


/* by capturing on both edges we can count via windows, much like
 * we do with the LT1/Nissan 360 decoder. This maps to an ENGINE_ANGLE().
 */
struct WindowInfo windows[] = {
    {.windowCount = 3, .angleIndex = 6}, /*        540 deg */
    {.windowCount = 2, .angleIndex = 0}, /* TDC #1   0 deg */
    {.windowCount = 2, .angleIndex = 2}, /*        180 deg */
    {.windowCount = 1, .angleIndex = 3}  /*        290 deg */
};

#define NUMBER_OF_WINDOWS ((uint8_t)(sizeof(windows) / sizeof(struct WindowInfo)))


typedef struct {
  uint8_t windowCount;
  uint8_t primaryEventIndex;
}SyncPosition;


void decoderSpecificInit() {
  /* Raise interrupt priorities for crank and cam capture.
   * These should always be the same priority so that sync does not ever skip a tooth. */
  ROUTE_INTERRUPT(0x76, S12X_INTERRUPT, S12X_PRIORITY_LEVEL_SEVEN);
  ROUTE_INTERRUPT(0x77, S12X_INTERRUPT, S12X_PRIORITY_LEVEL_SEVEN);

  memset(&decoderStats_g, 0, sizeof(decoderStats_g));
  setCalcRequiredFlag();
}

void decoderReset() {
  internalFlags.lastWindowMatch = FALSE;
}

/* An alternative to having this run at a high priority would be to have it
 * run on XGATE. No need for marking atomic sections since this section
 * has the highest priority. */
void pulseAccumulatorOverflowISR() {
  PAFLG |= PA0VF;  // Clear interrupt
}

/* Called on every pulse-accumulator overflow */
void PrimaryEngineAngle() {

  /* Clear INT flag */
  TFLG1 = C0F;

  ++decoderStats_g.primaryTeethSeen;

  /* Roll over ctr */
  if (decoderStats_g.currentPrimaryEvent >= TOTAL_ENGINE_CYCLE_INDEXES) {
    decoderStats_g.currentPrimaryEvent = 0;
  } else {
    ++decoderStats_g.currentPrimaryEvent;
  }

  /* Get current timestamp taking into account the overflow counter */
  ExtendedTime timeStamp;

  timeStamp.timeWord[1] = TC0;
  if (TFLG2 && !(TC0 & 0x8000)) {
    timeStamp.timeWord[0] = timerExtensionCounter_g + 1;
  } else {
    timeStamp.timeWord[0] = timerExtensionCounter_g;
  }

  if (decoderStats_g.decoderFlags.bits.minimalSync) {

    /* Get ticksPerDegree so we can calc RPM and schedule events, if we have lock */
    if (decoderStats_g.decoderFlags.bits.previousPrimaryEventValid) {
      ExtendedTime interEventPeriod;
      interEventPeriod.time = diffUint32(timeStamp.time,
          decoderStats_g.lastPrimaryTimeStamp.time);

      /* Since we are decoding at cam speed, we need to double our crank angle
       * travel and half our elapsed time (x *2 *2).
       */
      uint16_t degreesTraveled;
      if ((decoderStats_g.currentPrimaryEvent & 1) == 0) {
        degreesTraveled = ENGINE_ANGLE_S(70);
      } else {
        degreesTraveled = ENGINE_ANGLE_S(110);
      }

      decoderStats_g.instantTicksPerDegree =
          (uint16_t) ((TICKS_PER_DEGREE_MULTIPLIER * interEventPeriod.time)
              / degreesTraveled);
    } else {
      decoderStats_g.instantTicksPerDegree = 0;
    }

    uint16_t ratioBetweenCurrentAndLast;

    if (decoderStats_g.decoderFlags.bits.minimalSync
        && decoderStats_g.decoderFlags.bits.primaryPeriodValid) {


      if (decoderStats_g.decoderFlags.bits.primaryPeriodValid) {
        ratioBetweenCurrentAndLast = ratio16(previousPrimaryTicksPerDegree,
            decoderStats_g.instantTicksPerDegree,
            DECODER_STAMP_RATIO_F);
        decoderStats_g.primaryInputVariance = ratioBetweenCurrentAndLast;

        uint16_t allowedTollerance;
        decoderStats_g.RPM = (DEGREE_TICKS_PER_MINUTE
            / decoderStats_g.instantTicksPerDegree);

        //TODO(skeys) make these part of init!
        if (decoderStats_g.RPM < Config.tachDecoderSettings.maxCrankingRPM) {
          allowedTollerance =
              Config.tachDecoderSettings.inputEventCrankingTollerance;
        } else {
          allowedTollerance = Config.tachDecoderSettings.inputEventTollerance;
        }
        if (decoderStats_g.RPM > Config.tachDecoderSettings.filterBypassRPM) {
          if (ratioBetweenCurrentAndLast < allowedTollerance) {
            if (decoderStats_g.instantTicksPerDegree
                < previousPrimaryTicksPerDegree) {
              resetDecoderStatus(PRIMARY_EVENT_TOO_SOON);
            } else {
              resetDecoderStatus(PRIMARY_EVENT_TOO_LATE);
            }
            return;
          }
        }
      }

      if (decoderStats_g.requiredSyncCycles == 0) {
        plotOutputs(&decoderStats_g, timeStamp.time,
            TOTAL_ENGINE_CYCLE_INDEXES);
        decoderStats_g.syncADCsamples += updateAngleDependantData(
            &decoderStats_g, Config.mechanicalProperties.cylinderCount,
            &(Config.CylinderSetup[0]));
      }
    }

    /* Without minimal sync our inputs stamps are invalid */
    if (decoderStats_g.decoderFlags.bits.minimalSync) {
      if (decoderStats_g.decoderFlags.bits.previousPrimaryEventValid) {
        previousPrimaryTicksPerDegree = decoderStats_g.instantTicksPerDegree;
        decoderStats_g.decoderFlags.bits.primaryPeriodValid = 1;
      }
      decoderStats_g.lastPrimaryTimeStamp = timeStamp;
      decoderStats_g.decoderFlags.bits.previousPrimaryEventValid = 1;
    }
  }

}


void SecondaryEngineAngle() {
  static uint8_t currentWindowIndex;

  /* Clear the interrupt flag */
  TFLG1 = C1F;

  ++decoderStats_g.secondaryTeethSeen;

  uint8_t currentWindowSize = diffUint8(decoderStats_g.primaryTeethSeen,
      lastPrimaryCount);
  lastPrimaryCount = decoderStats_g.primaryTeethSeen;

  // if synced then check the expected window size
  if (decoderStats_g.decoderFlags.bits.phaseLock) {
    ++currentWindowIndex;
    if (!(currentWindowIndex < NUMBER_OF_WINDOWS)) {
      currentWindowIndex = 0;
    }


    if (currentWindowSize != windows[currentWindowIndex].windowCount) {
      if (currentWindowSize > windows[currentWindowIndex].windowCount) {
        resetDecoderStatus(PRIMARY_EVENT_COUNT_TOO_HIGH);
      }else {
        resetDecoderStatus(PRIMARY_EVENT_COUNT_TOO_LOW);
      }
      //decoderStats_g.debug_16b = currentWindowSize;
      return;
    }

    if (decoderStats_g.requiredSyncCycles) {
      --decoderStats_g.requiredSyncCycles;
    }

  } else {
    uint8_t i;
    for (i = 0; i < NUMBER_OF_WINDOWS; ++i) {
      if (windows[i].windowCount == currentWindowSize) {
        if (internalFlags.lastWindowMatch == FALSE) {
          internalFlags.lastWindowMatch = TRUE;
        } else {
          decoderStats_g.decoderFlags.bits.minimalSync = 1;
          decoderStats_g.decoderFlags.bits.crankLock   = 1;
          decoderStats_g.decoderFlags.bits.phaseLock   = 1;
          currentWindowIndex = i;
          decoderStats_g.currentPrimaryEvent = windows[currentWindowIndex].angleIndex;
         }
        break;
      }
      internalFlags.lastWindowMatch = FALSE;
    }
  }

}

