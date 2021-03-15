#include "TM4C123.h"                    // Device header
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "systick_timer.h"
#include "I2C_Driver.h"
#include "MCP23XX.h"
#include "PC_Comm.h"
#include <stdio.h>
#include <tgmath.h>

int main()
{
	uint8_t led = 0x00;
	volatile uint8_t data_in;
	PC_Comm_init(9600);
	I2C_init(SM);
	
	portex_setup();
	
	while(1)
	{
		data_in = portex_read(IO_B);
		portex_write(IO_A,data_in);
		//printf("\n\rreceived : %X\n\r", data_in);
		
		//delayms(100);
	}
	
	
	return 0;
}