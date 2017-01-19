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


#include "inc/outputPlotter.h"
#include "inc/dataCalculation.h"
#include "inc/dataAcquisition.h"
#include "inc/init.h"
#include <string.h>
#include "inc/globals.h"
#include "inc/xgate.h"
#include "inc/Configuration.h"
#include "inc/utils.h"
#include "inc/commsUtils.h"
#include "inc/init_depricated.h"


void init(){
  ATOMIC_START();
  initPLL();
  initADC();
  initAllPagedRAM();
  initVariables();
  initFlash();
  initSCIStuff();
  initXGateData();
  initXgate(Config.numberOfPrecisionOutputs);
  initializeXGateOutputs(Config.xGateOutputCHpinMapping);
  initECTchannels(&Config.inputCaptureSettings);
  initGPIOregisters(&Config.GPIOchannels[0]); /* Consider calling this from the above function */
  decoderSpecificInit();
  initPIT();
  initInterrupts();
  initMisc(&Config);
  initIAC(&Config.idleControl);
  // TODO fix init issue with CAN, it can *hang
  //initCAN(0, 0xC0, 0x3A, 0);
  ATOMIC_END();
}

void initializeXGateOutputs(XGateOutputCHpinMapping *pinMapping) {

  /* Generic output settings putting xgate driven outputs on ports B,C,D */
  uint8_t i;

  for (i = 0; i < XGATE_CHANNEL_COUNT; ++i, ++pinMapping) {

    outputSchedules[i].eventFlags = 0; /* default to cleared state */

    XGoutputEvents[i].goHigh.actionBits = IDLE_FLAG | GO_HIGH;
    XGoutputEvents[i].goLow.actionBits =  IDLE_FLAG | GO_LOW;
    XGoutputEvents[i].goHigh.downCounter.countDown32 = 0;
    XGoutputEvents[i].goLow.downCounter.countDown32 = 0;

    XGoutputEvents[i].goHigh.regAddress = pinMapping->regAddress;
    XGoutputEvents[i].goLow.regAddress = pinMapping->regAddress;
    XGoutputEvents[i].goHigh.regMask = pinMapping->regMask;
    XGoutputEvents[i].goLow.regMask = ~(pinMapping->regMask);
  }

  /* Clear nextEventPTR */
  nextEventPTR = (void*)0;
//  /* initialize angles etc */
//  updateIdleEventAngles(TRUE);
  updateCylinderCalcs(Config.mechanicalProperties.cylinderCount);

}


void initPIT() {

  PITMTLD0 = 0x1F; /* 32 prescaler (1 / ((40 MHz) / PRESCALAR)) */

  //PITMTLD1 = 0x1F; /* 32 prescaler  (1 / ((40 MHz) / PRESCALAR)) */

  PITMUX = 0xC0; /* set chan 0-1 to use PITMTLD0 base and chan 2-3 to use PITMTLD1 */
  PITLD0 = 1250;  //Setup timer for 1KHz
  //PITLD1 = 0xFFFF; /* This is our OLD metronome so this number is static */

  PITCFLMT = 0x80; // enable module
  PITCE    = BIT0;  // enable count down on PIT0
  PITINTE  = BIT0; // enable interrupts on 0
  PITFLT   = ONES;  // clear flags
}


void initXgate(uint8_t numChannels) {

  ROUTE_INTERRUPT(0x39, XGATE_INTERRUPT, PRIORITY_LEVEL_ONE) /*enable xgate int on software0 interrupt */
  ROUTE_INTERRUPT(0x73, XGATE_INTERRUPT, PRIORITY_LEVEL_ONE) /*enable xgate int on TC4 */
  ROUTE_INTERRUPT(0x3D, XGATE_INTERRUPT, PRIORITY_LEVEL_TWO) /*enable xgate int on PIT0 */

  /* XGATE sees flash starting at paged address 0xE0+0x8800 to + 30Kb*/
  uint8_t savedRPAGE = RPAGE;
  uint8_t savedPPAGE = PPAGE;

  RPAGE = RPAGE_XGATE;
  PPAGE = 0xE1;
  // XGATE threads execute from RAM
  //TODO set RAM protection there is an upper and lower boundary register
  // we can't use the symbols for the memcpy part because the symbols need to contain xgate relevant values
  memcpy((void*)START_OF_RAM_WINDOW, (void*)START_OF_FLASH_WINDOW, XGATE_TEXT_ALLOCATION_SIZE);
  /* TODO again test symbol offset linker feature that I added over a year ago so the code below can be used
   * Also if those symbols can be used we can then map xg-channels to physical pins outside asm code vs having
   * them hardcoded in the xgate sources
   */

  /*
   * Assemble XG instruction for bit-bang loop optimization
   * ie. SUB R3, (numEvents * sizeOfEventStruct + XGoutputEvents)
   * {"subl",  OP_IMM8, "11000rrriiiiiiii", XG_R_I, 2, 0xC000, 1, 1, CHG_NZVC, ALL}
   * {"subh",  OP_IMM8, "11001rrriiiiiiii", XG_R_I, 2, 0xC800, 1, 1, CHG_NZVC, ALL},
   * */

  uint16_t operand = ((numChannels * sizeof(XGoutputEvent)) + (uint16_t)XGoutputEvents) + XG_SHMEM_OFFSET;

//   readelf src/main/output/LibreEMS-0.3.5-SNAPSHOT-22-g217bc52-DEV-SEANKR1-XGATE-EvenTeeth-Cam-16and1.elf -s | grep XGEventCountOpCode
//    3955: 0000906c     2 OBJECT  GLOBAL DEFAULT   25 XGEventCountOpCode

  uint16_t *insnAddress = (uint16_t*)0x906c; //FIXME we should be able to use a symbol for this

  insnAddress = (uint16_t*)(((uint16_t)insnAddress % (uint16_t)START_OF_RAM_WINDOW) + (uint16_t)START_OF_RAM_WINDOW);
  uint16_t *instructionPointer = (uint16_t*) insnAddress;

  *instructionPointer = 0xC000 + XG_IMM8_REG(3) + (operand & 0xFF);
  ++instructionPointer;
  *instructionPointer = 0xC800 + XG_IMM8_REG(3) + ((operand >> 8) & 0xFF);

  RPAGE = savedRPAGE;
  PPAGE = savedPPAGE;
  // Set the XGVBR register to its start address in flash (page 0xE0 after 2K register space)
  XGVBR = (uint16_t) 0x0800; // EO region is divided to ensure vectors end up here visible to xgate
  // Enable XGate and XGate interrupts
  XGMCTL = (uint16_t) 0x8181;
  TIE |= 0x10; //Enable ISR for TC4
}

void initDefaults() {
  currentFuelingAlgorithm_g = Config.fuelingProperties.fuelingStrategeyCode;
}


void primeInjectors(uint16_t pulseWidth) {
  uint8_t i;
  for (i = 0; i < ENGINE_CYLINDER_COUNT; ++i) {
    uint16_t address = (void *) (Config.CylinderSetup[i].primaryFuelEvent) - (void *) &(outputSchedules[0]);
    uint8_t j;
    if (address == 0) {
      j = 0;
    } else {
      j = address / sizeof(outputEvent);
    }
    loadOutSchedule(j, 200, pulseWidth);
    scheduleOutput(j, TCNT);
    //TODO consider priming secondary injectors too
  }
}

void initIAC(IdleControl *controlInfo) {

  if (controlInfo->IdleTypeID == GM_STEPPER_IDLE) {
    /* Initialize stepper params */
    loadOutSchedule(controlInfo->StepperCH0num, 50, controlInfo->IACpwLength * 1250);
    loadOutSchedule(controlInfo->StepperCH1num, 50, controlInfo->IACpwLength * 1250);

    /* Rewind stepper */
    uint8_t i;
    for (i = 0; i < controlInfo->TotalIACsteps; ++i) {
      scheduleOutput(controlInfo->StepperCH0num, TCNT); //FIXME we dont want to inline here!
      sleep(1); //TODO we might want to make this tunable
    }
  }
}

void sampleAllSyncData() { //TODO move to data aq source file
  uint8_t i;
  for (i = 0; i < ENGINE_CYLINDER_COUNT; ++i) {
    readRTADCValues(Config.CylinderSetup[i].syncedEngineData);
  }
}

void initGPIOregisters(GPIOchannel *GPIOchannels) {

  /* Set all ports to low by default */
  PORTA = 0;
  PORTB = 0;
  PORTC = 0;
  PORTD = 0;

  uint8_t i;

  uint8_t portDDRA = 0xFF; /* default to outputs */
  uint8_t portDDRB = 0xFF; /* default to outputs */
  uint8_t portDDRC = 0xFF; /* default to outputs */
  uint8_t portDDRD = 0xFF; /* default to outputs */
  uint8_t portDDRE = 0xFF; /* default to outputs */
  uint8_t portDDRH = 0xFF; /* default to outputs */
  uint8_t portDDRK = 0xFF; /* default to outputs */
  uint8_t portDDRM = 0xFF; /* default to outputs */


  for (i = 0; i < NUM_GPIO_CHANNELS; ++i) {

    uint16_t regAddress = (uint16_t)(GPIOchannels[i].reg);

    if (GPIOchannels[i].flags.isOutput) {
      continue;
    }

    switch (regAddress) {
    case PORTA_ADDR:
      portDDRA &= ~(GPIOchannels[i].mask);
      break;
    case PORTB_ADDR:
      portDDRB &= ~(GPIOchannels[i].mask);
      break;
    case PORTC_ADDR:
      portDDRC &= ~(GPIOchannels[i].mask);
      break;
    case PORTD_ADDR:
      portDDRD &= ~(GPIOchannels[i].mask);
      break;
    case PORTE_ADDR:
      portDDRE &= ~(GPIOchannels[i].mask);
      break;
    case PORTH_ADDR:
      portDDRH &= ~(GPIOchannels[i].mask);
      //TODO consider additional checks, these pins can gen interrupts
      break;
    case PORTK_ADDR:
      portDDRK &= ~(GPIOchannels[i].mask);
      break;
    case PORTM_ADDR:
      portDDRM &= ~(GPIOchannels[i].mask);
      break;
    default:
      //TODO flag error
      break;
    }
  }

  DDRA = portDDRA | BIT6 | BIT7;        /* CEL and fuel pump are reserved */
  DDRB = portDDRB;
  DDRC = portDDRC;
  DDRD = portDDRD;
  DDRE = (portDDRE | BIT5 | BIT6 | BIT7) & 0xFC; /* See schematics for details */
  DDRH = portDDRH;
  DDRK = portDDRK;

  /* TODO investigate usage */
  DDRJ = 0xFF;
  DDRM = portDDRM;

  /* Enable pull-ups on ports A-D*/
  PUCR |= 0xF;
}

void initPWMchannels() {
  /* TODO add configurables, for now just make it generic */

  /* Default to full 8-bit period */
  PWMPER0 = 0xFF;
  PWMPER1 = 0xFF;
  PWMPER2 = 0xFF;
  PWMPER3 = 0xFF;
  PWMPER4 = 0xFF;
  PWMPER5 = 0xFF;
  PWMPER6 = 0xFF;
  PWMPER7 = 0xFF;

  /* Initial DC of 0 */
  PWMDTY0 = 0;
  PWMDTY1 = 0;
  PWMDTY2 = 0;
  PWMDTY3 = 0;
  PWMDTY4 = 0;
  PWMDTY5 = 0;
  PWMDTY6 = 0;
  PWMDTY7 = 0;

  PWMCLK   = 0;
  PWMPRCLK = 0;
  PWMSCLA  = 0;
  PWMSCLB  = 0;
  PWMPOL   = 0;
  PWMCAE   = 0;
  PWMCTL   = 0xF0; /* See DS for reserved bits */
  PWME     = 0xFF; /* Always set this reg last */
}

void initECTchannels(InputCaptureSettings *settings) {

//  DLYCT = 0xFF; /* See DS for potential uses */
  TSCR1 = 0x88; /* Enable time and precision timer */
  TSCR2 = 0x87; /* Interrupt on overflow */
  PTPSR = 0x1F; /* 0.8uS per tick */

  /* Should always be in capture mode, if you need outputs, use Xgate */
  TIE   = 0;    /* Disable interrupts */
  TFLG1 = 0xFF; /* Clear timer flags */
  TFLG2 = 0xFF; /* Likewise ^ */
  TIOS  = 0x10; /* CH4 reserved for Xgate, 0-3 5-7 IC */
  TCTL1 = 0;
  TCTL2 = 0;

  ICPAR = 0x0C; // Enable PulseAccumulators on TC2-3. Setup Flex-Fuel eth% reading TODO move to specific config section
  PBCTL = 0;
  /* Set all ECT to capture on rising and falling.
   * These settings may be overridden by the decoder.
   */
  TCTL3 = settings->inputCaptureRegs.inputCaptureEdgesTCTL3.value;
  TCTL4 = settings->inputCaptureRegs.inputCaptureEdgesTCTL4.value;

  TIE = 0xFF; /* enable all ECT interrupts */
}

void initXGateData(void) {
  uint8_t savedRPage = RPAGE;
  RPAGE = RPAGE_XGATE;
    // we can't use the symbols for the memcpy part because the symbols need to contain xgate relevant values
  buildCANqueue(Config.canConfig,(CANqueue*)(START_OF_RAM_WINDOW + XGATE_TEXT_ALLOCATION_SIZE));
  RPAGE = savedRPage;
}

void initMisc(MasterConfig *config) {
  memset(&CoreVars_g, 0, sizeof(CoreVars_g));
  TPSrange_g = config->sensorProperties.TPSMaximum - config->sensorProperties.TPSMinimum;
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
