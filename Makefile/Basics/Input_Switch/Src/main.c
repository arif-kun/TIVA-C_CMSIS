#include "TM4C123GH6PM.h"


int main()			//for switch2
{
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOF;		//PORTF clocked
	GPIOF->LOCK = GPIO_LOCK_KEY;   //0x4C4F434B;		//unlock commit register
	GPIOF->CR = 0x1;
	
	GPIOF->DIR |= 1<<1 | 1<<3;		//set PF3 as output, all others are input by default
	GPIOF->DEN |= 1 | 1<<1 | 1<<3 | 1<<4;		//set PF0 and PF3 as digital IO
	GPIOF->PUR |= 1 | 1<<4;		//PORTS are at tristated. by default no pull up or pull down. we explicitly pull up PF0
	
	while(1)
	{
		if(!(GPIOF->DATA & (1)))		//check if PF0 is pulled to ground ie switch pressed
		{
			GPIOF->DATA |= 1<<1;
		}
		else if(!(GPIOF->DATA & (1<<4)))	//check if PF4 is pulled to ground ie switch pressed
		{
			GPIOF->DATA |= 1<<3;
		}
		else GPIOF->DATA &=~(1<<1 | 1<<3);
	
	}
	return 0;
}
