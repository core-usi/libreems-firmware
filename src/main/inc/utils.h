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
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_UTILS_H_SEEN
#define FILE_UTILS_H_SEEN


uint16_t safeAdd(uint16_t, uint16_t);
uint16_t safeSubtract(uint16_t, uint16_t);
uint16_t safeTrim(uint16_t, int16_t);
uint16_t safeScale(uint16_t, uint16_t, uint16_t);

void sleep(uint16_t) FPAGE_FE;
void sleepMicro(uint16_t) FPAGE_FE;

void adjustPWM(void) FPAGE_FE;
void setupPagedRAM(uint8_t) FPAGE_F8;

void sampleEachADC(ADCBuffer*) FPAGE_F8;
void sampleLoopADC(ADCBuffer*) FPAGE_F8;
//void sampleBlockADC(ADCBuffer*) FPAGE_F8; broken, do not use

uint8_t checksum(uint8_t *, uint16_t) FPAGE_F8;
uint16_t stringCopy(uint8_t*, uint8_t*) FPAGE_F8;
uint16_t compare(uint8_t*, uint8_t*, uint16_t); // In unpaged flash as it needs to compare paged flash with unpaged things
void* mset(void*, int, uint16_t);

/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
