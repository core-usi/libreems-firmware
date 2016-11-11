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


/** @file
 *
 * @ingroup Configuration
 *
 */

#ifndef FILE_HARDWARE_CONFIGURATION_H_SEEN
#define FILE_HARDWARE_CONFIGURATION_H_SEEN


#define HARDWARE_ID         F16
#define XGATE_CHANNEL_COUNT	 24
#define CAN_QUEUE_COUNT      50
#define GP_CAPTURE_CHANNELS   5  /* Number of GP capture channels */


#define BRV_MINIMUM VOLTS(0)
#define BRV_MAXIMUM VOLTS(24.65)
#define BRV_RANGE   (BRV_MAXIMUM - BRV_MINIMUM)


#ifndef XGATE_OUTPUT_CHANNEL_CONFIG
#define XGATE_OUTPUT_CHANNEL_CONFIG
/*
 *  XGATE channel designation
 *
 * ATTENTION -- this needs to coincide with your cylinder config setup
 *
 */

/* We reserve the first four channels for ignition */
#define CH0_PORT   PORTD_ADDR
#define CH0_MASK   (1 << 0)

#define CH1_PORT   PORTD_ADDR
#define CH1_MASK   (1 << 0)

#define CH2_PORT   PORTD_ADDR
#define CH2_MASK   (1 << 0)

#define CH3_PORT   PORTD_ADDR
#define CH3_MASK   (1 << 0)

/* We setup the next for channels for fuel */
#define CH4_PORT   PORTB_ADDR
#define CH4_MASK   (1 << 0)

#define CH5_PORT   PORTB_ADDR
#define CH5_MASK   (1 << 1)

#define CH6_PORT   PORTB_ADDR
#define CH6_MASK   (1 << 2)

#define CH7_PORT   PORTB_ADDR
#define CH7_MASK   (1 << 3)


/* Second set of 4 channels are for fuel */
#define CH8_PORT   PORTB_ADDR
#define CH8_MASK   (1 << 4)

#define CH9_PORT   PORTB_ADDR
#define CH9_MASK   (1 << 5)

#define CH10_PORT  PORTB_ADDR
#define CH10_MASK  (1 << 6)

#define CH11_PORT  PORTB_ADDR
#define CH11_MASK  (1 << 7)

/* Typically last four pins on port D are used for ignition, for guys with > 4 cylinders */
#define CH12_PORT  PORTD_ADDR
#define CH12_MASK  (1 << 0)

#define CH13_PORT  PORTD_ADDR
#define CH13_MASK  (1 << 0)

#define CH14_PORT  PORTD_ADDR
#define CH14_MASK  (1 << 0)

#define CH15_PORT  PORTD_ADDR
#define CH15_MASK  (1 << 0)

/* More channels, incase you need them */
#define CH16_PORT  PORTC_ADDR
#define CH16_MASK  (1 << 0)

#define CH17_PORT  PORTC_ADDR
#define CH17_MASK  (1 << 1)

#define CH18_PORT  PORTC_ADDR
#define CH18_MASK  (1 << 2)

#define CH19_PORT  PORTC_ADDR
#define CH19_MASK  (1 << 3)

#define CH20_PORT  PORTC_ADDR
#define CH20_MASK  (1 << 4)

#define CH21_PORT  PORTC_ADDR
#define CH21_MASK  (1 << 5)

#define CH22_PORT  PORTC_ADDR
#define CH22_MASK  (1 << 6)

#define CH23_PORT  PORTC_ADDR
#define CH23_MASK  (1 << 7)

#endif


#endif
