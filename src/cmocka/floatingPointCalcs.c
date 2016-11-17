/*
 * floatingPointCalcs.c
 *
 *  Created on: Oct 9, 2014
 *      Author: seank
 */

#include "floatingPointCalcs.h"

/* Floating point implementations */
double calcAirChargeMAF(double gramsPerSecond, double rpm) {

   double massInGrams = gramsPerSecond / rpm / (Config.mechanicalProperties.cylinderCount / Config.mechanicalProperties.revoloutionsPerCycle);

   return massInGrams;
}

double calcMAFatSTP(double RPM, double cylinderCount, double cylinderDisplacement, double revsPerEngineCycle) {
	double MAF = (RPM / revsPerEngineCycle) * cylinderDisplacement * cylinderCount * DENSITY_OF_ONE_CC_OF_AIR_STP / SECONDS_PER_MINUTE;
	return MAF;
}

/* Floating point implementation */
double calcAirFlow(double pressure, double volume) {

  double massInGrams;
  double temperature = CEL_TO_KELVIN_S(20);

  pressure = (pressure * VE(50)) / VE(100);

  massInGrams = ((pressure * volume) / (IGL_R_CONSTANT * temperature)) * MOLAR_MASS_AIR;
  massInGrams *= IGL_LOWER_SCALER;

  return massInGrams;
}

double calcMicroSecondPW(DerivedVar* fuelAttrs, double lambda, double flowCCmin, double airCharge) {

  double reqFuel;
  double fuelDensity = fuelAttrs->FuelDensity;
  double stoichAFR = fuelAttrs->StoichAFR;

  flowCCmin = (flowCCmin * fuelDensity ) / FUEL_DENSITY_F;

  // we should get 202198.775510 =
  //http://calculator.tutorvista.com/chemistry/567/ideal-gas-law-calculator.html
 //293.15K 100kpa .25L = 0.010257466091586617 moles = 0.297158792673 grams
 // 0.297158792673 / 14.7 AFR = 0.02021488385

  //200 cc/min * 0.720 = 144 grams / 60 seconds = 2.4 g/s  = 0.0000024 per uS = 8422.86827304 uSec
  //  or 10,528 ticks

  reqFuel = airCharge / ((stoichAFR * lambda) / LAMBDA(1.0)) ; //Apply lambda to stoich AFR and apply AFR to airCharge
  reqFuel = reqFuel  / flowCCmin;
  reqFuel = reqFuel * FLOATING_POINT_FINAL_SCALE;

  return reqFuel;
}

//double calculateAFR(double percentEth) {
//
//	//uint32_t AFR = (ETHANOL_AFR_STOICH - GASOLINE_AFR_STOICH ) * percentEth + GASOLINE_AFR_STOICH;
//
////	(03:21:40 PM) Abraham Mara: SG * (1 - FF) + SE * E
////	(03:22:28 PM) Abraham Mara: (SE - SG) * FF +SG
////	(03:23:05 PM) Abraham Mara: SG * (1 - FF) + SE * F
//
//	//D$4*(1-$E14) + D$6*$E14
//	double AFR = ((double)GASOLINE_AFR_STOICH * ((100.0 * (double)ETHANOL_COMPOSITION_FACTOR) - percentEth) + (ETHANOL_AFR_STOICH * percentEth));
//
//	return AFR;
//
//}
