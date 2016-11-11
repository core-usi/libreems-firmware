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
 * @brief MC9S12XDP512 SPI flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */

/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_SPI_FLAGS_H_SEEN
#define FILE_9S12XDP512_SPI_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//
               
/* -------------------------------------------------------------------------
 *  Serial Peripheral Interface (SPI) Registers
 * -------------------------------------------------------------------------
 */
               
// SPICR1 (SPI Control Register 1) 12.3.2.1, Table 12-1
#define SPIE          BIT7 // SPI Interrupt Enable Bit
#define SPE           BIT6 // SPI System Enable Bit
#define SPTIE         BIT5 // SPI Transmit Interrupt Enable 
#define MSTR          BIT4 // SPI Master/Slave Mode Select Bit
#define CPOL          BIT3 // SPI Clock Polarity Bit
#define CPHA          BIT2 // SPI Clock Phase Bit
#define SSOE          BIT1 // Slave Select Output Enable. See Table 12-2
#define LSBFE         BIT0 // LSB-First Enable

// SPICR2 (SPI Control Register 2) 12.3.2.2, Table 12-3
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
#define MODFEN        BIT4 // Mode Fault Enable Bit
#define BIDIROE       BIT3 // Output Enable in Bidirectional Mode of Operation
//#define 0           BIT2 // Reserved
#define SPISWAI       BIT1 // SPI Stop in Wait Mode Bit
#define SPC0          BIT0 // Serial Pin Control Bit 0, See Table 12-4

// SPIBR (SPI Baud Rate Register) 12.3.2.3, Table 12-5
//#define 0           BIT7 //
#define SPPR2         BIT6 // SPI Baud Rate Preselection Bits
#define SPPR1         BIT5 // See Table 12-6
#define SPPR0         BIT4 //
//#define 0           BIT3 // Reserved
#define SPR2          BIT2 // SPI Baud Rate Selection Bits
#define SPR1          BIT1 // See Table 12-6
#define SPR0          BIT0 //

// SPISR (SPI Status Register) 12.3.2.4, Table 12-7
#define SPIF          BIT7 // SPIF Interrupt Flag
//#define 0           BIT6 // Reserved
#define SPTEF         BIT5 // SPI Transmit Empty Interupt Flag
#define MODF          BIT4 // Mode Fault Flag
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
//#define 0           BIT1 // Reserved
//#define 0           BIT0 // Reserved
 
// SPIDR (SPI Data Register) 12.3.2.5
// Both input and output register for SPI data, write allows data to be 
// queued and transmitted.. 


#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_SPI_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
