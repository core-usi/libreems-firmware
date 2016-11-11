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

#ifndef FILE_DECODERSTATSDESCRIPTOR_H_SEEN
#define FILE_DECODERSTATSDESCRIPTOR_H_SEEN

/* Names */
const int8_t DSD_PRIMARY_TEETH_SEEN[] DSD_NAME_PAGE = "PrimaryTeethSeen";
const int8_t DSD_SECONDARY_TEETH_SEEN[] DSD_NAME_PAGE = "SecondaryTeethSeen";
const int8_t DSD_TICKSPERDEGREE[] DSD_NAME_PAGE = "TicksPerDegree";
const int8_t DSD_PRIMARY_TIME_STAMP[] DSD_NAME_PAGE = "Primary Time Stamp";
const int8_t DSD_SYNCED_ADC_SAMPLES[] DSD_NAME_PAGE = "Synced ADC samples";
const int8_t DSD_CURRENT_PRIMARY_EVENT[] DSD_NAME_PAGE = "Current Primary Event";
const int8_t DSD_DECODER_LOCK_LOSS_ID[] DSD_NAME_PAGE = "Decoder Lock Loss ID";
const int8_t DSD_DECODER_LOCK_LOSS_COUNT[] DSD_NAME_PAGE = "Decoder Lock Loss Count";
const int8_t DSD_LOCK_LOST_PRIMARY_EVENT[] DSD_NAME_PAGE = "Lock Lost Primary Event";
const int8_t DSD_DECODER_DEBUG[] DSD_NAME_PAGE = "Spare 16-bit For Debug";
const int8_t DSD_DECODER_SYNC_CYCLE_REQUIREMENT[] DSD_NAME_PAGE = "Required sync cycles";

/* Descriptions */
const int8_t DSD_THE_NUMBER_OF_TEETH_SEEN_BY_THE_PRIMARY_DECODER_ISR[] DSD_DESC_PAGE = "The number of teeth seen by the primary decoder ISR";
const int8_t DSD_THE_NUMBER_OF_TEETH_SEEN_BY_THE_SECONDARY_DECODER_ISR[] DSD_DESC_PAGE = "The number of teeth seen by the secondary decoder ISR";
const int8_t DSD_TICKS_PER_DEGREE_AS_CALCULATED_BY_PRIMARY_DECODER_ISR[] DSD_DESC_PAGE = "Ticks-Per-Degree as calculated by primary decoder ISR";
const int8_t DSD_TIME_STAMP_FROM_PRIMARY_ENGINE_ANGLE_DECODER_SIGNAL[] DSD_DESC_PAGE = "Time Stamp From Primary Engine Angle Decoder Signal";
const int8_t DSD_NUMBER_OF_ADC_SAMPLES_TAKEN_AT_SPECIFIC_ENGINE_ANGLES[] DSD_DESC_PAGE = "Number of ADC samples taken at specific engine angles";
const int8_t DSD_PRIMARY_EVENT_INDEX_PROCESSED_BY_ISR[] DSD_DESC_PAGE = "Primary Event Index Processed by ISR";
const int8_t DSD_TODO_SEND_ENUM_DESCRIPTOR[] DSD_DESC_PAGE = "TODO send enum descriptor";
const int8_t DSD_NUMBER_OF_TIMES_THE_DECODER_LOST_ALL_LOCKS[] DSD_DESC_PAGE = "Number of times the decoder lost all locks";
const int8_t DSD_EVENT_BEING_PROCESSED_WHEN_LOCK_WAS_LOST[] DSD_DESC_PAGE = "Event being processed when lock was lost";
const int8_t DSD_SEE_DECODER_NOTES_SPECIFIC_TO_YOUR_ENGINE[] DSD_DESC_PAGE = "See decoder notes specific to your engine";
const int8_t DSD_DECODER_SYNC_CYCLE_REQUIREMENT_DESCRIPTION[] DSD_DESC_PAGE = "Number of engine cycles that sync must be maintained before scheduling outputs";


#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */

