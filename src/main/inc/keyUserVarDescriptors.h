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

#ifndef FILE_KEYUSERVARDESCRIPTORS_H_SEEN
#define FILE_KEYUSERVARDESCRIPTORS_H_SEEN

#include "memory.h"

/* Names */
const int8_t KUVD_LOG_PACKET_COUNT[] KUVD_NAME_PAGE = "Log Packet Count";
const int8_t KUVD_SPARE0[] KUVD_NAME_PAGE = "Spare0";
const int8_t KUVD_SERIAL_OVERRUN[] KUVD_NAME_PAGE = "Serial over-run";
const int8_t KUVD_SERIAL_HARDWARE_ERRORS[] KUVD_NAME_PAGE = "Serial Hardware Errors";
const int8_t KUVD_PACKET_ERRORS[] KUVD_NAME_PAGE = "Packet Errors";
const int8_t KUVD_FLAGGABLE_FLAGS2[] KUVD_NAME_PAGE = "Flaggable Flags2";
const int8_t KUVD_DEBUG_MESSAGE_COUNTER[] KUVD_NAME_PAGE = "Debug Message Counter";
const int8_t KUVD_ZSP8[] KUVD_NAME_PAGE = "zsp8 ";
const int8_t KUVD_INJECTOR_DC_SECONDARY[] KUVD_NAME_PAGE = "Injector DC(Secondary)";
const int8_t KUVD_INJECTOR_DC_PRIMARY[] KUVD_NAME_PAGE = "Injector DC(Primary)";
const int8_t KUVD_BLENDALPHANPERCENT[] KUVD_NAME_PAGE = "blendAlphaNPercent ";
const int8_t KUVD_SPEEDDENSITYAIRFLOW[] KUVD_NAME_PAGE = "speedDensityAirflow ";
const int8_t KUVD_ALPHANAIRFLOW[] KUVD_NAME_PAGE = "alphaNAirFlow ";
const int8_t KUVD_CLOCK_IN_MS[] KUVD_NAME_PAGE = "Clock in mS";
const int8_t KUVD_CLOCKIN8THSOFAMILLI[] KUVD_NAME_PAGE = "clockIn8thsofAMilli ";
const int8_t KUVD_FUELING_DELTA[] KUVD_NAME_PAGE = "Fueling Delta";
const int8_t KUVD_CAN_RX_BYTES[] KUVD_NAME_PAGE = "CAN RX Bytes";
const int8_t KUVD_CAN_RX_FRAMES[] KUVD_NAME_PAGE = "CAN RX Frames";


/* Descriptions */
const int8_t KUVD_THE_NUMBER_OF_DATALOGS_SENT[] KUVD_DESC_PAGE = "The number of datalogs sent";
const int8_t KUVD_CANBUS_STATUS[] KUVD_DESC_PAGE = "CANbus status";
const int8_t KUVD_CORESTATUSA_BITFIELD[] KUVD_DESC_PAGE = "CoreStatusA bitfield";
const int8_t KUVD_SPARE_0[] KUVD_DESC_PAGE = "Spare 0";
const int8_t KUVD_FLAGGABLE_FLAGS[] KUVD_DESC_PAGE = "Flaggable Flags";
const int8_t KUVD_INCREMENTED_WHEN_AN_OVERRUN_OCCURS_DUE_TO_HIGH_INTERRUPT_LOAD_YES_IT_IS_A_FAULT_FIXME[] KUVD_DESC_PAGE = "Incremented when an overrun occurs due to high interrupt load yes it is a fault FIXME";
const int8_t KUVD_SUM_OF_NOISE_PARITY_AND_FRAMING_ERRORS[] KUVD_DESC_PAGE = "Sum of noise parity and framing errors";
const int8_t KUVD_SUM_OF_CHECKSUM_ESCAPE_MISMATCHES_STARTS_INSIDE_AND_OVER_OR_UNDER_LENGTH[] KUVD_DESC_PAGE = "Sum of checksum escape mismatches starts inside and over/under length";
const int8_t KUVD_COUNTER_INCREMENTED_STATUS_BITS_FOR_VARIOUS_THINGS_LIKE_COMMS_AND_DECODERS_ETC_APPLICABLE_TO_FLAGGABLES2_STRUCT[] KUVD_DESC_PAGE = "Counter incremented status bits for various things like comms and decoders etc applicable to flaggables2 struct";
const int8_t KUVD_COUNTER_OF_DEBUG_MESSAGES_SENT_UP_TO_THE_TUNER_FROM_PRINTF_CALLS[] KUVD_DESC_PAGE = "Counter of debug messages sent up to the tuner from printf calls";
const int8_t KUVD_SPARE_8[] KUVD_DESC_PAGE = "Spare 8";
const int8_t KUVD_SECONDARY_INJECTOR_DUTY_CYCLE[] KUVD_DESC_PAGE = "Secondary Injector Duty Cycle";
const int8_t KUVD_PRIMARY_INJECTOR_DUTY_CYCLE[] KUVD_DESC_PAGE = "Primary Injector Duty Cycle";
const int8_t KUVD_NOT_DOCUMENTED_YET[] KUVD_DESC_PAGE = "Not documented yet";
const int8_t KUVD_INTERNAL_CLOCK_IN_MILLISECOND_INCREMENTS[] KUVD_DESC_PAGE = "Internal Clock in millisecond increments";
const int8_t KUVD_INTERNAL_CLOCK_IN_ONE_EIGHTS_MILLISECOND_INCREMENTS[] KUVD_DESC_PAGE = "Internal Clock in one eights millisecond increments";
const int8_t KUVD_IGNITION_CUTS[] KUVD_DESC_PAGE = "Ignition Cuts";
const int8_t KUVD_INJETION_CUTS[] KUVD_DESC_PAGE = "Injetion Cuts";
const int8_t KUVD_FUELING_DELTA_BETWEEN_FUELING_EVENTS_IN_SCALED_PERCENTAGE[] KUVD_DESC_PAGE = "Fueling delta between fueling events in scaled percentage";
const int8_t KUVD_NUMBER_OF_BYTES_RECEIVED_ON_THE_CAN_BUSES[] KUVD_DESC_PAGE = "Number of bytes received on the CAN buses";
const int8_t KUVD_NUMBER_OF_FRAMES_RECEIVED_ON_CAN_BUS_0[] KUVD_DESC_PAGE = "Number of Frames received on CAN bus 0";

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */

