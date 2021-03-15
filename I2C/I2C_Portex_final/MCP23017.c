#include "tm4c123gh6pm.h"
#include "MCP23XX.h"
#include "I2C_Driver.h"
#include "TM4C123.h"                    // Device header


void portex_setup(void)
{
	portex_write(IODIRA,0x00);
	portex_write(IODIRB,0xFF);
	portex_write(IPOLB,0xFF);
	
}

void portex_write(uint8_t reg, uint8_t data)
{
	i2c_begin(PORTEX_WR);
	i2c_write(reg,START);
	i2c_write(data,STOP);
	//i2c_stop();
	
}

uint8_t portex_read(uint8_t reg)
{
	i2c_begin(PORTEX_WR);
	i2c_write(reg,START);
	i2c_begin(PORTEX_RD);
	i2c_read(START | STOP);
	//i2c_stop();
}