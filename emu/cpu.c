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

static const char* reg_names[] =
{
    "GP_13",
    "GP_12",
    "GP_11",
    "GP_10",
    "GP_09",
    "GP_08",
    "GP_07",
    "GP_06",
    "GP_05",
    "RSRVD",
    "CLOCK",
    "FLAGS",
    "PC   ",
    "ZERO ",
    "GP01 ",
    "GP02 ",
    "GP03 ",
    "GP04 ",
    "GP05 ",
    "GP06 ",
    "GP07 ",
    "GP08 ",
    "GP09 ",
    "GP10 ",
    "GP11 ",
    "GP12 ",
    "GP13 ",
};

/* Functions *****************************************************************/

/**
 * [Description]
 *
 * @param
 * @return
 */
TriWord ReadTriWord( TriCpu* cpu, TriWord addr )
{
    TriWord tmp = ReadAddr(addr);
    tmp |= (TriWord)ReadAddr(ternaryADD(addr, 0b0001)) << (BITS_PER_TRYTE);
    tmp |= (TriWord)ReadAddr(ternaryADD(addr, 0b0111)) << (2 * BITS_PER_TRYTE);
    cpu->regs[REG_CLOCK]=ternaryADD(cpu->regs[REG_CLOCK], 0b0100);
    return tmp;
}


/**
 * [Description]
 *
 * @param
 * @return
 */
void WriteTriWord( TriCpu* cpu, TriWord addr , TriWord val )
{
    WriteAddr(addr , val & TRYTE_MASK);
    WriteAddr(ternaryADD(addr, 0b0001), (val >>     (BITS_PER_TRYTE)) & TRYTE_MASK );
    WriteAddr(ternaryADD(addr, 0b0111), (val >> (2 * BITS_PER_TRYTE)) & TRYTE_MASK );
    cpu->regs[REG_CLOCK]=ternaryADD(cpu->regs[REG_CLOCK], 0b0100);
}


/**
 * [Description]
 *
 * @param
 * @return
 */
Tryte ReadTryte( TriCpu* cpu, TriWord addr )
{
    cpu->regs[REG_CLOCK]=ternaryADD(cpu->regs[REG_CLOCK], 0b01);
    return ReadAddr(addr);
}


/**
 * [Description]
 *
 * @param
 * @return
 */
void WriteTryte( TriCpu* cpu, TriWord addr , Tryte val )
{
    WriteAddr(addr , val );
    cpu->regs[REG_CLOCK]=ternaryADD(cpu->regs[REG_CLOCK], 0b01);
}


/**
 * [Description]
 *
 * @param
 * @return
 */
TriWord ReadModReg( TriCpu* cpu, Tryte reg, Tryte mod )
{
    int32_t shift=ternary2int(mod);
    TriWord val=0;
    if( 0 != reg )
    {
        val = cpu->regs[reg];
    }

    switch (mod)
    {
        case OPMOD_NEG:
            return ternaryNEGB(val);

        case OPMOD_INC:
            return ternaryINCB(val);

        case OPMOD_DEC:
            return ternaryDECB(val);

        case OPMOD_ABN:
            return ternaryNEGB(ternaryABSB(val));

        case OPMOD_ABS:
            return ternaryABSB(val);

        case OPMOD_FLT:
            return ternaryFLTB(val);

        default:
            if (shift > 26 || shift < -26 )
            {
                printf("\nInvalid  mod: %X\n", mod);
                return val;
            }
            else if( shift < 0 )
            {
                return val >> (-2 * shift);
            }
            else
            {
                return (val << (2 * shift)) & ((1ULL << 54) - 1);
            }
    }
}

/**
 * [Description]
 *
 * @param
 * @return
 */
void SetSignTrit( TriCpu* cpu, TriWord val )
{
    FlagReg tmp;
    tmp.val=cpu->regs[REG_FLAGS];
    tmp.flags.S=ternarySGN(val);
    cpu->regs[REG_FLAGS]=tmp.val;
}

/**
 * [Description]
 *
 * @param
 * @return
 */
void WriteReg( TriCpu* cpu, Tryte reg, TriWord val )
{
    if( 0 != reg )
    {
        cpu->regs[reg] = val;
    }
}

/**
 * [Description]
 *
 * @param
 * @return
 */
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
        int shift = (ternary2int(input & 0b00111111) + 13) * 2;
        input >>= 6;
        return (input << shift);
    }
}

/*
 * See Header
 *
 */
void printCpuState(TriCpu* cpu)
{
    TriCpu disposable;
    Tryte i = 0b00111111;
    int x = -13;
    printf("             876543210876543210876543210\n");
    while( 0b00010101 != i )
    {
        printf(" %s %03d : ", reg_names[x+13], x);
        ternaryPrint(cpu->regs[i], TRITS_PER_WORD);
        printf("(%"PRIi64")\n", ternary2int(cpu->regs[i]));
        i=ternaryADD(i, 0b0001);
        ++x;
    }
    printf("             876543210876543210876543210\n");
    printf("            |    Immed 18     |R1|OpCode|\n");
    printf("            | Immed 11 |R2+Mod|R1|OpCode|\n");
    printf("            |Im4|R3+Mod|R2+Mod|R1|OpCode|\n Next INST > ");
    disposable.regs[REG_PC]=0;
    disposable.regs[REG_CLOCK]=0;
    ternaryPrint(ReadTriWord(&disposable, cpu->regs[REG_PC]),TRITS_PER_WORD);
    printf("\n");
}


/*
 * See Header
 *
 */
void resetCPU(TriCpu* cpu)
{
    int i;
    for( i=0; i<NUM_TRIREGS; ++i)
    {
        cpu->regs[i]=0;
    }
    cpu->regs[REG_PC]=ReadTriWord(cpu, ADDR_PC_START0);
}

/*
 * See Header
 *
 */
void runCPU( TriCpu* cpu, int cycles )
{
    TriWord inst=0;
//    TriWord imm4;
    TriWord imm11;
//    TriWord imm18;
    TriWord addr;
    TriWord val;
    Tryte opcode;
    Tryte r1;
    Tryte r2;
    Tryte r2mod;
//    Tryte r3;
//    Tryte r3mod;

    while( cycles-- > 0 )
    {
        inst = ReadTriWord(cpu, cpu->regs[REG_PC]);
        cpu->regs[REG_PC]=ternaryADD(cpu->regs[REG_PC], 0b0100);

        // | 4 Immediate | 7 R3+Mod | 7 R2+Mod | 3 R1 | 6 OpCode |
        // | 11 Immediate           | 7 R2+Mod | 3 R1 | 6 OpCode |
        // | 18 Immediate                      | 3 R1 | 6 OpCode |
        opcode = inst & 0x0FFF;
        r1 = (inst >> 12 ) & 0x003F;
        r2mod = (inst >> 18 ) & 0x00FF;
        r2 = (inst >> 26 ) & 0x003F;
//        r3mod = (inst >> 32 ) & 0x00FF;
//        r3 = (inst >> 40 ) & 0x003F;
//        imm4 = expandImmediate((inst >> 46 ) & 0x00FF);
        imm11 = expandImmediate((inst >> 32 ) & 0x003FFFFF);
//        imm18 = expandImmediate((inst >> 18 ) & 0x0FFFFFFFFFULL);

        switch( opcode )
        {
            case OPCODE_NOP       :  // NOP
                break;
            case OPCODE_LD1       :  // Load Rd <- (Rs+immediate) 9 trits
                val = ReadTryte(cpu, ternaryADD(ReadModReg(cpu, r2, r2mod), imm11));
                WriteReg(cpu,r1,val);
                SetSignTrit(cpu, val);
                break;
            case OPCODE_LD2       :  // Load Rd <- (Rs+immediate) 18 trits
                addr = ternaryADD(ReadModReg(cpu, r2, r2mod), imm11);
                val=ReadTryte(cpu, addr);
                val|=((TriWord)ReadTryte(cpu, ternaryADD(addr, 0b0001))<<BITS_PER_TRYTE) ;
                WriteReg(cpu,r1,val);
                SetSignTrit(cpu, val);
                break;
            case OPCODE_LD3       :  // Load Rd <- (Rs+immediate) 27 trits
                val=ReadTriWord(cpu, ternaryADD(ReadModReg(cpu, r2, r2mod), imm11));
                WriteReg(cpu,r1,val);
                SetSignTrit(cpu, val);
                break;
            case OPCODE_ST1       :  // Store (Rs1+immediate) <- Rs2 9 trits
                addr = ternaryADD(ReadModReg(cpu, r1, 0), imm11);
                val = ReadModReg(cpu, r2, r2mod) & TRYTE_MASK ;
                WriteTryte(cpu,addr,val);
                SetSignTrit(cpu, val);
                break;
            case OPCODE_ST2       :  // Store (Rs1+immediate) <- Rs2 18 trits
                addr = ternaryADD(ReadModReg(cpu, r1, 0), imm11);
                val = ReadModReg(cpu, r2, r2mod) & ((1ULL << (2*BITS_PER_TRYTE))-1);
                WriteTryte(cpu,addr,val & TRYTE_MASK);
                WriteTryte(cpu,ternaryADD(addr, 0b0001),(val >> BITS_PER_TRYTE)& TRYTE_MASK);
                SetSignTrit(cpu, val );
                break;
            case OPCODE_ST3       :  // Store (Rs1+immediate) <- Rs2 27 trits
                addr = ternaryADD(ReadModReg(cpu, r1, 0), imm11);
                val = ReadModReg(cpu, r2, r2mod);
                WriteTriWord(cpu,addr,val);
                SetSignTrit(cpu, val);
                break;
            case OPCODE_POP       :  // Load Rd <- (Rs) ; Rs <- Rs + immediate
                addr = ReadModReg(cpu, r2, r2mod);
                val=ReadTriWord(cpu, addr);
                WriteReg(cpu,r1,val);
                WriteReg(cpu,r2,ternaryADD(addr, imm11));
                SetSignTrit(cpu, val);
                break;
            case OPCODE_PSH       :  // Store Rd += immediate; (Rd)  <- Rs
                addr = ternaryADD(ReadModReg(cpu, r1, 0), imm11);
                val = ReadModReg(cpu, r2, r2mod);
                WriteTriWord(cpu,addr,val);
                WriteReg(cpu,r1,addr);
                SetSignTrit(cpu, val);
                break;
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

/*****************************************************************************/
