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
 * @brief MC9S12XDP512 flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */


/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_ECT_FLAGS_H_SEEN
#define FILE_9S12XDP512_ECT_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//

/* -------------------------------------------------------------------------
 *  Enhanced Capture Timer Registers (ECT) Registers
 * -------------------------------------------------------------------------
 */

// TIOS (Timer Input Capture/Output Compare Select) 7.3.2.1, Table 7-2
#define IOS7          BIT7 // Input Capture or Output Compare Channel Config
#define IOS6          BIT6 // 0 = set for input capture
#define IOS5          BIT5 // 1 = set for output compare
#define IOS4          BIT4 //
#define IOS3          BIT3 //
#define IOS2          BIT2 //
#define IOS1          BIT1 //
#define IOS0          BIT0 //

// CFORC (Timer Compare Force Register) 7.3.2.2, Table 7-3
#define FOC7          BIT7 // Force Output Compare Action for channel 7:0
#define FOC6          BIT6 // A wrtie with corresponding bits set causes the
#define FOC5          BIT5 // action which is programmed for output compare
#define FOC4          BIT4 // "x" to occur immediately
#define FOC3          BIT3 // See Table 7-3 in REFERENCE DOC
#define FOC2          BIT2 //
#define FOC1          BIT1 //
#define FOC0          BIT0 //

// OC7M (Output Compare 7 Mask Register) 7.3.2.3, Table 7-4
#define OC7M7         BIT7 // Output Compare Mask Action for Channel 7:0
#define OC7M6         BIT6 // 0 = The corresponding OC7Dx bit in the output
#define OC7M5         BIT5 // compare data register will NOT be transferred to
#define OC7M4         BIT4 // the timer port on a successfull channel 7 OC.
#define OC7M3         BIT3 // 1 = The corresponding OC7Dx bit in the output 
#define OC7M2         BIT2 // compare 7 data register will be transferred to 
#define OC7M1         BIT1 // the timer port on a successful channel 7 OC.
#define OC7M0         BIT0 // See Table 7-4 in REFERENCE DOC

// OC7D (Output Compare 7 Data Register) 7.3.2.4, Table 7-5
#define OC7D7         BIT7 // Output Compare Data Bits. A Channel 7 output 
#define OC7D6         BIT6 // compare can cause bits in the output compare 7
#define OC7D5         BIT5 // data register to transfer to the timer port data
#define OC7D4         BIT4 // register depending on the output compare 7
#define OC7D3         BIT3 // mask register (OC7M)
#define OC7D2         BIT2 //
#define OC7D1         BIT1 //
#define OC7D0         BIT0 //

// TCNT (High) (Timer Count Register HIGH Byte) 7.3.2.5, Table 7-6
#define TCNT15        BIT15_16 // Timer Counter bits. The 16-bit main timer 
#define TCNT14        BIT14_16 // is an up counter. A read to this register 
#define TCNT13        BIT13_16 // will returnthe current value of the 
#define TCNT12        BIT12_16 // counter. Acces will takeplace in 1 
#define TCNT11        BIT11_16 // clock cycle.  Must be a 16 bit read
#define TCNT10        BIT10_16 // otherwise results may/will not be correct
#define TCNT9         BIT9_16 //
#define TCNT8         BIT8_16 //
#define TCNT7         BIT7_16 //
#define TCNT6         BIT6_16 //
#define TCNT5         BIT5_16 //
#define TCNT4         BIT4_16 //
#define TCNT3         BIT3_16 //
#define TCNT2         BIT2_16 //
#define TCNT1         BIT1_16 //
#define TCNT0         BIT0_16 //

// TSCR1 (Timer System Control Register 1) 7.3.2.6, Table 7-7
#define TEN           BIT7 // Timer Enable 0 = disable, 1 = enable
#define TSWAI         BIT6 // Timer Stops in Wait, 0=keep running, 1=stop
#define TSFRZ         BIT5 // Timer and Modulus Counter Stop while in freeze
#define TFFCA         BIT4 // Timer Fast Flag Clear All (see Table 7-7)
#define PRNT          BIT3 // Precision timer, 0 = legacy, 1 = precision
//#define 0           BIT2 // Reserved See REFERENCE DOC for more info
//#define 0           BIT1 // Reserved
//#define 0           BIT0 // Reserved

// TTOV (Timer Toggle Overflow Register) 7.3.2.7, Table 7-8
#define TOV7          BIT7 // Toggle on Overflow Bits (TOV[7:0])
#define TOV6          BIT6 // toggles output compare pin on timer counter
#define TOV5          BIT5 // overflow. Only works in OC mode. When set it 
#define TOV4          BIT4 // takes precedence over forced OC but not channel
#define TOV3          BIT3 // 7 override events.
#define TOV2          BIT2 // 0 = toggle OC pin on overflow disabled
#define TOV1          BIT1 // 1 = toggle OC pin on overflow enabled
#define TOV0          BIT0 //

// TCTL1 (Timer Control Register 1) 7.3.2.8, Table 7-9
#define OM7           BIT7 // OMx Output Mode
#define OL7           BIT6 // OLx Output Level
#define OM6           BIT5 // These pairs of control bits are encoded to
#define OL6           BIT0 // specify the output action to be taken as a 
#define OM5           BIT3 // result of a successful OCx compare. When OMx
#define OL5           BIT2 // or OLx is 1, the pin associated with OCx becomes
#define OM4           BIT1 // an output times to OCx, see Table 7-10
#define OL4           BIT0 // in the REFERENCE DOC

// TCTL2 (Timer Control Register 1) 7.3.2.8, Table 7-9
#define OM3           BIT7 // Same rules as TCTL1 above
#define OL3           BIT6 //
#define OM2           BIT5 //
#define OL2           BIT0 //
#define OM1           BIT3 //
#define OL1           BIT2 //
#define OM0           BIT1 //
#define OL0           BIT0 //

// TCTL3 (Timer Control Register 3) 7.3.2.9, Table 7-11
#define EDG7B         BIT7 // Input Capture Edge Control
#define EDG7A         BIT6 // These eight pairs configure the input capture
#define EDG6B         BIT5 // edge detector circuits fo reach IC channel.
#define EDG6A         BIT4 // See table 7-12 in REFERENCE DOC
#define EDG5B         BIT3 //
#define EDG5A         BIT2 //
#define EDG4B         BIT1 //
#define EDG4A         BIT0 //

// TCTL4 (Timer Control Register 4) 7.3.2.9, Table 7-11
#define EDG3B         BIT7 // Same rules as above, with the folowing exception
#define EDG3A         BIT6 // These pairs ALSO configure the input capture
#define EDG2B         BIT5 // edge control for the 4 8 bit pulse accumulators 
#define EDG2A         BIT4 // PAC[0-3].  EDG0B and EDG0A also determine the
#define EDG1B         BIT3 // active edge for the 16 bit pulse accumulator PACB
#define EDG1A         BIT2 // See table 7-12 in REFERENCE DOC
#define EDG0B         BIT1 //
#define EDG0A         BIT0 //

// TIE (Timer Interrupt Enable Register) 7.3.2.10, Table 7-13
#define C7I           BIT7 // Input Capture/Output Compare "x" Interrupt Enable
#define C6I           BIT6 // 0 = don't interrupt
#define C5I           BIT5 // 1 = interrupt 
#define C4I           BIT4 // These bits correspond bit for bit with the flags 
#define C3I           BIT3 // in the TFLG1 status register
#define C2I           BIT2 //
#define C1I           BIT1 //
#define C0I           BIT0 //

// TSCR2 (Timer System Control Register 2) 7.3.2.11, Tqble 7-14 
#define TOI           BIT7 // Timer overflwo interrupt enable
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
#define TCRE          BIT3 // Time Counter Reset Enable, 0 = free run, 1 = reset by OC on channel 7 only
#define PR2           BIT2 // Timer Prescaler Select (PR[2:0]) Specified the
#define PR1           BIT1 // division rate of the main prescaler when PRNT 
#define PR0           BIT0 // of TSCR1 is set to 0. See Table 7-15

// TFLG1 (Main Timer Interrupt Flag 1) 7.3.2.12, Table 7-16
#define C7F           BIT7 // Input Capture/Output Compare channel "x" flag
#define C6F           BIT6 // Main Timer Interrupt Flag. Writing 1 to the bit
#define C5F           BIT5 // clears it,  writing 0 has no effect.
#define C4F           BIT4 // TFLG1 indicates when interrupt condition have
#define C3F           BIT3 // occurred, and are cleaered by writign one to the 
#define C2F           BIT2 // coresponding flag
#define C1F           BIT1 // See Section 7.3.2.12 in REFERENCE DOC
#define C0F           BIT0 //

// TFLG2 (Main Timer Interrupt Flag 2) 7.3.2.13, Table 7-17
#define TOF           BIT7 // Timer Overflow Flag, set when free running timer  resets to 0. Clear by writing 1 to this bit.
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
//#define 0           BIT1 // Reserved
//#define 0           BIT0 // Reserved

// TC[0-7] (Timer Input Capture/Output Compare Registers 0-7) 7.3.2.14
// are 16 bit registers that are NOT accessed as individula bits only as whole words...

// PACTL (16-Bit Pulse Accumulator A Control Register) 7.3.2.15, Table 7-18
//#define 0           BIT7 // Reserved
#define PAEN          BIT6 // Pulse Accumulator A System Enable See Table 7-18
#define PAMOD         BIT5 // Pulse Accumulator Mode
#define PEDGE         BIT4 // Pulse Accum Edge Control, see Table 7-19
#define CLK1          BIT3 // Clock Select bits (CLK[1:0]), see Table 7-20
#define CLK0          BIT2 // in REFERENCE DOC
#define PA0VI         BIT1 // Pulse Accum A Overflow Interrupt Enable
#define PAI           BIT0 // Pulse Accum Input Interrupt Enable
 
// PAFLG (Pulse Accumulator A Flag Register) 7.3.2.16, Table 7-21
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved See Table 7-21 in REFERENCE DOC
#define PA0VF         BIT1 // Pulse Accum A Overflow Flag
#define PAIF          BIT0 // Pulse Accum Input Edge Flag

// PACNT[2-3] (Pulse Accumulation Count registers) 7.3.2.17
// PACNT[0-1] (Pulse Accumulation Count registers) 7.3.2.18
// PSCNTx are 16 bit counters intended to be read as either
// whole words or bytes depending if configured in 8 or 16 bit mode

// MCCTL (16-Bit ModulusDown Counter Register) 7.3.2.19, Table 7-22
#define MCZI          BIT7 // Modulus Down Counter Underflow Interrupt Enable
#define MODMC         BIT6 // Modulus Mode Enable
#define RDMCL         BIT5 // Read Modulus Down-Counter Load, See 7-22
#define ICLAT         BIT4 // Input Capture Force Latch Action
#define FLMC          BIT3 // Force Load Register ino the Modulus Counter Count Register
#define MCEN          BIT2 // Modulus Down-counter Enable
#define MCPR1         BIT1 // Modulus Counter Prescaler Select (MCPR[1:0])
#define MCPR0         BIT0 // Sets the division rate of the mod counter see 7-23

// MCFLG (16-Bit Modulus Down Counter Flag Register) 7.3.2.20, Table 7-24
#define MCZF          BIT7 // Modulus Counter Underflow Flag, indicates interrupt
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
#define POLF3         BIT3 // First Input Capture Polarity Status (POLF[3:0])
#define POLF2         BIT2 // Gives the polarity of the first edge that has 
#define POLF1         BIT1 // caudes an input capture to occur after the 
#define POLF0         BIT0 // capture latch has been read.  See 7-24

// ICPAR (Input Control Pulse Accumulator Register) 7.3.2.21, Table 7-25
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
#define PA3EN         BIT3 // 8 Bit Pulse Accumulator "x" enable
#define PA2EN         BIT2 // 0 = disabled
#define PA1EN         BIT1 // 1 = enabled
#define PA0EN         BIT0 //

// DLYCT (Delay Counter Control Register) 7.3.2.22, Table 7-26
#define DLY7          BIT7 // Delay Counter Select. DLY[7:0]
#define DLY6          BIT6 // When PRNT is set to 0, DLY0 and DLY1 are used to
#define DLY5          BIT5 // calculate the delay (see Table 7-27). When PRNT
#define DLY4          BIT0 // is 1 all bits are used to set a more precise 
#define DLY3          BIT3 // delay, see table 7-28
#define DLY2          BIT2 //
#define DLY1          BIT1 //
#define DLY0          BIT0 //

// ICOVW (Input Control Overwrite Register) 7.3.2.23, Table 7-29
#define NOVW7         BIT7 // No input Capture Overwrite
#define NOVW6         BIT6 // 0 = The contents of the related capture register
#define NOVW5         BIT5 // or holding register can be overwritten when a 
#define NOVW4         BIT4 // new capture or latch occurs
#define NOVW3         BIT3 // 1 = The related capture register or holding 
#define NOVW2         BIT2 // register can NOT be written by an event unless 
#define NOVW1         BIT1 // they are empty. This will prevent the captured
#define NOVW0         BIT0 // value being overwritten until it is read or 
                           // Latched in the holding register.

// ICSYS (Input Control System Control Register) 7.3.2.24, Table 7-30
#define SH37          BIT7 // SH[7:4] Share input action of Input Capture 
#define SH26          BIT6 // channels x and y SH[7:4]
#define SH15          BIT5 //
#define SH04          BIT4 //
#define TFMOD         BIT3 // Timer Flag Setting Mode
#define PACMX         BIT2 // 8-Bit Pulse Accumulator Maximum Count
#define BUFEN         BIT1 // IC Buffer Enable
#define LATQ          BIT0 // Input Control Latch or Queue Mode Enable

// PTPSR (Precision Timer Prescaler Select Register) 7.3.2.25, Table 7-31
#define PTPS7         BIT7 // PTPS[7:0] Precision timer Prescaler Select Bits
#define PTPS6         BIT6 // These 8 bits specify the division rate of the 
#define PTPS5         BIT5 // main timer prescaler.  These are effective ONLY
#define PTPS4         BIT4 // when the PRNT bit of TSCR1 is set to 1. See Table
#define PTPS3         BIT3 // 7-32 for prescale factors.
#define PTPS2         BIT2 // Basically allows from divide by 1 to 256
#define PTPS1         BIT1 // Factor = these bits + 1 ?
#define PTPS0         BIT0 //

// PTMCPSR (Precision Timer Modulus Counter Prescaler Select Register) 7.3.2.26
// Table 7-33
#define PTMPS7        BIT7 // PTMPS[7:0] Precision timer Modulus Counter
#define PTMPS6        BIT6 // Prescaler Select Bitsa.  These set the division 
#define PTMPS5        BIT5 // rate of the modulus counter prescaler. They are
#define PTMPS4        BIT4 // only effective when the PRNT bit of TSCR1 is set
#define PTMPS3        BIT3 // to 1  See Table 7-34 
#define PTMPS2        BIT2 // Basiclaly allows dividion rates from
#define PTMPS1        BIT1 // 1-256 includive
#define PTMPS0        BIT0 // Factor = these bits + 1 ?

// PBCTL (16-Bit Pulse Accumulator B Control Register) 7.3.2.27, Table 7-35
//#define 0           BIT7 // Reserved
#define PBEN          BIT6 // Pulse Accumulator B system Enable
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
#define PBOVI         BIT1 // Pulse Accumulator B Overflow interrupt enable
//#define 0           BIT0 // Reserved

// PBFLG (16-Bit Pulse Accumulator B Flag Register) 7.3.2.28, Table 7-36
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
#define PBOVF         BIT1 // Pulse Accumulator B Overflow Flag
//#define 0           BIT0 // Reserved

// PA[3-0]H (8-Bit Pulse Accumulator Holding Register) 7.3.2.29
#define PAxH7         BIT7 // these registers are used to latch the 
#define PAxH6         BIT6 // corresponding pulse accumulator when the related
#define PAxH5         BIT5 // bits in register ICPAR are enabled
#define PAxH4         BIT4 // See Section 7.4.1.3
#define PAxH3         BIT3 //
#define PAxH2         BIT2 //
#define PAxH1         BIT1 //
#define PAxH0         BIT0 //

// MCCNT (High) (Modulus Down-Counter Count Register High Byte) 7.3.2.20
// MCCNT (Low) (Modulus Down-Counter Count Register Low Byte)
// These are meantd to be read or written in 16 bit (word) form only
//

// TC[0-3]H (Timer Input Capture Holding Registers 0-3 (TCxH) 7.3.2.31
// READ ONLY, expected to be read as whole WORDS only...)


#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_ECT_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
