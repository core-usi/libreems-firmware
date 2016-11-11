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
 * @brief MC9S12XDP512 PIT flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */

/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_PIT_FLAGS_H_SEEN
#define FILE_9S12XDP512_PIT_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//
               
/* -------------------------------------------------------------------------
 *  Periodic Interrupt Timer (PIT) Registers
 * -------------------------------------------------------------------------
 */
               
// PITCLMT (PIT Control and Force Load Micro Timer Register) 13.3.0.1, Tbl 13-1
#define PITE          BIT7 // PIT Module Enable Bit, 0 = disabled, 1 = enabled
#define PITSWAI       BIT6 // PIT Stop in Wait Mode Bit, 0 = normal, 1 = stop
#define PITFRZ        BIT5 // PIT Counter Freeze while in Freeze Mode Bit
//#define 0           BIT4 //
//#define 0           BIT3 //
//#define 0           BIT2 //
#define PFLMT1        BIT1 // PIT Force Load Bits for Micro Timer 1:0
#define PFLMT0        BIT0 //

// PITFLT (PIT Force Load Timer Register) 13.3.0.2, Table 13-2
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
#define PFLT3         BIT3 // PIT Force Load Bits for Timer 3-0.  these bits 
#define PFLT2         BIT2 // have only an effect if the corresponding timer
#define PFLT1         BIT1 // channel (PCE set) is enable and PIT is enablet
#define PFLT0         BIT0 // Writing 1 loads the corresponding 16 bit timer 
                           // Register into the down-counter

// PITCE (PIT Channel Enable Register) 13.3.0.3, Table 13-3
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
#define PCE3          BIT3 // PIE Enable Bits for Timer Channel 3:0. These bits
#define PCE2          BIT2 // enable the PIT Channels 3-0. If PCE is cleared the
#define PCE1          BIT1 // PIT channel is disabled and corresponding flag in
#define PCE0          BIT0 // PITTF register is cleared. 1 = enabled

// PITMUX (PIT Multiplex Register) 13.3.0.4, Table 13-4
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
#define PMUX3         BIT3 // PIT Multiplex Bits for Timer channel 3:0. These
#define PMUX2         BIT2 // bits select if the corresponding 16 bit timer is 
#define PMUX1         BIT1 // connected to micro time base (MTB) 0 or 1.
#define PMUX0         BIT0 // 0 conencted to MTB0, 1 = connected to MTB1

// PITINTE (PIT Interrupt Enable Register) 13.3.0.5, Table 13-5
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
#define PINTE3        BIT3 // PIT Time-Out Interrupt Enable Bits for Channel 3:0
#define PINTE2        BIT2 // 0 = ISR disabled, 1 = ISR enabled
#define PINTE1        BIT1 //
#define PINTE0        BIT0 //

// PITTF (PIT Time-Out flag Register) 13.3.0.6, Table 13-6
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
#define PTF3          BIT3 // PIT Time-out Flag Bits for Timer Channel 3:0
#define PTF2          BIT2 // Set when counter has reached 0, cleared by 
#define PTF1          BIT1 // writing a 1 to it.
#define PTF0          BIT0 //

// PITMTLD0 (PIT Micro Timer Load Register 0 to 1)
// PITMTLD1
#define PMTLD7        BIT7 // ?PIT Micro Timer Load Bits 7:0. These bits set 
#define PMTLD6        BIT6 // the modulus down counter load value of the  micro
#define PMTLD5        BIT5 // timers, Values don't take effect until it reaches
#define PMTLD4        BIT4 // 0 or can be force via PFLMT bits in PITCFLMT
#define PMTLD3        BIT3 // register
#define PMTLD2        BIT2 //
#define PMTLD1        BIT1 //
#define PMTLD0        BIT0 //

// PITLD0 (16 bit) (PIT Load Register 0-3) 13.3.0.8
// PITLD1 (16 bit) These MUST be loaded with a 16 bit call to ensure date
// PITLD2 (16 bit) consistency. Will be loaded when count hits zero or can be
// PITLD3 (16 bit) force loaded via PFLT bits in PITFLT register


// PITCNT0 (16 bit) (PIT Count Register 0-3) 13.3.0.9
// PITCNT1 (16 bit) These bits represent the current 16 bit modulus down-count
// PITCNT2 (16 bit) value. Msut be read as a 16 bit access to read in 1 clock
// PITCNT3 (16 bit)

#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_PIT_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
