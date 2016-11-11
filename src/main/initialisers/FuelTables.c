/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014-2016 Sean Keys, David J. Andruczyk
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
 * @ingroup dataInitialisers
 *
 * @brief Fuel VE and Lambda tables
 *
 * This file contains the definitions of the primary group VE and lambda
 * tables. The declaration can be found in the global constants header file.
 *
 * @note At least one Doxygen bug prevents the data structures below being show
 *       correctly in the documentation for this file. Please see the source
 *       code itself for more information.
 */


#include "../inc/freeEMS.h"
#include "../inc/Configuration.h"


#ifndef VETableMainFlashV
#define VETableMainFlashV VETableMainFlash
#define VETableSecondaryFlashV VETableSecondaryFlash
#define AirflowTableFlashV AirflowTableFlash
#define LambdaTableFlashV LambdaTableFlash
#endif


const volatile mainTable VETableMainFlashV FUELTABLESD = {
	RPMLength:  VE_TABLE_RPM_LENGTH,
	LoadLength: VE_TABLE_LOAD_LENGTH,
	RPM: {
		#include VE_RPM_AXIS_PRIMARY
	/*
#if CONFIG == TRUCK_ID
  #include "../data/tables/axis/FredsTruck-RPM-16.h"
#elif CONFIG == PRESTO_ID
  #include "../data/tables/axis/FredsTruck-RPM-16.h"
#elif CONFIG == SEANKLT1_ID
  #include "../data/tables/axis/SeansLT1-RPM-16.h"
#elif CONFIG == SLATER_ID
  #include "../data/tables/axis/Slater-RPM-16.h"
#elif CONFIG == PETERJSERIES_ID
  #include "../data/tables/axis/PetersJSeries-RPM-16.h"
#elif CONFIG == DEUCECOUPE_ID
  #include "../data/tables/axis/HotelHyundai-RPM-16.h"
#else CONFIG == DEUCES10_ID
  #include "../data/tables/axis/Deuces3100-RPM-13.h"
#endif
  */
	},
	Load: {
		#include VE_LOAD_AXIS_PRIMARY
/*
#if CONFIG == TRUCK_ID
  #include "../data/tables/axis/FredsTruck-Load-16.h"
#elif CONFIG == PRESTO_ID
  #include "../data/tables/axis/FredsTruck-Load-16.h"
#elif CONFIG == SEANKLT1_ID
  #include "../data/tables/axis/FredsTruck-Load-16.h"
#elif CONFIG == SLATER_ID
  #include "../data/tables/axis/Slater-Load-16.h"
#elif CONFIG == PETERJSERIES_ID
  #include "../data/tables/axis/PetersJSeries-Load-16.h"
#elif CONFIG == DEUCECOUPE_ID
  #include "../data/tables/axis/HotelHyundai-Load-16.h"
#else CONFIG == DEUCES10_ID
  #include "../data/tables/axis/Deuces3100-Load-10.h"
#endif
*/
	},
	Table: {
		#include VE_TABLE_PRIMARY
/*
#if CONFIG == TRUCK_ID
  #include "../data/tables/ve/FredsTruck-VE16RPMx16Load.h"
#elif CONFIG == PRESTO_ID
  #include "../data/tables/ve/flat60-VE16RPMx16Load.h"
#elif CONFIG == SEANKLT1_ID
  #include "../data/tables/ve/SeansLT1-VE16RPMx16Load.h"
#elif CONFIG == SLATER_ID
  #include "../data/tables/ve/Slater-VE16RPMx16Load.h"
#elif CONFIG == PETERJSERIES_ID
  #include "../data/tables/ve/PetersJSeries-VE16RPMx16Load.h"
#elif CONFIG == DEUCECOUPE_ID
  #include "../data/tables/ve/flat60-VE16RPMx16Load.h"
#else CONFIG == DEUCES10_ID
  #include "../data/tables/ve/DeucesS10-VE13RPMx10Load.h"
#endif
*/
	}
};


const volatile mainTable VETableSecondaryFlashV FUELTABLESD = {
	RPMLength:  MAINTABLE_RPM_LENGTH,
	LoadLength: MAINTABLE_LOAD_LENGTH,
	RPM:{
		#include VE_RPM_AXIS_SECONDARY
	},
	Load:{
		#include VE_LOAD_AXIS_SECONDARY
	},
	Table:{
		#include VE_TABLE_SECONDARY
	}
};


const volatile mainTable AirflowTableFlashV FUELTABLESD = {
	RPMLength:  MAINTABLE_RPM_LENGTH,
	LoadLength: MAINTABLE_LOAD_LENGTH,
	RPM:{
		#include AIRFLOW_RPM_AXIS
	},
	Load:{
		#include AIRFLOW_LOAD_AXIS
	},
	Table:{
		#include AIRFLOW_TABLE
	}
};


const volatile mainTable LambdaTableFlashV FUELTABLESD = {
	RPMLength:  LAMBDA_TABLE_RPM_LENGTH,
	LoadLength: LAMBDA_TABLE_LOAD_LENGTH,
/*
#elif CONFIG == DEUCES10_ID
	RPMLength:  13,
	LoadLength: 10,
#else
	RPMLength:  16,
	LoadLength: 16,
#endif
*/
	RPM: {
		#include LAMBDA_RPM_AXIS
/*
#if CONFIG == SLATER_ID
  #include "../data/tables/axis/Slater-RPM-16.h"
#else CONFIG == DEUCES10_ID
  #include "../data/tables/axis/Deuces3100-RPM-13.h"
#endif
*/
	},
	Load: {
		#include LAMBDA_LOAD_AXIS
/*
#if CONFIG == SLATER_ID
  #include "../data/tables/axis/Slater-Load-16.h"
#else CONFIG == DEUCES10_ID
  #include "../data/tables/axis/Deuces3100-Load-10.h"
#endif
*/
	},
	Table: {
		#include LAMBDA_TABLE

/*
#if CONFIG == SLATER_ID
  #include "../data/tables/lambda/Slater-Lambda16RPMx16Load.h"
#else CONFIG == DEUCES10_ID
  #include "../data/tables/lambda/DeucesS10--Lambda13RPMx10Load.h"
#endif
*/
	}
};
