#include "TM4C123.h"                    // Device header

int main()
{
	SYSCTL->RCGCGPIO |= 0X20;		//PORTF clocked
	GPIOF->DIR |= 0X08;		//set PF3 as output, all others are input by default
	GPIOF->DEN |= 0X18;		//set PF4 and PF3 as digital IO
	GPIOF->PUR |= 0X10;		//PORTS are at tristated. by default no pull up or pull down. we explicitly pull up PF4
	
	while(1)
	{
		if(!(GPIOF->DATA & (1<<4)))		//check if PF4 is pulled to ground ie switch pressed
		{
			GPIOF->DATA |= (1<<3);
		}
		else{
			GPIOF->DATA &=~(1<<3);
		}
	}
}


/*
int main()			//for switch2
{
	SYSCTL->RCGCGPIO |= 0X20;		//PORTF clocked
	GPIOF->LOCK = 0X4C4F434B;		//unlock commit register
	GPIOF->CR = 0X01;			//PF0 unlocked
	
	GPIOF->DIR |= 0X08;		//set PF3 as output, all others are input by default
	GPIOF->DEN |= 0X9;		//set PF0 and PF3 as digital IO
	GPIOF->PUR |= 0X01;		//PORTS are at tristated. by default no pull up or pull down. we explicitly pull up PF0
	
	while(1)
	{
		if(!(GPIOF->DATA & (1)))		//check if PF0 is pulled to ground ie switch pressed
		{
			GPIOF->DATA |= (0x08);
		}
		else{
			GPIOF->DATA &=~(0x08);
		}
	
	}
}

*/
