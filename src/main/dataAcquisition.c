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
 * @ingroup data calculation
 */


#include "inc/dataAcquisition.h"
#include "inc/dataCalculation.h"
#include "inc/printf.h"
#include "inc/freeEMS.h"
#include "inc/interrupts_depricated.h"
#include "inc/utils.h"
#include "inc/locationIDs.h"


/*
 * Here we update angle dependent ADC values. Each output has it's own buffer
 */
//TODO combine count into config struct
uint8_t updateAngleDependantData(DecoderStats *decoderStats, uint8_t cylinderCount, CylinderConfig *Cylinder) {
  uint8_t i;
  uint8_t updates;

  for (i = 0, updates = 0; i < cylinderCount; ++i, ++Cylinder) {
    if (getAngle(decoderStats->currentPrimaryEvent) == Cylinder->ReadAngle) {
      readRTADCValues(Cylinder->syncedEngineData);
      Cylinder->syncedEngineData->TPD = decoderStats->instantTicksPerDegree;
      ++updates;
    }
  }
  return updates;
}

inline void readRTADCValues(SyncedData *buffer) {
/* TODO we need some sort of HAL for at least the ADC channels IMO */
  buffer->IAP = ATD1DR1;
  buffer->TPS = ATD0DR2;
  buffer->MAP = ATD0DR4;
  buffer->MAF = ATD1DR2;

  return;
}

/* Since we are taking the sample once a second there is not much to be gained by keeping
 * track of the ISR latency.
 */
uint8_t readFlexFuelEth() {
  static uint8_t counter = 0;
  /*
   * This function needs to use frequency in Hz and PW. It works as follows:
   * At 0% ethanol we should read 50 Hertz
   * At 100% ethanol we should read 150 Hertz.
   * The pulse width indicates the fuel temperature. The normal pulse width is between 1 and 5 milliseconds:
   * at -40°C our PW will measure 1 millisecond
   * at 125C° our PW will measure 5 milliseconds
   */

  //TODO add cases for more flex sensor types
    uint8_t frequency = capturedInputData_g[0].frequencyHz;

  if (frequency >= (CONTINENTAL_FS_RANGE_LOWER - CONTINENTAL_ERROR_WINDOW) && frequency <= (CONTINENTAL_FS_RANGE_UPPER + CONTINENTAL_ERROR_WINDOW)) {
    if (frequency >= CONTINENTAL_FS_RANGE_UPPER) {
      frequency = (CONTINENTAL_FS_RANGE_UPPER - CONTINENTAL_FS_RANGE_LOWER) * ETHANOL_COMPOSITION_FACTOR;
    }else if (frequency <= CONTINENTAL_FS_RANGE_LOWER) {
      frequency = 0;
    }else {
      frequency = (frequency - CONTINENTAL_FS_RANGE_LOWER) * ETHANOL_COMPOSITION_FACTOR;
    }

  } else {
    counter++;
    //TODO Return default expected percentage and flag an error to indicate the sensor is unreadable
    frequency = 85 * ETHANOL_COMPOSITION_FACTOR; //Return E85 advertised ratio

    //TODO (skeys) this counter serves as a reminder that we need to only
    //  check certain sensors every so often. IE use the RT interrupt to set a
    //  flag that certain sensor reads and data need to be updated.
/*    if (counter > 5) {
      e_printf("Ethanol sensor unreadable!\n");
      counter = 0;
    }
      */
  }

    return frequency;
}

void updateCapturedInput(uint8_t edge, CapturedInputData *dataStore, ExtendedTime *previousStamp, ExtendedTime *captureStamp) {
  ++dataStore->ISRcount;
  /* Update Angle Data */
  DecoderStats *decoderStats = getDecoderStats();
  uint16_t currentAngle = getAngle(decoderStats->currentPrimaryEvent);
  currentAngle = offsetAngle(currentAngle, -(Config.mechanicalProperties.decoderInputAngleOffset));
  uint32_t elapsedTime = diffUint32(captureStamp->time, decoderStats->lastPrimaryTimeStamp.time);
  uint16_t degreesSinceLastInput = (elapsedTime * TICKS_PER_DEGREE_MULTIPLIER) / decoderStats->instantTicksPerDegree;
  uint16_t angle = angleAdd(currentAngle, degreesSinceLastInput);
  /* Calc elapsed time */
  uint16_t pw = diffUint32(captureStamp->time, previousStamp->time);

  /* Is edge high? */
  if (edge == 0) {
    dataStore->periodHighTicks = pw;
    /* Update Angle Data */
    dataStore->capturedAngleHigh = angle;
  } else {
    dataStore->periodLowTicks = pw;
    dataStore->capturedAngleLow = angle;
  }
  /* calc frequency */
  dataStore->frequencyHz = ((uint32_t)TICKS_PER_SECOND) /
      ((uint32_t)dataStore->periodLowTicks + dataStore->periodHighTicks);
  previousStamp->time = captureStamp->time;

}
