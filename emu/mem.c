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
	switch(offset)
	{
		case ADDR_UART_IN:
			// return int2Triword(getchar());
			return 0;
			break;
		case ADDR_UART_OUT:
			return 0;
			break;
		case ADDR_RTC:
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
	switch(offset)
	{
		case ADDR_UART_IN:
		case ADDR_RTC:
			break;
		case ADDR_UART_OUT:
			putchar(TriWord2int(val));
			break;
		default:
			ram[BASE_OFFSET+offset]=val;
	}

}



/*****************************************************************************/


