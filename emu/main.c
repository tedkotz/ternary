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
 * @file    main.c
 * @author  Ted Kotz <ted@kotz.us>
 * @version 0.1
 *
 * The main program for the Ternary Computer Emulator. This file plumbs
 * together all the parts of the system and kicks it off.
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
 * Main Program entry point.
 *
 * @param argc number of command line arguments
 * @param argv array of pointers to command line arguments
 * @return 0 if successful, otherwise error code
 */
int main( int argc, char** argv )
{
    char c='\r';
    TriCpu cpu;
    TriWord addr;
    TriWord val;
    TriCpu disposable;
    resetMem();
    resetCPU(&disposable);
    resetCPU(&cpu);
    printCpuState(&cpu);
    c=getchar();
    while ('q' != c)
    {
        switch(c)
        {
            case 'r':
                printf("ADDR: ");
                TriWordScan( &addr );
                printf("\nVAL: ");
                val = ReadAddr(addr);
                TriWordPrint( val, 0 );
                printf("\n");
                break;
            case 'w':
                printf("ADDR: ");
                TriWordScan( &addr );
                printf("\nVAL: ");
                TriWordScan( &val );
                WriteAddr(addr, val);
                printf("done.\n");
                break;
            case 'd':
                printCpuState(&cpu);
                break;
            default:
                runCPU(&cpu, 1);
                printCpuState(&cpu);
        }
        c=getchar();
    }
    return 0;
}
