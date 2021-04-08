#include "TM4C123GH6PM.h"

void delay(int ms);

void sysdelay(int count);

int main()
{
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOF;

	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
	
	while(1)
	{
		
		GPIOF->DATA |= 0x02;				//RED

		sysdelay(100);
		GPIOF->DATA &=~ 0x02;
		sysdelay(100);
		
		
		GPIOF->DATA |= 0x04;			//BLUE
		sysdelay(100);
		GPIOF->DATA &=~ 0x04;
		sysdelay(100); 
		
		
		GPIOF->DATA |= 0x08;			//GREEN
		sysdelay(100);
		GPIOF->DATA &=~ 0x08;
		sysdelay(100);

	
		
	
	}
		
		
	
}


void sysdelay(int count)
{
	SysTick->LOAD = SystemCoreClock/1000 -1;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; //0101
	
	for(int i=0; i<count; i++)
	{
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	}

	SysTick->CTRL=0;
}