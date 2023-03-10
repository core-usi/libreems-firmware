/*
 * File: printf.c
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
 */

/** @file
 *
 * @ingroup debugging 
 * @brief Tiny printf() implementation
 *
 * Tiny (low flash/ram) printf implementation from 
 * http://www.sparetimelabs.com/printfrevisited/printfrevisited.php
 */

#include "inc/printf.h"
#include "inc/debugging.h"


char* tpf_bf;
char tpf_buf[12];
unsigned int tpf_num;
char tpf_uc;
char tpf_zs;

void out(char c) {
    *tpf_bf++ = c;
    }

void outDgt(char dgt) {
  out(dgt+(dgt<10 ? '0' : (tpf_uc ? 'A' : 'a')-10));
  tpf_zs=1;
    }
  
void divOut(unsigned int div) {
    uint8_t dgt=0;
  tpf_num &= 0xffff; // just for testing the code  with 32 bit ints
  while (tpf_num>=div) {
    tpf_num -= div;
    dgt++;
    }
  if (tpf_zs || dgt>0) 
    outDgt(dgt);
    } 

void tfp_printf(char *fmt, ...) {
  va_list va;
  char ch;
  char* p;
  
  va_start(va,fmt);
  
  while ((ch=*(fmt++))) {
    if (ch!='%') {
      dbg_push(ch);
      }
    else {
      char lz=0;
      char w=0;
      ch=*(fmt++);
      if (ch=='0') {
        ch=*(fmt++);
        lz=1;
        }
      if (ch>='0' && ch<='9') {
        w=0;
        while (ch>='0' && ch<='9') {
          w=(((w<<2)+w)<<1)+ch-'0';
          ch=*fmt++;
          }
        }
      tpf_bf=tpf_buf;
      p=tpf_bf;
      tpf_zs=0;
      switch (ch) {
        case 0: 
          goto abort;
        case 'u':
        case 'd' : 
          tpf_num=va_arg(va, unsigned int);
          if (ch=='d' && (int)tpf_num<0) {
            tpf_num = -(int)tpf_num;
            out('-');
            }
          divOut(10000);
          divOut(1000);
          divOut(100);
          divOut(10);
          outDgt(tpf_num);
          break;
        case 'x': 
        case 'X' : 
            tpf_uc= ch=='X';
          tpf_num=va_arg(va, unsigned int);
          divOut(0x1000);
          divOut(0x100);
          divOut(0x10);
          outDgt(tpf_num);
          break;
        case 'c' : 
          out((char)(va_arg(va, int)));
          break;
        case 's' : 
          p=va_arg(va, char*);
          break;
        case '%' :
          out('%');
        default:
          break;
        }
      *tpf_bf=0;
      tpf_bf=p;
      while (*tpf_bf++ && w > 0)
        w--;
      while (w-- > 0) 
        dbg_push(lz ? '0' : ' ');
      while ((ch= *p++))
        dbg_push(ch);
      }
    }
  abort:;
  va_end(va);
  }

/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
