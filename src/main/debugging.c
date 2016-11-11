/* LibreEMS - the community driven open source engine management system
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
 * Thank you for choosing LibreEMS to run your engine!
 */


/** @file
 *
 * @ingroup debugging ringbuffer implementation
 */

#include "inc/memory.h"
#include <string.h>
#include "inc/debugging.h"

extern char dbg_ringbuffer[];
uint8_t dbg_head = 0;
uint8_t dbg_tail = 0;

char dbg_push(const char data) 
{
  uint16_t next = dbg_head + 1;
    if (next >= DBG_MAXLEN)
        next = 0;
 
/*    // Circular buffer is full
    if (next == dbg_tail)
        return -1;  // quit with an error
        // We don't care about overflow curently
 */
    dbg_ringbuffer[dbg_head] = data;
    dbg_head = next;
    return 0;
} 

uint16_t drain_debug_buffer()
{
  extern uint8_t* TXBufferCurrentPositionHandler;
  uint16_t count = 0;
  if(dbg_head > dbg_tail) /* not wrapped */
  {
    count = dbg_head - dbg_tail;
    memcpy(TXBufferCurrentPositionHandler,dbg_ringbuffer+dbg_tail,count);
    TXBufferCurrentPositionHandler += count;
  }
  else /* wrapped, need to copy each section one at a time */
  {
    count = DBG_MAXLEN - dbg_tail;
    memcpy(TXBufferCurrentPositionHandler,dbg_ringbuffer+dbg_tail,count);
    TXBufferCurrentPositionHandler += count;
    memcpy(TXBufferCurrentPositionHandler+(count),dbg_ringbuffer,dbg_head);
    TXBufferCurrentPositionHandler += dbg_head;
    count += dbg_head;
  }
  dbg_head = dbg_tail;
  return count;
}
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
