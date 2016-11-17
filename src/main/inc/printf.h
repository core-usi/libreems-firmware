/*
 * File: printf.h
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
 *
 * Copyright (c) 2004,2008 Kustaa Nyholm / SpareTimeLabs
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 *
 * Neither the name of the Kustaa Nyholm or SpareTimeLabs nor the names of its
 * contributors may be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 * ---------------------------------------------------------------------------

 * This library is realy just two files: 'printf.h' and 'printf.c'.
 * 
 * They provide a simple and small (+100 loc) printf functionality to 
 * be used in embedded systems.
 * 
 * I've found them so usefull in debugging that I do not bother with a 
 * debugger at all.
 * 
 * They are distributed in source form, so to use them, just compile them 
 * into your project. 
 * 
 * The formats supported by this implementation are: 'd' 'u' 'c' 's' 'x' 'X'.
 * 
 * Zero padding and field width (limited to 255) are also supported.
 * 
 * The memory foot print of course depends on the target cpu, compiler and 
 * compiler options, but a rough guestimate (based on a HC08 target) is about 
 * 600 - 1100 bytes for code and some twenty bytes of static data.  Note
 * that this printf is not re-entrant. 
 * 
 * Note that the code expects that int size is 16 bits, and that char is
 * 8 bits.
 * 
 * To use the printf you need to supply your own character output function, 
 * something like :
 * 
 * void putchar (char c)
 *  {
 *  while (!SERIAL_PORT_EMPTY) ;
 *  SERIAL_PORT_TX_REGISTER = c;
 *  }
 * 
 * 
 * The printf function is actually a macro that translates to 'tfp_printf'. 
 * This makes it possible to use it along with 'stdio.h' printf's in a single 
 * source file. You just need to undef the names before you include the 'stdio.h'.
 * Note that these are not function-like macros, so if you have variables
 * or struct members with these names, things will explode in your face.
 * Without variadic macros this is the best we can do. If it is a  problem 
 * just give up the macros and use the functions directly or rename them.
 * 
 * For further details see source code.
 * 
 * regs Kusti, 26.2.2008
 */


#ifndef __TFP_PRINTF__
#define __TFP_PRINTF__

#include "memory.h"
#include <stdarg.h>

void out(char c) FPPAGE_E5;
void outDgt(char dgt) FPPAGE_E5;
void divOut(unsigned int div) FPPAGE_E5;
void tfp_printf(char *fmt, ...) FPPAGE_E5;


#define printf tfp_printf 
#define i_printf(...) tfp_printf("I: "); extern KeyUserDebug KeyUserDebugs; KeyUserDebugs.debugMessageCnt++; tfp_printf(__VA_ARGS__)  // Informational
#define w_printf(...) tfp_printf("W: "); extern KeyUserDebug KeyUserDebugs; KeyUserDebugs.debugMessageCnt++; tfp_printf(__VA_ARGS__)  // Warning
#define e_printf(...) tfp_printf("E: "); extern KeyUserDebug KeyUserDebugs; KeyUserDebugs.debugMessageCnt++; tfp_printf(__VA_ARGS__)  // Error

#endif



/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
