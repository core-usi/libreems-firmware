/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014-2016 Sean Keys, David J. Andruczyk
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

#define CORVARSDESCRIPTOR_C

#include <stddef.h>

//#include "inc/typeChecks.h"
#include "inc/freeEMS.h"
#include "inc/coreVarsDescriptor.h"
#include "inc/dataLogDefinitions.h"
#include "inc/libreDefs.h"
#include "inc/memory.h"
#include "inc/shared/libreExternalTypes.h"


//TODO Potentially change linker so that they are guaranteed to have a successive LMA(load memory address)
//TODO Create macro(s) to remove duplicates. Eg .start and .size take the same parameters
//TODO once all done enable CASSERT
extern CoreVar CoreVars_g;

const dataBlockDescriptor coreVarsDescriptor[] FD_BASE_PAGE = {
  {
    .ID = IAT_DID,
    .start = offsetof(CoreVar, IAT), 
    .CANid = 0x101
  },
  {
    .ID = CHT_DID,
    .start = offsetof(CoreVar, CHT), 
    .CANid = 0x102
  },
  {
    .ID = TPS_DID,
    .start = offsetof(CoreVar, TPS),
    .CANid = 0x103
  },
  {
    .ID = EGO_DID,
    .start = offsetof(CoreVar, EGO), 
    .CANid = 0x104
  },
  {
    .ID = MAP_DID,
    .start = offsetof(CoreVar, MAP), 
    .CANid = 0x105
  },
  {
    .ID = AAP_DID,
    .start = offsetof(CoreVar, AAP), 
    .CANid = 0x106
  },
  {
    .ID = BRV_DID,
    .start = offsetof(CoreVar, BRV), 
    .CANid = 0x107
  },
  {
    .ID = MAT_DID,
    .start = offsetof(CoreVar, MAT), 

    .CANid = 0x108
  },
  {
    .ID = EGT_DID,
    .start = offsetof(CoreVar, EGT),
    .CANid = 0x109
  },
  {
    .ID = IAP_DID,
    .start = offsetof(CoreVar, IAP), 
    .CANid = 0x10A
  },
  {
    .ID = MAF_DID,
    .start = offsetof(CoreVar, MAF), 
    .CANid = 0x10B
  },
  {
    .ID = DMAP_DID,
    .start = offsetof(CoreVar, DMAP), 
    .CANid = 0x10C
  },
  {
    .ID = DTPS_DID,
    .start = offsetof(CoreVar, DTPS), 
    .CANid = 0x10D
  },
  {
    .ID = RPM_DID,
    .start = offsetof(CoreVar, RPM), 
    .CANid = 0x10E
  },
  {
    .ID = FP_DID,
    .start = offsetof(CoreVar, FuelPressure),
    .CANid = 0x10F
  },
  {
    .ID = EP_DID,
    .start = offsetof(CoreVar, EthanolPercentage),
    .CANid = 0x110
  }
};


C_ASSERT((sizeof(CoreVar) / sizeof(uint16_t)) == (sizeof(coreVarsDescriptor) / sizeof(dataBlockDescriptor)), DATALOGDEFINITIONS_C) // At least check for correct number of entries
const uint8_t coreVarsDescriptorCnt = (sizeof(coreVarsDescriptor) / sizeof(dataBlockDescriptor));

/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
