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

#define KEYUSERVARSDSCRIPTOR_C

#include <stddef.h>

//#include "inc/typeChecks.h"
#include "inc/freeEMS.h"
#include "inc/dataLogDefinitions.h"
#include "inc/keyUserVarDescriptors.h"
#include "inc/libreDefs.h"
#include "inc/memory.h"
#include "inc/shared/libreExternalTypes.h"


const dataBlockDescriptor KeyUserVarsDescriptor[] KUVD_BASE_PAGE ={
  {
    .ID = U8_DID,
    .start = offsetof(KeyUserDebug, tempClock),
    .name = KUVD_LOG_PACKET_COUNT,
    .description = KUVD_THE_NUMBER_OF_DATALOGS_SENT,
  },
  {
    .ID = CNS_DID,
    .start = offsetof(KeyUserDebug, canStatus),
    .description = KUVD_CANBUS_STATUS,
  },
  {
    .ID = CSA_DID,
    .start = offsetof(KeyUserDebug, coreStatusA), 
    .description = KUVD_CORESTATUSA_BITFIELD,
  },
  {
    .ID = U8_DID,
    .name = KUVD_SPARE0,
    .start = offsetof(KeyUserDebug, spare0),
    .description = KUVD_SPARE_0,
  },
  {
    .ID = SFL_DID,
    .start = offsetof(KeyUserDebug, flaggableFlags), 
    .description = KUVD_FLAGGABLE_FLAGS,
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, serialOverrunErrors),
    .name = KUVD_SERIAL_OVERRUN,
    .description = KUVD_INCREMENTED_WHEN_AN_OVERRUN_OCCURS_DUE_TO_HIGH_INTERRUPT_LOAD_YES_IT_IS_A_FAULT_FIXME,
  },
  {
    .ID = U8_DID,
    .start = offsetof(KeyUserDebug, serialHardwareErrors), 
    .name = KUVD_SERIAL_HARDWARE_ERRORS,
    .description = KUVD_SUM_OF_NOISE_PARITY_AND_FRAMING_ERRORS
  },
  {
    .ID = U8_DID,
    .start = offsetof(KeyUserDebug, serialAndCommsCodeErrors), 
    .name = KUVD_PACKET_ERRORS,
    .description = KUVD_SUM_OF_CHECKSUM_ESCAPE_MISMATCHES_STARTS_INSIDE_AND_OVER_OR_UNDER_LENGTH,
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, flaggableFlags2), 
    .name = KUVD_FLAGGABLE_FLAGS2,
    .description = KUVD_COUNTER_INCREMENTED_STATUS_BITS_FOR_VARIOUS_THINGS_LIKE_COMMS_AND_DECODERS_ETC_APPLICABLE_TO_FLAGGABLES2_STRUCT
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, debugMessageCnt), 
    .name = KUVD_DEBUG_MESSAGE_COUNTER,
    .description = KUVD_COUNTER_OF_DEBUG_MESSAGES_SENT_UP_TO_THE_TUNER_FROM_PRINTF_CALLS,
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, zsp8), 
    .name = KUVD_ZSP8, 
    .description = KUVD_SPARE_8,
  },
  {
    .ID = PC_H_DID,
    .start = offsetof(KeyUserDebug, SecondaryInjDC),
    .name = KUVD_INJECTOR_DC_SECONDARY,
    .description = KUVD_SECONDARY_INJECTOR_DUTY_CYCLE,
  },
  {
    .ID = PC_H_DID,
    .start = offsetof(KeyUserDebug, PrimaryInjDC),
    .name = KUVD_INJECTOR_DC_PRIMARY,
    .description = KUVD_PRIMARY_INJECTOR_DUTY_CYCLE,
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, blendAlphaNPercent), 
    .name = KUVD_BLENDALPHANPERCENT,
    .description = KUVD_NOT_DOCUMENTED_YET,
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, speedDensityAirFlow), 
    .name = KUVD_SPEEDDENSITYAIRFLOW,
    .description = KUVD_NOT_DOCUMENTED_YET,
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, alphaNAirFlow), 
    .name = KUVD_ALPHANAIRFLOW,
    .description = KUVD_NOT_DOCUMENTED_YET,
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, clockInMilliSeconds),
    .name = KUVD_CLOCK_IN_MS,
    .description = KUVD_INTERNAL_CLOCK_IN_MILLISECOND_INCREMENTS,
  },
  {
    .ID = CMS_DID,
    .start = offsetof(KeyUserDebug, clockIn8thsOfAMilli), 
    .name = KUVD_CLOCKIN8THSOFAMILLI,
    .description = KUVD_INTERNAL_CLOCK_IN_ONE_EIGHTS_MILLISECOND_INCREMENTS,
  },
  {
    .ID = ICB_DID,
    .start = offsetof(KeyUserDebug, ignitionCuts), 
    .description = KUVD_IGNITION_CUTS,
  },
  {
    .ID = IJB_DID,
    .start = offsetof(KeyUserDebug, injectionCuts), 
    .description = KUVD_INJETION_CUTS,
  },
  {
    .ID = PC_H_DID,
    .start = offsetof(KeyUserDebug, fuelingDelta),
    .name = KUVD_FUELING_DELTA,
    .description = KUVD_FUELING_DELTA_BETWEEN_FUELING_EVENTS_IN_SCALED_PERCENTAGE
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, CANbytesRx),
    .name = KUVD_CAN_RX_BYTES,
    .description = KUVD_NUMBER_OF_BYTES_RECEIVED_ON_THE_CAN_BUSES,
  },
  {
    .ID = U16_DID,
    .start = offsetof(KeyUserDebug, CANframesRx),
    .name = KUVD_CAN_RX_FRAMES,
    .description = KUVD_NUMBER_OF_FRAMES_RECEIVED_ON_CAN_BUS_0,
  },
  {
    .ID = FP_DID,
    .start = offsetof(KeyUserDebug, engineOilPressure),
    .name = KUVD_OIL_PRESSURE_LOG,
    .description = KUVD_OIL_PRESSURE,
  }
};


//CASSERT((sizeof(KeyUserDebug) / sizeof(uint16_t)) == (sizeof(KeyUserVarsDescriptor) / sizeof(dataBlockDescriptor)), DATALOGDEFINITIONS_C) // At least check for correct number of entries
const uint8_t KeyUserVarsDescriptorCnt = (sizeof(KeyUserVarsDescriptor) / sizeof(dataBlockDescriptor));
