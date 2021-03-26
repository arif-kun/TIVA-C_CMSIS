#include "tm4c123gh6pm.h"
#include "systick_timer.h"


void delayms(int count)
{
	int i;
	SysTick->LOAD = SystemCoreClock/1000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	
	for(i=0;i<count;i++)
	{
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));				//hold till COUNTFLAG = 1
	}
	SysTick->CTRL=0;
	
}