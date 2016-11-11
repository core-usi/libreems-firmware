/*
 * CANcomms.h
 *
 *  Created on: Aug 9, 2015
 *      Author: seank
 */

#ifndef SRC_INC_CANCOMMS_H_
#define SRC_INC_CANCOMMS_H_

#include "9S12X_CAN_REGS.h"
#include "memory.h"


typedef struct {
  uint32_t id;
  uint8_t  RTR;
  uint8_t  data[MAX_CAN_BYTES];
  uint8_t  length;
  uint8_t  prty;
}CANmessage;

void initCAN(uint8_t, uint8_t, uint8_t, uint8_t) TEXT;  //TODO(skeys) move to paged flash
uint8_t sendCANmessage(uint8_t, CANmessage*) FPPAGE_E6;
void sendDispayData() FPPAGE_E6;

#endif /* SRC_MAIN_INC_CANCOMMS_H_ */
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
