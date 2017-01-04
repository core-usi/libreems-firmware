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

#ifndef FILE_LIBRETYPES_H_SEEN
#define FILE_LIBRETYPES_H_SEEN

#include <stdint.h>

typedef struct {
  uint16_t sendDisplayData :1;
  uint16_t res1            :1;
  uint16_t res2            :1;
  uint16_t res3            :1;
  uint16_t res4            :1;
  uint16_t res5            :1;
  uint16_t res6            :1;
  uint16_t res7            :1;
  uint16_t res8            :1;
  uint16_t res9            :1;
  uint16_t res10           :1;
  uint16_t res11           :1;
  uint16_t res12           :1;
  uint16_t res13           :1;
  uint16_t res14           :1;
  uint16_t res15           :1;
}CANflags;

typedef struct {
  uint16_t IAT_fault      :1;
  uint16_t CLT_fault      :1;
  uint16_t MAP_fault      :1;
  uint16_t AAP_fault      :1;
  uint16_t MAF_fault      :1;
  uint16_t TPS_fault      :1;
  uint16_t EGT_fault      :1;
  uint16_t EGO_fault      :1;
  uint16_t Crank_PS_fault :1;
  uint16_t Cam_PS_fault   :1;
  uint16_t res10           :1;
  uint16_t res11           :1;
  uint16_t res12           :1;
  uint16_t res13           :1;
  uint16_t res14           :1;
  uint16_t res15           :1;
}SensorFaults;

typedef union {
  uint32_t time;
  uint16_t timeWord[2];
}ExtendedTime;

#define DEGREE_TICKS_PER_MINUTE 4166667u

typedef struct {
  uint8_t res                         : 2;
  uint8_t previousSecondaryEventValid : 1;
  uint8_t primaryPeriodValid          : 1;
  uint8_t previousPrimaryEventValid   : 1;
  uint8_t phaseLock                   : 1;
  uint8_t crankLock                   : 1;
  uint8_t minimalSync                 : 1;
}DecoderFlagBits;

typedef union {
  DecoderFlagBits bits;
  uint8_t         var;
}DecoderFlags;

typedef struct {
  ExtendedTime lastPrimaryTimeStamp;
  uint16_t     decoderResetCalls;
  uint16_t     primaryTeethSeen;
  uint16_t     secondaryTeethSeen;
  uint16_t     instantTicksPerDegree;
  uint16_t     primaryInputVariance;
  uint16_t     syncADCsamples;
  uint16_t     RPM;
  uint16_t     debug_16b;
  DecoderFlags decoderFlags;
  uint8_t      currentPrimaryEvent;
  uint8_t      lockLossCauseID;
  uint8_t      requiredSyncCycles;
  uint8_t      eventLockWasLost;
  uint8_t      padding;
}DecoderStats;

typedef enum {
  PRIMARY_EVENT_TOO_SOON         = 1,
  PRIMARY_EVENT_TOO_LATE         = 2,
  SECONDARY_EVENT_TOO_SOON       = 3,
  SECONDARY_EVENT_TOO_LATE       = 4,
  PRIMARY_EVENT_COUNT_TOO_HIGH   = 5,
  PRIMARY_EVENT_COUNT_TOO_LOW    = 6,
  SELF_CLOCK_MODE                = 7,
  PLL_LOCK_LOST                  = 8,
  PRIMARY_INPUT_TIMEOUT          = 9,
  PRIMARY_INPUT_DEAD             = 10,
  PRIMARY_EVENT_TOO_SOON_UNSYNC  = 11,
  PRIMARY_EVENT_TOO_LATE_UNSYNC  = 12,
  PRIMARY_EVENT_TOO_FEW_TEETH_TO_SYNC =  13,
  FALSE_CRANK_SYNC                    =  14

}DecoderResetCodes;

typedef struct {
  uint8_t  timeLeft;
  uint8_t  priorityID;
  void     *dataPTR;
  uint16_t ID;
  uint8_t  dataLen;
  uint8_t  reserved;
}CANqueue;

typedef struct {
  uint16_t CANid;
  uint8_t  TXrateMs; /* Rate in timer ti1cks */
}CANconfig;

typedef struct {
  //MSB
  uint8_t reserved         : 2;
  uint8_t setINITTAKfirst  : 1;
  uint8_t setINITTAKSecond : 1;
  uint8_t setSync          : 1;
  uint8_t INITAKfirst      : 1;
  uint8_t INITAKsecond     : 1;
  uint8_t synced           : 1;
}CANbusStatus;

typedef union {
  uint16_t countHL[2];  /* This is essentially the roll-over counter */
  uint32_t countDown32;
} counter32;

typedef struct {
  uint8_t actionBits;     /* Flags for various states */
  uint8_t regMask;
    uint16_t regAddress;
  counter32 downCounter;  /* RAM variable containing a TTL countdown value */
  uint16_t lastRunStamp;  /* variable containing the last TCNT stamp */
} outputAction;

typedef struct {
  outputAction goHigh;
  outputAction goLow;
} XGoutputEvent;

typedef struct {
  uint16_t IAP;       /* Intercooler Absolute Pressure */
  uint16_t MAF;       /* Mass Air Flow */
  uint16_t TPS;       /* Throttle Position Sensor */
  uint16_t EGO;       /* Exhaust Gas Oxygen */
  uint16_t MAP;       /* Manifold Absolute Pressure */
  uint16_t TPD;       /* Ticks per degree */
  uint16_t previousFuelRequirement; /* Recording of last fueling amount */
}SyncedData;

typedef struct {
  uint16_t  startAngle;       /* where we start an event */
  int16_t   startAngleOffset; /* angle correction(eg knock retard) */
  counter32 countDown;        /* How long until we fire */
  uint16_t  runTime;          /* how long we run, eg dwell or PW */
  int16_t   runTimeOffset;    /* fuel or dwell trim */
  uint8_t   updateOnEvent;    /* The input number where we perform output updates */
  uint8_t   eventFlags;       /* configs related to this channel */
  uint16_t  nextStartAngle;   /* This gives us a way to support safe async angle updates */
} outputEvent;

typedef struct {
  uint16_t capturedAngleHigh;   /* Captured edge */
  uint16_t capturedAngleLow;   /* Captured edge */
  uint16_t periodHighTicks; /* Pulse Width in microseconds */
  uint16_t periodLowTicks;  /* ditto^ except measuring low time */
  uint16_t frequencyHz;     /* Frequency */
  uint16_t ISRcount;        /* Number of events captured */
}CapturedInputData;

typedef struct {
  uint32_t delay;
  uint16_t runtime;
  uint16_t testInterval;
  uint16_t simulatedTCNT;
  uint8_t numberOfEvents;
  uint8_t channel;
  uint8_t testID;
} BTpatternParameters;

/* TODO this needs to be combined with derivedVars */
typedef struct {
//  uint16_t stoichAFR;
//  uint16_t densityGcc; /* density in grams per cc */
  uint16_t primaryInjFlow;
  uint16_t secondaryInjFlow;
//  uint16_t cylinderDisplacement;
}fuelAttributes;

typedef struct {
  uint8_t cylinderCount;
  uint16_t decodersMechanicalOffset;
//  uint16_t
}Configuration;

typedef struct {
  SyncedData *syncedEngineData;
  outputEvent *igntionEvent;
  outputEvent *primaryFuelEvent;
  outputEvent *secondaryFuelEvent;
  uint16_t TDCAngle;
  uint16_t ReadAngle;
  uint16_t InjectionAngle;
}CylinderConfig;

typedef struct {
  uint16_t lookup;
  int16_t  scalar;
}TableEntryINT16;

typedef struct {
  uint16_t lookup;
  uint16_t  scalar;
}TableEntryUINT16;

typedef struct {
  uint16_t lookup;
  uint32_t scalar;
}TableEntryU1632;


#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
