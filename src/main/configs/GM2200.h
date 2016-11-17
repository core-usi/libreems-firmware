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

/* This is for use on the PCM which has additional ports brought out on the 112pin MCU. */

/* Config terms */
#define ENABLED                     1
#define DISABLED                    0

#define TRUE                        1
#define FALSE                       0

/* Engine Config */
#define ENGINE_CYLINDER_COUNT   	        4
#define CRANKSHAFT_REVS_PER_CYCLE           2    /* Four stroke */
#define NUM_OF_PRECISON_OUTPUTS		       10    /* Total number of fuel and ignition channels */ //4 injection, 4 ignition, 2 IAC
#define INJECTOR_FLOW_RATE                180    /* Flow rate in cc/min */ // 17 lb/hr injectors
#define SECONDARY_INJ_FLOW_RATE             0    /* secondary injector flow rate */
#define ANTICIPATED_STOICH_AFR             14.7  /* E10 pump gas */
#define MAX_INJ_DUTY_CYCLE                 95.0  /* Percent */
#define MAX_INJ_DC_SECONDARY                0.0  /* Percent */

#define INJECTION_STRATEGY             PLAIN_INJECTION /* Choices are PLAIN_INJECTION, STAGED_EXTENSION */ 
#define PRIMARY_FUELING_ALGORITHM   ALGO_SPEED_DENSITY /* Choices are ALGO_SPEED_DENSITY, ALGO_MAF */

#define MAX_RPM_CRANKING                  600    /* Max RPM at which the ECU will consider it to be in cranking mode */
#define PRIMARY_SKIP_EDGES                  0
#define PRIMARY_INPUT_TOLLERANCE           85.0  /* Difference allowed in percentage */
#define PRIMARY_INPUT_TOLLERANCE_CRANKING  60.0  /* Difference allowed in percentage */

#define MAP_MAXIMUM                 105
#define MAP_MINIMUM                  10

#define FUEL_PUMP_RUNTIME             2     /* Minimum fuel pump run time, in seconds */

/* Algorithm settings */
#define FLEX_FUEL                   DISABLED
#define MASS_AIR                    DISABLED
#define SPEED_DENSITY               ENABLED
#define ALPHA_N                     DISABLED
#define ALPHA_SD_BLEND              DISABLED
#define DELTA_AE                    ENABLED

#define IDLE_TYPE                   GM_STEPPER_IDLE
#define IDLE_IAC_STEPS              160
#define IDLE_IAC_PW                 50
#define IDLE_IAC_CHA                8
#define IDLE_IAC_CHB                9
#define PWM_CHANNEL                 0

/* Ultimate Limits */
#define RPM_FUEL_DISABLE            5600  /* Max RPM allowed before fuel is cut */
#define RPM_FUEL_REENABLE           5550  /* RPM to re-enable fueling */
#define RPM_IGNITION_DISABLE        5600  /* Max RPM allowed before igntion is cut */
#define RPM_IGNTTION_REENABLE       5550  /* RPM at which to re-enable ignition */
#define MAP_MAX_FUEL_DISABLE        105    /* Max KPA allowed before fuel is cut */
#define MAP_FUEL_RENABLE            100    /* KPA at which to re-enable fueling */
#define MAP_MAX_IGNITION_DISABLE    105    /* Max KPA before igntion is cut */
#define MAP_IGNITION_REENABLE       100    /* KPA to re-enable igntion */

/* First De-rate Limits */
#define DERATE_L1_RPM_FUEL_DISABLE            5500
#define DERATE_L1_RPM_FUEL_REENABLE           5400
#define DERATE_L1_RPM_IGNITION_DISABLE        5500
#define DERATE_L1_RPM_IGNTTION_REENABLE       5400
#define DERATE_L1_MAP_MAX_FUEL_DISABLE        105
#define DERATE_L1_MAP_FUEL_RENABLE            100
#define DERATE_L1_MAP_MAX_IGNITION_DISABLE    105
#define DERATE_L1_MAP_IGNITION_REENABLE       100

#define INPUT_OFFSET			    ENGINE_ANGLE_S(0.0)
#define ENGINE_CYL_VOLUME		    CC_VOLUME_S(548)
#define SPECIFIED_OPERATING_LEVELS  3

/* Not sure if this is needed, it was in the R1 config file... */
//#define XGATE_CHANNEL_COUNT		        24

/*
 *
 * Engine angle specific settings
 *
 */

#define CYL_1_TDC_ANGLE             0           /* TDC angle */ //405
#define CYL_1_INJ_ANGLE             450         /* Angle to inject Fuel */ //135 (-270)
#define CYL_1_READ_ANGLE            360         /* Angle to sample sensors */ //45 (-90)
#define CYL_1_IGN_CH                0           /* XGate ignition channel  */
#define CYL_1_PRIMARY_INJ_CH        4           /* XGate primary fuel channel */
#define CYL_1_SECONDARY_INJ_CH      0           /* XGate secondary fuel channel */

#define CYL_2_TDC_ANGLE             540         /* TDC angle */ //585
#define CYL_2_INJ_ANGLE             270         /* Angle to inject Fuel */ //315
#define CYL_2_READ_ANGLE            180         /* Angle to sample sensors */ //225
#define CYL_2_IGN_CH                1           /* XGate ignition channel */
#define CYL_2_PRIMARY_INJ_CH        5           /* XGate primary fuel channel */
#define CYL_2_SECONDARY_INJ_CH      0           /* XGate secondary fuel channel */

#define CYL_3_TDC_ANGLE             180          /* TDC angle */ //45
#define CYL_3_INJ_ANGLE             630         /* Angle to inject Fuel */ //495
#define CYL_3_READ_ANGLE            540         /* Angle to sample sensors */ //405
#define CYL_3_IGN_CH                2           /* XGate ignition channel */
#define CYL_3_PRIMARY_INJ_CH        6           /* XGate primary fuel channel */
#define CYL_3_SECONDARY_INJ_CH      0           /* XGate secondary fuel channel */

#define CYL_4_TDC_ANGLE             360         /* TDC angle */ //225
#define CYL_4_INJ_ANGLE             90          /* Angle to inject Fuel */ //675
#define CYL_4_READ_ANGLE            0           /* Angle to sample sensors */ //585
#define CYL_4_IGN_CH                3           /* XGate ignition channel */
#define CYL_4_PRIMARY_INJ_CH        7           /* XGate primary fuel channel */
#define CYL_4_SECONDARY_INJ_CH      0           /* XGate secondary fuel channel */

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


//#define GPO_NULL_REGISTER_ADDRESS    (uint8_t *)0xFFFF

/* Primary Fan */
#define GPIO_0_ENABLED               TRUE
#define GPIO_0_VARIABLE	             &CoreVars_g.CHT
#define GPIO_0_UPPER_BOUNDARY        DEGREES_C(100)
#define GPIO_0_LOWER_BOUNDARY        DEGREES_C(90)
#define GPIO_0_REGISTER              (uint8_t*)&PORTK
#define GPIO_0_BIT_MASK              BIT4
#define GPIO_0_TRIGGER_HIGH          TRUE
#define GPIO_0_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_0_IS_PARENT             TRUE
#define GPIO_0_DERATE                FALSE
#define GPIO_0_DERATE_LEVEL          0                          /* Ignored since derate is false */
#define GPIO_0_CHILD_ID              3
#define GPIO_0_IS_OUTPUT             TRUE
#define GPIO_0_HAS_CHILD             TRUE                          /* GPIO CH3 condition must also be true */

/* For GM DIS/HEI Bypass signal */
#define GPIO_1_ENABLED               TRUE
#define GPIO_1_VARIABLE	             &CoreVars_g.RPM
#define GPIO_1_UPPER_BOUNDARY        RPM(700)
#define GPIO_1_LOWER_BOUNDARY        RPM(600)
#define GPIO_1_REGISTER              (uint8_t*)&PORTA
#define GPIO_1_BIT_MASK              BIT1
#define GPIO_1_TRIGGER_HIGH          TRUE
#define GPIO_1_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_1_IS_PARENT             TRUE
#define GPIO_1_DERATE                FALSE
#define GPIO_1_DERATE_LEVEL          0                          /* Ignored since derate is false */
#define GPIO_1_CHILD_ID              1
#define GPIO_1_IS_OUTPUT             TRUE
#define GPIO_1_HAS_CHILD             FALSE

/* Over temperature derate */
#define GPIO_2_ENABLED               TRUE
#define GPIO_2_VARIABLE	             &CoreVars_g.CHT
#define GPIO_2_UPPER_BOUNDARY        DEGREES_C(107)
#define GPIO_2_LOWER_BOUNDARY        DEGREES_C(101)
#define GPIO_2_REGISTER              (uint8_t*)&PORTH
#define GPIO_2_BIT_MASK              BIT7
#define GPIO_2_TRIGGER_HIGH          TRUE
#define GPIO_2_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_2_IS_PARENT             TRUE
#define GPIO_2_DERATE                TRUE
#define GPIO_2_DERATE_LEVEL          0                          /* Ignored since derate is false */
#define GPIO_2_CHILD_ID              2
#define GPIO_2_IS_OUTPUT             TRUE
#define GPIO_2_HAS_CHILD             FALSE

/* Only allow Fans to run while engine is running */
#define GPIO_3_ENABLED               TRUE
#define GPIO_3_VARIABLE	             &CoreVars_g.RPM
#define GPIO_3_UPPER_BOUNDARY        RPM(700)
#define GPIO_3_LOWER_BOUNDARY        RPM(600)
#define GPIO_3_REGISTER              (uint8_t*)&PORTK
#define GPIO_3_BIT_MASK              BIT7
#define GPIO_3_TRIGGER_HIGH          TRUE
#define GPIO_3_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
#define GPIO_3_IS_PARENT             FALSE                       /* The chain stop here */
#define GPIO_3_DERATE                FALSE
#define GPIO_3_DERATE_LEVEL          0                           /* Ignored since derate is false */
#define GPIO_3_CHILD_ID              3 
#define GPIO_3_IS_OUTPUT             TRUE
#define GPIO_3_HAS_CHILD             FALSE                          /* Ignored by setting this value to the same as ourselves */

/* For GM DIS/HEI Bypass signal */
/* I couldn't get this one to work, but maybe I mis-configured something. */
//#define GPIO_4_ENABLED               TRUE
//#define GPIO_4_VARIABLE	       &CoreVars_g.RPM
//#define GPIO_4_UPPER_BOUNDARY        RPM(700)
//#define GPIO_4_LOWER_BOUNDARY        RPM(600)
//#define GPIO_4_REGISTER              (uint8_t*)&PORTA
//#define GPIO_4_BIT_MASK              BIT1
//#define GPIO_4_TRIGGER_HIGH          TRUE
//#define GPIO_4_OUTPUT_POLARITY       GPO_POLARITY_ENABLED_HIGH
//#define GPIO_4_IS_PARENT             TRUE
//#define GPIO_4_DERATE                FALSE
//#define GPIO_4_DERATE_LEVEL          0                           /* Ignored since derate is false */
//#define GPIO_4_CHILD_ID              4
//#define GPIO_4_IS_OUTPUT             TRUE
//#define GPIO_4_HAS_CHILD             FALSE                          /* Ignored by setting this value to the same as ourselves */

/* 2D LUTs */
#define FUEL_DELTA_PERCENTS { FD(110.0), FD(150.0), FD(175.0), FD(200.0), FD(250.0), FD(300), FD(400), FD(500)}
#define FUEL_DELTA_ADDER    { FA(100.0), FA(120.0), FA(125.0), FA(150.0), FA(175.0), FA(200), FA(250), FA(300)}

/* We reserve the first four channels for DIS 4 cylinder ignition */
#define CH0_PORT   PORTA_ADDR
#define CH0_MASK   (1 << 0)

#define CH1_PORT   PORTA_ADDR
#define CH1_MASK   (1 << 0)

#define CH2_PORT   PORTA_ADDR
#define CH2_MASK   (1 << 0)

#define CH3_PORT   PORTA_ADDR
#define CH3_MASK   (1 << 0)

/* We setup the next for channels for fuel */
#define CH4_PORT   PORTB_ADDR
#define CH4_MASK   (1 << 0)

#define CH5_PORT   PORTB_ADDR
#define CH5_MASK   (1 << 1)

#define CH6_PORT   PORTB_ADDR
#define CH6_MASK   (1 << 2)

#define CH7_PORT   PORTB_ADDR
#define CH7_MASK   (1 << 3)

/* We reserve the next two channels for stepper IAC */
#define CH8_PORT   PORTH_ADDR
#define CH8_MASK   (1 << 1)

#define CH9_PORT   PORTH_ADDR
#define CH9_MASK   (1 << 2)

/* Second set of 4 channels are for fuel */
#define CH10_PORT  PORTB_ADDR
#define CH10_MASK  (1 << 4)

#define CH11_PORT  PORTB_ADDR
#define CH11_MASK  (1 << 5)

#define CH12_PORT  PORTB_ADDR
#define CH12_MASK  (1 << 6)

#define CH13_PORT  PORTB_ADDR
#define CH13_MASK  (1 << 7)

/* Four pins on port A can be used for ignition, for more than 4 cylinders */
#define CH14_PORT  PORTA_ADDR
#define CH14_MASK  (1 << 2)

#define CH15_PORT  PORTA_ADDR
#define CH15_MASK  (1 << 3)

#define CH16_PORT  PORTA_ADDR
#define CH16_MASK  (1 << 4)

#define CH17_PORT  PORTA_ADDR
#define CH17_MASK  (1 << 5)

/* More channels, in case you need them */
#define CH18_PORT  PORTM_ADDR
#define CH18_MASK  (1 << 0)

#define CH19_PORT  PORTM_ADDR
#define CH19_MASK  (1 << 1)

#define CH20_PORT  PORTM_ADDR
#define CH20_MASK  (1 << 2)

#define CH21_PORT  PORTM_ADDR
#define CH21_MASK  (1 << 3)

#define CH22_PORT  PORTM_ADDR
#define CH22_MASK  (1 << 4)

#define CH23_PORT  PORTM_ADDR
#define CH23_MASK  (1 << 5)

#endif
