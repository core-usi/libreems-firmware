/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2015 Sean Keys
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
 * @ingroup External headers
 *
 */

#ifndef FILE_EXTERNAL_TYPES_H_SEEN
#define FILE_EXTERNAL_TYPES_H_SEEN

#include <stdint.h>
/*
 * TODO these enums should replace the IDs used in the COMMS switch/case block.
 */
typedef enum {
  VE_TID                            =  0,
  IAT_VS_IGN_TID                    =  1,
  IAT_TRANSFER_TID                  =  2,
  CHT_TRANSFER_TID                  =  3,
  LAMBDA_VS_LOAD_TID                =  4,
  IGNITION_ADVANCE_TID              =  5,
  VOLTAGE_VS_DWELL_TID              =  6,
  INJECTOR_DEAD_TIME_VS_VOLTAGE_TID =  7,
  TEMP_VS_INJECTOR_PRIMING_TID      =  8,
  ENGINE_TEMP_ENRICHMENT_TID        =  9,
  RPM_VS_DWELL_TID                  = 10,
  RPM_VS_BLEND_TID                  = 11,
  AIRFLOW_VS_TPS_TID                = 12,
  MAF_VS_VOLTAGE_TID                = 13,
  CHT_VS_IGN_TID                    = 14,
  ETHANOL_PERCENT_VS_IGN_TID        = 15,
  AAP_VS_VOLTAGE_TID                = 16,
  MAP_VS_VOLTAGE_TID                = 17,
  RPM_LIMIT_VS_TEMPERATURE_TID      = 18,
  RPM_VS_IAC_STEPS_TID              = 19,
  FUEL_DELTA_VS_PERCENT_ADDER_TID   = 20,
  EGO_VS_LAMBDA_TID                 = 21,
  EGT_VS_VOLTAGE_TID                = 22,
  TEMP_VS_ASE_PERCENT_TID           = 23,

  UNDEF_TABLE_FORMAT   = 255
}TableDescriptorID;

typedef enum {
  TABLE_FORMAT_UNHANDLED  = 0,
  TABLE_FORMAT_UNDEFINED  = 1,

  TABLE_1D                = 5,
  TABLE_2D_STRUCTURED     = 10,
  TABLE_2D_LEGACY         = 11,

  TABLE_3D                = 12,

  TABLE_FORMAT_NOT_FOUND  = 255
}TableFormatID;

typedef enum {
  NULL_DID       = 0,
  U16_DID        = 10,
  U8_DID         = 11,
  U32_DID        = 12,

  IAT_DID        = 20,
  CHT_DID        = 21,
  TPS_DID        = 22,
  EGO_DID        = 23,
  MAP_DID        = 24,
  AAP_DID        = 25,
  BRV_DID        = 26,
  MAT_DID        = 27,
  EGT_DID        = 28,
  IAP_DID        = 29,
  MAF_DID        = 30,
  DMAP_DID       = 31,
  DTPS_DID       = 32,
  RPM_DID        = 33,
  FP_DID         = 34,
  EP_DID         = 35,
  ANG_DID        = 36,
  PW_DID         = 37,
  HZ_DID         = 38,
  LD_DID         = 39,
  VE_DID         = 40,
  LMB_DID        = 41,
  ACM_DID        = 42,
  SAR_DID        = 43,
  FDN_DID        = 44,
  ETE_DID        = 45,
  TFC_DID        = 46,
  DPM_DID        = 47,
  PW_M_DID       = 49,
  CNS_DID        = 50,
  CSA_DID        = 51,
  SFL_DID        = 52,
  PC_H_DID       = 53,
  CMS_DID        = 54,
  ICB_DID        = 55,
  IJB_DID        = 56,
  PC_D_DID       = 57,
  DCF_DID        = 58,
  EXT_DID        = 59,
  IT_DID         = 60,
  ANG_OFFSET_DID = 61,
  AV_DID         = 62,
  GS_DID         = 63,

  NOT_USED_DID   = 254,
  UNDEF_DID      = 255,
}ScalarDescriptorID;

typedef enum {
  CRANK_ONLY    = 1,
  CRANK_AND_CAM = 2
}MinimalSyncLevel;

#endif
