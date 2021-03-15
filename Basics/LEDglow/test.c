#include "TM4C123.h"                    // Device header
 
int main()
{
	
	SYSCTL->RCGCGPIO |= (1<<5);			//PORT F clock enabled
	
	GPIOF->DIR |= (1<<3);		//PF3 configured as output
	GPIOF->DEN |= (1<<3);	  //enable digital function on PF3
	
	GPIOF->DR2R |= 1<<3;
	
	GPIOF->DATA |=(1<<3);		//set bit 3 to glow LED connected to PF3
	

	
	while(1);
	
}