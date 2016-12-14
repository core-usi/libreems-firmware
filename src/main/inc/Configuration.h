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

#ifndef FILE_CONFIGURATION_H_SEEN
#define FILE_CONFIGURATION_H_SEEN

#include <stdint.h>

#include "memory.h"
#include "libreTypes.h"
#include "libreMath.h"
#include "systemConfig.h" //TODO remove this dep with a new build system


/* Hardware spec stuff TODO move to dedicated header */
#define SYSTEM_CLOCK        (40000000u) /* Hz */
#define SYSTEM_OSCILATOR    16 /* MHz */
#define SCI_BAUD(BAUD)      (uint32_t)ROUND(SYSTEM_CLOCK / ((double)(BAUD) * SYSTEM_OSCILATOR)) // 40MHz / (16*115.2kHz) TODO pull 40MHz out of clock rate stuff
#define TICKS_PER_SECOND    (1250000u)


#define TC7_DATA_INDEX  4
#define TC6_DATA_INDEX  3
#define TC5_DATA_INDEX  2
#define TC3_DATA_INDEX  1
#define TC2_DATA_INDEX  0

/* Config terms */
#define ENABLED                     1
#define DISABLED                    0

#define TRUE                        1
#define FALSE                       0

#define PLAIN_INJECTION             0
#define STAGED_EXTENSION            1

#define ALGO_SPEED_DENSITY          0
#define ALGO_ALPHA_N                1
#define ALGO_MAF                    2
#define ALGO_SD_AN_BLEND            3

#define IAT_VS_IGN_TABLE_LENGTH     16
#define CLT_VS_IGN_TABLE_LENGTH     16
#define IGN_VS_ETH_TABLE_LENGTH     16
#define BRV_VS_DWELL_TABLE_LENGTH   16
#define RPM_VS_DWELL_TABLE_LENGTH   16

#define MAP_LUT_TABLE_LENGTH         8
#define AAP_LUT_TABLE_LENGTH         8

#define RPM_VS_TEMP_TABLE_LENGTH     8
#define RPM_VS_STEPS_TABLE_LENGTH    8

#define EGO_LOOKUP_TABLE_LENGTH      8

#define EGT_LOOKUP_TABLE_LENGTH      8

#define FUEL_PRESSURE_TABLE_LENGTH   8

#define ENGINE_TEMP_ENRICHMENT_TABLE_LENGTH 16
#define FUEL_DELTA_VS_PERCENT_ADDER_TABLE_LENGTH 8
#define IDT_LOOKUP_TABLE_LENGTH     16
#define TEMP_VS_ASE_PERCENT_TABLE_LENGTH 16
#define TEMP_VS_PRIMING_VOLUME_TABLE_LENGTH 16
#define RPM_VS_BLEND_TABLE_LENGTH   16

#define MAF_VS_V_LUT_TABLE_SIZE     32

/* System Config */
#define XGATE_CHANNEL_COUNT         24
#define MAX_CYLINDER_COUNT          16
#define NUM_GPIO_CHANNELS           16
#define GPO_NULL_REGISTER_ADDRESS   (uint8_t *)&nullScratch
#define MAX_CAN_QUEUE               50

/* Tuner shared macros */
#define ULTIMATE_OPERATING_LIMITS_INDEX         0
#define DERATE_LEVEL_ONE_LIMITS_INDEX           1
#define DERATE_LEVEL_TWO_LIMITS_INDEX           2
#define NUM_OPERATING_LEVELS                    3
#define GPO_POLARITY_ENABLED_HIGH               1
#define GPO_POLARITY_ENABLE_LOW                 0
#define GPO_ENABLE_DERATE                       1



#if CONFIG == DEFAULT_ID
   #include "../configs/Default.h"
   #include "../configs/PowerEFI_F16.h"
#elif CONFIG == SEANKR1_ID
   #include "../configs/YamahaR1-2002-2003.h"
   #include "../configs/PowerEFI_F16.h"
#elif CONFIG == SEANKHAYABUSA_ID
   #include "../configs/Suzuki_GSXR1300_2002-2007.h"
   #include "../configs/PowerEFI_F16.h"
#elif CONFIG == SEANKLT1_ID
   #include "../configs/GM_LT1_1992-1997.h"
   #include "../configs/PowerEFI_F16.h"
#elif CONFIG == MAZDAVVT_ID
   #include "../configs/MazdaVVT.h"
   #include "../configs/PowerEFI_F16.h"
#elif CONFIG == FORD4600_ID
   #include "../configs/ModularFord4600-32v.h"
   #include "../configs/PowerEFI_F16.h"
#elif CONFIG == SBC383MALCOM_ID
   #include "../configs/SBC383_MALCOM.h"
   #include "../configs/CoolEFI_Jaguar.h"
#elif CONFIG == DEUCES10_ID
   #include "../configs/GM2200.h"
   #include "../configs/CoolEFI_Jaguar.h"
#elif CONFIG == FORDV10_ID
   #include "../configs/FordV10.h"
   #include "../configs/PowerEFI_F16.h"
#elif CONFIG == JUSTINMIATA_ID
   #include "../configs/JUSTIN_MIATA.h"
   #include "../configs/PowerEFI_F16.h"
#elif CONFIG == MITSU4G63_ID
   #include "../configs/MITSU4G63.h"
   #include "../configs/CoolEFI_BasicECU.h"
#else
   "Warning no config definded for build"
#endif

typedef enum{
  FIXED = 0,
}ValveTrainTiming;

typedef void (*InputAction)(void);    /* Function pointer for GPI */

typedef struct{
  uint16_t SC0baudDivisor;  /* Clock Divisor */
  uint8_t  SC0modeCode;     /* Mode code */
}ComSettings;

typedef struct {
  uint8_t CANenable   :1;
  uint8_t CANloopBack :1;
}CANbusSettings;

typedef struct {
  uint8_t        CANbtr0;
  uint8_t        CANbtr1;
  CANbusSettings bus;
}CANsettings;

typedef struct{
  uint16_t inputEventTollerance;
  uint16_t inputEventCrankingTollerance;
  uint16_t maxCrankingRPM;
  uint16_t filterBypassRPM;
  uint8_t  primaryEventSkipEdges;
  uint8_t  minimalSyncRequired;
}TachDecoderSettings;

typedef struct{
  /* MSB on s12x */
  uint8_t enabled:        1;  /* 1 for enabled 0 for disabled */
  uint8_t invertOutput:   1;  /* 1 for go high or 0 for go low */
  uint8_t isOutput:       1;  /* 1 for output, 0 for input */
  uint8_t derate:         1;  /* Trigger a de-rate */
  uint8_t triggerOnUpper: 1;  /* Trigger when upper boundary is crossed, else trigger when below lower boundary */
  uint8_t isParentEvent:  1;
  uint8_t hasChild:       1;
  uint8_t reserved:       1;
  /* LSB */
}GPIOChannelFlags;              /* sizeof() reports 1 byte */

typedef struct GPoutput{
  uint16_t *varPointer;       /* Pointer to the register or variable containing the upper or lower trigger value */
  InputAction inputAction;    /* Pointer to the function to be called when an input pin changes */
  uint16_t upperBoundary;
  uint16_t lowerBoundary;
    uint8_t  childIndex;        /* If event has a child, its child index should be here, if not this index should match the GPIO position */
  uint8_t  conditionCount;    /* Number of conditions that must be true */
  uint8_t  *reg;              /* Destination register/port */
  uint8_t  mask;              /* Bit mask to apply */
  uint8_t derateLevel;
  GPIOChannelFlags flags;     /* Polarity, Direction,  etc. */
}GPIOchannel;


typedef struct {
  /* MSB */
  uint8_t ECT3captureFalling : 1;
  uint8_t ECT3captureRising  : 1;
  uint8_t ECT2captureFalling : 1;
  uint8_t ECT2captureRising  : 1;
  uint8_t ECT1captureFalling : 1;
  uint8_t ECT1captureRising  : 1;
  uint8_t ECT0captureFalling : 1;
  uint8_t ECT0captureRising  : 1;
}InputCaptureEdges_TCTL4_bits;

typedef struct {
  /* MSB */
  uint8_t ECT7captureFalling : 1;
  uint8_t ECT7captureRising  : 1;
  uint8_t ECT6captureFalling : 1;
  uint8_t ECT6captureRising  : 1;
  uint8_t ECT5captureFalling : 1;
  uint8_t ECT5captureRising  : 1;
  uint8_t ECT4captureFalling : 1;
  uint8_t ECT4captureRising  : 1;
}InputCaptureEdges_TCTL3_bits;


typedef struct {
  InputCaptureEdges_TCTL4_bits bits;
  uint8_t value;
}InputCaptureEdgesTCTL4;

typedef struct {
  InputCaptureEdges_TCTL3_bits bits;
  uint8_t value;
}InputCaptureEdgesTCTL3;

typedef struct {
  uint8_t ECT7normal :1;
  uint8_t ECT6normal :1;
  uint8_t ECT5normal :1;
  uint8_t ECT4normal :1;
  uint8_t ECT3normal :1;
  uint8_t ECT2normal :1;
  uint8_t ECT1normal :1;
  uint8_t ECT0normal :1;
}ReportPolarity_bits;

typedef union {
  ReportPolarity_bits bits;
  uint8_t value;
}ReportPolarity;


typedef struct {
  InputCaptureEdgesTCTL4 inputCaptureEdgesTCTL4;
  InputCaptureEdgesTCTL3 inputCaptureEdgesTCTL3;
  ReportPolarity    reportPolarity;
}InputCaptureSettings;

typedef struct{
  uint16_t TDCAngle;
  uint16_t InjectionAngle;
  uint16_t SensorSampleAngle;
}CylinderAngleConfig;

typedef struct{
  uint8_t alphaN :       1;
  uint8_t speedDensity : 1;
  uint8_t SDAlphaBlend : 1;
  uint8_t massAir :      1;
  uint8_t flexFuel :     1;
  uint8_t deltaScaling : 1;  /* Enables or disabled the fueling delta scaler function(Accell enrichment) */
  uint8_t reserved1 :    1;
  uint8_t reserved2 :    1;
}FuelingAlgorithmFlags;

typedef struct MechanicalProperties {
  uint16_t perCylinderVolume;   ///< Displacement of each cylinder ie 5.7L / 8 = 712.5 CCs */
  int16_t  decoderInputAngleOffset;
  uint8_t  cylinderCount;       ///< The number of cylinders your engine has */
  uint8_t  revoloutionsPerCycle;  ///< The number of 360 degree revolutions needed to complete an engine cycle */
}MechanicalProperties;

typedef struct InjectionProperties {
  uint16_t injectorFlow;        ///< Fuel injector flow in CC/min */
  uint16_t secondaryInjectorFlow; ///< Same type of specification as above injectorFlow */
  uint16_t stoichiometricAFR;     ///< Stoich AFR for fixed-fuels or default for flex-fuel fail safe */
  uint16_t densityOfFuelAtSTP;    ///< Density of fuel at STP for fixed-fuels or default fail safe for flex-fuel */
  uint16_t maxPrimaryDC;          ///< Max injector duty-cycle allowed >///
  uint16_t maxSecondaryDC;        ///< Max injector duty-cycle allowed >///
  FuelingAlgorithmFlags fuelAlgoFlags;
  uint8_t  injectionStrategy;     ///< How you strategize your injections ie plain, staged etc >///
  uint8_t  fuelingStrategeyCode;   ///< Code to determine fueling stragegies >///
  uint8_t  fuelPumpMinRuntime;
}FuelingProperties;

/* Sensor ranges and fail-safe values */
typedef struct SensorProperties {

  uint16_t MAPMinimum;
  uint16_t MAPMaximum;
  uint16_t MAPFailSafe;

  uint16_t AAPMinimum;
  uint16_t AAPMaximum;
  uint16_t APPFailSafe;

  uint16_t EGOMinimum;
  uint16_t EGOMaximum;
    uint16_t EGOFailSafe;

  uint16_t BRVMinimum;
  uint16_t BRVRange;
  uint16_t BRVFailSafe;

  uint16_t TPSMinimum;
  uint16_t TPSMaximum;
  uint16_t TPSFailSafe;

  /* Engine Coolant Temperature */
    uint16_t ECTMinimum;
    uint16_t ECTMaximum;
    uint16_t ECTFailSafe;

    /* Intake Air Temperature */
    uint16_t IATMinimum;
    uint16_t IATMaximum;
    uint16_t IATFailSafe;
}SensorProperties;

typedef struct XGateOutputCHpinMapping {
  uint8_t regMask;
    uint16_t regAddress;
}XGateOutputCHpinMapping;


/* these are simple BANG BANG limits,  i.e. hard cutoff points, they are 
 * intended to be INDEPENDENT of features like launch control, revlimiting,
 * antilag and so on. They are the ULTIMATE cutoff points to prevent major
 * engine failure, and exceeding them will result in a hard cutoff of that
 * feature (fuel/ignition) in order to minimize the chance for catastrophic
 * failure
 */
typedef struct OperatingLimits {

  /* RPM (Engine RPM) Ultimate limits */
  uint16_t RPMfuelDisableLimit;      /* High RPM fuel cutoff */
  uint16_t RPMfuelEnableLimit;       /* Turn on point to re-enable fuel */
  uint16_t RPMignitionDisableLimit;  /* High RPM ignition cutoff */
  uint16_t RPMignitionEnableLimit;   /* Turn on point to re-enable ignition */

  /* MAP (Manifold Absolute Pressure) ultimate limits */
  uint16_t MAPfuelDisableLimit;     /* Max MAP to cutoff fuel */
  uint16_t MAPfuelEnableLimit;      /* MAP to re-enable fuel */
  uint16_t MAPignitionDisableLimit; /* Max MAP to cutoff ignition */
  uint16_t MAPignitionEnableLimit;    /* MAP to re-enable ignition */

}OperatingLimits;

typedef enum {
  NO_IDLE = 0,
  GM_STEPPER_IDLE,
}IdleType;

typedef struct {
  uint8_t IdleTypeID;
  uint8_t TotalIACsteps;             /* Used to re-wind after power-off */
  uint8_t IACpwLength;               /* PW required for each step mS */
  uint8_t StepperCH0num;             /* Which XGATE channel to use for opening the valve */
  uint8_t StepperCH1num;             /* Which XGATE channel to use for opening the valve */
  uint8_t PWMchannel;
}IdleControl;


/* This is where we tie it all together */
typedef struct MasterConfig {
    MechanicalProperties    mechanicalProperties;
    TachDecoderSettings     tachDecoderSettings;
    CylinderConfig          CylinderSetup[MAX_CYLINDER_COUNT];
    CylinderAngleConfig     CylindersAngles[MAX_CYLINDER_COUNT];
    FuelingProperties       fuelingProperties;
    SensorProperties        sensorProperties;
    OperatingLimits         operatingLimits[NUM_OPERATING_LEVELS];
    GPIOchannel             GPIOchannels[NUM_GPIO_CHANNELS];
    XGateOutputCHpinMapping xGateOutputCHpinMapping[XGATE_CHANNEL_COUNT];
    ComSettings             comSettings;
    IdleControl             idleControl;
    CANconfig               canConfig[MAX_CAN_QUEUE];
    CANsettings             camBusSettings;
    InputCaptureSettings    inputCaptureSettings;
    uint8_t                 numberOfPrecisionOutputs;  // The number of fuel or ign outputs that the user has setup */
    uint8_t                 numberOfDerateLevels;
    uint8_t                 numberOfDerateTriggers;
    uint8_t                 configMessage[25];
}MasterConfig;

extern MasterConfig Config CONFIG_DATA;

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
