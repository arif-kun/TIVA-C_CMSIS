#include "tm4c123gh6pm.h"								//Device header by TI
#include "systick_timer.h"
#include "SPI_Driver.h"
#include "MCP23XX.h"
#include <stdint.h>


int main()
{
	volatile uint8_t data_in;
	
	SPI_init(0,0,8);
	
	/*====================================================================================================*/
	CS_LOW;
	
	SPI_transmit(0x40);
	SPI_transmit(IODIRA);
	SPI_transmit(0x00);
	
	CS_HI;
	
	/*====================================================================================================*/
	
	CS_LOW;
	
	SPI_transmit(0x40);
	SPI_transmit(IODIRB);
	SPI_transmit(0xFF);
	
	CS_HI;
	
	/*====================================================================================================*/
	
	
	while(1)
	{
		//Read data on PortB of MCP23S17
		CS_LOW;
		
		SPI_transmit_receive(0x41);								//slave address + read
		SPI_transmit_receive(IO_B);
		data_in = SPI_transmit_receive(0x00);			//send a dummy byte and receive data on variable
		
		CS_HI;
		
		//Write data received on PortB to PortA
		CS_LOW;
		
		SPI_transmit(0x40);
		SPI_transmit(IO_A);
		SPI_transmit(data_in);
		
		CS_HI;
		
	
	}
	

	return 0;
	
}


//REMARK : SPI_transmit() function can be replaced with SPI_transmit_receive() eveywhere
