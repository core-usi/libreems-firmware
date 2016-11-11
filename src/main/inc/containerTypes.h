/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2013 Fred Cooke
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
 * @ingroup dataStructures
 *
 * @brief Container struct typedefs
 *
 * This file contains all of the data container struct typedefs used for calculations.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_CONTAINER_TYPES_H_SEEN
#define FILE_CONTAINER_TYPES_H_SEEN

#include "libreTypes.h"

/** Use this block to ensure that the components are contiguous and we can then reference
 * them via offsets and pointers (NC= Not (likely) connected).
 */
typedef struct {
  /* ADC0 raw readings */
  uint16_t IAT;       ///< Inlet Air Temperature
  uint16_t CHT;       ///< Coolant / Head Temperature
  uint16_t TPS;       ///< Throttle Position Sensor
  uint16_t EGO;       ///< Exhaust Gas Oxygen
  uint16_t MAP;       ///< Manifold Absolute Pressure
  uint16_t AAP;       ///< Atmospheric Absolute Pressure
  uint16_t BRV;       ///< Battery Reference Voltage
  uint16_t MAT;       ///< Manifold Air Temperature

  /* ADC1 raw readings (Subject to change! http://issues.freeems.org/view.php?id=190) */
  uint16_t FuelPressure;
  uint16_t IAP;       ///< Intercooler Absolute Pressure
  uint16_t MAF;       ///< Mass Air Flow
  uint16_t SpareADC3; ///< Spare ADC1 port 3
  uint16_t SpareADC4; ///< Spare ADC1 port 4
  uint16_t SpareADC5; ///< Spare ADC1 port 5
  uint16_t SpareADC6; ///< Spare ADC1 port 6
  uint16_t EGT;      ///< EGT
} ADCBuffer;


/// Use this block to make it easy to manage the core variables.
typedef struct {
  /* Calculated and averaged from ADC0 readings */
  uint16_t IAT;   ///< Inlet Air Temperature           : 0.0 -   655.35       (0.01 Kelvin (/100))
  uint16_t CHT;   ///< Coolant / Head Temperature      : 0.0 -   655.35       (0.01 Kelvin (/100))
  uint16_t TPS;   ///< Throttle Position Sensor        : 0.0 -   102.398438   (0.0015625 % (/640))
  uint16_t EGO;   ///< Exhaust Gas Oxygen              : 0.0 -     1.99996948 (0.0000305175781 lambda (/32768))
  uint16_t MAP;   ///< Manifold Absolute Pressure      : 0.0 -   655.35       (0.01 kPa (/100))
  uint16_t AAP;   ///< Atmospheric Absolute Pressure   : 0.0 -   655.35       (0.01 kPa (/100))
  uint16_t BRV;   ///< Battery Reference Voltage       : 0.0 -    65.535      (0.001 Volts (/1000))
  uint16_t MAT;   ///< Manifold Air Temperature        : 0.0 -   655.35       (0.01 Kelvin (/100))

  /* Calculated and averaged from ADC1 readings (Subject to change! http://issues.freeems.org/view.php?id=190) */
  uint16_t EGT;  ///< Exhaust Gas Temperature              : 0.0 -     1.99996948 (0.0000305175781 lambda (/32768))
  uint16_t IAP;   ///< Intercooler Absolute Pressure   : 0.0 -   655.35       (0.01 kPa (/100))
  uint16_t MAF;   ///< Mass Air Flow                   : 0.0 - 65535.0        (raw units from lookup)

  /* Calculated from MAP and TPS history */
  uint16_t DMAP;  ///< Delta MAP kPa/second or similar
  uint16_t DTPS;  ///< Delta TPS %/second or similar

  /* Calculated from engine position data */
  uint16_t RPM;   ///< Revolutions Per Minute (Calced) : 0.0 - 32767.5        (0.5 RPM (/2))
  uint16_t FuelPressure;  ///< Delta RPM (Calced)              : 0.0 - 32767.5        (0.5 RPM/Second (/2))
  uint16_t EthanolPercentage;

} CoreVar;


/** Use this block to make it easy to manage the derived variables.
 * Calculated from core vars stored in CoreVar .
 */
typedef struct {
  /*  */
  uint16_t LoadMain;       ///< Configurable unit of load, same scale as VE by default
  uint16_t VEMain;         ///< Divide by 512 to get 0 - 128%
  uint16_t Lambda;         ///< Divide by 32768 to get Lamda 0 - 2.0

  // TODO remove these:
  uint16_t AirChargeMass;      /* Only here for logging TODO refactor & remove*/
  uint16_t StoichAFR;

  uint16_t FuelDensity;
  uint16_t ETE;            ///< Engine Temperature Enrichment percentage correction divide by 327.68 for 0 - 200%
  int16_t TFCTotal;         ///< Transient fuel correction PW (+/-) divide by PW_TICK_FACTOR for milli seconds

  uint16_t Displacement;   /* Combustion displacement per unit/cyl */
  uint16_t IDT;            ///< PW duration before fuel flow begins, before per channel corrections, divide by PW_TICK_FACTOR for milli seconds
  uint16_t RefPW;          ///< Reference electrical PW what each cylinder is based on, used for all general decisions, divide by PW_TICK_FACTOR for milli seconds

  uint16_t Advance;        ///< Ignition advance (scaled degrees / ANGLE_FACTOR = degrees)
  uint16_t Dwell;          ///< Dwell period, divide by PW_TICK_FACTOR for milli seconds
} DerivedVar;


/// Important "always send" stuff for datalogging
typedef struct {
  // To be improved MAJORLY:
  uint8_t tempClock;       ///< Incremented once per log sent
  CANbusStatus canStatus;

  // All flags! Pair keeps things sane for hacky apps that think everything is 16 bit.
  uint8_t coreStatusA;     ///< Duplicated, migrate here, remove global var
  uint8_t spare0;    ///< Various decoder state flags
  uint16_t flaggableFlags; ///< Flags to go with our flaggables struct.
  // counter flags once counter mechanism implemented

  // Likewise these too
  uint16_t serialOverrunErrors;         ///< Incremented when an overrun occurs due to high interrupt load, not a fault, just a fact of life at high RPM
                                             ///< It's a dual-core MCU, there are no excuses for this and it should be fixed -sk
  uint8_t serialHardwareErrors;        ///< Sum of noise, parity, and framing errors
  uint8_t serialAndCommsCodeErrors;    ///< Sum of checksum, escape mismatches, starts inside, and over/under length

  // TODO move this up above with the other flags post OLV 0.0.3 release
  uint16_t flaggableFlags2; ///< Flags to go with our flaggables2 struct.

  // replace highest first to avoid hassles for offset based dave/mtx...
  uint16_t debugMessageCnt;  ///< Count of debug"syslog" messages sent
  uint16_t zsp8;  ///< Spare US variable
  uint16_t SecondaryInjDC;  ///< Spare US variable
  uint16_t PrimaryInjDC;  ///< Spare US variable

  // TODO move these:
  uint16_t blendAlphaNPercent;  ///< TODO migrate to correct place once OLV/EMStudio are flexible...
  uint16_t speedDensityAirFlow; ///< TODO migrate to correct place once OLV/EMStudio are flexible...
  uint16_t alphaNAirFlow;       ///< TODO migrate to correct place once OLV/EMStudio are flexible...

  // Do we want these recorded at log assembly time, or at recording of ADC time, or at calculation of vars (core and/or deriv) or at enabling of scheduling, or all of the above?
  uint16_t clockInMilliSeconds; ///< Migrate to start of all large datalogs once analysed
  uint16_t clockIn8thsOfAMilli; ///< Migrate to start of all large datalogs once analysed
  uint16_t fuelingDelta;
  uint16_t CANbytesRx;
  uint16_t CANframesRx;
  uint8_t ignitionCuts;  ///< Up to 8 reasons to not schedule ignition
  uint8_t injectionCuts; ///< Up to 8 reasons to not schedule injection

} KeyUserDebug;


/// Active flags for each injection cut
typedef struct { // BIT7 at the top
  unsigned Spare7 :1;
  unsigned Spare6 :1;
  unsigned Spare5 :1;
  unsigned Spare4 :1;
  unsigned InjSelfClock :1; ///< @todo document this
  unsigned InjLostPLL   :1; ///< @todo document this
  unsigned InjOverBoost :1; ///< @todo document this
  unsigned InjectionRPM :1; ///< @todo document this
} injectionCutFlags; // BIT0 at the bottom


/// Active flags for each ignition cut
typedef struct { // BIT7 at the top
  unsigned Spare7 :1;
  unsigned Spare6 :1;
  unsigned Spare5 :1;
  unsigned Spare4 :1;
  unsigned IgnSelfClock :1; ///< @todo document this
  unsigned IgnLostPLL   :1; ///< @todo document this
  unsigned IgnOverBoost :1; ///< @todo document this
  unsigned IgnitionRPM  :1; ///< @todo document this
} ignitionCutFlags; // BIT0 at the bottom


/* Individual fuel channel data that is needed for fuel trim and transient corrections */
typedef struct {
  uint32_t  calcTime;             ///< used for TPS and other delta calcs
  uint16_t throttlePosition;     ///< used for TPS delta calculation
  uint16_t airFlowCalc;          ///< used for fuel delta calculation
  uint16_t primaryPulseWidth;    ///< used by the output scheduler
  uint16_t secondaryPulseWidth;  ///< used by the output scheduler
  uint8_t  statusFlags;          ///< flags such as consumed etc
} individualFuelChannel;


#else
  /* let us know if we are being untidy with headers */
  #warning "Header file CONTAINER_TYPES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
