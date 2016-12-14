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

#define TABLEDESCRIPTORS_C

#include <stddef.h>

//#include "inc/typeChecks.h"
#include "inc/freeEMS.h"
#include "inc/dataLogDefinitions.h"
#include "inc/libreDefs.h"
#include "inc/memory.h"
#include "inc/tableDescriptors.h"
#include "inc/shared/libreExternalTypes.h"


const TableDescriptor tableDescriptor[] TD_BASE_PAGE = {
  {
    .tableKey     = VE_TID,
    .tableName    = TD_VOLUMETRIC_EFFICIENCY,
    .tableDesc    = TD_RPM_VS_MAP_VE_TABLE,
    .formatID     = TABLE_3D,
    .xAxisID      = RPM_DID,
    .xHighLightID = RPM_DID,
    .yAxisID      = MAP_DID,
    .yHighLightID = MAP_DID,
    .lookupID     = VE_DID,
  },
  {
    .tableKey  = IAT_VS_IGN_TID,
    .tableName = TD_IAT_VS_IGN,
    .tableDesc = TD_INTAKE_AIR_TEMPERATURE_VS_IGNITION_OFFSET,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = IAT_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = ANG_OFFSET_DID
  },
  {
    .tableKey  = CHT_VS_IGN_TID,
    .tableName = TD_CLT_VS_IGN,
    .tableDesc = TD_ENGINE_TEMPERATURE_CLT_VS_IGNITION_OFFSET,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = CHT_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = ANG_OFFSET_DID
  },
  {
    .tableKey  = ETHANOL_PERCENT_VS_IGN_TID,
    .tableName = TD_ETHANOL_PERCENT_VS_IGN,
    .tableDesc = TD_ETHANOL_PERCENTAGE_VS_IGNITION_OFFSET,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = EP_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = ANG_OFFSET_DID
  },
  {
    .tableKey  = IAT_TRANSFER_TID,
    .tableName = TD_IAT_TRANSFER,
    .tableDesc = TD_INTAKE_AIR_TEMPERATURE_SENSOR_TABLE,
    .formatID  = TABLE_1D,
    .xAxisID   = NULL_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = IAT_DID
  },
  {
    .tableKey  = CHT_TRANSFER_TID,
    .tableName = TD_CHT_TRANSFER,
    .tableDesc = TD_COOLANT_OR_HEAD_TEMPERATURE_SENSOR_TABLE,
    .formatID  = TABLE_1D,
    .xAxisID   = NULL_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = CHT_DID
  },
  {
    .tableKey  = MAT_TRANSFER_TID,
    .tableName = TD_MAT_TRANSFER,
    .tableDesc = TD_MANIFOLD_AIR_TEMPERATURE_SENSOR_TABLE,
    .formatID  = TABLE_1D,
    .xAxisID   = NULL_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = MAT_DID
  },
  {
    .tableKey  = LAMBDA_VS_LOAD_TID,
    .tableName = TD_LAMBDA,
    .tableDesc = TD_LAMBDA_VS_LOAD,
    .formatID  = TABLE_3D,
    .xAxisID   = RPM_DID,
    .yAxisID   = MAP_DID,    //TODO change to load in %
    .lookupID  = LMB_DID,
  },
  {
    .tableKey  = IGNITION_ADVANCE_TID,
    .tableName = TD_TIMING,
    .tableDesc = TD_TIMING_VS_LOAD,
    .formatID  = TABLE_3D,
    .xAxisID   = RPM_DID,
    .yAxisID   = MAP_DID,    //TODO change to load in %
    .lookupID  = IT_DID
  },
  {
    .tableKey  = VOLTAGE_VS_DWELL_TID,
    .tableName = TD_VOLTAGE_VS_DWELL,
    .tableDesc = TD_VOLTAGE_VS_DWELL,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = BRV_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = PW_M_DID
  },
  {
    .tableKey  = INJECTOR_DEAD_TIME_VS_VOLTAGE_TID,
    .tableName = TD_IDT,
    .tableDesc = TD_INJECTOR_DEAD_TIME_VS_VOLTAGE,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = BRV_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = PW_M_DID
  },
  {
    .tableKey  = TEMP_VS_INJECTOR_PRIMING_TID,
    .tableName = TD_INJECTOR_PRIMING,
    .tableDesc = TD_ENGINE_TEMP_VS_VOLUME_FIXME_SHOULD_NOT_BE_IN_PW,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = CHT_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = PW_M_DID
  },
  {
    .tableKey  = ENGINE_TEMP_ENRICHMENT_TID,
    .tableName = TD_ENGINE_TEMPERATURE_ENRICHMENT,
    .tableDesc = TD_ENGINE_TEMP_VS_FUEL_SCALER,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = CHT_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = ETE_DID
  },
  {
    .tableKey  = RPM_VS_DWELL_TID,
    .tableName = TD_RPM_VS_DWELL,
    .tableDesc = TD_RPM_VS_MAX_IGNTION_DWELL,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = RPM_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = PW_M_DID
  },
  {
    .tableKey  = RPM_VS_BLEND_TID,
    .tableName = TD_ALPHA_N_VS_SD_BLEND,
    .tableDesc = TD_SPEEDDENSITY_LOAD_PERCENT_OVER_ALPHA_N_VS_RPM,
    .formatID  = TABLE_2D_STRUCTURED,
    .xAxisID   = RPM_DID,
    .yAxisID   = NULL_DID,
    .lookupID  = LMB_DID
  },
  {
    .tableKey   = MAF_VS_VOLTAGE_TID,
    .tableName  = TD_MAF_SENSOR_LUT,
    .tableDesc  = TD_MAF_VS_VOLTAGE_LUT,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = AV_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = GS_DID
  },
  {
    .tableKey   = AAP_VS_VOLTAGE_TID,
    .tableName  = TD_AAP_SENSOR_LUT,
    .tableDesc  = TD_AAP_VS_VOLTAGE,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = AV_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = AAP_DID
  },
  {
    .tableKey   = MAP_VS_VOLTAGE_TID,
    .tableName  = TD_MAP_SENSOR_LUT,
    .tableDesc  = TD_MAP_VS_VOLTAGE_SENSOR_LOOKUP,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = AV_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = MAP_DID
  },
  {
    .tableKey   = RPM_LIMIT_VS_TEMPERATURE_TID,
    .tableName  = TD_RPM_LIMIT,
    .tableDesc  = TD_ENGINE_TEMPERATURE_VS_RPM_LIMIT,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = RPM_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = CHT_DID
  },
  {
    .tableKey   = RPM_VS_IAC_STEPS_TID,
    .tableName  = TD_IAC_STEPS,
    .tableDesc  = TD_RPM_VS_IAC_STEPS,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = RPM_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = U16_DID
  },
  {
    .tableKey   = FUEL_DELTA_VS_PERCENT_ADDER_TID,
    .tableName  = TD_FUEL_PERCENT,
    .tableDesc  = TD_FUEL_SCALER_VS_DELTA_ENRICHMENT,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = PC_H_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = PC_H_DID
  },
  {
    .tableKey   = EGO_VS_LAMBDA_TID,
    .tableName  = TD_EGO_LUT,
    .tableDesc  = TD_EGO_VS_LAMBDA,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = AV_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = LMB_DID
  },
  {
    .tableKey   = EGT_VS_VOLTAGE_TID,
    .tableName  = TD_EGT_LUT,
    .tableDesc  = TD_EGT_LUT,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = AV_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = EGT_DID
  },
  {
    .tableKey   = TEMP_VS_ASE_PERCENT_TID,
    .tableName  = TD_TEMP_VS_ASE,
    .tableDesc  = TD_TEMP_VS_ASE,
    .formatID   = TABLE_2D_STRUCTURED,
    .xAxisID    = CHT_DID,
    .yAxisID    = NULL_DID,
    .lookupID   = ETE_DID
  },

};

const uint8_t tableDescriptorCnt = (sizeof(tableDescriptor) / sizeof(TableDescriptor));
