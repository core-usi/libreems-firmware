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
 * @ingroup TODO
 *
 * @brief TODO
 *
 *
 */


#ifndef FILE_INTERRUPTS_H_SEEN
#define FILE_INTERRUPTS_H_SEEN

#include "memory.h"


/* ISR attribute necessary to restore some soft registers */
#define ISR __attribute__((interrupt))

#ifndef HOST_TESTS
#define ATOMIC_START() __asm__ __volatile__ ("sei") /* Disable S12 interrupts */
#define ATOMIC_END()   __asm__ __volatile__ ("cli") /* Enable S12 Interrupts */
#else
#define ATOMIC_START() return  /* Disable S12 interrupts */
#define ATOMIC_END()   return  /* Enable S12 Interrupts */
#endif

#define VECTORS __attribute__ ((section (".vectors")))

extern void _start(void);

typedef void (* interruptFunction)(void);

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
