/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup allHeaders
 * @ingroup globalHeaders
 * @ingroup dataStructures
 *
 * @brief Compile time checks on types
 *
 * This file contains checks on sizes of various structs.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_TYPE_CHECKS_H_SEEN
#define FILE_TYPE_CHECKS_H_SEEN

#include "libreMath.h"
#include "libreTypes.h"

/** A compile time assertion check.
 *
 * Validate at compile time that the predicate is true without
 * generating code. This can be used at any point in a source file
 * where typedef is legal.
 *
 * On success, compilation proceeds normally.
 *
 * On failure, attempts to typedef an array type of negative size. The
 * offending line will look like
 *     typedef assertion_failed_file_h_42[-1]
 * where file is the content of the second parameter which should
 * typically be related in some obvious way to the containing file
 * name, 42 is the line number in the file on which the assertion
 * appears, and -1 is the result of a calculation based on the
 * predicate failing.
 *
 * @param predicate The predicate to test. It must evaluate to
 * something that can be coerced to a normal C boolean.
 *
 * @param file A sequence of legal identifier characters that should
 * uniquely identify the source file in which this condition appears.
 */
#define C_ASSERT(predicate, file) _impl_CASSERT_LINE(predicate,__LINE__,file)
#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1];


#ifndef HOST_TESTS

// Things with specific sizes:
C_ASSERT(sizeof(Flaggable) == 16, Flaggable)
C_ASSERT(sizeof(ADCBuffer)  == 32, ADCBuffer)
C_ASSERT(sizeof(mainTable) == FLASHSECTORSIZE, mainTable)
C_ASSERT(sizeof(cutEnabled) == 2, cutEnabled)
C_ASSERT(sizeof(ignitionCutFlags) == 1, ignitionCutFlags)
C_ASSERT(sizeof(injectionCutFlags) == 1, injectionCutFlags)

// Short alignment checks:
C_ASSERT((sizeof(Clock) % 2) == 0, Clock)
C_ASSERT((sizeof(Counter) % 2) == 0, Counter)
C_ASSERT((sizeof(CoreVar) % 2) == 0, CoreVar)
C_ASSERT((sizeof(DerivedVar) % 2) == 0, DerivedVar)
C_ASSERT((sizeof(DecoderStats) % 2) == 0, DecoderStats)
C_ASSERT((sizeof(KeyUserDebug) % 2) == 0, KeyUserDebug)

// Flash block alignment checks:
C_ASSERT((sizeof(SmallTables1) == FLASHSECTORSIZE), SmallTables1)
C_ASSERT((sizeof(SmallTables2) == FLASHSECTORSIZE), SmallTables2)
C_ASSERT((sizeof(SmallTables3) == FLASHSECTORSIZE), SmallTables3)
C_ASSERT((sizeof(SmallTables4) == FLASHSECTORSIZE), SmallTables4)

//CASSERT((sizeof(fixedConfig1) == FLASHSECTORSIZE), fixedConfig1)
//CASSERT((sizeof(fixedConfig2) == FLASHSECTORSIZE), fixedConfig2)

// Check the fixed point readability macros for correct behaviour
C_ASSERT(KPA(655.36) > SHORTMAX, PRESSURE)          // Overflow gets caught
C_ASSERT(KPA(655.35) == SHORTMAX, PRESSURE)         // Centre == max
C_ASSERT(KPA(655.3450000000) == SHORTMAX, PRESSURE) // Lowest to round up
C_ASSERT(KPA(655.3549999999) == SHORTMAX, PRESSURE) // Highest to round down

C_ASSERT(DEGREES_K(655.36) > SHORTMAX, TEMPERATURE_K)          // Overflow gets caught
C_ASSERT(DEGREES_K(655.35) == SHORTMAX, TEMPERATURE_K)         // Centre == max
C_ASSERT(DEGREES_K(655.3450000000) == SHORTMAX, TEMPERATURE_K) // Lowest to round up
C_ASSERT(DEGREES_K(655.3549999999) == SHORTMAX, TEMPERATURE_K) // Highest to round down

C_ASSERT(CC_PER_MINUTE(3840) > SHORTMAX, INJECTOR_FLOW)             // Overflow gets caught
C_ASSERT(CC_PER_MINUTE(3839.94140625) == SHORTMAX, INJECTOR_FLOW)   // Centre == max
C_ASSERT(CC_PER_MINUTE(3839.9701171875) == SHORTMAX, INJECTOR_FLOW) // Lowest to round up
C_ASSERT(CC_PER_MINUTE(3839.9121093750) == SHORTMAX, INJECTOR_FLOW) // Highest to round down

/* TODO reimpliment this */
//CASSERT(CC_VOLUME_S(2000) > SHORTMAX, CYL_VOLUME)            // Overflow gets caught
//CASSERT(CYLINDER_VOLUME(1999.969482422) == SHORTMAX, CYL_VOLUME) // Centre == max
//CASSERT(CYLINDER_VOLUME(1999.954223633) == SHORTMAX, CYL_VOLUME) // Lowest to round up
//CASSERT(CYLINDER_VOLUME(1999.984740906) == SHORTMAX, CYL_VOLUME) // Highest to round down

C_ASSERT(VOLTS(65.536) > SHORTMAX, VOLTAGE)         // Overflow gets caught
C_ASSERT(VOLTS(65.535) == SHORTMAX, VOLTAGE)        // Centre == max
C_ASSERT(VOLTS(65.5345000001) == SHORTMAX, VOLTAGE) // Lowest to round up
C_ASSERT(VOLTS(65.5354999999) == SHORTMAX, VOLTAGE) // Highest to round down

//TODO complete
//CASSERT(ADC_VOLTS(5.03) > ADC_MAX_VALUE, ADC_VOLTAGE)         // Overflow gets caught
//CASSERT(ADC_VOLTS(5.02) == ADC_MAX_VALUE, ADC_VOLTAGE)         // Centre == max
//CASSERT(ADC_VOLTS(5.0250000001) == ADC_MAX_VALUE, ADC_VOLTAGE) // Lowest to round up
//CASSERT(ADC_VOLTS(5.0249999999) == ADC_MAX_VALUE, ADC_VOLTAGE) // Highest to round down

C_ASSERT(LAMBDA(2.0) > SHORTMAX, LAMBDA)          // Overflow gets caught
C_ASSERT(LAMBDA(1.999969482) == SHORTMAX, LAMBDA) // Centre == max
C_ASSERT(LAMBDA(1.999954224) == SHORTMAX, LAMBDA) // Lowest to round up
C_ASSERT(LAMBDA(1.999984741) == SHORTMAX, LAMBDA) // Highest to round down

C_ASSERT(RPM(32767.75) > SHORTMAX, RPM)           // Overflow gets caught
C_ASSERT(RPM(32767.5) == SHORTMAX, RPM)           // Centre == max
C_ASSERT(RPM(32767.25) == SHORTMAX, RPM)          // Lowest to round up
C_ASSERT(RPM(32767.74999999999) == SHORTMAX, RPM) // Highest to round down

//FIXME
//// Only used with values less than 720, overflows over 720 handled in the code
//CASSERT(ANGLE(1310.71) > SHORTMAX, ANGLE)          // Overflow gets caught
//CASSERT(ANGLE(1310.7) == SHORTMAX, ANGLE)          // Centre == max
//CASSERT(ANGLE(1310.69) == SHORTMAX, ANGLE)         // Lowest to round up
//CASSERT(ANGLE(1310.7099999999) == SHORTMAX, ANGLE) // Highest to round down

C_ASSERT(PW_MS(52.4284) > SHORTMAX, PW_MS)          // Overflow gets caught
C_ASSERT(PW_MS(52.428) == SHORTMAX, PW_MS)          // Centre == max
C_ASSERT(PW_MS(52.4276) == SHORTMAX, PW_MS)         // Lowest to round up
C_ASSERT(PW_MS(52.428399999999) == SHORTMAX, PW_MS) // Highest to round down

C_ASSERT(PERCENT(102.39921875) > SHORTMAX, PERCENT)  // Overflow gets caught
C_ASSERT(PERCENT(102.3984375) == SHORTMAX, PERCENT)  // Centre == max
C_ASSERT(PERCENT(102.39765625) == SHORTMAX, PERCENT) // Lowest to round up
C_ASSERT(PERCENT(102.39921874) == SHORTMAX, PERCENT) // Highest to round down

C_ASSERT(VE(127.9990234375) > SHORTMAX, VE)     // Overflow gets caught
C_ASSERT(VE(127.998046875) == SHORTMAX, VE)     // Centre == max
C_ASSERT(VE(127.9970703125) == SHORTMAX, VE)    // Lowest to round up
C_ASSERT(VE(127.9990234374999) == SHORTMAX, VE) // Highest to round down

C_ASSERT(W(399.996948242188) > SHORTMAX, WARMUP)  // Overflow gets caught
C_ASSERT(W(399.993896484375) == SHORTMAX, WARMUP) // Centre == max
C_ASSERT(W(399.990844726563) == SHORTMAX, WARMUP) // Lowest to round up
C_ASSERT(W(399.996948242187) == SHORTMAX, WARMUP) // Highest to round down

C_ASSERT(AP(29.4) > SHORTMAX, AFR) // Overflow gets caught
C_ASSERT(AP(14.7) == LR(1.0), AFR) // Matches lambda macro
C_ASSERT(AP(7.35) == LR(0.5), AFR) // Matches lambda macro
C_ASSERT(AP(0) == 0, AFR)          // Minimum is OK

#endif
// TODO Add checks for the IT() macro once new format is setup


#else
  /* let us know if we are being untidy with headers */
  #warning "Header file TYPE_CHECKS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
/* ex: set tabstop=2 shiftwidth=2 expandtab softtabstop=2: */
