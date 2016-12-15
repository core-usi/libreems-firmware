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
 * @brief Initialise the devices state
 *
 * Setup, configure and initialise all aspects of the devices state including
 * but not limited to:
 *
 * - Setup the bus clock speed
 * - Configuration based variable initialisation
 * - I/O register behaviour and initial state
 * - Configure and enable interrupts
 * - Copy tunable data up to RAM from flash
 * - Configure peripheral module behaviour
 */


#define INIT_DEPRICATED_C
#include "inc/freeEMS.h"
#include "inc/interrupts_depricated.h"
#include "inc/utils.h"
#include "inc/commsISRs.h"
#include "inc/init_depricated.h"
#include "inc/init.h"
#include "inc/Configuration.h"
#include <string.h>
#include "inc/CANcomms.h"
#include "engineAngleDecoders/common/interface.h"

extern KeyUserDebug KeyUserDebugs;



/** @brief Set the PLL clock frequency
 *
 * Set the Phase Locked Loop to our desired frequency (80MHz) and enable PLL.
 */
void initPLL(){
  CLKSEL &= PLLSELOFF;  /* Switches to base external OSCCLK to ensure PLL is not being used (off out of reset, but not sure if the monitor turns it on before passing control or not) */
  PLLCTL &= PLLOFF;     /* Turn the PLL device off to adjust its speed (on by default out of reset) */
  REFDV = PLLDIVISOR;   /* 16MHz / (3 + 1) = 4MHz Bus frequency */
  SYNR = PLLMULTIPLIER; /* 4MHz * (9 + 1) = 40MHz Bus frequency */
  PLLCTL |= PLLON;      /* Turn the PLL device back on again at 80MHz */
  enablePLL();
}

/** @brief Switch to using PLL
 *
 * Switch to using PLL for clock (40MHz bus speed). Interrupt is enabled elsewhere.
 *
 * Note: Requires busy wait loop, only for init and emergency use.
 *
 * @todo Should be limited, and have break out with error code and fall back mechanism.
 */
void enablePLL(){
  while (!(CRGFLG & LOCK)){
    /* Do nothing while we wait till the PLL loop locks onto the target frequency. */
    /* Target frequency is given by (2 * (crystal frequency / (REFDV + 1)) * (SYNR + 1)) */
    /* Bus frequency is half PLL frequency and given by ((crystal frequency / (REFDV + 1)) * (SYNR + 1)) */
  }

  CLKSEL = PLLSEL; /* Switches to PLL clock for internal bus frequency        */
  /* from MC9S12XDP512V2.pdf Section 2.4.1.1.2 page 101 Third paragraph       */
  /* "This takes a MAXIMUM of 4 OSCCLK clock cylces PLUS 4 PLL clock cycles"  */
  /* "During this time ALL clocks freeze, and CPU activity ceases"            */
  /* Therefore there is no point waiting for this to occur, we already are... */
}


/// Set up the analogue inputs
void initADC(){
  // Currently not true, and may never be: TODO When the port something uses
  // is changed via the tuning interface, the configuration will be done on
  // the fly, and the value burned to flash such that next boot happens
  // correctly and current running devices are used in that way.

  /* Digital input buffers on the ATD channels are off by default, leave them this way! */
  //ATD0DIEN = ZEROS; /* You are out of your mind if you waste this on digital Inputs */
  //ATD1DIEN0 = ZEROS; /* You are out of your mind if you waste this on digital Inputs (NOT-bonded, can't use) */
  //ATD1DIEN1 = ZEROS; /* You are out of your mind if you waste this on digital Inputs */

  /* And configure them all for analog input */
  //ATD0CTL0 = 0x07/* With mult turned on this is required to be set to cause wrap around, but is correct out of reset */
  //ATD0CTL1 = 0x07/* Trigger and interrupt configuration, unused for now. */
  ATD0CTL2 = 0xC0; /* Turns on the ADC block and sets auto flag clear */
  ATD0CTL3 = 0x40; /* Set sequence length = 8 */
  ATD0CTL4 = 0x73; /* Set the ADC clock and sample period for best accuracy */
  ATD0CTL5 = 0xB0; /* Sets justification to right, multiplex and scan all channels. Writing to this causes conversions to begin */

  /* And configure them all for analog input */
  ATD1CTL0 = 0x07; /* TODO bring this out of config based on chip variant variable. Sets wrap on 8th ADC because we can't use the other 8 on 112 pin version */
  //ATD0CTL1 = 0x07/* Trigger and interrupt configuration, unused for now. */
  ATD1CTL2 = 0xC0; /* Turns on the ADC block and sets auto flag clear */
  ATD1CTL3 = 0x40; /* Set sequence length = 8 */
  ATD1CTL4 = 0x73; /* Set the ADC clock and sample period for best accuracy */
  ATD1CTL5 = 0xB0; /* Sets justification to right, multiplex and scan all channels. Writing to this causes conversions to begin */
}


/** @brief Buffer lookup tables addresses
 *
 * Save pointers to the lookup tables which live in paged flash.
 */
void initLookupAddresses(){
  extern const volatile uint16_t IATTransferTable[]; /* 2k */                                                                            
  extern const volatile uint16_t CHTTransferTable[]; /* 2k */
  extern const volatile uint16_t MATTransferTable[]; /* 2k */
  extern const volatile uint8_t TestTransferTable[];
  extern void* IATTransferTableLocation;
  extern void* CHTTransferTableLocation;
  extern void* MATTransferTableLocation;
  extern void* TestTransferTableLocation;
  IATTransferTableLocation = (void*)&IATTransferTable;
  CHTTransferTableLocation = (void*)&CHTTransferTable;
  MATTransferTableLocation = (void*)&MATTransferTable;
  TestTransferTableLocation = (void*)&TestTransferTable;
}


/** @brief Buffer fuel tables addresses
 *
 * Save pointers to the fuel tables which live in paged flash.
 */
void initFuelAddresses(){
  extern const volatile mainTable VETableMainFlash;                                                                                                
  extern const volatile mainTable VETableSecondaryFlash;
  extern const volatile mainTable AirflowTableFlash;
  extern const volatile mainTable LambdaTableFlash;
  extern const volatile mainTable VETableMainFlash2;
  extern const volatile mainTable VETableSecondaryFlash2;
  extern const volatile mainTable AirflowTableFlash2;
  extern const volatile mainTable LambdaTableFlash2;
  extern void* VETableMainFlashLocation;
  extern void* VETableMainFlash2Location;
  extern void* VETableSecondaryFlashLocation;
  extern void* VETableSecondaryFlash2Location;
  extern void* AirflowTableFlashLocation;
  extern void* AirflowTableFlash2Location;
  extern void* LambdaTableFlashLocation;
  extern void* LambdaTableFlash2Location;

  /* Setup addresses within the page to avoid warnings */
  VETableMainFlashLocation       = (void*)&VETableMainFlash;
  VETableSecondaryFlashLocation  = (void*)&VETableSecondaryFlash;
  AirflowTableFlashLocation      = (void*)&AirflowTableFlash;
  LambdaTableFlashLocation       = (void*)&LambdaTableFlash;
  VETableMainFlash2Location      = (void*)&VETableMainFlash2;
  VETableSecondaryFlash2Location = (void*)&VETableSecondaryFlash2;
  AirflowTableFlash2Location     = (void*)&AirflowTableFlash2;
  LambdaTableFlash2Location      = (void*)&LambdaTableFlash2;
}


/** @brief Copy fuel tables to RAM
 *
 * Initialises the fuel tables in RAM by copying them up from flash.
 */
void initPagedRAMFuel(void){
  extern void* VETableMainFlashLocation;
  extern void* VETableMainFlash2Location;
  extern void* VETableSecondaryFlashLocation;
  extern void* VETableSecondaryFlash2Location;
  extern void* AirflowTableFlashLocation;
  extern void* AirflowTableFlash2Location;
  extern void* LambdaTableFlashLocation;
  extern void* LambdaTableFlash2Location;
  /* Copy the tables from flash to RAM */
  RPAGE = RPAGE_FUEL_ONE;
  memcpy((void*)&TablesA, VETableMainFlashLocation,       sizeof(mainTable));
  memcpy((void*)&TablesB, VETableSecondaryFlashLocation,  sizeof(mainTable));
  memcpy((void*)&TablesC, AirflowTableFlashLocation,      sizeof(mainTable));
  memcpy((void*)&TablesD, LambdaTableFlashLocation,       sizeof(mainTable));
  RPAGE = RPAGE_FUEL_TWO;
  memcpy((void*)&TablesA, VETableMainFlash2Location,      sizeof(mainTable));
  memcpy((void*)&TablesB, VETableSecondaryFlash2Location, sizeof(mainTable));
  memcpy((void*)&TablesC, AirflowTableFlash2Location,     sizeof(mainTable));
  memcpy((void*)&TablesD, LambdaTableFlash2Location,      sizeof(mainTable));
}


/** @brief Buffer timing tables addresses
 *
 * Save pointers to the timing tables which live in paged flash.
 */
void initTimingAddresses(){
  extern const volatile mainTable IgnitionAdvanceTableMainFlash;
  extern const volatile mainTable IgnitionAdvanceTableSecondaryFlash;
  extern const volatile mainTable InjectionAdvanceTableMainFlash;
  extern const volatile mainTable InjectionAdvanceTableSecondaryFlash;
  extern const volatile mainTable IgnitionAdvanceTableMainFlash2;
  extern const volatile mainTable IgnitionAdvanceTableSecondaryFlash2;
  extern const volatile mainTable InjectionAdvanceTableMainFlash2;
  extern const volatile mainTable InjectionAdvanceTableSecondaryFlash2;
  extern void* IgnitionAdvanceTableMainFlashLocation;
  extern void* IgnitionAdvanceTableMainFlash2Location;
  extern void* IgnitionAdvanceTableSecondaryFlashLocation;
  extern void* IgnitionAdvanceTableSecondaryFlash2Location;
  extern void* InjectionAdvanceTableMainFlashLocation;
  extern void* InjectionAdvanceTableMainFlash2Location;
  extern void* InjectionAdvanceTableSecondaryFlashLocation;
  extern void* InjectionAdvanceTableSecondaryFlash2Location;
  /* Setup addresses within the page to avoid warnings */
  IgnitionAdvanceTableMainFlashLocation        = (void*)&IgnitionAdvanceTableMainFlash;
  IgnitionAdvanceTableSecondaryFlashLocation   = (void*)&IgnitionAdvanceTableSecondaryFlash;
  InjectionAdvanceTableMainFlashLocation       = (void*)&InjectionAdvanceTableMainFlash;
  InjectionAdvanceTableSecondaryFlashLocation  = (void*)&InjectionAdvanceTableSecondaryFlash;
  IgnitionAdvanceTableMainFlash2Location       = (void*)&IgnitionAdvanceTableMainFlash2;
  IgnitionAdvanceTableSecondaryFlash2Location  = (void*)&IgnitionAdvanceTableSecondaryFlash2;
  InjectionAdvanceTableMainFlash2Location      = (void*)&InjectionAdvanceTableMainFlash2;
  InjectionAdvanceTableSecondaryFlash2Location = (void*)&InjectionAdvanceTableSecondaryFlash2;
}


/** @brief Copy timing tables to RAM
 *
 * Initialises the timing tables in RAM by copying them up from flash.
 */
void initPagedRAMTime(){
  extern void* IgnitionAdvanceTableMainFlashLocation;
  extern void* IgnitionAdvanceTableMainFlash2Location;
  extern void* IgnitionAdvanceTableSecondaryFlashLocation;
  extern void* IgnitionAdvanceTableSecondaryFlash2Location;
  extern void* InjectionAdvanceTableMainFlashLocation;
  extern void* InjectionAdvanceTableMainFlash2Location;
  extern void* InjectionAdvanceTableSecondaryFlashLocation;
  extern void* InjectionAdvanceTableSecondaryFlash2Location;
  /* Copy the tables from flash to RAM */
  RPAGE = RPAGE_TIME_ONE;
  memcpy((void*)&TablesA, IgnitionAdvanceTableMainFlashLocation,        sizeof(mainTable));
  memcpy((void*)&TablesB, IgnitionAdvanceTableSecondaryFlashLocation,   sizeof(mainTable));
  memcpy((void*)&TablesC, InjectionAdvanceTableMainFlashLocation,       sizeof(mainTable));
  memcpy((void*)&TablesD, InjectionAdvanceTableSecondaryFlashLocation,  sizeof(mainTable));
  RPAGE = RPAGE_TIME_TWO;
  memcpy((void*)&TablesA, IgnitionAdvanceTableMainFlash2Location,       sizeof(mainTable));
  memcpy((void*)&TablesB, IgnitionAdvanceTableSecondaryFlash2Location,  sizeof(mainTable));
  memcpy((void*)&TablesC, InjectionAdvanceTableMainFlash2Location,      sizeof(mainTable));
  memcpy((void*)&TablesD, InjectionAdvanceTableSecondaryFlash2Location, sizeof(mainTable));
}


/** @brief Buffer tunable tables addresses
 *
 * Save pointers to the tunable tables which live in paged flash and their
 * sub-sections too.
 */
void initTunableAddresses(){
  /* Setup addresses within the page to avoid warnings */
  extern const volatile SmallTables1 SmallTablesAFlash;
  extern const volatile SmallTables2 SmallTablesBFlash;
  extern const volatile SmallTables3 SmallTablesCFlash;
  extern const volatile SmallTables4 SmallTablesDFlash;
  extern const volatile SmallTables1 SmallTablesAFlash2;
  extern const volatile SmallTables2 SmallTablesBFlash2;
  extern const volatile SmallTables3 SmallTablesCFlash2;
  extern const volatile SmallTables4 SmallTablesDFlash2;
  /* Tunable blocks */
  extern void* SmallTablesAFlashLocation;
  extern void* SmallTablesAFlash2Location;
  extern void* SmallTablesBFlashLocation;
  extern void* SmallTablesBFlash2Location;
  extern void* SmallTablesCFlashLocation;
  extern void* SmallTablesCFlash2Location;
  extern void* SmallTablesDFlashLocation;
  extern void* SmallTablesDFlash2Location;
  /* Small chunks of TablesA here */
  extern void* voltageVersusDwellDesiredTableLocation;
  extern void* voltageVersusDwellDesiredTable2Location;
  extern void* injectorDeadTimeTableLocation;
  extern void* injectorDeadTimeTable2Location;
  extern void* postStartEnrichmentTableLocation;
  extern void* postStartEnrichmentTable2Location;
  extern void* primingVolumeTableLocation;
  extern void* primingVolumeTable2Location;
  extern void* engineTempEnrichmentTableLocation;
  extern void* engineTempEnrichmentTable2Location;
  extern void* RPMVersusDwellTableLocation;
  extern void* RPMVersusDwellTable2Location;
  extern void* RPMVersusBlendTableLocation;
  extern void* RPMVersusBlendTable2Location;

  /* Small chunks of TablesB here */
  extern void* loggingSettingsLocation;
  extern void* loggingSettings2Location;
  extern void* perCylinderFuelTrimsLocation;
  extern void* perCylinderFuelTrims2Location;
  /* Small chunks of TablesC here */
  extern void* MAFvsVoltageTableLocation;
  extern void* IATvsIgnitionTableLocation;
  extern void* CLTvsIgnitionTableLocation;
  extern void* ETHvsIgnitionTableLocation;
  extern void* fuelDeltaVersusPercentAdderTableLocation;
  extern void* EGOlutTableLocation;
  extern void* EGTlutTableLocation;
  extern void* AAPlutTableLocation;
  extern void* MAPlutTableLocation;
  extern void* oilPressurelutTableLocation;
  extern void* fuelPressurelutTableLocation;
  extern void* rpmVersusIACStepsTableLocation;
  extern void* rpmVersusEngineTempTableLocation;


  /* Fillers here */
  extern void* fillerALocation;
  extern void* fillerA2Location;
  extern void* fillerBLocation;
  extern void* fillerB2Location;
  extern void* fillerCLocation;
  extern void* fillerC2Location;
  extern void* fillerDLocation;
  extern void* fillerD2Location;

  SmallTablesAFlashLocation  = (void*)&SmallTablesAFlash;
  SmallTablesBFlashLocation  = (void*)&SmallTablesBFlash;
  SmallTablesCFlashLocation  = (void*)&SmallTablesCFlash;
  SmallTablesDFlashLocation  = (void*)&SmallTablesDFlash;
  SmallTablesAFlash2Location = (void*)&SmallTablesAFlash2;
  SmallTablesBFlash2Location = (void*)&SmallTablesBFlash2;
  SmallTablesCFlash2Location = (void*)&SmallTablesCFlash2;
  SmallTablesDFlash2Location = (void*)&SmallTablesDFlash2;

  /* TablesA */
  voltageVersusDwellDesiredTableLocation    = (void*)&SmallTablesAFlash.voltageVSDwellTable;
  voltageVersusDwellDesiredTable2Location   = (void*)&SmallTablesAFlash2.voltageVSDwellTable;
  injectorDeadTimeTableLocation             = (void*)&SmallTablesAFlash.injectorDeadTimeTable;
  injectorDeadTimeTable2Location            = (void*)&SmallTablesAFlash2.injectorDeadTimeTable;
  postStartEnrichmentTableLocation          = (void*)&SmallTablesAFlash.postStartEnrichmentTable;
  postStartEnrichmentTable2Location         = (void*)&SmallTablesAFlash2.postStartEnrichmentTable;
  primingVolumeTableLocation                = (void*)&SmallTablesAFlash.primingVolumeTable;
  primingVolumeTable2Location               = (void*)&SmallTablesAFlash2.primingVolumeTable;
  engineTempEnrichmentTableLocation         = (void*)&SmallTablesAFlash.engineTempEnrichmentTable;
  engineTempEnrichmentTable2Location        = (void*)&SmallTablesAFlash2.engineTempEnrichmentTable;
  RPMVersusDwellTableLocation               = (void*)&SmallTablesAFlash.RPMVersusDwellTable;
  RPMVersusDwellTable2Location              = (void*)&SmallTablesAFlash2.RPMVersusDwellTable;
  RPMVersusBlendTableLocation               = (void*)&SmallTablesAFlash.RPMVersusBlendTable;
  RPMVersusBlendTable2Location              = (void*)&SmallTablesAFlash2.RPMVersusBlendTable;

  /* TablesB */
  loggingSettingsLocation       = (void*)&SmallTablesBFlash.loggingSettings;
  loggingSettings2Location      = (void*)&SmallTablesBFlash2.loggingSettings;
  perCylinderFuelTrimsLocation  = (void*)&SmallTablesBFlash.perCylinderFuelTrims;
  perCylinderFuelTrims2Location = (void*)&SmallTablesBFlash2.perCylinderFuelTrims;

  /* TablesC */
  MAFvsVoltageTableLocation  = (void*) &SmallTablesCFlash.MAFvsVoltageTable;
  IATvsIgnitionTableLocation = (void*) &SmallTablesCFlash.IATvsIgnitionTable;
  CLTvsIgnitionTableLocation = (void*) &SmallTablesCFlash.CLTvsIgnitionTable;
  ETHvsIgnitionTableLocation = (void*) &SmallTablesCFlash.ETHvsIgnitionTable;
  EGOlutTableLocation        = (void*) &SmallTablesCFlash.EGOlut;
  EGTlutTableLocation        = (void*) &SmallTablesCFlash.EGTlut;
  AAPlutTableLocation        = (void*) &SmallTablesCFlash.AAPlut;
  MAPlutTableLocation        = (void*) &SmallTablesCFlash.MAPlut;
  fuelPressurelutTableLocation = (void*) &SmallTablesCFlash.fuelPressureLUT;
  oilPressurelutTableLocation  = (void*) &SmallTablesCFlash.oilPressureLUT;
  rpmVersusIACStepsTableLocation = (void*) &SmallTablesCFlash.rpmVersusIACStepsTable;
  rpmVersusEngineTempTableLocation = (void*) &SmallTablesCFlash.rpmVersusEngineTempTable;
  fuelDeltaVersusPercentAdderTableLocation = (void*) &SmallTablesCFlash.fuelDeltaVersusPercentAdderTable;

  /* TablesD */
  // TODO

  /* filler defs */
  fillerALocation  = (void*)&SmallTablesAFlash.filler;
  fillerA2Location = (void*)&SmallTablesAFlash2.filler;
  fillerBLocation  = (void*)&SmallTablesBFlash.filler;
  fillerB2Location = (void*)&SmallTablesBFlash2.filler;
  fillerCLocation  = (void*)&SmallTablesCFlash.filler;
  fillerC2Location = (void*)&SmallTablesCFlash2.filler;
  fillerDLocation  = (void*)&SmallTablesDFlash.filler;
  fillerD2Location = (void*)&SmallTablesDFlash2.filler;
}


/**
 *
 */
void initPagedRAMTune(){
  /* Tunable blocks */
  extern void* SmallTablesAFlashLocation;
  extern void* SmallTablesBFlashLocation;
  extern void* SmallTablesCFlashLocation;
  extern void* SmallTablesDFlashLocation;
  /*
  extern void* SmallTablesAFlash2Location;
  extern void* SmallTablesBFlash2Location;
  extern void* SmallTablesCFlash2Location;
  extern void* SmallTablesDFlash2Location;
  */
  
  /* Copy the tables from flash to RAM */
  RPAGE = RPAGE_TUNE_ONE;
  memcpy((void*)&TablesA, SmallTablesAFlashLocation, sizeof(mainTable));
  memcpy((void*)&TablesB, SmallTablesBFlashLocation, sizeof(mainTable));
  memcpy((void*)&TablesC, SmallTablesCFlashLocation, sizeof(mainTable));
  memcpy((void*)&TablesD, SmallTablesDFlashLocation, sizeof(mainTable));
}


/** @brief Buffer addresses of paged data
 *
 * Save the paged memory addresses to variables such that we can access them
 * from another paged block with no warnings.
 *
 * If you try to access paged data from the wrong place you get nasty warnings.
 * These calls to functions that live in the same page that they are addressing
 * prevent those warnings.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 */
void initAllPagedAddresses(){
  /* Setup pointers to lookup tables */
  initLookupAddresses();
  /* Setup pointers to the main tables */
  initFuelAddresses();
  initTimingAddresses();
  initTunableAddresses();
}


/** @brief Copies paged flash to RAM
 *
 * Take the tables and config from flash up to RAM to allow live tuning.
 *
 * For the main tables and other paged config we need to adjust
 * the RPAGE value to the appropriate one before copying up.
 *
 * This function is simply a delegator to the ones for each flash page. Each
 * one lives in the same paged space as the data it is copying up.
 */
void initAllPagedRAM(){
  /* Setup the flash block pointers before copying flash to RAM using them */
  initAllPagedAddresses();

  /* Copy the tables up to their paged RAM blocks through the window from flash */
  initPagedRAMFuel();
  initPagedRAMTime();
  initPagedRAMTune();

  /* Default to page one for now, perhaps read the configured port straight out of reset in future? TODO */
  setupPagedRAM(TRUE); // probably something like (PORTA & TableSwitchingMask)
}


/* Initialise and set up all running variables that require a non-zero start value here */
/* All other variables are initialised to zero by the premain built in code             */
void initVariables(){
  /* And the opposite for the other halves */
  CoreVars = &CoreVars_g;
  DerivedVars = &DerivedVars0;

  coreStatusA |= FUEL_PUMP_PRIME;

}


/** @brief Flash module setup
 *
 * Initialise configuration registers for the flash module to allow burning of
 * non-volatile flash memory from within the firmware.
 *
 * The FCLKDIV register can be written once only after reset, thus the lower
 * seven bits and the PRDIV8 bit must be set at the same time.
 *
 * We want to put the flash clock as high as possible between 150kHz and 200kHz
 *
 * The oscillator clock is 16MHz and because that is above 12.8MHz we will set
 * the PRDIV8 bit to further divide by 8 bits as per the manual.
 *
 * 16MHz = 16000KHz which pre-divided by 8 is 2000kHz
 *
 * 2000kHz / 200kHz = 10 thus we want to set the divide register to 10 or 0x0A
 *
 * Combining 0x0A with PRDIV8 gives us 0x4A (0x0A | 0x40 = 0x4A) so we use that
 *
 * @author Sean Keys
 *
 * @note If you use a different crystal lower than 12.8MHz PRDIV8 should not be set.
 *
 * @warning If the frequency you end up with is outside 150kHz - 200kHz you may
 *          damage your flash module or get corrupt data written to it.
 */
void initFlash(){
  FCLKDIV = 0x4A;                   /* Set the flash clock frequency */
  FPROT = 0xFF;                     /* Disable all flash protection  */
  FSTAT = FSTAT | (PVIOL | ACCERR); /* Clear any errors              */
}


/* Setup the sci module(s) that we need to use. */
void initSCIStuff(){

  /* The alternative register set selector defaults to zero */

  // set the baud/data speed
  SCI0BD = Config.comSettings.SC0baudDivisor;

  // etc

  /* Switch to alternative register set? */

  // etc

  /* Switch back again? */

  /*
   * 0 = LOOPS (normal two wire operation)
   * 0 = SCISWAI (Wait mode on)
   * 0 = RSRC (if loops=1, int/ext wiring)
   * 0 = M MODE (9 data bits operation) Only set for use with parity bit.
   * 0 = WAKE (idle line wakeup)
   * 0 = ILT (idle line type count start pos)
   * 0 = PE (parity on)
   * 0 = PT (odd parity)
   *
   * 0x13 = ODD (default)
   * 0x12 = EVEN
   * 0x00 = NONE
   */
  SCI0CR1 = 0x00;

  /*
   * 0 = TIE (tx data empty isr disabled)
   * 0 = TCIE (tx complete isr disabled)
   * 1 = RIE (rx full isr enabled)
   * 0 = ILIE (idle line isr disabled)
   * 0 = TE (transmit disabled)
   * 1 = RE (receive enabled)
   * 0 = RWU (rx wake up normal)
   * 0 = SBK (send break off)
   */
  SCI0CR2 = 0x24;
}



/* Set up all the remaining interrupts */
void initInterrupts(){
  /* IMPORTANT : Set the s12x vector base register (Thanks Karsten!!) */
  IVBR = 0xF7; /* Without this the interrupts will never find your code! */

  /* Set up the Real Time Interrupt */
  RTICTL = 0x81; /* 0b_1000_0001 0.125ms/125us period http://duckduckgo.com/?q=1+%2F+%2816MHz+%2F+%282+*+10^3%29+%29 */
//  RTICTL = 0xF9; /* 0b_1111_1001 0.125s/125ms period http://duckduckgo.com/?q=1+%2F+%2816MHz+%2F+%282*10^6%29+%29 */
  CRGINT |= (RTIE | LOCKIE | SCMIE); /* Enable the Real Time Interrupt, PLL Lock Interrupt, and Self Clock Mode Interrupt */
  CRGFLG = (RTIF | LOCKIF | SCMIF); /* Clear the RTI, LOCKI, and SCMI flags */
  RAMWPC |= AVIE; // Enable the access protection interrupt for XGATE RAM

  // set up port H for testing
  PPSH = ZEROS; // falling edge/pull up for all
  PIEH = ONES; // enable all pins interrupts
  PIFH = ONES; // clear all port H interrupt flags

  // TODO set up irq and xirq for testing
  // IRQCR for IRQ

  /* VReg API setup (only for wait mode? i think so) */
//  VREGAPIR = 0x09C3; /* For 500ms period : (500ms - 0.2ms) / 0.2ms = 0b100111000011 = 2499 */
//  VREGAPICL = 0x02; /* Enable the interrupt */
//  VREGAPICL = 0x04; /* Start the counter running */
  /* Writing a one to the flag will set it if it is unset, so best not to mess with it here as it probably starts off unset */

  /* LVI Low Voltage Interrupt enable */
  VREGCTRL = 0x02; // Counts bad power events for diagnosis reasons
}
