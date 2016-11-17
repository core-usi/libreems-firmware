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
 * @ingroup initializers
 */


#include "inc/outputPlotter.h"
#include "inc/globals.h"
#include "inc/freeEMS.h"
#include "inc/dataAcquisition.h"
#include "inc/dataCalculation.h"
#include "inc/libreDefs.h"


#define MIN_INJ_DELAY_TICKS         50
#define MIN_ANGLE_TO_EVENT_SPREAD   3

/* Both of these need to be moved to a proper header etc*/
#define SIZE_OF_EVENT_ARRAYS 256


/* Call this from the primary decoder ISR */
void plotOutputs(DecoderStats *decoderStats, uint32_t ISRstartStamp, uint8_t totalInputIndexes) {

  uint8_t i;
  uint8_t currentInput = decoderStats->currentPrimaryEvent;
  uint8_t nextInput = currentInput + 1;
   //uint8_t scheduleAdder = 0;
  outputEvent *event = &outputSchedules[0];
  uint16_t softAngle = 0; /* A target output angle which does not exist as a hard input on the cam or crank */

  /* Wrap input index if necessary */
  if (nextInput > totalInputIndexes) {
    nextInput = 0;
  }

  uint16_t currentAngle = getAngle(currentInput);
  uint16_t nextAngle    = getAngle(nextInput);

  //TODO move to doxygen
  /* We are not factoring in decoder ISR latency which means that any super short delay's run-time may be consumed, just a little bit.
    *  In the case of ignition this means that our coil dwell may at times be cut short by our ISR latency, but our spark will occur at
    *  the time we command with the highest possible accuracy and that's what counts. MINIMUM_DWELL should be .5-mS to cover lethargic decoders.
    *
    *  If we are dealing with fuel this would be a bit of a shame, so we must adjust our scheduling so that we never consume any of our run-time.
    *  Right now the cleanest/simplest thing to do is to just hop to the next input event that is closest to your desired injection angle. The only
    *  safety we need is enough free duty cycle to make the move, so that we don't eat into runtime or skip an injection event because it was not yet
    *  finished. Moves should be made one hop at a time so that we can have as high a DC as possible and to minimize any transient conditions.
    *
    *  A better approach would be to have virtual events for each output, something like that may need to wait for an FPGA based design.
    */

  /* Loop though our current angle window and see if we have any outputs that fall within it */
  for (i = 0; i < Config.numberOfPrecisionOutputs; ++i, ++event) {
    /* If our event flags is clear attempt to schedule, otherwise don't bother */
    if (event->eventFlags == EVENT_ENABLED) {
      if (nextInput < currentInput) {  // Handle possible rollover case (actually events from 675<->720 (0))
        /* we don't need to care aboutnextInput as the "else" case handles from 0-675 deg */
        if ((event->startAngle > currentAngle)  || (event->startAngle == nextAngle)) {
          /* See how many degrees are between our hard edge and the start of our event */
          softAngle = outputSchedules[i].startAngle - currentAngle;
          if (outputSchedules[i].startAngle < currentAngle) {
            softAngle += ENGINE_ANGLE_S(360) * Config.mechanicalProperties.revoloutionsPerCycle;
          }
          goto scheduleEvent;
        }
      } else {
        if ((event->startAngle <= nextAngle) && (event->startAngle > currentAngle)) {
          /* See how many degrees are between our hard edge and the start of our event */
          softAngle = outputSchedules[i].startAngle - currentAngle;
          goto scheduleEvent;
        }
      }
    }
    checkNext:
    continue;
  }
  return;
  /* We can combine the logic above we can drop this goto */
  scheduleEvent:
  if (softAngle && (event->countDown.countDown32 == 0)) {
    outputSchedules[i].countDown.countDown32 = ((uint32_t)softAngle * (decoderStats->instantTicksPerDegree)) / (TICKS_PER_DEGREE_MULTIPLIER);
  }

  scheduleOutput(i, ISRstartStamp);
  event->startAngle = event->nextStartAngle; /* Since we just scheduled this event we know it's safe to update */
  goto checkNext;
}


//TODO inline code called by ISRs

/* This code has been moved to a callable function mainly for verification purposes.
 * Likely it will only be called from the output plotter */
inline void scheduleOutput(uint8_t outEvent, uint32_t ISRstartStamp) {

  BLOCK_UNTIL_LOCKED(2);

  /* If the go low of our event has not yet cleared then we must skip trying to schedule it */
  if(XGoutputEvents[outEvent].goLow.actionBits & COCKED_FLAG) {
    REL_SEM(2);
    return;
  }

  XGoutputEvents[outEvent].goHigh.downCounter.countDown32 = outputSchedules[outEvent].countDown.countDown32;
    /* calc count downs for short counts */
  if (outputSchedules[outEvent].countDown.countHL[0] == 0) {
    XGoutputEvents[outEvent].goHigh.actionBits |= COCKED_FLAG;
    XGoutputEvents[outEvent].goHigh.lastRunStamp = ISRstartStamp & 0xFFFF; /* we want to disreguard the high word if we are a short count */
    XGoutputEvents[outEvent].goLow.downCounter.countDown32 = outputSchedules[outEvent].runTime;
  } else { /* Calculate outputs for use with the metronome aka long counts */
    XGoutputEvents[outEvent].goHigh.actionBits |= FAR_FLAG;
    XGoutputEvents[outEvent].goHigh.lastRunStamp = 0;
    XGoutputEvents[outEvent].goHigh.downCounter.countDown32 += ISRstartStamp;
    XGoutputEvents[outEvent].goLow.downCounter.countDown32 = outputSchedules[outEvent].runTime;
  }

  REL_SEM(2);
  XGSWT = 0x0101; //Trigger xgate software ISR

  return;
}


/* This gets called on every TCNT overflow. This helps us handle > 16-bit OC values. */
void metronome() {

  #ifdef BENCHTEST
  uint8_t numEvents = 24;
  #else
  uint8_t numEvents = Config.numberOfPrecisionOutputs; //TODO make this a function parameter
  #endif

  uint8_t i = 0;

  do {
    SET_SEM(2);
    //try to allocate semaphore
  } while (!TST_SEM(2));/* out of a pool of 0..7 */

  for (; i < numEvents; ++i) {
    if (XGoutputEvents[i].goHigh.actionBits & FAR_FLAG) {
      --(XGoutputEvents[i].goHigh.downCounter.countHL[0]);
      if (XGoutputEvents[i].goHigh.downCounter.countHL[0] == 0) {
        XGoutputEvents[i].goHigh.actionBits |= COCKED_FLAG;
        XGoutputEvents[i].goHigh.actionBits &= ~(FAR_FLAG);
        XGoutputEvents[i].goHigh.lastRunStamp = 0;
      }
    }
  }
  REL_SEM(2);
  XGSWT = 0x0101;
}


/* As soon as we schedule an event we are safe to update it's angle */

//void updateIdleEventAngles(uint8_t force) {
//  uint8_t i;
//
//  for (i = 0; i < Config.numberOfPrecisionOutputs; ++i) {
//    /* If our event flag is anything but zero we know it's disabled and requires updates */
//    if (outputSchedules[i].eventFlags || force) {
//      outputSchedules[i].startAngle = outputSchedules[i].nextStartAngle;
//    }
//  }
//}

/* This code has been moved to a callable function mainly for verification purposes.
 * Likely it will only be called from the output plotter */
void loadOutSchedule(uint8_t outEvent, uint32_t delay, uint32_t runtime) {
  outputSchedules[outEvent].countDown.countDown32 = delay;
  outputSchedules[outEvent].runTime = runtime; //TODO this needs a *next stage too because if its being used for ign it should match the base angle data too
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
