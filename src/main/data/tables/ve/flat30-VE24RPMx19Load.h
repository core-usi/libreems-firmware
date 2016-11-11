/* LibreEMS - the open source engine management system
 *
 * Copyright 2016 David Andruczyk
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
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing LibreEMS to run your engine!
 */


/** @file
 *
 * @ingroup dataInitialisers
 *
 * @brief A dead flat 30% VE curve to use as a default for typical engines. 24x19
 */


// Low RPM                          -5-                                      -10-                                      -15-                                      -20-                           High RPM
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),

VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),

VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),

VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),

VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),   VE(30), VE(30), VE(30), VE(30),
