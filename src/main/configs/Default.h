/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2016 David Andruczyk
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

/* Use this for the appropriate wheel decoder... */
#include "../engineAngleDecoders/Crank8x_Cam1x.h"

// 4 Cylinder Default
/* Engine Config */
#define ENGINE_CYLINDER_COUNT   	    4
#define CRANKSHAFT_REVS_PER_CYCLE       2    /* Four stroke */
#define NUM_OF_PRECISON_OUTPUTS		   12    /* Total number of fuel and ignition channels */
#define INJECTOR_FLOW_RATE          305.0   /* Flow rate in cc/min */
#define SECONDARY_INJ_FLOW_RATE     0.0   /* secondary injector flow rate */
#define ANTICIPATED_STOICH_AFR      14.06  /* E10 */
#define MAX_INJ_DUTY_CYCLE          90.0  /* Percent */
#define MAX_INJ_DC_SECONDARY        90.0  /* Percent */
#define INJECTION_STRATEGY          PLAIN_INJECTION
#define PRIMARY_FUELING_ALGORITHM   ALGO_SPEED_DENSITY

#define MAX_RPM_CRANKING                  400     /* Max RPM at which the ECU will consider it to be in cranking mode */
#define PRIMARY_SKIP_EDGES                  0
#define PRIMARY_INPUT_TOLLERANCE           80.0   /* Difference allowed in percentage */
#define PRIMARY_INPUT_TOLLERANCE_CRANKING  80.0   /* Difference allowed in percentage */
#define FILTER_ENABLE_RPM                 800.0   /* RPM to start filtering tach signal */

#define MAP_MAXIMUM                 105.5   /* At 5.0v */
#define MAP_MINIMUM                   1.1   /* At 0v   */


#define FUEL_PUMP_RUNTIME             2     /* Minimum fuel pump run time, in seconds */

/* Fuel Algorithm settings */
#define FLEX_FUEL                   DISABLED
#define MASS_AIR                    DISABLED
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

#define ECT0_CAPTURE_RISING         FALSE
#define ECT0_CAPTURE_FALLING        TRUE
#define ECT1_CAPTURE_RISING         FALSE
#define ECT1_CAPTURE_FALLING        TRUE
#define ECT2_CAPTURE_RISING         TRUE
#define ECT2_CAPTURE_FALLING        TRUE
#define ECT3_CAPTURE_RISING         TRUE
#define ECT3_CAPTURE_FALLING        TRUE
#define ECT4_CAPTURE_RISING         TRUE  /* No effect reserved by XGate */
#define ECT4_CAPTURE_FALLING        TRUE  /* No effect reserved by XGate */
#define ECT5_CAPTURE_RISING         TRUE
#define ECT5_CAPTURE_FALLING        TRUE
#define ECT6_CAPTURE_RISING         TRUE
#define ECT6_CAPTURE_FALLING        TRUE
#define ECT7_CAPTURE_RISING         TRUE
#define ECT7_CAPTURE_FALLING        TRUE

/* Ultimate Limits */
#define RPM_FUEL_DISABLE            5950  /* Max RPM allowed before fuel is cut */
#define RPM_FUEL_REENABLE           5800  /* RPM to re-enable fueling */
#define RPM_IGNITION_DISABLE        6000  /* Max RPM allowed before ignition is cut */
#define RPM_IGNTTION_REENABLE       5750  /* RPM at which to re-enable ignition */
#define MAP_MAX_FUEL_DISABLE        110    /* Max KPA allowed before fuel is cut */
#define MAP_FUEL_RENABLE            106    /* KPA at which to re-enable fueling */
#define MAP_MAX_IGNITION_DISABLE    109    /* Max KPA before ignition is cut */
#define MAP_IGNITION_REENABLE       105    /* KPA to re-enable ignition */

/* First De-rate Limits */
#define DERATE_L1_RPM_FUEL_DISABLE            4500
#define DERATE_L1_RPM_FUEL_REENABLE           4200
#define DERATE_L1_RPM_IGNITION_DISABLE        4600
#define DERATE_L1_RPM_IGNTTION_REENABLE       4300
#define DERATE_L1_MAP_MAX_FUEL_DISABLE        125
#define DERATE_L1_MAP_FUEL_RENABLE            120
#define DERATE_L1_MAP_MAX_IGNITION_DISABLE    125
#define DERATE_L1_MAP_IGNITION_REENABLE       120

#define INPUT_OFFSET			        ENGINE_ANGLE_S(30.5)
#define ENGINE_CYL_VOLUME		        CC_VOLUME_S(400)
#define SPECIFIED_OPERATING_LEVELS  3

/*
 *
 * Engine angle specific settings
 *
 */

#define CYL_1_TDC_ANGLE             405         /* TDC angle */
#define CYL_1_INJ_ANGLE             135         /* Angle to inject Fuel */
#define CYL_1_READ_ANGLE            90          /* Angle to sample sensors */
#define CYL_1_IGN_CH                0           /* XGate ignition channel  */
#define CYL_1_PRIMARY_INJ_CH        4           /* XGate primary fuel channel */
#define CYL_1_SECONDARY_INJ_CH      8           /* XGate secondary fuel channel */

#define CYL_2_TDC_ANGLE             585         /* TDC angle */
#define CYL_2_INJ_ANGLE             315         /* Angle to inject Fuel */
#define CYL_2_READ_ANGLE            270         /* Angle to sample sensors */
#define CYL_2_IGN_CH                1           /* XGate ignition channel */
#define CYL_2_PRIMARY_INJ_CH        5           /* XGate primary fuel channel */
#define CYL_2_SECONDARY_INJ_CH      9           /* XGate secondary fuel channel */

#define CYL_3_TDC_ANGLE             225         /* TDC angle */
#define CYL_3_INJ_ANGLE             675         /* Angle to inject Fuel */
#define CYL_3_READ_ANGLE            630         /* Angle to sample sensors */
#define CYL_3_IGN_CH                2           /* XGate ignition channel */
#define CYL_3_PRIMARY_INJ_CH        6           /* XGate primary fuel channel */
#define CYL_3_SECONDARY_INJ_CH      10          /* XGate secondary fuel channel */

#define CYL_4_TDC_ANGLE             45          /* TDC angle */
#define CYL_4_INJ_ANGLE             495         /* Angle to inject Fuel */
#define CYL_4_READ_ANGLE            450         /* Angle to sample sensors */
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
#define GPIO_0_UPPER_BOUNDARY        DEGREES_C(90)
#define GPIO_0_LOWER_BOUNDARY        DEGREES_C(85)
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
#define GPIO_2_UPPER_BOUNDARY        DEGREES_C(105)
#define GPIO_2_LOWER_BOUNDARY        DEGREES_C(101)
#define GPIO_2_REGISTER              (uint8_t*)&PORTK
#define GPIO_2_BIT_MASK              BIT5
#define GPIO_2_TRIGGER_HIGH          TRUE
#define GPIO_2_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_2_IS_PARENT             TRUE
#define GPIO_2_DERATE                TRUE
#define GPIO_2_DERATE_LEVEL          DERATE_LEVEL_ONE_LIMITS_INDEX                          /* Ignored since derate is false */
#define GPIO_2_CHILD_ID              0
#define GPIO_2_IS_OUTPUT             TRUE
#define GPIO_2_HAS_CHILD             FALSE

/* Secondary RPM condition for the Fans */
#define GPIO_3_ENABLED               TRUE
#define GPIO_3_VARIABLE	             &CoreVars_g.RPM
#define GPIO_3_UPPER_BOUNDARY        RPM(700)
#define GPIO_3_LOWER_BOUNDARY        RPM(600)
#define GPIO_3_REGISTER              GPO_NULL_REGISTER_ADDRESS
#define GPIO_3_BIT_MASK              0
#define GPIO_3_TRIGGER_HIGH          TRUE
#define GPIO_3_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_3_IS_PARENT             FALSE                       /* The chain stops here */
#define GPIO_3_DERATE                FALSE
#define GPIO_3_DERATE_LEVEL          0                           /* Ignored since derate is false */
#define GPIO_3_CHILD_ID              3                           /* Ignored by setting this value to the same as ourselves */
#define GPIO_3_IS_OUTPUT             TRUE
#define GPIO_3_HAS_CHILD             FALSE

/* Under temperature de-rate */
#define GPIO_4_ENABLED               TRUE
#define GPIO_4_VARIABLE	             &CoreVars_g.CHT
#define GPIO_4_UPPER_BOUNDARY        DEGREES_C(65)
#define GPIO_4_LOWER_BOUNDARY        DEGREES_C(60)
#define GPIO_4_REGISTER              GPO_NULL_REGISTER_ADDRESS
#define GPIO_4_BIT_MASK              BIT5
#define GPIO_4_TRIGGER_HIGH          FALSE
#define GPIO_4_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_4_IS_PARENT             TRUE
#define GPIO_4_DERATE                TRUE
#define GPIO_4_DERATE_LEVEL          DERATE_LEVEL_ONE_LIMITS_INDEX                          /* Ignored since derate is false */
#define GPIO_4_CHILD_ID              0
#define GPIO_4_IS_OUTPUT             TRUE
#define GPIO_4_HAS_CHILD             FALSE

/* Sensor Ranges */
#define TPS_MINIMUM (0)
#define TPS_MAXIMUM (1024 - 1)

/* 2D LUTs */
#define IAT_VS_IGN_TABLE \
  {C(-40),  DEG( 5)}, \
  {C(-30),  DEG( 5)}, \
  {C(-20),  DEG( 5)}, \
  {C(-12),  DEG( 5)}, \
  {C(  0),  DEG( 5)}, \
  {C( 10),  DEG( 1)}, \
  {C( 20),  DEG( 0)}, \
  {C( 30),  DEG( 0)}, \
  {C( 38),  DEG( 0)}, \
  {C( 44),  DEG(-1)}, \
  {C( 48),  DEG(-2)}, \
  {C( 65),  DEG(-3)}, \
  {C( 88),  DEG(-4)}, \
  {C( 94),  DEG(-5)}, \
  {C(105),  DEG(-6)}, \
  {C(120),  DEG(-8)}

#define CLT_VS_IGN_TABLE \
  {C(-40),  DEG( 2)}, \
  {C(-30),  DEG( 2)}, \
  {C(-20),  DEG( 2)}, \
  {C(-12),  DEG( 1)}, \
  {C(  0),  DEG( 0)}, \
  {C( 10),  DEG( 0)}, \
  {C( 20),  DEG( 0)}, \
  {C( 30),  DEG( 0)}, \
  {C( 38),  DEG( 0)}, \
  {C( 44),  DEG( 0)}, \
  {C( 48),  DEG( 0)}, \
  {C( 65),  DEG( 0)}, \
  {C( 88),  DEG(-1)}, \
  {C( 94),  DEG(-2)}, \
  {C(105),  DEG(-2)}, \
  {C(120),  DEG(-3)}

#define ENGINE_TEMP_ENRICHMENT_TABLE \
  {C(-30), W(170)}, \
  {C(-20), W(165)}, \
  {C(-10), W(160)}, \
  {C(  0), W(145)}, \
  {C( 10), W(140)}, \
  {C( 20), W(130)}, \
  {C( 30), W(120)}, \
  {C( 40), W(115)}, \
  {C( 50), W(110)}, \
  {C( 60), W(108)}, \
  {C( 70), W(104)}, \
  {C( 80), W(100)}, \
  {C( 90), W(100)}, \
  {C(100), W(110)}, \
  {C(110), W(120)}, \
  {C(120), W(130)}

#define FUEL_DELTA_VS_PERCENT_ADDER_TABLE \
  {FD(110.0), FA(100.0)}, \
  {FD(150.0), FA(120.0)}, \
  {FD(175.0), FA(125.0)}, \
  {FD(200.0), FA(150.0)}, \
  {FD(250.0), FA(175.0)}, \
  {FD(300.0), FA(200.0)}, \
  {FD(400.0), FA(250.0)}, \
  {FD(500.0), FA(300.0)}

#define ETHANOL_PERCENT_VS_IGN_TABLE \
  {EP(  0), DEG(0.00)}, \
  {EP(  5), DEG(0.00)}, \
  {EP( 10), DEG(0.00)}, \
  {EP( 15), DEG(0.50)}, \
  {EP( 20), DEG(1.00)}, \
  {EP( 30), DEG(1.25)}, \
  {EP( 35), DEG(1.50)}, \
  {EP( 40), DEG(2.00)}, \
  {EP( 45), DEG(2.50)}, \
  {EP( 55), DEG(3.00)}, \
  {EP( 65), DEG(3.50)}, \
  {EP( 75), DEG(4.00)}, \
  {EP( 85), DEG(4.50)}, \
  {EP( 90), DEG(5.00)}, \
  {EP( 95), DEG(5.50)}, \
  {EP(100), DEG(6.00)}

#define RPM_VS_DWELL_TABLE \
  {RPM(  500), MS(4.00)}, \
  {RPM( 1000), MS(4.00)}, \
  {RPM( 1500), MS(4.00)}, \
  {RPM( 2000), MS(3.50)}, \
  {RPM( 2500), MS(3.50)}, \
  {RPM( 3000), MS(3.50)}, \
  {RPM( 3500), MS(3.00)}, \
  {RPM( 4000), MS(3.00)}, \
  {RPM( 6500), MS(2.50)}, \
  {RPM( 8500), MS(2.25)}, \
  {RPM(10000), MS(2.00)}, \
  {RPM(10500), MS(2.00)}, \
  {RPM(11000), MS(2.00)}, \
  {RPM(12000), MS(2.00)}, \
  {RPM(12500), MS(2.00)}, \
  {RPM(13000), MS(1.75)}

#define BRV_VS_DWELL_TABLE  \
  {AV( 6.1), MS(5.5)}, \
  {AV( 7.3), MS(5.5)}, \
  {AV( 8.5), MS(5.5)}, \
  {AV( 9.1), MS(5.5)}, \
  {AV( 9.7), MS(5.5)}, \
  {AV(10.3), MS(5.5)}, \
  {AV(10.9), MS(5.5)}, \
  {AV(11.4), MS(5.5)}, \
  {AV(12.1), MS(5.5)}, \
  {AV(12.7), MS(5.5)}, \
  {AV(13.3), MS(5.5)}, \
  {AV(13.9), MS(5.5)}, \
  {AV(14.5), MS(5.5)}, \
  {AV(17.9), MS(5.5)}, \
  {AV(21.1), MS(5.5)}, \
  {AV(24.5), MS(5.5)}

#define IDT_LOOKUP_TABLE \
  {AV( 6.1), MS(2.91)}, \
  {AV( 7.3), MS(2.30)}, \
  {AV( 8.5), MS(1.86)}, \
  {AV( 9.1), MS(1.70)}, \
  {AV( 9.7), MS(1.58)}, \
  {AV(10.3), MS(1.47)}, \
  {AV(10.9), MS(1.39)}, \
  {AV(11.4), MS(1.30)}, \
  {AV(12.1), MS(1.23)}, \
  {AV(12.7), MS(1.15)}, \
  {AV(13.3), MS(1.10)}, \
  {AV(13.9), MS(1.04)}, \
  {AV(14.5), MS(0.99)}, \
  {AV(17.9), MS(0.76)}, \
  {AV(21.1), MS(0.57)}, \
  {AV(24.5), MS(0.40)}

#define RPM_VS_TEMP_TABLE \
  {RPM( 500), C(-30)}, \
  {RPM( 700), C(-10)}, \
  {RPM( 900), C(  0)}, \
  {RPM(1000), C( 20)}, \
  {RPM(1200), C( 40)}, \
  {RPM(1400), C( 60)}, \
  {RPM(1600), C( 80)}, \
  {RPM(1800), C( 90)}

#define RPM_VS_STEPS_TABLE \
  {RPM( 500), 160}, \
  {RPM( 700), 120}, \
  {RPM( 900),  90}, \
  {RPM(1000),  70}, \
  {RPM(1200),  50}, \
  {RPM(1400),  40}, \
  {RPM(1600),  30}, \
  {RPM(1800),  10}

#define TEMP_VS_ASE_PERCENT_TABLE \
  {C(-30), W(230)}, \
  {C(-20), W(210)}, \
  {C(-10), W(200)}, \
  {C(  0), W(175)}, \
  {C( 10), W(155)}, \
  {C( 20), W(145)}, \
  {C( 30), W(135)}, \
  {C( 40), W(120)}, \
  {C( 50), W(112)}, \
  {C( 60), W(108)}, \
  {C( 70), W(104)}, \
  {C( 80), W(100)}, \
  {C( 90), W(100)}, \
  {C(100), W(110)}, \
  {C(110), W(120)}, \
  {C(120), W(130)}

#define TEMP_VS_PRIMING_VOLUME_TABLE \
  {C(-30), T(6.40)}, \
  {C(-20), T(5.06)}, \
  {C(-10), T(4.09)}, \
  {C(  0), T(3.74)}, \
  {C( 10), T(3.48)}, \
  {C( 20), T(3.23)}, \
  {C( 30), T(3.06)}, \
  {C( 40), T(2.86)}, \
  {C( 50), T(2.71)}, \
  {C( 60), T(2.53)}, \
  {C( 70), T(2.41)}, \
  {C( 80), T(2.29)}, \
  {C( 90), T(2.18)}, \
  {C(100), T(1.67)}, \
  {C(110), T(1.25)}, \
  {C(120), T(0.88)}

#define RPM_VS_BLEND_TABLE \
  {RPM( 500), SHORTMAX}, \
  {RPM(1000), SHORTMAX}, \
  {RPM(1500), SHORTMAX}, \
  {RPM(2000), LR(1.5)}, \
  {RPM(2500), LR(1.0)}, \
  {RPM(3000), LR(0.5)}, \
  {RPM(3500), LR(0.0)}, \
  {RPM(4000), LR(0.0)}, \
  {RPM(4500), LR(0.0)}, \
  {RPM(5000), LR(0.0)}, \
  {RPM(5500), LR(0.0)}, \
  {RPM(6000), LR(0.0)}, \
  {RPM(6500), LR(0.0)}, \
  {RPM(7000), LR(0.0)}, \
  {RPM(7500), LR(0.0)}, \
  {RPM(8000), LR(0.0)} 
/* MAF table, likely always custom */

#define MAF_LUT             \
  {AV(1.300), GS(  0.000)}, \
  {AV(1.403), GS(  0.707)}, \
  {AV(1.506), GS(  0.900)}, \
  {AV(1.609), GS(  1.000)}, \
  {AV(1.712), GS(  1.500)}, \
  {AV(1.816), GS(  2.501)}, \
  {AV(1.919), GS(  3.000)}, \
  {AV(2.022), GS(  4.000)}, \
  {AV(2.125), GS(  4.750)}, \
  {AV(2.220), GS(  5.500)}, \
  {AV(2.332), GS(  9.256)}, \
  {AV(2.435), GS( 12.614)}, \
  {AV(2.538), GS( 14.882)}, \
  {AV(2.641), GS( 14.882)}, \
  {AV(2.745), GS( 16.216)}, \
  {AV(2.848), GS( 18.805)}, \
  {AV(2.951), GS( 20.467)}, \
  {AV(3.054), GS( 27.042)}, \
  {AV(3.158), GS( 34.973)}, \
  {AV(3.261), GS( 45.511)}, \
  {AV(3.364), GS( 60.216)}, \
  {AV(3.467), GS( 66.248)}, \
  {AV(3.570), GS( 70.653)}, \
  {AV(3.674), GS( 75.139)}, \
  {AV(3.777), GS( 84.066)}, \
  {AV(3.880), GS( 96.694)}, \
  {AV(3.983), GS(120.055)}, \
  {AV(4.087), GS(132.184)}, \
  {AV(4.190), GS(156.114)}, \
  {AV(4.293), GS(163.880)}, \
  {AV(4.396), GS(170.516)}, \
  {AV(4.500), GS(180.055)}

/* Pressure Sensors */
#include "../data/tables/sensorLUTs/pressure.h"
#include "../data/tables/sensorLUTs/temperature.h"

#define LOOKUP_MAP  APS_DENSOR1
#define LOOKUP_AAP  APS_DENSOR1

#define FUEL_PRESSURE_TABLE  PS_GLOWSHIFT_60

/* Primary EGO table LC2 */
#define EGO_LOOKUP_TABLE  \
  {AV(0.000), LR(0.500)}, \
  {AV(0.714), LR(0.642)}, \
  {AV(1.428), LR(0.785)}, \
  {AV(2.142), LR(0.928)}, \
  {AV(2.857), LR(1.071)}, \
  {AV(3.571), LR(1.214)}, \
  {AV(4.285), LR(1.357)}, \
  {AV(5.000), LR(1.50)}

#define LOOKUP_EGT EGT_F16

/* CHT Transfer Table */
#define CHT_TRANSFER_TABLE           "../data/thermistors/Denso-2k7Bias.h"

/* IAT Transfer Table */
#define IAT_TRANSFER_TABLE           "../data/thermistors/Denso-2k7Bias.h"

/* FUEL (VE) Table(s) */
#define VE_TABLE_RPM_LENGTH          MAINTABLE_RPM_LENGTH
#define VE_TABLE_LOAD_LENGTH         MAINTABLE_LOAD_LENGTH
#define VE_RPM_AXIS_PRIMARY          "../data/tables/axis/DefaultWith400Spacing-RPM-27.h"
#define VE_LOAD_AXIS_PRIMARY         "../data/tables/axis/DefaultWith10and20SplitSpacing-Load-21.h"
#define VE_TABLE_PRIMARY             "../data/tables/ve/Default-VE24RPMx19Load.h"
#define VE_RPM_AXIS_SECONDARY        "../data/tables/axis/DefaultWith400Spacing-RPM-27.h"
#define VE_LOAD_AXIS_SECONDARY       "../data/tables/axis/DefaultWith10and20SplitSpacing-Load-21.h"
#define VE_TABLE_SECONDARY           "../data/tables/ve/Default-VE24RPMx19Load.h"

/* Airflow (Alpha-N) Tables */
#define AIRFLOW_RPM_AXIS             "../data/tables/axis/DefaultWith400Spacing-RPM-27.h"
#define AIRFLOW_LOAD_AXIS            "../data/tables/axis/DefaultForAlphaN-Load-19.h"
#define AIRFLOW_TABLE                "../data/tables/airflow/flat15PercentAirflow.h"
  
/* Lambda Table */
#define LAMBDA_TABLE_RPM_LENGTH      MAINTABLE_RPM_LENGTH
#define LAMBDA_TABLE_LOAD_LENGTH     MAINTABLE_LOAD_LENGTH
#define LAMBDA_RPM_AXIS              "../data/tables/axis/DefaultWith400Spacing-RPM-27.h"
#define LAMBDA_LOAD_AXIS             "../data/tables/axis/DefaultWith10and20SplitSpacing-Load-21.h"
#define LAMBDA_TABLE                 "../data/tables/lambda/Default-Lambda24RPMx19Load.h"

/* Ignition Table */
#define IGNITION_TABLE_RPM_LENGTH    MAINTABLE_RPM_LENGTH
#define IGNITION_TABLE_LOAD_LENGTH   MAINTABLE_LOAD_LENGTH
#define IGNITION_RPM_AXIS_PRIMARY    "../data/tables/axis/DefaultWith400Spacing-RPM-27.h"
#define IGNITION_LOAD_AXIS_PRIMARY   "../data/tables/axis/DefaultWith10and20SplitSpacing-Load-21.h"
#define IGNITION_TABLE_PRIMARY       "../data/tables/ign/Default-Timing24RPMx19Load.h"
#define IGNITION_RPM_AXIS_SECONDARY  "../data/tables/axis/DefaultWith400Spacing-RPM-27.h"
#define IGNITION_LOAD_AXIS_SECONDARY "../data/tables/axis/DefaultWith10and20SplitSpacing-Load-21.h"
#define IGNITION_TABLE_SECONDARY     "../data/tables/ign/Default-Timing24RPMx19Load.h"

/* Injection timing Tables */
#define INJECTION_TABLE_RPM_LENGTH    MAINTABLE_RPM_LENGTH
#define INJECTION_TABLE_LOAD_LENGTH   MAINTABLE_LOAD_LENGTH
#define INJECTION_RPM_AXIS_PRIMARY    "../data/tables/axis/DefaultWith400Spacing-RPM-27.h"
#define INJECTION_LOAD_AXIS_PRIMARY   "../data/tables/axis/DefaultWith10and20SplitSpacing-Load-21.h"
#define INJECTION_TABLE_PRIMARY       "../data/tables/ign/flat15degrees.h"
#define INJECTION_RPM_AXIS_SECONDARY  "../data/tables/axis/DefaultWith400Spacing-RPM-27.h"
#define INJECTION_LOAD_AXIS_SECONDARY "../data/tables/axis/DefaultWith10and20SplitSpacing-Load-21.h"
#define INJECTION_TABLE_SECONDARY     "../data/tables/ign/flat15degrees.h"


#endif
