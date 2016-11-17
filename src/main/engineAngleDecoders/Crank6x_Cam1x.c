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


/* V12 even fire */
const uint16_t inputAngles[] = {
    ENGINE_ANGLE_S(0),   ENGINE_ANGLE_S(60),  
    ENGINE_ANGLE_S(120), ENGINE_ANGLE_S(180), 
    ENGINE_ANGLE_S(240), ENGINE_ANGLE_S(300), 
    ENGINE_ANGLE_S(360), ENGINE_ANGLE_S(420),
    ENGINE_ANGLE_S(480), ENGINE_ANGLE_S(540),
    ENGINE_ANGLE_S(600), ENGINE_ANGLE_S(660),
};

#include "./common/EvenX_with_CamSync.c"
