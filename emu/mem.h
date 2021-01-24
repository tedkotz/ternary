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
 * @file    mem.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */

#ifndef   TERNARY_MEM_H
#define   TERNARY_MEM_H
/* Includes ******************************************************************/
#include "cpu.h"

/* Defines *******************************************************************/
// 3^11 Trites of RAM
#define RAM_SIZE 177147
#define BASE_OFFSET (RAM_SIZE/2)
#define RAM_ADDR_MASK ((1<<(11*2))-1)

/* Types *********************************************************************/
typedef enum
{
    ADDR_ISR_INV_INSTR = -2,
    ADDR_ISR_DIV_ZERO  = -3,
    ADDR_UART_IN       = -4,
	ADDR_UART_OUT      = -5,
	ADDR_RTC           = -6,
	/*BITMAP DISPLAY*/
	/*DAC*/
	/*ADC*/
	/*TIMER_INT*/
} MemMappedDevices;

/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */
extern Tryte ReadAddr(TriWord addr);

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void WriteAddr(TriWord addr, Tryte val);


#endif /* TERNARY_MEM_H */

/*****************************************************************************/
