/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014-2015 Sean Keys
 *
 * This file is part of the LibreEMS project.
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
 * along with any LibreEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * Thank you for choosing LibreEMS to run your engine!
 */


/** @file
 *
 * @ingroup allHeaders
 */

#ifndef FILE_INIT_H_SEEN
#define FILE_INIT_H_SEEN

#include "Configuration.h"

#define XG_SHMEM_OFFSET     0xC000  /* Used to negate the automatic linker offsets */
#define XG_IMM8_REG(reg)    (reg << 8)  /* Xgate register 3 operand in IMM8 mode */

void initializeXGateOutputs(XGateOutputCHpinMapping *pinMapping) FPAGE_FE;
void init(void) FPAGE_FE;
void initPIT(void) FPAGE_FE;
void initXgate(uint8_t numChannels) TEXT1;
void primeInjectors(uint16_t pulseWidth) TEXT;
void initECTchannels(InputCaptureSettings *settings) TEXT1;
void initGPIOregisters(GPIOchannel *GPIOchannels) TEXT1;
void initIAC(IdleControl *controlInfo) TEXT1;
void initXGateData(void) TEXT1;
void initMisc(MasterConfig *config) TEXT;

/* Assembly labels */
extern void *XGEventCountOpCode;

/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
