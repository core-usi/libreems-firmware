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

#ifndef FILE_FIELDDESCRIPTOR_H_SEEN
#define FILE_FIELDDESCRIPTOR_H_SEEN

#include "memory.h"

/* Multipliers */
const int8_t MULT_000000083333[] FD_MISC_PAGE = "0.00000083333";
const int8_t MULT_000000166666[] FD_MISC_PAGE = "0.00000166666";
const int8_t MULT_00000305175781[] FD_MISC_PAGE = "0.0000305175781";
const int8_t MULT_00008[] FD_MISC_PAGE = "0.0008";
const int8_t MULT_000153054977[] FD_MISC_PAGE = "0.00153054977";
const int8_t MULT_00015625[] FD_MISC_PAGE = "0.0015625";
const int8_t MULT_0001953125[] FD_MISC_PAGE = "0.001953125";
const int8_t MULT_0001[] FD_MISC_PAGE = "0.001";
const int8_t MULT_00048828125[] FD_MISC_PAGE = "0.0048828125";
const int8_t MULT_000610360875[] FD_MISC_PAGE = "0.00610360875";
const int8_t MULT_001[] FD_MISC_PAGE = "0.01";
const int8_t MULT_002[] FD_MISC_PAGE = "0.02";
const int8_t MULT_004[] FD_MISC_PAGE = ".04";
const int8_t MULT_05[] FD_MISC_PAGE = "0.5";
const int8_t MULT_1[] FD_MISC_PAGE = "1";

/* Adders */
const int8_t ADD_0[] FD_MISC_PAGE = "0";
const int8_t ADD_27315[] FD_MISC_PAGE = "-273.15";

/* Names */
const int8_t NAME_AAP[] FD_NAME_PAGE = "AAP";
const int8_t NAME_AIRFLOW[] FD_NAME_PAGE = "AirFlow";
const int8_t NAME_ANGLE_OFFSET[] FD_NAME_PAGE = "Angle Offset";
const int8_t NAME_BRV[] FD_NAME_PAGE = "BRV";
const int8_t NAME_CAN_STATUS_BITS[] FD_NAME_PAGE = "CAN Status Bits";
const int8_t NAME_CHT[] FD_NAME_PAGE = "CHT";
const int8_t NAME_CLOCKINMILLISECONDS[] FD_NAME_PAGE = "clockInMilliSeconds";
const int8_t NAME_CORESTATUSA[] FD_NAME_PAGE = "coreStatusA";
const int8_t NAME_DECODER_FLAGS[] FD_NAME_PAGE = "Decoder Flags";
const int8_t NAME_DISPLACEMENT[] FD_NAME_PAGE = "Displacement";
const int8_t NAME_DMAP[] FD_NAME_PAGE = "DMAP";
const int8_t NAME_DTPS[] FD_NAME_PAGE = "DTPS";
const int8_t NAME_EGO[] FD_NAME_PAGE = "EGO";
const int8_t NAME_EGT[] FD_NAME_PAGE = "EGT";
const int8_t NAME_ENGINE_ANGLE[] FD_NAME_PAGE = "Engine Angle";
const int8_t NAME_ETE[] FD_NAME_PAGE = "ETE";
const int8_t NAME_ETHANOLPERCENTAGE[] FD_NAME_PAGE = "EthanolPercentage";
const int8_t NAME_FLAGGABLEFLAGS[] FD_NAME_PAGE = "flaggableFlags";
const int8_t NAME_FUELDENSITY[] FD_NAME_PAGE = "FuelDensity";
const int8_t NAME_FUEL_PRESSURE[] FD_NAME_PAGE = "Fuel Pressure";
const int8_t NAME_GRAMS_SECOND[] FD_NAME_PAGE = "Grams/Second";
const int8_t NAME_HZ[] FD_NAME_PAGE = "Hz";
const int8_t NAME_IAP[] FD_NAME_PAGE = "IAP";
const int8_t NAME_IAT[] FD_NAME_PAGE = "IAT";
const int8_t NAME_IGNITION_CUT_BITS[] FD_NAME_PAGE = "Ignition Cut Bits";
const int8_t NAME_INJECTIONCUTS[] FD_NAME_PAGE = "injectionCuts";
const int8_t NAME_LAMBDA[] FD_NAME_PAGE = "Lambda";
const int8_t NAME_LOADMAIN[] FD_NAME_PAGE = "LoadMain";
const int8_t NAME_MAF_VOLTAGE[] FD_NAME_PAGE = "MAF Voltage";
const int8_t NAME_MAP[] FD_NAME_PAGE = "MAP";
const int8_t NAME_MAT[] FD_NAME_PAGE = "MAT";
const int8_t NAME_PERCENT[] FD_NAME_PAGE = "Percent";
const int8_t NAME_PRIMARY_DECODER_ISR_VARIANCE[] FD_NAME_PAGE = "Primary Decoder ISR Variance";
const int8_t NAME_REFPW[] FD_NAME_PAGE = "RefPW";
const int8_t NAME_RPM[] FD_NAME_PAGE = "RPM";
const int8_t NAME_STOICHAFR[] FD_NAME_PAGE = "StoichAFR";
const int8_t NAME_TFCTOTAL[] FD_NAME_PAGE = "TFCTotal";
const int8_t NAME_TIMING_TABLE_ENTRY[] FD_NAME_PAGE = "Timing Table Entry";
const int8_t NAME_TPS[] FD_NAME_PAGE = "TPS";
const int8_t NAME_UNDEFINED[] FD_NAME_PAGE = "Undefined";
const int8_t NAME_UNSIGNED_16_BIT[] FD_NAME_PAGE = "U16";
const int8_t NAME_UNSIGNED_32_BIT[] FD_NAME_PAGE = "U32";
const int8_t NAME_UNSIGNED_8_BIT[] FD_NAME_PAGE = "U8";
const int8_t NAME_USEC[] FD_NAME_PAGE = "uSec";
const int8_t NAME_VEMAIN[] FD_NAME_PAGE = "VEMain";
const int8_t NAME_VOLTS[] FD_NAME_PAGE = "Volts";

/* Suffixes */
const int8_t SFX_CALLSTOUNIMPLMENTEDISRS[] FD_MISC_PAGE = "CallsToUnimplmentedISRs";
const int8_t SFX_CAMLOCK[] FD_MISC_PAGE = "CamLock";
const int8_t SFX_CAN_BUS_SYNC[] FD_MISC_PAGE = "CAN Bus Sync";
const int8_t SFX_CRANKLOCK[] FD_MISC_PAGE = "CrankLock";
const int8_t SFX_DECODERSYNCCORRECTIONS[] FD_MISC_PAGE = "DecoderSyncCorrections";
const int8_t SFX_DECODERSYNCLOSSES[] FD_MISC_PAGE = "DecoderSyncLosses";
const int8_t SFX_DECODERSYNCSTATECLEARS[] FD_MISC_PAGE = "DecoderSyncStateClears";
const int8_t SFX_DEGREES[] FD_MISC_PAGE = "degrees";
const int8_t SFX_FUELPUMPPRIME[] FD_MISC_PAGE = "FuelPumpPrime";
const int8_t SFX_IGNITIONCUROVERBOOST[] FD_MISC_PAGE = "IgnitioncurOverBoost";
const int8_t SFX_IGNITIONCUTOVERRPM[] FD_MISC_PAGE = "IgnitionCutOverRPM";
const int8_t SFX_INITAK_FIRST[] FD_MISC_PAGE = "INITAK First";
const int8_t SFX_INITAK_SECOND[] FD_MISC_PAGE = "INITAK Second";
const int8_t SFX_INJECTIONCUTOVERBOOST[] FD_MISC_PAGE = "InjectionCutOverBoost";
const int8_t SFX_INJECTIONCUTOVERRPM[] FD_MISC_PAGE = "InjectionCutOverRPM";
const int8_t SFX_INJECTIONLOSTPLLSYNC[] FD_MISC_PAGE = "InjectionLostPLLSync";
const int8_t SFX_INJECTIONLOSTSELFCLOCK[] FD_MISC_PAGE = "InjectionLostSelfClock";
const int8_t SFX_KPA[] FD_MISC_PAGE = "kPa";
const int8_t SFX_LOWVOLTAGECONDITIONS[] FD_MISC_PAGE = "LowVoltageConditions";
const int8_t SFX_MINIMALLOCK[] FD_MISC_PAGE = "MinimalLock";
const int8_t SFX_MS[] FD_MISC_PAGE = "mS";
const int8_t SFX_PERCENT[] FD_MISC_PAGE = "%";
const int8_t SFX_PREVIOUSPRIMARYEVENTVALID[] FD_MISC_PAGE = "PreviousPrimaryEventValid";
const int8_t SFX_PREVIOUSSECONDARYEVENTVALID[] FD_MISC_PAGE = "PreviousSecondaryEventValid";
const int8_t SFX_PRIMARYPERIODVALID[] FD_MISC_PAGE = "PrimaryPeriodValid";
const int8_t SFX_SERIALCHECKSUMMISMATCHES[] FD_MISC_PAGE = "SerialChecksumMismatches";
const int8_t SFX_SERIALESCAPEPAIRMISMATCHES[] FD_MISC_PAGE = "SerialEscapePairMismatches";
const int8_t SFX_SERIALFRAMINGERRORS[] FD_MISC_PAGE = "SerialFramingErrors";
const int8_t SFX_SERIALNOISEERRORS[] FD_MISC_PAGE = "SerialNoiseErrors";
const int8_t SFX_SERIALOVERRUNERRORS[] FD_MISC_PAGE = "SerialOverrunErrors";
const int8_t SFX_SERIALPACKETSOVERLENGTH[] FD_MISC_PAGE = "SerialPacketsOverLength";
const int8_t SFX_SERIALPACKETSUNDERLENGTH[] FD_MISC_PAGE = "SerialPacketsUnderLength";
const int8_t SFX_SERIALPARITYERRORS[] FD_MISC_PAGE = "SerialParityErrors";
const int8_t SFX_SERIALSTARTSINSIDEAPACKET[] FD_MISC_PAGE = "SerialStartsInsideAPacket";

/* Descriptions */
const int8_t FD_UNDEFINED_TABLE_FOUND[] FD_DESC_PAGE = "Undefined table found.";
const int8_t FD_0_255_UNSIGNED_DATA[] FD_DESC_PAGE = "0-255 unsigned data";
const int8_t FD_0_65535_UNSIGNED_DATA[] FD_DESC_PAGE = "0-65535 unsigned data";
const int8_t FD_0_0XFFFFFFFF_UNSIGNED_DATA[] FD_DESC_PAGE = "0-0xFFFFFFFF unsigned data";
const int8_t FD_INLET_AIR_TEMPERATURE_CELSIUS[] FD_DESC_PAGE = "Inlet Air Temperature (Celsius)";
const int8_t FD_ADVANCE_IN_DEGREES_BTDC[] FD_DESC_PAGE = "Advance in degrees BTDC";
const int8_t FD_COOLANT_OR_HEAD_TEMPERATURE_CELSIUS[] FD_DESC_PAGE = "Coolant or Head Temperature (Celsius)";
const int8_t FD_THROTTLE_POSITION_SENSOR[] FD_DESC_PAGE = "Throttle Position Sensor";
const int8_t FD_EXHAUST_GAS_OXYGEN_LAMBDA[] FD_DESC_PAGE = "Exhaust Gas Oxygen (Lambda)";
const int8_t FD_MANIFOLD_ABSOLUTE_PRESSURE[] FD_DESC_PAGE = "Manifold Absolute Pressure";
const int8_t FD_ATMOSPHERE_ABSOLUTE_PRESSURE[] FD_DESC_PAGE = "Atmosphere Absolute Pressure";
const int8_t FD_BATTERY_REFERENCE_VOLTAGE[] FD_DESC_PAGE = "Battery Reference Voltage";
const int8_t FD_MANIFOLD_AIR_TEMPERATURE[] FD_DESC_PAGE = "Manifold Air Temperature";
const int8_t FD_EXHAUST_GAS_TEMPERATURE[] FD_DESC_PAGE = "Exhaust Gas Temperature";
const int8_t FD_AIRFLOW_IN_GRAMS_PER_SECOND[] FD_DESC_PAGE = "Airflow in Grams per second.";
const int8_t FD_INTERCOOLER_ABSOLUTE_PRESSURE[] FD_DESC_PAGE = "Intercooler Absolute Pressure";
const int8_t FD_MASS_AIR_FLOW[] FD_DESC_PAGE = "Mass Air Flow";
const int8_t FD_MAP_RATE_OF_CHANGE[] FD_DESC_PAGE = "MAP rate of change";
const int8_t FD_TPS_RATE_OF_CHANGE[] FD_DESC_PAGE = "TPS rate of change";
const int8_t FD_INSTANT_ENGINE_RPM[] FD_DESC_PAGE = "Instant Engine RPM";
const int8_t FD_FUEL_PRESSURE_KPA[] FD_DESC_PAGE = "Fuel Pressure (KPA)";
const int8_t FD_PERCENTAGE_OF_ETHANOL_IN_YOUR_FUEL[] FD_DESC_PAGE = "Percentage of Ethanol in your fuel";
const int8_t FD_ENGINE_ANGLE_0_720[] FD_DESC_PAGE = "Engine Angle 0-720.";
const int8_t FD_PULSEWIDTH_IN_USEC[] FD_DESC_PAGE = "Pulsewidth in uSec.";
const int8_t FD_MEASURED_FREQUENCY[] FD_DESC_PAGE = "Measured Frequency.";
const int8_t FD_ALGORITHM_DEPENDENT_REPRESENTATION_OF_ENGINE_LOAD[] FD_DESC_PAGE = "Algorithm dependent representation of engine load";
const int8_t FD_CURRENT_VOLUMETRIC_EFFICIENCY[] FD_DESC_PAGE = "Current Volumetric Efficiency";
const int8_t FD_DESIRED_LAMBDA[] FD_DESC_PAGE = "Desired Lambda";
const int8_t FD_ALGORITHM_INDEPENDENT_AIRFLOW_CALCULATION[] FD_DESC_PAGE = "Algorithm independent airflow calculation.";
const int8_t FD_CALCULATED_AFR_IE_FLEX_FUEL_OR_FIXED_FUEL[] FD_DESC_PAGE = "Calculated AFR ie Flex Fuel Or Fixed Fuel";
const int8_t FD_CALCULATED_FUEL_DENSITY[] FD_DESC_PAGE = "Calculated Fuel Density";
const int8_t FD_ENGINE_TEMPERATURE_ENRICHMENT_PERCENTAGE[] FD_DESC_PAGE = "Engine Temperature Enrichment percentage";
const int8_t FD_TRANSIENT_FUEL_CORRECTION_PW[] FD_DESC_PAGE = "Transient Fuel correction PW";
const int8_t FD_DISPLACEMENT_PER_COMBUSTION_UNIT_CYL[] FD_DESC_PAGE = "Displacement per combustion unit/cyl";
const int8_t FD_REFERENCE_PW_IE_ACTUAL_PW_BEFORE_TRIMS_ARE_APPLIED[] FD_DESC_PAGE = "Reference PW (i.e. actual PW before trims are applied)";
const int8_t FD_CAN_BUS_STATUS_BITS[] FD_DESC_PAGE = "CAN Bus Status Bits";
const int8_t FD_STATUS_BITS_REGISTER_A[] FD_DESC_PAGE = "Status Bits Register 'A'";
const int8_t FD_COUNTER_INCREMENTED_STATUS_BITS_FOR_VARIOUS_THINGS_LIKE_COMMS_AND_DECODERS_ETC[] FD_DESC_PAGE = "Counter incremented status bits for various things like comms and decoders etc.";
const int8_t FD_PERCENT_IN_HUNDREDTHS[] FD_DESC_PAGE = "Percent in hundredth's.";
const int8_t FD_ENGINE_ANGLE_OFFSET_IN_HUNDREDTHS[] FD_DESC_PAGE = "Engine angle offset in hundredth's.";
const int8_t FD_INTERNAL_CLOCK_IN_MILLISECONDS[] FD_DESC_PAGE = "Internal Clock in milliseconds";
const int8_t FD_ANALOG_VOLTAGE_0_5V[] FD_DESC_PAGE = "Analog Voltage 0-5v";
const int8_t FD_BIT_FIELD_OF_REASONS_WHY_IGNITION_WAS_CUT[] FD_DESC_PAGE = "Bit-field of reasons why ignition was cut";
const int8_t FD_BIT_FIELD_OF_REASONS_WHY_INJECTION_WAS_CUT[] FD_DESC_PAGE = "Bit-field of reasons why injection was cut";
const int8_t FD_VARIANCE_IN_TEETH_IN_SCALED_PERCENT[] FD_DESC_PAGE = "Variance in teeth, in scaled percent";
const int8_t FD_FLAGS_REPRESENTING_VARIOUS_DECODER_STATES[] FD_DESC_PAGE = "Flags representing various decoder states";


#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */

