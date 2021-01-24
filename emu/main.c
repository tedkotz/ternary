/**
 * @file    [FileName.c]
 * @author  [John Doe <jdoe@example.com>]
 * @version 1.0
 *
 * @section LICENSE
 *
 * Copyright 2009-2009 [John Doe].  All rights reserved.
 *  See license distributed with this file and
 *  available online at http://[Project Website]/license.html
 *
 * @section DESCRIPTION
 *
 * [Description]
 *
 */


/* Includes ******************************************************************/
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


#include "ternary.h"


typedef enum
{
	 MOV  = 0b11 11 11,
     ADD  = 0b11 11 00,
	 ADC  = 0b11 11 01,
     MUL  = 0b11 00 11,
     SHL  = 0b11 00 00,
     RCL  = 0b11 00 01,
     CAL  = 0b11 01 11,
	 //SPARE -+0 -> 00-
     NOP  = 0b00 00 00,
     ADDB = 0b00 00 01,
     MULB = 0b00 01 11,
     ANDB = 0b00 01 00,
     ORRB = 0b00 01 01,
     SETB = 0b01 11 11
     //Spare 1-0 -> 111
} OPCODES;


typedef enum
{
     COND_SE  = 0b11 11,
     COND_SN  = 0b11 00,
     COND_CE  = 0b11 01,
     COND_CN  = 0b00 11,
     COND_ZE  = 0b00 00, // Zero Equals: so Always is 000
     COND_VE  = 0b00 01,
     COND_VN  = 0b01 11,
     COND_PE  = 0b01 00,
     COND_PN  = 0b01 01
} CONDITIONALS;


typedef union
{
	TriWord val;
	struct {
	TriWord Reserved:6; // for future use
	TriWord Cond:6;
	TriWord CondValue:2;
	TriWord OpCnt:2;
	TriWord OpCode:12;
	TriWord Op3:10;
	TriWord Op2:8;
	TriWord Op1:10;
    TriWord OpMod:4;
	} parts;
} InstReg;


static int evalConditon(TriCpu cpu)

static void incClock(TriCpu cpu)
{
	cpu.regs[REG_CLOCK]=TriWord_ADD(cpu.regs[REG_CLOCK], 1);

}

static void getInstruction(TriCpu cpu)
{
	cpu.regs[REG_INST]=ReadRam(cpu.regs[REG_PC]);
	cpu.regs[REG_PC]=TriWord_ADD(cpu.regs[REG_PC], 1);
    incClock(cpu);
}



static void getOperands(TriCpu cpu)
{
	InstReg INST;
	INST.val=cpu.regs[REG_INST];
	if(N!=INST.parts.OpCnt)
	{
		cpu.A=getOP(INST.parts.Op2);
	}
	else
	{
		cpu.A=0;
	}
    incClock(cpu);


	if((N!=INST.parts.OpCnt) || (0!=INST.parts.OpCode))
	{
		cpu.B=getOP(INST.parts.Op1);
		if(N==INST.parts.OpMod)
		{
			cpu.B=TriWord_NEGB(cpu.B);
		}
	}
	else
	{
		cpu.B=0;
	}
    incClock(cpu);

}

static void storeResult(TriCpu cpu)
{
	InstReg INST;
	INST.val=cpu.regs[REG_INST];
	cpu.regs[REG_INST]=ram[cpu.regs[REG_PC++]];
	cpu.regs[REG_CLOCK]++;
}


int main( int argc, char** argv )
{
	TriCpu cpu;
	cpu.running = true;
	while(cpu.running)
	{
		getInstruction(cpu);
		getOperands(cpu);
		storeResult(cpu);
	}
}
