/* LibreEMS - the open source engine management system
 *
 * Copyright 2014 David J. Andruczyk
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
 * @brief MC9S12XDP512 CRG (Clock andReset Generator) flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf
 */


/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_CRG_FLAGS_H_SEEN
#define FILE_9S12XDP512_CRG_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//

/* -------------------------------------------------------------------------
 *  CLOCK AND RESET GENERATOR REGISTERS (CRG)
 * -------------------------------------------------------------------------
 */

// SYNR (CRG Synthesizer Register) 2.3.2.1
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
#define SYN5          BIT5 // SYN[5:0] Control multiplcation factor of the
#define SYN4          BIT4 // PLL. If PLL is on, the count in the loop divider
#define SYN3          BIT3 // (SYNR) effectively multiplies the PLL clock 
#define SYN2          BIT2 // (PLLCLK) from the reference fred by 2x(SYNR+1)
#define SYN1          BIT1 // PLLCLK = 2*OSCCLK*((SYNR+1)/(REFDV+1))
#define SYN0          BIT0 //

// REFDV (CRG Reference Divider Register) 2.3.2.2 
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
#define REFDV5        BIT5 // REFDV[5:0] provides finer granularity for the
#define REFDV4        BIT4 // PLL multiplier steps, The Count in the reference
#define REFDV3        BIT3 // divider divides OSCCLK frequency by REFDV+1
#define REFDV2        BIT2 //
#define REFDV1        BIT1 //
#define REFDV0        BIT0 //

// CTFLG (CRG Test Flags Register (Intended for factory test only)) 2.3.2.3
// Reserved for factory usage only, not available in normal modes..

// CRGFLG (Clock and Regest Generator Flags) 2.3.2.4, Table 2-2
#define RTIF          BIT7 // Mask for clearing the Real Time Interrupt flag
#define PORF          BIT6 // Mask for checking to see whether this was a 
                           // fresh start, or not
#define LVRF          BIT5 // Mask for checking to see whether this was a 
                           // post-low-Voltage start, or not
#define LOCKIF        BIT4 // Mask for clearing the PLL Lock Interrupt flag
#define LOCK          BIT3 // Mask for checking to see when the PLL is
                           // locked onto its target
#define TRACK         BIT2 // Mask for checking to see when the PLL is 
                           // tracking its target
#define SCMIF         BIT1 // Mask for clearing the Self Clock Mode 
                           // Interrupt flag
#define SCM           BIT0 // Mask for checking to see whether we're in 
                           // Self Clock Mode, or not

// CRGINT (CRG Interrupt Enable Register) 2,3,2,5m Table 2-3
#define RTIE          BIT7 // Real Time Interrupt Enable Bit
#define ILAF          BIT6 // Illegal Address Reset Flag
//#define 0           BIT5 // Reserved
#define LOCKIE        BIT4 // Lock Interrupt Enable Bit
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
#define SCMIE         BIT1 // Self ClockMMode Interupt Enable Bit
//#define 0           BIT0 // Reserved

// CLKSEL (CRG Clock Select Register) 2.3.2.6, Table 2-4
#define PLLSEL        BIT7 // Mask for selecting internally multiplied 
                           // PLL clock mode
#define PSTP          BIT6 // Pseudo Stop Bit
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
#define PLLWAI        BIT3 // PLL Stops in Wait Mode Bit
//#define 0           BIT2 // Reserved
#define RTIWAI        BIT1 // RTI Stops in Wait Mode Bit
#define COPWAI        BIT0 // COP Stops in Wait Mode Bit

// PLLCTL (CRG PLL Control Register) 2.3.2.7, Table 2-5
#define CME           BIT7 // Clock Monitor enable bit
#define PLLON         BIT6 // Phase Lock Look On Bit
#define PLLAUTO       BIT5 // Automatic Bandwidth Control Bit
#define ACQ           BIT4 // Acquisition Bit
#define FSTWKP        BIT3 // Fast Wake-up from Full Stop Bit
#define PRE           BIT2 // RTI Enable during Psuedo Stop Bit
#define PCE           BIT1 // COP Enable during Psuedo Stop Bit
#define SCME          BIT0 // Self Clock Mode Enable bit

// RTICTL (CRG RTI Control Register) 2.3.2.8, Table 2-6
#define RTDEC         BIT7 // Decimal or Binary Divider Select Bit
#define RTR6          BIT6 // RTR[6:4] are the Real Time Interrupt 
#define RTR5          BIT5 // Prescale Rate Select Bits
#define RTR4          BIT4 // see Table 2.7 and 2.8 in REFERENCE DOC
#define RTR3          BIT3 // RTR[3:0] are the Real Time Interrupt 
#define RTR2          BIT2 // Modulus Counter Select Bits
#define RTR1          BIT1 // See Table 2.7 and 2.8 in REFERENCE DOC
#define RTR0          BIT0 //

// COPCTL (CRG COP Control Register) 2.3.2.9, table 2-9
#define WCOP          BIT7 // Window COP Mode Bit
#define RSBCK         BIT6 // COP and RTI Stop in Active BDM Mode Bit
#define WRTMASK       BIT5 // Write MAsk for WCOP and CR[2:0] Bit
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
#define CR2           BIT2 // COP Watchdog Timer Rate Select, see Table 2-10 
#define CR1           BIT1 // in 
#define CR0           BIT0 //

// FORBYP (CRG Force and Bypass Test Register) 2.3.2.10
// Reserved for factory usage only, not available in normal modes..

// CTCTL (CRG Test Control Register 2.3.2.11
// Reserved for factory usage only, not available in normal modes..

// ARMCOP (CRG COP Arm/Timer Reset) 2.3.2.12
/* When the COP is disabled (CR[2:0] = “000”) writing to this register has 
 * no effect.  When the COP is enabled by setting CR[2:0] nonzero, the 
 * following applies:
 * Writing any value other than 0x_55 or 0x_AA causes a COP reset. To 
 * restart the COP time-out period you must write 0x_55 followed by a write 
 * of 0x_AA. Other instructions may be executed between these writes but 
 * the sequence (0x_55, 0x_AA) must be completed prior to COP end of 
 * time-out period to avoid a COP reset. Sequences of 0x_55 writes or 
 * sequences of 0x_AA writes are allowed. When the WCOP bit is set, 0x_55 
 * and 0x_AA writes must be done in the last 25% of the selected time-out 
 * period; writing any value in the first 75% of the selected period will 
 * cause a COP reset.
 */

#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_CRG_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
