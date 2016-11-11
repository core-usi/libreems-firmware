/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2013 Fred Cooke
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
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_INIT_DEPRICATED_H_SEEN
#define FILE_INIT_DEPRICATED_H_SEEN


/* Keep this non ISR stuff out of linear flash space */
void initPLL(void) FPAGE_FE;
void initADC(void) FPAGE_FE;
void initPWM(void) FPAGE_FE;
void initGPIO(void) FPAGE_FE;
void initAllPagedRAM(void) FPAGE_FE;
void initAllPagedAddresses(void) FPAGE_FE;
void initVariables(void) FPAGE_FE;
void initFlash(void) FPAGE_FE;
void initECTTimer(void) FPAGE_FE;
void initPITTimer(void) FPAGE_FE;
void initSCIStuff(void) FPAGE_FE;
void initConfiguration(void) FPAGE_FE;
void initInterrupts(void) FPAGE_FE;

// XGATE assembly symbols, only used for address/size
extern void xgateThread0(void);
extern void xgateThread0End(void);

/* Place these functions in the same block of flash as the data upon which they operate! */
void initLookupAddresses(void) LOOKUPF;
void initFuelAddresses(void) FUELTABLESF;
void initTimingAddresses(void) TIMETABLESF;
void initTunableAddresses(void) TUNETABLESF;
void initPagedRAMFuel(void) FUELTABLESF;
void initPagedRAMTime(void) TIMETABLESF;
void initPagedRAMTune(void) TUNETABLESF;


/* Other function declarations are private and present in the C     */
/* source file purely to assign them to a particular memory region. */
void enablePLL(void) FPAGE_FE; // Needed in self clock ISR


/* Various masks and values used for initialising the contents of control registers. */
/* For information on how these are being used, try this link :                      */
/* http://www.vipan.com/htdocs/bitwisehelp.html                                      */


// PLL control values
#define PLLSELOFF     0x7F /* Mask for switching to base external OSCCLK clock 0b_0111_1111 */
#define PLLOFF        0xBF /* Mask for turning the PLLON bit to ZERO 0b_1011_1111, IE, turning PLL off */
#define PLLDIVISOR    0x03 /* Input crystal frequency is divided by this number */
#define PLLMULTIPLIER 0x09 /* The result of the above is multiplied by this number to give the bus frequency */

// Flash control values
#define PRDIV8        0x40 /* Mask for flash module to divide the oscillator clock by 8 */


/// @todo TODO define other macros such that raw values aren't used in the code
/// @todo TODO move all the reg masks to a header of their own for general use.


/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
