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
#define TRITS_PER_WORD 27
#define BITS_PER_TRIT 2
#define BITS_PER_TRIWORD ( TRITS_PER_WORD * BITS_PER_TRIT)
#define N 3
#define TRIWORD_MASK ((1ULL << BITS_PER_TRIWORD) - 1)

#define PRITRIWORD PRIx64
#define SCNTRIWORD SCNi64

/* Types *********************************************************************/
typedef uint64_t TriWord;
typedef uint64_t trint32_t;
typedef uint32_t trint16_t;

/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */
extern int trit2int( unsigned int x );
extern unsigned int int2trit( int x );

extern int64_t TriWord2int( TriWord x );
//extern TriWord int2TriWord( int64_t x, int lvl );

extern void TriWordPrint( TriWord x, int_fast8_t started);
extern void TriWordScan( TriWord* x );

// BITWISE 1 OP
extern TriWord TriWord_INCB( TriWord op1 );
extern TriWord TriWord_DECB( TriWord op1 );
extern TriWord TriWord_NEGB( TriWord op1 );
extern TriWord TriWord_FLTB( TriWord op1 );
extern TriWord TriWord_ABSB( TriWord op1 );

// BITWISE 2 OPS
extern TriWord TriWord_ADDB ( TriWord op1, TriWord op2 );
extern TriWord TriWord_MULB ( TriWord op1, TriWord op2 );
extern TriWord TriWord_ANDB ( TriWord op1, TriWord op2 );
extern TriWord TriWord_ORRB ( TriWord op1, TriWord op2 );
extern TriWord TriWord_SETB ( TriWord op1, TriWord op2 );
extern TriWord TriWord_IMPB ( TriWord op1, TriWord op2 );
extern TriWord TriWord_UNMB ( TriWord op1, TriWord op2 );


// ARITHMETIC 1 OP
//extern TriWord TriWord_SGN  ( TriWord op1 );

// ARITHMETIC 2 OPS
extern TriWord TriWord_SHL  ( TriWord op1, TriWord op2 );
extern TriWord TriWord_RCL  ( TriWord op1, TriWord op2, unsigned* carry );
extern TriWord TriWord_ADD  ( TriWord op1, TriWord op2 );
extern TriWord TriWord_ADC  ( TriWord op1, TriWord op2, unsigned* carry );
extern TriWord TriWord_MUL  ( TriWord op1, TriWord op2 );
//extern TriWord TriWord_DIVMOD  ( TriWord op1, TriWord op2 );

#endif /* TERNARY_MATH_H */
/*****************************************************************************/
