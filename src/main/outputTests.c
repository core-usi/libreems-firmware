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


#include "inc/outputTests.h"
#include "inc/globals.h"
#include "inc/freeEMS.h"

#define OUTPUT_DELAY_TICKS  (200)

/* TODO doc me */
void BTPattern(uint16_t measure) {

  uint32_t simulatedInputStamp = TCNT;

  /* If our over-flow is awaiting to be serviced we need to account for it here */
  if(TFLG2 && !(TCNT & 0x8000)){
    simulatedInputStamp += (1 << 8);
  }

  uint8_t i;


  if (BTpatternParemeterSet.testID) {
    if (measure % BTpatternParemeterSet.testInterval == 0) {
      BLOCK_UNTIL_LOCKED(2);
      PORTA |= BIT0; //Bring marker bit high
      REL_SEM(2);
      if (BTpatternParemeterSet.delay > 0xFFFF) {
        BLOCK_UNTIL_LOCKED(2);
        PORTA |= BIT1; //Bring metronome marker bit high
        REL_SEM(2);
      } else {
        BLOCK_UNTIL_LOCKED(2);
        PORTA &= ~(BIT1); //Bring metronome marker bit low
        REL_SEM(2);
      }

      switch (BTpatternParemeterSet.testID) {
      case BTP_ROLLING:
        loadOutSchedule(BTpatternParemeterSet.channel, BTpatternParemeterSet.delay, BTpatternParemeterSet.runtime);
        scheduleOutput(BTpatternParemeterSet.channel, simulatedInputStamp);
        BTpatternParemeterSet.channel++;
        if (BTpatternParemeterSet.channel > BTpatternParemeterSet.numberOfEvents) {
          BTpatternParemeterSet.channel = 0;
        }
        break;
      case BTP_ROLLING_INC:
        loadOutSchedule(BTpatternParemeterSet.channel, BTpatternParemeterSet.delay, BTpatternParemeterSet.runtime);
        scheduleOutput(BTpatternParemeterSet.channel, simulatedInputStamp);
        BTpatternParemeterSet.channel++;
        BTpatternParemeterSet.runtime++;
        if (BTpatternParemeterSet.channel >= BTpatternParemeterSet.numberOfEvents) {
          BTpatternParemeterSet.channel = 0;
        }
        break;
      case BTP_ROLLING_BATCH: /* Schedule multiple events at once with the same delay and runtime */
        for (i = 0; i < BTpatternParemeterSet.numberOfEvents; ++i) {
          uint16_t spaceDelay = i * BTpatternParemeterSet.channel;
          loadOutSchedule(i, BTpatternParemeterSet.delay + spaceDelay, BTpatternParemeterSet.runtime);
          scheduleOutput(i, simulatedInputStamp);

          if (i > MAX_NUMBER_OF_OUTPUT_EVENTS) {
            break;
          }
        }
        //BTpatternParemeterSet.channel++;
        break;
      case BTP_INC_DELAY:
        loadOutSchedule(BTpatternParemeterSet.channel, BTpatternParemeterSet.delay, BTpatternParemeterSet.runtime);
        scheduleOutput(BTpatternParemeterSet.channel, simulatedInputStamp);
        BTpatternParemeterSet.channel++;
        BTpatternParemeterSet.delay++;
        if (BTpatternParemeterSet.channel > BTpatternParemeterSet.numberOfEvents) {
          BTpatternParemeterSet.channel = 0;
        }
        break;
      default:
        BTpatternParemeterSet.testID = 0; //Disable BTpattern test
        break;
      }

    }
  }
  PORTA &= ~(BIT0); //Bring marker bit low
}

void singleChannelOutputTest(BTpatternParameters *parameters) {
  /* Schedule one output */
  if (getDecoderStats()->decoderFlags.bits.minimalSync) {
    e_printf("Output Test Unavailable");
  } else {
    loadOutSchedule(parameters->channel, parameters->delay, parameters->runtime);
    scheduleOutput(parameters->channel, TCNT);
  }
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
