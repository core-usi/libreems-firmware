/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014-2016 Sean Keys, David Andruczyk
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
 * @brief Struct typedefs for tunable configuration
 *
 * This file contains both the struct data type definitions and the arrays of
 * default values for small tables. Place reusable definitions of default table
 * values in here such that they can be used in multiple tunable table definitions.
 *
 * You should add your configuration item here if it is best that it is adjusted with
 * instant results on a running engine. For everything else, please consider placing
 * it in one of the fixed configuration structs.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_TUNABLE_CONFIGS_H_SEEN
#define FILE_TUNABLE_CONFIGS_H_SEEN

#include "dataLogDefinitions.h"
#include "Configuration.h"

/** Information about what page holds the static strings pertaining to
 * the dataBlockDescriptor
 */
typedef struct {
  uint8_t base_struct_page; /** Page where the base structure lives (for the integer values) */
  uint8_t base_name_page;   /** Page where the "name" strings live (not necessarily in base struct) */
  uint8_t base_desc_page;   /** Page where the "description" strings live (not necessarily in base struct) */
  uint8_t base_misc_page;   /** Page where the misc strings live (not necessarily in base struct) */
}descriptorPages;

/** Holds a datalog chunk configuration pair.
 *
 * A datalog configuration pair consists of an address and a size.
 */
typedef struct {
  void* address;
  uint16_t size;
  const dataBlockDescriptor* descriptor;
  const uint8_t *numDescriptions;
  const descriptorPages pages;
} logChunk;


#define MAX_LOG_CHUNKS 16
/** Holds all configuration for logging.
 *
 * These are in tunable config such that the system can pick up where it left
 * off if reset with settings burned to flash, or simply switch back to default
 * if changed in ram and not burned and then reset.
 */
typedef struct {
  uint8_t datalogStreamType;            ///< Which type of datalog to pump out as fast as we can. @see commsCore.h
  uint8_t datalogPollingType;           ///< Which type of datalog to pump out as fast as we can. @see commsCore.h
  uint8_t firstChunk;                   ///< The index of the first chunk to send.
  uint8_t numberOfChunks;               ///< How many chunks to send.
  logChunk logChunks[MAX_LOG_CHUNKS];         ///< Array of chunk sets so as to have on-board presets available to quickly swap to.
  void* datalogByteStreamSourceAddress;       ///< Where to grab our data from.
  void* datalogWordStreamSourceAddress;       ///< Where to grab our data from.
  void* datalogLongStreamSourceAddressFirst;  ///< Where to grab our data from. If the second address is set to zero, get 4 bytes from this address.
  void* datalogLongStreamSourceAddressSecond; ///< Where to grab our data from. If this is non-zero, get 2 bytes from the first address and 2 from this address.
  // TODO scratch pad configs
} loggingSetting;


/* Correct way to calculate the filler, ALWAYS update this when changing the structure below... */
#define SMALL_TABLES_1_FILLER_SIZE (FLASHSECTORSIZE - ( \
    (sizeof(TableEntryUINT16) * BRV_VS_DWELL_TABLE_LENGTH) + \
    (sizeof(TableEntryUINT16) * IDT_LOOKUP_TABLE_LENGTH) + \
    (sizeof(TableEntryINT16)  * TEMP_VS_ASE_PERCENT_TABLE_LENGTH) + \
    (sizeof(TableEntryINT16)  * TEMP_VS_PRIMING_VOLUME_TABLE_LENGTH) + \
    (sizeof(TableEntryUINT16) * RPM_VS_BLEND_TABLE_LENGTH) + \
    (sizeof(TableEntryINT16)  * ENGINE_TEMP_ENRICHMENT_TABLE_LENGTH) + \
    (sizeof(TableEntryUINT16) * RPM_VS_DWELL_TABLE_LENGTH) \
    )) // Update this if adding another table!
/**
 * One of four structs of live tunable data such as small tables and fuel trims
 * etc. If you add something here, please ensure you update all of the following :
 * - Default values in the initial definitions in TunableConfig.c and TunableConfig2.c
 * - The address values within the initPagedRAMTune() function in init.c
 * - The lookupBlockDetails() function in blockDetailsLookup.c
 * - The JSON data map and other related firmware interface definition files
 *
 */
typedef struct {
  TableEntryUINT16 voltageVSDwellTable[BRV_VS_DWELL_TABLE_LENGTH];///< Dwell curve dependent on voltage.
  TableEntryUINT16 injectorDeadTimeTable[IDT_LOOKUP_TABLE_LENGTH];///< Injector dead time curve dependent on voltage.
  TableEntryINT16  postStartEnrichmentTable[TEMP_VS_ASE_PERCENT_TABLE_LENGTH];///< Unused at this time.
  TableEntryINT16  primingVolumeTable[TEMP_VS_PRIMING_VOLUME_TABLE_LENGTH];///< @todo TODO define units. perhaps micro litres (cubic milli meters) would be good, 5 - 100 seem to be the norm 327.68 = 65535/200
  TableEntryUINT16 RPMVersusBlendTable[RPM_VS_BLEND_TABLE_LENGTH];///< Used to combine Speed Density and Alpha-N algorithms based on RPM
  TableEntryINT16  engineTempEnrichmentTable[ENGINE_TEMP_ENRICHMENT_TABLE_LENGTH]; ///< Engine temperature enrichment by percent, AKA warmup curve.
  TableEntryUINT16 RPMVersusDwellTable[RPM_VS_DWELL_TABLE_LENGTH];///< Useful for certain setups, will generalise later.
  uint8_t filler[SMALL_TABLES_1_FILLER_SIZE];
} SmallTables1;


/* Correct way to calculate the filler, ALWAYS update this when changing the structure below... */
#define SMALL_TABLES_2_FILLER_SIZE (FLASHSECTORSIZE - ( \
      (sizeof(loggingSetting)) + \
      (sizeof(uint16_t)  * MAX_NUMBER_OF_CYLINDERS) \
      )) // Update this if adding another table/struct!
/** @copydoc SmallTables1 */
typedef struct {
  loggingSetting loggingSettings;                          ///< @copydoc loggingSetting
  uint16_t perCylinderFuelTrims[MAX_NUMBER_OF_CYLINDERS]; ///< Trims for injection, from 0% to 200% of base.
  uint8_t filler[SMALL_TABLES_2_FILLER_SIZE];        ///< Padding data.
} SmallTables2;


/* Correct way to calculate the filler, ALWAYS update this when changing the structure below... */
#define SMALL_TABLES_3_FILLER_SIZE (FLASHSECTORSIZE - ( \
      (sizeof(TableEntryU1632)  * MAF_VS_V_LUT_TABLE_SIZE) + \
      (sizeof(TableEntryINT16)  * IAT_VS_IGN_TABLE_LENGTH) + \
      (sizeof(TableEntryINT16)  * CLT_VS_IGN_TABLE_LENGTH) + \
      (sizeof(TableEntryINT16)  * IGN_VS_ETH_TABLE_LENGTH) + \
      (sizeof(TableEntryUINT16) * EGO_LOOKUP_TABLE_LENGTH) + \
      (sizeof(TableEntryUINT16) * MAP_LUT_TABLE_LENGTH) + \
      (sizeof(TableEntryUINT16) * AAP_LUT_TABLE_LENGTH) + \
      (sizeof(TableEntryINT16)  * RPM_VS_TEMP_TABLE_LENGTH) + \
      (sizeof(TableEntryUINT16) * RPM_VS_STEPS_TABLE_LENGTH) + \
      (sizeof(TableEntryUINT16) * FUEL_DELTA_VS_PERCENT_ADDER_TABLE_LENGTH) + \
      (sizeof(TableEntryUINT16) * FUEL_PRESSURE_TABLE_LENGTH) + \
      (sizeof(TableEntryUINT16) * OIL_PRESSURE_TABLE_LENGTH) + \
      (sizeof(TableEntryUINT16) * EGT_LOOKUP_TABLE_LENGTH) \
      )) // Update this if adding another table/struct!
/** @copydoc SmallTables1 */
typedef struct {
  TableEntryU1632 MAFvsVoltageTable[MAF_VS_V_LUT_TABLE_SIZE];       ///< MAF table location
  TableEntryINT16 IATvsIgnitionTable[IAT_VS_IGN_TABLE_LENGTH];
  TableEntryINT16 CLTvsIgnitionTable[CLT_VS_IGN_TABLE_LENGTH];
  TableEntryINT16 ETHvsIgnitionTable[IGN_VS_ETH_TABLE_LENGTH];        /* Timing offset for ethanol percentage */
  TableEntryUINT16 EGOlut[EGO_LOOKUP_TABLE_LENGTH];
  TableEntryUINT16 MAPlut[MAP_LUT_TABLE_LENGTH];
  TableEntryUINT16 AAPlut[AAP_LUT_TABLE_LENGTH];
  TableEntryINT16 rpmVersusEngineTempTable[RPM_VS_TEMP_TABLE_LENGTH];///< Used for Idle Air Control, RPM vs Engine Temperature.
  TableEntryUINT16 rpmVersusIACStepsTable[RPM_VS_STEPS_TABLE_LENGTH]; ///< Used for Idle Air Control, RPM vs IAC Steps.
  TableEntryUINT16 fuelDeltaVersusPercentAdderTable[FUEL_DELTA_VS_PERCENT_ADDER_TABLE_LENGTH];
  TableEntryUINT16 fuelPressureLUT[FUEL_PRESSURE_TABLE_LENGTH];
  TableEntryUINT16 oilPressureLUT[OIL_PRESSURE_TABLE_LENGTH];
  TableEntryUINT16 EGTlut[EGT_LOOKUP_TABLE_LENGTH];
  uint8_t filler[SMALL_TABLES_3_FILLER_SIZE]; ///< Padding data.
} SmallTables3;


#define SMALL_TABLES_4_FILLER_SIZE FLASHSECTORSIZE // Update this if adding a table!
/** @copydoc SmallTables1 */
typedef struct {
  uint8_t filler[SMALL_TABLES_4_FILLER_SIZE]; ///< Padding data.
} SmallTables4;


#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
