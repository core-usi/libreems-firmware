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


/** @file
 *
 * @brief
 *
/* @defgroup xgateThread included */

/**
 * @cond DOXYGEN_IGNORE_ASM
*/


.global swISR0
.global TC4ISR
.global startXGATECode
.global XGoutputEvents ;starting address of output events
.global xgateTOFISR
.global timerExtensionClockShared
.global PIT0

.global XGEventCountOpCode
.type	XGEventCountOpCode, @object
.size   XGEventCountOpCode, 2

.equ numEvents,  48

.equ PIT0_CFLAG_MASK, 1
.equ LATE_OFLOW, 0x40
.equ WFTOF_FLAG_COM, 0xDF
.equ WFTOF_FLAG, 0x20
.equ GO_LOW_BIT, (1 << 4)
.equ GO_HIGH_BIT, (1 << 3)
.equ BIT2_COM, 0xFB
.equ BIT2, (1 << 2)
.equ COCKED_FLAG, (1 << 0)


.equ TIE_REG,  0x004C
;.equ TC2_REG, 0x54
.equ TC4_REG, 0x0058
.equ TFLG2, 0x4F
.equ TFLG_REG, 0x004E /* Timer channel flags */
.equ TCNT_REG, 0x0044 /* Timer counter */
.equ SW_ISR_FLAG_REG, 0x0398 /* XG software interrupt register */
.equ SW_ISR_ZERO_CFLAG_MASK, 0x0100
.equ PITTF,  0x0345     /* PIT ISR Register, low 4 bits set when each counter reaches 0 */
.equ PITLD0, 0x0348   /* Down counter register, loaded when the counter reaches */


.equ sizeOfEventStruct, 10
;typedef struct {
;	uint8_t actionBits;
;	uint8_t regMask;
;	uint16_t regAddress;
;	counter32 OCReg;          /* software register containing an OC value */
;   uint16_t lastRunStamp;
;} outputAction;

/**
* @endcond DOXYGEN_IGNORE_ASM
*/
