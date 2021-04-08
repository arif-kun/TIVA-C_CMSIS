#include "tm4c123gh6pm.h"								//Device header by TI
#include "systick_timer.h"
#include "I2C_Driver.h"
#include "MCP23XX.h"
#include <stdint.h>


int main()
{
	volatile uint8_t data_in;
	
	I2C_init(SM);					//initialize I2C in standard mode
	
	/*==================================================================================================================*/
	
	//Set up port A direction
	
	i2c_begin(0x40);						//write to MCP23017
	i2c_write(IODIRA, START);		//generate START condition and write to IODIR(IO Direction) register of PortA of MCP23017
	i2c_write(0x00, STOP);			//write 0x00 to set all pins of PortA as Output and then generate STOP condition	
	
	/*==================================================================================================================*/
	
	//Set up port B direction
	
	i2c_begin(0x40);						//write to MCP23017
	i2c_write(IODIRB, START);		//generate START condition and write to IODIR(IO Direction) register of PortB of MCP23017
	i2c_write(0xFF, STOP);			//write 0x00 to set all pins of PortB as Input and then generate STOP condition	
	
	/*==================================================================================================================*/
	
	while(1)
	{
		
		//Read data at port B of MCP23017
		i2c_begin(0X40);											//write to MCP23017
		i2c_write(IO_B, START);								//generate START condition and access IO_B register
		i2c_begin(0x41);											//read from MCP23017
		data_in = i2c_read(START | STOP);			//generate START condition, read data on IO_B, and then generate STOP condition;
		
		
		//Write to IO_A
		i2c_begin(0x40);											//write to MCP23017
		i2c_write(IO_A, START);								//generate START condition and access IO_A register
		i2c_write(data_in, STOP);							//write value of led variable and then generate STOP condition
		

		
	}
	
}