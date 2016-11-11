/*
 * floatingPointCalcs.h
 *
 *  Created on: Oct 9, 2014
 *      Author: seank
 */

#ifndef SRC_CMOCKA_FLOATINGPOINTCALCS_H_
#define SRC_CMOCKA_FLOATINGPOINTCALCS_H_

/* Libre Headers */
#include "../main/inc/dataCalculation.h"
#include "../main/inc/outputPlotter.h"
#include "../main/inc/utils.h"

#define TEN_THOUSANDTH_OF_A_PERCENT    10000

#define KPA_MINIMUM     0.01f
#define KPA_MAXIMUM     600.00f

#define INJECTOR_MAX    2000
#define INJECTOR_MIN    100  // <- math needs to be revised to permit smaller injectors while maintaining 99.9% accuracy

#define FLOATING_POINT_FINAL_SCALE		125000
#define ADC_100KPA     374u /* ADC value at 100.1290KPA using the default map sensor */

/* ##########################     Golden Numbers    ############################# */
#define GS_MAF_AT_6K_RPM_1L_4STROKE     (double)((250.0 * 4.0 * (6000.0 / 2.0)) / 60.0) * (double)DENSITY_OF_ONE_CC_OF_AIR_STP
/*                                       (250cc * 4 cylinders * RPM) / RevoloutionsPerCycle / secondsPerMinute */


/* Floating point implementations */
double calcAirChargeMAF(double gramsPerSecond, double rpm);
double calcMAFatSTP(double RPM, double cylinderCount, double cylinderDisplacement, double revsPerEngineCycle);
/* Floating point implementation */
double calcAirFlow(double pressure, double volume);
double calcMicroSecondPW(DerivedVar* fuelAttrs, double lambda, double flowCCmin, double airCharge);

extern	const volatile fixedConfig2 fixedConfigs2;
extern	const volatile fixedConfig1 fixedConfigs1;
extern uint32_t cmockaAirFlow; //Temp until core is cleaned up

#endif /* SRC_CMOCKA_FLOATINGPOINTCALCS_H_ */
