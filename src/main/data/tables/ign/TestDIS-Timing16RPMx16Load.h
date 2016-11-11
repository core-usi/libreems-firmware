/* FreeEMS - the open source engine management system
 *
 * Copyright 2012 Fred Cooke
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
 * @brief A stepped timing test for GM DIS use.
 *
 * This file only contains the data to be hash included into some timing tables
 */


/* Based on divisor of 1024 giving approximately 64 degree range with absurd wasteful accuracy level to be corrected later */
/// TODO @todo this is all wrongly laid out now, due to Dave's whinging, so needs fixing...
/* Laid out to make sense for 24 RPM and 19 Load bins, 8 extras on end to make up size. */

//  Low RPM                                      10btdc to 20btdc        20btdc to 0btdc                              High RPM
//  100     500     700    1300    1700    2100    2500    2501    3300    3500    3501    4700    5300    5900    6500    6501  // Vacuum
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),

 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),

 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),

 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
 IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(20), IT(20), IT(20),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0)
//  100     500     700    1300    1700    2100    2500    2501    3300    3500    3501    4700    5300    5900    6500    6501  // Boost
//  Low RPM                                                                                                            High RPM
