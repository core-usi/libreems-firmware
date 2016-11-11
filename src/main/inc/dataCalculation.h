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
 * @ingroup allHeaders
 */


#ifndef DATA_CALCULATION_H_SEEN
#define DATA_CALCULATION_H_SEEN

#include <stdint.h>
#include "Configuration.h"
#include "memory.h"
#include "systemConfig.h"
#include "outputPlotter.h"
#include "freeEMS.h"


void calculateAirCharge(SyncedData *syncedLookups, uint16_t cylVolumeCC, uint32_t *airCharge) TEXT1;
void calculateRequiredFuel(fuelAttributes* fuelDensity, DerivedVar* derivedVars, uint32_t airFlow, CylinderConfig*) TEXT1;
void updateCylinderCalcs(uint8_t numCylinders) TEXT1;
void updateCylinderCuts(uint8_t numCylinders, OperatingLimits *limits) TEXT1;
void updateTimedDerivatives() TEXT1;
void sensorRangesCheck();
uint16_t calculateAFR(uint8_t percentEth);
uint16_t calculateFuelDensity(uint8_t percentEth);
void updateCoreData(MasterConfig *config) LOOKUPF;

#else

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
