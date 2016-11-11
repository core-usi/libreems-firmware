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
 * @brief MC9S12XDP512 VREG flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */

/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_VREG_FLAGS_H_SEEN
#define FILE_9S12XDP512_VREG_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//
               
/* -------------------------------------------------------------------------
 *  Voltage Regulator (VREG) Registers
 * -------------------------------------------------------------------------
 */
               
// VREGHTCL (HT Control Register) 14.3.2.1, Factory use only

// VREGCTRL (Control Register) 14.3.2.2, Table 14-3
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
//#define 0           BIT3 //
#define LVDS          BIT2 // Low-Voltage Detect Status Bit
#define LVIE          BIT1 // Low-Voltage Interrupt Enable Bit
#define LVIF          BIT0 // Low-Voltage Interrupt Flag

// VREGAPICL (Autonomous Periodical Interupt Control Reguster) 14.3.2.3,Tbl 14-4
#define APICLK        BIT7 // Autonomous Periodical Interrupt Feature Enable Bit
//#define 0           BIT6 // 0 =Autonomous Periodical Interrupt Clock as source
//#define 0           BIT5 // 1 = Bus clock used as source
//#define 0           BIT4 //
//#define 0           BIT3 //
#define APIFE         BIT2 // Autonomous Peridical Interrupt Feature Enable Bit
#define APIE          BIT1 // Autonomous Periodical Interrupt Enable Bit
#define APIF          BIT0 // Autonomous Periodical Interrupt Flag 

// VREGAPITR (Autonomous Periodical Interrupt Trimming Register) 14.3.2.4
#define APITR5        BIT7 // Autonomous Periodical Interrupt Period Trim Bits
#define APITR4        BIT6 // See Table 14-6
#define APITR3        BIT5 //
#define APITR2        BIT4 //
#define APITR1        BIT3 //
#define APITR0        BIT2 //
//#define 0           BIT1 //
//#define 0           BIT0 //

// VREGAPIRH (Autonomous Periodical Interrupt Rate High and Low Register)
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
#define APIR11        BIT3 // Autonomous Periodic Interrupt Rate bits APIR[11:0]
#define APIR10        BIT2 //
#define APIR9         BIT1 //
#define APIR8         BIT0 //
//
// VREGAPIRL 14.3.2.5
#define APIR7         BIT7 // Autonomous Periodic Interrupt Rate bits APIR[11:0]
#define APIR6         BIT6 // Low 8 bits of APIR 
#define APIR5         BIT5 // See Table 14-8
#define APIR4         BIT4 //
#define APIR3         BIT3 //
#define APIR2         BIT2 //
#define APIR1         BIT1 //
#define APIR0         BIT0 //

#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_VREG_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
