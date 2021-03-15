#include "TM4C123.h"                    // Device header
#include <stdint.h>

#define RED_ON	(GPIOF->DATA |= 1<<1)
#define GREEN_ON	(GPIOF->DATA |= 1<<3)
#define BLUE_ON	(GPIOF->DATA |= 1<<2)

#define RED_OFF	(GPIOF->DATA &= ~(1<<1))
#define GREEN_OFF	(GPIOF->DATA &= ~(1<<3))
#define BLUE_OFF	(GPIOF->DATA &= ~(1<<2))

void SSI2init(void);
void SPI_write(uint8_t data);
void delayms(int count);

volatile int data;

int main()
{
	SSI2init();			//initialize SSI
	
	SYSCTL->RCGCGPIO |= (1<<5);			//PORT F clock enabled
	
	while(1);	
}

void SSI2init(void)
{
	
	
	SYSCTL->RCGCSSI |= 1<<2;			//SSI module 2 clocked
	SYSCTL->RCGCGPIO |= 1<<1;				//clock PORT B
	
	GPIOB->AFSEL |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
	GPIOB->PCTL |= (2<<16) | (2<<20) | (2<<24) | (2<<28);
	
	GPIOB->DEN |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
	
	SSI2->CR1 &= ~(1<<1);			// disable SSI
	
	SSI2->CR0 |= 0X7<<0;				//8 bit data, BR = Sysclk/CPSR, Mode0, Freescale Frame Format
	
	SSI2->CR1 |= 1<<4;				//configure as slave	
	
	SSI2->CC = 0X5;					//clock source - precision internal oscillator = 16MHz
	SSI2->CPSR = 16;		
	
	SSI2->IM |= 1<<2; 				//unmask FIFO interrupts on SSI2
	
	SSI2->CR1 |= 1<<1;			//Enable SSI
	
}

void SSI2_Handler(void)
{
	
	if(SSI2->SR & 1<<3)		//check if RX FIFO is NOT empty
	{
		data = SSI2->DR;
		
		switch(data)
		{
			case 'r':
			case 'R':
			case 1:
				RED_ON;
				GREEN_OFF;
				BLUE_OFF;
				break;
			
			case'g':
			case'G':
			case 2:
				GREEN_ON;
				RED_OFF;
				BLUE_OFF;
				break;
			
			case 'B':
			case 'b':
			case 3:
				BLUE_ON;
				RED_OFF;
				GREEN_OFF;
				break;
			
			default : 
				RED_OFF;
				GREEN_OFF;
				BLUE_OFF;
				break;
				
			
		}
		
		
	}
	
	
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
	SysTick->LOAD = 16000;		//16000 cycles in 1 ms
	SysTick->VAL = 0;					//reset current value to 0
	SysTick->CTRL = 5;				//clksource = internal. counter enabled. interrupt disabled
	
	for(i=0; i<count; i++)			//repeat 1ms cycles count number of times
	{
		while((SysTick->CTRL & 0x10000)==0){}			//do nothing till Countflag becomes 1
	}
	
	SysTick->CTRL=0;		//disable counter
	
}
