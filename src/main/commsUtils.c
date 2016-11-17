/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014 Sean Keys, David Andruczyk
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

#include "inc/commsUtils.h"
#include "inc/printf.h"
#include "inc/debugging.h"
#include "inc/dataLogDefinitions.h"
#include "inc/shared/libreExternalTypes.h"
#include "inc/tableLookup.h"
#include "inc/mathFunctions.h"


#define NUM_CHARS_IN_INT32  (10 + 2)  //Add potential sign and NULL terminator
#define BASE        10


const char *comma_quote = ",\"";
const char *quote_colon = "\":";
const char *quote = "\"";
const char *brace_quote = "{\"";
const char *quote_comma_quote = "\",\"";
const char *quote_colon_quote = "\":\"";

uint16_t verifyTableData(uint8_t ID, void *bufferToCheck, int16_t bufferLength) {

  uint16_t errorID = TABLE_FORMAT_NOT_FOUND; //TODO remove magic number use public def
    /* Find Field descriptor */
    uint8_t i;
    for (i = 0; i < tableDescriptorCnt; ++i) {
      if (ID == tableDescriptor[i].tableKey) {
        switch (tableDescriptor[i].formatID) {
        case TABLE_1D:
          errorID = TABLE_FORMAT_UNHANDLED;
          break;
        case TABLE_2D_STRUCTURED:
          // TODO we may want to consider a unique formatID
          if (tableDescriptor[i].tableKey ==  MAF_VS_VOLTAGE_TID) {
            errorID = verify16b32bAxis(bufferToCheck, (bufferLength / sizeof(TableEntryU1632)));
          } else {
            errorID = verify16b16bAxis(bufferToCheck, (bufferLength / sizeof(TableEntryINT16)));
          }
          break;
        case TABLE_3D:
          errorID = validateMainTable((mainTable*) bufferToCheck);
          break;
        default:
          errorID = TABLE_FORMAT_UNDEFINED;
          break;
        }
      }
    }

    return errorID;
}

/* TODO dox entries */
int stringLength(char *str) {
  int c = 0;
  while (*(str + c) != '\0') c++;
  return c;
}

void reverse(char *str) {
  uint16_t length, c;
  char *begin, *end, temp;

  length = stringLength(str);

  begin = str;
  end = str;

  for (c = 0; c < (length - 1); c++) end++;

  for (c = 0; c < length / 2; c++) {
    temp = *end;
    *end = *begin;
    *begin = temp;

    begin++;
    end--;
  }
}

char *integerToString(int32_t num, char *str){ //TODO maybe add other radix's

  char isNegative = FALSE;
  char *firstChar = str;

  /* Handle 0 */
  if (num == 0) {
    *(str)++ = '0';
    *str = '\0';
    return firstChar;
  }

  if (num < 0 && BASE == 10) {
    isNegative = TRUE;
    num = -num;
  }
  // Process digits
  while (num != 0) {
    int8_t rem = num % BASE;
    *(str)++ = (rem > 9)? (rem-10) + 'a' : rem + '0';
    num = num/BASE;
  }
  if (isNegative) {
    *(str)++ = '-';
  }

  *str = '\0'; //terminator

  // Reverse the string
  reverse(firstChar);

  return firstChar;
}


// Move as much data as we can to the TXBuffer without over-running it
char *payloadStrCat(char * dest, const char * src) {
  if (dest == 0) {
    return 0;
  }
  while(*src != '\0'){
    /* if we are not over-running our buffer copy data */
    if((uint16_t)dest - (uint16_t)(&(TXBuffer[0])) < TX_PAYLOAD_SIZE){
      *(dest++) = *(src++);
    } else{
      return 0;
    }
  }
  return dest;
}

// Move as much data as we can to the TXBuffer without over-running it
char *payloadStrCat_paged(uint8_t src_page, char *dest, const char *src) {
  uint8_t orig_page = PPAGE;
  if (dest == 0) {
    return 0;
  }
  PPAGE = src_page;
  while(*src != '\0'){
    /* if we are not over-running our buffer copy data */
    if((uint16_t)dest - (uint16_t)(&(TXBuffer[0])) < TX_PAYLOAD_SIZE){
      *(dest++) = *(src++);
    } else{
      PPAGE = orig_page;;
      return 0;
    }
  }
  PPAGE = orig_page;;
  return dest;
}


/* TODO we only need one header creation function, combine these */

char *addJSONHeader(JSONHeaderType header_type, char *TXBufferPosition) {
  switch (header_type){
    case DATALOG:
      if(!(TXBufferPosition = payloadStrCat(TXBufferPosition, "{\"id\":\"0001\",\"name\":\"JSON DataLog Descriptor\",\"descriptor\":["))) return 0;
      break;
    case FIELD_DESCRIPTOR:
      if(!(TXBufferPosition = payloadStrCat(TXBufferPosition, "{\"id\":\"0002\",\"name\":\"JSON Field Descriptor\",\"descriptor\":["))) return 0;
      break;
    case TABLE_DESCRIPTOR:
      if(!(TXBufferPosition = payloadStrCat(TXBufferPosition, "{\"id\":\"0003\",\"name\":\"JSON Table Descriptor\",\"descriptor\":["))) return 0;
      break;
    default:
      e_printf("In addJSONHeader(), header_type undefined\n");
      break;
  }
  return TXBufferPosition;
}

char *addJSONFooter(char *TXBufferPostion) {
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "]}"))) return 0;

    return TXBufferPostion;
}


char *addJSONdataLogRecord(char *TXBufferPostion, const dataBlockDescriptor *descriptorPTR, uint16_t baseOffset, descriptorPages pages) {
  char str[NUM_CHARS_IN_INT32] = {0};

  /* Find Field descriptor */
  uint8_t i;
  for (i = 0; i < fieldDescriptorCnt; ++i) {
    if (fieldDescriptor[i].ID == descriptorPTR->ID) {
      break;
    }
  }

  /* Set default size to 16 */
  uint8_t size = fieldDescriptor[i].bitsize;
  if (size == 0) {
    size = sizeof(uint16_t) * 8;
  }

  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "{\"start"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->start + baseOffset, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "size"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(size, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "is_signed"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(fieldDescriptor[i].isSigned, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "name"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  /* Get name */
  if (descriptorPTR->name == USE_FIELD_DESC) {
    if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_NAME_PAGE,TXBufferPostion, fieldDescriptor[i].name))) return 0;
  }else {
    if(!(TXBufferPostion = payloadStrCat_paged(pages.base_name_page,TXBufferPostion, descriptorPTR->name))) return 0;
  }

  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "description"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  /* Get Description */
  if (descriptorPTR->description == USE_FIELD_DESC) {
    if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_DESC_PAGE,TXBufferPostion, fieldDescriptor[i].description))) return 0;
  }else {
    if(!(TXBufferPostion = payloadStrCat_paged(pages.base_desc_page,TXBufferPostion, descriptorPTR->description))) return 0;
  }

  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "multiplier"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE,TXBufferPostion, fieldDescriptor[i].multiplier))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "adder"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE,TXBufferPostion, fieldDescriptor[i].adder))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "flags"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE,TXBufferPostion, fieldDescriptor[i].flags))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "suffix"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE,TXBufferPostion, fieldDescriptor[i].suffix))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote))) return 0;

  uint8_t addedBitfield = 0;
  uint8_t j = size;

  if(!(j > MAX_NUM_BFD)) { /* make sure we are within range */
    while (j) {
      --j;
      if (fieldDescriptor[i].bitFieldDescription[j].fieldName != (void *)0) {
        if (!addedBitfield) {
          addedBitfield = 1;
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "bitFieldDescriptor"))) return 0;
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "["))) return 0;
        }
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, brace_quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "bitFieldDescription"))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE,TXBufferPostion, fieldDescriptor[i].bitFieldDescription[j].fieldName))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "bitFieldPosition"))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(fieldDescriptor[i].bitFieldDescription[j].bitPosition, str)))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "}"))) return 0;
        if (j) {
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, ","))) return 0;
        }
      }
    }
  }

  if(addedBitfield) if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "]"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "}"))) return 0;
  return TXBufferPostion;
}


char *addJSONfieldDescriptor(char *TXBufferPostion, const FieldDescriptor *descriptorPTR) {
  char str[NUM_CHARS_IN_INT32] = {0};

  /* Set default size to 16 */
  uint8_t size = descriptorPTR->bitsize;
  if (size == 0) {
    size = sizeof(uint16_t) * 8;
  }

  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "{\"id"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->ID, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "size"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(size, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "is_signed"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->isSigned, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "name"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_NAME_PAGE, TXBufferPostion, descriptorPTR->name))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "description"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_DESC_PAGE, TXBufferPostion, descriptorPTR->description))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "multiplier"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE, TXBufferPostion, descriptorPTR->multiplier))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "adder"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE, TXBufferPostion, descriptorPTR->adder))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "flags"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE, TXBufferPostion, descriptorPTR->flags))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "suffix"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE, TXBufferPostion, descriptorPTR->suffix))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote))) return 0;

  uint8_t addedBitfield = 0;
  uint8_t i = size;

  if(!(i > MAX_NUM_BFD)) { /* make sure we are within range */
    while (i) {
      --i;
      if (descriptorPTR->bitFieldDescription[i].fieldName != (void *)0) {
        if (!addedBitfield) {
          addedBitfield = 1;
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "bitFieldDescriptor"))) return 0;
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "["))) return 0;
        }
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, brace_quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "bitFieldDescription"))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE, TXBufferPostion, descriptorPTR->bitFieldDescription[i].fieldName))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "bitFieldPosition"))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat_paged(FD_STATIC_MISC_PAGE, TXBufferPostion, integerToString(descriptorPTR->bitFieldDescription[i].bitPosition, str)))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote))) return 0;
        if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "}"))) return 0;
        if (i) {
          if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, ","))) return 0;
        }
      }
    }
  }

  if(addedBitfield) if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "]"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "}"))) return 0;
  return TXBufferPostion;
}

char *addJSONtableDescriptor(char *TXBufferPostion, const TableDescriptor *descriptorPTR) {
  char str[NUM_CHARS_IN_INT32] = {0};


  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "{\"id"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->tableKey, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "name"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(TD_STATIC_NAME_PAGE, TXBufferPostion, descriptorPTR->tableName))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "description"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat_paged(TD_STATIC_DESC_PAGE, TXBufferPostion, descriptorPTR->tableDesc))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "format_id"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->formatID, str)))) return 0;

  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "xAxisID"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->xAxisID, str)))) return 0;

  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "xHighLightID"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->xHighLightID, str)))) return 0;

  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "yHighLightID"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->yHighLightID, str)))) return 0;

  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "yAxisID"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->yAxisID, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, comma_quote))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "lookupID"))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, quote_colon))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, integerToString(descriptorPTR->lookupID, str)))) return 0;
  if(!(TXBufferPostion = payloadStrCat(TXBufferPostion, "}"))) return 0;
  return TXBufferPostion;
}


uint16_t buildCANqueue(CANconfig *CANconfig, CANqueue *queue) {
  uint16_t i;
  uint16_t j = 0;
    uint8_t  k = 0;

  uint16_t numDescriptors = 
    KeyUserVarsDescriptorCnt + 
    derivedVarsDescriptorCnt +
    coreVarsDescriptorCnt    + 
    DecoderStatsDescriptorCnt;

  /* Get pointer to the first descriptor */
  const dataBlockDescriptor *descriptorBase = &coreVarsDescriptor[0];

  for (i = 0; i < MAX_CAN_QUEUE; ++i) {

    /* Check for non zero CAN ID */
    if (CANconfig[i].CANid) {
      /* Find descriptor */
      for (j = 0; j < numDescriptors; ++j){
        if (CANconfig[i].CANid == descriptorBase[j].CANid) {
          break;
        }
      }
    } else {
      continue;
    }

    if (j < numDescriptors) {
      uint16_t id = descriptorBase[j].CANid;
      uint16_t MSB = (id >> 3) & 0xFF;
      uint8_t  LSB = (id << 5) & 0xFF;

      queue[k].ID = (MSB << 8) + LSB;

      queue[k].dataPTR = descriptorBase[j].varAddress;

      /* Find Field descriptor */
      uint8_t l;
      for (l = 0; l < fieldDescriptorCnt; ++l) {
        if (fieldDescriptor[l].ID == descriptorBase[j].ID) {
          break;
        }
      }

      /* Load a bit to describe each size */
      switch (fieldDescriptor[l].bitsize) {
        case 0: queue[k].dataLen = 1;         /* ID only */
          break;
        case 8: queue[k].dataLen = (1 << 1);  /* 8 Bits */
          break;
        case 16: queue[k].dataLen = (1 << 2);  /* 16 Bits */
          break;
        case 32: queue[k].dataLen = (1 << 3);  /* 32 Bits */
          break;
        default: queue[k].dataLen = 0;        /* Invalid */
          break;
      }

      queue[k].dataLen = fieldDescriptor[l].bitsize;

      queue[k].priorityID = CANconfig[i].TXrateMs;
      queue[k].timeLeft = k * 4; /* stagger the message schedules */
      ++k;
    }
  }

  /* Clear the rest of the queue, so XGate does not try to process them */
  for (i = k; i < MAX_CAN_QUEUE; ++i) {
    queue[i].ID = 0;
  }

  return k;
}

/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
