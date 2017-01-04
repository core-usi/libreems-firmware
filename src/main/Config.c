/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014 Sean Keys, David Andruczyk
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
 * @ingroup Configuration
 *
 * @brief Primary config file system initialization.
 *
 *
 */

#include "inc/Configuration.h"
#include "inc/dataCalculation.h"
#include "inc/libreMath.h"
#include "inc/shared/libreExternalTypes.h"

MasterConfig Config CONFIG_DATA = {
    .tachDecoderSettings = {
        .inputEventTollerance         = TACH_INPUT_RATIO(PRIMARY_INPUT_TOLLERANCE),
        .inputEventCrankingTollerance = TACH_INPUT_RATIO(PRIMARY_INPUT_TOLLERANCE_CRANKING),
        .primaryEventSkipEdges        = PRIMARY_SKIP_EDGES,
        .maxCrankingRPM               = RPM_S(MAX_RPM_CRANKING),
        .filterBypassRPM              = RPM_S(FILTER_ENABLE_RPM),
        .minimalSyncRequired          = (uint8_t)MIN_SYNC_REQUIRED
    },
    .numberOfPrecisionOutputs             = NUM_OF_PRECISON_OUTPUTS,
    .numberOfDerateLevels                 = SPECIFIED_OPERATING_LEVELS,
    .sensorProperties = {
        .MAPMinimum = KPA_S(MAP_MINIMUM),
        .MAPMaximum = KPA_S(MAP_MAXIMUM),
        .TPSMinimum = TPS_MINIMUM,
        .TPSMaximum = TPS_MAXIMUM
    },
    .inputCaptureSettings = {
/* Bit setting seems to be broken for a union */
//      .inputCaptureEdgesTCTL4.bits = {
//          .ECT0captureRising  = ECT0_CAPTURE_RISING,
//          .ECT0captureFalling = ECT0_CAPTURE_FALLING,
//          .ECT1captureRising  = ECT1_CAPTURE_RISING,
//          .ECT1captureFalling = ECT1_CAPTURE_FALLING,
//          .ECT2captureRising  = ECT2_CAPTURE_RISING,
//          .ECT2captureFalling = ECT2_CAPTURE_FALLING,
//          .ECT3captureRising  = ECT3_CAPTURE_RISING,
//          .ECT3captureFalling = ECT3_CAPTURE_FALLING,
//      },
      .inputCaptureEdgesTCTL4.value =
        (ECT0_CAPTURE_RISING << 0) | (ECT0_CAPTURE_FALLING << 1) |
        (ECT1_CAPTURE_RISING << 2) | (ECT1_CAPTURE_FALLING << 3) |
        (ECT2_CAPTURE_RISING << 4) | (ECT2_CAPTURE_FALLING << 5) |
        (ECT3_CAPTURE_RISING << 6) | (ECT3_CAPTURE_FALLING << 7),
      .inputCaptureEdgesTCTL3.value =
        (ECT4_CAPTURE_RISING << 0) | (ECT4_CAPTURE_FALLING << 1) |
        (ECT5_CAPTURE_RISING << 2) | (ECT5_CAPTURE_FALLING << 3) |
        (ECT6_CAPTURE_RISING << 4) | (ECT6_CAPTURE_FALLING << 5) |
        (ECT7_CAPTURE_RISING << 6) | (ECT7_CAPTURE_FALLING << 7),
/* Bit setting seems to be broken for a union */
//      .inputCaptureEdgesTCTL3.bits = {
//            .ECT4captureRising  = ECT4_CAPTURE_RISING,
//          .ECT4captureFalling = ECT4_CAPTURE_FALLING,
//          .ECT5captureRising  = ECT5_CAPTURE_RISING,
//          .ECT5captureFalling = ECT5_CAPTURE_FALLING,
//          .ECT6captureRising  = ECT6_CAPTURE_RISING,
//          .ECT6captureFalling = ECT6_CAPTURE_FALLING,
//            .ECT7captureRising  = ECT7_CAPTURE_RISING,
//              .ECT7captureFalling = ECT7_CAPTURE_FALLING,
//      },
    },
    .idleControl = {
      .IdleTypeID    = IDLE_TYPE,
      .TotalIACsteps = IDLE_IAC_STEPS,
      .IACpwLength   = IDLE_IAC_PW,
      .StepperCH0num = IDLE_IAC_CHA,
      .StepperCH1num = IDLE_IAC_CHB,
      .PWMchannel    = PWM_CHANNEL,
    },
    .mechanicalProperties = {
        .perCylinderVolume       = ENGINE_CYL_VOLUME,
        .cylinderCount           = ENGINE_CYLINDER_COUNT,
        .revoloutionsPerCycle    = CRANKSHAFT_REVS_PER_CYCLE,
        .decoderInputAngleOffset = INPUT_OFFSET
    },
    .CylinderSetup[0] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_1_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_1_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_1_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_1_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_1_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_1_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[0]
    },
    .CylinderSetup[1] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_2_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_2_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_2_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_2_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_2_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_2_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[1]
    },
    .CylinderSetup[2] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_3_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_3_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_3_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_3_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_3_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_3_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[2]
    },
    .CylinderSetup[3] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_4_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_4_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_4_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_4_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_4_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_4_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[3]
    },

    .CylinderSetup[4] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_5_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_5_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_5_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_5_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_5_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_5_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[4]
    },
    .CylinderSetup[5] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_6_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_6_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_6_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_6_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_6_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_6_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[5]
    },
    .CylinderSetup[6] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_7_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_7_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_7_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_7_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_7_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_7_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[6]
    },
    .CylinderSetup[7] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_8_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_8_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_8_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_8_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_8_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_8_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[7]
    },
    .CylinderSetup[8] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_9_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_9_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_9_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_9_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_9_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_9_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[8]
    },
    .CylinderSetup[9] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_10_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_10_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_10_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_10_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_10_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_10_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[9]
    },
    .CylinderSetup[10] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_11_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_11_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_11_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_11_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_11_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_11_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[10]
    },
    .CylinderSetup[11] = {
            .TDCAngle           = ENGINE_ANGLE_S(CYL_12_TDC_ANGLE),
            .InjectionAngle     = ENGINE_ANGLE_S(CYL_12_INJ_ANGLE),
            .ReadAngle          = ENGINE_ANGLE_S(CYL_12_READ_ANGLE),
            .igntionEvent       = &outputSchedules[CYL_12_IGN_CH],
            .primaryFuelEvent   = &outputSchedules[CYL_12_PRIMARY_INJ_CH],
            .secondaryFuelEvent = &outputSchedules[CYL_12_SECONDARY_INJ_CH],
            .syncedEngineData   = &syncedEngineData[11]
    },
    .fuelingProperties = {
        .injectorFlow               = CC_PER_MINUTE(INJECTOR_FLOW_RATE),
        .secondaryInjectorFlow      = CC_PER_MINUTE(SECONDARY_INJ_FLOW_RATE),
        .stoichiometricAFR          = AFR_S(ANTICIPATED_STOICH_AFR), /* E70 */
        .densityOfFuelAtSTP         = FUEL_DENSITY_S(E85_DENSITY),
        .maxPrimaryDC               = DUTYCYCLE(MAX_INJ_DUTY_CYCLE),
        .maxSecondaryDC             = DUTYCYCLE(MAX_INJ_DC_SECONDARY),
        .injectionStrategy          = INJECTION_STRATEGY, //TODO move to an enum
        .fuelPumpMinRuntime         = FUEL_PUMP_RUNTIME,
        .fuelingStrategeyCode       = PRIMARY_FUELING_ALGORITHM,              // ^ desired fueling algorithm
        .fuelAlgoFlags.massAir      = MASS_AIR,
        .fuelAlgoFlags.speedDensity = SPEED_DENSITY,
        .fuelAlgoFlags.flexFuel     = FLEX_FUEL,
        .fuelAlgoFlags.alphaN       = ALPHA_N,
        .fuelAlgoFlags.SDAlphaBlend = ALPHA_SD_BLEND,
        .fuelAlgoFlags.deltaScaling = DELTA_AE
    },
    .operatingLimits[ULTIMATE_OPERATING_LIMITS_INDEX] = {
        /* RPM (Engine RPM) Ultimate limits */
        .RPMfuelDisableLimit     = RPM(RPM_FUEL_DISABLE),
        .RPMfuelEnableLimit      = RPM(RPM_FUEL_REENABLE),
        .RPMignitionDisableLimit = RPM(RPM_IGNITION_DISABLE),
        .RPMignitionEnableLimit  = RPM(RPM_IGNTTION_REENABLE),

        /* MAP (Manifold Absolute Pressure) ultimate limits */
        .MAPfuelDisableLimit     = KPA(MAP_MAX_FUEL_DISABLE),
        .MAPfuelEnableLimit      = KPA(MAP_FUEL_RENABLE),
        .MAPignitionDisableLimit = KPA(MAP_MAX_IGNITION_DISABLE),
        .MAPignitionEnableLimit  = KPA(MAP_IGNITION_REENABLE),
    },
    .operatingLimits[DERATE_LEVEL_ONE_LIMITS_INDEX] = {
        /* RPM (Engine RPM) Ultimate limits */
        .RPMfuelDisableLimit     = RPM(DERATE_L1_RPM_FUEL_DISABLE),
        .RPMfuelEnableLimit      = RPM(DERATE_L1_RPM_FUEL_REENABLE),
        .RPMignitionDisableLimit = RPM(DERATE_L1_RPM_IGNITION_DISABLE),
        .RPMignitionEnableLimit  = RPM(DERATE_L1_RPM_IGNTTION_REENABLE),

        /* MAP (Manifold Absolute Pressure) ultimate limits */
        .MAPfuelDisableLimit     = KPA(DERATE_L1_MAP_MAX_FUEL_DISABLE),
        .MAPfuelEnableLimit      = KPA(DERATE_L1_MAP_FUEL_RENABLE),
        .MAPignitionDisableLimit = KPA(DERATE_L1_MAP_MAX_IGNITION_DISABLE),
        .MAPignitionEnableLimit  = KPA(DERATE_L1_MAP_IGNITION_REENABLE),
    },
    .operatingLimits[DERATE_LEVEL_TWO_LIMITS_INDEX] = {

    },
    .GPIOchannels[0] = {
        .varPointer           = GPIO_0_VARIABLE,
        .upperBoundary        = GPIO_0_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_0_LOWER_BOUNDARY,
        .reg                  = GPIO_0_REGISTER,
        .mask                 = GPIO_0_BIT_MASK,
        .childIndex           = GPIO_0_CHILD_ID,
        .derateLevel          = GPIO_0_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_0_TRIGGER_HIGH,
        .flags.derate         = GPIO_0_DERATE,
        .flags.invertOutput   = GPIO_0_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_0_IS_PARENT,
        .flags.enabled        = GPIO_0_ENABLED,
        .flags.isOutput       = GPIO_0_IS_OUTPUT,
        .flags.hasChild       = GPIO_0_HAS_CHILD,
    },
    .GPIOchannels[1] = {
        .varPointer           = GPIO_1_VARIABLE,
        .upperBoundary        = GPIO_1_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_1_LOWER_BOUNDARY,
        .reg                  = GPIO_1_REGISTER,
        .mask                 = GPIO_1_BIT_MASK,
        .childIndex           = GPIO_1_CHILD_ID,
        .derateLevel          = GPIO_1_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_1_TRIGGER_HIGH,
        .flags.derate         = GPIO_1_DERATE,
        .flags.invertOutput   = GPIO_1_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_1_IS_PARENT,
        .flags.enabled        = GPIO_1_ENABLED,
        .flags.isOutput       = GPIO_1_IS_OUTPUT,
        .flags.hasChild       = GPIO_1_HAS_CHILD,
    },
        .GPIOchannels[2] = {
        .varPointer           = GPIO_2_VARIABLE,
        .upperBoundary        = GPIO_2_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_2_LOWER_BOUNDARY,
        .reg                  = GPIO_2_REGISTER,
        .mask                 = GPIO_2_BIT_MASK,
        .childIndex           = GPIO_2_CHILD_ID,
        .derateLevel          = GPIO_2_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_2_TRIGGER_HIGH,
        .flags.derate         = GPIO_2_DERATE,
        .flags.invertOutput   = GPIO_2_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_2_IS_PARENT,
        .flags.enabled        = GPIO_2_ENABLED,
        .flags.isOutput       = GPIO_2_IS_OUTPUT,
        .flags.hasChild       = GPIO_2_HAS_CHILD,
    },
    .GPIOchannels[3] = {
        .varPointer           = GPIO_3_VARIABLE,
        .upperBoundary        = GPIO_3_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_3_LOWER_BOUNDARY,
        .reg                  = GPIO_3_REGISTER,
        .mask                 = GPIO_3_BIT_MASK,
        .childIndex           = GPIO_3_CHILD_ID,
        .derateLevel          = GPIO_3_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_3_TRIGGER_HIGH,
        .flags.derate         = GPIO_3_DERATE,
        .flags.invertOutput   = GPIO_3_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_3_IS_PARENT,
        .flags.enabled        = GPIO_3_ENABLED,
        .flags.isOutput       = GPIO_3_IS_OUTPUT,
        .flags.hasChild       = GPIO_3_HAS_CHILD,
    },
    .GPIOchannels[4] = {
        .varPointer           = GPIO_4_VARIABLE,
        .upperBoundary        = GPIO_4_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_4_LOWER_BOUNDARY,
        .reg                  = GPIO_4_REGISTER,
        .mask                 = GPIO_4_BIT_MASK,
        .childIndex           = GPIO_4_CHILD_ID,
        .derateLevel          = GPIO_4_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_4_TRIGGER_HIGH,
        .flags.derate         = GPIO_4_DERATE,
        .flags.invertOutput   = GPIO_4_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_4_IS_PARENT,
        .flags.enabled        = GPIO_4_ENABLED,
        .flags.isOutput       = GPIO_4_IS_OUTPUT,
        .flags.hasChild       = GPIO_4_HAS_CHILD,
    },
    .GPIOchannels[5] = {
        .varPointer           = GPIO_5_VARIABLE,
        .upperBoundary        = GPIO_5_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_5_LOWER_BOUNDARY,
        .reg                  = GPIO_5_REGISTER,
        .mask                 = GPIO_5_BIT_MASK,
        .childIndex           = GPIO_5_CHILD_ID,
        .derateLevel          = GPIO_5_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_5_TRIGGER_HIGH,
        .flags.derate         = GPIO_5_DERATE,
        .flags.invertOutput   = GPIO_5_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_5_IS_PARENT,
        .flags.enabled        = GPIO_5_ENABLED,
        .flags.isOutput       = GPIO_5_IS_OUTPUT,
        .flags.hasChild       = GPIO_5_HAS_CHILD,
    },
    .GPIOchannels[6] = {
        .varPointer           = GPIO_6_VARIABLE,
        .upperBoundary        = GPIO_6_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_6_LOWER_BOUNDARY,
        .reg                  = GPIO_6_REGISTER,
        .mask                 = GPIO_6_BIT_MASK,
        .childIndex           = GPIO_6_CHILD_ID,
        .derateLevel          = GPIO_6_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_6_TRIGGER_HIGH,
        .flags.derate         = GPIO_6_DERATE,
        .flags.invertOutput   = GPIO_6_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_6_IS_PARENT,
        .flags.enabled        = GPIO_6_ENABLED,
        .flags.isOutput       = GPIO_6_IS_OUTPUT,
        .flags.hasChild       = GPIO_6_HAS_CHILD,
    },
    .GPIOchannels[7] = {
        .varPointer           = GPIO_7_VARIABLE,
        .upperBoundary        = GPIO_7_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_7_LOWER_BOUNDARY,
        .reg                  = GPIO_7_REGISTER,
        .mask                 = GPIO_7_BIT_MASK,
        .childIndex           = GPIO_7_CHILD_ID,
        .derateLevel          = GPIO_7_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_7_TRIGGER_HIGH,
        .flags.derate         = GPIO_7_DERATE,
        .flags.invertOutput   = GPIO_7_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_7_IS_PARENT,
        .flags.enabled        = GPIO_7_ENABLED,
        .flags.isOutput       = GPIO_7_IS_OUTPUT,
        .flags.hasChild       = GPIO_7_HAS_CHILD,
    },
    .GPIOchannels[8] = {
        .varPointer           = GPIO_8_VARIABLE,
        .upperBoundary        = GPIO_8_UPPER_BOUNDARY,
        .lowerBoundary        = GPIO_8_LOWER_BOUNDARY,
        .reg                  = GPIO_8_REGISTER,
        .mask                 = GPIO_8_BIT_MASK,
        .childIndex           = GPIO_8_CHILD_ID,
        .derateLevel          = GPIO_8_DERATE_LEVEL,
        .flags.triggerOnUpper = GPIO_8_TRIGGER_HIGH,
        .flags.derate         = GPIO_8_DERATE,
        .flags.invertOutput   = GPIO_8_OUTPUT_POLARITY,
        .flags.isParentEvent  = GPIO_8_IS_PARENT,
        .flags.enabled        = GPIO_8_ENABLED,
        .flags.isOutput       = GPIO_8_IS_OUTPUT,
        .flags.hasChild       = GPIO_8_HAS_CHILD,
    },
    .GPIOchannels[9] = { .varPointer = 0, .upperBoundary = 0, .lowerBoundary = 0, .reg = 0, .mask = 0, .flags = {0}},
    .GPIOchannels[10] = { .varPointer = 0, .upperBoundary = 0, .lowerBoundary = 0, .reg = 0, .mask = 0, .flags = {0}},
    .GPIOchannels[11] = { .varPointer = 0, .upperBoundary = 0, .lowerBoundary = 0, .reg = 0, .mask = 0, .flags = {0}},
    .GPIOchannels[12] = { .varPointer = 0, .upperBoundary = 0, .lowerBoundary = 0, .reg = 0, .mask = 0, .flags = {0}},
    .GPIOchannels[13] = { .varPointer = 0, .upperBoundary = 0, .lowerBoundary = 0, .reg = 0, .mask = 0, .flags = {0}},
    .GPIOchannels[14] = { .varPointer = 0, .upperBoundary = 0, .lowerBoundary = 0, .reg = 0, .mask = 0, .flags = {0}},
    .GPIOchannels[15] = { .varPointer = 0, .upperBoundary = 0, .lowerBoundary = 0, .reg = 0, .mask = 0, .flags = {0}},

     /* We reserve the first four channels for ignition */
     .xGateOutputCHpinMapping[0] = {.regMask  = CH0_MASK, .regAddress  = CH0_PORT},
     .xGateOutputCHpinMapping[1] = {.regMask  = CH1_MASK, .regAddress  = CH1_PORT},
     .xGateOutputCHpinMapping[2] = {.regMask  = CH2_MASK, .regAddress  = CH2_PORT},
     .xGateOutputCHpinMapping[3] = {.regMask  = CH3_MASK, .regAddress  = CH3_PORT},
     /* We setup the next for channels for fuel */
     .xGateOutputCHpinMapping[4] = {.regMask  = CH4_MASK, .regAddress  = CH4_PORT},
     .xGateOutputCHpinMapping[5] = {.regMask  = CH5_MASK, .regAddress  = CH5_PORT},
     .xGateOutputCHpinMapping[6] = {.regMask  = CH6_MASK, .regAddress  = CH6_PORT},
     .xGateOutputCHpinMapping[7] = {.regMask  = CH7_MASK, .regAddress  = CH7_PORT},
     /* If the user has more than a four cylinder8 then the following channels used */
     .xGateOutputCHpinMapping[8] = {.regMask  = CH8_MASK, .regAddress  = CH8_PORT},
     .xGateOutputCHpinMapping[9] = {.regMask  = CH9_MASK, .regAddress  = CH9_PORT},
     .xGateOutputCHpinMapping[10] = {.regMask = CH10_MASK, .regAddress = CH10_PORT},
     .xGateOutputCHpinMapping[11] = {.regMask = CH11_MASK, .regAddress = CH11_PORT},
         /* The last four pins on port D are used for ignition, for guys with 4-8 cylinders */
     .xGateOutputCHpinMapping[12] = {.regMask = CH12_MASK, .regAddress = CH12_PORT},
     .xGateOutputCHpinMapping[13] = {.regMask = CH13_MASK, .regAddress = CH13_PORT},
     .xGateOutputCHpinMapping[14] = {.regMask = CH14_MASK, .regAddress = CH14_PORT},
     .xGateOutputCHpinMapping[15] = {.regMask = CH15_MASK, .regAddress = CH15_PORT},
         /* All pins on port C are used for staged injection purposes */
     .xGateOutputCHpinMapping[16] = {.regMask = CH16_MASK, .regAddress = CH16_PORT},
     .xGateOutputCHpinMapping[17] = {.regMask = CH17_MASK, .regAddress = CH17_PORT},
     .xGateOutputCHpinMapping[18] = {.regMask = CH18_MASK, .regAddress = CH18_PORT},
     .xGateOutputCHpinMapping[19] = {.regMask = CH19_MASK, .regAddress = CH19_PORT},
     .xGateOutputCHpinMapping[20] = {.regMask = CH20_MASK, .regAddress = CH20_PORT},
     .xGateOutputCHpinMapping[21] = {.regMask = CH21_MASK, .regAddress = CH21_PORT},
     .xGateOutputCHpinMapping[22] = {.regMask = CH22_MASK, .regAddress = CH22_PORT},
     .xGateOutputCHpinMapping[23] = {.regMask = CH23_MASK, .regAddress = CH23_PORT},

     /* Default CAN TX settings */
    .canConfig[0]  = {.CANid = 0x101, .TXrateMs = 255},
    .canConfig[1]  = {.CANid = 0x102, .TXrateMs = 255},
    .canConfig[2]  = {.CANid = 0x103, .TXrateMs = 255},
    .canConfig[3]  = {.CANid = 0x104, .TXrateMs = 255},
    .canConfig[4]  = {.CANid = 0x105, .TXrateMs = 255},
    .canConfig[5]  = {.CANid = 0x106, .TXrateMs = 255},
    .canConfig[6]  = {.CANid = 0x107, .TXrateMs = 255},
    .canConfig[7]  = {.CANid = 0x108, .TXrateMs = 255},
    .canConfig[8]  = {.CANid = 0x109, .TXrateMs = 255},
    .canConfig[9]  = {.CANid = 0x10A, .TXrateMs = 255},
    .canConfig[10] = {.CANid = 0x10B, .TXrateMs = 255},
    .canConfig[11] = {.CANid = 0x10C, .TXrateMs = 255},
    .canConfig[12] = {.CANid = 0x10D, .TXrateMs = 255},
    .canConfig[13] = {.CANid = 0x10E, .TXrateMs = 255},
    .canConfig[14] = {.CANid = 0x10F, .TXrateMs = 255},
    .canConfig[15] = {.CANid = 0x110, .TXrateMs = 255},

    /* Communication settings */
    .comSettings = {
      .SC0baudDivisor = SCI_BAUD(115200),
      .SC0modeCode    = 0
    }
};

// Doesnt seem to work on GCC 3.6.6
//#if INPUT_OFFSET > ENGINE_ANGLE_S(360)
//  #warning "Engine angle decoder offset must be < 360!"
//#endif
