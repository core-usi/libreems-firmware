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
 * @ingroup communicationsFiles
 *
 * @brief Memory block details lookup
 *
 * This file holds the single function lookupBlockDetails() which
 * functions as a sort of address book for logical blocks of memory.
 */


#define BLOCK_DETAILS_LOOKUP_C
#include "inc/freeEMS.h"
#include "inc/interrupts_depricated.h"
#include "inc/locationIDs.h"
#include "inc/blockDetailsLookup.h"
#include "inc/shared/libreExternalTypes.h"

/* Global Variables */
/*&&&&&&&&&&&&&&&&&&&&& Large 1k or 2k blocks here only &&&&&&&&&&&&&&&&&&&&&*/

/* Fueling blocks */
void* VETableMainFlashLocation;
void* VETableMainFlash2Location;
void* VETableSecondaryFlashLocation;
void* VETableSecondaryFlash2Location;
void* AirflowTableFlashLocation;
void* AirflowTableFlash2Location;
void* LambdaTableFlashLocation;
void* LambdaTableFlash2Location;

/* Timing blocks */
void* IgnitionAdvanceTableMainFlashLocation;
void* IgnitionAdvanceTableMainFlash2Location;
void* IgnitionAdvanceTableSecondaryFlashLocation;
void* IgnitionAdvanceTableSecondaryFlash2Location;
void* InjectionAdvanceTableMainFlashLocation;
void* InjectionAdvanceTableMainFlash2Location;
void* InjectionAdvanceTableSecondaryFlashLocation;
void* InjectionAdvanceTableSecondaryFlash2Location;

/* Tunable blocks */
void* SmallTablesAFlashLocation;
void* SmallTablesAFlash2Location;
void* SmallTablesBFlashLocation;
void* SmallTablesBFlash2Location;
void* SmallTablesCFlashLocation;
void* SmallTablesCFlash2Location;
void* SmallTablesDFlashLocation;
void* SmallTablesDFlash2Location;

/* Flash ONLY blocks */
void* IATTransferTableLocation;
void* CHTTransferTableLocation;
void* MATTransferTableLocation;
void* TestTransferTableLocation;


/*&&&&&&&&&&&&&&& Small chunks of the above blocks here only! &&&&&&&&&&&&&&&*/

/* Small chunks of TablesA here */
void* voltageVersusDwellDesiredTableLocation;
void* voltageVersusDwellDesiredTable2Location;
void* injectorDeadTimeTableLocation;
void* injectorDeadTimeTable2Location;
void* postStartEnrichmentTableLocation;
void* postStartEnrichmentTable2Location;
void* primingVolumeTableLocation;
void* primingVolumeTable2Location;
void* engineTempEnrichmentTableLocation;
void* engineTempEnrichmentTable2Location;
void* RPMVersusDwellTableLocation;
void* RPMVersusDwellTable2Location;
void* RPMVersusBlendTableLocation;
void* RPMVersusBlendTable2Location;
void* IGNvsCLTtableLocation;
void* IGNvsIATtableLocation;

/* Small chunks of TablesB here */
void* loggingSettingsLocation;
void* loggingSettings2Location;
void* perCylinderFuelTrimsLocation;
void* perCylinderFuelTrims2Location;

/* Small chunks of TablesC here */
void* MAFvsVoltageTableLocation;
void* IATvsIgnitionTableLocation;
void* CLTvsIgnitionTableLocation;
void* ETHvsIgnitionTableLocation;
void* AAPlutTableLocation;
void* MAPlutTableLocation;
void* EGOlutTableLocation;
void* EGTlutTableLocation;
void* OILPlutTableLocation;
void* rpmVersusEngineTempTableLocation;
void* rpmVersusIACStepsTableLocation;
void* fuelDeltaVersusPercentAdderTableLocation;
void* fuelPressurelutTableLocation;
void* oilPressurelutTableLocation;


/* Small chunks of TablesD here */

/* Fillers here */
void* fillerALocation;
void* fillerA2Location;
void* fillerBLocation;
void* fillerB2Location;
void* fillerCLocation;
void* fillerC2Location;
void* fillerDLocation;
void* fillerD2Location;


/** @brief Lookup memory block details.
 *
 * Flash only blocks leave the RAM address and page values
 * set to zero. ID's that don't exist return an error code.
 *
 * @note This function is an exception to the style rule switch statement
 * blocks of using a {} pair for each case statement. Readability is better
 * without them in this case.
 *
 * @param locationID is the ID of the memory location for which details are required.
 * @param details is a pointer to the blockDetails struct to populate with the details.
 *
 * @return An error code. Zero means success, anything else is a failure.
 */
uint16_t lookupBlockDetails(uint16_t locationID, blockDetails* details){
  extern Clock Clocks;
  extern Counter Counters;
  extern KeyUserDebug KeyUserDebugs;
  extern Flaggable Flaggables; 
  extern Flaggable2 Flaggables2;
  extern const volatile uint16_t IATTransferTable[1024]; /* 2k */                                                                            
  extern const volatile uint16_t CHTTransferTable[1024];
  extern const volatile uint16_t MATTransferTable[1024];


  /* Initialise the four values needed for operations on memory at 0 for error checking */
  details->RAMPage      = 0;
  details->FlashPage    = 0;
  details->RAMAddress   = 0;
  details->FlashAddress = 0;
  details->descriptorID = UNDEF_TABLE_FORMAT;

  /* Initialise the block size to 1024 to save code space and increase readability */
  details->size = sizeof(mainTable);

  // No need to set parent value to zero as ignored unless flag set, done for clarity in hex stream.
  details->parent = 0;

  /* Look up the locations and set non default sizes */
  switch (locationID) {
  case CONFIG_LOCATION_ID:
    details->FlashPage = PPAGE;
    details->FlashAddress = (void*)&Config;
    break;
  /* lookup tables */
  case IAT_TRANSFER_TABLE_LOCATION_ID:
    details->size = sizeof(IATTransferTable);
    details->FlashPage = LOOKUP_PPAGE;
    details->FlashAddress = IATTransferTableLocation;
    details->descriptorID = IAT_TRANSFER_TID;
    break;
  case CHT_TRANSFER_TABLE_LOCATION_ID:
    details->size = sizeof(CHTTransferTable);
    details->FlashPage = LOOKUP_PPAGE;
    details->FlashAddress = CHTTransferTableLocation;
    details->descriptorID = CHT_TRANSFER_TID;
    break;
  case MAT_TRANSFER_TABLE_LOCATION_ID:
    details->size = sizeof(MATTransferTable);
    details->FlashPage = LOOKUP_PPAGE;
    details->FlashAddress = MATTransferTableLocation;
    details->descriptorID = MAT_TRANSFER_TID;
    break;
#ifdef ALL_CONFIG
  case TEST_TRANSFER_TABLE_LOCATION_ID:
    details->size = sizeof(TestTransferTable);
    details->FlashPage = LOOKUP_PPAGE;
    details->FlashAddress = TestTransferTableLocation;
    break;
#endif
  /* fuel tables */
  case VE_TABLE_MAIN_LOCATION_ID:
    details->RAMPage = RPAGE_FUEL_ONE;
    details->FlashPage = FUELTABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA;
    details->FlashAddress = VETableMainFlashLocation;
    details->descriptorID = VE_TID;
    break;
#ifdef ALL_CONFIG
  case VETABLE_SECONDARY_LOCATION_ID:
    details->RAMPage = RPAGE_FUEL_ONE;
    details->FlashPage = FUELTABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB;
    details->FlashAddress = VETableSecondaryFlashLocation;
    break;
#endif
  case AIRFLOW_TABLE_LOCATION_ID:
    details->RAMPage = RPAGE_FUEL_ONE;
    details->FlashPage = FUELTABLES_PPAGE;
    details->RAMAddress = (void*)&TablesC;
    details->FlashAddress = AirflowTableFlashLocation;
    details->descriptorID = AIRFLOW_VS_TPS_TID;
    break;
  case LAMBDA_TABLE_LOCATION_ID:
    details->RAMPage = RPAGE_FUEL_ONE;
    details->FlashPage = FUELTABLES_PPAGE;
    details->RAMAddress = (void*)&TablesD;
    details->FlashAddress = LambdaTableFlashLocation;
    details->descriptorID = LAMBDA_VS_LOAD_TID;
    break;
#ifdef ALL_CONFIG
  case VE_TABLE_MAIN2_LOCATION_ID:
    details->RAMPage = RPAGE_FUEL_TWO;
    details->FlashPage = FUELTABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA;
    details->FlashAddress = VETableMainFlash2Location;
    break;
  case VE_TABLE_SECONDARY2_LOCATION_ID:
    details->RAMPage = RPAGE_FUEL_TWO;
    details->FlashPage = FUELTABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB;
    details->FlashAddress = VETableSecondaryFlash2Location;
    break;
  case AIRFLOW_TABLE2_LOCATION_ID:
    details->RAMPage = RPAGE_FUEL_TWO;
    details->FlashPage = FUELTABLES_PPAGE;
    details->RAMAddress = (void*)&TablesC;
    details->FlashAddress = AirflowTableFlash2Location;
    break;
  case LAMBDA_TABLE2_LOCATION_ID:
    details->RAMPage = RPAGE_FUEL_TWO;
    details->FlashPage = FUELTABLES_PPAGE;
    details->RAMAddress = (void*)&TablesD;
    details->FlashAddress = LambdaTableFlash2Location;
    break;
#endif

  /* timing tables */
  case IGNITION_ADVANCE_TABLE_MAIN_LOCATION_ID:
    details->RAMPage = RPAGE_TIME_ONE;
    details->FlashPage = TIMETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA;
    details->FlashAddress = IgnitionAdvanceTableMainFlashLocation;
    details->descriptorID = IGNITION_ADVANCE_TID;
    break;
#ifdef ALL_CONFIG
  case IGNITION_ADVANCE_TABLE_SECONDARY_LOCATION_ID:
    details->RAMPage = RPAGE_TIME_ONE;
    details->FlashPage = TIMETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB;
    details->FlashAddress = IgnitionAdvanceTableSecondaryFlashLocation;
    break;
  case INJECTION_ADVANCE_TABLE_MAIN_LOCATION_ID:
    details->RAMPage = RPAGE_TIME_ONE;
    details->FlashPage = TIMETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesC;
    details->FlashAddress = InjectionAdvanceTableMainFlashLocation;
    break;
  case INJECTION_ADVANCE_TABLE_SECONDARY_LOCATION_ID:
    details->RAMPage = RPAGE_TIME_ONE;
    details->FlashPage = TIMETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesD;
    details->FlashAddress = InjectionAdvanceTableSecondaryFlashLocation;
    break;
  case IGNITION_ADVANCE_TABLE_MAIN2_LOCATION_ID:
    details->RAMPage = RPAGE_TIME_TWO;
    details->FlashPage = TIMETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA;
    details->FlashAddress = IgnitionAdvanceTableMainFlash2Location;
    break;
  case IGNITION_ADVANCE_TABLE_SECONDARY2_LOCATION_ID:
    details->RAMPage = RPAGE_TIME_TWO;
    details->FlashPage = TIMETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB;
    details->FlashAddress = IgnitionAdvanceTableSecondaryFlash2Location;
    break;
  case INJECTION_ADVANCE_TABLE_MAIN2_LOCATION_ID:
    details->RAMPage = RPAGE_TIME_TWO;
    details->FlashPage = TIMETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesC;
    details->FlashAddress = InjectionAdvanceTableMainFlash2Location;
    break;
  case INJECTION_ADVANCE_TABLE_SECONDARY2_LOCATION_ID:
    details->RAMPage = RPAGE_TIME_TWO;
    details->FlashPage = TIMETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesD;
    details->FlashAddress = InjectionAdvanceTableSecondaryFlash2Location;
    break;
#endif

  /* small table full blocks */
  case SMALL_TABLES_A_LOCATION_ID:
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA;
    details->FlashAddress = SmallTablesAFlashLocation;
    break;
  case SMALL_TABLES_B_LOCATION_ID:
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB;
    details->FlashAddress = SmallTablesBFlashLocation;
    break;
  case SMALL_TABLES_C_LOCATION_ID:
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesC;
    details->FlashAddress = SmallTablesCFlashLocation;
    break;
#ifdef ALL_CONFIG
  case SMALL_TABLES_D_LOCATION_ID:
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesD;
    details->FlashAddress = SmallTablesDFlashLocation;
    break;
  case SMALL_TABLES_A2_LOCATION_ID:
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA;
    details->FlashAddress = SmallTablesAFlash2Location;
    break;
  case SMALL_TABLES_B2_LOCATION_ID:
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB;
    details->FlashAddress = SmallTablesBFlash2Location;
    break;
  case SMALL_TABLES_C2_LOCATION_ID:
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesC;
    details->FlashAddress = SmallTablesCFlash2Location;
    break;
  case SMALL_TABLES_D2_LOCATION_ID:
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesD;
    details->FlashAddress = SmallTablesDFlash2Location;
    break;
#endif

  /* TablesA small tables */
  case VOLTAGE_VS_DWELL_DESIRED_TABLE_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.voltageVSDwellTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.voltageVSDwellTable;
    details->FlashAddress = voltageVersusDwellDesiredTableLocation;
    details->parent = SMALL_TABLES_A_LOCATION_ID;
    details->descriptorID = VOLTAGE_VS_DWELL_TID;
    break;
  case INJECTOR_DEAD_TIME_TABLE_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.injectorDeadTimeTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.injectorDeadTimeTable;
    details->FlashAddress = injectorDeadTimeTableLocation;
    details->parent = SMALL_TABLES_A_LOCATION_ID;
    details->descriptorID = INJECTOR_DEAD_TIME_VS_VOLTAGE_TID;
    break;
  case POST_START_ENRICHMENT_TABLE_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.postStartEnrichmentTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.postStartEnrichmentTable;
    details->FlashAddress = postStartEnrichmentTableLocation;
    details->parent = SMALL_TABLES_A_LOCATION_ID;
    details->descriptorID = TEMP_VS_ASE_PERCENT_TID;
    break;
  case PRIMING_VOLUME_TABLE_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.primingVolumeTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.primingVolumeTable;
    details->FlashAddress = primingVolumeTableLocation;
    details->parent = SMALL_TABLES_A_LOCATION_ID;
    details->descriptorID = TEMP_VS_INJECTOR_PRIMING_TID;
    break;
  case ENGINE_TEMP_ENRICHMENT_TABLE_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.engineTempEnrichmentTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.engineTempEnrichmentTable;
    details->FlashAddress = engineTempEnrichmentTableLocation;
    details->parent = SMALL_TABLES_A_LOCATION_ID;
        details->descriptorID = ENGINE_TEMP_ENRICHMENT_TID;
    break;
  case RPM_VS_DWELL_TABLE_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.RPMVersusDwellTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.RPMVersusDwellTable;
    details->FlashAddress = RPMVersusDwellTableLocation;
    details->parent = SMALL_TABLES_A_LOCATION_ID;
        details->descriptorID = RPM_VS_DWELL_TID;
    break;
  case RPM_VS_BLEND_TABLE_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.RPMVersusBlendTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.RPMVersusBlendTable;
    details->FlashAddress = RPMVersusBlendTableLocation;
    details->parent = SMALL_TABLES_A_LOCATION_ID;
        details->descriptorID = RPM_VS_BLEND_TID;
    break;
#ifdef ALL_CONFIG
  case VOLTAGE_VERSUS_DWELL_DESIRED_TABLE2_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.voltageVersusDwellDesiredTable);
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.voltageVersusDwellDesiredTable;
    details->FlashAddress = voltageVersusDwellDesiredTable2Location;
    details->parent = SMALL_TABLES_A2_LOCATION_ID;
    break;
  case INJECTOR_DEAD_TIME_TABLE2_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.injectorDeadTimeTable);
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.injectorDeadTimeTable;
    details->FlashAddress = injectorDeadTimeTable2Location;
    details->parent = SMALL_TABLES_A2_LOCATION_ID;
    break;
  case POST_START_ENRICHMENT_TABLE2_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.postStartEnrichmentTable);
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.postStartEnrichmentTable;
    details->FlashAddress = postStartEnrichmentTable2Location;
    details->parent = SMALL_TABLES_A2_LOCATION_ID;
    break;
  case PRIMING_VOLUME_TABLE2_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.primingVolumeTable);
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.primingVolumeTable;
    details->FlashAddress = primingVolumeTable2Location;
    details->parent = SmallTablesA2LocationID;
    break;
  case ENGINE_TEMP_ENRICHMENT_TABLE2_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.engineTempEnrichmentTable);
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.engineTempEnrichmentTable;
    details->FlashAddress = engineTempEnrichmentTable2Location;
    details->parent = SmallTablesA2LocationID;
    break;
  case DWELL_VS_RPM_TABLE2_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.dwellVersusRPMTable);
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.dwellVersusRPMTable;
    details->FlashAddress = dwellVersusRPMTable2Location;
    details->parent = SmallTablesA2LocationID;
    break;
  case RPM_VS_BLEND_TABLE2_LOCATION_ID:
    details->size = sizeof(TablesA.SmallTablesA.RPMVersusBlendTable);
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.RPMVersusBlendTable;
    details->FlashAddress = RPMVersusBlendTable2Location;
    details->parent = SmallTablesA2LocationID;
    break;
#endif
  /* TablesB small tables */
  case LOGGING_SETTINGS_LOCATION_ID:
    details->size = sizeof(TablesB.SmallTablesB.loggingSettings);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB.SmallTablesB.loggingSettings;
    details->FlashAddress = loggingSettingsLocation;
    details->parent = SMALL_TABLES_B_LOCATION_ID;
    break;
#ifdef ALL_CONFIG
  case LOGGING_SETTINGS2_LOCATION_ID:
    details->size = sizeof(TablesB.SmallTablesB.loggingSettings);
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB.SmallTablesB.loggingSettings;
    details->FlashAddress = loggingSettings2Location;
    details->parent = SMALL_TABLES_B2_LOCATION_ID;
    break;
#endif

  /* TablesC small tables */
  case MAF_VS_VOLTAGE_TABLE_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.MAFvsVoltageTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.MAFvsVoltageTable;
    details->FlashAddress = MAFvsVoltageTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = MAF_VS_VOLTAGE_TID;
    break;
  case IAT_VS_IGN_TABLE_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.IATvsIgnitionTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.IATvsIgnitionTable;
    details->FlashAddress = IATvsIgnitionTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = IAT_VS_IGN_TID;
    break;
  case CLT_VS_IGN_TABLE_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.CLTvsIgnitionTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.CLTvsIgnitionTable;
    details->FlashAddress = CLTvsIgnitionTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = CHT_VS_IGN_TID;
    break;
  case ETHANOL_PERCENT_VS_IGN_TABLE_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.ETHvsIgnitionTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.ETHvsIgnitionTable;
    details->FlashAddress = ETHvsIgnitionTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = ETHANOL_PERCENT_VS_IGN_TID;
    break;
  case EGO_LUT_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.EGOlut);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.EGOlut;
    details->FlashAddress = EGOlutTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = EGO_VS_LAMBDA_TID;
    break;
  case EGT_LUT_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.EGTlut);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.EGTlut;
    details->FlashAddress = EGTlutTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = EGT_VS_VOLTAGE_TID;
    break;
  case AAP_LUT_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.AAPlut);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.AAPlut;
    details->FlashAddress = AAPlutTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = AAP_VS_VOLTAGE_TID;
    break;
  case FUEL_PRESSURE_LUT_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.fuelPressureLUT);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.fuelPressureLUT;
    details->FlashAddress = fuelPressurelutTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = AAP_VS_VOLTAGE_TID;
    break;
  case OIL_PRESSURE_LUT_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.oilPressureLUT);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.oilPressureLUT;
    details->FlashAddress = oilPressurelutTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = OILP_VS_VOLTAGE_TID;
    break;
  case MAP_LUT_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.MAPlut);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.MAPlut;
    details->FlashAddress = MAPlutTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = MAP_VS_VOLTAGE_TID;
    break;
  case RPM_LIMIT_VS_ENGINE_TEMP_TABLE_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.rpmVersusEngineTempTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.rpmVersusEngineTempTable;
    details->FlashAddress = rpmVersusEngineTempTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = RPM_LIMIT_VS_TEMPERATURE_TID;
    break;
  case RPM_VS_IAC_STEPS_TABLE_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.rpmVersusIACStepsTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.rpmVersusIACStepsTable;
    details->FlashAddress = rpmVersusIACStepsTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = RPM_VS_IAC_STEPS_TID;
    break;
  case FUEL_DELTA_VS_PERCENT_ADDER_TABLE_LOCATION_ID:
    details->size = sizeof(TablesC.SmallTablesC.fuelDeltaVersusPercentAdderTable);
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*) &TablesC.SmallTablesC.fuelDeltaVersusPercentAdderTable;
    details->FlashAddress = fuelDeltaVersusPercentAdderTableLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    details->descriptorID = FUEL_DELTA_VS_PERCENT_ADDER_TID;
    break;

  /* TablesD small tables */
    // TODO add data chunks from TablesD when some are put in

#ifdef ALL_CONFIG
  /* filler block entries */
  case FILLER_A_LOCATION_ID:
    details->size = SMALL_TABLES_1_FILLER_SIZE;
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.filler;
    details->FlashAddress = fillerALocation;
    details->parent = SMALL_TABLES_A_LOCATION_ID;
    break;
  case FILLER_A2_LOCATION_ID:
    details->size = SMALL_TABLES_1_FILLER_SIZE;
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesA.SmallTablesA.filler;
    details->FlashAddress = fillerA2Location;
    details->parent = SmallTablesA2LocationID;
    break;
  case FILLER_B_LOCATION_ID:
    details->size = SMALL_TABLES_2_FILLER_SIZE;
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB.SmallTablesB.filler;
    details->FlashAddress = fillerBLocation;
    details->parent = SMALL_TABLES_B_LOCATION_ID;
    break;
  case FILLER_B2_LOCATION_ID:
    details->size = SMALL_TABLES_2_FILLER_SIZE;
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesB.SmallTablesB.filler;
    details->FlashAddress = fillerB2Location;
    details->parent = SMALL_TABLES_B2_LOCATION_ID;
    break;
  case FILLER_C_LOCATION_ID:
    details->size = SMALL_TABLES_3_FILLER_SIZE;
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesC.SmallTablesC.filler;
    details->FlashAddress = fillerCLocation;
    details->parent = SMALL_TABLES_C_LOCATION_ID;
    break;
  case FILLER_C2_LOCATION_ID:
    details->size = SMALL_TABLES_3_FILLER_SIZE;
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesC.SmallTablesC.filler;
    details->FlashAddress = fillerC2Location;
    details->parent = SMALL_TABLES_C2_LOCATION_ID;
    break;
  case FILLER_D_LOCATION_ID:
    details->size = SMALL_TABLES_4_FILLER_SIZE;
    details->RAMPage = RPAGE_TUNE_ONE;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesD.SmallTablesD.filler;
    details->FlashAddress = fillerDLocation;
    details->parent = SmallTablesDLocationID;
    break;
  case FILLER_D2_LOCATION_ID:
    details->size = SMALL_TABLES_4_FILLER_SIZE;
    details->RAMPage = RPAGE_TUNE_TWO;
    details->FlashPage = TUNETABLES_PPAGE;
    details->RAMAddress = (void*)&TablesD.SmallTablesD.filler;
    details->FlashAddress = fillerD2Location;
    details->parent = SmallTablesD2LocationID;
    break;
#endif

// Internal blocks of variables that are sometimes useful to read out
  case ADC_REGISTERS_LOCATION_ID:
    details->size = sizeof(ADCBuffer);
    details->RAMPage = RPAGE_LINEAR;
    details->RAMAddress = (void*)&ADCBuffers0;
    break;
  case CORE_VARS_LOCATION_ID:
    details->size = sizeof(CoreVar);
    details->RAMPage = RPAGE_LINEAR;
    details->RAMAddress = (void*)CoreVars;
    break;
  case DERIVED_VARS_LOCATION_ID:
    details->size = sizeof(DerivedVar);
    details->RAMPage = RPAGE_LINEAR;
    details->RAMAddress = (void*)DerivedVars;
    break;
  case KEY_USER_DEBUG_LOCATION_ID:
    details->size = sizeof(KeyUserDebug);
    details->RAMPage = RPAGE_LINEAR;
    details->RAMAddress = &KeyUserDebugs;
    break;
  case COUNTERS_LOCATION_ID:
    details->size = sizeof(Counter);
    details->RAMPage = RPAGE_LINEAR;
    details->RAMAddress = &Counters;
    break;
  case CLOCKS_LOCATION_ID:
    details->size = sizeof(Clock);
    details->RAMPage = RPAGE_LINEAR;
    details->RAMAddress = &Clocks;
    break;
  case FLAGGABLES_LOCATION_ID:
    details->size = sizeof(Flaggable);
    details->RAMPage = RPAGE_LINEAR;
    details->RAMAddress = &Flaggables;
    break;
  case FLAGGABLES2_LOCATION_ID:
    details->size = sizeof(Flaggable2);
    details->RAMPage = RPAGE_LINEAR;
    details->RAMAddress = &Flaggables2;
    break;

  default:
    /* Return early if locationID is not valid. */
    return LOCATION_ID_NOT_FOUND;
  }


  // Setup all of the flags for various groups here
  // Setting flags above is wrong, keep it all in one place, here!

  // Initialise the flags to having flash, everything does at the moment, and indexable, most is, negate at end for those that don't.
  details->flags = BLOCK_IS_IN_FLASH | BLOCK_IS_INDEXABLE;

  if (locationID == MAF_VS_VOLTAGE_TABLE_LOCATION_ID) {
    details->flags |= BLOCK_IS_2DUL_TABLE;
  }

  if(locationID < MAIN_TABLE_TWO_D_TABLE_US_BORDER){
    details->flags |= BLOCK_IS_MAIN_TABLE | BLOCK_IS_IN_RAM | BLOCK_GETS_VERIFIED | BLOCK_FOR_BACKUP_RESTORE;
  }else if(locationID < TWO_D_TABLE_US_SMALL_TABLE_FULL_BLOCKS_BORDER){
    details->flags |= BLOCK_IS_2DUS_TABLE | BLOCK_IS_IN_RAM | BLOCK_HAS_PARENT | BLOCK_GETS_VERIFIED;
  }else if(locationID < SMALL_TABLE_FULL_BLOCKS_SMALL_TABLE_FILLERS_BORDER){
    details->flags |= BLOCK_IS_IN_RAM | BLOCK_FOR_BACKUP_RESTORE;
    details->flags &= ~BLOCK_IS_INDEXABLE;
  }else if(locationID < SMALL_TABLE_FILLERS_FLASH_LOOKUP_TABLES_BORDER){
    details->flags |= BLOCK_HAS_PARENT | BLOCK_IS_IN_RAM;
    details->flags &= ~BLOCK_IS_INDEXABLE;
  }else if(locationID < FLASH_LOOKUP_TABLES_SMALL_TABLE_CONFIGS_BORDER){
    details->flags |= BLOCK_IS_LOOKUP_DATA | BLOCK_FOR_BACKUP_RESTORE;
    details->flags &= ~BLOCK_IS_INDEXABLE;
  }else if(locationID < SMALL_TABLE_CONFIGS_FIXED_CONFIG_BLOCKS_BORDER){
    details->flags |= BLOCK_HAS_PARENT | BLOCK_IS_IN_RAM | BLOCK_IS_CONFIGURATION;
  }else if(locationID < FIXED_CONFIG_BLOCKS_FIXED_CONFIG_SUB_BLOCKS_BORDER){
    details->flags |= BLOCK_FOR_BACKUP_RESTORE;
  }else if(locationID < FIXED_CONFIG_SUB_BLOCKS_BORDER_READ_ONLY_VAR_BLOCKS){
    details->flags |= BLOCK_HAS_PARENT | BLOCK_IS_CONFIGURATION;
  }else{ // RO variable blocks exposed polling and streaming
    details->flags |= BLOCK_IS_READ_ONLY | BLOCK_IS_IN_RAM;
    details->flags &= ~BLOCK_IS_IN_FLASH;
  }

/* Fall through to not return error */
  return 0;
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
