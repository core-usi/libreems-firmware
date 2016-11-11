/* LibreEMS - the open source engine management system
 *
 * Copyright 2012 Sean Keys
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
 */


/** @file
 *
 * @ingroup dataInitialisers
 *
 * @brief A timing table for a 2003 Yamaha R1.
 *
 * Under development
 *
 */


// Low R                                                                                                                                                                                        High RPM
// 250    500     750      1000    1500    2000      2500    3000     3500     4000     4500      5000     5500     6000    6500      7500      8000    8500    9000    9500   10000   10500   11000   12400   13000// Boost
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(8.0), IT(30),  IT(26),  IT(30),  IT(33),  IT(33),  IT(34),  IT(34),  IT(34),  IT(34),  IT(35),  IT(35),  IT(35), IT(35), IT(35), IT(36), IT(36), IT(35), IT(35), IT(35), IT(35), // 15
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(8.0), IT(30),  IT(37),  IT(50),  IT(55),  IT(55),  IT(56),  IT(59),  IT(59),  IT(60),  IT(60),  IT(56),  IT(56), IT(55), IT(55), IT(54), IT(52), IT(52), IT(52), IT(52), IT(52), // 20
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(8.0), IT(17),  IT(25),  IT(35),  IT(38),  IT(38),  IT(39),  IT(39),  IT(39),  IT(39),  IT(40),  IT(40),  IT(40), IT(40), IT(40), IT(41), IT(41), IT(40), IT(40), IT(40), IT(40), // 30
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(6.0), IT(10),  IT(20),  IT(35),  IT(33),  IT(33),  IT(34),  IT(34),  IT(34),  IT(34),  IT(35),  IT(35),  IT(35), IT(35), IT(35), IT(36), IT(36), IT(35), IT(35), IT(35), IT(35), // 45

IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(6.0), IT(10),  IT(20),  IT(28),  IT(30),  IT(32),  IT(32),  IT(33),  IT(34),  IT(34),  IT(35),  IT(35),  IT(35), IT(35), IT(35), IT(36), IT(36), IT(35), IT(35), IT(35), IT(35), // 60
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(6.0), IT(10),  IT(20),  IT(28),  IT(30),  IT(32),  IT(32),  IT(33),  IT(34),  IT(34),  IT(35),  IT(35),  IT(35), IT(35), IT(35), IT(36), IT(36), IT(35), IT(35), IT(35), IT(35), // 75
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(6.0), IT(10),  IT(20),  IT(28),  IT(30),  IT(32),  IT(32),  IT(33),  IT(34),  IT(34),  IT(35),  IT(35),  IT(35), IT(35), IT(35), IT(36), IT(36), IT(35), IT(35), IT(35), IT(35), // 90
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(6.0), IT(10),  IT(19),  IT(28),  IT(30),  IT(32),  IT(32),  IT(33),  IT(34),  IT(34),  IT(35),  IT(35),  IT(35), IT(35), IT(35), IT(36), IT(36), IT(35), IT(35), IT(35), IT(35), // 105

IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(6.0), IT(10),  IT(18),  IT(27),  IT(28),  IT(32),  IT(30),  IT(32),  IT(30),  IT(32),  IT(30),  IT(33),  IT(33), IT(33), IT(33), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), // 120
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(6.0), IT(10),  IT(18),  IT(26),  IT(28),  IT(30),  IT(30),  IT(31),  IT(29),  IT(29),  IT(29),  IT(29),  IT(30), IT(30), IT(30), IT(30), IT(31), IT(31), IT(31), IT(31), IT(31), // 135
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(6.0), IT(10),  IT(18),  IT(25),  IT(28),  IT(29),  IT(29),  IT(30),  IT(28),  IT(28),  IT(28),  IT(28),  IT(28), IT(28), IT(28), IT(29), IT(29), IT(29), IT(29), IT(29), IT(29), // 150
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(8.0), IT(10),  IT(18),  IT(23),  IT(29),  IT(28),  IT(29),  IT(29),  IT(27),  IT(27),  IT(27),  IT(27),  IT(27), IT(27), IT(27), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), // 165

IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(8.0), IT(10),  IT(16),  IT(23),  IT(27),  IT(27),  IT(28),  IT(28),  IT(26),  IT(26),  IT(26),  IT(26),  IT(26), IT(26), IT(26), IT(27), IT(27), IT(27), IT(27), IT(27), IT(27), // 180
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(8.0), IT(9),  IT(16),  IT(23),  IT(26),  IT(26),  IT(27),  IT(27),  IT(25),  IT(25),  IT(25),  IT(25),  IT(25), IT(25), IT(25), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), // 195
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(8.0), IT(8),  IT(16),  IT(22),  IT(25),  IT(25),  IT(26),  IT(26),  IT(24),  IT(24),  IT(24),  IT(24),  IT(24), IT(24), IT(24), IT(25), IT(25), IT(25), IT(25), IT(25), IT(25), // 200
IT(5.0), IT(5.0), IT(5.0),IT(5.0),IT(8.0), IT(8),  IT(16),  IT(20),  IT(23),  IT(23),  IT(24),  IT(24),  IT(23),  IT(23),  IT(23),  IT(23),  IT(23), IT(23), IT(23), IT(24), IT(24), IT(24), IT(24), IT(24), IT(24)  // 225
// 250    500     750      1000    1500    2000      2500    3000     3500     4000     4500      5000     5500     6000    6500      7500      8000    8500    9000    9500   10000   10500   11000   12400   13000// Boost
// Low R                                                                                                                                                                                        High RPM
