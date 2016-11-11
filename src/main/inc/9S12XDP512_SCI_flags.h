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
 * @brief MC9S12XDP512 SCI flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */

/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_SCI_FLAGS_H_SEEN
#define FILE_9S12XDP512_SCI_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//
               
/* -------------------------------------------------------------------------
 *  Serial Communication Interface (SCI) Registers
 * -------------------------------------------------------------------------
 */
               
// SCIBDH (SCI Baud Rate Register High byte) 11.3.2.1, Table 11-1
#define IREN          BIT7 // Infrared Enable bit, 0 = disabled, 1 = enabled
#define TNP1          BIT6 // Transmitter Narrow Pulse Bits, see Table 11-2
#define TNP0          BIT5 //
#define SBR12         BIT4 // SCI Baud Rate Bits SBR[12:0]
#define SBR11         BIT3 // SCI Baud rate = SCI clock/(16 * SBR[12:0])
#define SBR10         BIT2 //
#define SBR9          BIT1 //
#define SBR8          BIT0 //

// SCIBDL (SCI Baud Rate Register Low byte) 11.3.2.1
#define SBR7          BIT7 //
#define SBR6          BIT6 //
#define SBR5          BIT5 //
#define SBR4          BIT4 //
#define SBR3          BIT3 //
#define SBR2          BIT2 //
#define SBR1          BIT1 //
#define SBR0          BIT0 //

// SICR1 (SCI Control Register 1), 11.3.2.2, Table 11-3
#define LOOPS         BIT7 // Loop Select Bit, 0 =normal, 1 = loop operation
#define SCISWAI       BIT6 // SCI Stop in Wait Mode bit (1 = disabled in wait)
#define RSRC          BIT5 // Receiver Source Bit, See Table 11-4
#define M             BIT4 // Data Format Mode Bit,0 = 8 bit, 1 = 9 bit
#define WAKE          BIT3 // Wakeup Condition Bit,0 = idle, 1 = address mark
#define ILT           BIT2 // Idle Line Type Bit,0 = after start,1 = after stop
#define PE            BIT1 // Parity Enable, 0 = disabled, 1 = enabled
#define PT            BIT0 // Parity Type Bit, 0 = Even, 1 = Odd

// SCIASR1 (SCI Alternative Status Register 1) 11.3.2.3, Table 11-5
#define RXEDGIF       BIT7 // Receive Input Active Edge Interrupt Falg
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
#define BEERV         BIT2 // Bit Error Value
#define BERRIF        BIT1 // Bit Error Interrupt Flag, cleared with a 1
#define BKDIF         BIT0 // Break Detect Interrupt Flag, cleared with a 1

// SCIACR1 (SCI Alternative Control Register 1) 11.3.2.4, Table 11-6
#define RXEDGIE       BIT7 // Receive Input Active edge Interrupt Enable
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
#define BERRIE        BIT1 // Bit Error Interrupt Enable
#define BKDIE         BIT0 // Break Detect Interrupt Enable

// SCIACR2 (SCI Alternative Control Register 2) 11.3.2.5, Table 11-7
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
#define BERRM1        BIT2 // Bit Error Mode (see Table 11-8)
#define BERRM0        BIT1 //
#define BKDFE         BIT0 // Break Detect Feature Enable,0=disabled, 1=enabled

// SCICR2 (SCI Control Registe 2) 11.3.2.6, Table 11-9
#define SCITIE        BIT7 // Transmitter Interrupt Enable Bit
#define TCIE          BIT6 // Transmission Complete Interrupt Enable Bit
#define RIE           BIT5 // Receiver Full Interrupt Enable Bit
#define ILIE          BIT4 // Idle Line Interupt Enable Bit
#define TE            BIT3 // Transmitter Enable Bit
#define RE            BIT2 // Receiver Enable Bit
#define RWU           BIT1 // Receiver Wakeup Bit
#define SBK           BIT0 // Send Break Bit

// SCISR1 (SCI Status Register 1), 11.3.2.7, Table 11-10
#define TDRE          BIT7 // Transmit Date Register Empty Flag
#define TC            BIT6 // Transmit Complete Flag
#define RDRF          BIT5 // Receive Data Register Full Flag
#define IDLE          BIT4 // Idle Line Flag
#define OR            BIT3 // Overrun Flag
#define NF            BIT2 // Noise Flag
#define FE            BIT1 // Framing Error Flag
#define PF            BIT0 // Parity Error Flag

// SCISR2 (SCI Status Register 2) 11.3.2.8, Table 11-11
#define AMAP          BIT7 // Alternative Map
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
#define TXPOL         BIT4 // Transmit Polarity 0 = normal, 1 = inverted
#define RXPOL         BIT3 // Receive Polarity 0 = normal, 1 = inverted
#define BRK13         BIT2 // Break Transmit character Length 0= 10-11, 1=13-14 
#define TXDIR         BIT1 // Transmitter Pin Data Direction in Single Wire Mode
#define RAF           BIT0 // Receiver Active Flag

// SCIDRH (SCI Data Registers (high byte) 11.3.2.9, Table 11-12
#define R8            BIT7 // Received Bit 8 (9th bit when in 9 bit mode)
#define T8            BIT6 // Transmit Bit 8 (9 bit mode only)
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
//#define 0           BIT1 // Reserved
//#define 0           BIT0 // Reserved

// SCIDRL (SCI Data Registers (low byte) 11.3.2.9, Table 11-12
// R7:R0, T7:T0 received or transmitted bits


#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_SCI_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
