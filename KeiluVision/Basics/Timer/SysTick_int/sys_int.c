#include "TM4C123.h"                    // Device header


void blinkLED(int count);

int main()
{
	SYSCTL->RCGCGPIO |= 1<<5;		//clock port F
	
	GPIOF->DIR |= (1<<3);		//PF3 configured as output
	GPIOF->DEN |= (1<<3);	  //enable digital function on PF3
	
	blinkLED(2000000);
	
	
	
	while(1);
	
}

void SysTick_Handler(void)
{
	GPIOF->DATA ^= (1<<3);			//toggle
}

void blinkLED(int count)
{
	SysTick->LOAD = count - 1;			//starting from 0
	SysTick->VAL = 0;
	SysTick->CTRL = 3;			
}