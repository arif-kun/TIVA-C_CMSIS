#include "TM4C123.h"                    
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char readChar(void);
void printChar(char c);
void printString(char * string);
void sysdelay(int count);
void UART0_init(void);

volatile char c;

int main(void) 
{    
		UART0_init();
    
    SYSCTL->RCGCGPIO |= (1<<5); 
    GPIOF->DIR = (1<<1)|(1<<2)|(1<<3);  
    GPIOF->DEN = (1<<1)|(1<<2)|(1<<3); 
    GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3)); 
	

	
		NVIC_EnableIRQ(UART0_IRQn);
	
		sysdelay(100);
			__enable_irq();
    while(1)
    {
					 printString("Enter \"r\", \"g\", or \"b\":\n\r");
			sysdelay(2000);
        //printString("Enter \"r\", \"g\", or \"b\":\n\r");
/*
        c = readChar();
        printChar(c);
        printString("\n\r");
        
        switch(c)
        {
        case 'r':
          GPIOF->DATA = (1<<1);
          break;
        case 'b':
          GPIOF->DATA = (1<<2);
          break;
        case 'g':
          GPIOF->DATA = (1<<3);
          break;
        default:
          GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3));
          break;
        }
				
				*/
     }
 
}


void UART0_Handler(void)
{
	
	if((UART0->FR & 1<<4) | (UART0->MIS & 1<<4) )
	{
		c = UART0->DR;
		UART0->ICR |= 1<<4;			//clear RX interrupt
		printChar(c);
		switch(c)
    {
        case 'r':
          GPIOF->DATA = (1<<1);
          break;
        case 'b':
          GPIOF->DATA = (1<<2);
          break;
        case 'g':
          GPIOF->DATA = (1<<3);
          break;
        default:
          GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3));
          break;
    }
		
		 //printString("Enter \"r\", \"g\", or \"b\":\n\r");
	}
	
}

void UART0_init(void)
{
    SYSCTL->RCGCUART |= (1<<0);     
    SYSCTL->RCGCGPIO |= (1<<0); 
    
    GPIOA->AFSEL = (1<<1)|(1<<0);     
    GPIOA->PCTL = (1<<0)|(1<<4);      
    GPIOA->DEN = (1<<0)|(1<<1); 
   
    UART0->CTL &= ~(1<<0);    
    UART0->IBRD = 104;          
    UART0->FBRD = 11; 
    UART0->LCRH = (0x3<<5);         
    UART0->CC = 0x05;          
	
		UART0->IM |= 1<<4;			//enable RX interrupt
	
    UART0->CTL = (1<<0)|(1<<8)|(1<<9); 
}

char readChar(void)  
{
    char c;
    while((UART0->FR & (1<<4)) != 0);
    c = (uint8_t)	UART0->DR;                 
    return c;                    
}

void printChar(char c)  
{
    while((UART0->FR & (1<<5)) != 0);
    UART0->DR = c;           
}

void printString(char * string)
{
  while(*string)
  {
    printChar(*(string++));
  }
}


void sysdelay(int count)
{
	int i;
	SysTick->LOAD = 4000-1;
	SysTick->VAL = 0;
	SysTick->CTRL=1;		//0101
	
	for(i=0;i<count;i++)
	{
		while((SysTick->CTRL & (0x10000))==0 ){}
	}
	SysTick->CTRL=0;
}
