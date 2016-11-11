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


#ifndef DATA_ACQUISITIONISRS_H_SEEN
#define DATA_ACQUISITIONISRS_H_SEEN

#include <stdint.h>
#include "memory.h"
#include "systemConfig.h"
#include "interrupts.h"


void gpCapture7() ISR TEXT1;
void gpCapture6() ISR TEXT1;
void gpCapture5() ISR TEXT1;
void gpCapture3() ISR TEXT1;
void gpCapture2() ISR TEXT1;

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
