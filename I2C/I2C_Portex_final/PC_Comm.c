#include "TM4C123.h"                    // Device header
#include "tm4c123gh6pm.h"
#include "PC_Comm.h"
#include <stdio.h>
#include <tgmath.h>

void PC_Comm_init(unsigned int baud)
{
	unsigned int fbrd, clkdiv;
	float brd, ibrd;
	
	SYSCTL->RCGCUART |= SYSCTL_RCGCUART_UART0;
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOA;
	
	GPIOA->AFSEL |= 1 | 1<<1;
	GPIOA->PCTL |= (1<<0)|(1<<4);      
  GPIOA->DEN |= (1<<0)|(1<<1);
	
	brd = SystemCoreClock/(16*baud);
	
	fbrd = modff(brd,&ibrd);
	
	
	UART0->CTL &=~ (UART_CTL_UARTEN);
	
	UART0->CC = 0x00;
	
	UART0->IBRD = (unsigned int) ibrd;
	UART0->FBRD = fbrd;
	
	UART0->LCRH |= UART_LCRH_WLEN_8;
	
	UART0->CTL |= UART_CTL_TXE | UART_CTL_RXE;		//enable transmit and receive
	
	UART0->CTL |= UART_CTL_UARTEN;
	
}


int send_char(uint8_t data)
{
	UART0->DR = data;
	
	while(!(UART0->FR & UART_FR_TXFE));			//hold till transmit register is empty
}


int rec_char(void)
{
	while(!(UART0->FR & UART_FR_RXFF));			//wait till receive register is full
	
	return ((int)UART0->DR);
}



struct __FILE									//__FILE__ is a preprocessor macro that expands to full path to the current file
{
	int handle;		//handler
};

//Initializing standard streams - stdin, stdout, stderror
FILE __stdin;			
FILE __stdout;
FILE __stderr;



// re-defining fgetc for reading input
int fgetc(FILE *f)												//f is a pointer to current file 
{
	int c;
	c= rec_char();
	send_char(c);			//echo on screen what was entered
	
	if(c=='\r')			//if enter is pressed
	{
		send_char(c);					//print carriage return
		send_char('\n');			//print new line
	}
	
	return c;
} 


int fputc(int c, FILE *f)					// re-defining fputc for writing 
{
	return send_char(c);
}