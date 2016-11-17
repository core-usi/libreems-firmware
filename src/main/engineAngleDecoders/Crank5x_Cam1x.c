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


/* Even Fire 10 cylinder (V10)  */
const uint16_t inputAngles[] = {
    ENGINE_ANGLE_S(0),   ENGINE_ANGLE_S(72),  
    ENGINE_ANGLE_S(144), ENGINE_ANGLE_S(216), 
    ENGINE_ANGLE_S(288), ENGINE_ANGLE_S(360), 
    ENGINE_ANGLE_S(432), ENGINE_ANGLE_S(504), 
    ENGINE_ANGLE_S(576), ENGINE_ANGLE_S(648)
};

#include "./common/EvenX_with_CamSync.c"
