/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2015 Sean Keys
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


/** @file
 *
 * @ingroup Configuration
 *
 */

#ifndef SRC_MAIN_ENGINEANGLEDECODERS_COMMON_INTERFACE_H_
#define SRC_MAIN_ENGINEANGLEDECODERS_COMMON_INTERFACE_H_

#include <stdint.h>

#include "../../inc/dataAcquisition.h"
#include "../../inc/mathFunctions.h"
#include "../../inc/libreTypes.h"
#include "../../inc/outputPlotter.h"
#include "../../inc/Configuration.h"
#include "../../inc/interrupts.h"
#include "../../inc/libreDefs.h"
#include "../../inc/shared/libreExternalTypes.h"
#include "../../inc/xgate.h"


extern const    uint16_t     inputAngles[];
extern const    uint8_t      maxInputAngleIndex;
extern          DecoderStats decoderStats_g;
extern volatile uint16_t     timerExtensionCounter_g;

DecoderStats* getDecoderStats();
void resetDecoderStatus(uint8_t reasonCode) TEXT;
void decoderSpecificInit()                  TEXT;
void decoderReset()                         TEXT;
uint16_t getInstantAngle(void)              TEXT1;


void SecondaryEngineAngle(void)        ISR TEXT;
void PrimaryEngineAngle(void)          ISR TEXT;
void pulseAccumulatorOverflowISR(void) ISR TEXT;

extern DecoderStats decoderStats_g;
extern const uint8_t decoderName[];

DecoderStats decoderStats_g;


#endif /* SRC_MAIN_ENGINEANGLEDECODERS_COMMON_INTERFACE_H_ */
