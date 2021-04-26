#include "TM4C123GH6PM.h"		
#include "systick_timer.h"
#include "I2C_Driver.h"
#include "MCP23XX.h"
#include <stdint.h>


int main()
{
	uint8_t led = 0x00;
	I2C_init(SM);							//initialize I2C in standard mode
	
	/*==================================================================================================================*/
	
	//Set up port directions
	
	i2c_begin(0x40);						//write to MCP23017
	i2c_write(IODIRA, START);				//generate START condition and write to IODIR(IO Direction) register of PortA of MCP23017
	
	/*
	REMARK : when the START condition is generated, 2 Bytes are transferred :
	1st byte - slave address + rd/wr (here 0x40) stored in MSA register
	2nd byte - data (here IODIRA = 0x00) stored in MDR register
	*/

	i2c_write(0x00, STOP);					//write 0x00 to set all pins of PortA as Output and then generate STOP condition	
	
	/*==================================================================================================================*/
	
	while(1)
	{
		i2c_begin(0x40);					//write to MCP23017
		i2c_write(IO_A, START);				//generate START condition and write to IO_A register
		i2c_write(led++, STOP);				//write value of led variable and then generate STOP condition
		
		delayms(250);
		
	}
	
}