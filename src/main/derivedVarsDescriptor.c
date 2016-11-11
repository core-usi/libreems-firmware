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

#define DERIVEDVARSDESCRIPTOR_C

#include <stddef.h>

//#include "inc/typeChecks.h"
#include "inc/freeEMS.h"
#include "inc/dataLogDefinitions.h"
#include "inc/derivedVarsDescriptor.h"
#include "inc/libreDefs.h"
#include "inc/memory.h"
#include "inc/shared/libreExternalTypes.h"



const dataBlockDescriptor derivedVarsDescriptor[] DVD_BASE_PAGE ={
  {
    .ID = LD_DID,
    .start = offsetof(DerivedVar, LoadMain),
    .name = DVD_LOADMAIN,
    .description = DVD_DOCUMENT_LOADMAIN,
  },
  {
    .ID = VE_DID,
    .start = offsetof(DerivedVar, VEMain),
    .name = DVD_VEMAIN,
    .description = DVD_DOCUMENT_VEMAIN,
  },
  {
    .ID = LMB_DID,
    .start = offsetof(DerivedVar, Lambda),
    .name = DVD_LAMBDA,
    .description = DVD_DOCUMENT_LAMBDA,

  },
  {
    .ID = ACM_DID,
    .start = offsetof(DerivedVar, AirChargeMass),
    .name = DVD_AIRCHARGEMASS,
    .description = DVD_DOCUMENT_AIRCHARGEMASS,
  },
  {
    .ID = SAR_DID,
    .start = offsetof(DerivedVar, StoichAFR),
    .name = DVD_STOICHAFR,
    .description = DVD_DOCUMENT_STOICHAFR,
  },
  {
    .ID = FDN_DID,
    .start = offsetof(DerivedVar, FuelDensity),
    .name = DVD_FUELDENSITY,
    .description = DVD_DOCUMENT_FUELDENSITY,
  },
  {
    .ID = ETE_DID,
    .start = offsetof(DerivedVar, ETE),
    .name = DVD_ETE,
    .description = DVD_DOCUMENT_ETE,
  },
  {
    .ID = TFC_DID,
    .start = offsetof(DerivedVar, TFCTotal),
    .name = DVD_TFCTOTAL,
    .description = DVD_DOCUMENT_TFCTOTAL,
  },
  {
    .ID = DPM_DID,
    .start = offsetof(DerivedVar, Displacement),
    .name = DVD_DISPLACEMENT,
    .description = DVD_DOCUMENT_DISPLACEMENT,
  },
  {
    .ID = PW_M_DID,
    .start = offsetof(DerivedVar, IDT),
    .name = DVD_IDT,
    .description = DVD_INJECTOR_DEAD_TIME_TIME_BEFORE_FUEL_FLOW_BEGINS,
  },
  {
    .ID = PW_M_DID,
    .start = offsetof(DerivedVar, RefPW),
    .name = DVD_FUEL_PW,
    .description = DVD_REFERENCE_PW_IE_ACTUAL_PW_BEFORE_TRIMS_ARE_APPLIED,
  },
  {
    .ID = ANG_DID,
    .start = offsetof(DerivedVar, Advance),
    .name = DVD_TIMING_ADVANCE,
    .description = DVD_TOTAL_IGNITION_TIMING_ADVANCE_BTDC,
  },
  {
    .ID = PW_M_DID,
    .start = offsetof(DerivedVar, Dwell),
    .name = DVD_IGNITION_DWELL,
    .description = DVD_IGNITION_DWELL_PERIOD,
  }
};



C_ASSERT((sizeof(DerivedVar) / sizeof(uint16_t)) == (sizeof(derivedVarsDescriptor) / sizeof(dataBlockDescriptor)), DATALOGDEFINITIONS_C) // At least check for correct number of entries
const uint8_t derivedVarsDescriptorCnt = (sizeof(derivedVarsDescriptor) / sizeof(dataBlockDescriptor));

/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
