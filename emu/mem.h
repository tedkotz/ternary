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
    //                   __--__--__--
    ADDR_UART          = 0b000000000011, // -1 ,
    ADDR_PC_START2     = 0b000000001101, // -2 ,
    ADDR_PC_START1     = 0b000000001100, // -3 ,
    ADDR_PC_START0     = 0b000000001111, // -4 ,
    ADDR_ERROR_ISR2    = 0b000000110101, // -5 ,
    ADDR_ERROR_ISR1    = 0b000000110100, // -6 ,
    ADDR_ERROR_ISR0    = 0b000000110111, // -7 ,
    ADDR_NMI_ISR2      = 0b000000110001, // -8 ,
    ADDR_NMI_ISR1      = 0b000000110000, // -9 ,
    ADDR_NMI_ISR0      = 0b000000110011, // -10,
    ADDR_EXT_ISR2      = 0b000000111101, // -11,
    ADDR_EXT_ISR1      = 0b000000111100, // -12,
    ADDR_EXT_ISR0      = 0b000000111111, // -13,
    ADDR_RTC2          = 0b000011010101, // -14,
    ADDR_RTC1          = 0b000011010100, // -15,
    ADDR_RTC0          = 0b000011010111, // -16,
//  ADDR_              = 0b000011010001, // -00,
//  ADDR_              = 0b000011010000, // -00,
//  ADDR_              = 0b000011010011, // -00,
//  ADDR_              = 0b000011011101, // -00,
//  ADDR_              = 0b000011011100, // -00,
//  ADDR_              = 0b000011011111, // -00,


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

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void resetMem( void );

#endif /* TERNARY_MEM_H */

/*****************************************************************************/
