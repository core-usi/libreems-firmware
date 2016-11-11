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
 * @brief MC9S12XDP512 ATD (Analog to Digital) flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf
 */


/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_ADT_FLAGS_H_SEEN
#define FILE_9S12XDP512_ATD_FLAGS_H_SEEN

// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//

/* -------------------------------------------------------------------------
 *  ANALOG TO DIGITAL REGISTERS (ATD)
 * -------------------------------------------------------------------------
 */

// ATDCTL0 (ATD Control Register 0) 4.3.2.1, Table 4-2
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
#define WRAP3         BIT3 // WRAP[3:0] Wrap Around Channel Select Bits, 
#define WRAP2         BIT2 // see Table 4-3 in REFERENCE DOC
#define WRAP1         BIT1 //
#define WRAP0         BIT0 //

// ATDCTL1 (ATD Control Register 1) 4.3.2.2, table 4-4
#define ETRIGSEL      BIT7 // External Trigger Source Select See Table 4-5
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
#define ETRIGCH3      BIT3 // ETRIGCH[3:0] External Trigger Channel Select,
#define ETRIGCH2      BIT2 // These bits select  one of the A/D chanels or 
#define ETRIGCH1      BIT1 // one ofthe ETRIG[3:0] inputs as source for the 
#define ETRIGCH0      BIT0 // external trigger, see Table 4-5 in REFERENCE_DOC

// ATDCTL2 (ATD Control Register 2) 4.3.2.3, Table 4-6
#define ADPU          BIT7 // ATD Power Down, 1 = on, 0 = off
#define AFFC          BIT6 // ATD Fast Flag Clear All, 0 = Normal, 1=Fast Clear
#define AWAI          BIT5 // ATD Power Down in Wait mode, 0 = run during wait,
                           // 1 = power down during wait
#define ETRIGLE       BIT4 // External Trigger Level/Edge Control, 
                           // see Table 4-7 in REFERENCE ODC
#define ETRIGP        BIT3 // External Trigger Polarity, see Table 4-7
#define ETRIGE        BIT2 // External Trigger Mode Enable. 
                           // 0 = Disable ext trigger, 1 = Enable
#define ASCIE         BIT1 // ATD Sequence Complete Interupt Enable, 
                           // 0 = disabled, 1 = enabled
#define ASCIF         BIT0 // Read Only, ATD Sequence Complete Interrupt Flag 
                           // 0 = no interrupt occured, 1 = ATD sequence 
               // complete interrupt pending

// ATDCTL3 (ATD Control Register 3) 4.3.2.4, Table 4-8
//#define 0           BIT7 // Reserved
#define S8C           BIT6 // Conversion Sequence Length, See table 4-9
#define S4C           BIT5 // Conversion Sequence Length, See table 4-9
#define S2C           BIT4 // Conversion Sequence Length, See table 4-9
#define S1C           BIT3 // Conversion Sequence Length, See table 4-9
#define FIFO          BIT2 // Result Register FIFO Mode, 
                           // 0 = non FIFO, 1 = FIFO, see REFERENCE DOC
#define FRZ1          BIT1 // FRZ[1:0] Background Debug Freeze Enable, 
                           // See table 4-10 in REFERENCE DOC
#define FRZ0          BIT0 //

// ATDCTL4 (ATD Control Register 4) 4.3.2.5, Table 4-11
#define SRES8         BIT7 // A/D Resolution Select 0 = 10 bit, 1 = 8 bit
#define SMP1          BIT6 // SMP[1:0] Sample Time Select, 
                           // See table 4-12 in REFERENCE DOC
#define SMP0          BIT5 // 
#define PRS4          BIT4 // PRS[4:0] ATD Clock Prescaler
#define PRS3          BIT3 // ATDClock = (BusClock/(PRS+1)) * 0.5
#define PRS2          BIT2 // See Table 4-13 in REFERENCE DOC
#define PRS1          BIT1 //
#define PRS0          BIT0 //

// ATDCTL5 (ATD Control Register 5) 4.3.2.6, table 4-14
#define DJM           BIT7 // Result Register Data Justification, 
                           // 0 = Left justified, 
               // 1 = Right Justified. see Table 4-15
#define DSGN          BIT6 // Result register Data signed or Unsigned 
                           // representation 0 = unsigned, 1 = signed 
               // (2's complement), NOTE signed is not available 
               // in right justified, see table 4-15
#define SCAN          BIT5 // Continuous Conversion Sequence Mode, 
                           // 0 - single, 1 = continuous scan
#define MULT          BIT4 // Multi-Channel Sample Mode, 0 = sample only 1
                           // channel, 1 = sample across several channels
#define CD            BIT3 // C[D:A] Analog Input Channel Select Code, 
                           // Determines which channels are sampled
#define CC            BIT2 // In single mode this sets the channel to 
                           // be examined.  In scan mode
#define CB            BIT1 // it sets the STARTING channel and wrapping 
                           // at the wrap channel or at the max 
#define CA            BIT0 // if start is set higher than wrap.

// ATDSTAT0 (ATD Status Register 0) 4.3.2.7, Table 4-18
#define SCF           BIT7 // Sequence Complete Flag, 0 = conversion not 
                           // complete, 1 = conversion complete
//#define 0           BIT6 // Reserved
#define ETORF         BIT5 // Externa; Trigger Overrun Flag, 0 = no overrun, 
                           // 1 = overrun occurred
#define FIFOR         BIT4 // FIFO Overrun flag, see REFERENCE DOC
#define CC3           BIT3 // READ ONLY CC[3:0] Conversion Counter
#define CC2           BIT2 // READ ONLY
#define CC1           BIT1 // READ ONLY
#define CC0           BIT0 // READ ONLY

// ATDTEST0 (ATD Test Register 0) 4.3.2.8
// FACTORY USE ONLY
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
//#define 0           BIT1 // Reserved
//#define 0           BIT0 // Reserved

// ATDTEST1 (ATD Test Register 1) 4.3.2.9
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
//#define 0           BIT1 // Reserved
#define SC            BIT0 //  Special Channel Conversion Bit, 
                           // see Table 4-20 in REREFENCE DOC

// ATDSTAT2 (ATD Status Register 2) 4.3.2.10,  Table 4-21, ALL ARE READ ONLY!
#define CCF15         BIT7 // CCF[15:8] Conversion Complete Flag Bitsa. 
#define CCF14         BIT6 // Bits are set when conversions for 
#define CCF13         BIT5 // their channel are complete. 
#define CCF12         BIT4 // See REFERENCE DOC for more information
#define CCF11         BIT3 //
#define CCF10         BIT2 //
#define CCF9          BIT1 //
#define CCF8          BIT0 //

// ATDSTAT1 (ATD Status Register 1) 4.3.2.11, Table 4-22 ALL ARE READ ONLY
#define CCF7          BIT7 // CCF[7:0] Conversion Complete Flag Bitsa. 
#define CCF6          BIT6 // Bits are set when conversions for 
#define CCF5          BIT5 // their channel are complete. 
#define CCF4          BIT4 // See REFERENCE DOC for more information
#define CCF3          BIT3 //
#define CCF2          BIT2 //
#define CCF1          BIT1 //
#define CCF0          BIT0 //

// ATDDIEN0 (ATD Input Enable Register 0) 4.3.2.12, Table 4-23
#define IEN15         BIT7 // IEN[15:8] ATD Digital Input Enable on Channel Bits
#define IEN14         BIT6 // 0 = Disable digital input buffer to PTADx
#define IEN13         BIT5 // 1 = Enable digital input buffer to PTADx
#define IEN12         BIT4 // Don't set this if using this pin as 
#define IEN11         BIT3 // an analog input.
#define IEN10         BIT2 // See Table 4-23 in REFERENCE DOC 
#define IEN9          BIT1 //
#define IEN8          BIT0 //

// ATDDIEN1 (ATD Input Enable Register 1) 4.3.2.13, Table 4-24
#define IEN7          BIT7 // IEN[15:8] ATD Digital Input Enable on Channel Bits
#define IEN6          BIT6 // 0 = Disable digital input buffer to PTADx
#define IEN5          BIT5 // 1 = Enable digital input buffer to PTADx
#define IEN4          BIT4 // Don't set this if using this pin as 
#define IEN3          BIT3 // an analog input.
#define IEN2          BIT2 // See Table 4-23 in REFERENCE DOC 
#define IEN1          BIT1 //
#define IEN0          BIT0 //

// PORTAD0 (Port Data Register 0) 4.3.2.14, Table 4-25, ALL ARE READ ONLY
#define PTAD15        BIT7 // PTAD[15:8] A/D Channel x (ANx) Digital Input Bits
#define PTAD14        BIT6 // If the digital input buffer on the ANx pin is
#define PTAD13        BIT5 // enabled (IENx = 1) or channel x is enabled as 
#define PTAD12        BIT4 // external trigger (ETRIGE = 1, ETRIGCH[3:0] = x 
#define PTAD11        BIT3 // ETRIGSEL = 0) read returns the logic level on 
#define PTAD10        BIT2 // ANx pin (signal potential snot meeting V(il) and 
#define PTAD9         BIT1 // V(ih) specs will have indeterminate value). If 
#define PTAD8         BIT0 // the digital input buffers are disabled (IENx = 0)
                           // and channel x is not enabled as external trigger,
               // read return a "1" RESET sets all PORTAD0 bits to 1

// PORTAD1 (Port Data Register 1) 4.3.2.15, Table 4-26
#define PTAD7         BIT7 // see PORTAD0, same rules apply
#define PTAD6         BIT6 //
#define PTAD5         BIT5 //
#define PTAD4         BIT4 //
#define PTAD3         BIT3 //
#define PTAD2         BIT2 //
#define PTAD1         BIT1 //
#define PTAD0         BIT0 //

// ATDDR0H, ATDDR0L (ATD Result Register 0)
// ATDDR1H, ATDDR1L (ATD Result Register 1)
// ATDDR2H, ATDDR2L (ATD Result Register 2)
// ATDDR3H, ATDDR3L (ATD Result Register 3)
// ATDDR4H, ATDDR4L (ATD Result Register 4)
// ATDDR5H, ATDDR5L (ATD Result Register 5)
// ATDDR6H, ATDDR6L (ATD Result Register 6)
// ATDDR7H, ATDDR7L (ATD Result Register 7)
// ATDDR8H, ATDDR8L (ATD Result Register 8)
// ATDDR9H, ATDDR9L (ATD Result Register 9)
// ATDDR10H, ATDDR10L (ATD Result Register 10)
// ATDDR11H, ATDDR11L (ATD Result Register 11)
// ATDDR12H, ATDDR12L (ATD Result Register 12)
// ATDDR13H, ATDDR13L (ATD Result Register 13)
// ATDDR14H, ATDDR14L (ATD Result Register 14)
// ATDDR15H, ATDDR15L (ATD Result Register 15)
// Pqcking depends on the combination of SRES8 DJM and DSGN, see Table 4-15 in RERERENCE DOC
// 16 | 15 | 14 | 13 | 12 | 11 | 10 | 9  | 8  | 7  | 6  | 5  | 4  | 3  | 2  | 1  | 0  |
// MSB|Bit8|Bit7|Bit6|Bit5|Bit4|Bit3|Bit2|Bit1|Bit0| 0  | 0  | 0  | 0  | 0  | 0  | 0  |  10 Bit LJ
// MSB|Bit6|Bit5|Bit4|Bit3|Bit2|Bit1|Bit0| 0  | 0  | 0  | 0  | 0  | 0  | 0  | 0  | 0  |  8 Bit LJ
//  0 | 0  | 0  | 0  | 0  | 0  | 0  | 0  | 0  |Bit7|Bit6|Bit5|Bit4|Bit3|Bit3|Bit1|Bit0|  8 bit RJ
//  0 | 0  | 0  | 0  | 0  | 0  | 0  |Bit9|Bit8|Bit7|Bit6|Bit5|Bit4|Bit3|Bit3|Bit1|Bit0|  10 bit RJ


#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_ATD_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
