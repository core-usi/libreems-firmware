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

#ifndef SRC_INC_9S12X_REG_NOMENCLATURE_H_
#define SRC_INC_9S12X_REG_NOMENCLATURE_H_

#include <stdint.h>

#define REG_DATA_8BIT(address)  (*((volatile uint8_t*)(address)))
#define REG_DATA_16BIT(address) (*((volatile uint16_t*)(address))))


#endif /* SRCINC_9S12X_REG_NOMENCLATURE_H_ */
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
