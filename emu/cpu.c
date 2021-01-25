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

#include <stdio.h>
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

// typedef union
// {
//     TriWord val;
//     struct {
//     TriWord Reserved:6;  // for future use
//     TriWord Cond:6;      // conditional flag
//     TriWord CondValue:2; // conditional test value
//     TriWord OpCnt:2;     // number of operators
//     TriWord OpCode:12;   // instruction number
//     TriWord Op3:10;      // OP2 = OP3 + MOD(OP1)
//     TriWord Op2:10;      // OP2 = OP2 + MOD(OP1)
//     TriWord Op1:10;      // OP1 = + MOD(OP1)
//     TriWord OpMod:4;     // ALU MOdifier to apply to OP1
//     } parts;
// } InstReg;
//
//
//
// int evalConditon(TriCpu* cpu)
// {
//     InstReg INST;
//     FlagReg FLGS;
//     INST.val=cpu->regs[REG_INST];
//     FLGS.val=cpu->regs[REG_FLAGS];
//     switch (INST.parts.Cond)
//     {
//         case COND_SE:
//             return( FLGS.flags.S == INST.parts.CondValue );
//         case COND_SN:
//             return( FLGS.flags.S != INST.parts.CondValue );
//         case COND_CE:
//             return( FLGS.flags.C == INST.parts.CondValue );
//         case COND_CN:
//             return( FLGS.flags.C != INST.parts.CondValue );
//         case COND_ZE:
//             return( 0 == INST.parts.CondValue );
//         case COND_VE:
//             return( FLGS.flags.V == INST.parts.CondValue );
//         case COND_VN:
//             return( FLGS.flags.V != INST.parts.CondValue );
//         case COND_PE:
//             return( FLGS.flags.P == INST.parts.CondValue );
//         case COND_PN:
//             return( FLGS.flags.P != INST.parts.CondValue );
//         default:
// //			callInst(ReadAddr(ADDR_ISR_INV_INSTR));
//             return 0;
//     }
// }
//
// void incClock(TriCpu* cpu)
// {
//     cpu->regs[REG_CLOCK]=TriWord_ADD(cpu->regs[REG_CLOCK], 1);
//
// }
//
// void getInstruction(TriCpu* cpu)
// {
//     cpu->regs[REG_INST]=ReadAddr(cpu->regs[REG_PC]);
//     cpu->regs[REG_PC]=TriWord_ADD(cpu->regs[REG_PC], 1);
//     incClock(cpu);
// }
//
//
// void getOperands(TriCpu* cpu)
// {
//     InstReg INST;
//     INST.val=cpu->regs[REG_INST];
//     if(N!=INST.parts.OpCnt)
//     {
// //		cpu->A=getOP(INST.parts.Op2);
//     }
//     else
//     {
//         cpu->A=0;
//     }
//     incClock(cpu);
//
//
//     if((N!=INST.parts.OpCnt) || (0!=INST.parts.OpCode))
//     {
// //		cpu->B=getOP(INST.parts.Op1);
//         if(N==INST.parts.OpMod)
//         {
//             cpu->B=TriWord_NEGB(cpu->B);
//         }
//     }
//     else
//     {
//         cpu->B=0;
//     }
//     incClock(cpu);
//
// }
// //
// void storeResult(TriCpu* cpu)
// {
// //	InstReg INST;
// //	INST.val=cpu->regs[REG_INST];
//     cpu->regs[REG_INST]=ReadAddr((cpu->regs[REG_PC])++);
//     cpu->regs[REG_CLOCK]++;
// }


TriWord ReadTriWord( TriCpu* cpu, TriWord addr )
{
    TriWord tmp = ReadAddr(addr);
    tmp |= (TriWord)ReadAddr(TriWord_ADD(addr, 0b0001)) << (BITS_PER_TRYTE);
    tmp |= (TriWord)ReadAddr(TriWord_ADD(addr, 0b0111)) << (2 * BITS_PER_TRYTE);
    cpu->regs[REG_CLOCK]=TriWord_ADD(cpu->regs[REG_CLOCK], 0b0100);
    return tmp;
}

void WriteTriWord( TriCpu* cpu, TriWord addr , TriWord val )
{
    WriteAddr(addr , val & 0x03FFFF);
    WriteAddr(TriWord_ADD(addr, 0b0001), (val >>     (BITS_PER_TRYTE)) & 0x03FFFF );
    WriteAddr(TriWord_ADD(addr, 0b0111), (val >> (2 * BITS_PER_TRYTE)) & 0x03FFFF );
    cpu->regs[REG_CLOCK]=TriWord_ADD(cpu->regs[REG_CLOCK], 0b0100);
}

Tryte ReadTryte( TriCpu* cpu, TriWord addr )
{
    cpu->regs[REG_CLOCK]=TriWord_ADD(cpu->regs[REG_CLOCK], 0b01);
    return ReadAddr(addr);
}

void WriteTryte( TriCpu* cpu, TriWord addr , Tryte val )
{
    WriteAddr(addr , val );
    cpu->regs[REG_CLOCK]=TriWord_ADD(cpu->regs[REG_CLOCK], 0b01);
}

TriWord ReadModReg( TriCpu* cpu, Tryte reg, Tryte mod )
{
    int32_t shift=TriWord2int(mod);
    switch (mod)
    {
        default:
            if (shift > 26 || shift < -26 )
            {
                printf("\nInvalid  mod: %X\n", mod);
                return cpu->regs[reg];
            }
            else if( shift < 0 )
            {
                return cpu->regs[reg] >> (-2 * shift);
            }
            else
            {
                return (cpu->regs[reg] << (2 * shift)) & ((1ULL << 54) - 1);
            }
    }
}

TriWord expandImmediate( TriWord input )
{
    if( 0b00111111 == input )
    {
        return (-1LL) & ((1ULL << 54) - 1);
    }
    else if ( 0b00010101 == input )
    {
        return (-1LL) & ((1ULL << 54) - 1);
    }
    else
    {
        int shift = (TriWord2int(input & 0b00111111) + 13) * 2;
        input >>= 6;
        return (input << shift);
    }
}

void printCpuState(TriCpu* cpu)
{
    TriCpu disposable;
    Tryte i = 0b00111111;
    int x = -13;
    printf("       876543210876543210876543210\n");
    while( 0b00010101 != i )
    {
        printf(" %03d : ", x);
        TriWordPrint(cpu->regs[i], 1);
        printf("(%"PRIi64")\n", TriWord2int(cpu->regs[i]));
        i=TriWord_ADD(i, 0b0001);
        ++x;
    }
    printf("       876543210876543210876543210\n");
    printf("      |Imm|R3+Mod|R2+Mod|R1|OpCode|\nINST : ");
    disposable.regs[REG_PC]=0;
    disposable.regs[REG_CLOCK]=0;
    TriWordPrint(ReadTriWord(&disposable, cpu->regs[REG_PC]),1);
    printf("\n");
}


void resetCPU(TriCpu* cpu)
{
    int i;
    for( i=0; i<NUM_TRIREGS; ++i)
    {
        cpu->regs[i]=0;
    }
    cpu->regs[REG_PC]=ReadTriWord(cpu, ADDR_PC_START0);
}

void runCPU( TriCpu* cpu, int cycles )
{
    TriWord inst=0;
    TriWord imm4;
    TriWord imm11;
    TriWord imm18;
    TriWord addr;
    Tryte opcode;
    Tryte r1;
    Tryte r2;
    Tryte r2mod;
    Tryte r3;
    Tryte r3mod;

    while( cycles-- > 0 )
    {
        inst = ReadTriWord(cpu, cpu->regs[REG_PC]);
        cpu->regs[REG_PC]=TriWord_ADD(cpu->regs[REG_PC], 0b0100);

        // | 4 Immediate | 7 R3+Mod | 7 R2+Mod | 3 R1 | 6 OpCode |
        // | 11 Immediate           | 7 R2+Mod | 3 R1 | 6 OpCode |
        // | 18 Immediate                      | 3 R1 | 6 OpCode |
        opcode = inst & 0x0FFF;
        r1 = (inst >> 12 ) & 0x003F;
        r2mod = (inst >> 18 ) & 0x00FF;
        r2 = (inst >> 26 ) & 0x003F;
        r3mod = (inst >> 32 ) & 0x00FF;
        r3 = (inst >> 40 ) & 0x003F;
        imm4 = expandImmediate((inst >> 46 ) & 0x00FF);
        imm11 = expandImmediate((inst >> 32 ) & 0x003FFFFF);
        imm18 = expandImmediate((inst >> 18 ) & 0x0FFFFFFFFFULL);

        switch( opcode )
        {
            case OPCODE_NOP       :  // NOP
                break;
            case OPCODE_LD1       :  // Load Rd <- (Rs+immediate) 9 trits
                cpu->regs[r1]=ReadTryte(cpu, TriWord_ADD(ReadModReg(cpu, r2, r2mod), imm11));
                printf("LD1: ");
                printf("\n R1: ");TriWordPrint(r1, 0);
                printf("\n R2: ");TriWordPrint(r2, 0);
                printf("\n R2MOD: ");TriWordPrint(r2mod, 0);
                printf("\n IMM11: ");TriWordPrint(imm11, 1);
                printf("\n");
                break;
            case OPCODE_LD2       :  // Load Rd <- (Rs+immediate) 18 trits
                addr = TriWord_ADD(ReadModReg(cpu, r2, r2mod), imm11);
                cpu->regs[r1]=ReadTryte(cpu, addr);
                cpu->regs[r1]|=((TriWord)ReadTryte(cpu, TriWord_ADD(addr, 0b0001))<<18) ;
                break;
            case OPCODE_LD3       :  // Load Rd <- (Rs+immediate) 27 trits
                cpu->regs[r1]=ReadTriWord(cpu, TriWord_ADD(ReadModReg(cpu, r2, r2mod), imm11));
                break;
            case OPCODE_ST1       :  // Store (Rs1+immediate) <- Rs2 9 trits
            case OPCODE_ST2       :  // Store (Rs1+immediate) <- Rs2 18 trits
            case OPCODE_ST3       :  // Store (Rs1+immediate) <- Rs2 27 trits
            case OPCODE_POP       :  // Load Rd <- (Rs) ; Rs += immediate
            case OPCODE_PSH       :  // Store Rd += immediate; (Rd)  <- Rs
//          case OPCODE_          :  //
            case OPCODE_ADD_SEN   :  // if S==- , C:Rd = Rs1 - Rs2
            case OPCODE_ADD_SEZ   :  // if S==0 , C:Rd = Rs1 - Rs2
            case OPCODE_ADD_SEP   :  // if S==1 , C:Rd = Rs1 - Rs2
            case OPCODE_ADC       :  // C:Rd = Rs1 - Rs2 + C
            case OPCODE_ADD       :  // C:Rd = Rs1 - Rs2
//          case OPCODE_          :  //
            case OPCODE_ADD_SNN   :  // if S!=- , C:Rd = Rs1 - Rs2
            case OPCODE_ADD_SNZ   :  // if S!=0 , C:Rd = Rs1 - Rs2
            case OPCODE_ADD_SNP   :  // if S!=1 , C:Rd = Rs1 - Rs2
            case OPCODE_ADDI_SEN  :  // if S==- , C:Rd = Rs + immediate
            case OPCODE_ADDI_SEZ  :  // if S==0 , C:Rd = Rs + immediate
            case OPCODE_ADDI_SEP  :  // if S==1 , C:Rd = Rs + immediate
            case OPCODE_ADCI      :  // C:Rd = Rs1 + immediate + C
            case OPCODE_ADDI      :  // C:Rd = Rs1 + immediate
//          case OPCODE_          :  //
            case OPCODE_ADDI_SNN  :  // if S!=- , C:Rd = Rs + immediate
            case OPCODE_ADDI_SNZ  :  // if S!=0 , C:Rd = Rs + immediate
            case OPCODE_ADDI_SNP  :  // if S!=1 , C:Rd = Rs + immediate
            case OPCODE_RTL       :  // R1:R2 = R1:R2 Rotate Left by R3
//          case OPCODE_          :  //
            case OPCODE_TAND      :  // Rd = Tritwise Rs1 & Rs2
            case OPCODE_TOR       :  // Rd = Tritwise Rs1 | Rs2
            case OPCODE_TMAJ      :  // Rd = Tritwise Majority
            case OPCODE_TADD      :  // Rd = Tritwise Rs1 + Rs2
            case OPCODE_TMUL      :  // Rd = Tritwise Rs1 * Rs2
            case OPCODE_MUL       :  // Rd = Rs1 * Rs2
            case OPCODE_MULU      :  // Rd = (Rs1 * Rs2) >> 27
            case OPCODE_RTLI      :  // R1:R2 = R1:R2 Rotate Left by immed
//          case OPCODE_          :  //
            case OPCODE_TANDI     :  // Rd = Tritwise Rs1 & immediate
            case OPCODE_TORI      :  // Rd = Tritwise Rs1 | immediate
            case OPCODE_TMAJI     :  // Rd = Tritwise Majority
            case OPCODE_TADDI     :  // Rd = Tritwise Rs1 + immediate
            case OPCODE_TMULI     :  // Rd = Tritwise Rs1 * immediate
//          case OPCODE_          :  //
//          case OPCODE_          :  //
            default:
                printf("\nInvalid  Opcode: %X\n", opcode);


        }

    }
}

