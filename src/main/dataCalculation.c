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
 * @ingroup data acquisition
 */

#include "inc/Configuration.h"
#include "inc/dataAcquisition.h"
#include "inc/dataCalculation.h"
#include "inc/outputPlotter.h"
#include "inc/tableLookup.h"
#include "inc/locationIDs.h"
#include "inc/utils.h"
#include "inc/libreMath.h"
#include "inc/freeEMS.h"
#include "inc/TunableConfigs.h"
#include "inc/dataLookup.h"
#include "inc/shared/libreExternalTypes.h"


extern KeyUserDebug KeyUserDebugs;
extern  const volatile fixedConfig2 fixedConfigs2;
extern uint32_t cmockaAirFlow;
extern const volatile uint16_t CHTTransferTable[1024];
extern const volatile uint16_t IATTransferTable[1024];

/* Return the amount of air in mass whether measured or calculated for a given cylinder
 * TODO revise ADCBuffer and other non-synced parameters
 * */
void calculateAirCharge(SyncedData *syncedLookups, uint16_t cylVolumeCC, uint32_t *airChargeMass) {

  /* Local Vars */
  uint32_t IGLUpper;
  uint32_t IGLLower;
  uint32_t pressureKPA;
  uint32_t temperature;

  uint32_t airFlow;

  /* FIXME actually we want to calc air flow for all enabled algorithm types then use the switch statement to apply the one
  * we currently want
  */

  switch (currentFuelingAlgorithm_g) {
  case ALGO_SD_AN_BLEND:

    break;
  case ALGO_MAF: //Since this is being measured all we need to do is look it up and apply RPM

#ifndef HOST_TESTS
     airFlow = TableLookupU16U32(syncedLookups->MAF, TablesC.SmallTablesC.MAFvsVoltageTable, MAF_VS_V_LUT_TABLE_SIZE);
#else
     airFlow = cmockaAirFlow;
#endif
    *airChargeMass = (airFlow / GET_RPM(syncedLookups->TPD)) / (Config.mechanicalProperties.cylinderCount / Config.mechanicalProperties.revoloutionsPerCycle);
    *airChargeMass *= 1000;

    // 0.0012041 * 250 * 4 * 6000  / 60 / 2 = 60.250  60.250 should be the GS at 6K RPM at 100%VE
    //1,509,000 scaled grams per charge at 6K rpm/ 50% VE  =  (1,509,000  * 6000)  /  60  * 2 = 301800000 *2 for 100% ve
    // 3,010,000 =
    break;
  case ALGO_ALPHA_N:
    break;
  case ALGO_SPEED_DENSITY:
#ifndef HOST_TESTS
    pressureKPA = TableLookupUINT16(syncedLookups->MAP, TablesC.SmallTablesC.MAPlut, MAP_LUT_TABLE_LENGTH);

    temperature = CoreVars->IAT;
    DerivedVars->VEMain = lookupMainTable(GET_RPM(syncedLookups->TPD), (uint16_t)pressureKPA, VE_TABLE_MAIN_LOCATION_ID);
    pressureKPA = (pressureKPA * DerivedVars->VEMain) / VE(100);
#else
    pressureKPA = syncedLookups->MAP;
    temperature = CEL_TO_KELVIN_S(20);
    pressureKPA = (pressureKPA * VE(50)) / VE(100);
#endif
    /* Calculate mass of air in the cylinder via Ideal Gas Law*/
    // http://www.chemguide.co.uk/physical/kt/idealgases.html   see number of moles section
    IGLUpper = (pressureKPA * cylVolumeCC);
    IGLLower = (temperature * IGL_R_S) / IGL_LOWER_SCALER;

    *airChargeMass =  (IGLUpper / IGLLower) * MOLAR_MASS_AIR_S;

    break;
  default: /* default to disabled */
    *airChargeMass = 1;
    break;
  }

  return;
}

//TODO combine fuelAttrs and DerivedVars once this has been tested and we have time to adjust downstream applications
void calculateRequiredFuel(fuelAttributes* fuelAttrs, DerivedVar* derivedVars, uint32_t airFlow, CylinderConfig *cylinder) {


  uint32_t AFR = derivedVars->StoichAFR;
  uint32_t fuelGramsSecond = fuelAttrs->primaryInjFlow;
  uint16_t pulseWidth;
  uint32_t secondaryPulseWidth; /* 32-bit for intermediate scaling only */

  /* Figure out AFR after factoring in desired Lambda */
  airFlow = (airFlow * TICKS_PER_TENTH_MILI) / ((AFR * derivedVars->Lambda) / LAMBDA(1.0)); //consider moving the TICKS_PER_TENTH_MILI into airflow
  airFlow *= 1000; //FIXME I feel like we should be able to tuck this into a scaling factor somewhere in the air calc.
                   // kind of like a required fuel base-number

  /* TODO apply individual cyl correction*/

  /* Apply Fuel Density Correction */
  fuelGramsSecond = ((fuelGramsSecond * derivedVars->FuelDensity)) / FUEL_DENSITY_F;

  pulseWidth = (airFlow / fuelGramsSecond);

  /* Apply temperature enrichment */
  pulseWidth = safeScale(pulseWidth, derivedVars->ETE, SHORT4TH); //TODO consider dropping effectivePW

    /* TODO apply AE enrichment */

  if (cylinder->syncedEngineData->previousFuelRequirement == 0) {
    KeyUserDebugs.fuelingDelta = FUELING_DELTA_FACTOR;
  } else {
      KeyUserDebugs.fuelingDelta = (uint32_t)(pulseWidth * FUELING_DELTA_FACTOR) / cylinder->syncedEngineData->previousFuelRequirement;
  }

  cylinder->syncedEngineData->previousFuelRequirement = pulseWidth;

  /* TODO we should change the way we are doing scaled percents */
  if (Config.fuelingProperties.fuelAlgoFlags.deltaScaling) {
    uint32_t AEscaler = TableLookupUINT16(KeyUserDebugs.fuelingDelta, TablesC.SmallTablesC.fuelDeltaVersusPercentAdderTable, FUEL_DELTA_VS_PERCENT_ADDER_TABLE_LENGTH);
    pulseWidth = (AEscaler * pulseWidth) / FA(100);
  }

  uint8_t semiSequential = FALSE;

  if ((getDecoderStats()->decoderFlags.bits.phaseLock == FALSE) &&
      Config.tachDecoderSettings.minimalSyncRequired == CRANK_ONLY) {
    semiSequential = TRUE;
  }

  if (semiSequential) {
    pulseWidth /= 2;
  }

  /* Apply Dead Time Last*/
  pulseWidth  = safeAdd(pulseWidth, derivedVars->IDT);

  uint32_t dutyCycle;
  uint32_t cyclePeriod;

  /* Make sure we don't div by zero */
  if (cylinder->syncedEngineData->TPD) {
    cyclePeriod = ((uint32_t)cylinder->syncedEngineData->TPD * DEGRESS_PER_ROTATION) * Config.mechanicalProperties.revoloutionsPerCycle;
    if (semiSequential) {
      cyclePeriod /= 2;
    }
    dutyCycle = (uint32_t)pulseWidth * DUTY_CYCLE_FACTOR;
    dutyCycle = dutyCycle / cyclePeriod;
  } else {
    dutyCycle = 0;
    cyclePeriod = 0;
  }

  uint16_t maxPrimaryDC = Config.fuelingProperties.maxPrimaryDC;

  switch (Config.fuelingProperties.injectionStrategy) {
  case STAGED_EXTENSION:
    if (dutyCycle > maxPrimaryDC) {
      /* Calc fuel for first injector */
      cylinder->primaryFuelEvent->runTime = (cyclePeriod * maxPrimaryDC) / DUTY_CYCLE_FACTOR;

      /* Calc fuel for second injector */
      secondaryPulseWidth =  pulseWidth - cylinder->primaryFuelEvent->runTime; /* subtract the amount we injected via the primary */
      secondaryPulseWidth += DerivedVars->IDT; /* Add lost fuel since above calc does not account for IDT */

      /* Correct against any flow difference between the primary and secondary set */
      secondaryPulseWidth = (uint16_t) ((secondaryPulseWidth * injectorFlowDifference_g) / FLOW_SCALE_FACTOR);
      secondaryPulseWidth += DerivedVars->IDT; //FIXME we need a second lookup, incase the characteristics are different from our first set of injectors
      cylinder->secondaryFuelEvent->runTime = secondaryPulseWidth;

      KeyUserDebugs.PrimaryInjDC = maxPrimaryDC; /* record primary DC */
      /* Check DC of secondary injector */
      uint32_t dutyCycle =  secondaryPulseWidth * DUTY_CYCLE_FACTOR;
      dutyCycle = dutyCycle / cyclePeriod;
      KeyUserDebugs.SecondaryInjDC = dutyCycle;
      if (dutyCycle > Config.fuelingProperties.maxSecondaryDC) {
        //TODO cut fuel on both primary and secondary
        cylinder->primaryFuelEvent->eventFlags |= EVENT_DUTY_CYCLE_EXCEEDDED;
        cylinder->secondaryFuelEvent->eventFlags |= EVENT_DUTY_CYCLE_EXCEEDDED;
      } else {
        cylinder->primaryFuelEvent->eventFlags &= ~(EVENT_DUTY_CYCLE_EXCEEDDED);
        cylinder->secondaryFuelEvent->eventFlags &= ~(EVENT_DUTY_CYCLE_EXCEEDDED);
      }
    } else {
      KeyUserDebugs.SecondaryInjDC = 0; //FIXME make zsp7 a secondary duty cycle log var
      KeyUserDebugs.PrimaryInjDC = dutyCycle; //TODO add this to the log stream, its been years and still no *official DC in the log, pathetic
      cylinder->primaryFuelEvent->runTime = pulseWidth;
            //TODO disable secondary fuel
      cylinder->primaryFuelEvent->eventFlags &= ~(EVENT_DUTY_CYCLE_EXCEEDDED);
      cylinder->secondaryFuelEvent->eventFlags |= EVENT_DUTY_CYCLE_EXCEEDDED;
      //TODO clear disable flags for DC above max
    }

    break;

  default:
    cylinder->primaryFuelEvent->runTime = pulseWidth;
    if (dutyCycle > maxPrimaryDC) {
      cylinder->primaryFuelEvent->eventFlags |= EVENT_DUTY_CYCLE_EXCEEDDED;
    } else {
      cylinder->primaryFuelEvent->eventFlags &= ~(EVENT_DUTY_CYCLE_EXCEEDDED);
    }
    break;
  }
}


void updateCylinderCalcs(uint8_t numCylinders) {
  uint32_t airCharge; /* mass of air in the hole */
  uint16_t dwellInDegrees;
  uint16_t startAngle;
  CylinderConfig *cylinder = &Config.CylinderSetup[0];

  DecoderStats *decoderStats = getDecoderStats();

  uint16_t dwellTime = TableLookupUINT16(CoreVars->BRV, TablesA.SmallTablesA.voltageVSDwellTable, BRV_VS_DWELL_TABLE_LENGTH);
  uint16_t dwellLimit = TableLookupUINT16(CoreVars->RPM, TablesA.SmallTablesA.RPMVersusDwellTable, RPM_VS_DWELL_TABLE_LENGTH);

  if (dwellTime > dwellLimit) {
    DerivedVars->Dwell = dwellLimit;
  } else {
    DerivedVars->Dwell = dwellTime;
  }
  /* Lookup Offsets */
  int16_t decoderOffset = Config.mechanicalProperties.decoderInputAngleOffset;
  int16_t IATOffset = TableLookupINT16(CoreVars->IAT, TablesC.SmallTablesC.IATvsIgnitionTable, IAT_VS_IGN_TABLE_LENGTH);
  int16_t CLTOffset = TableLookupINT16(CoreVars->CHT, TablesC.SmallTablesC.CLTvsIgnitionTable, CLT_VS_IGN_TABLE_LENGTH);

  /* Get Ethanol Fuel offset */
  int16_t ethanolOffset = 0;
  if (Config.fuelingProperties.fuelAlgoFlags.flexFuel) {
    ethanolOffset = TableLookupINT16(CoreVars->EthanolPercentage, TablesC.SmallTablesC.ETHvsIgnitionTable, IGN_VS_ETH_TABLE_LENGTH);
  }

  uint8_t i;
  for (i = 0; i < numCylinders; ++i, ++cylinder) {
    /* Update Fuel */
    calculateAirCharge(cylinder->syncedEngineData, DerivedVars->Displacement, &airCharge);
    calculateRequiredFuel(&FuelAttribs, DerivedVars, airCharge, cylinder);
    cylinder->primaryFuelEvent->countDown.countDown32 = 100u; /* For now this should be greater >= max ISR latency */

    cylinder->primaryFuelEvent->nextStartAngle = cylinder->InjectionAngle;
    if (decoderStats->decoderFlags.bits.minimalSync) {
      if (cylinder->primaryFuelEvent->eventFlags & EVENT_CALC_REQUIRED) {
        cylinder->primaryFuelEvent->startAngle = cylinder->InjectionAngle;
        cylinder->primaryFuelEvent->eventFlags &= ~(EVENT_CALC_REQUIRED);
      }
    }

    if (Config.fuelingProperties.injectionStrategy != PLAIN_INJECTION) {
      cylinder->secondaryFuelEvent->nextStartAngle = cylinder->InjectionAngle;
      cylinder->secondaryFuelEvent->countDown.countDown32 = 100u; /* For now this should be greater >= max ISR latency */

      if (decoderStats->decoderFlags.bits.minimalSync) {
        if (cylinder->secondaryFuelEvent->eventFlags & EVENT_CALC_REQUIRED) {
          cylinder->secondaryFuelEvent->startAngle = cylinder->InjectionAngle;
          cylinder->secondaryFuelEvent->eventFlags &= ~(EVENT_CALC_REQUIRED);
        }
      }

    }


    /* Use TDC angle and subtract advance to get abs angle */
    startAngle = offsetAngle(cylinder->TDCAngle, DerivedVars->Advance);
    /* Apply decoder offset */
    startAngle = offsetAngle(startAngle, decoderOffset);
    /* Apply IAT correction */
    startAngle = offsetAngle(startAngle, IATOffset);
    /* Apply CHT/CLT correction */
    startAngle = offsetAngle(startAngle, CLTOffset);
    /* Apply Ethanol correction */
    startAngle = offsetAngle(startAngle, ethanolOffset);
    //FIXME temp code to record desired timing for reference
//    if (i == 0) {
//      getDecoderStats()->capturedAngle = offsetAngle(startAngle, -(Config.mechanicalProperties.decoderInputAngleOffset));
//    }
    /* Apply dwell to spark angle */
    cylinder->igntionEvent->runTime = DerivedVars->Dwell;
startAngle = offsetAngle(cylinder->TDCAngle, DerivedVars->Advance);
startAngle = offsetAngle(startAngle, decoderOffset);

    dwellInDegrees = ((uint32_t)DerivedVars->Dwell
        * TICKS_PER_DEGREE_MULTIPLIER) / decoderStats->instantTicksPerDegree;
    startAngle = offsetAngle(startAngle, dwellInDegrees);

    cylinder->igntionEvent->nextStartAngle = startAngle;

    if (decoderStats->decoderFlags.bits.minimalSync) {
      if (cylinder->igntionEvent->eventFlags & EVENT_CALC_REQUIRED) {
        cylinder->igntionEvent->startAngle = startAngle;
        cylinder->igntionEvent->eventFlags &= ~(EVENT_CALC_REQUIRED);
      }
    }

    cylinder->igntionEvent->countDown.countDown32 = 0; /* Zero signifies to the scheduler that we want it to calculate the count down */
  }
  DerivedVars->AirChargeMass = airCharge / 1000;  //TODO this needs to be rotated on a per cyl basis for logging
}


uint16_t calculateAFR(uint8_t percentEth) {

  uint16_t AFR = ((uint32_t)GASOLINE_AFR_STOICH * ((PERCENT_100 * ETHANOL_COMPOSITION_FACTOR) - percentEth) + \
      ((uint32_t)ETHANOL_AFR_STOICH * percentEth)) / (PERCENT_100 * ETHANOL_COMPOSITION_FACTOR);

  return AFR;
}


uint16_t calculateFuelDensity(uint8_t percentEth) {

  uint16_t density = ((uint32_t)GASOLINE_DENSITY_STP * ((PERCENT_100 * ETHANOL_COMPOSITION_FACTOR) - percentEth) + \
      ((uint32_t)ETHANOL_DENSITY_STP * percentEth)) / (PERCENT_100 * ETHANOL_COMPOSITION_FACTOR);

  return density;
}


#ifndef HOST_TESTS
void updateCylinderCuts(uint8_t numCylinders, OperatingLimits *limits) {

  uint8_t i;
  CylinderConfig *cylinder = &Config.CylinderSetup[0];
// TODO remove need for i and optimize
  for (i = 0; i < numCylinders; ++i, ++cylinder) {

    /* Check for RPM Injection cut */
    if (CoreVars->RPM > limits->RPMfuelDisableLimit) {
      cylinder->primaryFuelEvent->eventFlags |= EVENT_RPM_EXCEEDED;
      if ((cylinder->secondaryFuelEvent) != (void*) 0) {
        cylinder->secondaryFuelEvent->eventFlags |= EVENT_RPM_EXCEEDED;
      }
    } else if (CoreVars->RPM < limits->RPMfuelEnableLimit) {
      cylinder->primaryFuelEvent->eventFlags &= ~(EVENT_RPM_EXCEEDED);
      if ((cylinder->secondaryFuelEvent) != (void*) 0) {
        cylinder->secondaryFuelEvent->eventFlags &= ~(EVENT_RPM_EXCEEDED);
      }
    }

    /* Check for RPM Ignition cut */
    if (CoreVars->RPM > limits->RPMignitionDisableLimit) {
      cylinder->igntionEvent->eventFlags |= EVENT_RPM_EXCEEDED;
    } else if (CoreVars->RPM < limits->RPMignitionEnableLimit) {
      cylinder->igntionEvent->eventFlags &= ~(EVENT_RPM_EXCEEDED);
    }

    /* Check over-boost inj and ign cut */
    if (CoreVars->MAP > limits->MAPfuelDisableLimit) {
      cylinder->igntionEvent->eventFlags |= EVENT_LOAD_EXCEEDED;
      cylinder->primaryFuelEvent->eventFlags |= EVENT_LOAD_EXCEEDED;
      if ((cylinder->secondaryFuelEvent) != (void*) 0) {
        cylinder->secondaryFuelEvent->eventFlags |= EVENT_LOAD_EXCEEDED;
      }
    } else if (CoreVars->MAP < limits->MAPfuelEnableLimit) {
      cylinder->igntionEvent->eventFlags &= ~(EVENT_LOAD_EXCEEDED);
      cylinder->primaryFuelEvent->eventFlags &= ~(EVENT_LOAD_EXCEEDED);
      if ((cylinder->secondaryFuelEvent) != (void*) 0) {
        cylinder->secondaryFuelEvent->eventFlags &= ~(EVENT_LOAD_EXCEEDED);
      }
    }
    /* Deflood mode */
    if (CoreVars->TPS > PERCENT(60.0) && CoreVars->RPM < RPM(400)) {
      cylinder->primaryFuelEvent->eventFlags |= EVENT_DEFLOOD;
      cylinder->secondaryFuelEvent->eventFlags |= EVENT_DEFLOOD;
    } else {
      cylinder->primaryFuelEvent->eventFlags &= ~(EVENT_DEFLOOD);
      cylinder->secondaryFuelEvent->eventFlags &= ~(EVENT_DEFLOOD);
    }

  }
  /* Copy flags for debug/diagnostics.  */
  cylinder = &Config.CylinderSetup[0];
  KeyUserDebugs.ignitionCuts  = cylinder->igntionEvent->eventFlags;
  KeyUserDebugs.injectionCuts = cylinder->primaryFuelEvent->eventFlags;
}


void updateTimedDerivatives(DerivedVar *derivedVariables) {

  //TODO make a fixed or flex fuel config flag
#if CONFIG == SEANKR1_ID
  derivedVariables->StoichAFR = calculateAFR(CoreVars->EthanolPercentage);
  derivedVariables->FuelDensity = calculateFuelDensity(CoreVars->EthanolPercentage);
#else
  derivedVariables->StoichAFR = Config.fuelingProperties.stoichiometricAFR;
  derivedVariables->FuelDensity = Config.fuelingProperties.densityOfFuelAtSTP;
#endif
  derivedVariables->Displacement = Config.mechanicalProperties.perCylinderVolume;
  FuelAttribs.primaryInjFlow = Config.fuelingProperties.injectorFlow;
  FuelAttribs.secondaryInjFlow = Config.fuelingProperties.secondaryInjectorFlow;

  /* for staged injection calcs*/
  injectorFlowDifference_g = (Config.fuelingProperties.injectorFlow
      * FLOW_SCALE_FACTOR) / Config.fuelingProperties.secondaryInjectorFlow;
}


/*
 * Here we can place code that does sanity checks on various sensor values.
 */
void sensorRangesCheck() {

#if CONFIG == SEANKR1_ID
  if (CoreVars->RPM < RPM(175)) {
    currentFuelingAlgorithm_g = ALGO_SPEED_DENSITY; //FIXME should be blended
  }else if (Config.CylinderSetup[0].syncedEngineData->MAF > AV(3.9)) {
    currentFuelingAlgorithm_g = ALGO_SPEED_DENSITY; //FIXME should be blended
  } else {
    currentFuelingAlgorithm_g = Config.fuelingProperties.fuelingStrategeyCode;
  }
#endif

}

extern const SmallTables3 smallLUTS;

void updateCoreData(MasterConfig *config) {

  CoreVars->BRV = (((uint32_t)ADCBuffers0.BRV * BRV_RANGE) / ADC_DIVISIONS) + BRV_MINIMUM;
  CoreVars->CHT = CHTTransferTable[ADCBuffers0.CHT];
  CoreVars->IAT = IATTransferTable[ADCBuffers0.IAT];
  CoreVars->MAT = IATTransferTable[ADCBuffers0.MAT];
  /* RPM only duplicated here to prevent breakage with EMSTune */
  CoreVars->RPM = getDecoderStats()->RPM;
  CoreVars->EthanolPercentage = readFlexFuelEth();

  /* Perform small table lookups */
  CoreVars->TPS = getTPSpercent(&Config.sensorProperties, ADCBuffers0.TPS, TPSrange_g);
  CoreVars->MAP = TableLookupUINT16(ADCBuffers0.MAP, TablesC.SmallTablesC.MAPlut, MAP_LUT_TABLE_LENGTH);
  CoreVars->EGO = TableLookupUINT16(ADCBuffers0.EGO, TablesC.SmallTablesC.EGOlut, EGO_LOOKUP_TABLE_LENGTH);
  CoreVars->AAP = TableLookupUINT16(ADCBuffers0.AAP, TablesC.SmallTablesC.AAPlut, AAP_LUT_TABLE_LENGTH);
  CoreVars->FuelPressure = TableLookupUINT16(ADCBuffers0.FuelPressure, TablesC.SmallTablesC.fuelPressureLUT, FUEL_PRESSURE_TABLE_LENGTH);
  CoreVars->EGT = TableLookupUINT16(ADCBuffers0.EGT, TablesC.SmallTablesC.EGTlut, EGT_LOOKUP_TABLE_LENGTH);

  DerivedVars->ETE = TableLookupINT16(CoreVars->CHT, TablesA.SmallTablesA.engineTempEnrichmentTable,
      ENGINE_TEMP_ENRICHMENT_TABLE_LENGTH);
  DerivedVars->IDT = TableLookupUINT16(CoreVars->BRV, TablesA.SmallTablesA.injectorDeadTimeTable, IDT_LOOKUP_TABLE_LENGTH);

  CoreVars->IAP = ADCBuffers0.IAP;
  CoreVars->MAF = ADCBuffers0.MAF;

  /* TODO unify load for all algos, for now use MAP */
  DerivedVars->LoadMain = CoreVars->MAP;

  DerivedVars->RefPW = Config.CylinderSetup[dataLogCylinderIndex].primaryFuelEvent->runTime;
  DerivedVars->Advance = (ANGLE_FACTOR / IGNITION_TIMING_ENTRY_FACTOR) * lookupMainTable(CoreVars->RPM, DerivedVars->LoadMain,
      IGNITION_ADVANCE_TABLE_MAIN_LOCATION_ID);

  DerivedVars->Lambda = lookupMainTable(CoreVars->RPM, DerivedVars->LoadMain, LAMBDA_TABLE_LOCATION_ID);
}

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
