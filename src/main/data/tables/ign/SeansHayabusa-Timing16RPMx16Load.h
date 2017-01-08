/* LibreEMS - the community driven open source engine management system
 *
 * Copyright Sean Keys
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
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)libreems(dot)org or, even better, fork the code on gitlab.com!
 *
 * Thank you for choosing LibreEMS to run your engine!
 */


/** @file
 *
 * @ingroup dataInitialisers
 *
 * @brief A rough guess at the the R1 needs.
 */


// Low RPM                                                                                                                     High RPM
// 250     800    1600    2400      3200    4000    4800    5600      6800    7600    8400    9200     10000   10800   11500    13000 // Vacuum
IT(1), IT(7), IT(19), IT(28),   IT(27), IT(33), IT(33), IT(33),   IT(33), IT(32), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),//  15
IT(1), IT(6), IT(19), IT(28),   IT(27), IT(33), IT(33), IT(33),   IT(33), IT(32), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),//  20
IT(1), IT(6), IT(19), IT(28),   IT(27), IT(33), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),//  30
IT(1), IT(6), IT(18), IT(27),   IT(26), IT(32), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),//  45

IT(1), IT(5), IT(18), IT(27),   IT(26), IT(32), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),//  60
IT(1), IT(5), IT(17), IT(26),   IT(25), IT(31), IT(31), IT(31),   IT(31), IT(31), IT(31), IT(31),   IT(31), IT(31), IT(32), IT(32),//  75
IT(1), IT(4), IT(16), IT(25),   IT(24), IT(31), IT(31), IT(31),   IT(31), IT(31), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),//  90
IT(1), IT(4), IT(15), IT(26),   IT(25), IT(31), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),   IT(32), IT(32), IT(32), IT(32),// 105

IT(1), IT(4), IT(13), IT(23),   IT(23), IT(27), IT(27), IT(27),   IT(27), IT(27), IT(27), IT(27),   IT(27), IT(27), IT(27), IT(27),// 120
IT(1), IT(3), IT(11), IT(20),   IT(21), IT(26), IT(26), IT(26),   IT(26), IT(26), IT(26), IT(26),   IT(26), IT(26), IT(26), IT(26),// 135
IT(1), IT(2), IT(10), IT(19),   IT(20), IT(25), IT(25), IT(25),   IT(25), IT(25), IT(25), IT(25),   IT(25), IT(25), IT(25), IT(25),// 150
IT(1), IT(1), IT(9),  IT(18),   IT(19), IT(24), IT(24), IT(24),   IT(24), IT(24), IT(24), IT(24),   IT(24), IT(24), IT(24), IT(24),// 165

IT(1), IT(1), IT(6), IT(15),   IT(16), IT(21), IT(21), IT(21),   IT(21), IT(21), IT(21), IT(21),   IT(21), IT(21), IT(21), IT(21),// 180
IT(1), IT(1), IT(4), IT(13),   IT(14), IT(19), IT(19), IT(19),   IT(19), IT(19), IT(19), IT(19),   IT(19), IT(19), IT(19), IT(19),// 195
IT(1), IT(1), IT(2), IT(11),   IT(12), IT(17), IT(17), IT(17),   IT(17), IT(17), IT(17), IT(17),   IT(17), IT(17), IT(17), IT(17),// 200
IT(1), IT(1), IT(1), IT(10),   IT(11), IT(16), IT(16), IT(16),   IT(16), IT(16), IT(16), IT(16),   IT(16), IT(16), IT(16), IT(16),// 225
// 250     800    1600    2400      3200    4000    4800    5600      6800    7600    8400    9200     10000   10800   11500    13000 // Vacuum
// Low RPM                                                                                                                      High RPM                                                                                                                                                                                    High RPM
