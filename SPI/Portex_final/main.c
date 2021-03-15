#include "TM4C123.h"                    // Device header
#include "tm4c123gh6pm.h"
#include "SPI_Driver.h"
#include "systick_timer.h"
#include "MCP23XX.h"

int main()
{
	uint8_t led = 0x00;
	volatile uint8_t data_in;
	SPI_init(0,0,8);
	CS_HI;
	
	portex_setup();
	
	while(1)
	{
		data_in = portex_read(IO_B);
		portex_write(IO_A,data_in);
		//delayms(100);
	}
	
	
}


