#include "TM4C123GH6PM.h"
#include "systick_timer.h"


int main()
{
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOF;

	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
	
	while(1)
	{
		
		GPIOF->DATA |= 0x02;				//RED
		delayms(250);
		GPIOF->DATA &=~ 0x02;
		delayms(250);
		
		
		GPIOF->DATA |= 0x04;			//BLUE
		delayms(250);
		GPIOF->DATA &=~ 0x04;
		delayms(250); 
		
		
		GPIOF->DATA |= 0x08;			//GREEN
		delayms(250);
		GPIOF->DATA &=~ 0x08;
		delayms(250);

	}
		
	return 0;
		
	
}


