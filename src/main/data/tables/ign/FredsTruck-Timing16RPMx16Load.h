/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2012 Fred Cooke
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
 * @brief Fred's truck's rough tuned ignition timing table
 */


//  Low RPM                                                                                                            High RPM
//  250     700    1000    1600    2200    2800    3400    4000    4600    5200    5800    6400    7000    7600    8200    8800  // Vacuum
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  15
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  30
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  45
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  60

 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  75
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  90
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), // 105
 IT(10), IT(15), IT(15), IT(17), IT(21), IT(26), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), // 120

 IT(10), IT(15), IT(15), IT(15), IT(19), IT(23), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), // 135
 IT(10), IT(15), IT(15), IT(15), IT(17), IT(21), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), // 150
 IT(10), IT(15), IT(15), IT(15), IT(15), IT(19), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), // 165
 IT(10), IT(15), IT(15), IT(15), IT(15), IT(17), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21), // 180

 IT(10), IT(15), IT(15), IT(15), IT(15), IT(15), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19), // 195
 IT(10), IT(15), IT(15), IT(15), IT(15), IT(15), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17), // 210
 IT(10), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), // 225
  IT(0),  IT(0), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10)  // 240
//  250     700    1000    1600    2200    2800    3400    4000    4600    5200    5800    6400    7000    7600    8200    8800  // Boost
//  Low RPM                                                                                                            High RPM
