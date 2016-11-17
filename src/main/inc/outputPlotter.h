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
 * @ingroup allHeaders
 */


#ifndef OUTPUT_PLOTTER_H_SEEN
#define OUTPUT_PLOTTER_H_SEEN

#include <stdint.h>

#include "memory.h"
#include "systemConfig.h"
#include "9S12XDP512.h"
#include "libreTypes.h"


/* Bench test pattern(BTP) definitions */
#define BTP_ROLLING             1
#define BTP_ROLLING_INC         2
#define BTP_ROLLING_BATCH       3
#define BTP_ROLLING_BATCH_INC   4
#define BTP_INC_DELAY       5

#define COCKED_FLAG  BIT0        /* if this bit is high during an OC check and we have a match hit the pin */
#define FAR_FLAG     BIT1        /* bit to control the metronome's actions */
#define IDLE_FLAG    BIT2        /* bit to signify an idle state */
#define GO_HIGH      BIT3        /* action is to go high */
#define GO_LOW       BIT4        /* action is go go low */
//#define WFTOF_FLAG   BIT5        /* Wait for timer overflow */
//#define LATE_OFLOW   BIT6        /* Late on over flow */

/* Scheduler flags */
#define EVENT_ENABLED                   0
#define EVENT_DUTY_CYCLE_EXCEEDDED  (1 << 0)
#define EVENT_RPM_EXCEEDED          (1 << 1)
#define EVENT_CALC_REQUIRED         (1 << 2)
#define EVENT_LOAD_EXCEEDED         (1 << 3)
#define EVENT_DEFLOOD               (1 << 4)


#define SET_SEM(x) (XGSEM = 0x0101 << (x))
#define TST_SEM(x) (XGSEM & 0x0001 << (x))

/* Block until sem lock is obtained */
#ifndef HOST_TESTS
#define REL_SEM(x) (XGSEM = 0x0100 << (x))
#define BLOCK_UNTIL_LOCKED(semID) \
                  do {SET_SEM(semID); \
                  \
                  } while (!TST_SEM(semID));
#else
#define REL_SEM(x)
#define BLOCK_UNTIL_LOCKED(semID)
#endif



void plotOutputs(DecoderStats *decoderStats, uint32_t ISRstartStamp, uint8_t totalInputAngles) TEXT1;
inline void scheduleOutput(uint8_t oututEvent, uint32_t ISRstartStamp) TEXT1;
void metronome() TEXT1;
void updateIdleEventAngles(uint8_t force);
void loadOutSchedule(uint8_t outEvent, uint32_t delay, uint32_t runtime) TEXT1;

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
