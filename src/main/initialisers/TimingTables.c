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
 * @ingroup dataInitialisers
 *
 * @brief Injection and ignition timing tables
 *
 * This file contains the definitions of the primary group timing tables. The
 * declaration can be found in the global constants header file.
 *
 * @note At least one Doxygen bug prevents the data structures below being show
 *       correctly in the documentation for this file. Please see the source
 *       code itself for more information.
 */


#include "../inc/freeEMS.h"
#include "../inc/dataCalculation.h"
#include "../inc/Configuration.h"

#ifndef IgnitionAdvanceTableMainFlashV
#define IgnitionAdvanceTableMainFlashV IgnitionAdvanceTableMainFlash
#define IgnitionAdvanceTableSecondaryFlashV IgnitionAdvanceTableSecondaryFlash
#define InjectionAdvanceTableMainFlashV InjectionAdvanceTableMainFlash
#define InjectionAdvanceTableSecondaryFlashV InjectionAdvanceTableSecondaryFlash
#endif


// See fuelAndIgnitionCalcs.c for more info about CLIFLAGS builds!
/* The main Advance Table */
const volatile mainTable IgnitionAdvanceTableMainFlashV TIMETABLESD = {
	RPMLength:  IGNITION_TABLE_RPM_LENGTH,
	LoadLength: IGNITION_TABLE_LOAD_LENGTH,

/*
#elif CONFIG == SNOTROCKET_ID
	RPMLength:  12,
	LoadLength: 8,
#elif CONFIG == DEUCES10_ID
	RPMLength:  13,
	LoadLength: 10,
#else
	RPMLength:  16,
	LoadLength: 16,
#endif
*/
	RPM:{
		#include IGNITION_RPM_AXIS_PRIMARY
/*
#if CONFIG == TRUCK_ID
#include "../data/tables/axis/FredsTruck-RPM-16.h"
#elif CONFIG == HOTEL_ID
#include "../data/tables/axis/HotelHyundai-RPM-16.h"
#elif CONFIG == PRESTO_ID
#include "../data/tables/axis/FredsTruck-RPM-16.h"
#elif CONFIG == SEANKLT1_ID
#include "../data/tables/axis/SeansLT1-RPM-16.h"
#elif CONFIG == SNOTROCKET_ID
#include "../data/tables/axis/SimsVolvo-RPM-12.h"
#elif CONFIG == SLATER_ID
#include "../data/tables/axis/Slater-RPM-16.h"
#elif CONFIG == DEUCECOUPE_ID
#include "../data/tables/axis/HotelHyundai-RPM-16.h"
#elif CONFIG == DEUCES10_ID
#include "../data/tables/axis/Deuces3100-RPM-16.h"
#else CONFIG == PETERTRUCK_ID
#include "../data/tables/axis/HotelHyundai-RPM-16.h"
#endif
*/
	},
	Load: {
		#include IGNITION_LOAD_AXIS_PRIMARY
/*
#if CONFIG == TRUCK_ID
#include "../data/tables/axis/FredsTruck-Load-16.h"
#elif CONFIG == HOTEL_ID
#include "../data/tables/axis/HotelHyundai-Load-16.h"
#elif CONFIG == PRESTO_ID
#include "../data/tables/axis/FredsTruck-Load-16.h"
#elif CONFIG == SEANKLT1_ID
#include "../data/tables/axis/FredsTruck-Load-16.h"
#elif CONFIG == SNOTROCKET_ID
#include "../data/tables/axis/SimsVolvo-Load-8.h"
#elif CONFIG == SLATER_ID
#include "../data/tables/axis/Slater-Load-16.h"
#elif CONFIG == DEUCECOUPE_ID
#include "../data/tables/axis/HotelHyundai-Load-16.h"
#elif CONFIG == DEUCES10_ID
#include "../data/tables/axis/Deuces3100-Load-10.h"
#elif CONFIG == PETERTRUCK_ID
#include "../data/tables/axis/HotelHyundai-Load-16.h"
#endif
*/
	},
	Table: {
		#include IGNITION_TABLE_PRIMARY
/*
// USE FLAT 0 DEGREE TIMING UNTIL YOU CAN VERIFY YOUR DECODER OFFSET!!
#if CONFIG == TRUCK_ID
#include "../data/tables/ign/FredsTruck-Timing16RPMx16Load.h"
#elif CONFIG == HOTEL_ID
#include "../data/tables/ign/HotelHyundai-Timing16RPMx16Load.h"
#elif CONFIG == PRESTO_ID
#include "../data/tables/ign/HotelHyundai-Timing16RPMx16Load.h"
#elif CONFIG == SEANKLT1_ID
#include "../data/tables/ign/SeansLT1-Timing16RPMx16Load.h"
#elif CONFIG == SNOTROCKET_ID
#include "../data/tables/ign/SimsVolvo-Timing12RPMx8Load.h"
#elif CONFIG == SLATER_ID
#include "../data/tables/ign/Slater-Timing16RPMx16Load.h"
#elif CONFIG == DEUCECOUPE_ID
//#include "../data/tables/ign/TestDIS.h" // Use for verifying your DIS timing
#include "../data/tables/ign/Deuces3100-Timing16RPMx16Load.h"
#elif CONFIG == DEUCES10_ID
#include "../data/tables/ign/DeucesS10-Timing13RPMx10Load.h"
#elif CONFIG == PETERTRUCK_ID
#include "../data/tables/ign/HotelHyundai-Timing16RPMx16Load.h"
#endif
*/
	}
};


/* The secondary Advance Table */
const volatile mainTable IgnitionAdvanceTableSecondaryFlashV TIMETABLESD = {
	RPMLength:  IGNITION_TABLE_RPM_LENGTH,
	LoadLength: IGNITION_TABLE_LOAD_LENGTH,
	RPM:{
		#include IGNITION_RPM_AXIS_SECONDARY
	},
	Load:{
		#include IGNITION_LOAD_AXIS_SECONDARY
	},
	Table:{
		#include IGNITION_TABLE_SECONDARY
	}
};


/* The main Volumetric Efficiency Table */
const volatile mainTable InjectionAdvanceTableMainFlashV TIMETABLESD = {
	RPMLength:  INJECTION_TABLE_RPM_LENGTH,
	LoadLength: INJECTION_TABLE_LOAD_LENGTH,
	RPM:{
		#include INJECTION_RPM_AXIS_PRIMARY
	},
	Load:{
		#include INJECTION_LOAD_AXIS_PRIMARY
	},
	Table:{
		#include INJECTION_TABLE_PRIMARY
	}
};


/* The secondary Volumetric Efficiency Table */
const volatile mainTable InjectionAdvanceTableSecondaryFlashV TIMETABLESD = {
	RPMLength:  INJECTION_TABLE_RPM_LENGTH,
	LoadLength: INJECTION_TABLE_LOAD_LENGTH,
	RPM:{
		#include INJECTION_RPM_AXIS_SECONDARY
	},
	Load:{
		#include INJECTION_LOAD_AXIS_SECONDARY
	},
	Table:{
		#include INJECTION_TABLE_SECONDARY
	}
};
