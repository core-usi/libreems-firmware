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
 * @ingroup I/O
 */

#include "inc/GPIO.h"
#include "inc/outputPlotter.h"

typedef enum {
  UN_SET = 0,
  HOLD   = 1,
  SET    = 2
}GPIOstatus;

static uint8_t currentRunLevel_s;

uint8_t getCurrentRunlevel() {
  return currentRunLevel_s;
}

void processGPIO(GPIOchannel *GPIOchannels) {
  uint8_t i;
  uint8_t runLevel = ULTIMATE_OPERATING_LIMITS_INDEX;

  for (i = 0; i < NUM_GPIO_CHANNELS; ++i) {

    if (GPIOchannels[i].flags.enabled && GPIOchannels[i].flags.isParentEvent) {
      if (0) { /* Process inputs */

      } else { /* Process outputs */
        uint8_t result = checkForCondition(&GPIOchannels[i]);
        uint8_t childResult = SET;

        if (GPIOchannels[i].flags.hasChild) {
          uint8_t childIndex = GPIOchannels[i].childIndex;
          childResult = checkForCondition(&GPIOchannels[childIndex]);
        }
        /* Set register bit(s) if both parent and child are true */
        if (result == SET && childResult == SET) {
          BLOCK_UNTIL_LOCKED(2);
          *(GPIOchannels[i].reg) |= GPIOchannels[i].mask;
          REL_SEM(2);
          /* find highest de-rate index and set it */
          if (GPIOchannels[i].derateLevel > runLevel) {
            runLevel = GPIOchannels[i].derateLevel;
          }
        } else if (result == UN_SET || childResult == UN_SET) {
          BLOCK_UNTIL_LOCKED(2);
          *(GPIOchannels[i].reg) &= ~(GPIOchannels[i].mask);
          REL_SEM(2);
        }
      }
      /* Set runlevel */
      currentRunLevel_s = runLevel;

    }
  }
}

uint8_t checkForCondition(GPIOchannel *GPIOchannel) {
  uint8_t condition = HOLD;
  if (GPIOchannel->flags.triggerOnUpper) { /* Process rising outputs */
    if (*(GPIOchannel->varPointer) > GPIOchannel->upperBoundary) {
      condition = SET;
    } else if (*(GPIOchannel->varPointer) < GPIOchannel->lowerBoundary) {
      condition = UN_SET;
    }
  } else { /* Process falling  outputs */
    if (*(GPIOchannel->varPointer) < GPIOchannel->lowerBoundary) {
      condition = SET;
    } else if (*(GPIOchannel->varPointer) > GPIOchannel->upperBoundary) {
      condition = UN_SET;
    }
  }
  return condition;
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
