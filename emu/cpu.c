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
 * @file    cpu.c
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */


/* Includes ******************************************************************/
#include "cpu.h"
#include "mem.h"

/* Defines *******************************************************************/
/* Types *********************************************************************/
/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */


/*****************************************************************************/



//0000 NOP          0
//     ADD.Cond     3
//     ADDC         3
//     MUL          3
//     SHL          3
//     RCL          3
//
//     ADDB         3
//     MULB         3
//     ANDB         3
//     ORRB         3
//     SETB         3
//
//     MV.Cond      2
//     CALL         1 Special
//
//Operand extras
//  Negate
//
//
//Conditonals (MV, ADD)
//  Flags (S-Sign, C-Carry, V-Overflow, P-Parity)
//  Values (P-One, NP-Not One, Z-Zero, NZ-Not Zero, M-Neg One, NM-Not Neg One)
//  Aliases (LT-SM, GE-SNM, EQ-SZ, NE-SNZ, GT-SP, LE-SNP, CC-CZ, CS-CNZ, VC-VM, VS-VNM, EV-PZ, OD-PNZ)
//
//Virtual Operators
//  JMP (MV PC, #dest)
//  RET (MV PC, (SP++))
//  SUB (ADD A, B, -C)
//  NEG (MV A, -B)
//  CMP (ADD 0, A, -B)
//  TST (MV 0, A)
//  CFL (MV 0,0)
//
//
//
//Extensions
//  BRC (ADD PC, PC, #offset)
//
// Stages
// Inst Fetch
// A Fetch
// B Fetch
// Store




//typedef enum
//{
//	 MOV  = 0b11 11 11,
//     ADD  = 0b11 11 00,
//	 ADC  = 0b11 11 01,
//     MUL  = 0b11 00 11,
//     SHL  = 0b11 00 00,
//     RCL  = 0b11 00 01,
//     CAL  = 0b11 01 11,
//	 //SPARE -+0 -> 00-
//     NOP  = 0b00 00 00,
//     ADDB = 0b00 00 01,
//     MULB = 0b00 01 11,
//     ANDB = 0b00 01 00,
//     ORRB = 0b00 01 01,
//     SETB = 0b01 11 11
//     //Spare 1-0 -> 111
//} OPCODES;


typedef enum
{
     COND_SE  = 0b1111,
     COND_SN  = 0b1100,
     COND_CE  = 0b1101,
     COND_CN  = 0b0011,
     COND_ZE  = 0b0000, // Zero Equals: so Always is 000
     COND_VE  = 0b0001,
     COND_VN  = 0b0111,
     COND_PE  = 0b0100,
     COND_PN  = 0b0101
} CONDITIONALS;

typedef enum
{
	OPMOD_NEG = 0b0011,
	OPMOD_NOP = 0b0000,
	OPMOD_INC = 0b0001,
	OPMOD_DEC = 0b0111,
	OPMOD_ABS = 0b0100,
	OPMOD_FLT = 0b0101,
} OpModifiers;

//typedef enum
//{
//	OPType_REG  = 0b1111,  // [--R0]
//	OPType_REG  = 0b1100,  // [R0]
//	OPType_REG  = 0b1101,  // [R0++]
//	OPType_REG  = 0b0011,  // R0
//	OPType_REG  = 0b0000,  // #nnn, If Dest value dropped
//	OPType_REG  = 0b0001,  // [[RO++]]
//} OpTypes;

typedef union
{
	TriWord val;
	struct {
	TriWord Reserved:6;  // for future use
	TriWord Cond:6;      // conditional flag
	TriWord CondValue:2; // conditional test value
	TriWord OpCnt:2;     // number of operators
	TriWord OpCode:12;   // instruction number
	TriWord Op3:10;      // OP2 = OP3 + MOD(OP1)
	TriWord Op2:10;      // OP2 = OP2 + MOD(OP1)
	TriWord Op1:10;      // OP1 = + MOD(OP1)
    TriWord OpMod:4;     // ALU MOdifier to apply to OP1
	} parts;
} InstReg;



int evalConditon(TriCpu* cpu)
{
	InstReg INST;
	FlagReg FLGS;
	INST.val=cpu->regs[REG_INST];
	FLGS.val=cpu->regs[REG_FLAGS];
	switch (INST.parts.Cond)
	{
		case COND_SE:
			return( FLGS.flags.S == INST.parts.CondValue );
		case COND_SN:
			return( FLGS.flags.S != INST.parts.CondValue );
		case COND_CE:
			return( FLGS.flags.C == INST.parts.CondValue );
		case COND_CN:
			return( FLGS.flags.C != INST.parts.CondValue );
		case COND_ZE:
			return( 0 == INST.parts.CondValue );
		case COND_VE:
			return( FLGS.flags.V == INST.parts.CondValue );
		case COND_VN:
			return( FLGS.flags.V != INST.parts.CondValue );
		case COND_PE:
			return( FLGS.flags.P == INST.parts.CondValue );
		case COND_PN:
			return( FLGS.flags.P != INST.parts.CondValue );
		default:
//			callInst(ReadAddr(ADDR_ISR_INV_INSTR));
			return 0;
	}
}

void incClock(TriCpu* cpu)
{
	cpu->regs[REG_CLOCK]=TriWord_ADD(cpu->regs[REG_CLOCK], 1);

}

void getInstruction(TriCpu* cpu)
{
	cpu->regs[REG_INST]=ReadAddr(cpu->regs[REG_PC]);
	cpu->regs[REG_PC]=TriWord_ADD(cpu->regs[REG_PC], 1);
    incClock(cpu);
}


void getOperands(TriCpu* cpu)
{
	InstReg INST;
	INST.val=cpu->regs[REG_INST];
	if(N!=INST.parts.OpCnt)
	{
//		cpu->A=getOP(INST.parts.Op2);
	}
	else
	{
		cpu->A=0;
	}
    incClock(cpu);


	if((N!=INST.parts.OpCnt) || (0!=INST.parts.OpCode))
	{
//		cpu->B=getOP(INST.parts.Op1);
		if(N==INST.parts.OpMod)
		{
			cpu->B=TriWord_NEGB(cpu->B);
		}
	}
	else
	{
		cpu->B=0;
	}
    incClock(cpu);

}
//
void storeResult(TriCpu* cpu)
{
//	InstReg INST;
//	INST.val=cpu->regs[REG_INST];
	cpu->regs[REG_INST]=ReadAddr((cpu->regs[REG_PC])++);
	cpu->regs[REG_CLOCK]++;
}

