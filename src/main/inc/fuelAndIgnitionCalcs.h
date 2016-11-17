/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
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
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_FUELANDIGNITIONCALCS_H_SEEN
#define FILE_FUELANDIGNITIONCALCS_H_SEEN


void calculateFuelAndIgnition(void) FPAGE_FE;


/* The scaling system was reworked extensively in the commit after:
 *
 * c11833092d0b22839287beb2c54787355c9f7adc
 *
 * Refer to all changes in the subsequent commit to decipher the docs below!
 */


/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Always show your working! &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

/* At least, that is what my teachers used to say 15 years ago ;-) */

/******************** The full calculations in an unusable form ******************/

/* Full calcs on a single line */
// final master PW = ((msToTicks * (molarMassOfAir/ molarMassOfAirDivisor) * (airPressure / airPressureDivisor) * (lookedUpVE / (lookedUpVEDivisor * VEpercentageDivisor)) * (perCylinderVolume / perCylinderVolumeDivisor)) / ((universalGasConstant / universalGasConstantDivisor) * (airInletTemp / airInletTempDivisor) * (stoichiometricAFR / stoichiometricAFRDivisor) * (desiredLambda / desiredLambdaDivisor) * (densityOfFuel / (densityOfFuelDivisor * densityOfFuelUnitDivisor)) * (injectorFlow / (injectorFlowUnitDivisor * injectorFlowDivisor))));

/* stripped with only variables and divisors left.*/
// finalMasterPulseWidth = (((airPressure / airPressureDivisor) * (lookedUpVE / (lookedUpVEDivisor * VEpercentageDivisor))) / ((airInletTemp / airInletTempDivisor) * (desiredLambda / desiredLambdaDivisor) * (densityOfFuel / (densityOfFuelDivisor * densityOfFuelUnitDivisor))));

/* stripped with only divisors left.*/
// finalMasterPulseWidth = (airInletTempDivisor * oneLambdaDivisor * densityOfFuelTotalDivisor) / (airPressureDivisor * VETotalDivisor) ;

/* stripped with only divisors left.*/
// divisors = 1;

/* totally stripped with no divisors */
// finalMasterPulseWidth = ((airPressure * lookedUpVE) / (airInletTemp * desiredLambda * densityOfFuel));

/**************************** The constant calculations **************************/

// uint16_t constant;
/* stripped with only constants and divisors left.*/
// constant = ((msToTicks * (molarMassOfAir/ molarMassOfAirDivisor) * (perCylinderVolume / perCylinderVolumeDivisor)) / ((universalGasConstant / universalGasConstantDivisor) * (stoichiometricAFR / stoichiometricAFRDivisor) * (injectorFlow / (injectorFlowUnitDivisor * injectorFlowDivisor))));

/* stripped with only divisors left. Top divisors go on bottom and bottom on top! */
// constDiv = (universalGasConstantDivisor * stoichiometricAFRDivisor * injectorFlowTotalDivisor) / (molarMassOfAirDivisor * perCylinderVolumeDivisor);
//  1310720 = (4096                        * 1024                     * 1024000                 ) / (100                   * 32768                   );

/* stripped with only constants left.*/
// constant = ((msToTicks * molarMassOfAir * perCylinderVolume) / (universalGasConstant * stoichiometricAFR * injectorFlow));
// constant = ((1250      * 2897           * 16384            ) / (34056                * 15053             * 4096        ));

/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/


/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
