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
	int64_t offset=TriWord2int(addr & RAM_ADDR_MASK);
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
	int64_t offset=TriWord2int(addr & RAM_ADDR_MASK);
	switch(addr)
	{
		case ADDR_UART:
			putchar(TriWord2int(val));
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
    int64_t idx = BASE_OFFSET+ 9;
    ram[BASE_OFFSET- 4]=0b00010000;
    // POP R_5, PC+3
    //           __--__--__--__--__
    ram[idx++]=0b110101111111110111;
    ram[idx++]=0b111100001100000000;
    ram[idx++]=0b000000000000010011;
    // Address of top of stack
    //           __--__--__--__--__
    ram[idx++]=0b000011000000000000;
    ram[idx++]=0b000000000000000000;
    ram[idx++]=0b000000000000000000;
    // LD1 R3, R0+9
    //           __--__--__--__--__
    ram[idx++]=0b000100111111111111;
    ram[idx++]=0b111100000000000000;
    ram[idx++]=0b000000000001000011;
    // LD2 R2, R0+9
    ram[idx++]=0b000111111111111100;
    ram[idx++]=0b111100000000000000;
    ram[idx++]=0b000000000001000011;
    // LD3 R1, R0+9
    ram[idx++]=0b000001111111111101;
    ram[idx++]=0b111100000000000000;
    ram[idx++]=0b000000000001000011;
    // PSH R_5-3, neg(R1)
    //           __--__--__--__--__
    ram[idx++]=0b110101111111110100;
    ram[idx++]=0b111100000111111111;
    ram[idx++]=0b000000000000110011;
    // POP R1, P_5+3
    //           __--__--__--__--__
    ram[idx++]=0b000001111111110111;
    ram[idx++]=0b111111010100000000;
    ram[idx++]=0b000000000000010011;
    // ST1 R0+6, neg(R1)
    //           __--__--__--__--__
    ram[idx++]=0b000000111111110011;
    ram[idx++]=0b111100000111111111;
    ram[idx++]=0b000000000001110011;
    // ST2 R0+6, inc(R1)
    //           __--__--__--__--__
    ram[idx++]=0b000000111111110000;
    ram[idx++]=0b111100000111111100;
    ram[idx++]=0b000000000001110011;
    // ST3 R0+6, dec(R1)
    //           __--__--__--__--__
    ram[idx++]=0b000000111111110001;
    ram[idx++]=0b111100000111111101;
    ram[idx++]=0b000000000001110011;
    // ST1 R0+6, abn(R1)
    //           __--__--__--__--__
    ram[idx++]=0b000000111111110011;
    ram[idx++]=0b111100000111110011;
    ram[idx++]=0b000000000001110011;
    // ST2 R0+6, abs(R1)
    //           __--__--__--__--__
    ram[idx++]=0b000000111111110000;
    ram[idx++]=0b111100000111110000;
    ram[idx++]=0b000000000001110011;
    // ST3 R0+6, flt(R1)
    //           __--__--__--__--__
    ram[idx++]=0b000000111111110001;
    ram[idx++]=0b111100000111110001;
    ram[idx++]=0b000000000001110011;

}

/*****************************************************************************/


