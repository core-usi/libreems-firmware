/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2012 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief For simple use on distributor ignition engines with batch injection
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS      2 // TODO  All three of these should migrate to a generic 4 cyl header...
#define NUMBER_OF_VIRTUAL_EVENTS   8 // TODO  All three of these should migrate to a generic 4 cyl header...

#include "../inc/freeEMS.h"
#include "../inc/interrupts_depricated.h"
#include "../inc/decoderInterface_depricated.h"
#include "../inc/utils.h"

// 69 is a little too high, and 68 is more than a little too low (or inversed)
#define E1 (69 * ANGLE_FACTOR) // TODO May need to be 111 instead, needs testing!


#include "../decoders_depricated/code/HallOrOptical-Distributor-XofY.c"
