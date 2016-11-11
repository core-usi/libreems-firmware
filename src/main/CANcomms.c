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

#include "inc/CANcomms.h"
#include "inc/9S12XDP512.h"
#include "inc/freeEMS.h"
#include "inc/commsCore.h"

extern KeyUserDebug KeyUserDebugs;
extern CoreVar      CoreVars_g;

/* Base pointers for each CAN module */
static const uint8_t *CANmodule[NUM_CAN_MODULES] = {
    (const uint8_t*)&CAN0CTL0,
    (const uint8_t*)&CAN1CTL0,
    (const uint8_t*)&CAN2CTL0,
    (const uint8_t*)&CAN3CTL0,
    (const uint8_t*)&CAN4CTL0
};

void initCAN(uint8_t CANmoduleIndex, uint8_t CANbtr0, uint8_t CANbtr1, uint8_t loopBack) {
  CANregisterSet *CAN;

  CAN = (CANregisterSet*) (CANmodule[CANmoduleIndex]); /*lookup base address of CAN module*/

  if (loopBack) {
    loopBack = CAN0CTL1_LOOPB_MASK;
  }

    if (!KeyUserDebugs.canStatus.setINITTAKfirst) {
      CAN->CTL0 = CAN0CTL0_INITRQ_MASK;
      KeyUserDebugs.canStatus.setINITTAKfirst = 1;
    }

  if (!KeyUserDebugs.canStatus.INITAKfirst) {
      if (!(CAN->CTL1 & CAN0CTL1_INITAK_MASK)) {
        return;
      } else {
        KeyUserDebugs.canStatus.INITAKfirst = 1;
      }
  }

  if (!KeyUserDebugs.canStatus.setINITTAKSecond) {
    CAN->CTL1 = 0x80 | loopBack;  // Enables MSCAN, Oscillator Clock, Loop Enabled/Disabled and Normal Operation
    CAN->BTR0 = CANbtr0;          // See spreadsheet
    CAN->BTR1 = CANbtr1;          // ditto

    CAN->IDMR0 = CAN->IDMR1 = CAN->IDMR2 = CAN->IDMR3 = 0xFF;
    CAN->IDMR4 = CAN->IDMR5 = CAN->IDMR6 = CAN->IDMR7 = 0xFF;

    CAN->CTL0 = 0x00;
    KeyUserDebugs.canStatus.setINITTAKSecond = 1;
  }
  // restarts MSCAN module
  if (!KeyUserDebugs.canStatus.INITAKsecond) {
    // wait for Initialization mode to complete
    if (CAN->CTL1 & CAN0CTL1_INITAK_MASK) {
      return;
    } else {
      KeyUserDebugs.canStatus.INITAKsecond = 1;
    }
  }
    /* Wait for sync */
  if (!KeyUserDebugs.canStatus.synced) {
    if (!(CAN->CTL0 & CAN0CTL0_SYNCH_MASK)) {
      return;
    } else {
      KeyUserDebugs.canStatus.synced = 1;
    }
  }

  CAN->RFLG = 0xC3; /*04*/
  CAN->RIER = 0x01; /*05*/
}

uint8_t sendCANmessage(uint8_t CANmoduleIndex, CANmessage *message) {
  uint8_t maxTries = 20;

  CANregisterSet *CAN;
  uint8_t TXbufEmpty = 0;

  // get base adders of the CAN channel
  CAN = (CANregisterSet*) (CANmodule[CANmoduleIndex]);

  if (!(CAN->CTL0 & CAN0CTL0_SYNCH_MASK)) {
    return 0;
  }

  // find empty transmit buffer from 3 buffers
  // TODO(skeys) potentially add max retry
  while (!(CAN->TFLG & (0x01 << TXbufEmpty))) {
    ++TXbufEmpty;
    --maxTries;
    if (TXbufEmpty == 3) {
      TXbufEmpty = 0;
    }
    if(!maxTries) {
      return 0;
    }
  }
  // select the empty transmit buffer
  CAN->TBSEL = (0x01 << TXbufEmpty);

    /* Load Id to IDR Registers */
    //*((uint32_t *)&CAN->TXIDR0)= message->id; this assumes a pre-formatted ID
  //TODO(seys) create code to handle extended IDs OTF

  //CAN->TXIDR0 = (uint8_t)(message->id >> 3);  // insert ID MSB
  //CAN->TXIDR1 = (uint8_t)(message->id << 5);  // insert last 3 bits of ID to the msb

CAN->TXIDR0 = (uint8_t)(message->id >> 8);  // insert ID MSB
CAN->TXIDR1 = (uint8_t)(message->id);  // insert last 3 bits of ID to the msb


  if (message->RTR) {
    CAN->TXIDR1 |= 0x10;
  }

  uint8_t i;
  for (i = 0; i < message->length; ++i) {
    CAN->TXDSR[i] = message->data[i];
  }

  CAN->TXDLR = message->length; // set message data length
  CAN->TXTBPR = message->prty;  // set message internal priority

  CAN->TFLG = (0x01 << TXbufEmpty);   // clear flag to send message

  return 1;
}

#include "inc/xgate.h"

void sendDispayData() {

  CANmessage msg;
  /* Send Time */
  uint8_t page = RPAGE;
  RPAGE = RPAGE_XGATE;
  uint16_t id = *((uint16_t*)(START_OF_RAM_WINDOW + XGATE_TEXT_ALLOCATION_SIZE + 6));
  msg.id = id;
  RPAGE = page;

  //msg.id = 0x101;

  msg.RTR = 0;
  msg.length = 4;
  msg.prty = 0;
  *((uint32_t*)&msg.data) =  Clocks.milliSecondTotal;
  sendCANmessage(0, &msg);



//  /* Send TPS */
//  msg.id = 0x102;
//  msg.RTR = 0;
//  msg.length = 2;
//  msg.prty = 0;
//  *((uint16_t*)&msg.data) =  CoreVars_g.TPS;
//  sendCANmessage(0, &msg);
//
//  /* Send MAP */
//  msg.id = 0x103;
//  msg.RTR = 0;
//  msg.length = 2;
//  msg.prty = 0;
//  *((uint16_t*)&msg.data) =  CoreVars_g.MAP;
//  sendCANmessage(0, &msg);
//
//  /* Send MAP */
//  msg.id = 0x104;
//  msg.RTR = 0;
//  msg.length = 2;
//  msg.prty = 0;
//  *((uint16_t*)&msg.data) =  CoreVars_g.RPM;
//  sendCANmessage(0, &msg);

}

/* Init code from app note that shows filtering etc */
//    CAN0CTL0 = 0x01;          /* Enter Initialization Mode
//                               *
//                               *  0b00000001
//                               *    ||||||||__ Enter Initialization Mode
//                               *    |||||||___ Sleep Mode Request bit
//                               *    ||||||____ Wake-Up disabled
//                               *    |||||_____ Time stamping disabled
//                               *    ||||______ Synchronized Status
//                               *    |||_______ CAN not affected by Wait
//                               *    ||________ Receiver Active Status bit
//                               *    |_________ Received Frame Flag bit
//                               */
//
//    while (!(CAN0CTL1&0x01)){}; /* Wait for Initialization Mode acknowledge
//                                 * INITRQ bit = 1
//                                 */
//
//    CAN0CTL1 = 0xA0;          /* Enable MSCAN module and LoopBack Mode
//                               *
//                               *  0b10100000
//                               *    ||||||||__ Initialization Mode Acknowledge
//                               *    |||||||___ Sleep Mode Acknowledge
//                               *    ||||||____ Wake-up low-pass filter disabled
//                               *    |||||_____ Unimplemented
//                               *    ||||______ Listen Only Mode disabled
//                               *    |||_______ Loop Back Mode enabled
//                               *    ||________ Ext Osc/Xtal as Clock Source
//                               *    |_________ MSCAN Module enabled
//                               */
//
//    CAN0BTR0 = 0xC7;          /* Synch Jump = 3 Tq clock Cycles
//                               *
//                               *  0b11000111
//                               *    ||||||||__
//                               *    |||||||___
//                               *    ||||||____ |
//                               *    |||||_____ |_ CAN Clock Prescaler = 7
//                               *    ||||______ |
//                               *    |||_______ |
//                               *    ||________/
//                               *    |_________>- SJW = 3
//                               */
//
//    CAN0BTR1 = 0x3A;        /* Set Number of samples per bit, TSEG1 and TSEG2
//                               *
//                               *  0b00111010
//                               *    ||||||||__
//                               *    |||||||___|
//                               *    ||||||____|- TSEG1 = 10
//                               *    |||||_____|
//                               *    ||||______
//                               *    |||_______\_ TSEG2 = 3
//                               *    ||________/
//                               *    |_________ One sample per bit
//                               */
//
//    CAN0IDAC = 0x10;          /* Set four 16-bit Filters
//                               *
//                               *  0b00010000
//                               *    ||||||||__
//                               *    |||||||___\_ Filter Hit Indicator
//                               *    ||||||____/
//                               *    |||||_____ Unimplemented
//                               *    ||||______
//                               *    |||_______>- Four 16-bit Acceptance Filters
//                               *    ||________
//                               *    |_________>- Unimplemented
//                               */
//
//    /* Acceptance Filters */
//    CAN0IDAR0 = ACC_CODE_ID100_HIGH;    //|\    16 bit Filter 0
//    CAN0IDMR0 = MASK_CODE_ST_ID_HIGH;   //| \__ Accepts Standard Data Frame Msg
//    CAN0IDAR1 = ACC_CODE_ID100_LOW;     //| /   with ID 0x100
//    CAN0IDMR1 = MASK_CODE_ST_ID_LOW;    //|/
//
//    CAN0IDAC  = 0x10;                   /* Set four 16-bit Filters */
//
//    CAN0IDAR2 = 0x00;                   //|\    16 bit Filter 1
//    CAN0IDMR2 = MASK_CODE_ST_ID_HIGH;   //| \__ Accepts Standard Data Frame Msg
//    CAN0IDAR3 = 0x00;                   //| /   with ID 0x000
//    CAN0IDMR3 = MASK_CODE_ST_ID_LOW;    //|/
//
//    CAN0IDAR4 = 0x00;                   //|\    16 bit Filter 2
//    CAN0IDMR4 = MASK_CODE_ST_ID_HIGH;   //| \__ Accepts Standard Data Frame Msg
//    CAN0IDAR5 = 0x00;                   //| /   with ID 0x000
//    CAN0IDMR5 = MASK_CODE_ST_ID_LOW;    //|/
//
//    CAN0IDAR6 = 0x00;                   //|\    16 bit Filter 3
//    CAN0IDMR6 = MASK_CODE_ST_ID_HIGH;   //| \__ Accepts Standard Data Frame Msg
//    CAN0IDAR7 = 0x00;                   //| /   with ID 0x000
//    CAN0IDMR7 = MASK_CODE_ST_ID_LOW;    //|/
//
//    CAN0CTL0 = 0x00;            /* Exit Initialization Mode Request */
//    while ((CAN0CTL1&0x01) != 0){}; /* Wait for Normal Mode */
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
