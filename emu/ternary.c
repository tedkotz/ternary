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
 * This defines  basic ternary logical and mathematical operations.
 * The approach to this is not to translate the values to binary and then
 * do binary arithmatic, but to define lookup tables for the basic ternary gates
 * then combine those to build up the higher level math funtions.
 *
 */


/* Includes ******************************************************************/
#include "ternary.h"

#include <stdio.h>
/* Defines *******************************************************************/
/* Types *********************************************************************/
/* Interfaces ****************************************************************/
/* Data **********************************************************************/

//                                       A 0  0  0  0    1  1  1  1   XXXXXXX   -1 -1 -1 -1
//                                       B 0  1  X -1    0  1  X -1              0  1  X -1
static const trit_t trigate_min[4][4] = {{ 0, 0, 2, N},{ 0, 1, 2, N},{2,2,2,2},{ N, N, 2, N}};
static const trit_t trigate_max[4][4] = {{ 0, 1, 2, 0},{ 1, 1, 2, 1},{2,2,2,2},{ 0, 1, 2, N}};
static const trit_t trigate_mul[4][4] = {{ 0, 0, 2, 0},{ 0, 1, 2, N},{2,2,2,2},{ 0, N, 2, 1}};
static const trit_t trigate_add[4][4] = {{ 0, 1, 2, N},{ 1, N, 2, 0},{2,2,2,2},{ N, 0, 2, 1}};
static const trit_t trigate_set[4][4] = {{ 0, 1, 2, N},{ 1, 1, 2, N},{2,2,2,2},{ N, 1, 2, N}};
static const trit_t trigate_imp[4][4] = {{ 1, 1, 2, 0},{ 0, 1, 2, N},{2,2,2,2},{ 1, 1, 2, 1}};
static const trit_t trigate_unm[4][4] = {{ 0, 0, 2, 0},{ 0, 1, 2, 0},{2,2,2,2},{ 0, 0, 2, N}};

//                                   A 0  1  X -1
static const trit_t trigate_inc[4] = { 1, N, 2, 0};  // Tritwise Increment
static const trit_t trigate_dec[4] = { N, 0, 2, 1};  // Tritwise Decrement
static const trit_t trigate_not[4] = { 0, N, 2, 1};  // Tritwise NOT / Negation
static const trit_t trigate_flt[4] = { 0, 1, 2, 0};  // Tritwise Flatten
//static const trit_t trigate_lax[4] = { 1, 1, 2, 0};
static const trit_t trigate_abs[4] = { 0, 1, 2, 1};  // Tritwise Decrement

/* Functions *****************************************************************/



/**
 * [Description]
 *
 * @param
 * @return
 */
int trit2int( trit_t x )
{
    return (x==N) ? -1 : x;
}

trit_t int2trit( int x )
{
    return (x==-1) ? N : x;
}

int64_t ternary2int( trint32_t x )
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

//trint32_t int2ternary( int64_t x, int lvl );
//{
//	trint32_t retVal=0;
//
//	return retVal;
//}

void ternaryPrint( trint32_t x, int_fast8_t width)
{
    int_fast8_t started;
    int_fast8_t i;
    if(width < 1)
    {
        i=BITS_PER_TRINT32_T-2;
        started=0;
    }
    else if(width < TRITS_PER_TRINT32_T)
    {
        i=(width*2)-2;
        started=1;
    }
    else
    {
        i=BITS_PER_TRINT32_T-2;
        started=1;
    }
    for(; i>=0; i-=2)
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

void ternaryScan( trint32_t* x )
{
    trint32_t dst=0;
    int_fast8_t state=2, count=TRITS_PER_TRINT32_T;
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
static trint32_t apply_tritwise_gate1 ( const trit_t gate[4],  trint32_t op1 )
{
    trint32_t dst = 0;
    uint_fast8_t i;
    for(i=0; i<BITS_PER_TRINT32_T; i+=BITS_PER_TRIT)
    {
        dst |= ((trint32_t)gate[(op1 >> i)&3])<<i;
    }
    return dst;
}

trint32_t ternaryINCB( trint32_t op1 )
{
    return apply_tritwise_gate1(trigate_inc, op1);
}

trint32_t ternaryDECB( trint32_t op1 )
{
    return apply_tritwise_gate1(trigate_dec, op1);
}

trint32_t ternaryNEGB( trint32_t op1 )
{
    return apply_tritwise_gate1(trigate_not, op1);
}

trint32_t ternaryFLTB( trint32_t op1 )
{
    return apply_tritwise_gate1(trigate_flt, op1);
}

trint32_t ternaryABSB( trint32_t op1 )
{
    return apply_tritwise_gate1(trigate_abs, op1);
}

// BITWISE 2 OPS
static trint32_t apply_tritwise_gate2 ( const trit_t gate[4][4],  trint32_t op1, trint32_t op2 )
{
    trint32_t dst = 0;
    uint_fast8_t i;
    for(i=0; i<BITS_PER_TRINT32_T; i+=BITS_PER_TRIT)
    {
        dst |= ((trint32_t)gate[(op1 >> i)&3][(op2 >> i)&3])<<i;
    }
    return dst;
}


trint32_t ternaryADDB ( trint32_t op1, trint32_t op2 )
{
    return apply_tritwise_gate2(trigate_add, op1, op2);
}

trint32_t ternaryMULB ( trint32_t op1, trint32_t op2 )
{
    return apply_tritwise_gate2(trigate_mul, op1, op2);
}

trint32_t ternaryANDB ( trint32_t op1, trint32_t op2 )
{
    return apply_tritwise_gate2(trigate_min, op1, op2);
}

trint32_t ternaryORRB ( trint32_t op1, trint32_t op2 )
{
    return apply_tritwise_gate2(trigate_max, op1, op2);
}

trint32_t ternarySETB ( trint32_t op1, trint32_t op2 )
{
    return apply_tritwise_gate2(trigate_set, op1, op2);
}

trint32_t ternaryIMPB ( trint32_t op1, trint32_t op2 )
{
    return apply_tritwise_gate2(trigate_imp, op1, op2);
}

trint32_t ternaryUNMB ( trint32_t op1, trint32_t op2 )
{
    return apply_tritwise_gate2(trigate_unm, op1, op2);
}


// ARITHMETIC 1 OP
trint32_t ternarySGN  ( trint32_t op1 )
{
    trint32_t sign = 0;
    while( op1 )
    {
        if(op1 & 3)
        {
            sign = op1 & 3;
        }
        op1 >>= BITS_PER_TRIT;
    }
    return sign;
}

// ARITHMETIC 2 OPS

trint32_t ternarySHL  ( trint32_t op1, trint32_t op2 )
{
    int shift=ternary2int(op2)*2;
    if(shift<0)
    {
        return op1 >> (unsigned)(-shift);
    }
    else
    {
        return op1 << shift;
    }
}

//trint32_t ternaryRCL  ( trint32_t op1, trint32_t op2, trit_t* carry )
//{
//    int shift=(ternary2int(op2) % (TRITS_PER_TRINT32_T + 1))*2;
//    trint32_t wrap;
//        op1 = (TRINT32_T_MASK & op1) | ((trint32_t)(*carry&3) << BITS_PER_TRINT32_T);
//    if(shift<0)
//    {
//        shift = (-shift) % (BITS_PER_TRINT32_T + 2);
//        wrap= op1 & ((1 << shift) -1);
//        op1=(op1 >> shift) | (wrap << ((BITS_PER_TRINT32_T+2) - shift));
//    }
//    else
//    if(shift!=0)
//    {
//        shift = shift % (BITS_PER_TRINT32_T + 2);
//        wrap=((op1 >> ((BITS_PER_TRINT32_T + 2) - shift)) & ((1 << shift) -1));
//        op1=(op1 << shift) | wrap;
//    }
//    *carry = (op1 >> BITS_PER_TRINT32_T) & 3;
//    op1 &= TRINT32_T_MASK;
//    return op1;
//}

trint32_t ternaryADD  ( trint32_t op1, trint32_t op2 )
{
    trint32_t op3;
    while(op2)
    {
        op3=ternaryUNMB(op1, op2);
        op1=ternaryADDB(op1, op2);
        op2=ternarySHL(op3, 1);
    }
    return op1;
}

trint32_t ternaryADC  ( trint32_t op1, trint32_t op2, trit_t* carry )
{
    return ternaryADD( op1, ternaryADD( op2, *carry ) );
}

trint32_t ternaryMUL  ( trint32_t op1, trint32_t op2 )
{
    trint32_t product=0;
    while(op2)
    {
        switch(op2 & 3)
        {
            case 1:
                product = ternaryADD( product, op1 );
                break;

            case N:
                product = ternaryADD( product, ternaryNEGB(op1) );
                break;
        }
        op1 <<= BITS_PER_TRIT;
        op2 >>= BITS_PER_TRIT;
    }
    return product;
}

//trint32_t ternaryDIVMOD  ( trint32_t op1, trint32_t op2 )
//{
//}

//#define TERNARY_MATH_MAIN 1

#if TERNARY_MATH_MAIN
int main( int argc, char** argv )
{
    //int64_t i;
    trint32_t A, B;
    trit_t carry=N;

    printf("A: ");
    ternaryScan( &A );
    printf("B: ");
    ternaryScan( &B );

    printf("\nA = %"PRIi64"  ", ternary2int(A) );  ternaryPrint( A, 0);
    printf("\nB = %"PRIi64"  ", ternary2int(B));  ternaryPrint( B, 0);

    printf("\n\nTritwise unary operations:\nINC(A)=");  ternaryPrint( ternaryINCB(A), 0 );
    printf("\nDEC(A)=");  ternaryPrint( ternaryDECB(A), 0 );
    printf("\nNEG(A)=");  ternaryPrint( ternaryNEGB(A), 0 );
    printf("\nFLT(A)=");  ternaryPrint( ternaryFLTB(A), 0 );
    printf("\nABS(A)=");  ternaryPrint( ternaryABSB(A), 0 );

    printf("\n\nTritwise 2 input operations:\nMUL(A, B)=");  ternaryPrint( ternaryMULB(A, B), 0 );
    printf("\nADD(A, B)=");  ternaryPrint( ternaryADDB(A, B), 0 );
    printf("\nORR(A, B)=");  ternaryPrint( ternaryORRB(A, B), 0 );
    printf("\nAND(A, B)=");  ternaryPrint( ternaryANDB(A, B), 0 );
    printf("\nSET(A, B)=");  ternaryPrint( ternarySETB(A, B), 0 );
    printf("\nIMP(A, B)=");  ternaryPrint( ternaryIMPB(A, B), 0 );
    printf("\nUNM(A, B)=");  ternaryPrint( ternaryUNMB(A, B), 0 );

    printf("\n\nSHL(A, +--)=");  ternaryPrint( ternarySHL(A, 0b011111), 0 );
    printf("\nSHL(A, 0--)=");  ternaryPrint( ternarySHL(A, 0b001111), 0 );
    printf("\nSHL(DEC(A), -++-)=");  ternaryPrint( ternarySHL(ternaryDECB(A), 0b0011010111), 0 );
//    printf("\nRCL(A, +--, -)=");  ternaryPrint( ternaryRCL(A, 0b011111, &carry), 0 ); carry=N;
//    printf("\nRCL(A, 0--, -)=");  ternaryPrint( ternaryRCL(A, 0b001111, &carry), 0 ); carry=N;

    printf("\n\nArithmetic operations:\nADD(A, B)=%"PRIi64"  ", ternary2int(ternaryADD(A, B)));  ternaryPrint( ternaryADD(A, B), 0 );
    printf("\nSUB(A, B)=%"PRIi64"  ", ternary2int(ternaryADD(A, ternaryNEGB(B))));  ternaryPrint( ternaryADD(A, ternaryNEGB(B)), 0 );
    printf("\nADC(A, B, -)=%"PRIi64"  ", ternary2int(ternaryADC(A, B, &carry))); carry=N; ternaryPrint( ternaryADC(A, B, &carry), 0 ); carry=N;
    printf("\nMUL(A, B)=%"PRIi64"  ", ternary2int(ternaryMUL(A, B)));  ternaryPrint( ternaryMUL(A, B), 0 );

    printf("\ndone.\n");
    return 0;
}
#endif //TERNARY_MATH_MAIN


/*****************************************************************************/
