/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014-2016 Sean Keys, David Andruczyk
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
 * @brief Utilities to facilitate communications.
 *
 *
 */

#ifndef DATA_COMMSUTILS_H_SEEN
#define DATA_COMMSUTILS_H_SEEN

#include "freeEMS.h"

typedef enum {
  DATALOG,
  FIELD_DESCRIPTOR,
  TABLE_DESCRIPTOR,
  MAX_JSON_HEADER_TYPES,
}JSONHeaderType;

int stringLength(char *str) FPPAGE_E6;
void reverse(char *str) FPPAGE_E6;
char *integerToString(int32_t num, char *str) FPPAGE_E6;
char *payloadStrCat(char *, const char *) FPPAGE_E6;
char *payloadStrCat_paged(uint8_t, char *, const char *) TEXT;
char *addJSONHeader(JSONHeaderType, char *) FPPAGE_E6;
char *addJSONFooter(char *) FPPAGE_E6;
char *addJSONdataLogRecord(char *TXBufferPostion, const dataBlockDescriptor *descriptorPTR, uint16_t baseOffset, descriptorPages pages) FPPAGE_E6; //FIXME revise linker etc for use with far attribute or keep as an alternative example...
char *addJSONfieldDescriptor(char *TXBufferPostion, const FieldDescriptor *descriptorPTR) FPPAGE_E6;
char *addJSONtableDescriptor(char *TXBufferPostion, const TableDescriptor *descriptorPTR) FPPAGE_E6;

uint16_t buildCANqueue(CANconfig *CANconfig, CANqueue *queue) FPPAGE_E6;
uint16_t verifyTableData(uint8_t ID, void *bufferToCheck, int16_t bufferLength) FPPAGE_E6;

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
