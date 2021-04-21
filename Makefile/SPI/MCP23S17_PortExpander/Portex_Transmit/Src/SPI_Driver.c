#include "TM4C123GH6PM.h"
#include "SPI_Driver.h"

/*==================================================================================================================*/

void SPI_init(uint8_t cpha, uint8_t cpol, uint8_t data_size)
{
	SYSCTL->RCGCSSI |= SYSCTL_RCGCSSI_SSI1;								//clock SSI module 1
	
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOD;							//clock GPIOD
		
	//PD0 --> Clk,  PD1 --> ~CS,  PD2 --> MISO,  PD3 --> MOSI
	
	GPIOD->AFSEL |= 1 | 1<<2 | 1<<3;									//select PD0, PD2 and PD3 as alternate function
	GPIOD->PCTL |=  2 | 2<<8 | 2<<12;									//Port Mux Control(PMC) encoding scheme for SSI1 on GPIOD
	
	GPIOD->DEN |= 1 | 1<<1 | 1<<2 | 1<<3;								//Select PD0,PD1,PD2,PD3 as Digital pins	
	GPIOD->DIR |= 1<<1;													//PD1 - digital output
	
	SSI1->CR1 &=~(SSI_CR1_SSE);											//disable SSI controller
	
	SSI1->CR0 |= (SSI1->CR0 & ~(3<<6)) | (cpha << 7) | (cpol << 6);		//set clock phase and polarity
	SSI1->CR0 |= (SSI1->CR0 & ~(0xF)) | (data_size-1);																		//set data size
	
	SSI1->CPSR = 50;	// CPSR = SystemCoreClock/Baudrate,   say desired Baudrate = 1MHz, then CPSR = 50MHz/1MHz = 50
	
	SSI1->CR1 |= SSI_CR1_SSE;											//enable SSI controller
	
	
}

/*==================================================================================================================*/

void SPI_transmit(uint8_t data)
{
	while(!(SSI1->SR & SSI_SR_TNF));			//wait and check if transmit FIFO not full from any previous operation
	
	SSI1->DR = data;											//put data on SSI Data register
	
	while(SSI1->SR & SSI_SR_BSY);					//wait if SSI bus is Busy, i.e, write/read operation is going on
}


/*==================================================================================================================*/

uint8_t SPI_transmit_receive(uint8_t data)
{
	while(!(SSI1->SR & SSI_SR_TNF));			//wait and check if transmit FIFO not full from any previous operation
	
	SSI1->DR = data;
	
	while(!(SSI1->SR & SSI_SR_RNE));			//wait till receieve FIFO is not empty
	
	return (uint8_t)SSI1->DR;
}


/*==================================================================================================================*/