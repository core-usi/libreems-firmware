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
 * @ingroup data calculation
 */

#include "inc/dataAcquisitionISRs.h"
#include "inc/globalDefines.h"
#include "inc/9S12XDP512.h"
#include "inc/globals.h"
#include "engineAngleDecoders/common/interface.h"
#include "inc/Configuration.h"


#define CAPTURE_DATA(CH)                                       \
  static ExtendedTime savedStamp;                              \
  ExtendedTime timeStamp;                                      \
  timeStamp.timeWord[1] = TC##CH;                              \
                                                               \
  if (TFLG2 && !(TC##CH & 0x8000)) {                           \
    timeStamp.timeWord[0] = timerExtensionCounter_g + 1;       \
  } else {                                                     \
    timeStamp.timeWord[0] = timerExtensionCounter_g;           \
  }                                                            \
                                                               \
  uint8_t isPinHigh = PTIT & (1 << CH);                        \
  /* TODO add config for polarity setting */                   \
  updateCapturedInput(isPinHigh, &capturedInputData_g[TC##CH##_DATA_INDEX], &savedStamp, &timeStamp); \
  savedStamp.time = timeStamp.time;                            \
  TFLG1 = (1 << CH);    /* Clear Interrupt Last */

/*
 * General purpose capture channels
 */
void gpCapture7() {
  CAPTURE_DATA(7)
}

void gpCapture6() {
  CAPTURE_DATA(6)
}

void gpCapture5() {
  CAPTURE_DATA(5)
}

void gpCapture3() {
  CAPTURE_DATA(3)
}

void gpCapture2() {
  CAPTURE_DATA(2)
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
