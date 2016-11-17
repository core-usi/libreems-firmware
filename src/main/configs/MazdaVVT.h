/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014 Sean Keys
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
 */

#ifndef FILE_ENGINE_CONFIGURATION_H_SEEN
#define FILE_ENGINE_CONFIGURATION_H_SEEN

/* Engine Config */
#define ENGINE_CYLINDER_COUNT   	4
#define CRANKSHAFT_REVS_PER_CYCLE   2     /* Four stroke */
#define NUM_OF_PRECISON_OUTPUTS		12    /* Total number of fuel and ignition channels */
#define INJECTOR_FLOW_RATE          425   /* Flow rate in cc/min */
#define SECONDARY_INJ_FLOW_RATE     185   /* secondary injector flow rate */
#define ANTICIPATED_STOICH_AFR      10.0  /* E70 */
#define MAX_INJ_DUTY_CYCLE          85.0  /* Percent */
#define MAX_INJ_DC_SECONDARY        85.0  /* Percent */
#define INJECTION_STRATEGY          STAGED_EXTENSION
#define PRIMARY_FUELING_ALGORITHM   ALGO_MAF

#define MAX_RPM_CRANKING                 500     /* Max RPM at which the ECU will consider it to be in cranking mode */
#define PRIMARY_SKIP_EDGES                  0
#define PRIMARY_INPUT_TOLLERANCE           80.0   /* Difference allowed in percentage */
#define PRIMARY_INPUT_TOLLERANCE_CRANKING  65.0   /* Difference allowed in percentage */

#define MAP_MAXIMUM                 260
#define MAP_MINIMUM                   8

#define FUEL_PUMP_RUNTIME             2     /* Minimum fuel pump run time, in seconds */

/* Fuel Algorithm settings */
#define FLEX_FUEL                   ENABLED
#define MASS_AIR                    ENABLED
#define SPEED_DENSITY               ENABLED
#define ALPHA_N                     DISABLED
#define ALPHA_SD_BLEND              DISABLED
#define DELTA_AE                    ENABLED

/* Advanced Scheduling Settings */
#define VIRTUAL_ANGLES              DISABLED
#define MAX_HARD_ANGLE_SPREAD       10.0       /* Max angle between input teeth, before virtual angles are created */

#define IDLE_TYPE                   NO_IDLE
#define IDLE_IAC_STEPS              0
#define IDLE_IAC_PW                 0
#define IDLE_IAC_CHA                0
#define IDLE_IAC_CHB                0
#define PWM_CHANNEL                 0

/* Chassis Config */
#define VSS                         ENABLED  /* Vehicle speed sensor input */
#define VSS_DIVISOR                 30


/* Ultimate Limits */
#define RPM_FUEL_DISABLE            11950  /* Max RPM allowed before fuel is cut */
#define RPM_FUEL_REENABLE           11800  /* RPM to re-enable fueling */
#define RPM_IGNITION_DISABLE        12000  /* Max RPM allowed before igntion is cut */
#define RPM_IGNTTION_REENABLE       11900  /* RPM at which to re-enable ignition */
#define MAP_MAX_FUEL_DISABLE        166    /* Max KPA allowed before fuel is cut */
#define MAP_FUEL_RENABLE            140    /* KPA at which to re-enable fueling */
#define MAP_MAX_IGNITION_DISABLE    170    /* Max KPA before igntion is cut */
#define MAP_IGNITION_REENABLE       160    /* KPA to re-enable igntion */

/* First De-rate Limits */
#define DERATE_L1_RPM_FUEL_DISABLE            6000
#define DERATE_L1_RPM_FUEL_REENABLE           5900
#define DERATE_L1_RPM_IGNITION_DISABLE        6100
#define DERATE_L1_RPM_IGNTTION_REENABLE       6000
#define DERATE_L1_MAP_MAX_FUEL_DISABLE        105
#define DERATE_L1_MAP_FUEL_RENABLE            100
#define DERATE_L1_MAP_MAX_IGNITION_DISABLE    110
#define DERATE_L1_MAP_IGNITION_REENABLE       101

#define INPUT_OFFSET			    ENGINE_ANGLE_S(22.5)
#define ENGINE_CYL_VOLUME		    CC_VOLUME_S(250)
#define SPECIFIED_OPERATING_LEVELS  3

/*
 *
 * Engine angle specific settings
 *
 */

#define CYL_1_TDC_ANGLE             405         /* TDC angle */
#define CYL_1_INJ_ANGLE             135         /* Angle to inject Fuel */
#define CYL_1_READ_ANGLE            45          /* Angle to sample sensors */
#define CYL_1_IGN_CH                0           /* XGate ignition channel  */
#define CYL_1_PRIMARY_INJ_CH        4           /* XGate primary fuel channel */
#define CYL_1_SECONDARY_INJ_CH      8           /* XGate secondary fuel channel */

#define CYL_2_TDC_ANGLE             585         /* TDC angle */
#define CYL_2_INJ_ANGLE             315         /* Angle to inject Fuel */
#define CYL_2_READ_ANGLE            225         /* Angle to sample sensors */
#define CYL_2_IGN_CH                1           /* XGate ignition channel */
#define CYL_2_PRIMARY_INJ_CH        5           /* XGate primary fuel channel */
#define CYL_2_SECONDARY_INJ_CH      9           /* XGate secondary fuel channel */

#define CYL_3_TDC_ANGLE             45          /* TDC angle */
#define CYL_3_INJ_ANGLE             495         /* Angle to inject Fuel */
#define CYL_3_READ_ANGLE            405         /* Angle to sample sensors */
#define CYL_3_IGN_CH                2           /* XGate ignition channel */
#define CYL_3_PRIMARY_INJ_CH        6           /* XGate primary fuel channel */
#define CYL_3_SECONDARY_INJ_CH      10          /* XGate secondary fuel channel */

#define CYL_4_TDC_ANGLE             225         /* TDC angle */
#define CYL_4_INJ_ANGLE             675         /* Angle to inject Fuel */
#define CYL_4_READ_ANGLE            585         /* Angle to sample sensors */
#define CYL_4_IGN_CH                3           /* XGate ignition channel */
#define CYL_4_PRIMARY_INJ_CH        7           /* XGate primary fuel channel */
#define CYL_4_SECONDARY_INJ_CH      11          /* XGate secondary fuel channel */

/* We just zero the rest of the cyl parameters, the ENGINE_CYLINDER_COUNT macro controls what gets processed */

#define CYL_5_TDC_ANGLE              0         /* TDC angle */
#define CYL_5_INJ_ANGLE              0         /* Angle to inject Fuel */
#define CYL_5_READ_ANGLE             0         /* Angle to sample sensors */
#define CYL_5_IGN_CH                 0         /* XGate ignition channel */
#define CYL_5_PRIMARY_INJ_CH         0         /* XGate primary fuel channel */
#define CYL_5_SECONDARY_INJ_CH       0         /* XGate secondary fuel channel */

#define CYL_6_TDC_ANGLE              0         /* TDC angle */
#define CYL_6_INJ_ANGLE              0         /* Angle to inject Fuel */
#define CYL_6_READ_ANGLE             0         /* Angle to sample sensors */
#define CYL_6_IGN_CH                 0         /* XGate ignition channel */
#define CYL_6_PRIMARY_INJ_CH         0         /* XGate primary fuel channel */
#define CYL_6_SECONDARY_INJ_CH       0         /* XGate secondary fuel channel */

#define CYL_7_TDC_ANGLE              0         /* TDC angle */
#define CYL_7_INJ_ANGLE              0         /* Angle to inject Fuel */
#define CYL_7_READ_ANGLE             0         /* Angle to sample sensors */
#define CYL_7_IGN_CH                 0         /* XGate ignition channel */
#define CYL_7_PRIMARY_INJ_CH         0         /* XGate primary fuel channel */
#define CYL_7_SECONDARY_INJ_CH       0         /* XGate secondary fuel channel */

#define CYL_8_TDC_ANGLE              0         /* TDC angle */
#define CYL_8_INJ_ANGLE              0         /* Angle to inject Fuel */
#define CYL_8_READ_ANGLE             0         /* Angle to sample sensors */
#define CYL_8_IGN_CH                 0         /* XGate ignition channel */
#define CYL_8_PRIMARY_INJ_CH         0         /* XGate primary fuel channel */
#define CYL_8_SECONDARY_INJ_CH       0         /* XGate secondary fuel channel */

#define CYL_9_TDC_ANGLE              0         /* TDC angle */
#define CYL_9_INJ_ANGLE              0         /* Angle to inject Fuel */
#define CYL_9_READ_ANGLE             0         /* Angle to sample sensors */
#define CYL_9_IGN_CH                 0         /* XGate ignition channel */
#define CYL_9_PRIMARY_INJ_CH         0         /* XGate primary fuel channel */
#define CYL_9_SECONDARY_INJ_CH       0         /* XGate secondary fuel channel */

#define CYL_10_TDC_ANGLE             0         /* TDC angle */
#define CYL_10_INJ_ANGLE             0         /* Angle to inject Fuel */
#define CYL_10_READ_ANGLE            0         /* Angle to sample sensors */
#define CYL_10_IGN_CH                0         /* XGate ignition channel */
#define CYL_10_PRIMARY_INJ_CH        0         /* XGate primary fuel channel */
#define CYL_10_SECONDARY_INJ_CH      0         /* XGate secondary fuel channel */

#define CYL_11_TDC_ANGLE             0         /* TDC angle */
#define CYL_11_INJ_ANGLE             0         /* Angle to inject Fuel */
#define CYL_11_READ_ANGLE            0         /* Angle to sample sensors */
#define CYL_11_IGN_CH                0         /* XGate ignition channel */
#define CYL_11_PRIMARY_INJ_CH        0         /* XGate primary fuel channel */
#define CYL_11_SECONDARY_INJ_CH      0         /* XGate secondary fuel channel */

#define CYL_12_TDC_ANGLE             0         /* TDC angle */
#define CYL_12_INJ_ANGLE             0         /* Angle to inject Fuel */
#define CYL_12_READ_ANGLE            0         /* Angle to sample sensors */
#define CYL_12_IGN_CH                0         /* XGate ignition channel */
#define CYL_12_PRIMARY_INJ_CH        0         /* XGate primary fuel channel */
#define CYL_12_SECONDARY_INJ_CH      0         /* XGate secondary fuel channel */


/* Primary Fan */
#define GPIO_0_ENABLED               TRUE
#define GPIO_0_VARIABLE	             &CoreVars_g.CHT
#define GPIO_0_UPPER_BOUNDARY        DEGREES_C(83)
#define GPIO_0_LOWER_BOUNDARY        DEGREES_C(75)
#define GPIO_0_REGISTER              (uint8_t*)&PORTK
#define GPIO_0_BIT_MASK              BIT4
#define GPIO_0_TRIGGER_HIGH          TRUE
#define GPIO_0_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_0_IS_PARENT             TRUE
#define GPIO_0_DERATE                FALSE
#define GPIO_0_DERATE_LEVEL          0                          /* Ignored since derate is false */
#define GPIO_0_CHILD_ID              3                          /* GPIO CH3 condition must also be true */
#define GPIO_0_IS_OUTPUT             TRUE
#define GPIO_0_HAS_CHILD             TRUE

/* Secondary Fan */
#define GPIO_1_ENABLED               TRUE
#define GPIO_1_VARIABLE	             &CoreVars_g.CHT
#define GPIO_1_UPPER_BOUNDARY        DEGREES_C(100)
#define GPIO_1_LOWER_BOUNDARY        DEGREES_C(90)
#define GPIO_1_REGISTER              (uint8_t*)&PORTK
#define GPIO_1_BIT_MASK              BIT5
#define GPIO_1_TRIGGER_HIGH          TRUE
#define GPIO_1_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_1_IS_PARENT             TRUE
#define GPIO_1_DERATE                FALSE
#define GPIO_1_DERATE_LEVEL          0                          /* Ignored since derate is false */
#define GPIO_1_CHILD_ID              3
#define GPIO_1_IS_OUTPUT             TRUE
#define GPIO_1_HAS_CHILD             TRUE

/* Over temperature derate */
#define GPIO_2_ENABLED               TRUE
#define GPIO_2_VARIABLE	             &CoreVars_g.CHT
#define GPIO_2_UPPER_BOUNDARY        DEGREES_C(107)
#define GPIO_2_LOWER_BOUNDARY        DEGREES_C(101)
#define GPIO_2_REGISTER              (uint8_t*)&PORTK
#define GPIO_2_BIT_MASK              BIT5
#define GPIO_2_TRIGGER_HIGH          TRUE
#define GPIO_2_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_2_IS_PARENT             TRUE
#define GPIO_2_DERATE                TRUE
#define GPIO_2_DERATE_LEVEL          0                          /* Ignored since derate is false */
#define GPIO_2_CHILD_ID              2
#define GPIO_2_IS_OUTPUT             TRUE
#define GPIO_2_HAS_CHILD             FALSE

#define GPIO_3_ENABLED               TRUE
#define GPIO_3_VARIABLE	             &CoreVars_g.RPM
#define GPIO_3_UPPER_BOUNDARY        RPM(700)
#define GPIO_3_LOWER_BOUNDARY        RPM(600)
#define GPIO_3_REGISTER              GPO_NULL_REGISTER_ADDRESS
#define GPIO_3_BIT_MASK              0
#define GPIO_3_TRIGGER_HIGH          TRUE
#define GPIO_3_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_3_IS_PARENT             FALSE                       /* The chain stop here */
#define GPIO_3_DERATE                FALSE
#define GPIO_3_DERATE_LEVEL          0                           /* Ignored since derate is false */
#define GPIO_3_CHILD_ID              3                           /* Ignored by setting this value to the same as ourselves */
#define GPIO_3_IS_OUTPUT             TRUE
#define GPIO_3_HAS_CHILD             FALSE

/* 2D LUTs */
#define FUEL_DELTA_PERCENTS { FD(110.0), FD(150.0), FD(175.0), FD(200.0), FD(250.0), FD(300), FD(400), FD(500)}
#define FUEL_DELTA_ADDER    { FA(100.0), FA(120.0), FA(125.0), FA(150.0), FA(175.0), FA(200), FA(250), FA(300)}

#endif
