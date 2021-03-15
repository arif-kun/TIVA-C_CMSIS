#include "TM4C123.h"                    // Device header
#include "tm4c123gh6pm.h"
#include "PC_Comm.h"
#include <stdio.h>


void delayms(int count);

int main()
{
	char color;
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOF;
	GPIOF->DIR = (1<<1)|(1<<2)|(1<<3);  
	GPIOF->DEN = (1<<1)|(1<<2)|(1<<3); 
	GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3));
	
	PC_Comm_init(9600);
	delayms(1);
	
	
	while(1)
	{
		printf("\n\rEnter R/G/B : \n\r");
		scanf("%c",&color);
		
		switch(color)
        {
        case 'r':
				case 'R':
          GPIOF->DATA = (1<<1);
          break;
        case 'b':
				case 'B':
          GPIOF->DATA = (1<<2);
          break;
        case 'g':
				case 'G':
          GPIOF->DATA = (1<<3);
          break;
        default:
          GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3));
          break;
        }
		
		//delayms(500);
	}
	
	return 0;
}



void delayms(int count)
{
	int i;
	SysTick->LOAD = SystemCoreClock/1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	
	for(i=0;i<count;i++)
	{
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	}
	SysTick->CTRL=0;
	
}