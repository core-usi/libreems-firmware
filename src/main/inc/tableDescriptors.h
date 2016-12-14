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


/** @file tableDescriptors.h
 *
 * @ingroup TODO
 *
 * @brief Static strings in flash to avoid wasting/duplicating data in .rodata
 *
 *
 */

#ifndef FILE_TABLEDESCRIPTORS_H_SEEN
#define FILE_TABLEDESCRIPTORS_H_SEEN

#include "memory.h"

/* Table Names */
const int8_t TD_VOLUMETRIC_EFFICIENCY[] TD_NAME_PAGE = "Volumetric Eff.";
const int8_t TD_IAT_VS_IGN[] TD_NAME_PAGE = "IAT vs IGN";
const int8_t TD_CLT_VS_IGN[] TD_NAME_PAGE = "CLT vs IGN";
const int8_t TD_ETHANOL_PERCENT_VS_IGN[] TD_NAME_PAGE = "ETHANOL % vs IGN";
const int8_t TD_EGO_LUT[] TD_NAME_PAGE = "EGO vs Voltage";
const int8_t TD_EGT_LUT[] TD_NAME_PAGE = "EGT vs Voltage";
const int8_t TD_IAT_TRANSFER[] TD_NAME_PAGE = "IAT Transfer";
const int8_t TD_CHT_TRANSFER[] TD_NAME_PAGE = "CHT Transfer";
const int8_t TD_MAT_TRANSFER[] TD_NAME_PAGE = "MAT Transfer";
const int8_t TD_LAMBDA[] TD_NAME_PAGE = "LAMBDA";
const int8_t TD_TIMING[] TD_NAME_PAGE = "Timing";
const int8_t TD_VOLTAGE_VS_DWELL[] TD_NAME_PAGE = "Volts vs Dwell";
const int8_t TD_IDT[] TD_NAME_PAGE = "Inj Dead Time";
const int8_t TD_INJECTOR_PRIMING[] TD_NAME_PAGE = "Injector Priming";
const int8_t TD_ENGINE_TEMPERATURE_ENRICHMENT[] TD_NAME_PAGE = "Engine Temp Enrich";
const int8_t TD_RPM_VS_DWELL[] TD_NAME_PAGE = "RPM vs Dwell";
const int8_t TD_ALPHA_N_VS_SD_BLEND[] TD_NAME_PAGE = "Alpha-N vs SD Blend";
const int8_t TD_MAF_SENSOR_LUT[] TD_NAME_PAGE = "MAF LUT";
const int8_t TD_AAP_SENSOR_LUT[] TD_NAME_PAGE = "AAP LUT";
const int8_t TD_MAP_SENSOR_LUT[] TD_NAME_PAGE = "MAP LUT";
const int8_t TD_RPM_LIMIT[] TD_NAME_PAGE = "RPM Limit";
const int8_t TD_IAC_STEPS[] TD_NAME_PAGE = "IAC Steps";
const int8_t TD_FUEL_PERCENT[] TD_NAME_PAGE = "Fuel %";
const int8_t TD_TEMP_VS_ASE[] TD_NAME_PAGE = "Afterstart Enrich %";

/* Table Descriptions */
const int8_t TD_RPM_VS_MAP_VE_TABLE[] TD_DESC_PAGE = "RPM vs MAP VE Table";
const int8_t TD_INTAKE_AIR_TEMPERATURE_VS_IGNITION_OFFSET[] TD_DESC_PAGE = "Intake Air Temp vs Ign offset";
const int8_t TD_ENGINE_TEMPERATURE_CLT_VS_IGNITION_OFFSET[] TD_DESC_PAGE = "Engine Temp(CLT) vs Ign offset";
const int8_t TD_ETHANOL_PERCENTAGE_VS_IGNITION_OFFSET[] TD_DESC_PAGE = "Ethanol % vs Ign offset";
const int8_t TD_INTAKE_AIR_TEMPERATURE_SENSOR_TABLE[] TD_DESC_PAGE = "Intake Air Temp Sensor Table";
const int8_t TD_COOLANT_OR_HEAD_TEMPERATURE_SENSOR_TABLE[] TD_DESC_PAGE = "Coolant or Head Temp Sensor Table";
const int8_t TD_MANIFOLD_AIR_TEMPERATURE_SENSOR_TABLE[] TD_DESC_PAGE = "Manifold Temp Sensor Table";
const int8_t TD_LAMBDA_VS_LOAD[] TD_DESC_PAGE = "Lambda vs Load";
const int8_t TD_TIMING_VS_LOAD[] TD_DESC_PAGE = "Timing vs Load";
const int8_t TD_INJECTOR_DEAD_TIME_VS_VOLTAGE[] TD_DESC_PAGE = "Injector Dead Time vs Volts";
const int8_t TD_ENGINE_TEMP_VS_VOLUME_FIXME_SHOULD_NOT_BE_IN_PW[] TD_DESC_PAGE = "Engine Temp vs Volume FIXME SHOULD NOT BE IN PW";
const int8_t TD_ENGINE_TEMP_VS_FUEL_SCALER[] TD_DESC_PAGE = "Engine Temp vs Fuel Scaler";
const int8_t TD_RPM_VS_MAX_IGNTION_DWELL[] TD_DESC_PAGE = "RPM vs Max Ign Dwell";
const int8_t TD_SPEEDDENSITY_LOAD_PERCENT_OVER_ALPHA_N_VS_RPM[] TD_DESC_PAGE = "SpeedDensity load % over Alpha-n vs RPM";
const int8_t TD_MAF_VS_VOLTAGE_LUT[] TD_DESC_PAGE = "MAF vs Volts LUT";
const int8_t TD_AAP_VS_VOLTAGE[] TD_DESC_PAGE = "AAP vs Volts";
const int8_t TD_MAP_VS_VOLTAGE_SENSOR_LOOKUP[] TD_DESC_PAGE = "MAP vs Volts sensor lookup";
const int8_t TD_ENGINE_TEMPERATURE_VS_RPM_LIMIT[] TD_DESC_PAGE = "Engine Temp vs RPM limit";
const int8_t TD_RPM_VS_IAC_STEPS[] TD_DESC_PAGE = "RPM vs IAC steps";
const int8_t TD_FUEL_SCALER_VS_DELTA_ENRICHMENT[] TD_DESC_PAGE = "Fuel scaler vs delta enrichment";
const int8_t TD_EGO_VS_LAMBDA[] TD_DESC_PAGE = "EGO sensor LUT";

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */

