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
 * Thank you for choosing LibreEMS to run your engine!
 */


/** @file
 *
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief MC9S12XDP512 BDM flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */

/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_BDM_FLAGS_H_SEEN
#define FILE_9S12XDP512_BDM_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//
               
/* -------------------------------------------------------------------------
 *  Background Debug Module (BDM) Registers
 * -------------------------------------------------------------------------
 */
               
// BDMSTS (BDM Status Register) 15.3.2.1, Table 15-2
#define ENBDM         BIT7 // Enable BDM, 0 disabled, 1 enabled
#define BDMACT        BIT6 // BDM Active Status
//#define 0           BIT5 //
#define SDV           BIT4 // Shift Data Valid, 0 no complete, 1 complete
#define TRACE         BIT3 // TRACE1 BDM Firmware cmd being executed (1)
#define CLKSW         BIT2 // Clock Switch See Table 15-3
#define UNSEC         BIT1 // Unsecure ( 0 secure, 1 = unsecured)
//#define 0           BIT0 //

// BDMCCRL (BDM CCR Low Holding Register) 15.3.2.2
#define CCR7          BIT7 // When in BdM more, BDMCCRL is used to save the low
#define CCR6          BIT6 // byte of the condition code register of the user
#define CCR5          BIT5 // program.
#define CCR4          BIT4 //
#define CCR3          BIT3 //
#define CCR2          BIT2 //
#define CCR1          BIT1 //
#define CCR0          BIT0 //

// BDMCCRL (BDM CCR High Holding Register) 15.3.2.2
//#edfine 0           BIT7 //
//#edfine 0           BIT6 //
//#edfine 0           BIT5 //
//#edfine 0           BIT4 //
//#edfine 0           BIT3 //
#define CCR10         BIT2 // High byte of CCR
#define CCR9          BIT1 //
#define CCR8          BIT0 //

// BDMGPR (BDM Global PAge Index Register) 15.3.2.4, Table 15-4
#define BGAE          BIT7 // BDM Global Page Access Enable Bit
#define BGP6          BIT6 // BDM Global Page Index Bits 6-0. Thes bits define
#define BGP5          BIT5 // the extended address bits rom 22 to 16, See
#define BGP4          BIT4 // S12X_MMC block guide
#define BGP3          BIT3 //
#define BGP2          BIT2 //
#define BGP1          BIT1 //
#define BGP0          BIT0 //

#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_BDM_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
