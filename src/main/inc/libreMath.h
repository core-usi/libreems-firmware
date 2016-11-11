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
 * @ingroup communicationsFiles
 *
 * @brief Utilities
 *
 *
 */

#ifndef DATA_LIBREMATH_H_SEEN
#define DATA_LIBREMATH_H_SEEN

#include <stdint.h>

#define ROUND(FLOAT_VALUE_ONLY) ((FLOAT_VALUE_ONLY) + 0.5)


/* constants */
#define IGL_R_CONSTANT                         8.314f  /* 8.3144621(75)×103 cm3 kPa K−1 mol−1 */
#define MOLAR_MASS_AIR                         28.97f  /* Molar mass of dry air */
#define KELVIN_TO_C_OFFSET                    273.15f
#define GASOLINE_DENSITY                       0.720f  /* grams/cc */
#define E85_DENSITY                            0.770f  /* grams/cc */
#define SECONDS_PER_MINUTE                      60.0f
#define TICKS_PER_TENTH_MILI                     125U    /* Timer ticks per tenth of a millisecond */
#define DEGRESS_PER_ROTATION                       36     /* 360 degrees scaled down by 10 */
#define DEGREE_TICKS_PER_MINUTE_       (uint32_t)((((double)(1250000u * 60) / 360) * 2 * 10) + 0.5)     /* timer ticks per second */
#define DEGREE_TICKS_PER_MIN           (uint32_t)4166667u
#define DENSITY_OF_ONE_CC_OF_AIR_STP   (double)0.0012041   /*Density of dry air = 0.0012041 g/cm3 (at 20C and 101.325kPa)*/
#define ETHANOL_PERCENTAGE_LIMIT               100.0
#define MSB_32BIT                           0x80000000  /* MSB of a 16-bit word */
#define TICKS_PER_MS                           1250u      /* Ticks per millisecond */

/* factors */
#define IGL_R_F                       100U
#define IGL_UPPER_SCALE              1000U   /* ideal gas law upper derivative scale factor */
#define IGL_LOWER_SCALER             1000U   /* ideal gas law lower derivative scale factor */
#define GRAMS_SCALER                 2000U
#define MOLAR_MASS_AIR_F              100U
#define TEMPERATURE_F                 100U
#define FUEL_DENSITY_F               1000U
#define AFR_F                        1000U
#define FUELING_DELTA_LUT_FACTOR      100U
#define DEGRESS_PERCYCLE_FACTOR        72UL  /* 720/10 */
#define FLOW_SCALE_FACTOR           10000UL  /* .01 % */
#define RPM_FACTOR                      2
#define DUTY_CYCLE_FACTOR           10000ul
#define FUELING_DELTA_FACTOR        10000ul
#define IGNITION_TIMING_ENTRY_FACTOR    2
#define CC_VOLUME_F                    10U   /* Gives us the ability to define tenths of a cc */
#define ANGLE_FACTOR                   50U
#define ETHANOL_COMPOSITION_FACTOR      2U   /* How much the raw flex-fuel sensor reading is scaled. */
#define KPA_F                         100U
#define DECODER_STAMP_RATIO_F      0xFFFFu
#define FREQUENCY_REPORT_F           (100u)

//#define DECODER_RATIO_F                10

/* Conversions */
#define CEL_TO_KELVIN(C)   (C + KELVIN_TO_C_OFFSET)

/* scaled versions */
#define RPM_S(RPM)                     ((uint32_t)ROUND((RPM) * (double)RPM_FACTOR))
#define ENGINE_ANGLE_S(CRANK_DEGREES)  ((uint16_t)ROUND((CRANK_DEGREES) * (double)ANGLE_FACTOR))
#define IGL_R_S                        ((uint16_t)(IGL_R_F * IGL_R_CONSTANT))
#define MOLAR_MASS_AIR_S               ((uint16_t)(MOLAR_MASS_AIR * MOLAR_MASS_AIR_F))
#define CEL_TO_KELVIN_S(c)             ((uint16_t)((double)(c + KELVIN_TO_C_OFFSET) * TEMPERATURE_F))
#define AFR_S(ratio)                   ((uint16_t)((double)ratio * AFR_F))
#define FUEL_DENSITY_S(d)              ((uint16_t)((double)d * FUEL_DENSITY_F))
#define CC_VOLUME_S(cc)                ((uint16_t)((double)cc * CC_VOLUME_F))
#define CC_FLOW_S(cc)                  ((uint16_t)((double)cc * FUEL_DENSITY_F / SECONDS_PER_MINUTE))
#define KPA_S(k)                       ((uint16_t)((double)k * KPA_F))
//#define LAMBDA_S(l)                    ((uint16_t)((double)l * 100u))
#define GPS(GS)                        ((uint32_t)ROUND((double)G * 10000.0 * 60.0 * RPM_FACTOR))  /* Grams Per Minute */
#define GET_RPM(TPD)                   (DEGREE_TICKS_PER_MIN / TPD)
#define IT(BTDC)                       ((uint8_t)((double)BTDC *  IGNITION_TIMING_ENTRY_FACTOR))
#define DEG(ANGLE)                     ((int16_t)((double)ANGLE *  ANGLE_FACTOR))
#define TICKS_PER_DEG_RPM(RPM)         ((uint16_t)(DEGREE_TICKS_PER_MIN / (RPM * RPM_FACTOR)))
#define TICKS_PER_DEGREE_MULTIPLIER    (10 * ANGLE_FACTOR)
//#define EP(PERCENTAGE)                 ((uint16_t)ROUND((((double)PERCENTAGE) / (double)ETHANOL_PERCENTAGE_LIMIT)  * 65536))
 /* TODO revise all flex fuel % to use above macro^ and not the one below */
#define EP(PERCENTAGE)                 ((uint16_t)ROUND((((double)PERCENTAGE) * ETHANOL_COMPOSITION_FACTOR)))

#define TACH_INPUT_RATIO(p)            ((uint16_t)ROUND(((double)p * DECODER_STAMP_RATIO_F) / 100.0))

#define FD(percent)                    (uint16_t)ROUND((double)percent * FUELING_DELTA_LUT_FACTOR)
#define FA(percent)                    (uint16_t)ROUND((double)percent * FUELING_DELTA_LUT_FACTOR)
#define MS(MILLISECONDS)               ((uint32_t)ROUND((MILLISECONDS) * (double)TICKS_PER_MS))

/* Useful Constants */
#define ETHANOL_AFR_STOICH      AFR_S(9.0)
#define GASOLINE_AFR_STOICH     AFR_S(14.69)
#define PERCENT_100             100u
#define ETHANOL_DENSITY_STP     FUEL_DENSITY_S(E85_DENSITY)
#define GASOLINE_DENSITY_STP    FUEL_DENSITY_S(GASOLINE_DENSITY)



#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
