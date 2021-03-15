#include "TM4C123.h"                    // Device header
#include "tm4c123gh6pm.h"
#include "SPI_Driver.h"


void SPI_init(uint8_t cpha, uint8_t cpol, uint8_t data_size)
{
	SYSCTL->RCGCSSI |= SYSCTL_RCGCSSI_SSI1;
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOD;
	SYSCTL_RCGCGPIO_R |= 
	
	//PD0 --> Clk,  PD1 --> ~CS,  PD2 --> MISO,  PD3 --> MOSI
	GPIOD->AFSEL |= 1<<4 | 1<<6 | 1<<7;
	GPIOD->PCTL |= 2<<16 | 2<<24 | 2<<28;
	
	GPIOD->DEN |= 1 | 1<<1 | 1<<2 | 1<<3;
	GPIOD->DIR |= 1<<1;			//PD1 - digital output
	
	SSI1->CR1 &=~(SSI_CR1_SSE);			//disable controller
	
	
	SSI1->CR0 |= (SSI1->CR0 & ~(3<<6)) |cpha<<7 | cpol<<6;
	SSI1->CR0 |= (SSI1->CR0 & ~(0xF))|(data_size-1);
	
	SSI1->CPSR = 16;	// 1 MHz clock
	
	SSI1->CR1 |= SSI_CR1_SSE;
	
	while(!(SYSCTL->PRSSI & SYSCTL_PRSSI_SSI1));
	
}

void SPI_transmit(uint16_t data)
{
	while(!(SSI1->SR & SSI_SR_TNF));			//wait and check if transmit FIFO not full from any previous operation
	
	SSI1->DR = data;
	
	//while(SSI1->SR & SSI_SR_BSY);
}


uint8_t SPI_receive(void)
{
	while(!(SSI1->SR & SSI_SR_RNE));			//wait till receieve FIFO is not empty
	//while(SSI1->SR & SSI_SR_BSY);
	return (uint8_t)SSI1->DR;
}

uint8_t SPI_transmit_receive(uint8_t data)
{
	while(!(SSI1->SR & SSI_SR_TNF));			//wait and check if transmit FIFO not full from any previous operation
	
	SSI1->DR = data;
	
	while(!(SSI1->SR & SSI_SR_RNE));			//wait till receieve FIFO is not empty
	
	//while(SSI1->SR & SSI_SR_BSY);
	
	return (uint8_t)SSI1->DR;
}

