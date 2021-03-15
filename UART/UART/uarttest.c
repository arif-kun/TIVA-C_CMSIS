#include "TM4C123.h" 
#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char readChar(void);
void printChar(char c);
void printString(char * string);
void sysdelay(int count);

int main(void) 
{
    char c;
	
		
    
    SYSCTL->RCGCUART |= (1<<0);     
    SYSCTL->RCGCGPIO |= (1<<0); 
	
		SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R0;
    
    GPIOA->AFSEL = (1<<1)|(1<<0);     
    GPIOA->PCTL = (1<<0)|(1<<4);      
    GPIOA->DEN = (1<<0)|(1<<1); 
	
	
		UART0->CTL &=~ (UART_CTL_UARTEN);
	
    UART0->CTL &= ~(1<<0);    
    UART0->IBRD = 104;          
    UART0->FBRD = 11; 
    UART0->LCRH = (0x3<<5); 			//8 bit, FIFOs 8 bit mode        
    UART0->CC = 0x05;          
    UART0->CTL = (1<<8)|(1<<9); 
		UART0->CTL |= UART_CTL_UARTEN;
    
    SYSCTL->RCGCGPIO |= (1<<5); 
    GPIOF->DIR = (1<<1)|(1<<2)|(1<<3);  
    GPIOF->DEN = (1<<1)|(1<<2)|(1<<3); 
    GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3)); 
	
		sysdelay(100);
    while(1)
    {
				
        printString("Enter \"r\", \"g\", or \"b\":\n\r");

        c = readChar();
        printChar(c);
        printString("\n\r");
        
        switch(c)
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
				
				
     }
    
}

char readChar(void)  
{
    char c;
    while(!(UART0->FR & UART_FR_RXFF));		//hold till receive register is full
    c = UART0->DR;                 
    return c;                    
}

void printChar(char c)  
{
    
    UART0->DR = c;  
		while(!(UART0->FR & UART_FR_TXFE));			//hold till transmit register is empty
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