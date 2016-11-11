/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief Memory usage directives
 *
 * This file is solely for the definition of compiler memory usage directives.
 * Each one is just a short form of the larger statements DFAR and FFAR found
 * near the top of this file.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_MEMORY_H_SEEN
#define FILE_MEMORY_H_SEEN


#define FLASHSECTORSIZE        1024
#define FLASHSECTORSIZEINWORDS  512 /* 512 words to a 1k flash sector */


/* Valid RPAGE values :
 *    0xFF - linear
 *    0xFE - linear
 *    0xFD - default
 *    0xFC
 *    0xFB
 *    0xFA
 *    0xF9
 *    0xF8
 */
/* The reset value of RPAGE is 0xFD               */
/* The other 8k of linear RAM space is accessible */
/* through the RPAGE window with 0xFE and 0xFF    */
/* 0xFE refers to the 0x2000 to 0x3000 region     */
/* 0xFF refers to the 0x3000 to 0x4000 region     */
#define RPAGE_TUNE_ONE    0xF8
#define RPAGE_XGATE    0xF9
#define RPAGE_FUEL_ONE    0xFA
#define RPAGE_FUEL_TWO    0xFB
#define RPAGE_TIME_ONE    0xFC
#define RPAGE_TIME_TWO    0xFD
#define RPAGE_LINEAR      0xFD
#define RPAGE_MIN         0xF8
#define PPAGE_MIN         0xE0
#define EPAGE_MIN         0x?? // TODO


/* http://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Variable-Attributes.html */

/* EEPROM */
//#define EEPROM __attribute__ ((section (".eeprom")))
/* EEPROM would appear to not be loadable by hcs12mem       */
/* Furthermore it isn't really needed except in code anyway */

/* RAM divided up into special purpose blocks */
#define RWINDOW __attribute__ ((section (".rpage"))) /* ~4k paged RAM window                 */
#define RXBUF   __attribute__ ((section (".rxbuf"))) /* ~1.5k block of RAM for receive buffer  */
#define TXBUF   __attribute__ ((section (".txbuf"))) /* ~2k block of RAM for transmit buffer */
// 4k of RAM for general variable and stack use, need to put some aside for xgate!!

/* Direct flash blocks */
#define CONFIG_DATA __attribute__ ((section (".configData")))  /* 2k unpaged configuration data */
#define TEXT1       __attribute__ ((section (".text1")))        /* 14k unpaged block, must be explicitly used.            */
#define TEXT        __attribute__ ((section (".text")))        /* 14k unpaged block, code defaults to being stored here. */
#define XG_SHARED   __attribute__ ((section (".xgshared")))    /* 0.5k unpaged block, shared RAM region */

/*define SERMON    __attribute__ ((section (".sermon")))         2k unpaged block, occupied by AN2548 serial monitor.  */


/* far shortcut for data */
/* SK - "far" data does not exist in the same sense as far text(trampoline jumps) and can be quite misleading to new guys.
 * TODO It should probably be removed or at the very least renamed, also see memory.x*/
#ifndef HOST_TESTS
  #define DFAR(label) __attribute__ ((section (label)))
  /* far shortcut for functions */
  #define FFAR(label) __attribute__ ((far)) __attribute__ ((section (label)))
#else
  #define DFAR(label) __attribute__ ((section (label)))
  /* far shortcut for functions */
  #define FFAR(label) __attribute__ ((section (label)))

#endif

/* Paged flash blocks for functions */
#define FPPAGE_E0X FFAR(".ppageE0X")
#define FPPAGE_E0S FFAR(".ppageE0S")
#define FPPAGE_E1 FFAR(".ppageE1")
#define FPPAGE_E2 FFAR(".ppageE2")
#define FPPAGE_E3 FFAR(".ppageE3")
#define FPPAGE_E4 FFAR(".ppageE4")
#define FPPAGE_E5 FFAR(".ppageE5")
#define FPPAGE_E6 FFAR(".ppageE6")
#define FPPAGE_E7 FFAR(".ppageE7")
#define FPPAGE_E8 FFAR(".ppageE8")
#define FPPAGE_E9 FFAR(".ppageE9")
#define FPPAGE_EA FFAR(".ppageEA")
#define FPPAGE_EB FFAR(".ppageEB")
#define FPPAGE_EC FFAR(".ppageEC")
#define FPPAGE_ED FFAR(".ppageED")
#define FPPAGE_EE FFAR(".ppageEE")
#define FPPAGE_EF FFAR(".ppageEF")
#define FPPAGE_F0 FFAR(".ppageF0")
#define FPPAGE_F1 FFAR(".ppageF1")
#define FPPAGE_F2 FFAR(".ppageF2")
#define FPPAGE_F3 FFAR(".ppageF3")
#define FPPAGE_F4 FFAR(".ppageF4")
#define FPPAGE_F5 FFAR(".ppageF5")
#define FPPAGE_F6 FFAR(".ppageF6")
#define FPPAGE_F7 FFAR(".ppageF7")

/* Paged flash blocks for data */
#define PPAGE_E0S DFAR(".ppageE0S")
#define PPAGE_E0X DFAR(".ppageE0X")
#define PPAGE_E1 DFAR(".ppageE1")
#define PPAGE_E2 DFAR(".ppageE2")
#define PPAGE_E3 DFAR(".ppageE3")
#define PPAGE_E4 DFAR(".ppageE4")
#define PPAGE_E5 DFAR(".ppageE5")
#define PPAGE_E6 DFAR(".ppageE6")
#define PPAGE_E7 DFAR(".ppageE7")
#define PPAGE_E8 DFAR(".ppageE8")
#define PPAGE_E9 DFAR(".ppageE9")
#define PPAGE_EA DFAR(".ppageEA")
#define PPAGE_EB DFAR(".ppageEB")
#define PPAGE_EC DFAR(".ppageEC")
#define PPAGE_ED DFAR(".ppageED")
#define PPAGE_EE DFAR(".ppageEE")
#define PPAGE_EF DFAR(".ppageEF")
#define PPAGE_F0 DFAR(".ppageF0")
#define PPAGE_F1 DFAR(".ppageF1")
#define PPAGE_F2 DFAR(".ppageF2")
#define PPAGE_F3 DFAR(".ppageF3")
#define PPAGE_F4 DFAR(".ppageF4")
#define PPAGE_F5 DFAR(".ppageF5")
#define PPAGE_F6 DFAR(".ppageF6")
#define PPAGE_F7 DFAR(".ppageF7")
/* Alternate name to use macro string concatenation */
#define PPAGE_0xE0S PPAGE_E0S
#define PPAGE_0xE0X PPAGE_E0X
#define PPAGE_0xE1 PPAGE_E1
#define PPAGE_0xE2 PPAGE_E2
#define PPAGE_0xE3 PPAGE_E3
#define PPAGE_0xE4 PPAGE_E4
#define PPAGE_0xE5 PPAGE_E5
#define PPAGE_0xE6 PPAGE_E6
#define PPAGE_0xE7 PPAGE_E7
#define PPAGE_0xE8 PPAGE_E8
#define PPAGE_0xE9 PPAGE_E9
#define PPAGE_0xEA PPAGE_EA
#define PPAGE_0xEB PPAGE_EB
#define PPAGE_0xEC PPAGE_EC
#define PPAGE_0xED PPAGE_ED
#define PPAGE_0xEE PPAGE_EE
#define PPAGE_0xEF PPAGE_EF
#define PPAGE_0xF0 PPAGE_F0
#define PPAGE_0xF1 PPAGE_F1
#define PPAGE_0xF2 PPAGE_F2
#define PPAGE_0xF3 PPAGE_F3
#define PPAGE_0xF4 PPAGE_F4
#define PPAGE_0xF5 PPAGE_F5
#define PPAGE_0xF6 PPAGE_F6
#define PPAGE_0xF7 PPAGE_F7

/* TODO move F7 to F8 until F8 is full, only here to prove that pages below F8 work fine */
#define FPAGE_F7 FFAR(".fpageF7")


/* General Purpose Page with PPAGE = 0xF8 */
#define FPAGE_F8 FFAR(".fpageF8")
#define DPAGE_F8 DFAR(".dpageF8")
#define PAGE_F8_PPAGE 0xF8

/* Function and large lookup tables for ADC to value mapping */
#define LOOKUPF FFAR(".fpageF9")
#define LOOKUPD DFAR(".dpageF9")
#define LOOKUP_PPAGE 0xF9

/* Fuel tables and the function for copying it up to RAM */
#define FUELTABLESF FFAR(".fpageFA")
#define FUELTABLESD DFAR(".dpageFA")
#define FUELTABLES_PPAGE 0xFA

/* Tunable tables etc and the function for copying them up to RAM */
#define TUNETABLESF FFAR(".fpageFB")
#define TUNETABLESD1 DFAR(".dpageFB1")
#define TUNETABLESD2 DFAR(".dpageFB2")
#define TUNETABLESD3 DFAR(".dpageFB3")
#define TUNETABLESD4 DFAR(".dpageFB4")
#define TUNETABLESD5 DFAR(".dpageFB5")
#define TUNETABLESD6 DFAR(".dpageFB6")
#define TUNETABLESD7 DFAR(".dpageFB7")
#define TUNETABLESD8 DFAR(".dpageFB8")
#define TUNETABLES_PPAGE 0xFB

/* Timing tables and the function for copying them up to RAM */
#define TIMETABLESF FFAR(".fpageFC")
#define TIMETABLESD DFAR(".dpageFC")
#define TIMETABLES_PPAGE 0xFC

/* General Purpose Page with PPAGE = 0xFE */
#define FPAGE_FE FFAR(".ppageFE") /* This is the block that is present in the page window using linear addressing, represents 0x8000 - 0xBFFF ("text2" paged) */
#define DPAGE_FE DFAR(".ppageFE") /* This is the block that is present in the page window using linear addressing, represents 0x8000 - 0xBFFF ("text2" paged) */
//#define FPAGE_FD FFAR(".ppageFD") /* Represents 0x4000 - 0x7FFF ("text1" paged) */
//#define DPAGE_FD DFAR(".ppageFD") /* Represents 0x4000 - 0x7FFF ("text1" paged) */
//#define FPAGE_FF FFAR(".ppageFF") /* Represents 0xC000 - 0xFFFF ("text" paged)  */
//#define DPAGE_FF DFAR(".ppageFF") /* Represents 0xC000 - 0xFFFF ("text" paged)  */
/* The previous four lines are included for clarity only. */
/* Changes to the memory layout should be reflected in memory.x and Makefile also */


/* Trick to get macro expansion to work right... */
#define TOKENPASTE(x,y) x ## y
#define TOKENPASTE2(x,y) TOKENPASTE(x,y)

/* Locations for the various descriptors and static string blocks */
/* coreVarsDescriptor */
#define CVD_STRUCT_BASE_PAGE 0xE6
#define CVD_STATIC_NAME_PAGE 0xEA
#define CVD_STATIC_DESC_PAGE 0xEA
#define CVD_STATIC_MISC_PAGE 0xEA

#define CVD_BASE_PAGE TOKENPASTE2(PPAGE_,CVD_STRUCT_BASE_PAGE)
#define CVD_NAME_PAGE TOKENPASTE2(PPAGE_,CVD_STATIC_NAME_PAGE)
#define CVD_DESC_PAGE TOKENPASTE2(PPAGE_,CVD_STATIC_DESC_PAGE)
#define CVD_MISC_PAGE TOKENPASTE2(PPAGE_,CVD_STATIC_MISC_PAGE)

/* derivedVarsDescriptor */
#define DVD_STRUCT_BASE_PAGE 0xE6
#define DVD_STATIC_NAME_PAGE 0xEA
#define DVD_STATIC_DESC_PAGE 0xEA
#define DVD_STATIC_MISC_PAGE 0xEA

#define DVD_BASE_PAGE TOKENPASTE2(PPAGE_,DVD_STRUCT_BASE_PAGE)
#define DVD_NAME_PAGE TOKENPASTE2(PPAGE_,DVD_STATIC_NAME_PAGE)
#define DVD_DESC_PAGE TOKENPASTE2(PPAGE_,DVD_STATIC_DESC_PAGE)
#define DVD_MISC_PAGE TOKENPASTE2(PPAGE_,DVD_STATIC_MISC_PAGE)

/* decoderStatsDescriptor */
#define DSD_STRUCT_BASE_PAGE 0xE6
#define DSD_STATIC_NAME_PAGE 0xEA
#define DSD_STATIC_DESC_PAGE 0xEA
#define DSD_STATIC_MISC_PAGE 0xEA

#define DSD_BASE_PAGE TOKENPASTE2(PPAGE_,DSD_STRUCT_BASE_PAGE)
#define DSD_NAME_PAGE TOKENPASTE2(PPAGE_,DSD_STATIC_NAME_PAGE)
#define DSD_DESC_PAGE TOKENPASTE2(PPAGE_,DSD_STATIC_DESC_PAGE)
#define DSD_MISC_PAGE TOKENPASTE2(PPAGE_,DSD_STATIC_MISC_PAGE)

/* fieldDescriptor */
#define FD_STRUCT_BASE_PAGE 0xE6
#define FD_STATIC_NAME_PAGE 0xEA
#define FD_STATIC_DESC_PAGE 0xEA
#define FD_STATIC_MISC_PAGE 0xEA

#define FD_BASE_PAGE TOKENPASTE2(PPAGE_,FD_STRUCT_BASE_PAGE)
#define FD_NAME_PAGE TOKENPASTE2(PPAGE_,FD_STATIC_NAME_PAGE)
#define FD_DESC_PAGE TOKENPASTE2(PPAGE_,FD_STATIC_DESC_PAGE)
#define FD_MISC_PAGE TOKENPASTE2(PPAGE_,FD_STATIC_MISC_PAGE)

/* generalPurposeInputsDescriptor */
#define GPID_STRUCT_BASE_PAGE 0xE6
#define GPID_STATIC_NAME_PAGE 0xEA
#define GPID_STATIC_DESC_PAGE 0xEA
#define GPID_STATIC_MISC_PAGE 0xEA

#define GPID_BASE_PAGE TOKENPASTE2(PPAGE_,GPID_STRUCT_BASE_PAGE)
#define GPID_NAME_PAGE TOKENPASTE2(PPAGE_,GPID_STATIC_NAME_PAGE)
#define GPID_DESC_PAGE TOKENPASTE2(PPAGE_,GPID_STATIC_DESC_PAGE)
#define GPID_MISC_PAGE TOKENPASTE2(PPAGE_,GPID_STATIC_MISC_PAGE)

/* keyUserVarsDescriptor */
#define KUVD_STRUCT_BASE_PAGE 0xE6
#define KUVD_STATIC_NAME_PAGE 0xEA
#define KUVD_STATIC_DESC_PAGE 0xEA
#define KUVD_STATIC_MISC_PAGE 0xEA

#define KUVD_BASE_PAGE TOKENPASTE2(PPAGE_,KUVD_STRUCT_BASE_PAGE)
#define KUVD_NAME_PAGE TOKENPASTE2(PPAGE_,KUVD_STATIC_NAME_PAGE)
#define KUVD_DESC_PAGE TOKENPASTE2(PPAGE_,KUVD_STATIC_DESC_PAGE)
#define KUVD_MISC_PAGE TOKENPASTE2(PPAGE_,KUVD_STATIC_MISC_PAGE)

/* tableDescriptor */
#define TD_STRUCT_BASE_PAGE 0xE6
#define TD_STATIC_NAME_PAGE 0xEA
#define TD_STATIC_DESC_PAGE 0xEA
#define TD_STATIC_MISC_PAGE 0xEA

#define TD_BASE_PAGE TOKENPASTE2(PPAGE_,TD_STRUCT_BASE_PAGE)
#define TD_NAME_PAGE TOKENPASTE2(PPAGE_,TD_STATIC_NAME_PAGE)
#define TD_DESC_PAGE TOKENPASTE2(PPAGE_,TD_STATIC_DESC_PAGE)
#define TD_MISC_PAGE TOKENPASTE2(PPAGE_,TD_STATIC_MISC_PAGE)


#else
  /* let us know if we are being untidy with headers */
//  #warning "Header file MEMORY_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
