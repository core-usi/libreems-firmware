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

#define FIELDDESCRIPTOR_C

#include <stddef.h>

//#include "inc/typeChecks.h"
#include "inc/freeEMS.h"
#include "inc/dataLogDefinitions.h"
#include "inc/fieldDescriptor.h"
#include "inc/libreDefs.h"
#include "inc/memory.h"
#include "inc/shared/libreExternalTypes.h"


const FieldDescriptor fieldDescriptor[] FD_BASE_PAGE = {
  {
    .ID = UNDEF_DID,
    .isSigned = 0,
    .name = NAME_UNDEFINED,
    .description = FD_UNDEFINED_TABLE_FOUND,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = U8_DID,
    .bitsize = sizeof(uint8_t) * 8,
    .isSigned = 0,
    .name = NAME_UNSIGNED_8_BIT,
    .description = FD_0_255_UNSIGNED_DATA,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = U16_DID,
    .isSigned = 0,
    .name = NAME_UNSIGNED_16_BIT,
    .description = FD_0_65535_UNSIGNED_DATA,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = EXT_DID,
    .bitsize = sizeof(ExtendedTime) * 8,
    .isSigned = 0,
    .name = NAME_UNSIGNED_32_BIT,
    .description = FD_0_0XFFFFFFFF_UNSIGNED_DATA,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = U32_DID,
    .bitsize = sizeof(uint32_t) * 8,
    .isSigned = 0,
    .name = NAME_UNSIGNED_32_BIT,
    .description = FD_0_0XFFFFFFFF_UNSIGNED_DATA,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = IAT_DID,
    .isSigned = 0,
    .name = NAME_IAT,
    .description = FD_INLET_AIR_TEMPERATURE_CELSIUS,
    .multiplier = MULT_001,
    .adder = ADD_27315,
    .flags = "",
    .suffix = SFX_DEGREES,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = IT_DID,
    .isSigned = 0,
    .name = NAME_TIMING_TABLE_ENTRY,
    .description = FD_ADVANCE_IN_DEGREES_BTDC,
    .multiplier = MULT_05,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_DEGREES,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = CHT_DID,
    .isSigned = 0,
    .name = NAME_CHT,
    .description = FD_COOLANT_OR_HEAD_TEMPERATURE_CELSIUS,
    .multiplier = MULT_001,
    .adder = ADD_27315,
    .flags = "",
    .suffix = SFX_DEGREES,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = TPS_DID,
    .isSigned = 0,
    .name = NAME_TPS,
    .description = FD_THROTTLE_POSITION_SENSOR,
    .multiplier = MULT_00015625,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_PERCENT,
  },
  {
    .ID = EGO_DID,
    .isSigned = 0,
    .name = NAME_EGO,
    .description = FD_EXHAUST_GAS_OXYGEN_LAMBDA,
    .multiplier = MULT_00000305175781,
    .adder = ADD_0,
    .flags = "",
    .suffix = "lambda",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = MAP_DID,
    .isSigned = 0,
    .name = NAME_MAP,
    .description = FD_MANIFOLD_ABSOLUTE_PRESSURE,
    .multiplier = MULT_001,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_KPA,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = AAP_DID,
    .isSigned = 0,
    .name = NAME_AAP,
    .description = FD_ATMOSPHERE_ABSOLUTE_PRESSURE,
    .multiplier = MULT_001,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_KPA,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = BRV_DID,
    .isSigned = 0,
    .name = NAME_BRV,
    .description = FD_BATTERY_REFERENCE_VOLTAGE,
    .multiplier = MULT_0001,
    .adder = ADD_0,
    .flags = "",
    .suffix = NAME_VOLTS,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = MAT_DID,
    .isSigned = 0,
    .name = NAME_MAT,
    .description = FD_MANIFOLD_AIR_TEMPERATURE,
    .multiplier = MULT_001,
    .adder = ADD_0,
    .flags = "temperature",
    .suffix = SFX_DEGREES,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = EGT_DID,
    .isSigned = 0,
    .name = NAME_EGT,
    .description = FD_EXHAUST_GAS_TEMPERATURE,
    .multiplier = MULT_004,
    .adder = ADD_0,
    .flags = "",
    .suffix = "C",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = GS_DID,
    .isSigned = 0,
    .bitsize = sizeof(uint32_t) * 8,
    .name = NAME_GRAMS_SECOND,
    .description = FD_AIRFLOW_IN_GRAMS_PER_SECOND,
    .multiplier = MULT_000000083333,
    .adder = ADD_0,
    .flags = "",
    .suffix = "g",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = IAP_DID,
    .isSigned = 0,
    .name = NAME_IAP,
    .description = FD_INTERCOOLER_ABSOLUTE_PRESSURE,
    .multiplier = MULT_001,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_KPA,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = MAF_DID,
    //.bitsize =  //TODO change to 32-bit lookup value
    .isSigned = 0,
    .name = NAME_MAF_VOLTAGE,
    .description = FD_MASS_AIR_FLOW,
    .multiplier = MULT_00048828125,
    .adder = ADD_0,
    .flags = "",
    .suffix = "raw",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = DMAP_DID,
    .isSigned = 0,
    .name = NAME_DMAP,
    .description = FD_MAP_RATE_OF_CHANGE,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "kPa/second",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = DTPS_DID,
    .isSigned = 0,
    .name = NAME_DTPS,
    .description = FD_TPS_RATE_OF_CHANGE,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "%/second",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = RPM_DID,
    .isSigned = 0,
    .name = NAME_RPM,
    .description = FD_INSTANT_ENGINE_RPM,
    .multiplier = MULT_05,
    .adder = ADD_0,
    .flags = "",
    .suffix = NAME_RPM,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = FP_DID,
    .isSigned = 0,
    .name = NAME_FUEL_PRESSURE,
    .description = FD_FUEL_PRESSURE_KPA,
    .multiplier = MULT_001,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_KPA,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = EP_DID,
    .isSigned = 0,
    .name = NAME_ETHANOLPERCENTAGE,
    .description = FD_PERCENTAGE_OF_ETHANOL_IN_YOUR_FUEL,
    .multiplier = MULT_05,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_PERCENT,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = ANG_DID,
    .isSigned = 0,
    .name = NAME_ENGINE_ANGLE,
    .description = FD_ENGINE_ANGLE_0_720,
    .multiplier = MULT_002,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = PW_DID,
    .isSigned = 0,
    .name = NAME_USEC,
    .description = FD_PULSEWIDTH_IN_USEC,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = HZ_DID,
    .isSigned = 0,
    .name = NAME_HZ,
    .description = FD_MEASURED_FREQUENCY,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = LD_DID,
    .isSigned = 0,
    .name = NAME_LOADMAIN,
    .description = FD_ALGORITHM_DEPENDENT_REPRESENTATION_OF_ENGINE_LOAD,
    .multiplier = MULT_001,
    .adder = ADD_0,
    .flags = "",
    .suffix = "Load",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = VE_DID,
    .isSigned = 0,
    .name = NAME_VEMAIN,
    .description = FD_CURRENT_VOLUMETRIC_EFFICIENCY,
    .multiplier = MULT_0001953125,
    .adder = ADD_0,
    .flags = "",
    .suffix = "VE %",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = LMB_DID,
    .isSigned = 0,
    .name = NAME_LAMBDA,
    .description = FD_DESIRED_LAMBDA,
    .multiplier = MULT_00000305175781,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = ACM_DID,
    .isSigned = 0,
    .name = NAME_AIRFLOW,
    .description = FD_ALGORITHM_INDEPENDENT_AIRFLOW_CALCULATION,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = SAR_DID,
    .isSigned = 0,
    .name = NAME_STOICHAFR,
    .description = FD_CALCULATED_AFR_IE_FLEX_FUEL_OR_FIXED_FUEL,
    .multiplier = MULT_0001,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = FDN_DID,
    .isSigned = 0,
    .name = NAME_FUELDENSITY,
    .description = FD_CALCULATED_FUEL_DENSITY,
    .multiplier = MULT_00008,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_MS,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = ETE_DID,
    .isSigned = 0,
    .name = NAME_ETE,
    .description = FD_ENGINE_TEMPERATURE_ENRICHMENT_PERCENTAGE,
    .multiplier = MULT_000610360875,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_PERCENT,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = TFC_DID,
    .isSigned = 1,
    .name = NAME_TFCTOTAL,
    .description = FD_TRANSIENT_FUEL_CORRECTION_PW,
    .multiplier = MULT_00008,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_MS,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = DPM_DID,
    .isSigned = 0,
    .name = NAME_DISPLACEMENT,
    .description = FD_DISPLACEMENT_PER_COMBUSTION_UNIT_CYL,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "CC",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = PW_M_DID,
    .isSigned = 0,
    .name = NAME_REFPW,
    .description = FD_REFERENCE_PW_IE_ACTUAL_PW_BEFORE_TRIMS_ARE_APPLIED,
    .multiplier = MULT_00008,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_MS,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = CNS_DID,
    .isSigned = 0,
    .bitsize = bitSize(KeyUserDebug, canStatus),
    .name = NAME_CAN_STATUS_BITS,
    .description = FD_CAN_BUS_STATUS_BITS,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
    .bitFieldDescription = {
      {
        .fieldName = SFX_INITAK_FIRST,
        .bitPosition = 2
      },
      {
        .fieldName = SFX_INITAK_SECOND,
        .bitPosition = 1
      },
      {
        .fieldName = SFX_CAN_BUS_SYNC,
        .bitPosition = 0
      }
    },
  },
  {
    .ID = CSA_DID,
    .bitsize = bitSize(KeyUserDebug, coreStatusA),
    .isSigned = 0,
    .name = NAME_CORESTATUSA,
    .description = FD_STATUS_BITS_REGISTER_A,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {
      {
        .fieldName = SFX_FUELPUMPPRIME,
        .bitPosition = 0
      }
    }
  },
  {
    .ID = SFL_DID,
    .bitsize = bitSize(KeyUserDebug, flaggableFlags),
    .isSigned = 0,
    .name = NAME_FLAGGABLEFLAGS,
    .description = FD_COUNTER_INCREMENTED_STATUS_BITS_FOR_VARIOUS_THINGS_LIKE_COMMS_AND_DECODERS_ETC,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {
      {
        .fieldName = SFX_SERIALPACKETSUNDERLENGTH,
        .bitPosition = 13
      },
      {
        .fieldName = SFX_SERIALCHECKSUMMISMATCHES,
        .bitPosition = 12
      },
      {
        .fieldName = SFX_SERIALPACKETSOVERLENGTH,
        .bitPosition = 11
      },
      {
        .fieldName = SFX_SERIALSTARTSINSIDEAPACKET,
        .bitPosition = 10
      },
      {
        .fieldName = SFX_SERIALESCAPEPAIRMISMATCHES,
        .bitPosition = 9
      },
      {
        .fieldName = SFX_SERIALOVERRUNERRORS,
        .bitPosition = 8
      },
      {
        .fieldName = SFX_SERIALPARITYERRORS,
        .bitPosition = 7
      },
      {
        .fieldName = SFX_SERIALFRAMINGERRORS,
        .bitPosition = 6
      },
      {
        .fieldName = SFX_SERIALNOISEERRORS,
        .bitPosition = 5
      },
      {
        .fieldName = SFX_DECODERSYNCSTATECLEARS,
        .bitPosition = 4
      },
      {
        .fieldName = SFX_DECODERSYNCCORRECTIONS,
        .bitPosition = 3
      },
      {
        .fieldName = SFX_DECODERSYNCLOSSES,
        .bitPosition = 2
      },
      {
        .fieldName = SFX_LOWVOLTAGECONDITIONS,
        .bitPosition = 1
      },
      {
        .fieldName = SFX_CALLSTOUNIMPLMENTEDISRS,
        .bitPosition = 0
      }
    }
  },
  {
    .ID = PC_H_DID,
    .isSigned = 0,
    .name = NAME_PERCENT,
    .description = FD_PERCENT_IN_HUNDREDTHS,
    .multiplier = MULT_001,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    /* There is a system-wide problem with the factor for this,
     * we inherited a factor that will not fully cover our 720deg
     * range, when using signed. Value should be less than 700deg
     * at all times. TODO fix this!
     */
    .ID = ANG_OFFSET_DID,
    .isSigned = 1,
    .name = NAME_ANGLE_OFFSET,
    .description = FD_ENGINE_ANGLE_OFFSET_IN_HUNDREDTHS,
    .multiplier = MULT_002,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = CMS_DID,
    .isSigned = 0,
    .name = NAME_CLOCKINMILLISECONDS,
    .description = FD_INTERNAL_CLOCK_IN_MILLISECONDS,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = SFX_MS,
    .bitFieldDescription = {{0}},
  },
  {
    .ID = AV_DID,
    .isSigned = 0,
    .name = NAME_VOLTS,
    .description = FD_ANALOG_VOLTAGE_0_5V,
    .multiplier = MULT_00048828125,
    .adder = ADD_0,
    .flags = "",
    .suffix = "v",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = ICB_DID,
    .bitsize = bitSize(KeyUserDebug, ignitionCuts),
    .isSigned = 0,
    .name = NAME_IGNITION_CUT_BITS,
    .description = FD_BIT_FIELD_OF_REASONS_WHY_IGNITION_WAS_CUT,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {
      {
        .fieldName = SFX_IGNITIONCUROVERBOOST,
        .bitPosition = 1
      },
      {
        .fieldName = SFX_IGNITIONCUTOVERRPM,
        .bitPosition = 0
      }
    }
  },
  {
    .ID = IJB_DID,
    .bitsize = bitSize(KeyUserDebug, injectionCuts),
    .isSigned = 0,
    .name = NAME_INJECTIONCUTS,
    .description = FD_BIT_FIELD_OF_REASONS_WHY_INJECTION_WAS_CUT,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {
      {
        .fieldName = SFX_INJECTIONLOSTSELFCLOCK,
        .bitPosition = 3
      },
      {
        .fieldName = SFX_INJECTIONLOSTPLLSYNC,
        .bitPosition = 2
      },
      {
        .fieldName = SFX_INJECTIONCUTOVERBOOST,
        .bitPosition = 1
      },
      {
        .fieldName = SFX_INJECTIONCUTOVERRPM,
        .bitPosition = 0
      }
    }
  },
  {
    .ID = PC_D_DID,
    .isSigned = 0,
    .name = NAME_PRIMARY_DECODER_ISR_VARIANCE,
    .description = FD_VARIANCE_IN_TEETH_IN_SCALED_PERCENT,
    .multiplier = MULT_000153054977,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {{0}},
  },
  {
    .ID = DCF_DID,
    .bitsize = bitSize(DecoderStats, decoderFlags),
    .isSigned = 0,
    .name = NAME_DECODER_FLAGS,
    .description = FD_FLAGS_REPRESENTING_VARIOUS_DECODER_STATES,
    .multiplier = MULT_1,
    .adder = ADD_0,
    .flags = "",
    .suffix = "",
    .bitFieldDescription = {
      {
        .fieldName = SFX_PREVIOUSSECONDARYEVENTVALID,
        .bitPosition = 5
      },
      {
        .fieldName = SFX_PRIMARYPERIODVALID,
        .bitPosition = 4
      },
      {
        .fieldName = SFX_PREVIOUSPRIMARYEVENTVALID,
        .bitPosition = 3
      },
      {
        .fieldName = SFX_CAMLOCK,
        .bitPosition = 2
      },
      {
        .fieldName = SFX_CRANKLOCK,
        .bitPosition = 1
      },
      {
        .fieldName = SFX_MINIMALLOCK,
        .bitPosition = 0
      }
    },
  }
};


const uint8_t fieldDescriptorCnt = (sizeof(fieldDescriptor) / sizeof(FieldDescriptor));

/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
