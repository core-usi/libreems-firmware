/* LibreEMS - the community driven open source engine management system
 *
 * Copyright 2014 Sean Keys, David J. Andruczyk
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

#ifndef FILE_DATALOGDEFINITIONS_H_SEEN
#define FILE_DATALOGDEFINITIONS_H_SEEN

#include "libreTypes.h"

#define MAX_NUM_BFD      16   /* Maximum number of bit field descriptors(16-bit machine) */
#define USE_FIELD_DESC   0


typedef struct {
  const int8_t *fieldName;
  uint8_t bitPosition;
}bitFieldDescriptor;

typedef struct {
  uint16_t start;         /* Starting byte number in the log stream */
  uint16_t CANid;         /* Can descriptor/config */
  void     *varAddress;   /* must be in shared mem space */
  uint8_t  ID;            /* Datalog field ID */
  const char *name;       /* ShortName */
  const char *description;/* Detailed Description */
} dataBlockDescriptor;

typedef struct {
  bitFieldDescriptor bitFieldDescription[MAX_NUM_BFD]; /* Description of each bit in the variable */
  uint8_t ID;
  uint8_t bitsize;                  /* Number of bits comprising the data */
  uint8_t isSigned;                 /* Signed or unsigned data */
  const char *name;                 /* Short name */
  const char *multiplier;           /* Suggested multiplier */
  const char *adder;                /* Suggested adder */
  const char *flags;                /* Textual flags to give the tuner hints */
  const char *suffix;               /* Tuner side suffix for this variable */
  const char *description;          /* Brief description */
}FieldDescriptor;

typedef struct {
  uint8_t tableKey;
  uint8_t xAxisID;
  uint8_t xHighLightID;
  uint8_t yAxisID;
  uint8_t yHighLightID;
  uint8_t lookupID;
  uint8_t formatID;
  const char *tableName;
  const char *tableDesc;
}TableDescriptor;

extern const FieldDescriptor     fieldDescriptor[];
extern const TableDescriptor     tableDescriptor[];

extern const dataBlockDescriptor coreVarsDescriptor[];
extern const dataBlockDescriptor derivedVarsDescriptor[];
extern const dataBlockDescriptor KeyUserVarsDescriptor[];
extern const dataBlockDescriptor DecoderStatsDescriptor[];
extern const dataBlockDescriptor generalPurproseInputsDescriptor[];

extern const uint8_t tableDescriptorCnt;
extern const uint8_t fieldDescriptorCnt;

extern const uint8_t coreVarsDescriptorCnt;
extern const uint8_t derivedVarsDescriptorCnt;
extern const uint8_t KeyUserVarsDescriptorCnt;
extern const uint8_t DecoderStatsDescriptorCnt;
extern const uint8_t gpInputDescriptorCnt;

#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
