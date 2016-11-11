/* LibreEMS - the open source engine management system
 *
 * Copyright 2014 David J.Andruczyk
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
 *
 * Thank you for choosing LibreEMS to run your engine!
 */


/** @file
 *
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief MC9S12XDP512 flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */


/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_FLAGS_H_SEEN
#define FILE_9S12XDP512_FLAGS_H_SEEN

#include "globalDefines.h"
#include "9S12XDP512_ATD_flags.h"
#include "9S12XDP512_BDM_flags.h"
#include "9S12XDP512_CRG_flags.h"
#include "9S12XDP512_ECT_flags.h"
#include "9S12XDP512_I2C_flags.h"
#include "9S12XDP512_MSCAN_flags.h"
#include "9S12XDP512_PIT_flags.h"
#include "9S12XDP512_PWM_flags.h"
#include "9S12XDP512_SCI_flags.h"
#include "9S12XDP512_SPI_flags.h"
#include "9S12XDP512_VREG_flags.h"
#include "9S12XDP512_XGATE_flags.h"

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//


// RAMWPC 
#define RPWE          BIT7 // TODO
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
#define AVIE          BIT1 // TODO
#define AVIF          BIT0 // TODO



#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
