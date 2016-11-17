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
 * @ingroup CAN communications
 */

#include "inc/canISRs.h"
#include "inc/globals.h"
#include "inc/freeEMS.h"

extern KeyUserDebug KeyUserDebugs;

void CAN0RxISR(void) {

  uint8_t length = (CAN0RXDLR & 0x0F);
  uint8_t data;
  uint8_t i;

  ++KeyUserDebugs.CANframesRx;

  //CANregisterSet *CAN = (CANregisterSet*)&CAN0CTL0;
  //KeyUserDebugs.CANbytesRx = ((uint16_t)(CAN->RXIDR0 << 3) & 0x0700) | ((uint8_t)CAN->RXIDR0 << 3) | (uint8_t)(CAN->RXIDR1 >> 5);

  /* Get received data */
  for (i = 0; i < length; ++i) {
    data = *(&CAN0RXDSR0 + i);
    ++KeyUserDebugs.CANbytesRx;
  }

  CAN0RFLG = 0x01; /* Clear RXF */

}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
