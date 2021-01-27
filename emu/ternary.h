/****************************************************************************
 * Copyright (C) 2020 by Ted Kotz                                           *
 *                                                                          *
 * This file is part of TernCpuEmu.                                         *
 *                                                                          *
 *   TernCpuEmu is free software: you can redistribute it and/or modify it  *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 2 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   TernCpuEmu is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with TernCpuEmu. If not, see                             *
 *   <http://www.gnu.org/licenses/>.                                        *
 ****************************************************************************/

/**
 * @file    ternary.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */

#ifndef   TERNARY_MATH_H
#define   TERNARY_MATH_H
/* Includes ******************************************************************/
#include <inttypes.h>

/* Defines *******************************************************************/
#define BITS_PER_TRIT 2
#define N 3

#define TRITS_PER_TRINT32_T 32
#define TRITS_PER_TRINT16_T 16
#define BITS_PER_TRINT32_T ( TRITS_PER_TRINT32_T * BITS_PER_TRIT)
#define BITS_PER_TRINT16_T ( TRITS_PER_TRINT16_T * BITS_PER_TRIT)
#define TRINT32_MASK ((1ULL << BITS_PER_TRINT32_T) - 1)
#define TRINT16_MASK ((1ULL << BITS_PER_TRINT16_T) - 1)

/* Types *********************************************************************/
typedef uint64_t trint32_t;
typedef uint32_t trint16_t;
typedef uint_fast8_t trit_t;

/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */
extern int trit2int( trit_t x );
extern trit_t int2trit( int x );

extern int64_t ternary2int( trint32_t x );
//extern trint32_t int2ternary( int64_t x, int lvl );

/**
 * Prints a ternary number
 *
 * @param x The trinary value to print
 * @param width the number of least significant trits to print, 0 drops leading 0s
 */
extern void ternaryPrint( trint32_t x, int_fast8_t width);
extern void ternaryScan( trint32_t* x );

// BITWISE 1 OP
extern trint32_t ternaryINCB( trint32_t op1 );
extern trint32_t ternaryDECB( trint32_t op1 );
extern trint32_t ternaryNEGB( trint32_t op1 );
extern trint32_t ternaryFLTB( trint32_t op1 );
extern trint32_t ternaryABSB( trint32_t op1 );

// BITWISE 2 OPS
extern trint32_t ternaryADDB ( trint32_t op1, trint32_t op2 );
extern trint32_t ternaryMULB ( trint32_t op1, trint32_t op2 );
extern trint32_t ternaryANDB ( trint32_t op1, trint32_t op2 );
extern trint32_t ternaryORRB ( trint32_t op1, trint32_t op2 );
extern trint32_t ternarySETB ( trint32_t op1, trint32_t op2 );
extern trint32_t ternaryIMPB ( trint32_t op1, trint32_t op2 );
extern trint32_t ternaryUNMB ( trint32_t op1, trint32_t op2 );


// ARITHMETIC 1 OP
extern trint32_t ternarySGN  ( trint32_t op1 );

// ARITHMETIC 2 OPS
extern trint32_t ternarySHL  ( trint32_t op1, trint32_t op2 );
//extern trint32_t ternaryRCL  ( trint32_t op1, trint32_t op2, trit_t* carry );
extern trint32_t ternaryADD  ( trint32_t op1, trint32_t op2 );
extern trint32_t ternaryADC  ( trint32_t op1, trint32_t op2, trit_t* carry );
extern trint32_t ternaryMUL  ( trint32_t op1, trint32_t op2 );
//extern trint32_t ternaryDIVMOD  ( trint32_t op1, trint32_t op2 );

#endif /* TERNARY_MATH_H */
/*****************************************************************************/
