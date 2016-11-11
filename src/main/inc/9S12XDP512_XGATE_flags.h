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
#ifndef FILE_9S12XDP512_XGATE_FLAGS_H_SEEN
#define FILE_9S12XDP512_XGATE_FLAGS_H_SEEN


// REFERENCE DOC: http://cache.freescale.com/files/microcontrollers/doc/data_sheet/MC9S12XDP512RMV2.pdf
//

/* -------------------------------------------------------------------------
 *  XGATE CO-PROCESSOR REGISTERS (XGATE)
 * -------------------------------------------------------------------------
 */

// XGMCTL (XGATE Control Register) 6.3.1.1, Table 6-1
#define XGEM          BIT15_16 // Controls write access to XGE Bit, see Table 6-1 in REFERNCE DOC
#define XGFRZM        BIT14_16 // Contols write access to the XGFRZ bit
#define XGDBGM        BIT13_16 // Controls write access to the XGDBG bit
#define XGSSM         BIT12_16 // Controls write access to the XGSS bit
#define XGFACTM       BIT11_16 // Controls write access to the XGFACT bit
//#define 0           BIT10_16 // Reserved
#define XGSWEIFM      BIT9_16  // Controls write access to the XGSWEIF bit
#define XGIEM         BIT8_16  // Controls write access to the XGIE bit
#define XGE           BIT7_16  // XGATE Module enable bit, 0 = disabled, 
                               // 1 = enabled
#define XGFRZ         BIT6_16  // Halt XGATE in Freeze Mode, 0 = normal 
                               // in freeze, 1 stop in freeze
#define XGDBG         BIT5_16  // XGATE Debug Mode, 0 = not in debug mode, 
                               // 1 = Enter debug mode
#define XGSS          BIT4_16  // XGATE Single Step 
#define XGFACT        BIT3_16  // Fake XGATE Activity, 0 = Flag activity 
                               // only if not idle, 1 = flag always
//#define 0           BIT2_16  // Reserved
#define XGSWEIF       BIT1_16  // XGATE Software Error Interrupt Flag
#define XGIE          BIT0_16  // XGATE Interrupt Enable. 0 = disable all
                               // XG interrups, 1 = enable all XGATE interrupts

// XGCHID (XGATE Channel ID Register) 6.3.1.2, Table 6-2
//#define 0           BIT7  // 
#define XGCHID6       BIT6  // XGCHID[6:0] ID of the currently active channel
#define XGCHID5       BIT5  // 
#define XGCHID4       BIT4  // 
#define XGCHID3       BIT3  // 
#define XGCHID2       BIT2  // 
#define XGCHID1       BIT1  // 
#define XGCHID0       BIT0  // 

// XGVBR (XGATE Vector Base Address Register) 6.3.1.3, Table 6-3
#define XGVBR15       BIT15_16 // XBVBR[15:1] Vector Base Adress, holds 
#define XGVBR14       BIT14_16 // the start address of the vector block 
#define XGVBR13       BIT13_16 // in the XGATE Memory map
#define XGVBR12       BIT12_16 // 
#define XGVBR11       BIT11_16 // 
#define XGVBR10       BIT10_16 // 
#define XGVBR9        BIT9_16 // 
#define XGVBR8        BIT8_16 // 
#define XGVBR7        BIT7_16 // 
#define XGVBR6        BIT6_16 // 
#define XGVBR5        BIT5_16 // 
#define XGVBR4        BIT4_16 // 
#define XGVBR3        BIT3_16 // 
#define XGVBR2        BIT2_16 // 
#define XGVBR1        BIT1_16 // 
//#define 0           BIT0_16  // Reserved

// XGIF_7F_70 (XGATE Channel Interrupt Flag Register (70-7F) 6.3.1.4, Table 6-4
//#define 0           BIT15_16 // Reserved
//#define 0           BIT14_16 // Reserved
//#define 0           BIT13_16 // Reserved
//#define 0           BIT12_16 // Reserved
//#define 0           BIT11_16 // Reserved
//#define 0           BIT10_16 // Reserved
//#define 0           BIT9_16  // Reserved
#define XGIF_78       BIT8_16 // The Interrupt vector provides access to the
#define XGIF_77       BIT7_16 // interrupt flags bits of each channel. Each
#define XGIF_76       BIT6_16 // flag may be cleared by writing a "1" to its
#define XGIF_75       BIT5_16 // location
#define XGIF_74       BIT4_16 //
#define XGIF_73       BIT3_16 //
#define XGIF_72       BIT2_16 //
#define XGIF_71       BIT1_16 //
#define XGIF_70       BIT0_16 //
// XGIF_6F_60 (XGATE Channel Interrupt Flag Register (60-6F) 6.3.1.4, Table 6-4
#define XGIF_6F       BIT15_16 //
#define XGIF_6E       BIT14_16 //
#define XGIF_6D       BIT13_16 //
#define XGIF_6C       BIT12_16 //
#define XGIF_6B       BIT11_16 //
#define XGIF_6A       BIT10_16 //
#define XGIF_69       BIT9_16 //
#define XGIF_68       BIT8_16 //
#define XGIF_67       BIT7_16 //
#define XGIF_66       BIT6_16 //
#define XGIF_65       BIT5_16 //
#define XGIF_64       BIT4_16 //
#define XGIF_63       BIT3_16 //
#define XGIF_62       BIT2_16 //
#define XGIF_61       BIT1_16 //
#define XGIF_60       BIT0_16 //
// XGIF_5F_50 (XGATE Channel Interrupt Flag Register (50-5F) 6.3.1.4, Table 6-4
#define XGIF_5F       BIT15_16 //
#define XGIF_5E       BIT14_16 //
#define XGIF_5D       BIT13_16 //
#define XGIF_5C       BIT12_16 //
#define XGIF_5B       BIT11_16 //
#define XGIF_5A       BIT10_16 //
#define XGIF_59       BIT9_16 //
#define XGIF_58       BIT8_16 //
#define XGIF_57       BIT7_16 //
#define XGIF_56       BIT6_16 //
#define XGIF_55       BIT5_16 //
#define XGIF_54       BIT4_16 //
#define XGIF_53       BIT3_16 //
#define XGIF_52       BIT2_16 //
#define XGIF_51       BIT1_16 //
#define XGIF_50       BIT0_16 //
// XGIF_4F_40 (XGATE Channel Interrupt Flag Register (40-4F) 6.3.1.4, Table 6-4
#define XGIF_4F       BIT15_16 //
#define XGIF_4E       BIT14_16 //
#define XGIF_4D       BIT13_16 //
#define XGIF_4C       BIT12_16 //
#define XGIF_4B       BIT11_16 //
#define XGIF_4A       BIT10_16 //
#define XGIF_49       BIT9_16 //
#define XGIF_48       BIT8_16 //
#define XGIF_47       BIT7_16 //
#define XGIF_46       BIT6_16 //
#define XGIF_45       BIT5_16 //
#define XGIF_44       BIT4_16 //
#define XGIF_43       BIT3_16 //
#define XGIF_42       BIT2_16 //
#define XGIF_41       BIT1_16 //
#define XGIF_40       BIT0_16 //
// XGIF_3F_30 (XGATE Channel Interrupt Flag Register (30-3F) 6.3.1.4, Table 6-4
#define XGIF_3F       BIT15_16 //
#define XGIF_3E       BIT14_16 //
#define XGIF_3D       BIT13_16 //
#define XGIF_3C       BIT12_16 //
#define XGIF_3B       BIT11_16 //
#define XGIF_3A       BIT10_16 //
#define XGIF_39       BIT9_16 //
#define XGIF_38       BIT8_16 //
#define XGIF_37       BIT7_16 //
#define XGIF_36       BIT6_16 //
#define XGIF_35       BIT5_16 //
#define XGIF_34       BIT4_16 //
#define XGIF_33       BIT3_16 //
#define XGIF_32       BIT2_16 //
#define XGIF_31       BIT1_16 //
#define XGIF_30       BIT0_16 //
// XGIF_2F_20 (XGATE Channel Interrupt Flag Register (20-2F) 6.3.1.4, Table 6-4
#define XGIF_2F       BIT15_16 //
#define XGIF_2E       BIT14_16 //
#define XGIF_2D       BIT13_16 //
#define XGIF_2C       BIT12_16 //
#define XGIF_2B       BIT11_16 //
#define XGIF_2A       BIT10_16 //
#define XGIF_29       BIT9_16 //
#define XGIF_28       BIT8_16 //
#define XGIF_27       BIT7_16 //
#define XGIF_26       BIT6_16 //
#define XGIF_25       BIT5_16 //
#define XGIF_24       BIT4_16 //
#define XGIF_23       BIT3_16 //
#define XGIF_22       BIT2_16 //
#define XGIF_21       BIT1_16 //
#define XGIF_20       BIT0_16 //
// XGIF_1F_10 (XGATE Channel Interrupt Flag Register (10-1F) 6.3.1.4, Table 6-4
#define XGIF_1F       BIT15_16 //
#define XGIF_1E       BIT14_16 //
#define XGIF_1D       BIT13_16 //
#define XGIF_1C       BIT12_16 //
#define XGIF_1B       BIT11_16 //
#define XGIF_1A       BIT10_16 //
#define XGIF_19       BIT9_16 //
#define XGIF_18       BIT8_16 //
#define XGIF_17       BIT7_16 //
#define XGIF_16       BIT6_16 //
#define XGIF_15       BIT5_16 //
#define XGIF_14       BIT4_16 //
#define XGIF_13       BIT3_16 //
#define XGIF_12       BIT2_16 //
#define XGIF_11       BIT1_16 //
#define XGIF_10       BIT0_16 //
// XGIF_0F_00 (XGATE Channel Interrupt Flag Register (00-0F) 6.3.1.4, Table 6-4
#define XGIF_0F       BIT15_16 //
#define XGIF_0E       BIT14_16 //
#define XGIF_0D       BIT13_16 //
#define XGIF_0C       BIT12_16 //
#define XGIF_0B       BIT11_16 //
#define XGIF_0A       BIT10_16 //
#define XGIF_09       BIT9_16 //
//#define 0           BIT8_16 // Reserved
//#define 0           BIT7_16 // Reserved
//#define 0           BIT6_16 // Reserved
//#define 0           BIT5_16 // Reserved
//#define 0           BIT4_16 // Reserved
//#define 0           BIT3_16 // Reserved
//#define 0           BIT2_16 // Reserved
//#define 0           BIT1_16 // Reserved
//#define 0           BIT0_16 // Reserved

// XGSWT (XGATE Software Trigger Register) 6.3.1.5, Table 6-5
#define XGSWTM7       BIT15_16 // Software Trigger Mask. These bits control 
#define XGSWTM6       BIT14_16 // write access to the XGSWT bits, Each XGSWT
#define XGSWTM5       BIT13_16 // bit can only be written if a "1" is written
#define XGSWTM4       BIT12_16 // to the corresponding XGSWTM bit in the SAME
#define XGSWTM3       BIT11_16 // ACCESS,  These always read as 0.
#define XGSWTM2       BIT10_16 //
#define XGSWTM1       BIT9_16 //
#define XGSWTM0       BIT8_16 //
#define XGSWT7        BIT7_16 // Software Trigger Bits.  These bits act as 
#define XGSWT6        BIT6_16 // interrupt flags that are able to trigger
#define XGSWT5        BIT5_16 // XGATE software channels, They can only be set
#define XGSWT4        BIT4_16 // and cleared bu software
#define XGSWT3        BIT3_16 // See table 6-5 in REFERENCE_DOC
#define XGSWT2        BIT2_16 //
#define XGSWT1        BIT1_16 //
#define XGSWT0        BIT0_16 //

// XGSEM (XGATE Semaphore Register) 6.3.1.6, Table 6-6
#define XGSEMM7       BIT15_16 // Semaphore Mask. These bits control access to
#define XGSEMM6       BIT14_16 // the XGSEM bits
#define XGSEMM5       BIT13_16 // 0 = disable write access to XGSEM bit in 
#define XGSEMM4       BIT12_16 // same bus cycle.
#define XGSEMM3       BIT11_16 // 1 = enable write access to XGSEM bit in
#define XGSEMM2       BIT10_16 // same bus cycle
#define XGSEMM1       BIT9_16 //
#define XGSEMM0       BIT8_16 //
#define XGSEM7        BIT7_16 // Semaphore Bits. These bits indicate whether
#define XGSEM6        BIT6_16 // a semaphore is locked by the S12X_CPU. A 
#define XGSEM5        BIT5_16 // semaphore can be attempted to be set by 
#define XGSEM4        BIT4_16 // writing a "1" to the XGSEM bit and to its 
#define XGSEM3        BIT3_16 // corresponding MASK bit in the same access.
#define XGSEM2        BIT2_16 // Only unlocked semaphores can be set. Can be 
#define XGSEM1        BIT1_16 // be cleared by writing a "0" to XGSEM and 1 to 
#define XGSEM0        BIT0_16 // corresponding XGSEMM bit.

// XGCCR (XGATE Condition Code Register) 6.3.1.7, Table 6-7
//#define 0           BIT7 // Reserved
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
#define XGN           BIT3 // Sign Flag
#define XGZ           BIT2 // Zero Flag
#define XGV           BIT1 // Overflow Flag
#define XGC           BIT0 // Carry Flag

// XGPC (XGATE Program Counter register) 6.3.1.8, Table 6-8
// This is a 16 bit register (Program Counter)

// XGR1 (XGATE Register 1) 6.3.1.9 Table 6-9
// This is a 16 bit register 
// It is preloaded with  the initial variable pointer of the channel's
// service request vector (see 6-20 in REFERENCE DOC)

// XGR2 (XGATE Register 2) 6.3.1.10, Tabele 6-10
// This is a 16 bit register 

// XGR3 (XGATE Register 3) 6.3.1.11, Tabele 6-11
// This is a 16 bit register 

// XGR4 (XGATE Register 4) 6.3.1.12, Tabele 6-12
// This is a 16 bit register 

// XGR5 (XGATE Register 5) 6.3.1.13, Tabele 6-13
// This is a 16 bit register 

// XGR6 (XGATE Register 6) 6.3.1.14, Tabele 6-14
// This is a 16 bit register 

// XGR7 (XGATE Register 7) 6.3.1.15, Tabele 6-15
// This is a 16 bit register 

#else
  /* let us know if we are being untidy with headers */
  #warning "Header file 9S12XDP512_XGATE_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
