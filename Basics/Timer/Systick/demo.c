#include "TM4C123.h"                    // Device head

void delay(int ms);

void sysdelay(int count);
int main()
{
	
	SYSCTL->RCGCGPIO |= 0X20;		//port F clocked
	
	GPIOF->DIR |= 0X0E;
	GPIOF->DEN |= 0X0E;
	
	while(1)
		{
		GPIOF->DATA |= 0X02;				//RED
		sysdelay(250);
		GPIOF->DATA &=~ 0X02;
		sysdelay(250);
		
		/*
		GPIOF->DATA |= 0X04;			//BLUE
		sysdelay(250);
		GPIOF->DATA &=~ 0X04;
		sysdelay(250); 
			
		GPIOF->DATA |= 0X08;			//GREEN
		sysdelay(250);
		GPIOF->DATA &=~ 0X08;
		sysdelay(250);
			*/
	}
		
		
	
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<3180;j++);
	}
}  

void sysdelay(int count)
{
	int i;
	SysTick->LOAD = SystemCoreClock/1000-1;
	SysTick->VAL = 0;
	SysTick->CTRL=5;		//0101
	
	for(i=0;i<count;i++)
	{
		while((SysTick->CTRL & (0x10000))==0 ){}
	}
	SysTick->CTRL=0;
}