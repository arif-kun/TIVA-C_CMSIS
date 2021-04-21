#include "TM4C123GH6PM.h"
#include "systick_timer.h"
#include "SPI_Driver.h"
#include "MCP23XX.h"
#include <stdint.h>


int main()
{
	uint8_t led = 0x00;
	
	SPI_init(0,0,8);
	
	/*====================================================================================================*/
	CS_LOW;
	
	SPI_transmit(0x40);				//device opcode to write
	SPI_transmit(IODIRA);			//Access IODIRA register to select direction of PortA on Port Expander
	SPI_transmit(0x00);				//set direction of every pin on port A to output	
	
	CS_HI;
	
	/*====================================================================================================*/
	
	while(1)
	{
		CS_LOW;
		
		SPI_transmit(0x40);		
		SPI_transmit(IO_A);		
		SPI_transmit(led++);
		
		CS_HI;
		
		delayms(250);
	}
	

	return 0;
	
}