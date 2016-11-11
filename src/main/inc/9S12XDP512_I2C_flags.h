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
 * @brief MC9S12XDP512 I2C flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */

/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_I2C_FLAGS_H_SEEN
#define FILE_9S12XDP512_I2C_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//
               
/* -------------------------------------------------------------------------
 *  Inter-Integrated Circuit (I2C) Registers
 * -------------------------------------------------------------------------
 */

// IBAD (IIC Address Register) 9.3.2.1, Table 9-1
#define ADR7          BIT7 // Slave Address (7 bits) Defaul mode is slave mode
#define ADR6          BIT6 //
#define ADR5          BIT5 //
#define ADR4          BIT4 //
#define ADR3          BIT3 //
#define ADR2          BIT2 //
#define ADR1          BIT1 //
//#define 0           BIT0 // Reserved

// IBFD (IIC Frequency Divider Register) 9.3.2.2, Table 9-2
#define ICB7          BIT7 // I Bus Clock Rate ICB[7:0]. This field is used to 
#define ICB6          BIT6 // prescale the clock for bit rate selection. Bits
#define ICB5          BIT5 // 7:6 sets the prescaler, bits 5:3 set the prescale
#define ICB4          BIT4 // divider, and IBC 2:0 select the shift register 
#define ICB3          BIT3 // tap point
#define ICB2          BIT2 //
#define ICB1          BIT1 // see Table 9-3 in REFERENCE DOC 
#define ICB0          BIT0 //

// IBCR (IIC Control Register) 9.3.2.3, Table 9-6
#define IBEN          BIT7 // I-Bus Enable, 0 = disable, 1 = enabled
#define IBIE          BIT6 // I-Bus Interrupt Enable, 0 = disabled, 1 = enabled
#define MS_SL         BIT5 // Master/Slave Mode Select Bit, 0=slave, 1=master
#define Tx_Rx         BIT4 // Transmit/Receive Mode Select Bit, 0 = receive
                           // 1 = transmit
#define TXAK          BIT3 // Transmit Acknowledge Enable, 0 = Ack Sent,
                           // 1 = No ack signal response sent
#define RSTA          BIT2 // Repeat Start. 1 Generate Repeate Start cycle
//#define 0           BIT1 // Reserved
#define IBSWAI        BIT0 // I Bus Interface Stop in Wait Mode. 0 IIC normal
                           // 1 Halt IIc bus module clock generation in wait
               
// IBSR (IIC Status Register) 9.3.2.4, Table 9-7
#define TCF           BIT7 // Data Transferring Bit, 0 = Transfer in progress,
                           // 1 = Transfer complete
#define IAAS          BIT6 // Addressed as a Slave Bit, 0 = not addressed,
                           // 1 = Addressed as a slave
#define IBB           BIT5 // Bus Busy Bit, 0 = idle, 1 = busy
#define IBAL          BIT4 // Arbritration Lost, must be cleared by writing 1
//#define 0           BIT3 // Reserved
#define SRW           BIT2 // Slave Read/Write, 0 = slave receive, 
                           // 1 = slave transmit, master reading from slave
#define IBIF          BIT1 // I-Bus Interrupt, write 1 to clear it
#define RXAK          BIT0 // Receive Acknowledg, 0 = Ack received, 
                           // 1 = no ack received

// IBDR (IIC Data I/O Register) 9.3.2.5

               
#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_I2C_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
