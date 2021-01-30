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
 * @file    mem.c
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */


/* Includes ******************************************************************/
#include "mem.h"

#include <stdio.h>
#include <ctype.h>

/* Defines *******************************************************************/
/* Types *********************************************************************/
/* Interfaces ****************************************************************/
/* Data **********************************************************************/
Tryte ram[RAM_SIZE];

/* Functions *****************************************************************/

/*
 * See Header
 *
 */
Tryte ReadAddr(TriWord addr)
{
    int64_t offset=ternary2int(addr & RAM_ADDR_MASK);
    switch(addr)
    {
        case ADDR_UART:
            // return int2Triword(getchar());
            return 0;
            break;
        case ADDR_RTC2:
        case ADDR_RTC1:
        case ADDR_RTC0:
            // return int2TriWord(time(null));
            return 0;
            break;
        default:
            return ram[BASE_OFFSET+offset];
    }
}

/*
 * See Header
 *
 */
void WriteAddr(TriWord addr, Tryte val)
{
    int64_t offset=ternary2int(addr & RAM_ADDR_MASK);
    switch(addr)
    {
        case ADDR_UART:
            putchar(ternary2int(val));
            break;
        case ADDR_RTC2:
        case ADDR_RTC1:
        case ADDR_RTC0:
            break;
        default:
            ram[BASE_OFFSET+offset]=val;
    }

}


/*
 * See Header
 *
 */
void resetMem( void )
{
    ram[BASE_OFFSET- 4]=0b00000000;
}


/*
 * See Header
 *
 */
int readFileIntoMem( FILE* fin , int verbose)
{
    TriWord addr=0;
    TriWord accum=0;
    trit_t t;
    int line=1;
    int pos=0;
    char filename[80] = "-";
    int c;
    for(;;)
    {
        ++pos;
        c=fgetc(fin);
        switch(c)
        {
            case EOF:
                return 0;

            case ';':
                WriteAddr(addr, accum & TRYTE_MASK);
                if (verbose > 0)
                {
                    ternaryPrint(addr, TRITS_PER_WORD);
                    printf(" : ");
                    ternaryPrint(accum, TRITS_PER_TRYTE);
                    printf(";\n");
                }
                accum=0;
                addr= ternaryADD(addr, 1);
                break;

            case ':':
                addr=accum;
                accum=0;
                break;

            case '#':
                // comments, maybe pragmas and line updates
                while( c!=EOF && c !='\n' )
                {
                    c=fgetc(fin);
                }
                //FALLTHRU to end of line processing after comment
            case '\n':
                if( accum != 0 )
                {
                    printf("%s:%d:%d: ERROR: End of line with non-zero accumulator.\n", filename, line, pos);
                    return -1;
                }
                else
                {
                    ++line;
                    pos=0; //Assume carriage return on newline
                }
                break;

            case '\r':
                pos=0;
                break;

            default:
                if (isspace(c))
                {
                    // ignore other whitespace
                }
                else
                {
                    t=char2trit (c);
                    if( 2 != t )
                    {
                        accum = (accum<<BITS_PER_TRIT)|t;
                    }
                    else
                    {
                        printf("%s:%d:%d: ERROR: Unexpected '%c' character.\n", filename, line, pos, c);
                        return -2;
                    }
                }
                break;
        }
    }
}
/*****************************************************************************/


