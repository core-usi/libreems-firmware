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

#define GENERALPURPOSEINPUTSDESCRIPTOR_C

#include <stddef.h>

//#include "inc/typeChecks.h"
#include "inc/freeEMS.h"
#include "inc/dataLogDefinitions.h"
#include "inc/generalPurposeInputsDescriptor.h"
#include "inc/libreDefs.h"
#include "inc/memory.h"
#include "inc/shared/libreExternalTypes.h"

const dataBlockDescriptor generalPurproseInputsDescriptor[] GPID_BASE_PAGE = {
  {
    .ID = ANG_DID,
    .name = GPID_GPC1_ANGLE_H,
    .start = offsetof(CapturedInputData, capturedAngleHigh),
    .description = GPID_ENGINE_ANGLE_AT_GPC1_TRANSITION_HIGH,
  },
  {
    .ID = ANG_DID,
    .name = GPID_GPC1_ANGLE_L,
    .start = offsetof(CapturedInputData, capturedAngleLow),
    .description = GPID_ENGINE_ANGLE_AT_GPC1_TRANSITION_LOW,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC1_PW_H,
    .start = offsetof(CapturedInputData, periodHighTicks),
    .description = GPID_MEASURED_PULSE_WIDTH_ON_GC1_PIN_IN_USEC,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC1_PW_L,
    .start = offsetof(CapturedInputData, periodLowTicks),
    .description = GPID_MEASURED_PULSE_WIDTH_ON_GPC1_PIN_IN_USEC,
  },
  {
    .ID = HZ_DID,
    .name = GPID_GPC1_HZ,
    .start = offsetof(CapturedInputData, frequencyHz),
    .description = GPID_MEASURED_HZ_ON_GPC1_PIN,
  },
  {
    .ID = U16_DID,
    .name = GPID_GPC1_EDGE_COUNT,
    .start = offsetof(CapturedInputData, ISRcount),
    .description = GPID_NUMBER_OF_EDGES_SEEN_ON_GPC1_PIN,
  },/* Second array member */
  {
    .ID = ANG_DID,
    .name = GPID_GPC2_ANGLE_H,
    .start = offsetof(CapturedInputData, capturedAngleHigh) + (sizeof(CapturedInputData) * 1),
    .description = GPID_ENGINE_ANGLE_AT_GPC2_TRANSITION_HIGH,
  },
  {
    .ID = ANG_DID,
    .name = GPID_GPC2_ANGLE_L,
    .start = offsetof(CapturedInputData, capturedAngleLow) + (sizeof(CapturedInputData) * 1),
    .description = GPID_ENGINE_ANGLE_AT_GPC2_TRANSITION_LOW,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC2_PW_H,
    .start = offsetof(CapturedInputData, periodHighTicks) + (sizeof(CapturedInputData) * 1),
    .description = GPID_MEASURED_PULSE_WIDTH_ON_GPC2_PIN_IN_USEC_H,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC2_PW_L,
    .start = offsetof(CapturedInputData, periodLowTicks) + (sizeof(CapturedInputData) * 1),
    .description = GPID_MEASURED_PULSE_WIDTH_ON_GPC2_PIN_IN_USEC_L,
  },
  {
    .ID = HZ_DID,
    .name = GPID_GPC2_HZ,
    .start = offsetof(CapturedInputData, frequencyHz) + (sizeof(CapturedInputData) * 1),
    .description = GPID_MEASURED_HZ_ON_GPC2_PIN,
  },
  {
    .ID = U16_DID,
    .name = GPID_GPC2_EDGE_COUNT,
    .start = offsetof(CapturedInputData, ISRcount) + (sizeof(CapturedInputData) * 1),
    .description = GPID_NUMBER_OF_EDGES_SEEN_ON_GPC2_PIN,
  },
  {
    .ID = ANG_DID,
    .name = GPID_GPC3_ANGLE_H,
    .start = offsetof(CapturedInputData, capturedAngleHigh) + (sizeof(CapturedInputData) * 2),
    .description = GPID_ENGINE_ANGLE_AT_GPC3_TRANSITION_HIGH,
  },
  {
    .ID = ANG_DID,
    .name = GPID_GPC3_ANGLE_L,
    .start = offsetof(CapturedInputData, capturedAngleLow) + (sizeof(CapturedInputData) * 2),
    .description = GPID_ENGINE_ANGLE_AT_GPC3_TRANSITION_LOW,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC3_PW_H,
    .start = offsetof(CapturedInputData, periodHighTicks) + (sizeof(CapturedInputData) * 2),
    .description = GPID_MEASURED_HIGH_PULSE_WIDTH_ON_A_GPC3_CAPTURE_PIN_IN_USEC,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC3_PW_L,
    .start = offsetof(CapturedInputData, periodLowTicks) + (sizeof(CapturedInputData) * 2),
    .description = GPID_MEASURED_LOW_PULSE_WIDTH_ON_GPC3_PIN_IN_USEC,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC3_HZ,
    .start = offsetof(CapturedInputData, frequencyHz) + (sizeof(CapturedInputData) * 2),
    .description = GPID_MEASURED_HZ_ON_GPC3_PIN,
  },
  {
    .ID = U16_DID,
    .name = GPID_GPC3_EDGE_COUNT,
    .start = offsetof(CapturedInputData, ISRcount) + (sizeof(CapturedInputData) * 2),
    .description = GPID_NUMBER_OF_EDGES_SEEN_ON_GPC3_PIN,
  },
  {
    .ID = ANG_DID,
    .name = GPID_GPC4_ANGLE_H,
    .start = offsetof(CapturedInputData, capturedAngleHigh) + (sizeof(CapturedInputData) * 3),
    .description = GPID_ENGINE_ANGLE_AT_GPC4_TRANSITION_HIGH,
  },
  {
    .ID = ANG_DID,
    .name = GPID_GPC4_ANGLE_L,
    .start = offsetof(CapturedInputData, capturedAngleLow) + (sizeof(CapturedInputData) * 3),
    .description = GPID_ENGINE_ANGLE_AT_GPC4_TRANSITION_LOW,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC4_PW_H,
    .start = offsetof(CapturedInputData, periodHighTicks) + (sizeof(CapturedInputData) * 3),
    .description = GPID_MEASURED_HIGH_PULSE_WIDTH_ON_GPC4_PIN_IN_USEC,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC4_PW_L,
    .start = offsetof(CapturedInputData, periodLowTicks) + (sizeof(CapturedInputData) * 3),
    .description = GPID_MEASURED_LOW_PULSE_WIDTH_ON_GPC4_PIN_IN_USEC,
  },
  {
    .ID = HZ_DID,
    .name = GPID_GPC4_HZ,
    .start = offsetof(CapturedInputData, frequencyHz) + (sizeof(CapturedInputData) * 3),
    .description = GPID_MEASURED_HZ_ON_A_GPC4_CAPTURE_PIN,
  },
  {
    .ID = U16_DID,
    .name = GPID_GPC4_EDGE_COUNT,
    .start = offsetof(CapturedInputData, ISRcount) + (sizeof(CapturedInputData) * 3),
    .description = GPID_NUMBER_OF_EDGES_SEEN_ON_GPC4_PIN,
  },
  {
    .ID = ANG_DID,
    .name = GPID_GPC5_ANGLE_H,
    .start = offsetof(CapturedInputData, capturedAngleHigh) + (sizeof(CapturedInputData) * 4),
    .description = GPID_ENGINE_ANGLE_AT_PIN_TRANSITION_HIGH,
  },
  {
    .ID = ANG_DID,
    .name = GPID_GPC5_ANGLE_L,
    .start = offsetof(CapturedInputData, capturedAngleLow) + (sizeof(CapturedInputData) * 4),
    .description = GPID_ENGINE_ANGLE_AT_PIN_TRANSITION_LOW,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC5_PW_H,
    .start = offsetof(CapturedInputData, periodHighTicks) + (sizeof(CapturedInputData) * 4),
    .description = GPID_MEASURED_HIGH_PULSE_WIDTH_ON_GPC5_PIN_IN_USEC,
  },
  {
    .ID = PW_DID,
    .name = GPID_GPC5_PW_L,
    .start = offsetof(CapturedInputData, periodLowTicks) + (sizeof(CapturedInputData) * 4),
    .description = GPID_MEASURED_PULSE_WIDTH_ON_GPC5_PIN_IN_USEC,
  },
  {
    .ID = HZ_DID,
    .name = GPID_GPC5_HZ,
    .start = offsetof(CapturedInputData, frequencyHz) + (sizeof(CapturedInputData) * 4),
    .description = GPID_MEASURED_HZ_ON_GPC5_PIN,
  },
  {
    .ID = U16_DID,
    .name = GPID_GPC5_EDGE_COUNT,
    .start = offsetof(CapturedInputData, ISRcount) + (sizeof(CapturedInputData) * 4),
    .description = GPID_NUMBER_OF_EDGES_SEEN_ON_GPC5_PIN,
  }
};


const uint8_t gpInputDescriptorCnt = (sizeof(generalPurproseInputsDescriptor) / sizeof(dataBlockDescriptor));

/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
