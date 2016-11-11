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

#ifndef SRC_MAIN_DATA_TABLES_SENSORLUTS_PRESSURE_H_
#define SRC_MAIN_DATA_TABLES_SENSORLUTS_PRESSURE_H_

#define APS_MPX4250A         \
  {AV(0.20), KPA_S( 20.00)}, \
  {AV(0.87), KPA_S( 52.85)}, \
  {AV(1.54), KPA_S( 85.71)}, \
  {AV(2.21), KPA_S(118.57)}, \
  {AV(2.88), KPA_S(151.42)}, \
  {AV(3.55), KPA_S(184.28)}, \
  {AV(4.22), KPA_S(217.14)}, \
  {AV(4.90), KPA_S(250.00)}

#define PS_GLOWSHIFT_60     \
  {AV(0.0), KPA_S(  0.00)}, \
  {AV(0.7), KPA_S( 58.00)}, \
  {AV(1.4), KPA_S(116.00)}, \
  {AV(2.1), KPA_S(174.00)}, \
  {AV(2.8), KPA_S(232.00)}, \
  {AV(3.5), KPA_S(290.00)}, \
  {AV(4.2), KPA_S(349.00)}, \
  {AV(4.9), KPA_S(410.00)}

#define APS_DENSOR1          \
  {AV(0.000), KPA_S( 10.5)}, \
  {AV(0.715), KPA_S( 34.8)}, \
  {AV(1.430), KPA_S( 59.1)}, \
  {AV(2.145), KPA_S( 83.4)}, \
  {AV(2.860), KPA_S(107.7)}, \
  {AV(3.575), KPA_S(132.0)}, \
  {AV(4.290), KPA_S(156.3)}, \
  {AV(5.000), KPA_S(180.6)}

#define APS_GM3BAR           \
  {AV(0.00), KPA_S(  1.10)}, \
  {AV(0.71), KPA_S( 46.01)}, \
  {AV(1.42), KPA_S( 90.92)}, \
  {AV(2.14), KPA_S(135.84)}, \
  {AV(2.85), KPA_S(180.75)}, \
  {AV(3.57), KPA_S(225.67)}, \
  {AV(4.28), KPA_S(270.58)}, \
  {AV(5.00), KPA_S(315.50)}

#define APS_MPXA6115A         \
  {AV(0.200), KPA_S( 15.0)}, \
  {AV(0.500), KPA_S( 20.0)}, \
  {AV(1.500), KPA_S( 40.0)}, \
  {AV(2.000), KPA_S( 51.0)}, \
  {AV(2.500), KPA_S( 65.0)}, \
  {AV(3.500), KPA_S( 80.0)}, \
  {AV(4.000), KPA_S( 99.0)}, \
  {AV(4.700), KPA_S(115.0)}

#endif /* SRC_MAIN_DATA_TABLES_SENSORLUTS_MAPDENSOR1_H_ */
