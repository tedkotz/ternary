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
// 3^11 Trites of RAM
#define RAM_SIZE 177147
#define BASE_OFFSET (RAM_SIZE/2)
#define RAM_ADDR_MASK ((1<<(11*2))-1)

typedef enum
{
    ADDR_ISR_INV_INSTR = -2,
    ADDR_ISR_DIV_ZERO  = -3,
    ADDR_UART_IN       = -4,
	ADDR_UART_OUT      = -5,
	ADDR_RTC           = -6,
	/*BITMAP DISPLAY*/
	/*DAC*/
	/*ADC*/
	/*TIMER_INT*/
} MemMappedDevices;

Trite ram[RAM_SIZE];

Trite ReadRam(TriWord addr)
{
	int64_t offset=TriWord2int(addr & RAM_ADDR_MASK);
	switch(offset)
	{
		case ADDR_UART_IN:
			// return int2Triword(getchar());
			return 0;
			break;
		case ADDR_UART_OUT:
			return 0;
			break;
		case ADDR_RTC:
			// return int2TriWord(time(null));
			return 0;
			break;
		default:
			return ram[BASE_OFFSET+offset];
	}
}

void WriteRam(TriWord addr, Trite Val)
{
	int64_t offset=TriWord2int(addr & RAM_ADDR_MASK);
	switch(offset)
	{
		case ADDR_UART_IN:
		case ADDR_RTC:
			break;
		case ADDR_UART_OUT:
			putchar(TriWord2int(val));
			break;
		default:
			ram[BASE_OFFSET+offset]=val;
	}

}
