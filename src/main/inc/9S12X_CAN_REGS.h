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

#ifndef SRC_INC_9S12X_CAN_REGS_H_
#define SRC_INC_9S12X_CAN_REGS_H_

#include <stdint.h>

#include "9S12X_REG_NOMENCLATURE.h"

#define NUM_CAN_MODULES        5  //TODO(skeys) may depend on pin count
#define MAX_CAN_BYTES          8

#define CAN0CTL1_INITAK_MASK            1
#define CAN0CTL1_SLPAK_MASK             2
#define CAN0CTL1_WUPM_MASK              4
#define CAN0CTL1_BORM_MASK              8
#define CAN0CTL1_LISTEN_MASK            16
#define CAN0CTL1_LOOPB_MASK             32
#define CAN0CTL1_CLKSRC_MASK            64
#define CAN0CTL1_CANE_MASK              128

#define CAN0CTL0_INITRQ_MASK            1
#define CAN0CTL0_SLPRQ_MASK             2
#define CAN0CTL0_WUPE_MASK              4
#define CAN0CTL0_TIME_MASK              8
#define CAN0CTL0_SYNCH_MASK             16
#define CAN0CTL0_CSWAI_MASK             32
#define CAN0CTL0_RXACT_MASK             64
#define CAN0CTL0_RXFRM_MASK             128

/* Base addresses for each module */
#define CAN0CTL0 REG_DATA_8BIT(0x0140)
#define CAN1CTL0 REG_DATA_8BIT(0x0180)
#define CAN2CTL0 REG_DATA_8BIT(0x01C0)
#define CAN3CTL0 REG_DATA_8BIT(0x0200)
#define CAN4CTL0 REG_DATA_8BIT(0x0280)

#define CAN0_BASE_ADDRESS   0x0140
#define CAN0RXDSR0 REG_DATA_8BIT(CAN0_BASE_ADDRESS + 0x24)
#define CAN0RXDLR  REG_DATA_8BIT(CAN0_BASE_ADDRESS + 0x2C)
#define CAN0RFLG   REG_DATA_8BIT(0x0144)


#define CAN0BTR0 REG_DATA_8BIT(0x0142)
#define CAN0BTR1 REG_DATA_8BIT(0x0143)
#define CAN0RFLG REG_DATA_8BIT(0x0144)
#define CAN0RIER REG_DATA_8BIT(0x0145)
#define CAN0TFLG REG_DATA_8BIT(0x0146)
#define CAN0TIER REG_DATA_8BIT(0x0147)
#define CAN0TARQ REG_DATA_8BIT(0x0148)
#define CAN0TAAK REG_DATA_8BIT(0x0149)
#define CAN0TBSEL REG_DATA_8BIT(0x014A)
#define CAN0IDAC REG_DATA_8BIT(0x014B)
#define CAN0MISC REG_DATA_8BIT(0x014D)
#define CAN0RXERR REG_DATA_8BIT(0x014E)
#define CAN0TXERR REG_DATA_8BIT(0x014F)

#define CAN0IDAR0 REG_DATA_8BIT(0x0150)
#define CAN0IDAR1 REG_DATA_8BIT(0x0151)
#define CAN0IDAR2 REG_DATA_8BIT(0x0152)
#define CAN0IDAR3 REG_DATA_8BIT(0x0153)

#define CAN0IDMR0 REG_DATA_8BIT(0x0154)
#define CAN0IDMR1 REG_DATA_8BIT(0x0155)
#define CAN0IDMR2 REG_DATA_8BIT(0x0156)
#define CAN0IDMR3 REG_DATA_8BIT(0x0157)

#define CAN0IDAR4 REG_DATA_8BIT(0x0158)
#define CAN0IDAR5 REG_DATA_8BIT(0x0159)
#define CAN0IDAR6 REG_DATA_8BIT(0x015A)
#define CAN0IDAR7 REG_DATA_8BIT(0x015B)

#define CAN0IDMR4 REG_DATA_8BIT(0x015C)
#define CAN0IDMR5 REG_DATA_8BIT(0x015D)
#define CAN0IDMR6 REG_DATA_8BIT(0x015E)
#define CAN0IDMR7 REG_DATA_8BIT(0x015F)

// – 0x0153 : CAN0IDAR0 – CAN0IDAR3
//0x0154 – 0x0157 : CAN0IDMR0 – CAN0IDMR3

//0x0158 – 0x015B : CAN0IDAR4 – CAN0IDAR7
//0x015C – 0x015F : CAN0IDMR4 – CAN0IDMR7
//0x0160 – 0x016F : CAN0RXFG
//0x0170 – 0x017F : CAN0TXFG

typedef volatile struct {
  uint8_t CTL0;    /*00*/
  uint8_t CTL1;    /*01*/
  uint8_t BTR0;    /*02*/
  uint8_t BTR1;    /*03*/
  uint8_t RFLG;    /*04*/
  uint8_t RIER;    /*05*/
  uint8_t TFLG;    /*06*/
  uint8_t TIER;    /*07*/
  uint8_t TARQ;    /*08*/
  uint8_t TAAK;    /*09*/
  uint8_t TBSEL;   /*0A*/
  uint8_t IDAC;    /*0B*/
  uint8_t RESER0;  /*0C*/
  uint8_t RESER1;  /*0D*/
  uint8_t RXERR;   /*0E*/
  uint8_t TXERR;   /*0F*/
  uint8_t IDAR0;   /*10*/
  uint8_t IDAR1;   /*11*/
  uint8_t IDAR2;   /*12*/
  uint8_t IDAR3;   /*13*/
  uint8_t IDMR0;   /*14*/
  uint8_t IDMR1;   /*15*/
  uint8_t IDMR2;   /*16*/
  uint8_t IDMR3;   /*17*/
  uint8_t IDAR4;   /*18*/
  uint8_t IDAR5;   /*19*/
  uint8_t IDAR6;   /*1A*/
  uint8_t IDAR7;   /*1B*/
  uint8_t IDMR4;   /*1C*/
  uint8_t IDMR5;   /*1D*/
  uint8_t IDMR6;   /*1E*/
  uint8_t IDMR7;   /*1F*/
  uint8_t RXIDR0;  /*20*/
  uint8_t RXIDR1;  /*21*/
  uint8_t RXIDR2;  /*22*/
  uint8_t RXIDR3;  /*23*/
  uint8_t RXDSR[MAX_CAN_BYTES];/*24 ~ 2B*/
  uint8_t RXDLR;   /*2C*/
  uint8_t NOTAPP0; /*2D*/
  uint8_t RXTSRH;  /*2E*/
  uint8_t RXTSRL;  /*2F*/
  uint8_t TXIDR0;  /*30*/
  uint8_t TXIDR1;  /*31*/
  uint8_t TXIDR2;  /*32*/
  uint8_t TXIDR3;  /*33*/
  uint8_t TXDSR[MAX_CAN_BYTES];/*34 ~ 3B*/
  uint8_t TXDLR;   /*3C*/
  uint8_t TXTBPR;  /*3D*/
  uint8_t TXTSRH;  /*3E*/
  uint8_t TXTSRL;  /*3F*/
} CANregisterSet;


#endif /* SRC_INC_9S12X_CAN_REGS_H_ */
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
