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
 * @file    disassem.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * Tools needed to disassemble instruction for the ternary computer.
 *
 */
#ifndef   DISASSEM_H
#define   DISASSEM_H


/* Includes ******************************************************************/
#include "cpu.h"

/* Defines *******************************************************************/
typedef enum InstructionFormat
{
    INSTFORMAT_NOP,
    INSTFORMAT_1REG,
    INSTFORMAT_2REG,
    INSTFORMAT_3REG,
    INSTFORMAT_1REG_2IMM,
} InstructionFormat;

/* Types *********************************************************************/
typedef struct TriOpInstruction
{
    TriOpcode opcode;
    TriReg r1;
    TriReg r2;
    OpModifiers r2mod;
    TriReg r3;
    OpModifiers r3mod;
//    TriWord imm4;
    TriWord imm11;
    TriWord imm9_1;
    TriWord imm9_2;
//    TriWord imm18;
}TriOpInstruction;

/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void parseInstruction( TriOpInstruction* fields, TriWord inst );

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void printInstruction( TriWord inst );





#endif // DISASSEM_H
