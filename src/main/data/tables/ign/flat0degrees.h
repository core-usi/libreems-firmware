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
 * @brief A flat 0 degree timing table, ONLY for use with mechanical timing as
 * a basis for a trim table or for finding TDC while setting up an engine.
 *
 * @warning DO NOT RUN YOUR CAR ON THIS!
 */


// Full data size, usable with any axis sizes
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0)
