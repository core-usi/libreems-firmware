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
 * @ingroup initializers LibreeEMS
 */

#include "inc/Configuration.h"
#include "inc/globals.h"
#include "inc/dataCalculation.h"
#include "inc/freeEMS.h"
#include "inc/debugging.h"


outputEvent outputSchedules[MAX_NUMBER_OF_OUTPUT_EVENTS]; //.data is default section

uint8_t currentFuelingAlgorithm_g;
uint16_t ticksPerDegree_g;
uint16_t TPSrange_g;
uint32_t injectorFlowDifference_g;
uint8_t dataLogCylinderIndex;

CANflags CANflags_g;

BTpatternParameters BTpatternParemeterSet;


//TODO guarantee proper alignment
outputAction  *nextEventPTR                               XG_SHARED;
XGoutputEvent XGoutputEvents[MAX_NUMBER_OF_OUTPUT_EVENTS] XG_SHARED;
uint16_t      nullScratch                                 XG_SHARED;
CoreVar       CoreVars_g                                  XG_SHARED; /** Core running variables */

/* Large blocks */
uint8_t TXBuffer[TX_BUFFER_SIZE] TXBUF;
uint8_t RXBuffer[RX_BUFFER_SIZE] RXBUF;

volatile uint16_t timerExtensionCounter_g;

SyncedData        syncedEngineData[ENGINE_CYLINDER_COUNT];
fuelAttributes    FuelAttribs;

CapturedInputData capturedInputData_g[GP_CAPTURE_CHANNELS];

Clock Clocks;
Counter Counters;
KeyUserDebug KeyUserDebugs;
Flaggable Flaggables;
Flaggable2 Flaggables2;

CoreVar* CoreVars; /** Pointer to the core running variables */

DerivedVar* DerivedVars; /** Pointer to the derived variables */
DerivedVar DerivedVars0; /** Derived running variables */

ADCBuffer ADCBuffers0;

Tables1 TablesA RWINDOW;
Tables2 TablesB RWINDOW;
Tables3 TablesC RWINDOW;
Tables4 TablesD RWINDOW;

/* RAM page variables */
uint8_t currentFuelRPage;
uint8_t currentTuneRPage;
uint8_t currentTimeRPage;
uint8_t portHDebounce;

/* State variables */
uint8_t coreStatusA;  /* Each bit represents the state of some core parameter, masks below */

char dbg_ringbuffer[DBG_MAXLEN];
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
