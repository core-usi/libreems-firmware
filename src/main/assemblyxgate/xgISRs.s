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
 * @brief
 *
 *                                                General Pricipal Of Operation:
*######################################################################################################################################################
*#    Time markers shown below were based on the scheduler running at marker S and plotting two output PWs(could be fuel or ign). The first event is at
*#    0xD6D8 and the action is to go high. The second event is H2 and the actaion again is to go high. The third event is L1 and the action is to go
*#    low. Finally the fourth event is L2 and the action is to go low. That gives us two pulse widths on two seperate channels of:
*#                    5,000 ticks(L1 - H1) or 4mS(5,000/800nS)    and  8,815 ticks(L2 - H2) or 7.052mS(8,815/800ns)
*#
*#     L2                                                                             S        T                    H1      H2            L1
*# 0 --|------------------------------------------------------------------------------|--------|--------------------|-------|-------------|--- 0xFFFF
*#    0x500                                                                           0x9C40   0xAFC8             0xD6D8   0xE290        0xEA60
*#                                                                                    40,000   45,000             55,000   58,000        60,000
*#
*#######################################################################################################################################################
 */

/* @defgroup xgateThreads */

/**
 * @cond DOXYGEN_IGNORE_ASM
*/


.sect .ppageE1 ;FIXME since we are running XG code out of ram we should not burn XG flash space as load storage

include "assemblyxgate/xgate.inc"

.equ nextDelayMax, 0x8000
.equ CAN0CTL0, 0x0140

;See Xgate init code addresses need to match what is goin on there !
.equ startOfCAN, (0x9000 + 0x200)

startXGATECode:

;Static Vars
CANptr:
  .word startOfCAN

xgTC2ISRVars:
  .word 0 ; ISR Start Stamp
  .word 0 ; Next Delay
  .word 0 ; flags
  .word 0 ; Current TCNT

.equ ISRStartStampOFST, 0x00
.equ nextDelayOFST, 0x02

.equ lastISRStampOFST, 0x08
.equ downCounterLowWordOFST, 0x06 

.equ rollOverIncFlag, 0x01
.equ rollOverIncFlag_Clear, 0xFE

;Software interrupt 0
swISR0:

  ;CIF
  LDW R7, SW_ISR_FLAG_REG
  LDW R6, SW_ISR_ZERO_CFLAG_MASK
  STW R6, (R7, #0)

; BRA SWISREntryPoint

;RTS

; Look for events that need to be bang and scheduled as next
TC4ISR:

  ;We can use the OC reg if we were called via interrupt
;  LDW R7, xgTC2ISRVars
;  LDL R6, #TC2_REG
;  LDW R6, (R6, #0)
;   BRA saveStartStamp

  ;We need to TCNT if we were called via software int
  SWISREntryPoint:

  ;Save start stamp TODO the better thing to do would be to use a captured time
  LDL R6, #TCNT_REG
  LDW R6, (R6, #0)
    
  saveStartStamp: ;Not required as long as we dont trash the contents of R6
  ;LDW R7, xgTC2ISRVars
  ;STW R6, (R7, ISRStartStampOFST) 

  LCKSEM:
  SSEM #2 ; try to lock semaphore
  BCC LCKSEM; retry until locked

  ;CIF //TODO we might be able to move this infront of the LCKSEM block
  LDL R7, #TFLG_REG
  LDL R5, (1 << 4)
  STB R5, (R7, #0)  
  
  ;Look for cocked events
  LDW R7, XGoutputEvents ;load address of our first event struct
; R6 still contains our start stamp
;  LDW R6, xgTC2ISRVars
;  LDW R6, (R7, ISRStartStampOFST)
  ;Default the next soonest to 0x8000
  LDW R5, nextDelayMax

  checkEventLoop:
    LDB R4, (R7, #0) ;load flags var
    BITL R4, COCKED_FLAG
      BEQ	loadNextEvent
    ;Elapsed time = (ISRStart(R6) - LastStamp)
    LDW R3, (R7, lastISRStampOFST) ;Load events last process stamp
    SUB R3, R6, R3 ;Calculate elapsed time, this should never overflow because we always use 0x8000 as our max delay.
    LDW R2, (R7, downCounterLowWordOFST)
    SUB R2, R2, R3 ; Subtract elapsed time from TTL count down.
      BHI storeTimeLeft ; If elapsed time is less than the count down store the new countdown value, else bang event 
    ;Else bang event
    bangEvent:
    LDW R3, (R7, #2)  ;Load bang register address; If we stick to 8-bit addressable ports we can use only a LDL
    LDB R2, (R7, #1)  ;Load bang mask
    LDB R1, (R3, #0)  ;Load current register data
    BITL R4, GO_HIGH_BIT
	  BEQ	 applyLowMask
    OR  R1, R1, R2   ;Apply High mask
    BRA hitRegister
    applyLowMask:
    AND R1, R1, R2 ;Apply Low mask
    hitRegister:
    STB R1, (R3, #0) ;Write new value
    ;If we were a high event that went off, we need to cock the low
    BITL R4, GO_HIGH_BIT
	  BEQ  clearEventFlags
    enableGoLowCountDown:
    LDB R3, (R7, #sizeOfEventStruct) ;If this was a high event reach out to the next array member and cock the low action
    ORL R3, COCKED_FLAG
    STB R3, (R7, #sizeOfEventStruct)
    STW R6, (R7, sizeOfEventStruct + lastISRStampOFST) ;Reach out and write our TCNT time into the lastStamp event variable
    ;Clear All Flags Except High/Low designation bit
    clearEventFlags:
    ANDL R4, #0x1C
    STB R4, (R7, #0)
      BRA loadNextEvent  
    storeTimeLeft:
    STW R2, (R7, downCounterLowWordOFST)
    STW R6, (R7, lastISRStampOFST)
    ;Check if event is the soonest
    checkIfSoonest:
    SUB R0, R5, R2
      BCS loadNextEvent
    MOV R5, R2 ;Update R5 with the new soonest value
  
  loadNextEvent:
  ADDL R7, #sizeOfEventStruct
  MOV R3, R7
  XGEventCountOpCode:
  SUB R3, (numEvents * sizeOfEventStruct + XGoutputEvents)
    BNE checkEventLoop
  
  ;Check to make sure we dont have an event that expired while we were running this ISR
  LDL R7, TCNT_REG
  LDW R7, (R7, #0)
  SUB R4, R7, R6 ; R4 Now contains the amount of time this ISR has run so far
  ADDL R4, #1 ;Saftey factor incase we were on an edge
  SUB R4, R5, R4  
    BCS SWISREntryPoint
  
  ;Set new OC value
  LDL R4, #TC4_REG
  ADD R6, R6, R5   ;new OC time is startStamp + soonest event
  STW R6, (R4, #0)
    
  CSEM #2 ;Release semaphore

RTS

;PIT 0 interrupt 0
PIT0:

;LDL R1, 1
;LDL R2, 0xF
;STB R2, (R1, 0)
  ;Get struct pointer
  LDW R7, CANptr
  LDW R6, R7, #0

  ;Check to see if we have a valid ID
  LDW R5, (R6, #4)
  TST R5
   BEQ prepNextEvent

  ;Load TimeLeft of Event
  LDB R4, (R6, #0)

  ;Subtract elapsed interval
  SUBL R4, 1
    BHI timeLeft
  ;Check Sync
  LDW R4, CAN0CTL0           ;Load CAN0 Control Register
  LDB R3, (R4, 0)
  BITL R3, 16
   BEQ returnNoCIF           ;Return but do not clear int flag
  LDB R3, (R4, 6)            ;Check for an empty TX buffer
  BITL R3, 1
    BNE foundEmptyBuffer0
  BITL R3, 2
    BNE foundEmptyBuffer1
  BITL R3, 4
    BNE foundEmptyBuffer2
  RTS                        ;Nothing found, just return and retry

  foundEmptyBuffer0:
  LDL R3, 1
  BRA selTXBuffer
  foundEmptyBuffer1:
  LDL R3, 2
  BRA selTXBuffer
  foundEmptyBuffer2:
  LDL R3, 2

  selTXBuffer:       	;CAN->TBSEL = (0x01 << TXbufEmpty);
  STB R3, (R4, 10)

  loadID:
  MOV R3, R4
  ADDL R3, 30           ;Create a new pointer since we are out of range of R4
  ;Preformatted by init()
  STW R5, (R3, 18)

  ;Load data to CAN TX register
  LDB R5, (R6, 4)       ;Get length from queue
  STB R5, (R3, 30)      ;Set Length
  LDL R1, 0             ;FIXME get priority from queue
  STB R1, (R3, 31)      ;Set Priority

  BITL R5, 1            ;ID only
    BNE send
  ;else load data pointer
  LDW R5, (R6, 2)       ;Load Data pointer
  BITL R5, 2            ; 8-bits
    BNE load8Bits:
  BITL R5, 4            ; 16-bits
    BNE load16Bits:
  BITL R5, 8            ; 32-bits
    BNE load32Bits:

  load8Bits:
  LDB R5, (R5, 0)
  STB R5, (R3, 22)
  BRA send

  load16Bits:
  LDW R5, (R5, 0)
  STW R5, (R3, 0)
  BRA send

  load32Bits:
  LDW R5, (R5, 0)
  STW R5, (R3, 0)
  LDW R5, (R5, 2)
  STW R5, (R3, 2)
  BRA send

  BRA resetInterval     ;Unhandled size, just skip

  send:
  LDB R3, (R4, 10)      ;TODO see if we can drop this reload
  STB R3, (R4, 6)       ;Send same ch bit as the empty buffer

  ;Reset interval counter
  resetInterval:
  LDB R3, (R6, 1)
  STB R3, (R6, 0)

  BRA prepNextEvent

  ;Save elapsed time
  timeLeft:
  STB R4, (R6, #0)
  ;Advance CAN queue pointer
  prepNextEvent:
  ADDL R6, 8 ;Size of CAN struct
  LDW  R5, (startOfCAN + (8 * (50 - 1)))
  SUB R0, R6, R5
  STW R6, (R7, #0)     ;save pointer
    BCS returnNoCIF

  ;If pointer needs to be rolled over, do so and clear CIF
  LDW R6, startOfCAN
  STW R6, (R7, #0)

  ;CIF
  LDL R2, #PIT0_CFLAG_MASK
  LDW R3, #PITTF
  STB R2, (R3, #0)
  RTS

returnNoCIF:
;debug
;LDL R1, 1
;LDL R2, 0
;STB R2, (R1, 0)
;end debug
RTS

endXGATECode:
.ascii "Libre, because free is a four letter word"
end

/**
 * @endcond DOXYGEN_IGNORE_ASM
*/
