/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2016 Sean Keys, David Andruczyk
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
 * @ingroup dataInitialisers
 *
 * @brief Manifold Air Temperature Transfer Table
 *
 */


#include "../inc/freeEMS.h"
#include "../inc/Configuration.h"


const volatile uint16_t MATTransferTable[1024] LOOKUPD = {
#include MAT_TRANSFER_TABLE
};
