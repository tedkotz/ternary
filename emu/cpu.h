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
 * @file    cpu.h
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * [Description]
 *
 */

#ifndef   TERNARY_CPU_H
#define   TERNARY_CPU_H

/* Includes ******************************************************************/
#include "ternary.h"

/* Defines *******************************************************************/
//#define TRITS_PER_WORD 27
//#define BITS_PER_TRIT 2
//#define BITS_PER_TRIWORD ( TRITS_PER_WORD * BITS_PER_TRIT)
//#define N 3
//#define TRIWORD_MASK ((1ULL << BITS_PER_TRIWORD) - 1)

//#define PRITRIWORD PRIx64
//#define SCNTRIWORD SCNi64

/* Types *********************************************************************/
//typedef trint32_t TriWord;
typedef trint16_t Tryte;

typedef enum TriReg
{
	REG_GP14       = 0b111111,
	REG_GP15       = 0b111100,
	REG_GP16       = 0b111101,
	REG_GP17       = 0b110011,
	REG_GP18       = 0b110000,
	REG_GP19       = 0b110001,
	REG_GP20       = 0b110111,
	REG_GP21       = 0b110100,
	REG_CLOCK      = 0b110101,
	REG_BASE       = 0b001111,
	REG_INST       = 0b001100,
	REG_SP         = 0b001101,
	REG_PC         = 0b000011,
	REG_ZERO       = 0b000000,
	REG_GP01       = 0b000001,
	REG_GP02       = 0b000111,
	REG_GP03       = 0b000100,
	REG_GP04       = 0b000101,
	REG_GP05       = 0b011111,
	REG_GP06       = 0b011100,
	REG_GP07       = 0b011101,
	REG_GP08       = 0b010011,
	REG_GP09       = 0b010000,
	REG_GP10       = 0b010001,
	REG_GP11       = 0b010111,
	REG_GP12       = 0b010100,
	REG_GP13       = 0b010101,
} TriReg;
//#define	NUM_TRIREGS (3*3*3)
#define	NUM_TRIREGS (0b111111)
//	REG_FLAGS,??

typedef struct TriFlags
{
	TriWord S :2 ; // Sign
	TriWord C :2 ; // Carry
	TriWord V :2 ; // Overflow
	TriWord P :2 ; // Parity
	TriWord I :2 ; // Interrupts
} TriFlags;

typedef struct TriCpu
{
	TriWord A;
	TriWord B;
	TriWord D;
	TriWord valA;
	TriWord valB;
	TriWord regs[NUM_TRIREGS];
	uint8_t running;
} TriCpu;


typedef enum TriOpcode
{
    //                 __--__--__--
    OPCODE_LD1     = 0b111111111111,  // Load Rd <- (Rs+immediate) 9 trits
    OPCODE_LD2     = 0b111111111100,  // Load Rd <- (Rs+immediate) 18 trits
    OPCODE_LD3     = 0b111111111101,  // Load Rd <- (Rs+immediate) 27 trits
    OPCODE_ST1     = 0b111111110011,  // Store (Rs1+immediate) <- Rs2 9 trits
    OPCODE_ST2     = 0b111111110000,  // Store (Rs1+immediate) <- Rs2 18 trits
    OPCODE_ST3     = 0b111111110001,  // Store (Rs1+immediate) <- Rs2 27 trits
    OPCODE_POP     = 0b111111110111,  // Load Rd <- (Rs) ; Rs += immediate
    OPCODE_PSH     = 0b111111110100,  // Store Rd += immediate; (Rd)  <- Rs
    OPCODE_SWP     = 0b111111110101,  // Rd1 = Rd2 + immeditate | Rd2 = Rd1
    //                 __--__--__--
    OPCODE_SUBCSEN = 0b111111001111,  // if S==- , C:Rd = Rs1 - Rs2
    OPCODE_SUBCSEZ = 0b111111001100,  // if S==0 , C:Rd = Rs1 - Rs2
    OPCODE_SUBCSEP = 0b111111001101,  // if S==1 , C:Rd = Rs1 - Rs2
    OPCODE_SUBCRRY = 0b111111000011,  // C:Rd = Rs1 - Rs2 + C
    OPCODE_SUB     = 0b111111000000,  // C:Rd = Rs1 - Rs2
//  OPCODE_SUBI    = 0b111111000001,  // C:Rd = Rs1 - immediate
    OPCODE_SUBCSNN = 0b111111000111,  // if S!=- , C:Rd = Rs1 - Rs2
    OPCODE_SUBCSNZ = 0b111111000100,  // if S!=0 , C:Rd = Rs1 - Rs2
    OPCODE_SUBCSNP = 0b111111000101,  // if S!=1 , C:Rd = Rs1 - Rs2
    //                 __--__--__--
    OPCODE_ADDCSEN = 0b111111011111,  // if S==- , C:Rd = Rs + immediate
    OPCODE_ADDCSEZ = 0b111111011100,  // if S==0 , C:Rd = Rs + immediate
    OPCODE_ADDCSEP = 0b111111011101,  // if S==1 , C:Rd = Rs + immediate
    OPCODE_ADDCRRY = 0b111111010011,  // C:Rd = Rs1 + Rs2 + C
    OPCODE_ADDR    = 0b111111010000,  // C:Rd = Rs1 + Rs2
    OPCODE_ADD     = 0b111111010001,  // C:Rd = Rs + immediate
    OPCODE_ADDCSNN = 0b111111010111,  // if S!=- , C:Rd = Rs + immediate
    OPCODE_ADDCSNZ = 0b111111010100,  // if S!=0 , C:Rd = Rs + immediate
    OPCODE_ADDCSNP = 0b111111010101,  // if S!=1 , C:Rd = Rs + immediate
    //                 __--__--__--
    OPCODE_SHLR    = 0b111100111111,  // C:Rd = C:Rs1 << Rs2
    OPCODE_SHLI    = 0b111100111100,  // C:Rd = C:Rs  << immediate
    OPCODE_TAND    = 0b111100111101,  // Rd = Tritwise Rs1 & Rs2
    OPCODE_TOR     = 0b111100110011,  // Rd = Tritwise Rs1 | Rs2
    OPCODE_TMAJ    = 0b111100110000,  // Rd = Tritwise Majority
    OPCODE_TADD    = 0b111100110001,  // Rd = Tritwise Rs1 + Rs2
    OPCODE_TMUL    = 0b111100110111,  // Rd = Tritwise Rs1 * Rs2
    OPCODE_MUL     = 0b111100110100,  // Rd = Rs1 * Rs2
    OPCODE_MULU    = 0b111100110101,  // Rd = (Rs1 * Rs2) >> 27

    OPCODE_NOP     = 0b000000000000,  // NOP

} TriOpcode;



// | -- | 4 OpCode | 3 R1 |
// | -0 | 4 OpCode | 3 R1 |
// | -1 | 7 OpCode        |
// | 0- | 6 OpCode     | 4 Immed | 3 R1 | 3 R2 |
// | XX | 7 OpCode        | 6 Immed     | 3 R1 |
// | 00 | 7 OpCode        | 3 R1 | 3 R2 | 3 R3 |
// | 1- | 7 OpCode        | 3 R1 | 3 R2 | 3 12 Immediate |


// MV Rd, Rs     | ADD Rd, Rs, R0
// MV Rd, immed  | ADDI Rd, R0, immed
// MV Rd, imm27  | POP Rd, PC+3
//               | imm27
// NEG Rd, Rs    | SUB Rd, R0, Rs
// TNOT Rd, Rs   | SUB Rd, R0, Rs

// MVC2S         | ADDC R0, R0, R0
// CLRCS         | ADDR R0, R0, R0
// CMP R1, R2    | SUB R0, R1, R2
// TST Rs        | SUB R0, Rs, R0
// BEQ rel       | ADDCSEZ PC, PC, rel
// BNE rel       | ADDCSNZ PC, PC, rel
// BLT rel       | ADDCSEN PC, PC, rel
// BGE rel       | ADDCSNN PC, PC, rel
// BLE rel       | ADDCSNP PC, PC, rel
// BGT rel       | ADDCSEP PC, PC, rel
// BRA rel       | ADD PC, PC, rel
// JMP X         | MV PC, X
// CAL X         | MV RR, X
//               | SWP RR, PC
// RET           | MV PC, RR

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


/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/


/**
 * [Description]
 *
 * @param
 * @return
 */
extern void incClock(TriCpu* cpu);

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void getInstruction(TriCpu* cpu);

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void getOperands(TriCpu* cpu);

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void storeResult(TriCpu* cpu);

#endif /* TERNARY_CPU_H */
/*****************************************************************************/
