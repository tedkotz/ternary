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
 * @file    ternary.c
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */


/* Includes ******************************************************************/
#include "ternary.h"

#include <stdio.h>
/* Defines *******************************************************************/
/* Types *********************************************************************/
/* Interfaces ****************************************************************/
/* Data **********************************************************************/

//                                            A 0  0  0  0    1  1  1  1   XXXXXXX   -1 -1 -1 -1
//                                            B 0  1  X -1    0  1  X -1              0  1  X -1
static const int_fast8_t trigate_min[4][4] = {{ 0, 0, 2, N},{ 0, 1, 2, N},{2,2,2,2},{ N, N, 2, N}};
static const int_fast8_t trigate_max[4][4] = {{ 0, 1, 2, 0},{ 1, 1, 2, 1},{2,2,2,2},{ 0, 1, 2, N}};
static const int_fast8_t trigate_mul[4][4] = {{ 0, 0, 2, 0},{ 0, 1, 2, N},{2,2,2,2},{ 0, N, 2, 1}};
static const int_fast8_t trigate_add[4][4] = {{ 0, 1, 2, N},{ 1, N, 2, 0},{2,2,2,2},{ N, 0, 2, 1}};
static const int_fast8_t trigate_set[4][4] = {{ 0, 1, 2, N},{ 1, 1, 2, N},{2,2,2,2},{ N, 1, 2, N}};
static const int_fast8_t trigate_imp[4][4] = {{ 1, 1, 2, 0},{ 0, 1, 2, N},{2,2,2,2},{ 1, 1, 2, 1}};
static const int_fast8_t trigate_unm[4][4] = {{ 0, 0, 2, 0},{ 0, 1, 2, 0},{2,2,2,2},{ 0, 0, 2, N}};

//                                        A 0  1  X -1
static const int_fast8_t trigate_inc[4] = { 1, N, 2, 0};  // Tritwise Increment
static const int_fast8_t trigate_dec[4] = { N, 0, 2, 1};  // Tritwise Decrement
static const int_fast8_t trigate_not[4] = { 0, N, 2, 1};  // Tritwise NOT / Negation
static const int_fast8_t trigate_flt[4] = { 0, 1, 2, 0};  // Tritwise Flatten
static const int_fast8_t trigate_abs[4] = { 0, 1, 2, 1};  // Tritwise Decrement

/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */
int trit2int( unsigned int x )
{
	return (x==N) ? -1 : x;
}

unsigned int int2trit( int x )
{
	return (x==-1) ? N : x;
}

int64_t TriWord2int( TriWord x )
{
	int64_t total=0;
	int i;
	for(i=58; i>=0; i-=2)
	{
		total *= 3;
		total += trit2int( (x >> i) & 3 );
	}
	return total;
}

//TriWord int2TriWord( int64_t x, int lvl )
//{
//	TriWord retVal=0;
//
//	return retVal;
//}

void TriWordPrint( TriWord x, int_fast8_t started)
{
	int_fast8_t i;
	for(i=(BITS_PER_TRIWORD-2); i>=0; i-=2)
	{
		switch((x >> i) & 0b011)
		{
			case 3:
				printf("-");
				started=1;
				break;

			case 0:
				if(started || !i) printf("0");
				break;

			case 1:
				printf("1");
				started=1;
				break;

			default:
				printf("X");
				break;
		}
	}
}

void TriWordScan( TriWord* x )
{
	TriWord dst=0;
	int_fast8_t state=2, count=TRITS_PER_WORD;
	char c;

	while( state && count )
	{
		scanf("%c",&c);
		switch(c)
		{
			case '-':
			case '_':
			case 'n':
			case 'N':
				state=1;
				--count;
				dst = (dst<<2)|N;
				break;

			case '0':
			case ')':
			case 'z':
			case 'Z':
				state=1;
				count--;
				dst = (dst<<2)|0;
				break;

			case '1':
			case '!':
			case '+':
			case '=':
			case 'p':
			case 'P':
				state=1;
				--count;
				dst = (dst<<2)|1;
				break;

			default:
				if(state==1) state=0;
				break;
		}
	}
	*x=dst;
}

// BITWISE 1 OP
static TriWord apply_bitwise_TriWord_gate1 ( const int_fast8_t gate[4],  TriWord op1 )
{
	TriWord dst = 0;
	uint_fast8_t i;
	for(i=0; i<BITS_PER_TRIWORD; i+=BITS_PER_TRIT)
	{
		dst |= ((TriWord)gate[(op1 >> i)&3])<<i;
	}
	return dst;
}

TriWord TriWord_INCB( TriWord op1 )
{
	return apply_bitwise_TriWord_gate1(trigate_inc, op1);
}

TriWord TriWord_DECB( TriWord op1 )
{
	return apply_bitwise_TriWord_gate1(trigate_dec, op1);
}

TriWord TriWord_NEGB( TriWord op1 )
{
	return apply_bitwise_TriWord_gate1(trigate_not, op1);
}

TriWord TriWord_FLTB( TriWord op1 )
{
	return apply_bitwise_TriWord_gate1(trigate_flt, op1);
}

TriWord TriWord_ABSB( TriWord op1 )
{
	return apply_bitwise_TriWord_gate1(trigate_abs, op1);
}

// BITWISE 2 OPS
static TriWord apply_bitwise_TriWord_gate ( const int_fast8_t gate[4][4],  TriWord op1, TriWord op2 )
{
	TriWord dst = 0;
	uint_fast8_t i;
	for(i=0; i<BITS_PER_TRIWORD; i+=BITS_PER_TRIT)
	{
		dst |= ((TriWord)gate[(op1 >> i)&3][(op2 >> i)&3])<<i;
	}
	return dst;
}


TriWord TriWord_ADDB ( TriWord op1, TriWord op2 )
{
	return apply_bitwise_TriWord_gate(trigate_add, op1, op2);
}

TriWord TriWord_MULB ( TriWord op1, TriWord op2 )
{
	return apply_bitwise_TriWord_gate(trigate_mul, op1, op2);
}

TriWord TriWord_ANDB ( TriWord op1, TriWord op2 )
{
	return apply_bitwise_TriWord_gate(trigate_min, op1, op2);
}

TriWord TriWord_ORRB ( TriWord op1, TriWord op2 )
{
	return apply_bitwise_TriWord_gate(trigate_max, op1, op2);
}

TriWord TriWord_SETB ( TriWord op1, TriWord op2 )
{
	return apply_bitwise_TriWord_gate(trigate_set, op1, op2);
}

TriWord TriWord_IMPB ( TriWord op1, TriWord op2 )
{
	return apply_bitwise_TriWord_gate(trigate_imp, op1, op2);
}

TriWord TriWord_UNMB ( TriWord op1, TriWord op2 )
{
	return apply_bitwise_TriWord_gate(trigate_unm, op1, op2);
}

// ARITHMETIC 2 OPS

TriWord TriWord_SHL  ( TriWord op1, TriWord op2 )
{
	int shift=TriWord2int(op2)*2;
	if(shift<0)
	{
		return (TRIWORD_MASK & op1)>>-shift;
	}
	else
	{
		return op1<<shift;
	}
}

TriWord TriWord_RCL  ( TriWord op1, TriWord op2, unsigned* carry )
{
	int shift=(TriWord2int(op2) % (TRITS_PER_WORD + 1))*2;
	TriWord wrap;
		op1 = (TRIWORD_MASK & op1) | ((TriWord)(*carry&3) << BITS_PER_TRIWORD);
	if(shift<0)
	{
		shift = (-shift) % (BITS_PER_TRIWORD + 2);
		wrap= op1 & ((1 << shift) -1);
		op1=(op1 >> shift) | (wrap << ((BITS_PER_TRIWORD+2) - shift));
	}
	else
	if(shift!=0)
	{
		shift = shift % (BITS_PER_TRIWORD + 2);
		wrap=((op1 >> ((BITS_PER_TRIWORD + 2) - shift)) & ((1 << shift) -1));
		op1=(op1 << shift) | wrap;
	}
	*carry = (op1 >> BITS_PER_TRIWORD) & 3;
	op1 &= TRIWORD_MASK;
	return op1;
}

TriWord TriWord_ADD  ( TriWord op1, TriWord op2 )
{
	TriWord op3;
	while(op2)
	{
		op3=TriWord_UNMB(op1, op2);
		op1=TriWord_ADDB(op1, op2);
		op2=TriWord_SHL(op3, 1);
	}
	return op1;
}

TriWord TriWord_ADC  ( TriWord op1, TriWord op2, unsigned* carry )
{
	return TriWord_ADD( op1, TriWord_ADD( op2, *carry & 3 ) );
}

TriWord TriWord_MUL  ( TriWord op1, TriWord op2 )
{
	TriWord product=0;
	while(op2)
	{
		switch(op2 & 3)
		{
			case 1:
				product = TriWord_ADD( product, op1 );
				break;

			case N:
				product = TriWord_ADD( product, TriWord_NEGB(op1) );
				break;
		}
		op1 <<= BITS_PER_TRIT;
		op2 >>= BITS_PER_TRIT;
	}
	return product;
}

//TriWord TriWord_DIVMOD  ( TriWord op1, TriWord op2 ){
//}
#if TERNARY_MATH_MAIN
int main( int argc, char** argv )
{
	//int64_t i;
	TriWord A, B;
	unsigned carry=N;

    printf("A: ");
	TriWordScan( &A );
    printf("B: ");
	TriWordScan( &B );

	printf("\nA = %"PRIi64"  ", TriWord2int(A) );  TriWordPrint( A );
	printf("\nB = %"PRIi64"  ", TriWord2int(B));  TriWordPrint( B );

	printf("\n\nTritwise unary operations:\nINC(A)=");  TriWordPrint( TriWord_INCB(A) );
	printf("\nDEC(A)=");  TriWordPrint( TriWord_DECB(A) );
	printf("\nNEG(A)=");  TriWordPrint( TriWord_NEGB(A) );
	printf("\nFLT(A)=");  TriWordPrint( TriWord_FLTB(A) );
	printf("\nABS(A)=");  TriWordPrint( TriWord_ABSB(A) );

	printf("\n\nTritwise 2 input operations:\nMUL(A, B)=");  TriWordPrint( TriWord_MULB(A, B) );
	printf("\nADD(A, B)=");  TriWordPrint( TriWord_ADDB(A, B) );
	printf("\nORR(A, B)=");  TriWordPrint( TriWord_ORRB(A, B) );
	printf("\nAND(A, B)=");  TriWordPrint( TriWord_ANDB(A, B) );
	printf("\nSET(A, B)=");  TriWordPrint( TriWord_SETB(A, B) );
	printf("\nIMP(A, B)=");  TriWordPrint( TriWord_IMPB(A, B) );
	printf("\nUNM(A, B)=");  TriWordPrint( TriWord_UNMB(A, B) );

	printf("\n\nSHL(A, +--)=");  TriWordPrint( TriWord_SHL(A, 0b011111) );
	printf("\nSHL(A, 0--)=");  TriWordPrint( TriWord_SHL(A, 0b001111) );
	printf("\nRCL(A, +--, -)=");  TriWordPrint( TriWord_RCL(A, 0b011111, &carry) ); carry=N;
	printf("\nRCL(A, 0--, -)=");  TriWordPrint( TriWord_RCL(A, 0b001111, &carry) ); carry=N;

	printf("\n\nArithmetic operations:\nADD(A, B)=%"PRIi64"  ", TriWord2int(TriWord_ADD(A, B)));  TriWordPrint( TriWord_ADD(A, B) );
	printf("\nSUB(A, B)=%"PRIi64"  ", TriWord2int(TriWord_ADD(A, TriWord_NEGB(B))));  TriWordPrint( TriWord_ADD(A, TriWord_NEGB(B)) );
	printf("\nADC(A, B, -)=%"PRIi64"  ", TriWord2int(TriWord_ADC(A, B, &carry))); carry=N; TriWordPrint( TriWord_ADC(A, B, &carry) ); carry=N;
	printf("\nMUL(A, B)=%"PRIi64"  ", TriWord2int(TriWord_MUL(A, B)));  TriWordPrint( TriWord_MUL(A, B) );

	printf("\ndone.\n");
	return 0;
}
#endif //TERNARY_MATH_MAIN


/*****************************************************************************/
