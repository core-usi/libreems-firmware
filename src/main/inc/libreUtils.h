/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2015 Sean Keys
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
 * @ingroup communicationsFiles
 *
 * @brief Utilities
 *
 *
 */

#ifndef DATA_LIBREUTILS_H_SEEN
#define DATA_LIBREUTILS_H_SEEN

static inline void strcpy(uint8_t *destination, uint8_t *source) {
  while (*source != 0) {
    *destination++ = *source++;
  }
  *destination = 0;
}

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
