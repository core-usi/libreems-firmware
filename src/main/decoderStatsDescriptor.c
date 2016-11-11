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

#define DECODERSTATSSCRIPTOR_C

#include <stddef.h>

//#include "inc/typeChecks.h"
#include "inc/freeEMS.h"
#include "inc/dataLogDefinitions.h"
#include "inc/decoderStatsDescriptor.h"
#include "inc/libreDefs.h"
#include "inc/memory.h"
#include "inc/shared/libreExternalTypes.h"


const dataBlockDescriptor DecoderStatsDescriptor[] DSD_BASE_PAGE = {
  {
    .ID = U16_DID,
    .start = offsetof(DecoderStats, primaryTeethSeen),
    .name = DSD_PRIMARY_TEETH_SEEN,
    .description = DSD_THE_NUMBER_OF_TEETH_SEEN_BY_THE_PRIMARY_DECODER_ISR,
  },
  {
    .ID = U16_DID,
    .start = offsetof(DecoderStats, secondaryTeethSeen),
    .name = DSD_SECONDARY_TEETH_SEEN,
    .description = DSD_THE_NUMBER_OF_TEETH_SEEN_BY_THE_SECONDARY_DECODER_ISR,
  },
  {
    .ID = U16_DID,
    .start = offsetof(DecoderStats, instantTicksPerDegree),
    .name = DSD_TICKSPERDEGREE,
    .description = DSD_TICKS_PER_DEGREE_AS_CALCULATED_BY_PRIMARY_DECODER_ISR,
  },
  {
    .ID = EXT_DID,
    .start = offsetof(DecoderStats, lastPrimaryTimeStamp),
    .name = DSD_PRIMARY_TIME_STAMP,
    .description = DSD_TIME_STAMP_FROM_PRIMARY_ENGINE_ANGLE_DECODER_SIGNAL,
  },
  {
    .ID = PC_D_DID,
    .start = offsetof(DecoderStats, primaryInputVariance),
  },
  {
    .ID = U16_DID,
    .start = offsetof(DecoderStats, syncADCsamples),
    .name = DSD_SYNCED_ADC_SAMPLES,
    .description = DSD_NUMBER_OF_ADC_SAMPLES_TAKEN_AT_SPECIFIC_ENGINE_ANGLES,
  },
  {
    .ID = DCF_DID,
    .start = offsetof(DecoderStats, decoderFlags),
  },
  {
    .ID = U8_DID,
    .start = offsetof(DecoderStats, currentPrimaryEvent),
    .name = DSD_CURRENT_PRIMARY_EVENT,
    .description = DSD_PRIMARY_EVENT_INDEX_PROCESSED_BY_ISR,
  },
  {
    .ID = U8_DID,
    .start = offsetof(DecoderStats, lockLossCauseID),
    .name = DSD_DECODER_LOCK_LOSS_ID,
    .description = DSD_TODO_SEND_ENUM_DESCRIPTOR,
  },
  {
    .ID = U16_DID,
    .start = offsetof(DecoderStats, decoderResetCalls),
    .name = DSD_DECODER_LOCK_LOSS_COUNT,
    .description = DSD_NUMBER_OF_TIMES_THE_DECODER_LOST_ALL_LOCKS,
  },
  {
    .ID = U8_DID,
    .start = offsetof(DecoderStats, eventLockWasLost),
    .name = DSD_LOCK_LOST_PRIMARY_EVENT,
    .description = DSD_EVENT_BEING_PROCESSED_WHEN_LOCK_WAS_LOST,
  },
  {
    .ID = U16_DID,
    .start = offsetof(DecoderStats, debug_16b),
    .name = DSD_DECODER_DEBUG,
    .description = DSD_SEE_DECODER_NOTES_SPECIFIC_TO_YOUR_ENGINE,
  },
  {
    .ID = U8_DID,
    .start = offsetof(DecoderStats, requiredSyncCycles),
    .name = DSD_DECODER_SYNC_CYCLE_REQUIREMENT,
    .description = DSD_DECODER_SYNC_CYCLE_REQUIREMENT_DESCRIPTION,
  }
};


const uint8_t DecoderStatsDescriptorCnt = (sizeof(DecoderStatsDescriptor) / sizeof(dataBlockDescriptor));

/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
