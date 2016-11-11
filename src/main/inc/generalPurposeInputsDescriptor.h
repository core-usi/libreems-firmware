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

#ifndef FILE_GENERALPURPOSEINPUTDESCRIPTOR_H_SEEN
#define FILE_GENERALPURPOSEINPUTDESCRIPTOR_H_SEEN

#include "memory.h"

/* Names */
const int8_t GPID_GPC1_ANGLE_H[] GPID_NAME_PAGE = "GPC1 Angle-H";
const int8_t GPID_GPC1_ANGLE_L[] GPID_NAME_PAGE = "GPC1 Angle-L";
const int8_t GPID_GPC1_PW_H[] GPID_NAME_PAGE = "GPC1 PW-H";
const int8_t GPID_GPC1_PW_L[] GPID_NAME_PAGE = "GPC1 PW-L";
const int8_t GPID_GPC1_HZ[] GPID_NAME_PAGE = "GPC1 Hz";
const int8_t GPID_GPC1_EDGE_COUNT[] GPID_NAME_PAGE = "GPC1 Edge Count";
const int8_t GPID_GPC2_ANGLE_H[] GPID_NAME_PAGE = "GPC2 Angle-H";
const int8_t GPID_GPC2_ANGLE_L[] GPID_NAME_PAGE = "GPC2 Angle-L";
const int8_t GPID_GPC2_PW_H[] GPID_NAME_PAGE = "GPC2 PW-H";
const int8_t GPID_GPC2_PW_L[] GPID_NAME_PAGE = "GPC2 PW-L";
const int8_t GPID_GPC2_HZ[] GPID_NAME_PAGE = "GPC2 Hz";
const int8_t GPID_GPC2_EDGE_COUNT[] GPID_NAME_PAGE = "GPC2 Edge Count";
const int8_t GPID_GPC3_ANGLE_H[] GPID_NAME_PAGE = "GPC3 Angle-H";
const int8_t GPID_GPC3_ANGLE_L[] GPID_NAME_PAGE = "GPC3 Angle-L";
const int8_t GPID_GPC3_PW_H[] GPID_NAME_PAGE = "GPC3 PW-H";
const int8_t GPID_GPC3_PW_L[] GPID_NAME_PAGE = "GPC3 PW-L";
const int8_t GPID_GPC3_HZ[] GPID_NAME_PAGE = "GPC3 Hz";
const int8_t GPID_GPC3_EDGE_COUNT[] GPID_NAME_PAGE = "GPC3 Edge Count";
const int8_t GPID_GPC4_ANGLE_H[] GPID_NAME_PAGE = "GPC4 Angle-H";
const int8_t GPID_GPC4_ANGLE_L[] GPID_NAME_PAGE = "GPC4 Angle-L";
const int8_t GPID_GPC4_PW_H[] GPID_NAME_PAGE = "GPC4 PW-H";
const int8_t GPID_GPC4_PW_L[] GPID_NAME_PAGE = "GPC4 PW-L";
const int8_t GPID_GPC4_HZ[] GPID_NAME_PAGE = "GPC4 Hz";
const int8_t GPID_GPC4_EDGE_COUNT[] GPID_NAME_PAGE = "GPC4 Edge Count";
const int8_t GPID_GPC5_ANGLE_H[] GPID_NAME_PAGE = "GPC5 Angle-H";
const int8_t GPID_GPC5_ANGLE_L[] GPID_NAME_PAGE = "GPC5 Angle-L";
const int8_t GPID_GPC5_PW_H[] GPID_NAME_PAGE = "GPC5 PW-H";
const int8_t GPID_GPC5_PW_L[] GPID_NAME_PAGE = "GPC5 PW-L";
const int8_t GPID_GPC5_HZ[] GPID_NAME_PAGE = "GPC5 Hz";
const int8_t GPID_GPC5_EDGE_COUNT[] GPID_NAME_PAGE = "GPC5 Edge Count";

/* Descriptions */
const int8_t GPID_ENGINE_ANGLE_AT_GPC1_TRANSITION_HIGH[] GPID_DESC_PAGE = "Engine angle at GPC1 transition(High).";
const int8_t GPID_ENGINE_ANGLE_AT_GPC1_TRANSITION_LOW[] GPID_DESC_PAGE = "Engine angle at GPC1 transition(Low).";
const int8_t GPID_MEASURED_PULSE_WIDTH_ON_GC1_PIN_IN_USEC[] GPID_DESC_PAGE = "Measured pulse-width on GC1 pin, in uSec.";
const int8_t GPID_MEASURED_PULSE_WIDTH_ON_GPC1_PIN_IN_USEC[] GPID_DESC_PAGE = "Measured pulse-width on GPC1 pin, in uSec";
const int8_t GPID_MEASURED_HZ_ON_GPC1_PIN[] GPID_DESC_PAGE = "Measured Hz on GPC1 pin.";
const int8_t GPID_NUMBER_OF_EDGES_SEEN_ON_GPC1_PIN[] GPID_DESC_PAGE = "Number of edges seen on GPC1 pin.";
const int8_t GPID_ENGINE_ANGLE_AT_GPC2_TRANSITION_HIGH[] GPID_DESC_PAGE = "Engine angle at GPC2 transition(high).";
const int8_t GPID_ENGINE_ANGLE_AT_GPC2_TRANSITION_LOW[] GPID_DESC_PAGE = "Engine angle at GPC2 transition(low).";
const int8_t GPID_MEASURED_PULSE_WIDTH_ON_GPC2_PIN_IN_USEC_H[] GPID_DESC_PAGE = "Measured pulse-width on GPC2 pin, in uSec, high part";
const int8_t GPID_MEASURED_PULSE_WIDTH_ON_GPC2_PIN_IN_USEC_L[] GPID_DESC_PAGE = "Measured pulse-width on GPC2 pin, in uSec, low part";
const int8_t GPID_MEASURED_HZ_ON_GPC2_PIN[] GPID_DESC_PAGE = "Measured Hz on GPC2 pin.";
const int8_t GPID_NUMBER_OF_EDGES_SEEN_ON_GPC2_PIN[] GPID_DESC_PAGE = "Number of edges seen on GPC2 pin.";
const int8_t GPID_ENGINE_ANGLE_AT_GPC3_TRANSITION_HIGH[] GPID_DESC_PAGE = "Engine angle at GPC3 transition(high).";
const int8_t GPID_ENGINE_ANGLE_AT_GPC3_TRANSITION_LOW[] GPID_DESC_PAGE = "Engine angle at GPC3 transition(low).";
const int8_t GPID_MEASURED_HIGH_PULSE_WIDTH_ON_A_GPC3_CAPTURE_PIN_IN_USEC[] GPID_DESC_PAGE = "Measured(High) pulse-width on a GPC3 capture pin, in uSec.";
const int8_t GPID_MEASURED_LOW_PULSE_WIDTH_ON_GPC3_PIN_IN_USEC[] GPID_DESC_PAGE = "Measured(Low) pulse-width on GPC3 pin, in uSec";
const int8_t GPID_MEASURED_HZ_ON_GPC3_PIN[] GPID_DESC_PAGE = "Measured Hz on GPC3 pin.";
const int8_t GPID_NUMBER_OF_EDGES_SEEN_ON_GPC3_PIN[] GPID_DESC_PAGE = "Number of edges seen on GPC3 pin.";
const int8_t GPID_ENGINE_ANGLE_AT_GPC4_TRANSITION_HIGH[] GPID_DESC_PAGE = "Engine angle at GPC4 transition(High).";
const int8_t GPID_ENGINE_ANGLE_AT_GPC4_TRANSITION_LOW[] GPID_DESC_PAGE = "Engine angle at GPC4 transition(Low).";
const int8_t GPID_MEASURED_HIGH_PULSE_WIDTH_ON_GPC4_PIN_IN_USEC[] GPID_DESC_PAGE = "Measured(High) pulse-width on GPC4 pin, in uSec.";
const int8_t GPID_MEASURED_LOW_PULSE_WIDTH_ON_GPC4_PIN_IN_USEC[] GPID_DESC_PAGE = "Measured(Low) pulse-width on GPC4 pin, in uSec";
const int8_t GPID_MEASURED_HZ_ON_A_GPC4_CAPTURE_PIN[] GPID_DESC_PAGE = "Measured Hz on a GPC4 capture pin.";
const int8_t GPID_NUMBER_OF_EDGES_SEEN_ON_GPC4_PIN[] GPID_DESC_PAGE = "Number of edges seen on GPC4 pin.";
const int8_t GPID_ENGINE_ANGLE_AT_PIN_TRANSITION_HIGH[] GPID_DESC_PAGE = "Engine angle at pin transition(High).";
const int8_t GPID_ENGINE_ANGLE_AT_PIN_TRANSITION_LOW[] GPID_DESC_PAGE = "Engine angle at pin transition(Low).";
const int8_t GPID_MEASURED_HIGH_PULSE_WIDTH_ON_GPC5_PIN_IN_USEC[] GPID_DESC_PAGE = "Measured(High) pulse-width on GPC5 pin, in uSec.";
const int8_t GPID_MEASURED_PULSE_WIDTH_ON_GPC5_PIN_IN_USEC[] GPID_DESC_PAGE = "Measured pulse-width on GPC5 pin, in uSec";
const int8_t GPID_MEASURED_HZ_ON_GPC5_PIN[] GPID_DESC_PAGE = "Measured Hz on GPC5 pin.";
const int8_t GPID_NUMBER_OF_EDGES_SEEN_ON_GPC5_PIN[] GPID_DESC_PAGE = "Number of edges seen on GPC5 pin.";


#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */

