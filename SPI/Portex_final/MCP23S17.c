#include "TM4C123.h"                    // Device header
#include "tm4c123gh6pm.h"
#include "SPI_Driver.h"
#include "systick_timer.h"
#include "MCP23XX.h"

void portex_setup()
{
	portex_write(IODIRA,0x00);
	portex_write(IODIRB,0xFF);
	portex_write(IPOLB, 0xFF);
	portex_write(IO_A,0x00);
}

void portex_write(uint8_t reg, uint8_t data)
{
	CS_LOW;
	SPI_transmit_receive(PORTEX_WR);
	SPI_transmit_receive(reg);
	SPI_transmit_receive(data);
	CS_HI;
}

uint8_t portex_read(uint8_t reg)
{
	volatile uint8_t rec_data;
	CS_LOW;
	
	SPI_transmit_receive(PORTEX_RD);
	SPI_transmit_receive(reg);
	rec_data = SPI_transmit_receive(0x00);
	
	CS_HI;
	return rec_data;
}
	