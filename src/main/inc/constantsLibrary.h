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

/* FreeEMS - the open source engine management system
 *
 * Copyright 2012-2013 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief Global physical constants and configuration library
 *
 * A convenient set of ready-to-use values for from-source builds.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template    */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual       */
#ifndef FILE_CONSTANTSLIBRARY_H_SEEN
#define FILE_CONSTANTSLIBRARY_H_SEEN


// Densities of various common fuels in grams per litre
#define DENSITYOFOCTANE_DEPRICATED FUEL_DENSITY(703)
#define DENSITYOFPETROL_DEPRICATED FUEL_DENSITY(720)
#define DENSITYOFE85_DEPRICATED    FUEL_DENSITY(770)

// Stoichiometric AFRs for various common fuels. Generated with http://www.diyefi.org/calculators.htm#stoich
#define STOICHIOMETRICAFRMETHANE  STOICH_AFR(17.245)
#define STOICHIOMETRICAFRPROPANE  STOICH_AFR(15.685)
#define STOICHIOMETRICAFRLPG      STOICH_AFR(15.599)
#define STOICHIOMETRICAFRBUTANE   STOICH_AFR(15.469)
#define STOICHIOMETRICAFROCTANE   STOICH_AFR(15.137)
#define STOICHIOMETRICAFRPETROL   STOICH_AFR(14.700)
#define STOICHIOMETRICAFRXYLENE   STOICH_AFR(13.681)
#define STOICHIOMETRICAFRTOLUENE  STOICH_AFR(13.512)
#define STOICHIOMETRICAFRBENZENE  STOICH_AFR(13.282)
#define STOICHIOMETRICAFRE85      STOICH_AFR( 9.862)
#define STOICHIOMETRICAFRETHANOL  STOICH_AFR( 9.008)
#define STOICHIOMETRICAFRMETHANOL STOICH_AFR( 6.475)

// Wide-band input common configuration values
#define LC1LAMBDAMIN                LAMBDA(0.5)
#define LC1LAMBDAMAX                LAMBDA(1.5)
#define LC1LAMBDARANGE              (LC1LAMBDAMAX - LC1LAMBDAMIN) // 1.0
#define AFR1020LAMBDAMIN            LAMBDA(0.68)
#define AFR1020LAMBDAMAX            LAMBDA(1.36)
#define AFR1020LAMBDARANGE          (AFR1020LAMBDAMAX - AFR1020LAMBDAMIN) // 0.68


/* MAP Sensor Data Explanation
 *
 * Motorola/Freescale pressure sensor data obtained from the
 * data sheets by extrapolation of the "typical" line to the
 * borders of the transfer function chart. This gives us the
 * correct values in the middle despite not being able to
 * reach the ends of the scale.
 *
 * By min and max I mean the OV and 5V pressures that aren't
 * attainable, but that give the correct function in between.
 */


/* Honda Denso 1.8bar found on 88 - ?? Honda vehicles. */
#define HONDADENSO183KPAMIN      KPA( -6.64)    /* Pressure read at lowest ADC reading */
#define HONDADENSO183KPAMAX      KPA(182.78)    /* Pressure read at highest ADC reading */
#define HONDADENSO183KPARANGE    (HONDADENSO183KPAMAX - HONDADENSO183KPAMIN)

/* Toyota 2.3bar found on some Toyota Cynos 5E-FE cars (and probably many others), em_knaps and Lev8n are responsible for this data! */
#define TOYOTANA227KPAMIN        KPA( 25)       /* Pressure read at lowest ADC reading */
#define TOYOTANA227KPAMAX        KPA(247)       /* Pressure read at highest ADC reading */
#define TOYOTANA227KPARANGE      (TOYOTANA227KPAMAX - TOYOTANA227KPAMIN)
// NOTE: The accuracy of this calibration is highly questionable. Please use the Honda units which is configured above and known to be accurate

/* GM 1bar found on naturally aspirated vehicles. Taken from http://www.robietherobot.com/storm/mapsensor.htm */
#define GM1BARMIN                KPA( 10.0)     /* Pressure read at lowest ADC reading */
#define GM1BARMAX                KPA(105.0)     /* Pressure read at highest ADC reading */
#define GM1BARRANGE              (GM1BARMAX - GM1BARMIN)

/* GM 2bar found on Cyclone Turbo V6 and probably other cars too. TODO These numbers are probably not that accurate... */
#define GM2BARMIN                KPA(  1.5)     /* Pressure read at lowest ADC reading */
#define GM2BARMAX                KPA(200.0)     /* Pressure read at highest ADC reading */
#define GM2BARRANGE              (GM2BARMAX - GM2BARMIN)

/* GM 2bar found on Cyclone Turbo V6 and probably other cars too. TODO These numbers are probably not that accurate... */
#define YAMAHADENSOMIN           KPA( 10.5)     /* Pressure read at lowest ADC reading */
#define YAMAHADENSOMAX           KPA(180.0)     /* Pressure read at highest ADC reading */
#define YAMAHADENSORANGE         (YAMAHADENSOMAX - YAMAHADENSOMIN)

/* www.freescale.com/files/sensors/doc/data_sheet/MPX4100A.pdf */
#define MPX4100AMIN              KPA( 14.0)     /* Pressure read at lowest ADC reading */
#define MPX4100AMAX              KPA(107.5)     /* Pressure read at highest ADC reading */
#define MPX4100ARANGE            (MPX4100AMAX - MPX4100AMIN)

/* www.freescale.com/files/sensors/doc/data_sheet/MPX4250A.pdf */
#define MPX4250AMIN              KPA(  8)       /* Pressure read at lowest ADC reading */
#define MPX4250AMAX              KPA(260)       /* Pressure read at highest ADC reading */
#define MPX4250ARANGE            (MPX4250AMAX - MPX4250AMIN)

#define MPXH6300AMIN             KPA( 12)       /* Pressure read at lowest ADC reading */
#define MPXH6300AMAX             KPA(320)       /* Pressure read at highest ADC reading */
#define MPXH6300ARANGE           (MPXH6300AMAX - MPXH6300AMIN)

#define MPXH6400AMIN             KPA( 12)       /* Pressure read at lowest ADC reading */
#define MPXH6400AMAX             KPA(420)       /* Pressure read at highest ADC reading */
#define MPXH6400ARANGE           (MPXH6400AMAX - MPXH6400AMIN)


// Tachometer default configuration
#define STANDARDTACHOARRAY {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}
#define STANDARDTACHOPORTS {(uint8_t*)&PORTE,(uint8_t*)&PORTK,(uint8_t*)&PORTK,(uint8_t*)&PORTK}
#define STANDARDTACHOMASKS {0x80,0x01,0x02,0x04}


#else

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
