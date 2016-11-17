/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014 Sean Keys
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
 
 
/*	FreeEMS - the open source engine management system

	Copyright 2008, 2009 Fred Cooke
	
	This file is part of the FreeEMS project.

	FreeEMS software is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeEMS software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


/** @file
 *
 * @brief Region definition linker script
 *
 * Memory region location definition file for inclusion into the linker
 * script. It defines the names, types, start addresses and lengths of
 * each memory region available for the linker to populate with code and
 * data. See hc9s12xdp512elfb.x and regions.x for more information. 
 *
 * A description of what some of this means can be found at the following URLs:
 * - http://www.gnu.org/software/m68hc11/m68hc11_binutils.html
 * - http://m68hc11.serveftp.org/wiki/index.php/FAQ:Link
 *
 * @cond memoryscript
 */


  MEMORY
  {
/*	regs		(r) 	: ORIGIN = 0x0000, LENGTH = 0x0800 /*	2k register space DON'T use! */
	eeprom		(r) 	: ORIGIN = 0x0800, LENGTH = 0x0800 /*	2K of eeprom for now, 4K requires paging */

 /* The ram in the global space is mapped to 0x2000 in the 16-bit address space for S12 and 0xE000 in the 16-bit address space
	for XGATE.  */

	/* RAM space split up for tuning and flash burning use as well as GP use */
	rpage		(rw)	: ORIGIN = 0x1000, LENGTH = 0x1000 /*   4k WINDOW for large tables etc */
	xgshared    (rw)    : ORIGIN = 0x2000, LENGTH = 0x0300 /*   512 Byte shared memory region */
	txbuf		(rw)	: ORIGIN = 0x2300, LENGTH = 0x0520 /*  ~1.25k FIXED transmission buffer */
	rxbuf		(rw)	: ORIGIN = 0x2820, LENGTH = 0x0810 /*  ~2k FIXED reception buffer */
	data		(rw)	: ORIGIN = 0x3030, LENGTH = 0x0FD0 /*  ~4k FIXED general purpose RAM */
	/* The TX and RX buffers are slightly larger than 2k because the RX buffer */
	/* needs to also receive a header, checksum and attributes for the data    */
	/* involved and the TX buffer needs to handle all of those two fold.       */
/**/
	/* Flash space in linear space while using the page window (16k + 14k + 2k SM = 30k usable, 2k protected) */
	text1		(rx)	: ORIGIN = 0x4000, LENGTH = 0x3800 /*	Unpaged 14k flash block before page window	*/
	configData 	(rx)	: ORIGIN = 0x7800, LENGTH = 0x0800 /*	2K unpaged configuration data */
	/*ppaged	(rx)	: ORIGIN = 0x8000, LENGTH = 0x4000		16K flash page window, DO NOT USE */
	text		(rx)	: ORIGIN = 0xC000, LENGTH = 0x3710 /*	Unpaged 14K flash block after page window minus serial monitor and vector space */
	/* TODO split the above text and text1 regions into halves or similar to allow us to know how the linear space is being spent, eg perf/required/isr etc */

	/* --------------------- NOTE ------------------------------------ */
	/* SK 3-15-14 "correct" is dependant on what you are trying to do. */
	/* The correct value is how the code will look to the selected CPU */
	/* when the code is run or called. See notes for sections below.   */
	/* TODO - Determine if the lower 16-bits of the VMA should always  */
	/* be at the start of the flash/eeprom page, UNELSS you are running*/
	/* Xgate code. */
	
/* These are the values defined inside the linker code:
   #define M68HC12_BANK_VIRT       0x010000
   #define M68HC12_BANK_MASK     0x00003fff
   #define M68HC12_BANK_BASE     0x00008000
   #define M68HC12_BANK_SHIFT            14
   #define M68HC12_BANK_PAGE_MASK     0x0ff */
   
   /* !!!!!!!!!!!!!! WARNING !!!!!!!!!!!!!!!!!!!!!!!!!
      it seems as though you can't change the VMA of paged
      sections. If you wish to use the address of data in a
      paged section of flash you need to make sure you pick
      a page with an origin address that ends in 0x8000.
      TODO figure out how to change VMA  */
   	
	/* These are correct as of the 0.0.17 release */
    /* TODO fix all of these */
    ppageE0S	(rx)	: ORIGIN = 0x390000, LENGTH = 0x0800
    ppageE0X	(rx)	: ORIGIN = 0x390800, LENGTH = 0x3800 
    ppageE1	(rx)	: ORIGIN =   0x9000, LENGTH = 0x0200 /* From S12 we move code from ppageE1 into this address via RPAGE2*/
 /*   ppageE1S	(rx)	: ORIGIN =   0x9000, LENGTH = 0x0400 */ 
    
    ppageE2	(rx)	: ORIGIN = 0x398000, LENGTH = 0x4000
    ppageE3	(rx)	: ORIGIN = 0x39C000, LENGTH = 0x4000
    ppageE4	(rx)	: ORIGIN = 0x3A0000, LENGTH = 0x4000
    ppageE5	(rx)	: ORIGIN = 0x3A4000, LENGTH = 0x4000 /* When we manually flip to page E5, the VMA needs to be at the start of the page window 0x8000 */
    ppageE6	(rx)	: ORIGIN = 0x3A8000, LENGTH = 0x4000
    ppageE7	(rx)	: ORIGIN = 0x3AC000, LENGTH = 0x4000
    ppageE8	(rx)	: ORIGIN = 0x3B0000, LENGTH = 0x4000
    ppageE9	(rx)	: ORIGIN = 0x3B4000, LENGTH = 0x4000
    ppageEA	(rx)	: ORIGIN = 0x3B8000, LENGTH = 0x4000
    ppageEB	(rx)	: ORIGIN = 0x3BC000, LENGTH = 0x4000
    ppageEC	(rx)	: ORIGIN = 0x3C0000, LENGTH = 0x4000
    ppageED	(rx)	: ORIGIN = 0x3C4000, LENGTH = 0x4000
    ppageEE	(rx)	: ORIGIN = 0x3C8000, LENGTH = 0x4000
    ppageEF	(rx)	: ORIGIN = 0x3CC000, LENGTH = 0x4000
    ppageF0	(rx)	: ORIGIN = 0x3D0000, LENGTH = 0x4000
    ppageF1	(rx)	: ORIGIN = 0x3D4000, LENGTH = 0x4000
    ppageF2	(rx)	: ORIGIN = 0x3D8000, LENGTH = 0x4000
    ppageF3	(rx)	: ORIGIN = 0x3DC000, LENGTH = 0x4000
    ppageF4	(rx)	: ORIGIN = 0x3E0000, LENGTH = 0x4000
    ppageF5	(rx)	: ORIGIN = 0x3E4000, LENGTH = 0x4000
    ppageF6	(rx)	: ORIGIN = 0x3E8000, LENGTH = 0x4000
    ppageF7	(rx)	: ORIGIN = 0x3EC000, LENGTH = 0x4000
    ppageF8	(rx)	: ORIGIN = 0x3F0000, LENGTH = 0x4000
    fpageF9	(rx)	: ORIGIN = 0x3F4000, LENGTH = 0x2000
    dpageF9	(rx)	: ORIGIN = 0x3F6000, LENGTH = 0x2000
    fpageFA	(rx)	: ORIGIN = 0x3F8000, LENGTH = 0x2000
    dpageFA	(rx)	: ORIGIN = 0x3FA000, LENGTH = 0x2000
    fpageFB	(rx)	: ORIGIN = 0x3FC000, LENGTH = 0x2000
    dpageFB1	(rx)	: ORIGIN = 0x3FE000, LENGTH = 0x0400      /* 0x3F E000, VMA is only correct because of a call to memcpy against SmallTablesAFlashV */
    dpageFB2	(rx)	: ORIGIN = 0x3FE400, LENGTH = 0x0400
    dpageFB3	(rx)	: ORIGIN = 0x3FE800, LENGTH = 0x0400
    dpageFB4	(rx)	: ORIGIN = 0x3FEC00, LENGTH = 0x0400
    dpageFB5	(rx)	: ORIGIN = 0x3FF000, LENGTH = 0x0400
    dpageFB6	(rx)	: ORIGIN = 0x3FF400, LENGTH = 0x0400
    dpageFB7	(rx)	: ORIGIN = 0x3FF800, LENGTH = 0x0400
    dpageFB8	(rx)	: ORIGIN = 0x3FFC00, LENGTH = 0x0400
    fpageFC	(rx)	: ORIGIN = 0x400000, LENGTH = 0x2000
    dpageFC	(rx)	: ORIGIN = 0x402000, LENGTH = 0x2000
    ppageFE	(rx)	: ORIGIN = 0x408000, LENGTH = 0x4000 /* Represents 0x8000 - 0xC000 ("text2" paged) */
/*  ppageFD	(rx)	: ORIGIN = 0x404000, LENGTH = 0x4000 ** Represents 0x4000 - 0x8000 ("text1" paged) */
/*  ppageFF	(rx)	: ORIGIN = 0x40C000, LENGTH = 0x3710 ** Represents 0xC000 - 0xFFFF ("text" paged) */
/*  The previous two lines are included for clarity only. */
/*	Changes to this file should be reflected in memory.h and Makefile also */
  }

  PROVIDE (_stack = 0x4000-1); /* Start the stack immediately after RAM */
  /* Vectors are located via the linker command line, not here. */
  PROVIDE (serialMonitor = 0xF82F);


/** @endcond */
