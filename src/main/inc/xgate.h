/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014 Sean Keys
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
 * @ingroup init
 *
 * @brief TODO
 *
 */
#ifndef FILE_XGATEVECTORS_H_SEEN
#define FILE_XGATEVECTORS_H_SEEN

#include <stdint.h>

#define START_OF_FLASH_WINDOW     ((uint16_t)0x8000) /* 16KB long */
#define START_OF_RAM_WINDOW       ((uint16_t)0x1000) /* 4KB long */
#define XGATE_TEXT_ALLOCATION_SIZE  ((uint16_t)0x0200) /* .5 KBytes */
//#define RPAGE_TUNE_TWO_WINDOW_DIFFERENCE (0x8000) /*RPAGE2 starts at 0x9000 for xgate and 0x1000 for s12 */

#define XGATE_INTERRUPT     (0x80)
#define S12X_INTERRUPT      (0)

#define PRIORITY_LEVEL_TWO  (0x01)
#define PRIORITY_LEVEL_ONE  (0x02)  /* Highest PRI */

#define S12X_PRIORITY_LEVEL_ZERO   (0) /* Disabled */
#define S12X_PRIORITY_LEVEL_ONE    (1)
#define S12X_PRIORITY_LEVEL_TWO    (2)
#define S12X_PRIORITY_LEVEL_THREE  (3)
#define S12X_PRIORITY_LEVEL_FOUR   (4)
#define S12X_PRIORITY_LEVEL_FIVE   (5)
#define S12X_PRIORITY_LEVEL_SIX    (6)
#define S12X_PRIORITY_LEVEL_SEVEN  (7) /* Highest Priority */


#define ROUTE_INTERRUPT(channel_id, cpu_assignment, priority) \
        INT_CFADDR = (channel_id * 2) & 0xF0;                 \
        INT_CFDATA_ARR[((channel_id * 2) & 0x0F) >> 1] = (cpu_assignment | priority);


typedef struct {
  uint16_t programCounterValue; /* This data is forced into the XGATE PC register */
  uint16_t initialVariable; /* This data is forced into the XGATE R1 register */
} xgateIntVector;

// This statement imports the symbol from the xgate ASM for use in the vector table
extern void swISR0();
extern void TC2ISR();
extern void TC3ISR();
extern void startXGATECode();
extern void endXGATECode();
extern void PIT0();


// Xgate control value
#define XGATE_ERROR_HANDLER 0x0000 /* TODO Create the XGATE error handling thread in asm. */


/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
