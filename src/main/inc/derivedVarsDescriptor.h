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

#ifndef FILE_DERIVEDVARSDESCRIPTOR_H_SEEN
#define FILE_DERIVEDVARSDESCRIPTOR_H_SEEN

#include "memory.h"

/* Names */
const int8_t DVD_LOADMAIN[] DVD_NAME_PAGE = "LoadMain";
const int8_t DVD_VEMAIN[] DVD_NAME_PAGE = "VEMain";
const int8_t DVD_LAMBDA[] DVD_NAME_PAGE = "Lambda";
const int8_t DVD_AIRCHARGEMASS[] DVD_NAME_PAGE = "AirChargeMass";
const int8_t DVD_STOICHAFR[] DVD_NAME_PAGE = "StoichAFR";
const int8_t DVD_FUELDENSITY[] DVD_NAME_PAGE = "FuelDensity";
const int8_t DVD_ETE[] DVD_NAME_PAGE = "ETE";
const int8_t DVD_TFCTOTAL[] DVD_NAME_PAGE = "TFCTotal";
const int8_t DVD_DISPLACEMENT[] DVD_NAME_PAGE = "Displacement";
const int8_t DVD_IDT[] DVD_NAME_PAGE = "IDT";
const int8_t DVD_FUEL_PW[] DVD_NAME_PAGE = "Fuel PW";
const int8_t DVD_TIMING_ADVANCE[] DVD_NAME_PAGE = "Timing Advance";
const int8_t DVD_IGNITION_DWELL[] DVD_NAME_PAGE = "Ignition Dwell";

/* Descriptions */
const int8_t DVD_DOCUMENT_LOADMAIN[] DVD_DESC_PAGE = "Document LoadMain";
const int8_t DVD_DOCUMENT_VEMAIN[] DVD_DESC_PAGE = "Doc VEMain";
const int8_t DVD_DOCUMENT_LAMBDA[] DVD_DESC_PAGE = "Doc Lambda";
const int8_t DVD_DOCUMENT_AIRCHARGEMASS[] DVD_DESC_PAGE = "Doc AirChargeMass";
const int8_t DVD_DOCUMENT_STOICHAFR[] DVD_DESC_PAGE = "Doc StoichAFR";
const int8_t DVD_DOCUMENT_FUELDENSITY[] DVD_DESC_PAGE = "Doc FuelDensity";
const int8_t DVD_DOCUMENT_ETE[] DVD_DESC_PAGE = "Document ETE";
const int8_t DVD_DOCUMENT_TFCTOTAL[] DVD_DESC_PAGE = "Document TFCTotal";
const int8_t DVD_DOCUMENT_DISPLACEMENT[] DVD_DESC_PAGE = "Document Displacement";
const int8_t DVD_INJECTOR_DEAD_TIME_TIME_BEFORE_FUEL_FLOW_BEGINS[] DVD_DESC_PAGE = "Injector Dead Time (time before fuel flow begins)";
const int8_t DVD_REFERENCE_PW_IE_ACTUAL_PW_BEFORE_TRIMS_ARE_APPLIED[] DVD_DESC_PAGE = "Reference PW (ie actual PW before trims are applied)";
const int8_t DVD_TOTAL_IGNITION_TIMING_ADVANCE_BTDC[] DVD_DESC_PAGE = "Total Ignition Timing Advance(BTDC)";
const int8_t DVD_IGNITION_DWELL_PERIOD[] DVD_DESC_PAGE = "Ignition Dwell Period";

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */

