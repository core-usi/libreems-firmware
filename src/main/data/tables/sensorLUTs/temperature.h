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

#ifndef SRC_MAIN_DATA_TABLES_TEMPERATURE_LUTS_PRESSURE_H_
#define SRC_MAIN_DATA_TABLES_TEMPERATURE_LUTS_PRESSURE_H_

#define EGT_F16                \
  {AV(0.009), EGT_C(  2.54)},  \
  {AV(0.102), EGT_C(  26.73)}, \
  {AV(0.371), EGT_C(  96.76)}, \
  {AV(1.215), EGT_C( 317.03)}, \
  {AV(1.655), EGT_C( 431.62)}, \
  {AV(2.929), EGT_C( 763.37)}, \
  {AV(3.666), EGT_C( 956.19)}, \
  {AV(4.995), EGT_C( 1302.00)}

#endif
