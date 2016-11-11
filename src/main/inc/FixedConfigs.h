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
 * @brief Struct typedefs for fixed configuration
 *
 * This file contains the struct data type definitions for fixed configuration items.
 *
 * Fixed, in this context means that it typically is not tuned in a live way
 * and therefore should not be cached in RAM while running. Usually these are
 * values that do not change such as cylinder volume, injector size, cylinder
 * count and other constants related to physical aspects of the engine setup.
 * When adding configuration values, please consider adding them here first.
 * If a value doesn't need to be live tunable definitely put it here instead.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_FIXED_CONFIGS_H_SEEN
#define FILE_FIXED_CONFIGS_H_SEEN

#include <stdint.h>

/// Decoder and scheduling settings
typedef struct {
  uint8_t syncConfirmationsRunning;  ///< Upon losing sync while already running, how many sync points are required to consider resync achieved. This should be a relatively high number.
  uint8_t syncConfirmationsStarting; ///< Upon losing sync while starting, before having gained sync for the first time, how many sync points are required to consider initial sync achieved. This should be a near-zero for fast starts.
  uint16_t accelerationInputEventTimeTolerance; ///< This will be replaced: http://issues.freeems.org/view.php?id=118
  uint16_t decelerationInputEventTimeTolerance; ///< This will be replaced: http://issues.freeems.org/view.php?id=118
  uint16_t missingToothTolerance; ///< The future of this variable is uncertain!
} decoderSetting;


#define SOURCE_NORMAL 0
#define SOURCE_PRESET 1
#define SOURCE_LINEAR 2 ///< Read from the normal ADC pin, but process linearly. For bench use, mainly.

/**
 * Configuration that controls how the values of variables are determined.
 */
typedef struct {
  uint8_t BRV;
  uint8_t CHT;
  uint8_t IAT;
} sensorSource;


/** @brief Preset values for inputs and other variables
 *
 * In some cases you may want to ignore input readings and just use some
 * configured value for a particular sensor. These are the values used when you
 * choose to use a fixed reading instead of the real thing.
 */
typedef struct {
  uint16_t presetIAT;   ///< Preset variable value to override calculated values.
  uint16_t presetCHT;   ///< @copydoc presetIAT
  uint16_t presetBRV;   ///< @copydoc presetIAT

  uint16_t failsafeIATIgnition;  ///< Value to fall back on if a sensor fault is detected
  uint16_t failsafeIATInjection; ///< @copydoc failsafeIATIgnition
  uint16_t failsafeCHT; ///< @copydoc failsafeIATIgnition
  uint16_t failsafeBRV; ///< @copydoc failsafeIATIgnition
  uint16_t failsafeMAP; ///< @copydoc failsafeIATIgnition
  uint16_t failsafeAAP; ///< @copydoc failsafeIATIgnition
  uint16_t failsafeTPS; ///< @copydoc failsafeIATIgnition
} sensorPreset;


/// Ranges for sensors with linear config
typedef struct {
  int16_t   MAPMinimum;    ///< Vacuum required to make the sensor reach 0 Volt output. Theoretical only, most do not rail.
  uint16_t MAPRange;      ///< Number of kPa between 0 Volts and 5 Volts.
  uint16_t AAPMinimum;    ///< @copydoc MAPMinimum
  uint16_t AAPRange;      ///< @copydoc MAPRange
  uint16_t EGOMinimum;    ///< Lambda that 0 Volt input corresponds to.
  uint16_t EGORange;      ///< Lambda difference between what 0V and 5V inputs correspond to.
  uint16_t BRVMinimum;    ///< Battery Voltage that 0 Volt input means. 0 Volts usually. TODO YAGNI usually? always? what/why?
  uint16_t BRVRange;      ///< TODO reword when above is fixed. Real world voltage difference between lowest and highest ADC reading (0 to 5V). FreeEMS standard is 24.5 Volts for 1k and 3k9 resistors on a 12v vehicle.
  uint16_t TPSMinimumADC; ///< This should be zero, but often isn't, this value is what the TPS input reads with the throttle fully closed.
  uint16_t TPSMaximumADC; ///< This should be the maximum ADC value, but often isn't. This value is what the TPS input reads with the throttle fully open.
} sensorRange;


/// Fuel injection settings
typedef struct {
  uint16_t perCylinderVolume;   ///< 500cc = 0.5l 0.5 * 32768 = pcv, so divide by 32768 go get litres */
  uint8_t  cylinderCount;     ///< The number of cylinders your engine has  */
  uint8_t  revoloutionsPerCycle;      ///< The number of strokes needed to complete an engine cycle  */
  uint16_t injectorFlow;        ///< Injector flow of 240cc/min / 60 is 4ml/second is multiplied by 1024, so divide by 1024 for ml/second, divide by 1000 for litres/second */
  uint16_t secondaryInjectorFlow; ///< Same measurement as injectorFlow */
  uint16_t stoichiometricAFR;  ///< 34 for hydrogen, all others less, figure is 14.7 * 1024, divide by 1024 to get AFR */
  uint16_t densityOfFuelAtSTP; ///< 703gm/litre for Octane. 32 * fuel density = number, divide by 32 for the real figure */
  uint16_t maxPrimaryDC;       ///< Max injector duty-cycle allowed >///
  uint16_t maxSecondaryDC;     ///< Max injector duty-cycle allowed >///
  uint8_t  injectionStrategy; ///< How you strategize your injections ie plain, staged etc >///
} engineSetting;


/// Settings related to serial communications
typedef struct {
  uint16_t baudDivisor; ///< The number used to set the data rate. 22 = (40MHz / (16*115.2kHz)) = 21.7013889
} serialSetting;


/// Settings for coarse bit bang outputs
typedef struct {
  uint8_t outputActions[256]; ///< Nothing, On, Off, Toggle for each input event.
  uint8_t* ports[4];         ///< The addresses of the port control registers.
  uint8_t  masks[4];         ///< The masks to apply to the ports above.
  uint8_t numberConfigured;  ///< How many to loop through, max of 4
} coarseBitBangSetting;


/// Settings for ignition and injection output scheduling
typedef struct {
  uint16_t decoderEngineOffset;
  uint8_t numberOfConfiguredOutputEvents;   ///< Should match the used section of the three arrays above
} schedulingSetting;


/// Enable flags for each cut
typedef struct {
  unsigned InjectionRPM :1; ///< @todo document this
  unsigned IgnitionRPM  :1; ///< @todo document this
  unsigned InjOverBoost :1; ///< @todo document this
  unsigned IgnOverBoost :1; ///< @todo document this
  unsigned Spare0 :1;
  unsigned Spare1 :1;
  unsigned Spare2 :1;
  unsigned Spare3 :1;
  unsigned Spare4 :1;
  unsigned Spare5 :1;
  unsigned Spare6 :1;
  unsigned Spare7 :1;
  unsigned Spare8 :1;
  unsigned Spare9 :1;
  unsigned SpareA :1;
  unsigned SpareB :1;
} cutEnabled;


/// Single cut/limiter
typedef struct {
  uint16_t disableThreshold;  ///< Level at which to disable outputs
  uint16_t reenableThreshold; ///< Level at which to re-enable outputs
} singleCut;


/// Cuts and limiters
typedef struct { // Comment represents normal and recommended cut type
  singleCut InjectionRPM;       ///< Injection, enabled by default at 5k with both and 200 RPM hysteresis
  singleCut IgnitionRPM;        ///< Ignition, enabled by default at 5k with both and 220 RPM hysteresis to ensure not lean when power comes back on
  singleCut OverBoost;          ///< Ignition, enabled by default, set to rail value for sensor, with large hysteresis, requires time out to operate safely

  // Disabled by default until duties are available, then enabled and fuel duty hard coded, elec duty optional, re enabled by time out not just hysteresis
//  singleCut InjectionFuelDuty;  ///< Both, disabled by default, until duties are available
//  singleCut InjectionElecDuty;  ///< Both, disabled by default, until duties are available

  // These require other logic in addition to the generic logic:
//  singleCut TwoStep;            ///< Ignition only or both, disabled by default
//  singleCut OverHeat;           ///< Ignition only or both, disabled by default
//  singleCut Overrun;            ///< Injection, disabled by default
//  singleCut FloodClear;         ///< Injection, disabled by default
  cutEnabled cutsEnabled;       ///< Override hard code on for desired fuel duty not to exceed 102.4% or similar
} cutAndLimiterSetting;


typedef struct {
  uint16_t* variable;
  uint16_t upperValue;
  uint16_t lowerValue;
  uint8_t* port;
  uint8_t mask;
  uint8_t flags; // for go high or low on success.
} singleSimpleGPOutput;


#define NUMBER_OF_OUTPUT_CONFIGS 8
typedef struct {
  singleSimpleGPOutput outputConfigs[NUMBER_OF_OUTPUT_CONFIGS];
  uint8_t numberConfigured;
  uint8_t spare;
} simpleGPIOSetting;


/// Settings related to sensor reading
typedef struct {
  uint16_t readingTimeout; ///< How often an ADC reading MUST occur.
  uint8_t fuelPumpPrimePeriod;
} sensorSetting;


#define LOAD_MAP 0
#define LOAD_TPS 1
#define LOAD_MAF 2
#define LOAD_AAP 3

//#define ALGO_SPEED_DENSITY 0
//#define ALGO_ALPHA_N       1
//#define ALGO_MAF           2
//#define ALGO_SD_AN_BLEND   3

#define DWELL_BRV   0
#define DWELL_RPM   1
#define DWELL_FIXED 2

/// Settings for fueling algorithms
typedef struct {
  uint8_t loadType;
  uint8_t algorithmType;
  uint8_t dwellType;
  uint8_t padding;
  uint16_t dwellFixedPeriod;
} algorithmSetting;


/// Input output pin usage configuration @todo TODO document this better
typedef struct {
//  uint8_t PullUpEnable;      ///< Enables per-port weak (~100k) internal pullups. See section 22.3.2.11 on page 834 of MC9S12XDP512RMV2.pdf
//  uint8_t ReducedDrive;      ///< Do NOT change this! This reduces drive strength and could harm your engine. See section 22.3.2.12 on page 835 of MC9S12XDP512RMV2.pdf
  uint8_t PWMEnable;         ///< Enables the PWM functionality for each pin. Note for 16 bit you the low order bit enabled. See section 8.3.2.1 on page 368 of MC9S12XDP512RMV2.pdf
  uint8_t PWMPolarity;       ///< Inverts the duty of the output. 1 means "duty is high portion", 0 means "duty is low portion". See section 8.3.2.2 on page 370 of MC9S12XDP512RMV2.pdf
  uint8_t PWMClock;          ///< TODO abstract this away
  uint8_t PWMClockPrescaler; ///< TODO abstract this away
  uint8_t PWMCenterAlign;    ///< See section 8.3.2.5 on page 372 of MC9S12XDP512RMV2.pdf
  uint8_t PWMControl;        ///< The high four bits concatenate the 8 bit PWM channels into 4 16 bit channels on a pair by pair basis. 4 joins (0,1), 5 joins (2,3), 6 joins (4,5), 7 joins (6,7).
  uint8_t PWMScalerA;        ///< TODO abstract this away
  uint8_t PWMScalerB;        ///< TODO abstract this away

  uint8_t PWMPeriod0; ///< TODO abstract this away
  uint8_t PWMPeriod1; ///< TODO abstract this away
  uint8_t PWMPeriod2; ///< TODO abstract this away
  uint8_t PWMPeriod3; ///< TODO abstract this away
  uint8_t PWMPeriod4; ///< TODO abstract this away
  uint8_t PWMPeriod5; ///< TODO abstract this away
  uint8_t PWMPeriod6; ///< TODO abstract this away
  uint8_t PWMPeriod7; ///< TODO abstract this away

  uint8_t PWMInitialDuty0; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
  uint8_t PWMInitialDuty1; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
  uint8_t PWMInitialDuty2; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
  uint8_t PWMInitialDuty3; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
  uint8_t PWMInitialDuty4; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
  uint8_t PWMInitialDuty5; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
  uint8_t PWMInitialDuty6; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
  uint8_t PWMInitialDuty7; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.

  uint8_t PortInitialValueA; ///< The state of the port at power up. @see PortDirectionA
  uint8_t PortInitialValueB; ///< The state of the port at power up. @see PortDirectionB
  uint8_t PortInitialValueC; ///< The state of the port at power up. @see PortDirectionC
  uint8_t PortInitialValueD; ///< The state of the port at power up. @see PortDirectionD
  uint8_t PortInitialValueE; ///< The state of the port at power up. @see PortDirectionE
  uint8_t PortInitialValueH; ///< The state of the port at power up. @see PortDirectionH
  uint8_t PortInitialValueJ; ///< The state of the port at power up. @see PortDirectionJ
  uint8_t PortInitialValueK; ///< The state of the port at power up. @see PortDirectionK
  uint8_t PortInitialValueM; ///< The state of the port at power up. @see PortDirectionM
  uint8_t PortInitialValueP; ///< The state of the port at power up. @see PortDirectionP
  uint8_t PortInitialValueS; ///< The state of the port at power up. @see PortDirectionS
  uint8_t PortInitialValueT; ///< The state of the port at power up. @see PortDirectionT Currently this setting is ignored. TODO Make it take effect on unused port T pins.

  uint8_t PortDirectionA; ///< @see PortDirectionB Pin 6 is the Firmware Load switch input AND the Check Engine Light output. Pin 7 is the standard fuel pump relay drive pin. These bits are therefore overridden and have no effect.
  uint8_t PortDirectionB; ///< Whether pins act as inputs or outputs, 1 means output, 0 means input. 0 is the default for most pins. Note, peripheral modules which use these pins override this control.
  uint8_t PortDirectionC; ///< @see PortDirectionB
  uint8_t PortDirectionD; ///< @see PortDirectionB
  uint8_t PortDirectionE; ///< @see PortDirectionB This port is associated with various control bits. Extreme care should be taken when using them, regardless of what for. Pins 0 and 1 are always inputs regardless of this setting.
  uint8_t PortDirectionH; ///< @see PortDirectionB This port is associated with the SPI1 (0-3), SPI2 (4-7), SCI4 (4,5), and SCI5 (6,7) modules.
  uint8_t PortDirectionJ; ///< @see PortDirectionB This port is associated with the SCI2 (0,1), I2C0 (6,7), I2C1 (4,5), and CAN4 (6,7) modules.
  uint8_t PortDirectionK; ///< @see PortDirectionB
  uint8_t PortDirectionM; ///< @see PortDirectionB This port is associated with the CAN0 (0,1), CAN1 (2,3), CAN2 (4,5), CAN3 (6,7), and SCI3 (6,7) modules.
  uint8_t PortDirectionP; ///< @see PortDirectionB This port is associated with the PWM (0-7) module.
  uint8_t PortDirectionS; ///< @see PortDirectionB This port is associated with the SCI0 (0,1), SCI1 (2,3), and SPI0 (4-7) modules. Primary communication is over SCI0, therefore the control bits for those pins are overridden to ensure correct operation, and have no effect.
  uint8_t PortDirectionT; ///< @see PortDirectionB This port is associated with the ECT (0-7) module. Currently this setting is ignored. TODO Make it take effect on unused port T pins.
} inputOutputSetting;


#define USER_TEXT_FIELD_ARRAY_LENGTH1 (FLASHSECTORSIZE - (sizeof(engineSetting) + sizeof(serialSetting) + sizeof(coarseBitBangSetting) + sizeof(schedulingSetting) + sizeof(cutAndLimiterSetting) + sizeof(simpleGPIOSetting)))
/**
 * One of two structs of fixed configuration data such as physical parameters etc.
 *
 * If you add something here, please ensure you update all of the following :
 * - Default values in the initial definitions in FixedConfig1.c and FixedConfig2.c
 * - The lookupBlockDetails() function in blockDetailsLookup.c
 * - The JSON data map and other related firmware interface definition files
 */
typedef struct {
  engineSetting engineSettings; ///< @see engineSetting
  serialSetting serialSettings; ///< @see serialSetting
  coarseBitBangSetting coarseBitBangSettings; ///< @see coarseBitBangSetting
  schedulingSetting schedulingSettings;       ///< @see schedulingSetting
  cutAndLimiterSetting cutAndLimiterSettings; ///< @see cutAndLimiterSetting
  simpleGPIOSetting simpleGPIOSettings;       ///< @see simpleGPIOSetting
} fixedConfig1;


#define USER_TEXT_FIELD_ARRAY_LENGTH2 (FLASHSECTORSIZE - (sizeof(sensorSource) + sizeof(sensorPreset) + sizeof(sensorRange) + sizeof(sensorSetting) + sizeof(algorithmSetting) + sizeof(inputOutputSetting) + sizeof(decoderSetting)))
/** @copydoc fixedConfig1 */
typedef struct {
  sensorSource sensorSources;                              ///< @see sensorSource
  sensorPreset sensorPresets;                              ///< @see sensorPreset
  sensorRange sensorRanges;                                ///< @see sensorRange
  sensorSetting sensorSettings;                            ///< @see sensorSetting
  algorithmSetting algorithmSettings;                      ///< @see algorithmSetting
  inputOutputSetting inputOutputSettings;                  ///< @see inputOutputSetting
  decoderSetting decoderSettings;                          ///< @see decoderSetting
} fixedConfig2;

extern const volatile fixedConfig1 fixedConfigs1; //FIXME create header file for the instance source


#else
  /* let us know if we are being untidy with headers */
  #warning "Header file FIXED_CONFIGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
