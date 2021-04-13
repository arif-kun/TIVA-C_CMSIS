#include "TM4C123GH6PM.h"
#include "systick_timer.h"

void delayms(int count)
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