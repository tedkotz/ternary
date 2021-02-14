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
#define TRITS_PER_WORD 27
#define BITS_PER_TRIWORD ( TRITS_PER_WORD * BITS_PER_TRIT)
#define TRIWORD_MASK ((1ULL << BITS_PER_TRIWORD) - 1)

#define TRITS_PER_TRYTE ( 9 )
#define BITS_PER_TRYTE ( TRITS_PER_TRYTE * BITS_PER_TRIT )
#define TRYTES_PER_TRIWORD (3)
#define TRYTE_MASK (( 1UL << BITS_PER_TRYTE ) - 1)

#define PRITRIWORD PRIx64
#define SCNTRIWORD SCNi64

/* Types *********************************************************************/
typedef trint32_t TriWord;
typedef trint16_t Tryte;

typedef enum TriReg
{
    REG_N13        = 0b111111,
    REG_N12        = 0b111100,
    REG_N11        = 0b111101,
    REG_N10        = 0b110011,
    REG_N09        = 0b110000,
    REG_N08        = 0b110001,
    REG_N07        = 0b110111,
    REG_N06        = 0b110100,
    REG_N05        = 0b110101,
    REG_N04        = 0b001111,
    REG_CLOCK      = 0b001100,
    REG_FLAGS      = 0b001101,
    REG_PC         = 0b000011,
    REG_ZERO       = 0b000000,
    REG_P01        = 0b000001,
    REG_P02        = 0b000111,
    REG_P03        = 0b000100,
    REG_P04        = 0b000101,
    REG_P05        = 0b011111,
    REG_P06        = 0b011100,
    REG_P07        = 0b011101,
    REG_P08        = 0b010011,
    REG_P09        = 0b010000,
    REG_P10        = 0b010001,
    REG_P11        = 0b010111,
    REG_P12        = 0b010100,
    REG_P13        = 0b010101,
} TriReg;
//#define	NUM_TRIREGS (3*3*3)
#define	NUM_TRIREGS (0b111111)

typedef struct TriFlags
{
    trint32_t S :2 ; // Sign
    trint32_t C :2 ; // Carry
    trint32_t V :2 ; // Overflow
    trint32_t P :2 ; // Parity
    trint32_t I :2 ; // Interrupts
} TriFlags;

typedef union FlagReg
{
    TriWord val;
    TriFlags flags;
} FlagReg;


typedef struct TriCpu
{
//	TriWord A;
//	TriWord B;
//	TriWord D;
//	TriWord valA;
//	TriWord valB;
    TriWord regs[NUM_TRIREGS];
//	uint8_t running;
} TriCpu;


typedef enum TriOpcode
{
    //                   __--__--__--
    OPCODE_LD1       = 0b111111111111,  // Load Rd <- (Rs+immediate) 9 trits
    OPCODE_LD2       = 0b111111111100,  // Load Rd <- (Rs+immediate) 18 trits
    OPCODE_LD3       = 0b111111111101,  // Load Rd <- (Rs+immediate) 27 trits
    OPCODE_ST1       = 0b111111110011,  // Store (Rs1+immediate) <- Rs2 9 trits
    OPCODE_ST2       = 0b111111110000,  // Store (Rs1+immediate) <- Rs2 18 trits
    OPCODE_ST3       = 0b111111110001,  // Store (Rs1+immediate) <- Rs2 27 trits
    OPCODE_POP       = 0b111111110111,  // Load Rd <- (Rs) ; Rs += immediate
    OPCODE_PSH       = 0b111111110100,  // Store Rd += immediate; (Rd)  <- Rs
//  OPCODE_          = 0b111111110101,  //
    //                   __--__--__--
    OPCODE_ADC       = 0b111111001111,  // C:Rd = Rs1 + Rs2 + C
    OPCODE_ADD       = 0b111111001100,  // C:Rd = Rs1 + Rs2
    OPCODE_ADS       = 0b111111001101,  // if S==1 then C:Rd = Rd + Rs1; if S==- then C:Rd = Rd + Rs2
    OPCODE_ADCI      = 0b111111000011,  // C:Rd = Rs1 + immediate + C
    OPCODE_ADDI      = 0b111111000000,  // C:Rd = Rs1 + immediate
    OPCODE_ADSI      = 0b111111000001,  // if S==1 then C:Rd = Rd + imm1; if S==- then C:Rd = Rd + imm2
    OPCODE_MUL       = 0b111111000111,  // Rd = Rs1 * Rs2
    OPCODE_MULU      = 0b111111000100,  // Rd = (Rs1 * Rs2) >> 27
//  OPCODE_          = 0b111111000101,  //
    //                   __--__--__--
//  OPCODE_          = 0b111111011111,  //
//  OPCODE_          = 0b111111011100,  //
//  OPCODE_          = 0b111111011101,  //
//  OPCODE_          = 0b111111010011,  //
//  OPCODE_          = 0b111111010000,  //
//  OPCODE_          = 0b111111010001,  //
//  OPCODE_          = 0b111111010111,  //
//  OPCODE_          = 0b111111010100,  //
//  OPCODE_          = 0b111111010101,  //
    //                   __--__--__--
    OPCODE_RTL       = 0b111100111111,  // R1:R2 = R1:R2 Rotate Left by R3
//  OPCODE_          = 0b111100111100,  //
    OPCODE_TAND      = 0b111100111101,  // Rd = Tritwise Rs1 & Rs2
    OPCODE_TOR       = 0b111100110011,  // Rd = Tritwise Rs1 | Rs2
    OPCODE_TMAJ      = 0b111100110000,  // Rd = Tritwise Majority
    OPCODE_TADD      = 0b111100110001,  // Rd = Tritwise Rs1 + Rs2
    OPCODE_TMUL      = 0b111100110111,  // Rd = Tritwise Rs1 * Rs2
    OPCODE_TMIN      = 0b111100110100,  // Rd = Tritwise MIN(Rs1, Rs2)
    OPCODE_TMAX      = 0b111100110101,  // Rd = Tritwise MAX(Rs1, Rs2)
    //                   __--__--__--
    OPCODE_RTLI      = 0b111100001111,  // R1:R2 = R1:R2 Rotate Left by immed
//  OPCODE_          = 0b111100001100,  //
    OPCODE_TANDI     = 0b111100001101,  // Rd = Tritwise Rs1 & immediate
    OPCODE_TORI      = 0b111100000011,  // Rd = Tritwise Rs1 | immediate
    OPCODE_TMAJI     = 0b111100000000,  // Rd = Tritwise Majority
    OPCODE_TADDI     = 0b111100000001,  // Rd = Tritwise Rs1 + immediate
    OPCODE_TMULI     = 0b111100000111,  // Rd = Tritwise Rs1 * immediate
    OPCODE_TMINI     = 0b111100000100,  // Rd = Tritwise MIN(Rs1, immediate)
    OPCODE_TMAXI     = 0b111100000101,  // Rd = Tritwise MAX(Rs1, immediate)

    OPCODE_NOP       = 0b000000000000,  // NOP

} TriOpcode;


typedef enum
{
    OPMOD_NEG = 0b11111111,
    OPMOD_INC = 0b11111100,
    OPMOD_DEC = 0b11111101,
    OPMOD_ABN = 0b11110011,
    OPMOD_ABS = 0b11110000,
    OPMOD_FLT = 0b11110001,
//  OPMOD_SHR = 0b11000001,
    OPMOD_NOP = 0b00000000,
//  OPMOD_SHL = 0b01000011,
} OpModifiers;

// Proposal allow every possible 1 input transform (there are 27)
//  typedef enum
//  {
//  //                  1 0 -1
//      OPMOD_NEG = 0b11110001,
//      OPMOD_INC = 0b11110100,
//      OPMOD_DEC = 0b11001101,
//      OPMOD_ABN = 0b11110011,
//      OPMOD_ABS = 0b11010001,
//      OPMOD_FLT = 0b11010000,
//      OPMOD_NOP = 0b11010011,
//  //  OPMOD_SHR = 0b00000000,
//  //  OPMOD_SHL = 0b01000000,
//  } OpModifiers;



// | 4 Immediate | 7 R3+Mod | 7 R2+Mod | 3 R1 | 6 OpCode |
// | 11 Immediate           | 7 R2+Mod | 3 R1 | 6 OpCode |
// | 18 Immediate                      | 3 R1 | 6 OpCode |
// | 9 Immediate     | 9 Immediate     | 3 R1 | 6 OpCode |


// 4 bit Immeditate
// 0--- -> 27 Neg
// 0+++ -> 27 Pos
// 0000 -> 27 Zero
// 1xxx -> 1 << X + 13
// -xxx -> - << X + 13

// 5-20 bit Immeditate
// 0..0--- -> 27 Neg
// 0..0+++ -> 27 Pos
// 0..0000 -> 27 Zero
// n..nxxx -> N << X + 13

// 21-26 bit Immeditate
// 0..0-- -> 27 Neg
// 0..0++ -> 27 Pos
// 0..000 -> 27 Zero
// n..nxx -> N << X + 4


// Rx + Mod
// rrrmmmm
// R selects Register
// M selects Modification
// |  M      | Operation                                   |
// |---------|---------------------------------------------|
// | -40     | Negate/Tritwise Not (0->0, -1<->1)          |
// | -39     | Tritwise Increment (0->1->-1->0)            |
// | -38     | Tritwise Decrement (0->-1->1->0)            |
// | -37     | Tritwise Absolute Value (-1 -> 1)           |
// | -36     | Tritwise Absolute Value Negated (1 -> -1)   |
// | -35     | Tritwise Flatten (-1->0)                    |
// |         |                                             |
// | -26..26 | Left shift by M                             |
// |         |                                             |


// MV Rd, Rs     | ADD Rd, Rs, R0
// MV Rd, immed  | ADDI Rd, R0, immed
// MV Rd, imm27  | POP Rd, PC+3
//               | imm27
// NEG Rd, Rs    | SUB Rd, R0, Rs
// TNOT Rd, Rs   | SUB Rd, R0, Rs

// SWP R1, R2    | RTL R1, R2, #27
// SHL Rd, Rs    | RTL R0, Rd, Rs
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



/* Interfaces ****************************************************************/
/* Data **********************************************************************/
/* Functions *****************************************************************/


/**
 * [Description]
 *
 * @param
 * @return
 */
extern void resetCPU(TriCpu* cpu);

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void printCpuState(TriCpu* cpu);

/**
 * [Description]
 *
 * @param
 * @return
 */
extern void runCPU( TriCpu* cpu, int cycles );


#endif /* TERNARY_CPU_H */
/*****************************************************************************/
