#include "tm4c123gh6pm.h"								//Device header by TI
#include "systick_timer.h"
#include "SPI_Driver.h"
#include "MCP23XX.h"
#include <stdint.h>


int main()
{
	uint8_t led = 0x00;
	
	SPI_init(0,0,8);
	
	/*====================================================================================================*/
	
	SPI_transmit(0x40);
	SPI_transmit(IODIRA);
	SPI_transmit(0x00);
	
	/*====================================================================================================*/
	
	while(1)
	{
		SPI_transmit(0x40);
		SPI_transmit(IO_A);
		SPI_transmit(led++);
		
		delayms(250);
	}
	

	return 0;
	
}