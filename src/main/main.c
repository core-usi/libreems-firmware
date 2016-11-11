/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2008-2015 Sean Keys
 *
 * This file is part of the LibreEMS project.
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
 * along with any LibreEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * Thank you for choosing LibreEMS to run your engine!
 */

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
 * @brief The main function!
 *
 * The function main is traditionally an applications starting point. For us
 * it has two jobs. The first is to call init() which initialises everything
 * before any normal code runs. After that main() is simply an infinite loop
 * from which low priority non-realtime code runs. The most important units of
 * code that runs under the main loop umbrella are the injection, ignition and
 * scheduling calculations.
 */


#include "inc/main.h"
#include "inc/init.h"
#include "inc/libreComTypes.h"
#include "inc/printf.h"
#include "inc/dataCalculation.h"
#include "inc/dataAcquisition.h"
#include "inc/debugging.h"
#include "inc/GPIO.h"
#include "inc/CANcomms.h"
#include "engineAngleDecoders/common/interface.h"


/** @brief The main function!
 *
 * The centre of the application is here. From here all non-ISR code is called
 * directly or indirectly. The two coarse blocks are init and the main loop.
 * Init is called first to set everything up and then the main loop is entered
 * where the flow of control continues until the device is switched off or
 * reset (excluding asynchronous ISR code). Currently the main loop only runs
 * the fuel, ignition and scheduling calculation code, and the communications
 * code and only when actually required. The intention is to maintain a very
 * low latency for calculations such that the behaviour of the device more
 * closely reflects the attached engines rapidly changing requirements. When
 * accessory code is added a new scheduling algorithm will be required to keep
 * the latency low without starving any particular blocks of CPU time.
 */
int  main(){ /// @todo TODO maybe move this to paged flash ?
  extern Counter Counters;
  extern uint8_t TXBufferInUseFlags;
  extern uint8_t  RXStateFlags;
  extern uint8_t* TXBufferCurrentPositionHandler;                         
//  extern const volatile fixedConfig1 fixedConfigs1;
  extern uint8_t dbg_tail;
  extern uint8_t dbg_head;
  // Set everything up.
  init();

  sampleEachADC(&ADCBuffers0);       // Read sensors
  uint16_t primingPulseWidth = TableLookupINT16(CoreVars->CHT, TablesA.SmallTablesA.primingVolumeTable, TEMP_VS_PRIMING_VOLUME_TABLE_LENGTH);
  primingPulseWidth = safeAdd(primingPulseWidth, DerivedVars->IDT);

  primeInjectors(primingPulseWidth);

  // Run forever repeating.
  while(TRUE){

    if (CANflags_g.sendDisplayData) {
      //sendDispayData();
      CANflags_g.sendDisplayData = 0;
    }

    /* If ADCs require forced sampling, sample now */
    if (coreStatusA & FORCE_READING) {
      sampleEachADC(&ADCBuffers0);
      sampleAllSyncData();
      resetDecoderStatus(PRIMARY_INPUT_TIMEOUT);
      updateCoreData(&Config);
      Counters.timeoutADCreadings++;

      /* Set flag to say calc required */
      coreStatusA |= CALC_FUEL_IGN;

      /* Clear force reading flag */
      coreStatusA &= CLEAR_FORCE_READING;
    }

    /* If required, do main fuel and ignition calcs first */
    if((coreStatusA & CALC_FUEL_IGN) || getDecoderStats()->decoderFlags.bits.minimalSync) {
      /* Clear the calc required flag */
      coreStatusA &= CLEAR_CALC_FUEL_IGN;

      // TODO DEBUG/TUNING MACRO HERE!
      /* Keep track of how many calcs we are managing per second... */
      Counters.calculationsPerformed++;

      /* Generate the core variables from sensor input and recorded tooth timings */
      updateCoreData(&Config);

      sampleEachADC(&ADCBuffers0); /* TODO pull out synced samples */
      updateTimedDerivatives(DerivedVars);
      sensorRangesCheck();
      updateCylinderCalcs(Config.mechanicalProperties.cylinderCount);
      updateCylinderCuts(Config.mechanicalProperties.cylinderCount, &Config.operatingLimits[getCurrentRunlevel()]);
//      updateIdleEventAngles(FALSE);

      /* Calculate the scheduling based on configuration and previously calculated variables */


      // TODO DEBUG/TUNING MACRO HERE!
    } else {
      /* In the event that no calcs are required, sleep a little before returning to retry. */
      sleepMicro(3000); // TODO tune this, and then replace it completely. not doing this will cause the ISR lockouts to run for too high a proportion of the time
      /* Using 0.8 ticks as micros so it will run for a little longer than the math did */
    }

    if(!(TXBufferInUseFlags)){
      /* Check debug buffer */
      if (dbg_head != dbg_tail) { // There's stuff that needs to get sent
        uint16_t *localLength = 0;
        prep_packet_with_length_ptr(ASYNC_DEBUG_INFO_PACKET,&localLength);
        /* drain the debug log to the packet */
        *localLength = drain_debug_buffer();
        finaliseAndSend(0);
      }
    }

    if(!(TXBufferInUseFlags)){
      if(commsCoreStateFlags & PROCESSING_MULTI_PACKET_PAYLOAD){
      prepForTX();
      multiPacketFunction();
      finaliseAndSend(0);
      } else{

      /* If the flag for com packet processing is set and the TX buffer is available process the data! */
      if(RXStateFlags & RX_READY_TO_PROCESS){
        /* Clear the flag */
        RXStateFlags &= RX_CLEAR_READY_TO_PROCESS;

        /* Handle the incoming packet */
        decodePacketAndRespond();
      }else{// if(lastCalcCount != Counters.calculationsPerformed){ // substitute true for full speed continuous stream test...
        /* send asynchronous data log if required */
        switch (TablesB.SmallTablesB.loggingSettings.datalogStreamType) {
          case ASYNCDATALOGOFF:
            break;
          case ASYNCDATALOGBASIC:
          {
            uint16_t *localLength = 0;
            prep_packet_with_length_ptr(RESPONSE_BASIC_DATALOG,&localLength);
            /* populate data log */
            *localLength = populateBasicDatalog();
            finaliseAndSend(0);
            break;
          }
          case ASYNCDATALOGSCRATCHPAD:
            break;
          case ASYNCDATALOGSTRUCTS:
            break;
          case ASYNCDATALOGPOSITION:
            break;
          case ASYNCDATALOGBLOCKBYTES:
            break;
          case ASYNCDATALOGBLOCKWORDS:
            break;
          case ASYNCDATALOGBLOCKLONGS:
            break;
          case ASYNCDATALOGSTREAMBYTE:
            prep_packet_with_no_length((uint16_t)RESPONSE_BYTE_LA_DATALOG);
            /** Store PTIT for now, later make address of byte configurable TODO @todo */
            *((uint8_t*)TXBufferCurrentPositionHandler) = PTIT;
            TXBufferCurrentPositionHandler++;

            finaliseAndSend(0);
            break;
          case ASYNCDATALOGSTREAMWORD:
            break;
          case ASYNCDATALOGSTREAMLONG:
            break;
        }
        // mechanism to ensure we only send something if the data has been updated
        lastCalcCount = Counters.calculationsPerformed;
      }
    }
  }
    processGPIO(Config.GPIOchannels);
    // PWM experimentation
    adjustPWM();
  }
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
