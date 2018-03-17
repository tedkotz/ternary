#define RAM_SIZE 177147
#define BASE_OFFSET (RAM_SIZE/2)

typedef enum
{
	ADDR_UART_IN  = -2,
	ADDR_UART_OUT = -3,
	ADDR_RTC      = -4,
	/*BITMAP DISPLAY*/
	/*DAC*/
	/*ADC*/
	/*TIMER_INT*/
} MemMappedDevices;

TriWord ram[RAM_SIZE];

TriWord ReadRam(TriWord addr)
{
	int64_t offset=TriWord2int(addr);
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

void WriteRam(TriWord addr, TriWord Val)
{
	int64_t offset=TriWord2int(addr);
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
