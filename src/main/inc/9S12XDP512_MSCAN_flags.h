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
 * @brief MC9S12XDP512 IIC flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */

/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_MSCAN_FLAGS_H_SEEN
#define FILE_9S12XDP512_MSCAN_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//
               
/* -------------------------------------------------------------------------
 *  Controller Area Network (I2C) Registers
 * -------------------------------------------------------------------------
 */

// CANCTL0 (MSCAN Control Register 0) 10.3.2.1, Table 10-1
#define RXFRM         BIT7 // Received Frame Flag, cleared by writing 1
#define RXACT         BIT6 // Receiver Active status 0 = idle, 1 = receiving
#define CSWAI         BIT5 // CAN Stops in wait mode, 0 = no, 1 = yes
#define SYNCH         BIT4 // Synchronized Status, 0 not sync'd, 1 = sync'd
#define TIME          BIT3 // Timer Enable, 0 = disabled, 1 = enabled
#define WUPE          BIT2 // Wake-Up Enable, 0 = disabled, 1 = enabled
#define SLPRQ         BIT1 // Sleep Mode request, 0 = running, 1 sleep when idle
#define INITRQ        BIT0 // Initialization Mode Request, 0 - normal, 1 = init

// CANCTL1 (MSCAN Control Register 1) 10.3.2.2, Table 10-2
#define CANE          BIT7 // MSCAN Enable, 0 = disabled, 1 = enabled
#define CLKSRC        BIT6 // MSCAN Clock Source, 0 = OSCCLK, 1 = BUSCLK
#define LOOPB         BIT5 // Loopback Self Test Mode, 0 = disabled, 1 = enabled
#define LISTEN        BIT4 // Listen Only Mode, 0 = normal, 1 = listen only
#define BORM          BIT3 // Bus-Off ecovery Mode, 0 = auto, 1 = on request
#define WUPM          BIT2 // Wake-Up Mode, 0 = on any dominant 1 = Tup min len
#define SLPAK         BIT1 // Sleep Mode Ack, 0 = running, 1 = sleep mode active
#define INITAK        BIT0 // Init Mode Ack, 0 = running, 1 = init mode active

// CANBTR0 (MSCAN Bus Timing register 0) 10.3.2.3 Table 10-3
#define SVW1          BIT7 // SJW[1:0] Sync Jump Width, see 10-3/10-4
#define SJW0          BIT6 //
#define BRP5          BIT5 // Baud Rate Prescaler BRP[5:0]  See Table 10-5
#define BRP4          BIT4 // Allows prescale values of 1-64
#define BRP3          BIT3 //
#define BRP2          BIT2 //
#define BRP1          BIT1 //
#define BRP0          BIT0 //

// CANBTR1 (MSCAN Bus Timing Register 1) 10.3.2.4, Table 10-6
#define SAMP          BIT7 // Sampling, 0 = 1 sample per bit, 1 = 3 samp/bit
#define TSEG22        BIT6 // Time Segments 2 (TSEG2[2:0] See Table 10-7
#define TSEG21        BIT5 // Range from 1-8 Tq clock cycles
#define TSEG20        BIT4 //
#define TSEG13        BIT3 // Time Segment 1 TSEG1[3:0] See table 10-8
#define TSEG12        BIT2 // Range frmo1-16 Tq clock cycles
#define TSEG11        BIT1 //
#define TSEG10        BIT0 //

// CANRFLG (MSCAN Receiver Flag register) 10.3.2.5, Table 10-9
#define WUPIF         BIT7 // Wake-Up Interrupt Flag
#define CSCIF         BIT6 // CAN Status Change Interrupt Flag
#define RSTAT1        BIT5 // Receiver Status Bits (RSTAT[1:0]) 00 = RxOK
#define RSTAT0        BIT4 // 01 = RxWRN, 10 = RxERR, 11 = Bus-off, errcnt>255
#define TSTAT1        BIT3 // Transmitter Status Bits (TSTAT[1:0]) 00 = TxOK
#define TSTAT0        BIT2 // 01 = TXWRN, 10 = TxERR, 11 = Bus-Off, errcnt>255
#define OVRIF         BIT1 // Overrun Interrupt Flag, 0, no overrun, 1 = overrun
#define RXF           BIT0 // Receive Buffer Full Flag, 0 no msg, 1 = msg avail

// CANRIER (MSCAN Receiver Interrupt Enable Register) 10.3.2.6, Table 10-10
#define WUPIE         BIT7 // Wake-Up Interrupt Enable,0 = disabled,1 = enabled
#define CSCIE         BIT6 // CAN Status Chane Interrupt Enable
#define RSTATE1       BIT5 // Receiver Status Change Enable, see 10-10
#define RSTATE0       BIT4 //
#define TSTATE1       BIT3 // Transmitter Status Change Enable, see 10-10
#define TSTATE0       BIT2 //
#define OVRIE         BIT1 // Overrun Interrupt Enable
#define RXFIE         BIT0 // Receiver Full Interrupt enable

// CANTFLG (MSCAN Transmitter Flag Register) 10.3.2.7, Table 10-11
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
//#define 0           BIT3 //
#define TXE2          BIT2 // Transmitter Buffer Empty (TXE[2:0], 
#define TXE1          BIT1 // 0 = full, 1 = empty
#define TXE0          BIT0 //

// CANTIER (MSCAN Transmitter Interrupt Enable Register) 10.3.2.8, Table 10-12
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
//#define 0           BIT3 //
#define TXEIE2        BIT2 // Transmitter Empty Interupt Enable (TXEIE[2:0], 
#define TXEIE1        BIT1 // 0 no interrupt for this event, 1 transmitter
#define TXEIE0        BIT0 // emptyc causes transmitter empty interupt request

// CANTARQ (MSCAN Xmitter Message Abort Request Register) 10.3.2.9, Table 10-13
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
//#define 0           BIT3 //
#define ABTRQ2        BIT2 // Abort Request, 0 - no abort request, 1 = abort 
#define ABTRQ1        BIT1 // request pending.
#define ABTRQ0        BIT0 //

// CANTAAK (MSCAN Xmitter Message Abort Ack Register) 1-.3.2.10, Table 10-14
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
//#define 0           BIT3 //
#define ABTAK2        BIT2 // Abort Acknowledg, 0 = msg not aborted,
#define ABTAK1        BIT1 // 1 = the message was aborted
#define ABTAK0        BIT0 //

// CANTBSEL (MSCAN Transmit Buffer Selection register) 10.3.2.11, Table 10-15
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
//#define 0           BIT3 //
#define TX2           BIT2 // Transmit Buffer Select, 0 = deselected, 
#define TX1           BIT1 // 1 = selected, see Table 10-15
#define TX0           BIT0 //

// CANIDAC (MSCAN Identifier Acceptance Control Register) 10.3.2.12, Table 10-16
//#define 0           BIT7 //
//#define 0           BIT6 //
#define IDAM1         BIT5 // Identifier Acceptance Mode, See Table 10-17
#define IDAM0         BIT4 //
//#define 0           BIT3 //
#define IDHIT2        BIT2 // Identifier Acceptance Hit Indicator
#define IDHIT1        BIT1 // See Table 10-18
#define IDHIT0        BIT0 //

// CANMISC (MSCAN Miscellaneous Register) 10.3.2.14, Table 10-19
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
//#define 0           BIT3 //
//#define 0           BIT2 //
//#define 0           BIT1 //
#define BOHOLD        BIT0 // Bus-Off Statte Hold Until User Request, see 10-19

// CANRXERR (MSCAN Receive Error Counter) 10.3.2.15
#define RXERR7        BIT7 // READ only, intended to be read as a byte
#define RXERR6        BIT6 // Read only when in sleep mode or init mode
#define RXERR5        BIT5 //
#define RXERR4        BIT4 //
#define RXERR3        BIT3 //
#define RXERR2        BIT2 //
#define RXERR1        BIT1 //
#define RXERR0        BIT0 //

// CANTXERR (MSCAN Transmit Error Counter) 10.3.2.16 
#define TXERR7        BIT7 // READ only, intended to be read as a byte
#define TXERR6        BIT6 // Read only when in sleep mode or init mode
#define TXERR5        BIT5 //
#define TXERR4        BIT4 //
#define TXERR3        BIT3 //
#define TXERR2        BIT2 //
#define TXERR1        BIT1 //
#define TXERR0        BIT0 //

// CANIDAR0-3 (MSCAN Identifier Acceptance Registers (1st Bank) 10.3.2.17
// CANIDAR4-7
#define AC7           BIT7 // Acceptance Code Bits AC[7:0] comprise a user-
#define AC6           BIT6 // defined sequence of bits which the corresponding
#define AC5           BIT5 // bits of the related identifier register (IDRn) of
#define AC4           BIT4 // the receive message buffer are compared. The 
#define AC3           BIT3 // result of this comparison is then masked with the
#define AC2           BIT2 // corresponding identifier mask register
#define AC1           BIT1 //
#define AC0           BIT0 //

// CANIDMR0-7 (MSCAN Identifier Mask Registers (CANIDMR0-7) 10.3.2.18
#define AM7           BIT7 // The identifier mask register specifies which of 
#define AM6           BIT6 // the corresponding bits in the CANIDARx register
#define AM5           BIT5 // are relevant for acceptance filtering. To receive
#define AM4           BIT4 // std identifiers in 32 bit filter mode, it is
#define AM3           BIT3 // required to program the last three bits AM[2:0]
#define AM2           BIT2 // in the mask register CANIDMR1 and CANIDMR5 to
#define AM1           BIT1 // "don't care". Likewise for 16 bit filter mode
#define AM0           BIT0 // AM[2:0} need to be set to "don't care" in 
                           // CANIDMR[1,3,5,7]
               
/* EXTENDED (29 BIT) Mapping*/
# ifdef CAN_29BIT // EXTENDED IDENTIFIER MAPPING 10.3.3.1.1
// IDR0 (Identifier Register 0, Extended Mapping)
#define ID28          BIT7 // ID[28:21] Extended Format Identifier, ID28 is MSB
#define ID27          BIT6 //
#define ID26          BIT5 //
#define ID25          BIT4 //
#define ID24          BIT3 //
#define ID23          BIT2 //
#define ID22          BIT1 //
#define ID21          BIT0 //

// IDR1 (Identifier Register 1, Extended Mapping)
#define ID20          BIT7 // ID[20:18] Extended Format Identifier
#define ID19          BIT6 //
#define ID18          BIT5 //
#define SRR           BIT4 // Substitute remtoe request, only used in extended
#define IDE           BIT3 // ID Extended 0 = standard (11 bit ), 1=ext (29 bit)
#define ID17          BIT2 // ID[17:15] Extended format identifier
#define ID16          BIT1 //
#define ID15          BIT0 //

// IDR2 (Identifier Register 2, Extended Mapping)
#define ID14          BIT7 // ID[14:7] Extended Format Identifier, ID28 is MSB
#define ID13          BIT6 //
#define ID12          BIT5 //
#define ID11          BIT4 //
#define ID10          BIT3 //
#define ID9           BIT2 //
#define ID8           BIT1 //
#define ID7           BIT0 //

// IDR3 (Identifier Register 3, Extended Mapping)
#define ID6           BIT7 // ID[6:0] Extended Format Identifier, ID28 is MSB
#define ID5           BIT6 //
#define ID4           BIT5 //
#define ID3           BIT4 //
#define ID2           BIT3 //
#define ID1           BIT2 //
#define ID0           BIT1 //
#define RTR           BIT0 // Remote Transmission Request, 0 = data frame,
                           // 1 == Remote frame

#endif


/* STANDARD (11 BIT) Mapping*/
#ifdef CAN_11BIT
// IDR0 (Identifier Register 0, Standard Mapping)
#define ID10          BIT7 // ID[10:3] Standard Format Identifier
#define ID9           BIT6 //
#define ID8           BIT5 //
#define ID7           BIT4 //
#define ID6           BIT3 //
#define ID5           BIT2 //
#define ID4           BIT1 //
#define ID3           BIT0 //

// IDR1 (Identifier Register 1, Standard Mapping)
#define ID2           BIT7 // ID[2:0] Standard Format Identifier
#define ID1           BIT6 //
#define ID0           BIT5 //
#define RTR           BIT4 // Remote Transmission request, 0 = data frame
                           // 1 = remote frame
#define IDE           BIT3 // ID Extended, 0 = standard (11), 1 = extended (29)
//#define 0           BIT2 // Reserved
//#define 0           BIT1 // Reserved
//#define 0           BIT0 // Reserved

// IDR2 (Identifier Register 2, Standard Mapping)
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
//#define 0           BIT1 // Reserved
//#define 0           BIT0 // Reserved

// IDR3 (Identifier Register 3, Standard Mapping)
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
//#define 0           BIT1 // Reserved
//#define 0           BIT0 // Reserved
#endif

// DSR0-7 (Data Segment Registers) 10.3.3.2
#define DB7           BIT7 // Data Segment registers (8 of them) contain the
#define DB6           BIT6 // data to be transmitted or received. The number of
#define DB5           BIT5 // bytes to be sent or received is determined by the
#define DB4           BIT4 // length code in the corresponding DLR register
#define DB3           BIT3 //
#define DB2           BIT2 //
#define DB1           BIT1 //
#define DB0           BIT0 //

// DLR (Data Length register) 10.3.3.3, Table 10-33
//#define 0           BIT7 //
//#define 0           BIT6 //
//#define 0           BIT5 //
//#define 0           BIT4 //
#define DLC3          BIT3 // Data Length Code Bits DLR[3:0] determine the 
#define DLC2          BIT2 // number of bytes  of the respective message
#define DLC1          BIT1 // rang of 0-8
#define DLC0          BIT0 // See table 10-33

// TBPF (Transmit Buffer Priority Register) 10.3.3.4
#define PRIO7         BIT7 // See 10.3.3.4
#define PRIO6         BIT6 //
#define PRIO5         BIT5 //
#define PRIO4         BIT4 //
#define PRIO3         BIT3 //
#define PRIO2         BIT2 //
#define PRIO1         BIT1 //
#define PRIO0         BIT0 //

// TSRH (Time Stamp Register High Byte) 10.3.3.5
#define TSR15         BIT7 //
#define TSR14         BIT6 //
#define TSR13         BIT5 //
#define TSR12         BIT4 //
#define TSR11         BIT3 //
#define TSR10         BIT2 //
#define TSR9          BIT1 //
#define TSR8          BIT0 //

// TSRH (Time Stamp Register Low Byte) 10.3.3.5
#define TSR7          BIT7 //
#define TSR6          BIT6 //
#define TSR5          BIT5 //
#define TSR4          BIT4 //
#define TSR3          BIT3 //
#define TSR2          BIT2 //
#define TSR1          BIT1 //
#define TSR0          BIT0 //

/* ID Definition */
#define ST_ID_100       (0x20000000)    /* Standard Id 0x100 formatted to be loaded
                                 * in IDRx Registers in Tx Buffer
                                 */

/* Acceptance Code Definitions */
#define ACC_CODE_ID100    (0x2000)
#define ACC_CODE_ID100_HIGH ((ACC_CODE_ID100&0xFF00)>>8)
#define ACC_CODE_ID100_LOW  (ACC_CODE_ID100&0x00FF)


/* Mask Code Definitions */
#define MASK_CODE_ST_ID    (0x0007)
#define MASK_CODE_ST_ID_HIGH ((MASK_CODE_ST_ID&0xFF00)>>8)
#define MASK_CODE_ST_ID_LOW  (MASK_CODE_ST_ID&0xFF)

/* Error Flags Definition */
#define NO_ERR          (0x00)
#define ERR_BUFFER_FULL (0x80)

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
