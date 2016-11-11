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
 * @brief MC9S12XDP512 PWM flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */

/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_PWM_FLAGS_H_SEEN
#define FILE_9S12XDP512_PWM_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//

/* -------------------------------------------------------------------------
 *  PULSE WIDTH MODULATION REGISTERS (PWM)
 * -------------------------------------------------------------------------
 */

// PWME (PWM Enable Register) 8.3.2.1 Table 8-1
#define PWME7         BIT7 // Channel 7 enable, 0 = disabled, 1 = enabled
#define PWME6         BIT6 // Channel 6 enable
#define PWME5         BIT5 // Channel 5 enable
#define PWME4         BIT4 // Channel 4 enable
#define PWME3         BIT3 // Channel 3 enable
#define PWME2         BIT2 // Channel 2 enable
#define PWME1         BIT1 // Channel 1 enable
#define PWME0         BIT0 // Channel 0 enable

// PWMPOL (PWM Polarity Register) 8.3.2.2, Table 8-2
#define PPOL7         BIT7 // Pulse Width Channel 7-0 Polarity Bits
#define PPOL6         BIT6 // 0 = low at beginning of period
#define PPOL5         BIT5 // 1 = high at beginning of period
#define PPOL4         BIT4 //
#define PPOL3         BIT3 //
#define PPOL2         BIT2 //
#define PPOL1         BIT1 //
#define PPOL0         BIT0 //

// PWMCLK (PWM Clock Select Register (PWMCLK) 8.3.2.3, Table 8-3
#define PCLK7         BIT7 // 0 = clock B, 1 Clock SB
#define PCLK6         BIT6 // 0 = clock B, 1 Clock SB
#define PCLK5         BIT5 // 0 = clock A, 1 Clock SA
#define PCLK4         BIT4 // 0 = clock A, 1 Clock SA
#define PCLK3         BIT3 // 0 = clock B, 1 Clock SB
#define PCLK2         BIT2 // 0 = clock B, 1 Clock SB
#define PCLK1         BIT1 // 0 = clock A, 1 Clock SA
#define PCLK0         BIT0 // 0 = clock A, 1 Clock SA

// PWMPRCLK (PWM Prescale Clock Select Register) 8.3.2.4, Table 8-4
//#define 0           BIT7 // PCKB[2:0] Precaler select for clock B
#define PCKB2         BIT6 // Clock B is one of 2 sources which can be used for
#define PCKB1         BIT5 // Channels 2, 3, 6 or 7
#define PCKB0         BIT4 // See Table 8-5
//#define 0           BIT3 // PCKA[2:0] Precaler select for clock A
#define PCKA2         BIT2 // Clock A is one of 2 sources which can be used for
#define PCKA1         BIT1 // Channels 0, 1, 4 or 5 
#define PCKA0         BIT0 // See Table 8-6

// PWMCAE (PWM Center Align Enable Register (PWMCAE) 8.3.2.5, Table 8-7
#define CAE7          BIT7 // Center Aligned Output modes for channels 7-0
#define CAE6          BIT6 // 0 = Channel x operates in left aligned mode
#define CAE5          BIT5 // 1 = Channel x operates in center aligned mode
#define CAE4          BIT4 //
#define CAE3          BIT3 //
#define CAE2          BIT2 //
#define CAE1          BIT1 //
#define CAE0          BIT0 //

// PWMCTL (PWM Control Register) 8.3.2.6, Table 8-8
#define CON67         BIT7 // Concatenate channels 6 and 7, 0 = 6 and 7 are
                           // separate 8 bit PWM's. 1 = 6 and 7 are concat-
               // enated into 1 16-Bit channel. Channel 6 becomes
               // the high order byte and channel 7 becomes the low
               // order byte, Channel 7 output pin is used as the 
               // output for this 16 bit PWM. Channel 7 clock, 
               // polarity, enable and alignment bits determine
               // output mode
#define CON45         BIT6 // See above but for channels 4 and 5 respectively
#define CON23         BIT5 // See above but for channels 2 and 3 respectively
#define CON01         BIT4 // See above but for channels 0 and 1 respectively
#define PSWAI         BIT3 // PWM Stops in Wait Mode, See table 8-8
#define PFRZ          BIT2 // PWM Counters Stop in Freeze Mode (see Table 8-8)
//#define 0           BIT1 //
//#define 0           BIT0 //

// PWMTST
//  FACTORY USE ONLY

// PWMPRSC
//  FACTORY USE ONLY

// PWMSCLA (PWM Scale A Register) 8.3.2.9
// PWMSCLA is the programming scale value used in scaling clock A to generate 
// clock SA. Clock SA is generated by taking clock A, dividing it by the value
// in the PWMSCLA register and diviiding that by 2. 
// ClockSA = Clock A/(2 * PWMSCLA)
// NOTE:  When PWMSCLA == 0, PWMSCLA is considered ful scale of 256 thus
// clock A is divided by 512.

// PWMSCLB (PWM Scale B Register) 8.3.2.10
// See PWMSCLA description

// PWMSCNT[A-B] 8.3.2.11
// FACTORY USE ONLY

// PWMCNT[0-7] (PWM Channel Counter Registers) 8.3.2.12
// PWMPER[0-7] (PWM Channel Period Registers) 8.3.2.13
// PWMDTY[0-7] (PWM Channel Duty Registers) 8.3.2.14
// PWMSDN (PWM Shutdown Register) 8.3.2.15, Table 8-9
#define PWMIF         BIT7 // PWM Interupt Flag, 0 = no change on PWM7IN
                           // 1 = change on PWM7IN
#define PWMIE         BIT6 // PWM Interrupt Enabled, 0 = disable, 1 = enabled
#define PWMRSTRT      BIT5 // PWM Restart
#define PWMLVL        BIT4 // PWM Shutdown Output Level 0 = 0, 1 = 1
//#define 0           BIT3 //
#define PWM7IN        BIT2 // PWM Ch 7 Input Sttus (READ ONLY)
#define PWM7INL       BIT1 // PWM Shutdown Active Input Level for Ch 7, 
                           // 0 = low, 1 = high
#define PWM7ENA       BIT0 // PWM Emergency Shutdon Enable, 0 = disabled
                           // 1 = enabled
               
               
#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_PWM_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
