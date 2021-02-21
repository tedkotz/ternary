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
 * @file    disassem.c
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * Tools needed to disassemble instruction for the ternary computer.
 *
 */


/* Includes ******************************************************************/
#include "disassem.h"

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
static TriWord expandImmediate( TriWord input )
{
    if( 0b00111111 == input )
    {
        return (-1LL) & TRIWORD_MASK;
    }
    else if ( 0b00010101 == input )
    {
        return (0b00010101010101010101010101010101010101010101010101010101ULL);
    }
    else
    {
        int shift = (ternary2int(input & 0b00111111) + 13) * 2;
        input >>= 6;
        return (input << shift);
    }
}

/**
 * [Description]
 *
 * @param
 * @return
 */
static void printRegister( TriReg reg )
{
    switch( reg )
    {
        case REG_N13     :
            printf("N13");
            break;
        case REG_N12     :
            printf("N12");
            break;
        case REG_N11     :
            printf("N11");
            break;
        case REG_N10     :
            printf("N10");
            break;
        case REG_N09     :
            printf("N9");
            break;
        case REG_N08     :
            printf("N8");
            break;
        case REG_N07     :
            printf("N7");
            break;
        case REG_N06     :
            printf("N6");
            break;
        case REG_N05     :
            printf("N5");
            break;
        case REG_N04     :
            printf("N4");
            break;
        case REG_CLOCK   :
            printf("N3(CLK)");
            break;
        case REG_FLAGS   :
            printf("N2(FLG)");
            break;
        case REG_PC      :
            printf("N1(PC)");
            break;
        case REG_ZERO    :
            printf("Z");
            break;
        case REG_P01     :
            printf("P1");
            break;
        case REG_P02     :
            printf("P2");
            break;
        case REG_P03     :
            printf("P3");
            break;
        case REG_P04     :
            printf("P4");
            break;
        case REG_P05     :
            printf("P5");
            break;
        case REG_P06     :
            printf("P6");
            break;
        case REG_P07     :
            printf("P7");
            break;
        case REG_P08     :
            printf("P8");
            break;
        case REG_P09     :
            printf("P9");
            break;
        case REG_P10     :
            printf("P10");
            break;
        case REG_P11     :
            printf("P11");
            break;
        case REG_P12     :
            printf("P12");
            break;
        case REG_P13     :
            printf("P13");
            break;
        default:
            printf("Runk");
    }
}


/**
 * [Description]
 *
 * @param
 * @return
 */
static void printRegMod( Tryte mod )
{
    int shift=ternary2int(mod);
    switch( mod )
    {
        case OPMOD_NEG :
            printf("_NEG");
            break;
        case OPMOD_INC :
            printf("_INC");
            break;
        case OPMOD_DEC :
            printf("_DEC");
            break;
        case OPMOD_ABN :
            printf("_ABN");
            break;
        case OPMOD_ABS :
            printf("_ABS");
            break;
        case OPMOD_FLT :
            printf("_FLT");
            break;
        case OPMOD_NOP :
            break;
        default:
            if (shift > 26 || shift < -26 )
            {
                printf("_UNK");
            }
            else if( shift < 0 )
            {
                printf(">>%d", -shift);
            }
            else
            {
                printf("<<%d", shift);
            }
    }
}

/**
 * [Description]
 *
 * @param
 * @return
 */
static InstructionFormat printOpcode(TriOpcode op)
{
    switch (op)
    {
        case OPCODE_LD1       : printf("LD1");       return (INSTFORMAT_2REG);
        case OPCODE_LD2       : printf("LD2");       return (INSTFORMAT_2REG);
        case OPCODE_LD3       : printf("LD3");       return (INSTFORMAT_2REG);
        case OPCODE_ST1       : printf("ST1");       return (INSTFORMAT_2REG);
        case OPCODE_ST2       : printf("ST2");       return (INSTFORMAT_2REG);
        case OPCODE_ST3       : printf("ST3");       return (INSTFORMAT_2REG);
        case OPCODE_POP       : printf("POP");       return (INSTFORMAT_2REG);
        case OPCODE_PSH       : printf("PSH");       return (INSTFORMAT_2REG);
//      case OPCODE_          : printf("        ");  return (INSTFORMAT_2REG);
        case OPCODE_ADC       : printf("ADC");       return (INSTFORMAT_3REG);
        case OPCODE_ADD       : printf("ADD");       return (INSTFORMAT_3REG);
        case OPCODE_ADS       : printf("ADS");       return (INSTFORMAT_3REG);
        case OPCODE_ADCI      : printf("ADCI");      return (INSTFORMAT_2REG);
        case OPCODE_ADDI      : printf("ADDI");      return (INSTFORMAT_2REG);
        case OPCODE_ADSI      : printf("ADSI");      return (INSTFORMAT_1REG_2IMM);
        case OPCODE_MUL       : printf("MUL");       return (INSTFORMAT_3REG);
        case OPCODE_MULU      : printf("MULU");      return (INSTFORMAT_3REG);
        case OPCODE_MULI      : printf("MULI");      return (INSTFORMAT_2REG);

        case OPCODE_RTL       : printf("RTL");       return (INSTFORMAT_3REG);
//      case OPCODE_          : printf("        ");  return (INSTFORMAT_2REG);
        case OPCODE_TAND      : printf("TAND");      return (INSTFORMAT_3REG);
        case OPCODE_TOR       : printf("TOR");       return (INSTFORMAT_3REG);
        case OPCODE_TMAJ      : printf("TMAJ");      return (INSTFORMAT_3REG);
        case OPCODE_TADD      : printf("TADD");      return (INSTFORMAT_3REG);
        case OPCODE_TMUL      : printf("TMUL");      return (INSTFORMAT_3REG);
        case OPCODE_TMIN      : printf("TMIN");      return (INSTFORMAT_3REG);
        case OPCODE_TMAX      : printf("TMAX");      return (INSTFORMAT_3REG);
        case OPCODE_RTLI      : printf("RTLI");      return (INSTFORMAT_2REG);
//      case OPCODE_          : printf("        ");  return (INSTFORMAT_2REG);
        case OPCODE_TANDI     : printf("TANDI");     return (INSTFORMAT_2REG);
        case OPCODE_TORI      : printf("TORI");      return (INSTFORMAT_2REG);
        case OPCODE_TMAJI     : printf("TMAJI");     return (INSTFORMAT_2REG);
        case OPCODE_TADDI     : printf("TADDI");     return (INSTFORMAT_2REG);
        case OPCODE_TMULI     : printf("TMULI");     return (INSTFORMAT_2REG);
        case OPCODE_TMINI     : printf("TMINI");     return (INSTFORMAT_2REG);
        case OPCODE_TMAXI     : printf("TMAXI");     return (INSTFORMAT_2REG);

        case OPCODE_NOP       : printf("NOP");       return (INSTFORMAT_NOP);
        default:
            printf("Unknown Opcode");return (INSTFORMAT_NOP);
    }
}



/*
 * See Header
 *
 */
void parseInstruction( TriOpInstruction* fields, TriWord inst )
{
    // | 4 Immediate | 7 R3+Mod | 7 R2+Mod | 3 R1 | 6 OpCode |
    // | 11 Immediate           | 7 R2+Mod | 3 R1 | 6 OpCode |
    // | 18 Immediate                      | 3 R1 | 6 OpCode |
    // | 9 Immediate2    | 9 Immediate1    | 3 R1 | 6 OpCode |
    fields->opcode = inst & 0x0FFF;
    fields->r1 = (inst >> 12 ) & 0x003F;
    fields->r2mod = (inst >> 18 ) & 0x00FF;
    fields->r2 = (inst >> 26 ) & 0x003F;
    fields->r3mod = (inst >> 32 ) & 0x00FF;
    fields->r3 = (inst >> 40 ) & 0x003F;
    //fields->imm4 = expandImmediate((inst >> 46 ) & 0x00FF);
    fields->imm11 = expandImmediate((inst >> 32 ) & 0x003FFFFF);
    fields->imm9_1 = expandImmediate((inst >> 18 ) & 0x003FFFF);
    fields->imm9_2 = expandImmediate((inst >> 36 ) & 0x003FFFF);
    //fields->imm18 = expandImmediate((inst >> 18 ) & 0x0FFFFFFFFFULL);
}

/*
 * See Header
 *
 */
void printInstruction( TriWord inst )
{
    TriOpInstruction fields;
    parseInstruction( &fields, inst);
    switch( printOpcode( fields.opcode ) )
    {
        case INSTFORMAT_NOP:
            break;
        case INSTFORMAT_1REG:
//            printf("  ");
//            printRegister(fields.r1);
//            printf(", #");
//            ternaryPrint(fields.imm18, 0);
            break;
        case INSTFORMAT_2REG:
            printf("  ");
            printRegister(fields.r1);
            printf(", ");
            printRegister(fields.r2);
            printRegMod(fields.r2mod);
            printf(", #");
            ternaryPrint(fields.imm11, 0);
            break;
        case INSTFORMAT_3REG:
            printf("  ");
            printRegister(fields.r1);
            printf(", ");
            printRegister(fields.r2);
            printRegMod(fields.r2mod);
            printf(", ");
            printRegister(fields.r3);
            printRegMod(fields.r3mod);
            break;
        case INSTFORMAT_1REG_2IMM:
            printf("  ");
            printRegister(fields.r1);
            printf(", #");
            ternaryPrint(fields.imm9_1, 0);
            printf(", #");
            ternaryPrint(fields.imm9_2, 0);
            break;

        //default:
            // Do nothing
    }
}
