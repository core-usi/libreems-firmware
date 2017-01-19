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
 * @ingroup initializers
 */


#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

/* Libre Headers */
#include "../main/inc/dataCalculation.h"
#include "../main/inc/outputPlotter.h"
#include "../main/inc/utils.h"
#include "floatingPointCalcs.h"
#include "../main/inc/mathFunctions.h"

uint32_t cmockaAirFlow;


/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

/* Test accuracy of math with ideal gas law .
*  I'm not sure what the best way is, maybe we can use double type variables and compare the results with our fixed-point math?
*/
static void testIdealGasLawScalingMaximum(void **state) {
  (void) state; /* unused */


  /* Statics */
  /* FIXME WARNING we are using .MAP to hold a raw KPA value */
  SyncedData mockSyncedData = {.MAP = KPA(250),
		                       .previousFuelRequirement = 1
                              };
  DerivedVar mockDerivedVars = {
      .Lambda = LAMBDA(1.00),
      .VEMain = VE(50)};

  uint32_t airCharge;
  double massInGrams;
  uint16_t cylVolumeCC = CC_VOLUME_S(2000);

  calculateAirCharge(&mockSyncedData, cylVolumeCC, &airCharge);

//  printf("aircharge is %d", airCharge);


  massInGrams = calcAirFlow(mockSyncedData.MAP, cylVolumeCC);

  /* see how close in % we are with our fixed point math */
  if (massInGrams > airCharge){
	  massInGrams =  airCharge / massInGrams;
  } else {
	  massInGrams = massInGrams / airCharge;
  }

  massInGrams = massInGrams * TEN_THOUSANDTH_OF_A_PERCENT;

  /* Check to see if we are within three nines accuracy*/
  assert_in_range((uint32_t)massInGrams, 9990, 9999);

}

static void testIdealGasLawScalingMinimum(void **state) {
  (void) state; /* unused */


  /* Statics */
  /* FIXME WARNING we are using .MAP to hold a raw KPA value */
  SyncedData mockSyncedData = { .MAP = KPA(25),
		                        .previousFuelRequirement = 1
  	  	  	  	              };

  DerivedVar mockDerivedVars = {.Lambda = LAMBDA(1.00), .VEMain = VE(50)};

  uint32_t airCharge;
  uint16_t cylVolumeCC = CC_VOLUME_S(80);
  double massInGrams;

  calculateAirCharge(&mockSyncedData, cylVolumeCC, &airCharge);

  massInGrams = calcAirFlow(mockSyncedData.MAP, cylVolumeCC);

  /* see how close in % we are with our fixed point math */
  if (massInGrams > airCharge){
	  massInGrams =  airCharge / massInGrams;
  } else {
	  massInGrams = massInGrams / airCharge;
  }

  massInGrams = massInGrams * TEN_THOUSANDTH_OF_A_PERCENT;

  /* TODO with default sensors we can only get 98% on the low end*/
  assert_in_range((uint32_t)massInGrams, 9800, 9999);

}

static void testRequiredFuelMinimum(void **state) {
	(void) state; /* unused */

	/* Statics */
	 /* FIXME WARNING we are using .MAP to hold a raw KPA value */
	SyncedData mockSyncedData = {.MAP = KPA(25),
			                     .previousFuelRequirement = 1
	};
	fuelAttributes fuelAttr = {.primaryInjFlow = CC_FLOW_S(200)
	                           };
	uint32_t airCharge;
	DerivedVar mockDerivedVars = {.Lambda = LAMBDA(1.00), .VEMain = VE(50), .IDT = 0, .ETE = W(100), .Displacement = CC_VOLUME_S(100),
			                      .StoichAFR = STOICH_AFR(14.70), .FuelDensity = FUEL_DENSITY_S(GASOLINE_DENSITY)};
	double massInGrams;

	calculateAirCharge(&mockSyncedData, mockDerivedVars.Displacement, &airCharge);

	double reqFuelFP = calcMicroSecondPW(&mockDerivedVars, mockDerivedVars.Lambda, fuelAttr.primaryInjFlow, airCharge);
	calculateRequiredFuel(&fuelAttr, &mockDerivedVars, airCharge, &Config.CylinderSetup[0]);

	if (reqFuelFP > Config.CylinderSetup[0].primaryFuelEvent->runTime) {
		reqFuelFP = Config.CylinderSetup[0].primaryFuelEvent->runTime / reqFuelFP;
	} else {
		reqFuelFP = reqFuelFP / Config.CylinderSetup[0].primaryFuelEvent->runTime;
	}
	reqFuelFP *= TEN_THOUSANDTH_OF_A_PERCENT;

	/* Check to see if we are within two nines accuracy*/
	assert_in_range((uint32_t)reqFuelFP, 9900, 9999);
}

static void testRequiredFuelMaximum(void **state) {
	(void) state; /* unused */

	/* Statics */

	SyncedData mockSyncedData = {.MAP = ADC_100KPA,
			                     .previousFuelRequirement = 1
	                            };
	fuelAttributes fuelAttr = {.primaryInjFlow = CC_FLOW_S(1000)
	                           };
	uint32_t airCharge;
	DerivedVar mockDerivedVars = {.Lambda = LAMBDA(1.00), .VEMain = VE(50), .IDT = 0, .ETE = W(100), .Displacement = CC_VOLUME_S(500),
			                      .StoichAFR = STOICH_AFR(14.70), .FuelDensity = FUEL_DENSITY_S(GASOLINE_DENSITY)};
	double massInGrams;
	currentFuelingAlgorithm_g = ALGO_SPEED_DENSITY;

	calculateAirCharge(&mockSyncedData, mockDerivedVars.Displacement, &airCharge);
	double reqFuelFP = calcMicroSecondPW(&mockDerivedVars, mockDerivedVars.Lambda, fuelAttr.primaryInjFlow, airCharge);

	calculateRequiredFuel(&fuelAttr, &mockDerivedVars, airCharge, &Config.CylinderSetup[0]);

	if (reqFuelFP > Config.CylinderSetup[0].primaryFuelEvent->runTime) {
		reqFuelFP = Config.CylinderSetup[0].primaryFuelEvent->runTime / reqFuelFP;
	} else {
		reqFuelFP = reqFuelFP / Config.CylinderSetup[0].primaryFuelEvent->runTime;
	}
	reqFuelFP *= TEN_THOUSANDTH_OF_A_PERCENT;

	/* Check to see if we are within three nines accuracy*/
	assert_in_range((uint32_t)reqFuelFP, 9990, 9999);
}

static void testRequiredFuelGolden(void **state) {
	(void) state; /* unused */

	SyncedData mockSyncedData = {.MAP = KPA(100),
			                     .previousFuelRequirement = 1
	                            };
	fuelAttributes fuelAttr = {.primaryInjFlow = CC_FLOW_S(200)
	                           };
	uint32_t airCharge;
	DerivedVar mockDerivedVars = {.Lambda = LAMBDA(1.00), .VEMain = VE(50), .IDT = 0, .ETE = W(100), .Displacement = CC_VOLUME_S(250),
			                      .StoichAFR = STOICH_AFR(14.70), .FuelDensity = FUEL_DENSITY_S(GASOLINE_DENSITY)};
	double massInGrams;

	currentFuelingAlgorithm_g = ALGO_SPEED_DENSITY;
	Config.fuelingProperties.fuelAlgoFlags.deltaScaling = 0;  /* Disable delta AE */

	do {

		calculateAirCharge(&mockSyncedData, mockDerivedVars.Displacement, &airCharge);

		double reqFuelFP = calcMicroSecondPW(&mockDerivedVars, mockDerivedVars.Lambda, fuelAttr.primaryInjFlow, airCharge);
		calculateRequiredFuel(&fuelAttr, &mockDerivedVars, airCharge, &Config.CylinderSetup[0]);

		if (reqFuelFP > Config.CylinderSetup[0].primaryFuelEvent->runTime) {
			reqFuelFP = Config.CylinderSetup[0].primaryFuelEvent->runTime / reqFuelFP;
		} else {
			reqFuelFP = reqFuelFP / Config.CylinderSetup[0].primaryFuelEvent->runTime;
		}
		reqFuelFP *= TEN_THOUSANDTH_OF_A_PERCENT;

		/* Check to see if we are within three nines accuracy*/
		assert_in_range((uint32_t)reqFuelFP, 9990, 9999);


		mockSyncedData.MAP++;


	} while (mockSyncedData.MAP < 1023);


}

static void testRequiredMAFGolden(void **state) {
	(void) state; /* unused */

	/* Statics */
	 /* FIXME WARNING we are using .MAP to hold a raw KPA value */
	SyncedData mockSyncedData = {
			.MAP = KPA(100),
	        .TPD = TICKS_PER_DEG_RPM(6000),
			.previousFuelRequirement = 1
	};
	fuelAttributes fuelAttr = { .primaryInjFlow = CC_FLOW_S(200) };
	uint32_t airCharge;
	DerivedVar mockDerivedVars = {
			.Lambda = LAMBDA(1.00),
			.VEMain = VE(100),
			.IDT = 0, .ETE = W(100),
			.Displacement = CC_VOLUME_S(250),
			.StoichAFR = STOICH_AFR(14.70),
			.FuelDensity = FUEL_DENSITY_S(GASOLINE_DENSITY)
	};

	CoreVar mockCoreVars = {
			.RPM = RPM(6000)
	};

	currentFuelingAlgorithm_g = ALGO_MAF;

	cmockaAirFlow = GS(60.250);

    /* How much air are we moving at 6K RPM at STP */
	double gramsPerSecond = (((DENSITY_OF_ONE_CC_OF_AIR_STP * Config.mechanicalProperties.perCylinderVolume) * (mockCoreVars.RPM / RPM_FACTOR)) / SECONDS_PER_MINUTE) \
			             * (ENGINE_CYLINDER_COUNT / Config.mechanicalProperties.revoloutionsPerCycle);
	/* Remove scaling factor for cylinder size */
	gramsPerSecond = gramsPerSecond / CC_VOLUME_F;

	double gramsPerHole = (gramsPerSecond /  ((mockCoreVars.RPM / RPM_FACTOR) / SECONDS_PER_MINUTE )) / (ENGINE_CYLINDER_COUNT /
			Config.mechanicalProperties.revoloutionsPerCycle);


	uint32_t massInGramsFixed;

	double MAF2 = calcMAFatSTP(6000, 4, 250, 2);

	calculateAirCharge(&mockSyncedData, Config.mechanicalProperties.perCylinderVolume, &massInGramsFixed);

	calculateAirCharge(&mockSyncedData, mockDerivedVars.Displacement, &airCharge);

}

static void testEthanolPercentage(void **state) {
	(void) state; /* unused */
	/* TODO should test the conversion function */
}

static void testWarmupPercentage(void **state) {
	(void) state;
	uint16_t basePW = 10000;
	uint16_t warmupPercent = W(50);

	basePW = safeScale(basePW, warmupPercent, SHORT4TH);
	assert_in_range((uint32_t)basePW, 4990, 5010);
}

static void testFlexFuelAFR(void **state) {
	(void) state;
	//TODO add edge and error cases
	uint8_t percentEthanol = (50 * ETHANOL_COMPOSITION_FACTOR);

	uint16_t AFR = calculateAFR(percentEthanol);

	assert_in_range((uint32_t)AFR, 11840, 11850);
}

static void testFlexFuelDensity(void **state) {
	(void) state;
	//TODO add edge and error cases
	uint8_t percentEthanol = (50 * ETHANOL_COMPOSITION_FACTOR);

	uint16_t density = calculateFuelDensity(percentEthanol);

	assert_in_range((uint32_t)density, 740, 750);
}

static void testGPO(void **state) {
	(void) state;

	portKemulated = 0;

	uint16_t monitoredValue = DEGREES_C(100);

	uint8_t i;

	for(i = 0; i < NUM_GPIO_CHANNELS; ++i) {
		Config.GPIOchannels[i].flags.enabled = FALSE;
	}

	Config.GPIOchannels[0].upperBoundary        = DEGREES_C(100);
    Config.GPIOchannels[0].lowerBoundary        = DEGREES_C(90);
    Config.GPIOchannels[0].inputAction          = (void*)0;
    Config.GPIOchannels[0].flags.triggerOnUpper = 1;
    Config.GPIOchannels[0].flags.enabled        = 1;
    Config.GPIOchannels[0].varPointer           = &monitoredValue;
    Config.GPIOchannels[0].reg                  = &portKemulated;
    Config.GPIOchannels[0].flags.hasChild       = FALSE;

	processGPIO(&Config.GPIOchannels[0]);

	assert_int_equal(0, portKemulated);
    /* Should trigger mask */
	monitoredValue = DEGREES_C(101);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask, portKemulated);
	/* Should hold mask */
	monitoredValue = DEGREES_C(99);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask, portKemulated);
	/* Should clear mask */
	monitoredValue = DEGREES_C(89);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, 0);
	/* Should hold mask */
	monitoredValue = DEGREES_C(95);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, 0);
    /* Should trigger mask */
	monitoredValue = DEGREES_C(101);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask, portKemulated);
}

static void testGPOlowTrigger(void **state) {
	(void) state;

	portKemulated = 0;

	uint16_t monitoredValue       = DEGREES_C(100);
	uint16_t secondMonitoredValue = RPM(1000);

	uint8_t i;
	for(i = 0; i < NUM_GPIO_CHANNELS; ++i) {
		Config.GPIOchannels[i].flags.enabled = FALSE;
	}


	Config.GPIOchannels[0].upperBoundary          = DEGREES_C(100);
    Config.GPIOchannels[0].lowerBoundary        = DEGREES_C(90);
    Config.GPIOchannels[0].inputAction          = (void*)0;
    Config.GPIOchannels[0].flags.triggerOnUpper = 0;
    Config.GPIOchannels[0].flags.enabled        = 1;
    Config.GPIOchannels[0].varPointer           = &monitoredValue;
    Config.GPIOchannels[0].flags.isParentEvent  = TRUE;
    Config.GPIOchannels[0].childIndex           = 3;

	Config.GPIOchannels[3].upperBoundary          = RPM(750);
    Config.GPIOchannels[3].lowerBoundary        = RPM(600);
    Config.GPIOchannels[3].inputAction          = (void*)0;
    Config.GPIOchannels[3].flags.triggerOnUpper = 0;
    Config.GPIOchannels[3].varPointer           = &secondMonitoredValue;
    Config.GPIOchannels[3].flags.isParentEvent  = FALSE;
    Config.GPIOchannels[3].childIndex           = 3;


	processGPIO(&Config.GPIOchannels);

	assert_int_equal(0, portKemulated);
    /* Should clear mask */
	monitoredValue = DEGREES_C(101);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, 0);
	/* Should hold mask */
	monitoredValue = DEGREES_C(99);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, 0);
	/* Should set mask */
	monitoredValue = DEGREES_C(89);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, Config.GPIOchannels[0].mask);
	/* Should hold mask */
	monitoredValue = DEGREES_C(99);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, Config.GPIOchannels[0].mask);
	/* Should clear mask */
	monitoredValue = DEGREES_C(101);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, 0);

}

static void testRatio32(void **state) {
	(void) state;

	uint32_t TimeStampA = 50; /* 50 is almost the max muber of times we can have our 16-bit timer roll over without overflow */
	uint32_t TimeStampB = 25;

	uint16_t aToB = ratio32(TimeStampA, TimeStampB, DECODER_STAMP_RATIO_F);
	assert_int_equal(aToB, (DECODER_STAMP_RATIO_F / 2));

	uint16_t BToA = ratio32(TimeStampB, TimeStampA, DECODER_STAMP_RATIO_F);
	assert_int_equal(BToA, (DECODER_STAMP_RATIO_F / 2));
}

static void testGPOChildCondition(void **state) {

	(void) state;

	portKemulated = 0;

	uint16_t monitoredValue = DEGREES_C(100);
	uint16_t monitoredValue2 = RPM(2000);

	uint8_t i;

	for(i = 0; i < NUM_GPIO_CHANNELS; ++i) {
		Config.GPIOchannels[i].flags.enabled = FALSE;
	}

	Config.GPIOchannels[0].upperBoundary        = DEGREES_C(100);
    Config.GPIOchannels[0].lowerBoundary        = DEGREES_C(90);
    Config.GPIOchannels[0].inputAction          = (void*)0;
    Config.GPIOchannels[0].flags.triggerOnUpper = 1;
    Config.GPIOchannels[0].flags.enabled        = 1;
    Config.GPIOchannels[0].flags.hasChild       = 1;
    Config.GPIOchannels[0].childIndex           = 3;
    Config.GPIOchannels[0].varPointer           = &monitoredValue;

	Config.GPIOchannels[3].upperBoundary        = RPM(800);
    Config.GPIOchannels[3].lowerBoundary        = RPM(600);
    Config.GPIOchannels[3].inputAction          = (void*)0;
    Config.GPIOchannels[3].flags.triggerOnUpper = 1;
    Config.GPIOchannels[3].flags.enabled        = 1;
    Config.GPIOchannels[3].varPointer           = &monitoredValue2;

	processGPIO(&Config.GPIOchannels[0]);

	assert_int_equal(0, portKemulated);
    /* Should trigger mask */
	monitoredValue = DEGREES_C(101);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask, portKemulated);

	/* Should clear mask */
	monitoredValue  = DEGREES_C(99);
	monitoredValue2 = RPM(500);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, 0);

	/* Should set  mask */
	monitoredValue = DEGREES_C(101);
	monitoredValue2 = RPM(900);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask, portKemulated);

	/* Should hold mask */
	monitoredValue = DEGREES_C(95);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask & portKemulated, portKemulated);

	/* Should trigger mask */
	monitoredValue = DEGREES_C(101);
	processGPIO(&Config.GPIOchannels);
	assert_int_equal(Config.GPIOchannels[0].mask, portKemulated);


}

static void testCANQueue(void **state) {
	(void) state;

    CANconfig    canConfig[MAX_CAN_QUEUE] = {{0}};
    CANqueue     queue[MAX_CAN_QUEUE]     = {{0}};

    uint8_t numEntries = buildCANqueue(canConfig, queue);

    assert_int_equal(numEntries, 0);

    canConfig[0].CANid = 0x101;
    canConfig[0].TXrateMs = 100;

    numEntries = buildCANqueue(canConfig, queue);
    assert_int_equal(numEntries, 1);

    //assert_int_equal(queue[0].ID, 0x101);
}

static void testAngleOffsetMath(void **state) {
  (void) state;
  /* Check starting form 0 */
  uint16_t baseAngle = ENGINE_ANGLE_S(0);
  uint16_t newAngle = offsetAngle(baseAngle, ENGINE_ANGLE_S(10));
  assert_int_equal(newAngle, ENGINE_ANGLE_S(710));

  /* Check roll over */
  baseAngle = ENGINE_ANGLE_S(20);
  newAngle = offsetAngle(baseAngle, ENGINE_ANGLE_S(30));
  assert_int_equal(newAngle, ENGINE_ANGLE_S(710));
  /* Check *normal */
  baseAngle = ENGINE_ANGLE_S(40);
  newAngle = offsetAngle(baseAngle, ENGINE_ANGLE_S(30));
  assert_int_equal(newAngle, ENGINE_ANGLE_S(10));
}

static void testAngleOffsetMathNegative(void **state) {
  (void) state;
  /* Check starting form 0 */
  uint16_t baseAngle = ENGINE_ANGLE_S(0);
  uint16_t newAngle = offsetAngle(baseAngle, -ENGINE_ANGLE_S(10));
  assert_int_equal(newAngle, ENGINE_ANGLE_S(10));

  /* Check roll over */
  baseAngle = ENGINE_ANGLE_S(710);
  newAngle = offsetAngle(baseAngle, -ENGINE_ANGLE_S(30));
  assert_int_equal(newAngle, ENGINE_ANGLE_S(20));
  /* Check *normal */
  baseAngle = ENGINE_ANGLE_S(40);
  newAngle = offsetAngle(baseAngle, -ENGINE_ANGLE_S(30));
  assert_int_equal(newAngle, ENGINE_ANGLE_S(70));
}


static void testInjectorFlow(void **state) {
  (void) state;

  Config.fuelingProperties.injectorFlow = CC_PER_MINUTE(200);
  //assert_int_equal(numEntries, 1);

  //assert_int_equal(queue[0].ID, 0x101);

}

static void testTableLookupINT16(void **state) {
  (void) state;

  TableEntryINT16 testTable[] = {
      {.lookup = 2, .scalar = -200},
      {.lookup = 4, .scalar = 0},
      {.lookup = 5, .scalar = 100},
      {.lookup = 6, .scalar = 200},
      {.lookup = 7, .scalar = 300},
      {.lookup = 8, .scalar = 400},
      {.lookup = 9, .scalar = 500},
      {.lookup = 20, .scalar = 32767},
  };

  /* Test getting lowest entry with lowest lookup */
  int16_t data = TableLookupINT16(2, testTable,sizeof(testTable)/sizeof(TableEntryINT16));
  assert_int_equal(data, -200);
  /* Test getting lowest entry with a number thats lower than the lowest lookup */
  data = TableLookupINT16(0, testTable,sizeof(testTable)/sizeof(TableEntryINT16));
  assert_int_equal(data, -200);
  /* Test interpolation */
  data = TableLookupINT16(3, testTable,sizeof(testTable)/sizeof(TableEntryINT16));
  assert_int_equal(data, -100);
  /* Test above last entry */
  data = TableLookupINT16(100, testTable,sizeof(testTable)/sizeof(TableEntryINT16));
  assert_int_equal(data, 32767);

  TableEntryINT16 testTable2[] = {
      {.lookup = 2, .scalar = -200},
      {.lookup = 4, .scalar = 0},
      {.lookup = 5, .scalar = 100},
      {.lookup = 6, .scalar = 200},
      {.lookup = 7, .scalar = 300},
      {.lookup = 8, .scalar = 400},
      {.lookup = 9, .scalar = 32767},
      {.lookup = 20, .scalar = 32767},
  };

  /* Test above last entry */
  data = TableLookupINT16(10, testTable2,sizeof(testTable)/sizeof(TableEntryINT16));
  assert_int_equal(data, 32767);


}

static void testTableLookupU1632(void **state) {
  (void) state;

  TableEntryU1632 testTable[] = {
      {.lookup = 2, .scalar = 0},
      {.lookup = 4, .scalar = 1},
      {.lookup = 5, .scalar = 100},
      {.lookup = 7, .scalar = 200},
      {.lookup = 8, .scalar = 300},
      {.lookup = 9, .scalar = 400},
      {.lookup = 10, .scalar = 500},
      {.lookup = 20, .scalar = 32767},
  };

  /* Test getting lowest entry with lowest lookup */
  uint32_t data = TableLookupU16U32(2, testTable,sizeof(testTable)/sizeof(TableEntryU1632));
  assert_int_equal(data, 0);
  /* Test getting lowest entry with a number thats lower than the lowest lookup */
  data = TableLookupU16U32(0, testTable,sizeof(testTable)/sizeof(TableEntryU1632));
  assert_int_equal(data, 0);
  /* Test interpolation */
  data = TableLookupU16U32(6, testTable,sizeof(testTable)/sizeof(TableEntryU1632));
  assert_int_equal(data, 150);
  /* Test above last entry */
  data = TableLookupU16U32(100, testTable,sizeof(testTable)/sizeof(TableEntryU1632));
  assert_int_equal(data, 32767);

  TableEntryU1632 testTable2[] = {
      {.lookup = 2, .scalar  = -200},
      {.lookup = 4, .scalar  = 0},
      {.lookup = 5, .scalar  = 100},
      {.lookup = 6, .scalar  = 10000000},
      {.lookup = 8, .scalar  = 20000000},
      {.lookup = 9, .scalar  = 0xf0000000},
      {.lookup = 20, .scalar = 0xffffffff},
  };

  /* Test above last entry */
  data = TableLookupU16U32(7, testTable2, sizeof(testTable2)/sizeof(TableEntryU1632));
  assert_int_equal(data, 15000000);

  /* Test above last entry */
  data = TableLookupU16U32(21, testTable2, sizeof(testTable2)/sizeof(TableEntryU1632));
  assert_int_equal(data, 0xffffffff);

  /* Test above last entry */
  data = TableLookupU16U32(15, testTable2, sizeof(testTable2)/sizeof(TableEntryU1632));
  assert_int_equal(data, 4172951178);
}

static void testRatio16(void **state) {
  (void) state;

  uint16_t a = 100;
  uint16_t b = 90;
  uint16_t scaler = 100;

  uint16_t ratio = ratio16(b, a, scaler);
  assert_int_equal(ratio, 90);
}

int main(void) {

  const UnitTest tests[] = {
  unit_test(testEthanolPercentage),
  unit_test(testWarmupPercentage),
  unit_test(null_test_success),
  unit_test(testIdealGasLawScalingMaximum),
  unit_test(testIdealGasLawScalingMinimum),
  unit_test(testRequiredFuelGolden),
  unit_test(testRequiredFuelMinimum),
  unit_test(testRequiredFuelMaximum),
  unit_test(testRequiredMAFGolden),
  unit_test(testFlexFuelAFR),
  unit_test(testFlexFuelDensity),
  unit_test(testGPO),
  unit_test(testGPOlowTrigger),
  unit_test(testRatio32),
  unit_test(testGPOChildCondition),
  unit_test(testCANQueue),
  unit_test(testInjectorFlow),
  unit_test(testAngleOffsetMath),
  unit_test(testAngleOffsetMathNegative),
  unit_test(testTableLookupINT16),
  unit_test(testTableLookupU1632),
  unit_test(testRatio16)
  };

  return run_tests(tests);
}

