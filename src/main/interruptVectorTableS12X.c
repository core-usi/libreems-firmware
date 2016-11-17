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
 * @ingroup TODO
 *
 * @brief TODO
 *
 *
 */

#include "inc/freeEMS.h"
#include "inc/dataAcquisitionISRs.h"
#include "inc/canISRs.h"
#include "engineAngleDecoders/common/interface.h"
#include "inc/interrupts_depricated.h"

/* The linker puts the table in flash at the correct address(0xFF10), expected by
 * the interrupt base address register. */

const interruptFunction _vectors[] VECTORS = {

  SpuriousISR,  /* Spurious */
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  UISR,
  RAMViolationISR,  /* RAM violation */
  XGATEErrorISR,    /* XGATE software error */
  UISR,             /* XGATE7 */
  UISR,             /* XGATE6 */
  UISR,             /* XGATE5 */
  UISR,             /* XGATE4 */
  UISR,             /* XGATE3 */
  UISR,             /* XGATE2 */
  UISR,             /* XGATE1 */
  UISR,             /* XGATE0 */
  UISR,             /* PIT3 */
  UISR,             /* PIT2 */
  UISR,             /* PIT1 */
  UISR,             /* PIT0 */
  UISR,             /* Reseved */
  UISR,
  LowVoltageISR,
  UISR,             /* IIC1 */
  UISR,             /* SCI5 */
  UISR,             /* SCI4 */
  UISR,             /* SCI3 */
  UISR,             /* SCI2 */
  UISR,             /* PWM */
  PortPISR,
  UISR,             /* CAN4 TX */
  UISR,             /* CAN4 RX */
  UISR,             /* CAN4 Error */
  UISR,             /* CAN4 Wake */
  UISR,             /* CAN3 TX */
  UISR,             /* CAN3 RX */
  UISR,             /* CAN3 Error */
  UISR,             /* CAN3 Wake */
  UISR,             /* CAN2 TX */
  UISR,             /* CAN2 RX */
  UISR,             /* CAN2 Error */
  UISR,             /* CAN2 Wake */
  UISR,             /* CAN1 TX */
  UISR,             /* CAN1 RX */
  UISR,             /* CAN1 Error */
  UISR,             /* CAN1 Wake */
  UISR,             /* CAN0 TX */
  CAN0RxISR,        /* CAN0 RX */
  UISR,             /* CAN0 Error*/
  UISR,             /* CAN0 Wake */
  UISR,             /* Flash */
  UISR,             /* EEPROM */
  UISR,             /* SPI2 */
  UISR,             /* SPI1 */
  UISR,             /* IIC0 */
  UISR,
  SelfClockISR,     /* CRG self-clock */
  PLLLockISR,       /* CRG PLL lock */
  UISR,             /* PAB over flow */
  UISR,             /* Down counter */
  PortHISR,         /* Port H */
  PortJISR,         /* Port J */
  UISR,             /* ATD1 */
  UISR,             /* ATD0 */
  UISR,             /* SCI1 */
  SCI0ISR,          /* SCI0 */
  UISR,             /* SPI0 */
  UISR,             /* PAIE */
  pulseAccumulatorOverflowISR,             /* PAA over flow */
  TimerOverflow,    /* ECT Timer over flow */
  gpCapture7,       /* ECT7 */
  gpCapture6,       /* ECT6 */
  gpCapture5,       /* ECT5 */
  UISR,             /* RESERVED FOR XGATE OUTPUTS */
  gpCapture3,       /* ECT3 */
  gpCapture2,       /* ECT2 */
  SecondaryEngineAngle,  /* ECT1 */
  PrimaryEngineAngle,    /* ECT0 */
  RTIISR,           /* RTI */
  IRQISR,           /* IRQ */
  XIRQISR,          /* XIRQ */
  UISR,             /* SWI */
  UnimplOpcodeISR,  /* unimplimented op-code */
  _start,           /* COP reset */
  _start,           /* Clock reset */
  _start            /* CPU reset */
};
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
