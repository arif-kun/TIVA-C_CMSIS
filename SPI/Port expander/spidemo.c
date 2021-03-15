#include "TM4C123.h"                    // Device header
#include <stdint.h>

#define CS_LOW		GPIOB->DATA &= ~(1<<5)
#define CS_HI			GPIOB->DATA |= 1<<5; 

void SSI2init();
void SPI_write(uint8_t data);
void delayms(int count);

int main()
{
	uint8_t led = 0x00;
	SSI2init();
	
	
	CS_HI;
	
//*********************************************	
	CS_LOW;
	SPI_write(0x40);
	SPI_write(0x0A);
	SPI_write(0x98);



	CS_HI;
//***********************************************
	
	CS_LOW;
	SPI_write(0x40);
	SPI_write(0x00);
	SPI_write(0x00);

		
	CS_HI;

//*****************************************************
	
	while(1)
	{
		CS_LOW;
		SPI_write(0x40);
		SPI_write(0x09);
		SPI_write(led++);
		CS_HI;
		
		delayms(250);
	}
	
}

void SSI2init()
{
	SYSCTL->RCGCSSI |= 1<<2;			//SSI module 2 clocked
	SYSCTL->RCGCGPIO |= 1<<1;
	
	GPIOB->AFSEL |= (1<<4)|(1<<6)|(1<<7);
	GPIOB->AFSEL &=~(1<<5);
	GPIOB->PCTL |= (2<<16) | (2<<20) | (2<<24) | (2<<28);
	
	GPIOB->DEN |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
	GPIOB->DIR |= 1<<5;
	
	SSI2->CR1 &= ~(1<<1);
	//SSI2->CR0 |= 2<<4;
	
	SSI2->CC = 0X00;
	SSI2->CPSR = 10;
	
	SSI2->CR0 = (0X7<<0);
	
	SSI2->CR1 |= 1<<1;
	
}

void SPI_write(uint8_t data)
{
	SSI2->DR = data;
	while((SSI2->SR & (1<<0))==0);
	while(SSI2->SR & (1<<4));					//check busy flag
}

void delayms(int count)
{
	int i;
	SysTick->LOAD = SystemCoreClock/1000 - 1;		//16000 cycles in 1 ms
	SysTick->VAL = 0;					//reset current value to 0
	SysTick->CTRL = 5;				//clksource = internal. counter enabled. interrupt disabled
	
	for(i=0; i<count; i++)			//repeat 1ms cycles count number of times
	{
		while((SysTick->CTRL & 0x10000)==0){}			//do nothing till Countflag becomes 1
	}
	
	SysTick->CTRL=0;		//disable counter
	
}