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


#ifndef OUTPUT_TESTS_H_SEEN
#define OUTPUT_TESTS_H_SEEN

#include <stdint.h>
#include "memory.h"
#include "systemConfig.h"
#include "libreTypes.h"
#include "../engineAngleDecoders/common/interface.h"
#include "printf.h"


void loadOutSchedule(uint8_t outEvent, uint32_t delay, uint32_t runtime) TEXT1;
void BTPattern(uint16_t measure) TEXT1;
void singleChannelOutputTest(BTpatternParameters *parameters) TEXT;

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
