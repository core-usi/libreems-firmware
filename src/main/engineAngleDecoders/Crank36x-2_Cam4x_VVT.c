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

#include "common/interface.h"

#define TOTAL_CRANK_TEETH             36
#define MISSING_CRANK_TEETH            2

#define TOTAL_PHYSICAL_CRANK_TEETH    (TOTAL_CRANK_TEETH - MISSING_CRANK_TEETH)
#define TOTAL_ENGINE_CYCLE_INDEXES ((TOTAL_PHYSICAL_CRANK_TEETH * 2) - 1)
#define ANGLE_BETWEEN_TEETH            ENGINE_ANGLE_S((360 / TOTAL_CRANK_TEETH))

/* Cached angle data */
const uint16_t inputAngles[] = {
    ENGINE_ANGLE_S(0),   ENGINE_ANGLE_S(10),  ENGINE_ANGLE_S(20),  ENGINE_ANGLE_S(30),
   ENGINE_ANGLE_S(40),   ENGINE_ANGLE_S(50),  ENGINE_ANGLE_S(60),  ENGINE_ANGLE_S(70),
   ENGINE_ANGLE_S(80),   ENGINE_ANGLE_S(90), ENGINE_ANGLE_S(100), ENGINE_ANGLE_S(110),
  ENGINE_ANGLE_S(120),  ENGINE_ANGLE_S(130), ENGINE_ANGLE_S(140), ENGINE_ANGLE_S(150),
  ENGINE_ANGLE_S(160),  ENGINE_ANGLE_S(170), ENGINE_ANGLE_S(180), ENGINE_ANGLE_S(190),
  ENGINE_ANGLE_S(200),  ENGINE_ANGLE_S(210), ENGINE_ANGLE_S(220), ENGINE_ANGLE_S(230),
  ENGINE_ANGLE_S(240),  ENGINE_ANGLE_S(250), ENGINE_ANGLE_S(260), ENGINE_ANGLE_S(270),
  ENGINE_ANGLE_S(280),  ENGINE_ANGLE_S(290), ENGINE_ANGLE_S(300), ENGINE_ANGLE_S(310),
  ENGINE_ANGLE_S(320),  ENGINE_ANGLE_S(330),
  ENGINE_ANGLE_S(360),  ENGINE_ANGLE_S(370), ENGINE_ANGLE_S(380), ENGINE_ANGLE_S(390),
  ENGINE_ANGLE_S(400),  ENGINE_ANGLE_S(410), ENGINE_ANGLE_S(420), ENGINE_ANGLE_S(450),
  ENGINE_ANGLE_S(460),  ENGINE_ANGLE_S(470), ENGINE_ANGLE_S(480), ENGINE_ANGLE_S(490),
  ENGINE_ANGLE_S(500),  ENGINE_ANGLE_S(510), ENGINE_ANGLE_S(520), ENGINE_ANGLE_S(530),
  ENGINE_ANGLE_S(540),  ENGINE_ANGLE_S(550), ENGINE_ANGLE_S(560), ENGINE_ANGLE_S(570),
  ENGINE_ANGLE_S(580),  ENGINE_ANGLE_S(590), ENGINE_ANGLE_S(600), ENGINE_ANGLE_S(610),
  ENGINE_ANGLE_S(620),  ENGINE_ANGLE_S(630), ENGINE_ANGLE_S(640), ENGINE_ANGLE_S(650),
  ENGINE_ANGLE_S(660),  ENGINE_ANGLE_S(670), ENGINE_ANGLE_S(680), ENGINE_ANGLE_S(690),
  ENGINE_ANGLE_S(700),  ENGINE_ANGLE_S(700)
};

static inline void camSyncLogic(DecoderStats *decoderStats) {
	//TODO add polling here
}

#include "./common/Missing_Tooth.c"
