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
 * @ingroup communicationsFiles
 *
 * @brief Core communications functions.
 *
 * This file contains most of the core comms functionality. Currently that is
 * only for UART serial style communication. It is already too big and needs
 * to be split up somewhat. This will happen fairly soon during the serial
 * refactoring and protocol fine tuning.
 *
 * @todo TODO function to setup a packet and send it fn(populateBodyFunctionPointer(), header, other, fields, here, and, use, or, not, within){}
 * @todo TODO factor many things into functions and move the receive delegator to its own file
 */


#define COMMSCORE_C
#include "inc/freeEMS.h"
#include "inc/flashWrite.h"
#include "inc/interrupts_depricated.h"
#include "inc/utils.h"
#include "inc/printf.h"
#include "inc/tableLookup.h"
#include "inc/locationIDs.h"
#include "inc/blockDetailsLookup.h"
#include "inc/commsCore.h"
#include "inc/debugging.h"
#include "inc/init.h"
#include <stdint.h>
#include <string.h> /// @todo TODO this is pulling in the system string.h not the m68hc1x version, and functions other than memcpy do not work because they are not in crt1.o or other included-by-default libs
#include "decoders_depricated/inc/BenchTest.h"
#include "inc/dataLogDefinitions.h"
#include "inc/libreComTypes.h"
#include "inc/commsUtils.h"
#include "inc/globals.h"
#include "engineAngleDecoders/common/interface.h"
#include "inc/printf.h"

#define BENCH_TEST_NAME "BenchTest"


/* Global Comms Variables */
uint8_t  RXBufferContentSourceID;
uint8_t* RXBufferCurrentPosition; 
uint16_t RXCalculatedPayloadLength;
uint8_t  RXHeaderFlags;
uint16_t RXHeaderPayloadID;
uint16_t RXHeaderPayloadLength;
uint8_t  RXStateFlags;
uint8_t* TXHeaderFlags;
uint8_t* TXBufferCurrentPositionCAN0;
uint8_t* TXBufferCurrentPositionHandler;
uint8_t* TXBufferCurrentPositionSCI0;
uint8_t  TXBufferInUseFlags;

uint8_t  commsCoreStateFlags;
uint8_t  currentChunk;
uint8_t  currentDescription;
uint16_t baseOffset;
uint8_t  packetPayloadEnum;
uint16_t RXHeaderPayloadIDInProcess;
uint16_t payloadID;

sendMultiPacketFunction multiPacketFunction;

extern void serialMonitor(void);  // Serial Monitor boot address



/** @brief Populate a basic datalog packet
 *
 * Copies various chunks of data to the transmission buffer and truncates to
 * the configured length. If changing this, update the maxBasicDatalogLength.
 */
uint16_t populateBasicDatalog(){
  /// @todo TODO setup proper sequence and clock with some sort of differential measurement log to log. insert in front of actual data because these are part of the log itself.

//  KeyUserDebugs.zsp10 = Counters.pinScheduledWithTimerExtension;
  KeyUserDebugs.coreStatusA = coreStatusA;
  KeyUserDebugs.clockIn8thsOfAMilli = Clocks.realTimeClockMain;
  KeyUserDebugs.clockInMilliSeconds = Clocks.realTimeClockMillis;


  uint16_t confSize = 0;
  uint8_t chunkLimit = TablesB.SmallTablesB.loggingSettings.firstChunk + TablesB.SmallTablesB.loggingSettings.numberOfChunks;
  uint8_t chunks;
  for(chunks=TablesB.SmallTablesB.loggingSettings.firstChunk;chunks<chunkLimit;chunks++){
    uint16_t localSize = TablesB.SmallTablesB.loggingSettings.logChunks[chunks].size;
    confSize += localSize;
    if(confSize > 2048){
      confSize -= localSize;
      break;
    }
    memcpy(TXBufferCurrentPositionHandler, TablesB.SmallTablesB.loggingSettings.logChunks[chunks].address, localSize);
    TXBufferCurrentPositionHandler += localSize;
  }
  // After copying data, otherwise tempClock is NEVER zero and reset detection does NOT work
  ++KeyUserDebugs.tempClock;

  return confSize;
}


// All of these require some range checking, eg only some registers, and all RAM, not flash, not other regs
// TODO pointer for one byte
// TODO pointer for one short
// TODO function to log generic memory region by location and size ? requires length!
// Ranges are :
// RAM window
// bss/data region
// IO registers etc that can't be altered simply by reading from.
// NOT :
// flash makes no sense
// some regs are sensitive
// some RAM is unused
// serial buffers make no sense
// eeprom makes no sense
//
// 2k of regs max - user beware for now
// 12k of RAM max
//
//init :
//logaddr = fixed.addr
//loglen = fixed.len
//
//len = loglen OR 1 OR 2
//
//check :
//if((addr < 0x0800) && (length < (0x0800 - addr))){
//  // reg space is OK
//}else if(((0x1000 < addr) && (addr < 0x4000)) && (length < (0x4000 - addr))){
//  // RAM space is OK
//}else{
//  // send an error instead
//}
//
//run check at init and set time, not run time or just not check?? maybe its silly to check at all
//
// /* Just dump the ADC channels as fast as possible */
//void populateScopeLogADCAll(){
//  sampleBlockADC(TXBufferCurrentPositionHandler);
//  TXBufferCurrentPositionHandler += sizeof(ADCBuffer);
//}


// what does this mean >> ??? TODO Look at the time stamps and where to write them, also whether to function call these simple blocks or write one function that handles all the logic.


/** @brief Finalise a packet and send it
 *
 * This functions job is to finalise the main loop part of the packet sending
 * process. It configures the pos/neg ack header bit, adds the code if neg,
 * runs a checksum over the packet data and tags it to the end before
 * configuring the various ISRs that need to send the data out.
 *
 * @bug http://issues.freeems.org/view.php?id=81
 * @todo TODO fix the double/none start byte bug and remove the hack!
 */
void finaliseAndSend(uint16_t errorID){

  if(errorID != 0){
    *TXHeaderFlags |= HEADER_IS_NACK;
    *((uint16_t*)TXBufferCurrentPositionHandler) = errorID;
    TXBufferCurrentPositionHandler += 2;
  }

  /* Tag the checksum on the end */
  *TXBufferCurrentPositionHandler = checksum((uint8_t*)&TXBuffer, ((uint16_t)TXBufferCurrentPositionHandler - (uint16_t)&TXBuffer));

  /* Send it out on all the channels required. */

  /* SCI0 - Main serial interface */
  if(TXBufferInUseFlags & COM_SET_SCI0_INTERFACE_ID){
    /* Initiate transmission */
    SCI0DRL = START_BYTE;

    /* Note : Order Is Important! */
    /* TX empty flag is already set, so we must clear it by writing out before enabling the interrupt */
    SCI0CR2 |= (SCICR2_TX_ENABLE | SCICR2_TX_ISR_ENABLE);
  }
  /* CAN0 - Main CAN interface */
  if(TXBufferInUseFlags & COM_SET_CAN0_INTERFACE_ID){
    // just clear up front for now
    TXBufferInUseFlags &= COM_CLEAR_CAN0_INTERFACE_ID;
  }
  /* spare2 */
  if(TXBufferInUseFlags & COM_SET_SPARE2_INTERFACE_ID){
    // just clear up front for now
    TXBufferInUseFlags &= COM_CLEAR_SPARE2_INTERFACE_ID;
  }
  /* spare3 */
  if(TXBufferInUseFlags & COM_SET_SPARE3_INTERFACE_ID){
    // just clear up front for now
    TXBufferInUseFlags &= COM_CLEAR_SPARE3_INTERFACE_ID;
  }
  /* spare4 */
  if(TXBufferInUseFlags & COM_SET_SPARE4_INTERFACE_ID){
    // just clear up front for now
    TXBufferInUseFlags &= COM_CLEAR_SPARE4_INTERFACE_ID;
  }
  /* spare5 */
  if(TXBufferInUseFlags & COM_SET_SPARE5_INTERFACE_ID){
    // just clear up front for now
    TXBufferInUseFlags &= COM_CLEAR_SPARE5_INTERFACE_ID;
  }
  /* spare6 */
  if(TXBufferInUseFlags & COM_SET_SPARE6_INTERFACE_ID){
    // just clear up front for now
    TXBufferInUseFlags &= COM_CLEAR_SPARE6_INTERFACE_ID;
  }
  /* spare7 */
  if(TXBufferInUseFlags & COM_SET_SPARE7_INTERFACE_ID){
    // just clear up front for now
    TXBufferInUseFlags &= COM_CLEAR_SPARE7_INTERFACE_ID;
  }
}


/** @brief Decode a packet and respond
 *
 * This is the core function that controls which functionality is run when a
 * packet is received in full by the ISR code and control is passed back to the
 * main loop code. The vast majority of communications action happens here.
 */
void decodePacketAndRespond(){
  // How big was the packet that we got back
  uint16_t RXPacketLengthReceived = (uint16_t)RXBufferCurrentPosition - (uint16_t)&RXBuffer;

  /* Check that the packet is big enough for header,ID,checksum */
  if(RXPacketLengthReceived < 4){
    resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
    FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_PACKETS_UNDER_LENGTH_OFFSET);
    KeyUserDebugs.serialAndCommsCodeErrors++;
    return;
  }

  /* Pull out the received checksum and calculate the real one, then check */
  uint8_t RXReceivedChecksum = (uint8_t)*(RXBufferCurrentPosition - 1);
  uint8_t RXCalculatedChecksum = checksum((uint8_t*)&RXBuffer, RXPacketLengthReceived - 1);
  if(RXCalculatedChecksum != RXReceivedChecksum){
    resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
    FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_CHECKSUM_MISMATCHES_OFFSET);
    KeyUserDebugs.serialAndCommsCodeErrors++;
    return;
  }

  /* Start this off as full packet length and build down to the actual length */
  RXCalculatedPayloadLength = RXPacketLengthReceived;

  /* Grab the RX header flags out of the RX buffer */
  RXBufferCurrentPosition = (uint8_t*)&RXBuffer;
  RXHeaderFlags = *RXBufferCurrentPosition;
  RXBufferCurrentPosition++;
  RXCalculatedPayloadLength--;

  /* Grab the payload ID for processing and load the return ID */
  RXHeaderPayloadID = *((uint16_t*)RXBufferCurrentPosition);

  prepForTX();

  RXBufferCurrentPosition += 2;
  RXCalculatedPayloadLength -= 2;

  /* Check that the length is sufficient for the fields configured. Packets
   * that are too long will be caught and rejected on an individual payload
   * ID basis as the information required to handle that is not available at
   * this point. Packets that are too short are rejected immediately!
   */
  if(((RXHeaderFlags & HEADER_HAS_LENGTH) && (RXHeaderFlags & HEADER_HAS_SEQUENCE) && (RXPacketLengthReceived < 7))
    || ((RXHeaderFlags & HEADER_HAS_LENGTH) && (RXPacketLengthReceived < 6))
    || ((RXHeaderFlags & HEADER_HAS_SEQUENCE) && (RXPacketLengthReceived < 5))){
    finaliseAndSend(PACKET_TOO_SHORT_FOR_SPECIFIED_FIELDS);
    resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
    return;
  }

  /* Subtract checksum to get final length */
  RXCalculatedPayloadLength--;

  if(RXHeaderFlags & HEADER_HAS_SEQUENCE){
    *TXBufferCurrentPositionHandler = *RXBufferCurrentPosition;
    RXBufferCurrentPosition++;
    TXBufferCurrentPositionHandler++;
    RXCalculatedPayloadLength--;
    *TXHeaderFlags |= HEADER_HAS_SEQUENCE;
  }

  if(RXHeaderFlags & HEADER_HAS_LENGTH){
    RXHeaderPayloadLength = *((uint16_t*)RXBufferCurrentPosition);
    RXBufferCurrentPosition += 2;
    RXCalculatedPayloadLength -= 2;
    /* Already subtracted one for checksum */
    if(RXHeaderPayloadLength != RXCalculatedPayloadLength){
      finaliseAndSend(PAYLOAD_LENGTH_HEADER_MISMATCH);
      resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
      return;
    }
  }

  /* Calculate the position of the end of the stored packet for later use as a buffer */
  void* leftOverBuffer = (void*)((uint16_t)&RXBuffer + RXPacketLengthReceived);

  uint16_t errorID = 0;
  /* This is where all the communication logic resides.
   *
   * Please Note: Length and its flag should be set by each return packet
   * type handler if required or desired. If an ack has been requested,
   * ensure the negative ack flag is set if the operation failed.
   */

  //tempHack:
  switch (RXHeaderPayloadID){

  // LibreEMS Core Comms Interface cases
    case REQUEST_JUMP_TO_SERIAL_MONITOR:
       //TODO check serial monitor version
       if (getDecoderStats()->RPM != 0) {
         e_printf("ENGINE IS RUNNING, request to jump to SM DENIED!\n");
       break;
       }
       ATOMIC_START();
       serialMonitor();
       break;
     case REQUEST_LIST_OF_DATASTREAM_IDS:
           //Reply packet RESPONSE_LIST_OF_DATASTREAM_IDS
       // Here we return a list of Datalog IDs, 8-bit IDs gives us more then enough possibilities IMO, do you think storage for 5 IDs is enough?
       // PACKET PAYLOAD RESPONSE = ...[ID,ID,ID,ID,ID]...
       // ID 0 should be reserved for ALL, so valid IDs are 1-255
       break;
     case REQUEST_DEFINE_DATASTREAM_ID:
         //(A)
       // Here we get a datalog ID along with what variables we want. Now since the user application is aware of the total available stream
       //variables I'm inclined to have the user application send a multi-byte bit-mask. One bit for each variable, 0 = I dont want it,
       // 1 = yes give it to me.
       //Example Playload:  [STREAMID, MULTIBYTE MASK]
       //(B)
       //Alternative, since each variable ID is only 1 byte, we can afford to send a list of IDs. If you prefer this just let me know.
       //now that I think about it, this is more reasonable IMO. It's not like we are pressed for serial time etc.
       //Example Playload:  [STREAMID, vID,vID,vID,vID,vID....]
         break;
     case REQUEST_SET_DATASTREAM_ID:
           //Easy enough, just set the stream ID. Once this is set the application should send REQUEST_DATALOG_DESCRIPTOR
       //On success return the ID request
       //On fail send the default id of 0
       //We should doc these protocols as a LibreEMS supplemental in addition to the underlying freeems coms
       break;
     case RETRIEVE_JSON_FIELD_DESCRIPTOR: /* return a data-stream descriptor in json */
       multiPacketFunction = &sendFieldDescriptor;
       multiPacketFunction();
       break;
     case RETRIEVE_JSON_TABLE_DESCRIPTOR: /* return a data-stream descriptor in json */
        multiPacketFunction = &sendTableDescriptor;
        multiPacketFunction();
        break;
     case RETRIEVE_JSON_DATALOG_DESCRIPTOR: /* return a data-stream descriptor in json */
        multiPacketFunction = &sendDataStreamDescriptor;
        multiPacketFunction();
        break;
       /* Pattern testing implies that outputs will be auto scheduled via the RTI. IE you set the initial values for
    * the pattern generator and observe the results. */
     case START_PATTERN_TEST_SEQUENCE:
    // This only works on the bench test decoder
    if (compare((uint8_t*) &decoderName, (uint8_t*) BENCH_TEST_NAME, sizeof(BENCH_TEST_NAME))) {
      errorID = THIS_IS_NOT_THE_BENCH_TEST_DECODER;
      break;
    }
    if (RXCalculatedPayloadLength != 10) {
      errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
      break;
    }
       BTpatternParemeterSet.simulatedTCNT = 0;
       BTpatternParemeterSet.delay = *((uint32_t *) RXBufferCurrentPosition);
       RXBufferCurrentPosition += sizeof(uint32_t);
       BTpatternParemeterSet.runtime = *((uint16_t *) RXBufferCurrentPosition);
       RXBufferCurrentPosition += sizeof(uint16_t);
       BTpatternParemeterSet.testInterval = *((uint16_t *) RXBufferCurrentPosition);
       RXBufferCurrentPosition += sizeof(uint16_t);;
       BTpatternParemeterSet.testID = *((uint8_t *) RXBufferCurrentPosition);
       RXBufferCurrentPosition += sizeof(uint8_t);
       BTpatternParemeterSet.numberOfEvents = *((uint8_t *) RXBufferCurrentPosition);
       BTpatternParemeterSet.channel = 0;

       // Validate input here returning codes if things are out of bounds
       //  SEANK define PATTERN_TEST_MIN_ID and MAX _ID perhaps in an ENUM and uncommment
       //  the following,  add other validation code for the other params unles the range of the
       //  size is considered valid (note that in a comment please) DJA
       //
       // if ((test_id < PATTERN_TEST_MIN_ID) && (test_id > PATTERN_TEST_MAX_ID)) {
       // errorID = PATTERN_TEST_INVALID_TEST_ID;
       // break;
       //}
       // Validate other params as well

       // Do Something cool here
       // Cool stuff for the pattern tester will be seen in the RTI code.

       break;
     case OUTPUT_TEST_SEQUENCE:
         if (RXCalculatedPayloadLength != 10) {
           errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
           break;
         }
         BTpatternParemeterSet.simulatedTCNT = 0;
         BTpatternParemeterSet.delay = *((uint32_t *) RXBufferCurrentPosition);
         RXBufferCurrentPosition += sizeof(uint32_t);
         BTpatternParemeterSet.runtime = *((uint16_t *) RXBufferCurrentPosition);
         RXBufferCurrentPosition += sizeof(uint16_t);
         BTpatternParemeterSet.testInterval = *((uint16_t *) RXBufferCurrentPosition);
         RXBufferCurrentPosition += sizeof(uint16_t);;
         BTpatternParemeterSet.channel = *((uint8_t *) RXBufferCurrentPosition);
         RXBufferCurrentPosition += sizeof(uint8_t);
         BTpatternParemeterSet.numberOfEvents = *((uint8_t *) RXBufferCurrentPosition);
         tfp_printf("Output Test Sequence Received");
       break;
  // FreeEMS Core Comms Interface cases
    case REQUEST_INTERFACE_VERSION:
      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }

      /* This type must have a length field, set that up */
      *((uint16_t*)TXBufferCurrentPositionHandler) = sizeof(interfaceVersion);
      *TXHeaderFlags |= HEADER_HAS_LENGTH;
      TXBufferCurrentPositionHandler += 2;
      /* Load the body into place */
      memcpy((void*)TXBufferCurrentPositionHandler, (void*)&interfaceVersion, sizeof(interfaceVersion));
      TXBufferCurrentPositionHandler += sizeof(interfaceVersion);
      break;
    case REQUEST_FIRMWARE_VERSION:
      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }
      /* This type must have a length field, set that up */
      *((uint16_t*)TXBufferCurrentPositionHandler) = sizeof(firmwareVersion);
      *TXHeaderFlags |= HEADER_HAS_LENGTH;
      TXBufferCurrentPositionHandler += 2;
      /* Load the body into place */
      memcpy((void*)TXBufferCurrentPositionHandler, (void*)&firmwareVersion, sizeof(firmwareVersion));
      TXBufferCurrentPositionHandler += sizeof(firmwareVersion);
      break;
    case REQUEST_MAX_PACKET_SIZE:
      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }
      /* Load the size into place */
      *((uint16_t*)TXBufferCurrentPositionHandler) = RX_BUFFER_SIZE;
      TXBufferCurrentPositionHandler += 2;
      break;
    case REQUEST_ECHO_PACKET_RETURN:
      /* This type must have a length field, set that up */
      *((uint16_t*)TXBufferCurrentPositionHandler) = RXPacketLengthReceived;
      *TXHeaderFlags |= HEADER_HAS_LENGTH;
      TXBufferCurrentPositionHandler += 2;
      /* Load the body into place */
      memcpy((void*)TXBufferCurrentPositionHandler, (void*)&RXBuffer, RXPacketLengthReceived);
      /* Note, there is no overflow check here because the TX buffer is slightly       */
      /* bigger than the RX buffer and there is overflow checking for receives anyway. */
      TXBufferCurrentPositionHandler += RXPacketLengthReceived;
      break;
    case REQUEST_SOFT_SYSTEM_RESET:
      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
      }else{ // Perform soft system reset
        _start();
      }
      break;
    case REQUEST_HARD_SYSTEM_RESET:
      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
      }else{
        /* This is how the serial monitor does it. */
        COPCTL = 0x01; /* Arm with shortest time */
        ARMCOP = 0xFF; /* Write bad value, should cause immediate reset */
        /* Using _start() only resets the app ignoring the monitor switch. It does not work */
        /* properly because the location of _start is not the master reset vector location. */
      }
      break;
    case REQUEST_RE_INIT_OF_SYSTEM:
      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
      }else{
        init();
      }
      break;
  // FreeEMS Vanilla Firmware Specific cases
    case CLEAR_COUNTERS_AND_FLAGS_TO_ZERO:
      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }

      uint16_t zeroCounter;
      uint8_t* counterPointer;

      counterPointer = (uint8_t*) &Counters;
      for(zeroCounter = 0;zeroCounter < sizeof(Counter);zeroCounter++){
        *counterPointer = 0;
        counterPointer++;
      }

      KeyUserDebugs.flaggableFlags = 0;
      counterPointer = (uint8_t*) &Flaggables;
      for(zeroCounter = 0;zeroCounter < sizeof(Flaggable);zeroCounter++){
        *counterPointer = 0;
        counterPointer++;
      }

      KeyUserDebugs.flaggableFlags2 = 0;
      counterPointer = (uint8_t*) &Flaggables2;
      for(zeroCounter = 0;zeroCounter < sizeof(Flaggable2);zeroCounter++){
        *counterPointer = 0;
        counterPointer++;
      }
      break;
    case REQUEST_DECODER_NAME:
    case REQUEST_FIRMWARE_BUILD_DATE:
    case REQUEST_COMPILER_VERSION:
    case REQUEST_OPERATING_SYSTEM:

      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }

      uint8_t* stringToSend = 0;
      switch (RXHeaderPayloadID) {
        case REQUEST_DECODER_NAME:
          stringToSend = (uint8_t*)decoderName;
          break;
        case REQUEST_FIRMWARE_BUILD_DATE:
          stringToSend = (uint8_t*)buildTimeAndDate;
          break;
        case REQUEST_COMPILER_VERSION:
          stringToSend = (uint8_t*)compilerVersion;
          break;
        case REQUEST_OPERATING_SYSTEM:
          stringToSend = (uint8_t*)operatingSystem;
          break;
      }
      /* This type must have a length field, set that up and load the body into place at the same time */
      *((uint16_t*)TXBufferCurrentPositionHandler) = stringCopy((TXBufferCurrentPositionHandler + 2), stringToSend);
      *TXHeaderFlags |= HEADER_HAS_LENGTH;
      // Update with length field and string length.
      TXBufferCurrentPositionHandler += 2 + *((uint16_t*)TXBufferCurrentPositionHandler);
      break;
    case UPDATE_BLOCK_IN_RAM:
      {
        // Subtract six to allow for the locationID, size, offset
        if(RXCalculatedPayloadLength < 7){
          errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
          break;
        }

        // Extract the RAM location ID
        uint16_t locationID = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the offset to place the data at
        uint16_t offset = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the size of the data to be stored
        uint16_t size = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Look up the memory location details
        blockDetails details;
        lookupBlockDetails(locationID, &details);

        // Don't let anyone write to running variables unless we are running BenchTest firmware!
        if((details.flags & BLOCK_IS_READ_ONLY) && compare((uint8_t*)&decoderName, (uint8_t*)BENCH_TEST_NAME, sizeof(BENCH_TEST_NAME))){
          errorID = ATTEMPT_TO_WRITE_TO_READ_ONLY_BLOCK;
          break;
        }

        // Subtract six to allow for the locationID, size, offset
        if((RXCalculatedPayloadLength - 6) != size){
          errorID = PAYLOAD_NOT_EQUAL_TO_SPECIFIED_VALUE;
          break;
        }

        // If either of these is zero then this block is not in RAM!
        if((details.RAMPage == 0) || (details.RAMAddress == 0)){
          errorID = INVALID_MEMORY_ACTION_FOR_ID;
          break;
        }

        // Check that size and offset describe a region that is not out of bounds
        if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
          errorID = INVALID_SIZE_OFFSET_COMBINATION;
          break;
        }

        // Don't allow sub region manipulation where it does not make sense or is unsafe.
        if((size != details.size) && !(details.flags & BLOCK_IS_INDEXABLE)){
          errorID = UNCHECKED_TABLE_MANIPULATION_NOT_ALLOWED;
          break;
        }

        // Save page values for restore
        uint8_t oldRamPage = RPAGE;
        // Set the viewable RAM page
        RPAGE = details.RAMPage;

        /// TODO @todo factor this out into validation delegation function once the number of types increases somewhat
        //
        if((details.flags & BLOCK_IS_MAIN_TABLE) || (details.flags & BLOCK_IS_2DUS_TABLE)){
          void* bufferToCheck;

          // For sub regions, construct an image for verification
          if(size != details.size){
            // Copy data from destination location to buffer
            memcpy(leftOverBuffer, details.RAMAddress, details.size);

            // Copy data from rx buffer to buffer over writing old data
            memcpy(leftOverBuffer + offset, RXBufferCurrentPosition, size);

            bufferToCheck = leftOverBuffer;
          }else{
            bufferToCheck = RXBufferCurrentPosition;
          }

          // Verify all tables
          errorID = verifyTableData(details.descriptorID, bufferToCheck, details.size);

          // If the validation failed, report it
          if(errorID != 0){
            RPAGE = oldRamPage; // Restore the original RAM page, even when getting an error condition.
            break;
          }
        }

        // Copy from the RX buffer to the block of RAM
        memcpy((uint8_t*)(details.RAMAddress + offset), RXBufferCurrentPosition, size);

        // Check that the write was successful
        uint8_t index = compare(RXBufferCurrentPosition, (uint8_t*)(details.RAMAddress + offset), size);

        // Restore the original RAM and flash pages
        RPAGE = oldRamPage;

        if(index != 0){
          errorID = MEMORY_WRITE_ERROR;
        }
        break;
      }
    case UPDATE_BLOCK_IN_FLASH:
      {
        // Subtract six to allow for the locationID, size, offset
        if(RXCalculatedPayloadLength < 7){
          errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
          break;
        }

        // Extract the RAM location ID
        uint16_t locationID = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the offset to place the data at
        uint16_t offset = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the size of the data to be stored
        uint16_t size = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Look up the memory location details
        blockDetails details;
        lookupBlockDetails(locationID, &details);

        // Subtract six to allow for the locationID, size, offset
        if((RXCalculatedPayloadLength - 6) != size){
          errorID = PAYLOAD_NOT_EQUAL_TO_SPECIFIED_VALUE;
          break;
        }

        // If either of these is zero then this block is not in flash!
        if((details.FlashPage == 0) || (details.FlashAddress == 0)){
          errorID = INVALID_MEMORY_ACTION_FOR_ID;
          break;
        }

        // Check that size and offset describe a region that is not out of bounds
        if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
          errorID = INVALID_SIZE_OFFSET_COMBINATION;
          break;
        }

        // Don't allow sub region manipulation where it does not make sense or is unsafe.
        if((size != details.size) && !(details.flags & BLOCK_IS_INDEXABLE)){
          errorID = UNCHECKED_TABLE_MANIPULATION_NOT_ALLOWED;
          break;
        }

        /// TODO @todo factor this out into validation delegation function once the number of types increases somewhat
        //
        if((details.flags & BLOCK_IS_MAIN_TABLE) || (details.flags & BLOCK_IS_2DUS_TABLE)){
          void* bufferToCheck;

          // For sub regions, construct an image for verification
          if(size != details.size){
            /* Save page value for restore and set the visible page */
            uint8_t oldFlashPage = PPAGE;
            PPAGE = details.FlashPage;

            // Copy data from destination location to buffer
            memcpy(leftOverBuffer, details.FlashAddress, details.size);

            /* Restore the original flash page */
            PPAGE = oldFlashPage;

            // Copy data from rx buffer to buffer over writing old data
            memcpy(leftOverBuffer + offset, RXBufferCurrentPosition, size);

            bufferToCheck = leftOverBuffer;
          }else{
            bufferToCheck = RXBufferCurrentPosition;
          }

          // Verify all tables
          errorID = verifyTableData(details.descriptorID, bufferToCheck, details.size);
        }

        /* Copy the flash details and populate the RAM details with the buffer location */
        blockDetails burnDetails;
        burnDetails.FlashPage = details.FlashPage;
        burnDetails.FlashAddress = details.FlashAddress + offset;
        burnDetails.RAMPage = RPAGE;
        burnDetails.RAMAddress = RXBufferCurrentPosition;
        burnDetails.size = size;

        /* Copy from the RX buffer to the block of flash */
        errorID = writeBlock(&burnDetails, leftOverBuffer);
        if(errorID != 0){
          break;
        }

        /* If present in RAM, update that too */
        if((details.RAMPage != 0) && (details.RAMAddress != 0)){
          /* Save page values for restore */
          uint8_t oldRamPage = RPAGE;
          /* Set the viewable RAM page */
          RPAGE = details.RAMPage;

          /* Copy from the RX buffer to the block of RAM */
          memcpy((uint8_t*)(details.RAMAddress + offset), RXBufferCurrentPosition, size);

          /* Check that the write was successful */
          uint8_t index = compare(RXBufferCurrentPosition, (uint8_t*)(details.RAMAddress + offset), size);

          /* Restore the original RAM and flash pages */
          RPAGE = oldRamPage;

          if(index != 0){
            errorID = MEMORY_WRITE_ERROR;
          }
        }

        break;
      }
    case RETRIEVE_BLOCK_FROM_RAM:
      {
        if(RXCalculatedPayloadLength != 6){
          errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
          break;
        }

        // Extract the RAM location ID
        uint16_t locationID = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the offset to place the data at
        uint16_t offset = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the size of the data to be stored
        uint16_t size = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        /* Look up the memory location details */
        blockDetails details;
        lookupBlockDetails(locationID, &details);

        if((details.RAMPage == 0) || (details.RAMAddress == 0)){
          errorID = INVALID_MEMORY_ACTION_FOR_ID;
          break;
        }

        // Special behaviour for size of zero which returns the whole block
        if((size == 0) && (offset == 0)){
          size = details.size;
        }

        // Check that size and offset describe a region that is not out of bounds
        if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
          errorID = INVALID_SIZE_OFFSET_COMBINATION;
          break;
        }

        // Don't allow sub region retrieval where it does not make sense or is unsafe. (keep it symmetric for djandruczyk)
        if((size != details.size) && !(details.flags & BLOCK_IS_INDEXABLE)){
          errorID = DOES_NOT_MAKE_SENSE_TO_RETRIEVE_PARTIALLY;
          break;
        }

        // This type must have a length field, set that up
        *((uint16_t*)TXBufferCurrentPositionHandler) = size;
        *TXHeaderFlags |= HEADER_HAS_LENGTH;
        TXBufferCurrentPositionHandler += 2;

        /* Save page value for restore and set the visible page */
        uint8_t oldRamPage = RPAGE;
        RPAGE = details.RAMPage;

        /* Copy the block of RAM to the TX buffer */
        memcpy(TXBufferCurrentPositionHandler, (uint8_t*)(details.RAMAddress + offset), size);
        TXBufferCurrentPositionHandler += size;

        /* Restore the original RAM and flash pages */
        RPAGE = oldRamPage;

        break;
      }
    case RETRIEVE_BLOCK_FROM_FLASH:
      {
        if(RXCalculatedPayloadLength != 6){
          errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
          break;
        }

        // Extract the RAM location ID
        uint16_t locationID = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the offset to place the data at
        uint16_t offset = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the size of the data to be stored
        uint16_t size = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        /* Look up the memory location details */
        blockDetails details;
        lookupBlockDetails(locationID, &details);

        if((details.FlashPage == 0) || (details.FlashAddress == 0)){
          errorID = INVALID_MEMORY_ACTION_FOR_ID;
          break;
        }

        // Special behaviour for size of zero which returns the whole block
        if((size == 0) && (offset == 0)){
          size = details.size;
        }

        // Check that size and offset describe a region that is not out of bounds
        if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
          errorID = INVALID_SIZE_OFFSET_COMBINATION;
          break;
        }

        // Don't allow sub region retrieval where it does not make sense or is unsafe. (keep it symmetric for djandruczyk)
        if((size != details.size) && !(details.flags & BLOCK_IS_INDEXABLE)){
          errorID = DOES_NOT_MAKE_SENSE_TO_RETRIEVE_PARTIALLY;
          break;
        }

        // This type must have a length field, set that up
        *((uint16_t*)TXBufferCurrentPositionHandler) = size;
        *TXHeaderFlags |= HEADER_HAS_LENGTH;
        TXBufferCurrentPositionHandler += 2;

        /* Save page value for restore and set the visible page */
        uint8_t oldFlashPage = PPAGE;
        PPAGE = details.FlashPage;

        /* Copy the block of flash to the TX buffer */
        memcpy(TXBufferCurrentPositionHandler, (uint8_t*)(details.FlashAddress + offset), size);
        TXBufferCurrentPositionHandler += size;

        /* Restore the original RAM and flash pages */
        PPAGE = oldFlashPage;

        break;
      }
    case BURN_BLOCK_FROM_RAM_TO_FLASH:
      {
        if(RXCalculatedPayloadLength != 6){
          errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
          break;
        }

        // Extract the RAM location ID
        uint16_t locationID = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the offset to place the data at
        uint16_t offset = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // Extract the size of the data to be stored
        uint16_t size = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        /* Look up the memory location details */
        blockDetails details;
        lookupBlockDetails(locationID, &details);

        /* Check that all data we need is present */
        if((details.RAMPage == 0) || (details.RAMAddress == 0) || (details.FlashPage == 0) || (details.FlashAddress == 0)){
          errorID = INVALID_MEMORY_ACTION_FOR_ID;
          break;
        }

        // Special behaviour for size of zero which burns the whole block
        if((size == 0) && (offset == 0)){
          size = details.size;
        }

        // Check that size and offset describe a region that is not out of bounds
        if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
          errorID = INVALID_SIZE_OFFSET_COMBINATION;
          break;
        }

        // Don't allow sub region retrieval where it does not make sense or is unsafe. (keep it symmetric for djandruczyk)
        if((size != details.size) && !(details.flags & BLOCK_IS_INDEXABLE)){
          errorID = DOES_NOT_MAKE_SENSE_TO_RETRIEVE_PARTIALLY;
          break;
        }


        // adjust details block to feed to represent the subsection of ram and flash that we want to burn down.
        details.RAMAddress += offset;
        details.FlashAddress += offset;
        details.size = size;

        /* Write the block down from RAM to Flash */
        errorID = writeBlock(&details, leftOverBuffer);
        break;
      }
    case REQUEST_DATALOG_PACKET: // Set type through standard configuration methods
      if(RXCalculatedPayloadLength != 0){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }

      /* Set the length field up */
      *TXHeaderFlags |= HEADER_HAS_LENGTH;
      uint16_t* localLength = (uint16_t*)TXBufferCurrentPositionHandler;
      TXBufferCurrentPositionHandler += 2;

      /* Fill out the log and send */
      *localLength = populateBasicDatalog();
      break;
    case SET_ASYNC_DATALOG_TYPE:
      if(RXCalculatedPayloadLength != 1){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }

      uint8_t newDatalogType = *((uint8_t*)RXBufferCurrentPosition);
      if(newDatalogType > ASYNCDATALOGLASTTYPE){
        errorID = NO_SUCH_ASYNC_DATALOG_TYPE;
        break;
      }

      TablesB.SmallTablesB.loggingSettings.datalogStreamType = newDatalogType;
      break;
    case RETRIEVE_ARBITRARY_MEMORY:
      if(RXCalculatedPayloadLength != 6){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }

      uint16_t length = *((uint16_t*)RXBufferCurrentPosition);
      RXBufferCurrentPosition += 2;
      // Make sure the buffer can handle the block
      if(length > TX_MAX_PAYLOAD_SIZE){
        errorID = REQUESTED_LENGTH_TOO_LARGE;
        break;
      }

      void* address = (void*) *((uint16_t*)RXBufferCurrentPosition);
      RXBufferCurrentPosition += 2;
      // Ensure we don't try to read past the end of the address space
      if(((uint16_t)address) <= ((0xFFFF - length) + 1)){
        // TODO Possibly check and limit ranges
        errorID = REQUESTED_ADDRESS_DISALLOWED;
        break;
      }

      uint8_t RAMPage = *((uint8_t*)RXBufferCurrentPosition);
      RXBufferCurrentPosition++;
      // Ensure RAM page is valid. Being too high is not possible.
      if(RAMPage < RPAGE_MIN){
        errorID = REQUESTED_RAM_PAGE_INVALID;
        break;
      }

      uint8_t FlashPage = *((uint8_t*)RXBufferCurrentPosition);
      RXBufferCurrentPosition++;
      // Ensure Flash page is valid. Being too high is not possible.
      if(FlashPage < PPAGE_MIN){
        errorID = REQUESTED_FLASH_PAGE_INVALID;
        break;
      }

      /* This type must have a length field, set that up */
      *((uint16_t*)TXBufferCurrentPositionHandler) = length + 6;
      *TXHeaderFlags |= HEADER_HAS_LENGTH;
      TXBufferCurrentPositionHandler += 2;

      /* Put the request payload into the reply */
      *((uint16_t*)TXBufferCurrentPositionHandler) = (uint16_t) address;
      TXBufferCurrentPositionHandler += 2;
      *((uint16_t*)TXBufferCurrentPositionHandler) = length;
      TXBufferCurrentPositionHandler += 2;
      *((uint8_t*)TXBufferCurrentPositionHandler) = RAMPage;
      TXBufferCurrentPositionHandler++;
      *((uint8_t*)TXBufferCurrentPositionHandler) = FlashPage;
      TXBufferCurrentPositionHandler++;

      /* Load the body into place */
      memcpy((void*)TXBufferCurrentPositionHandler, address, length);
      TXBufferCurrentPositionHandler += length;

      break;
    case RETRIEVE_LIST_OF_LOCATION_IDS:
      {
        if(RXCalculatedPayloadLength != 3){
          errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
          break;
        }

        // Extract the type of list that we want
        uint8_t listType = *((uint8_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition++;

        // Extract the mask for the qualities that we want
        uint16_t blockDetailsMask = *((uint16_t*)RXBufferCurrentPosition);
        RXBufferCurrentPosition += 2;

        // This type must have a length field, set that up
        uint16_t * listLength = (uint16_t*)TXBufferCurrentPositionHandler;
        *TXHeaderFlags |= HEADER_HAS_LENGTH;
        TXBufferCurrentPositionHandler += 2;

        // Zero the counter before we start, woops!
        *listLength = 0;

        uint32_t locationID;
        blockDetails details;
        for(locationID = 0;locationID < 65536;locationID++){
          uint16_t locationIDDoesntExist;
          locationIDDoesntExist = lookupBlockDetails((uint16_t)locationID, &details);

          if(!locationIDDoesntExist){
            if((listType == 0x00) || // get all
                ((listType == 0x01) && (details.flags & blockDetailsMask)) || // get OR of bits
                ((listType == 0x02) && (!(~(details.flags) & blockDetailsMask)))){ // get AND of bits
              *((uint16_t*)TXBufferCurrentPositionHandler) = (uint16_t)locationID;
              TXBufferCurrentPositionHandler += 2;
              *listLength += 2;
            }
          }
        }

        break;
      }
    case RETRIEVE_LOCATION_ID_DETAILS:
      if(RXCalculatedPayloadLength != 2){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }

      // Extract the RAM location ID
      uint16_t locationID = *((uint16_t*)RXBufferCurrentPosition);
      RXBufferCurrentPosition += 2;

      // This type must have a length field, set that up
      *((uint16_t*)TXBufferCurrentPositionHandler) = sizeof(blockDetails);
      *TXHeaderFlags |= HEADER_HAS_LENGTH;
      TXBufferCurrentPositionHandler += 2;

      // Write straight to output buffer to save time/code
      errorID = lookupBlockDetails(locationID, (blockDetails*)TXBufferCurrentPositionHandler);

      if(errorID != 0){
        break;
      }

      // Adjust TX buffer position if successful
      TXBufferCurrentPositionHandler += sizeof(blockDetails);

      break;
    case REQUEST_UNIT_TEST_OVER_SERIAL:
      /*
       * The idea here is to call this function with arguments, and data
       * and have the result sent back for comparison with an expected
       * result that isn't divulged to the firmware.
       *
       * It is intended that all testable functions be callable through
       * this mechanism and that any number of test executions can be
       * performed by an external suite using different parameters and
       * data sets and matching expected results.
       *
       * The usual error mechanism shall be used to indicate some sort of
       * either internal or test failure and returned errors shall be
       * suitably descriptive to allow diagnosis and fixing of issues.
       */

      // Must at least have test ID
      if(RXCalculatedPayloadLength < 2){
        errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
        break;
      }

      // grab unit test ID from payload
      uint16_t unitTestID = *((uint16_t*)RXBufferCurrentPosition);
      RXBufferCurrentPosition += 2;

      switch(unitTestID){
        case TESTEMPTYTEST:
          // Must be only the ID
          if(RXCalculatedPayloadLength != 2){
            errorID = PAYLOAD_SHORTER_THAN_REQUIRED_FOR_TEST;
            break;
          }

          *((uint16_t*)TXBufferCurrentPositionHandler) = unitTestID;
          TXBufferCurrentPositionHandler +=2;

          break;
        // http://issues.freeems.org/view.php?id=156
        //
        /// TODO @todo test all things listed below:
        // lookupPagedMainTableCellValue - pass this RPAGE so that it remains unchanged
        // validateMainTable
        // validateTwoDTable
        // set table values - leave this till last, currently unused by mtx, likely to be removed anyway
        // generateDerivedVars - convert to pointers, remove headers, privatise a lot of data!
        // calculateFuelAndIgnition - ditto
        // scheduling algorithm - ditto
        // safeAdd
        // safeTrim
        // safeScale
        // sleep (milliseconds)
        // sleepMicro (microseconds)
        // checksum
        // stringCopy
        // compare
        // utils that can't be checked: sampleLoopADC sampleBlockADC sampleEachADC - can check for how long each takes! adjustPWM (test only anyway), resetToNonRunningState and setupPagedRAM (would interfere with functioning of device)
        // init code may be able to be partially checked
        // most other code at this stage is ISR code, flash writing code, or could interfere with the running of the engine
        // more testable code will appear with time, such as the HAL layer, and most accessory functions.
        default:
          errorID = NO_SUCH_UNIT_TEST_ID;

      // each case:
        // checks length, fails if wrong
        // parses data into args
        // calls function on data/args
        // assembles response OR sets error
        // breaks
      }
      break;
    case START_BENCH_TEST_SEQUENCE:
      errorID = LEGACY_BENCH_TESTS_DEPRECATED;
      break;
        /* THIS CODE IS DEPRECATED AND MARKED FOR REMOVAL *
         *
      // see TODO on include at top and modify this line appropriately
      if(!(compare((uint8_t*)&decoderName, (uint8_t*)BENCH_TEST_NAME, sizeof(BENCH_TEST_NAME)))){
        if(RXCalculatedPayloadLength < 1){
          errorID = PAYLOAD_LENGTH_TYPE_MISMATCH;
          break;
        }

        uint8_t localTestMode = *((uint8_t*)RXBufferCurrentPosition); //1; // The only mode, for now.
        RXBufferCurrentPosition++;
        if(localTestMode > TEST_MODE_BUMP_UP_CYCLES){
          errorID = UNIMPLEMENTED_TEST_MODE;
          break;
        }else if((localTestMode == TEST_MODE_STOP) && (RXCalculatedPayloadLength == 1)){
          if(!(coreStatusA & BENCH_TEST_ON)){
            errorID = BENCH_TEST_NOT_RUNNING_TO_STOP;
            break;
          }

          // Ensure we succeed at stopping it as quickly as possible.
          ATOMIC_START();
          KeyUserDebugs.currentEvent = testEventsPerCycle - 1; // Gets incremented then compared with testEventsPerCycle
          testNumberOfCycles = 1;                              // Gets decremented then compared with zero
          ATOMIC_END();

          // eventually save and return where it got to
          break;
        }else if((localTestMode == TEST_MODE_BUMP_UP_CYCLES) && (RXCalculatedPayloadLength == 2)){
          if(!(coreStatusA & BENCH_TEST_ON)){
            errorID = BENCH_TEST_NOT_RUNNING_TO_BUMP;
            break;
          }

          // Get bump value from payload
          uint8_t bumpCycles = *((uint8_t*)RXBufferCurrentPosition); //1; // The only mode, for now.
          RXBufferCurrentPosition++;

          if(bumpCycles == 0){
            errorID = BUMPING_BY_ZERO_MAKES_NO_SENSE;
            break;
          }

          // Bump count by value from payload
          testNumberOfCycles += bumpCycles;
          // Given that this function is only for situations when A it's getting near to
          // zero and B the user is watching, not checking for overflow is reasonable.
          break;
        }else if((localTestMode == TEST_MODE_ITERATIONS) && (RXCalculatedPayloadLength == 24)){
          testMode = localTestMode;
          // do nothing to fall through, or move other code into here
        }else{
          errorID = PACKET_SIZE_WRONG_FOR_TEST_MODE;
          break;
        }

        if(coreStatusA & BENCH_TEST_ON){
          errorID = BENCH_TEST_ALREADY_RUNNING;
          break;
        }

        testEventsPerCycle = *((uint8_t*)RXBufferCurrentPosition); //100;  // @ 10ms  =  1s
        RXBufferCurrentPosition++;
        if(testEventsPerCycle == 0){
          errorID = INVALID_EVENTS_PER_CYCLE;
          break;
        }

        testNumberOfCycles = *((uint16_t*)RXBufferCurrentPosition); //20;   // @ 1s    = 20s
        RXBufferCurrentPosition += 2;
        if(testNumberOfCycles == 0){
          errorID = INVALID_NUMBER_OF_CYCLES;
          break;
        }

        testTicksPerEvent = *((uint16_t*)RXBufferCurrentPosition); //12500; // @ 0.8us = 10ms
        RXBufferCurrentPosition += 2;
        if(testTicksPerEvent < decoderMaxCodeTime){
          errorID = TOO_SHORT_OF_AN_EVENT_PERIOD;
          break;
        }

        // Pluck the arrays out of the packet for the loop below
        uint8_t* testEventNumbers = RXBufferCurrentPosition;
        RXBufferCurrentPosition += 6;
        uint16_t* testPulseWidths = (uint16_t*)RXBufferCurrentPosition;
        RXBufferCurrentPosition += 12;

        // Reset the clock for reading timeout
        Clocks.timeoutADCreadingClock = 0; // make this optional, such that we can use real inputs to determine pw and/or dwell.

        // Validate and transfer the per-channel data
        uint8_t channel;
        uint8_t configuredChannels = 6;
        for(channel = 0;channel < 6;channel++){
          if(testPulseWidths[channel] > injectorSwitchOnCodeTime){ // See next block for warning.
            // use as-is
            outputEventDelayFinalPeriod[channel] = decoderMaxCodeTime;
            outputEventPulseWidthsMath[channel] = testPulseWidths[channel];
            outputEventInputEventNumbers[channel] = testEventNumbers[channel];
          }else if(testPulseWidths[channel] > 3){
            // less than the code time, and not special, error!
            errorID = TOO_SHORT_OF_A_PULSE_WIDTH_TO_TEST;
            // Warning, PWs close to this could be slightly longer than requested, that will change in later revisions.
            break;
          }else if(testPulseWidths[channel] == 3){
            testMode++; // Dirty hack to avoid dealing with Dave for the time being.
            testNumberOfMissing = channel;
          }else if(testPulseWidths[channel] == 2){
            // use the dwell from the core maths and input vars.
            outputEventDelayFinalPeriod[channel] = decoderMaxCodeTime;
            outputEventPulseWidthsMath[channel] = DerivedVars->Dwell;
            outputEventInputEventNumbers[channel] = testEventNumbers[channel];
          }else if(testPulseWidths[channel] == 1){
            // use the reference pulse width from the core maths and input vars.
            outputEventDelayFinalPeriod[channel] = decoderMaxCodeTime;
            outputEventPulseWidthsMath[channel] = DerivedVars->RefPW;
            outputEventInputEventNumbers[channel] = testEventNumbers[channel];
          }else{ // is zero
            // Set this channel to zero for and therefore off, don't set this channel.
            outputEventInputEventNumbers[channel] = 0xFF; // Off.
            configuredChannels--;
          }
        }

        if(configuredChannels == 0){
          errorID = NO_CHANNELS_CONFIGURED_TO_TEST;
          break;
        }

        if(errorID == 0){
          // Let the first iteration roll it over to zero.
          KeyUserDebugs.currentEvent = 0xFF; // Needs to be here in case of multiple runs, init is not sufficient

          if(testMode == TEST_MODE_DODGY_MISSING_TOOTH){
            if(testEventsPerCycle <= 127){
              testEventsPerCycle *= 2;
            }else{
              errorID = TOO_MANY_EVENTS_PER_CYCLE_MISSING_TTH;
              break;
            }

            // Store the time per event in RPM such that it can be updated dynamically
            CoreVars->RPM = testTicksPerEvent;

            // The channels to use rely on the defaults from initialisers! Custom builds can break BenchTest mode!

            // Un-schedule anything that got scheduled
            outputEventInputEventNumbers[2] = 0xFF;
            outputEventInputEventNumbers[3] = 0xFF;
            outputEventInputEventNumbers[4] = 0xFF;
            outputEventInputEventNumbers[5] = 0xFF;
          }else if(testMode > TEST_MODE_DODGY_MISSING_TOOTH){
            errorID = UNIMPLEMENTED_TEST_MODE;
            break;
          }

          // Trigger decoder interrupt to fire thus starting the loop!
          TIE = 0x01; // The ISR does the rest!

          // Nothing went wrong, now set flag.
          coreStatusA |= BENCH_TEST_ON;
        }else{
          break;
        }


* http://issues.freeems.org/view.php?id=155
 *
 * The following block has been left in, as I still do not know why it won't work as intended:
 *
 * - It should fire all 6 output pins with a 52ms duration pulse, exactly once.
 * - The SAME code run from anywhere else (pre main loop, in main loop, in rtc, in decoder) works fine, just not here in commsCore.c
 * - The interrupts run, but the pin doesn't change state, despite the registers being configured correctly
 *
 * I've tried quite a bit:
 *
 * - Moving this code around
 * - Checking memory definitions
 * - Completely rewriting the output ISR
 * - Adding significant debug to output ISR
 * - Checking for register contents in output ISR
 * - Checking for key things modified in this file
 * - General head scratching and confused searching
 *

//        outputEventPinNumbers[0] = 0; // 1 ign
//        outputEventPinNumbers[1] = 1; // 2 ign
//        outputEventPinNumbers[2] = 2; // 3 ign/1 fuel
//        outputEventPinNumbers[3] = 3; // 4 ign/2 fuel
//        outputEventPinNumbers[4] = 4; // 3 fuel
//        outputEventPinNumbers[5] = 5; // 4 fuel
//        outputEventDelayFinalPeriod[0] = decoderMaxCodeTime;
//        outputEventDelayFinalPeriod[1] = decoderMaxCodeTime;
//        outputEventDelayFinalPeriod[2] = decoderMaxCodeTime;
//        outputEventDelayFinalPeriod[3] = decoderMaxCodeTime;
//        outputEventDelayFinalPeriod[4] = decoderMaxCodeTime;
//        outputEventDelayFinalPeriod[5] = decoderMaxCodeTime;
//        outputEventPulseWidthsMath[0] = SHORTMAX;
//        outputEventPulseWidthsMath[1] = SHORTMAX;
//        outputEventPulseWidthsMath[2] = SHORTMAX;
//        outputEventPulseWidthsMath[3] = SHORTMAX;
//        outputEventPulseWidthsMath[4] = SHORTMAX;
//        outputEventPulseWidthsMath[5] = SHORTMAX;
//
//        uint16_t edgeTimeStamp = TCNT;
//        // call sched output with args
//        LongTime timeStamp;
//        // Install the low word 
//        timeStamp.timeShorts[1] = edgeTimeStamp;
//        // Find out what our timer value means and put it in the high word 
//        if(TFLG2 && !(edgeTimeStamp & 0x8000)){ // see 10.3.5 paragraph 4 of 68hc11 ref manual for details 
//          timeStamp.timeShorts[0] = timerExtensionClock + 1;
//        }else{
//          timeStamp.timeShorts[0] = timerExtensionClock;
//        }
//
//        schedulePortTPin(0, timeStamp);
//        schedulePortTPin(1, timeStamp);
//        schedulePortTPin(2, timeStamp);
//        schedulePortTPin(3, timeStamp);
//        schedulePortTPin(4, timeStamp);
//        schedulePortTPin(5, timeStamp);
//
//        sleep(1000);
      }else{
        errorID = THIS_IS_NOT_THE_BENCH_TEST_DECODER;
      }
      break;
    }
        * THIS ABOVE CODE IS DEPRECATED AND MARKED FOR REMOVAL */
    default:
      if((RXHeaderPayloadID % 2) == 1){
        errorID = INVALID_PAYLOAD_ID;
      }else{
        errorID = UNRECOGNISED_PAYLOAD_ID;
      }
      break;
  }

  // Always reply, if errorID is zero it's just an ack.
  finaliseAndSend(errorID);

  /* Switch reception back on now that we are done with the received data */
  resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
}

void sendDataStreamDescriptor() {

  uint8_t* currentTXBufferPosition = TXBufferCurrentPositionHandler + 3; //FIXME create macro for the 2 +1
  uint8_t* lastTXBufferPosition;
  uint8_t numChunks = TablesB.SmallTablesB.loggingSettings.numberOfChunks;
  const dataBlockDescriptor* descriptorPTR;
  uint8_t full = 0;
  descriptorPages pages;

  if ((currentChunk == 0) && (currentDescription == 0)) {
    /* Add JSON header */
    currentTXBufferPosition = addJSONHeader(DATALOG, currentTXBufferPosition);
    packetPayloadEnum = 0;
  }
  lastTXBufferPosition = currentTXBufferPosition;
  //TODO fix first log chunk index as it is not guaranteed to be zero
  /* Pick up where we left off */
  while (currentChunk < numChunks) {
    //TODO if current descriptor = 0 maybe add another sub ID/name
    descriptorPTR = &(TablesB.SmallTablesB.loggingSettings.logChunks[currentChunk].descriptor[currentDescription]);
    pages = TablesB.SmallTablesB.loggingSettings.logChunks[currentChunk].pages;
    while (currentDescription < *(TablesB.SmallTablesB.loggingSettings.logChunks[currentChunk].numDescriptions)) {
      currentTXBufferPosition = addJSONdataLogRecord(currentTXBufferPosition, descriptorPTR, baseOffset, pages);
      if ((currentChunk != (numChunks - 1) || (currentDescription != (*(TablesB.SmallTablesB.loggingSettings.logChunks[currentChunk].numDescriptions) - 1)))) {
        currentTXBufferPosition = payloadStrCat(currentTXBufferPosition, ",");
      }
      if (currentTXBufferPosition) {
        ++currentDescription;
        ++descriptorPTR;
        lastTXBufferPosition = currentTXBufferPosition;
      } else {
        full = 1;
        break;
      }
    }
    if (full) {
      break;
    } else {
      currentDescription = 0;
    }
    baseOffset += TablesB.SmallTablesB.loggingSettings.logChunks[currentChunk].size;
    ++currentChunk;
  }
  /* If we aren't full yet, try to append footer, if we can't 
   * set full flag so we catch it on the next iteration around
   */
  if (!full)
  {
    currentTXBufferPosition = addJSONFooter(currentTXBufferPosition);
    if (currentTXBufferPosition) {
      lastTXBufferPosition = currentTXBufferPosition;
    } else {
      full = 1;
    }
  }
  /* once everything is sent reset our indexes */
  if (!full) {
    currentChunk = 0;
    currentDescription = 0;
    baseOffset = 0;
    commsCoreStateFlags &= ~(PROCESSING_MULTI_PACKET_PAYLOAD);
    RXHeaderPayloadIDInProcess = 0;
    *TXHeaderFlags |= HEADER_IS_COMPLETE;
  } else {
    *TXHeaderFlags |= HEADER_IS_PARTIAL;
    commsCoreStateFlags |= PROCESSING_MULTI_PACKET_PAYLOAD;
    RXHeaderPayloadIDInProcess = RXHeaderPayloadID;
  }
  /* write length into packet */
  *((uint16_t*) TXBufferCurrentPositionHandler) = lastTXBufferPosition - TXBufferCurrentPositionHandler;
  /* write payload number into packet */
  *(TXBufferCurrentPositionHandler + 2) = packetPayloadEnum;
  /* fast forward buffer to end */
  TXBufferCurrentPositionHandler = lastTXBufferPosition;
  /* This type must have a length field, set that up and load the body into place at the same time */
  *TXHeaderFlags |= HEADER_HAS_LENGTH;
  ++packetPayloadEnum;
}


void sendFieldDescriptor() {

  uint8_t* currentTXBufferPosition = TXBufferCurrentPositionHandler + 3; //FIXME create macro for the 2 +1
  uint8_t* lastTXBufferPosition;
  static const FieldDescriptor *descriptorPTR = fieldDescriptor;
  uint8_t full = 0;

  if (currentDescription == 0) {
    /* Add JSON header */
    currentTXBufferPosition = addJSONHeader(FIELD_DESCRIPTOR, currentTXBufferPosition);
    packetPayloadEnum = 0;
    descriptorPTR = fieldDescriptor;
  }

  lastTXBufferPosition = currentTXBufferPosition;
  //TODO fix first log chunk index as it is not guaranteed to be zero
  /* Pick up where we left off */
  while (currentDescription < fieldDescriptorCnt) {
    currentTXBufferPosition = addJSONfieldDescriptor(currentTXBufferPosition, descriptorPTR);
    if (currentDescription != (fieldDescriptorCnt - 1)) {
      currentTXBufferPosition = payloadStrCat(currentTXBufferPosition, ",");
    }
    if (currentTXBufferPosition) {
      ++currentDescription;
      ++descriptorPTR;
      lastTXBufferPosition = currentTXBufferPosition;
    } else {
      full = 1;
      break;
    }
  }

  if (full) {
    //break;
  } else {
    currentDescription = 0;
  }
  ++currentChunk;

  /* If we aren't full yet, try to append footer, if we can't
   * set full flag so we catch it on the next iteration around
   */
  if (!full)
  {
    currentTXBufferPosition = addJSONFooter(currentTXBufferPosition);
    if (currentTXBufferPosition) {
      lastTXBufferPosition = currentTXBufferPosition;
    } else {
      full = 1;
    }
  }

  /* once everything is sent reset our indexes */
  if (!full) {
    currentChunk = 0;
    currentDescription = 0;
    baseOffset = 0;
    commsCoreStateFlags &= ~(PROCESSING_MULTI_PACKET_PAYLOAD);
    RXHeaderPayloadIDInProcess = 0;
    *TXHeaderFlags |= HEADER_IS_COMPLETE;
  } else {
    *TXHeaderFlags |= HEADER_IS_PARTIAL;
    commsCoreStateFlags |= PROCESSING_MULTI_PACKET_PAYLOAD;
    RXHeaderPayloadIDInProcess = RXHeaderPayloadID;
  }
  /* write length into packet */
  *((uint16_t*) TXBufferCurrentPositionHandler) = lastTXBufferPosition - TXBufferCurrentPositionHandler;
  /* write payload number into packet */
  *(TXBufferCurrentPositionHandler + 2) = packetPayloadEnum;
  /* fast forward buffer to end */
  TXBufferCurrentPositionHandler = lastTXBufferPosition;
  /* This type must have a length field, set that up and load the body into place at the same time */
  *TXHeaderFlags |= HEADER_HAS_LENGTH;
  ++packetPayloadEnum;
}

/* Here we prepare for sending a TX packet. This is more or less just temp code before
 * we can rewrite the whole lot. This does enable us to send multi-packet payloads, but
 * not in a generic way just yet.  */

void prepForTX(){
  /* Rewind all pointers to start of buffer */
  TXBufferCurrentPositionHandler = (uint8_t*)&TXBuffer;
  TXBufferCurrentPositionSCI0 = (uint8_t*)&TXBuffer;
  TXBufferCurrentPositionCAN0 = (uint8_t*)&TXBuffer;

  /* Flag that we are transmitting! */
  TXBufferInUseFlags |= COM_SET_SCI0_INTERFACE_ID;
  // SCI0 only for now...

  /* Load a blank header into the TX buffer ready for masking */
  TXHeaderFlags = TXBufferCurrentPositionHandler;
  *TXHeaderFlags = 0;
  TXBufferCurrentPositionHandler++;
  *((uint16_t*)TXBufferCurrentPositionHandler) = RXHeaderPayloadID + 1;
  TXBufferCurrentPositionHandler += 2;
}

void sendTableDescriptor() {

  uint8_t* currentTXBufferPosition = TXBufferCurrentPositionHandler + 3; //FIXME create macro for the 2 +1
  uint8_t* lastTXBufferPosition;
  static const TableDescriptor *descriptorPTR = tableDescriptor;
  uint8_t full = 0;

  if (currentDescription == 0) {
    /* Add JSON header */
    currentTXBufferPosition = addJSONHeader(TABLE_DESCRIPTOR, currentTXBufferPosition);
    packetPayloadEnum = 0;
    descriptorPTR = tableDescriptor;
  }

  lastTXBufferPosition = currentTXBufferPosition;
  //TODO fix first log chunk index as it is not guaranteed to be zero
  /* Pick up where we left off */
  while (currentDescription < tableDescriptorCnt) {
    currentTXBufferPosition = addJSONtableDescriptor(currentTXBufferPosition, descriptorPTR);
    if (currentDescription != (tableDescriptorCnt - 1)) {
      currentTXBufferPosition = payloadStrCat(currentTXBufferPosition, ",");
    }
    if (currentTXBufferPosition) {
      ++currentDescription;
      ++descriptorPTR;
      lastTXBufferPosition = currentTXBufferPosition;
    } else {
      full = 1;
      break;
    }
  }

  if (full) {
    //break;
  } else {
    currentDescription = 0;
  }
  ++currentChunk;

  /* If we aren't full yet, try to append footer, if we can't
   * set full flag so we catch it on the next iteration around
   */
  if (!full)
  {
    currentTXBufferPosition = addJSONFooter(currentTXBufferPosition);
    if (currentTXBufferPosition) {
      lastTXBufferPosition = currentTXBufferPosition;
    } else {
      full = 1;
    }
  }

  /* once everything is sent reset our indexes */
  if (!full) {
    currentChunk = 0;
    currentDescription = 0;
    baseOffset = 0;
    commsCoreStateFlags &= ~(PROCESSING_MULTI_PACKET_PAYLOAD);
    RXHeaderPayloadIDInProcess = 0;
    *TXHeaderFlags |= HEADER_IS_COMPLETE;
  } else {
    *TXHeaderFlags |= HEADER_IS_PARTIAL;
    commsCoreStateFlags |= PROCESSING_MULTI_PACKET_PAYLOAD;
    RXHeaderPayloadIDInProcess = RXHeaderPayloadID;
  }
  /* write length into packet */
  *((uint16_t*) TXBufferCurrentPositionHandler) = lastTXBufferPosition - TXBufferCurrentPositionHandler;
  /* write payload number into packet */
  *(TXBufferCurrentPositionHandler + 2) = packetPayloadEnum;
  /* fast forward buffer to end */
  TXBufferCurrentPositionHandler = lastTXBufferPosition;
  /* This type must have a length field, set that up and load the body into place at the same time */
  *TXHeaderFlags |= HEADER_HAS_LENGTH;
  ++packetPayloadEnum;
}

void prep_packet_with_length_ptr(uint16_t payload_id, uint16_t **localLength)
{
  extern uint8_t* TXBufferCurrentPositionCAN0;
  extern uint8_t* TXBufferCurrentPositionSCI0;

  /* Flag that we are transmitting! */
  TXBufferInUseFlags |= COM_SET_SCI0_INTERFACE_ID;
  TXBufferCurrentPositionHandler = (uint8_t*)&TXBuffer;
  /* Initialised here such that override is possible */
  TXBufferCurrentPositionSCI0 = (uint8_t*)&TXBuffer;
  TXBufferCurrentPositionCAN0 = (uint8_t*)&TXBuffer;
  /* Set the flags : firmware, no ack, no addrs, has length */
  *TXBufferCurrentPositionHandler = HEADER_HAS_LENGTH;
  TXBufferCurrentPositionHandler++;
  /* Set the payload ID */
  *((uint16_t*)TXBufferCurrentPositionHandler) = payload_id;
  TXBufferCurrentPositionHandler += 2;
  /* Set the length */
  *localLength = (uint16_t*)TXBufferCurrentPositionHandler;
  TXBufferCurrentPositionHandler += 2;
}

void prep_packet_with_no_length(uint16_t payload_id)
{
  extern uint8_t* TXBufferCurrentPositionCAN0;
  extern uint8_t* TXBufferCurrentPositionSCI0;

  /* Flag that we are transmitting! */
  TXBufferInUseFlags |= COM_SET_SCI0_INTERFACE_ID;
  TXBufferCurrentPositionHandler = (uint8_t*)&TXBuffer;
  /* Initialised here such that override is possible */
  TXBufferCurrentPositionSCI0 = (uint8_t*)&TXBuffer;
  TXBufferCurrentPositionCAN0 = (uint8_t*)&TXBuffer;
  /* Set the flags : firmware, no ack, no addrs, has length */
  *TXBufferCurrentPositionHandler = 0;
  TXBufferCurrentPositionHandler++;
  /* Set the payload ID */
  *((uint16_t*)TXBufferCurrentPositionHandler) = payload_id;
  TXBufferCurrentPositionHandler += 2;
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
