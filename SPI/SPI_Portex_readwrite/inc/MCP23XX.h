#include <stdint.h>

#ifndef MCP23XX_H
#define MCP23XX_H


#define PORTEX_RD   0x41     /* Read */
#define PORTEX_WR   0x40     /* Write */


#define BANK  0




#if BANK==0                  //if BANK = 0,use folllowing macros

    /******************************
    * Control register for BANK=0
    ******************************/
    #define IODIRA        0x00      /* Data Direction Register for PORTA */
    #define IODIRB        0x01      /* Data Direction Register for PORTB */ 
    #define IPOLA         0x02      /* Input Polarity Register for PORTA */ 
    #define IPOLB         0x03      /* Input Polarity Register for PORTB */ 
    #define GPINTENA      0x04      /* Interrupt-on-change enable Register for PORTA */ 
    #define GPINTENB      0x05      /* Interrupt-on-change enable Register for PORTB */ 
    #define DEFVALA       0x06      /* Default Value Register for PORTA */    
    #define DEFVALB       0x07      /* Default Value Register for PORTB */      
    #define INTCONA       0x08      /* Interrupt-on-change control Register for PORTA */  
    #define INTCONB       0x09      /* Interrupt-on-change control Register for PORTB */      
    #define IOCON         0x0A      /* Configuration register for device */                      
    #define GPPUA         0x0C      /* 100kOhm pullup resistor register for PORTA (sets pin to input when set) */    
    #define GPPUB         0x0D      /* 100kOhm pullup resistor register for PORTB (sets pin to input when set) */      
    #define INTFA         0x0E      /* Interrupt flag Register for PORTA */        
    #define INTFB         0x0F      /* Interrupt flag Register for PORTB */    
    #define INTCAPA       0x10      /* Interrupt captured value Register for PORTA */  
    #define INTCAPB       0x11      /* Interrupt captured value Register for PORTB */    
    #define IO_A          0x12      /* General purpose I/O Register for PORTA */  
    #define IO_B          0x13      /* General purpose I/O Register for PORTB */ 
    #define OLATA         0x14      /* Output latch Register for PORTA */ 
    #define OLATB         0x15      /* Output latch Register for PORTB */

#else           //else use following macros
		/******************************
		* Control register for BANK=1
		******************************/
		#define IODIRA        0x00      /* Data Direction Register for PORTA */
		#define IPOLA         0x01      /* Input Polarity Register for PORTA */  
		#define GPINTENA      0x02      /* Interrupt-on-change enable Register for PORTA */     
		#define DEFVALA       0x03      /* Default Value Register for PORTA */    
		#define INTCONA       0x04      /* Interrupt-on-change control Register for PORTA */     
		#define IOCONA        0x05      /* Configuration register for device */          
		#define GPPUA         0x06      /* 100kOhm pullup resistor register for PORTA (sets pin to input when set) */     
		#define INTFA         0x07      /* Interrupt flag Register for PORTA */
		#define INTCAPA       0x08      /* Interrupt captured value Register for PORTA */
		#define IO_A          0x09      /* General purpose I/O Register for PORTA */  
		#define OLATA         0x0A      /* Output latch Register for PORTA */ 
		#define IODIRB        0x10      /* Data Direction Register for PORTB */ 
		#define IPOLB         0x11      /* Input Polarity Register for PORTB */ 
		#define GPINTENB      0x12      /* Interrupt-on-change enable Register for PORTB */
		#define DEFVALB       0x13      /* Default Value Register for PORTB */      
		#define INTCONB       0x14      /* Interrupt-on-change control Register for PORTB */
		#define IOCONB        0x15      /* Configuration register for device */  
		#define GPPUB         0x16      /* 100kOhm pullup resistor register for PORTB (sets pin to input when set) */        
		#define INTFB         0x17      /* Interrupt flag Register for PORTB */    
		#define INTCAPB       0x18      /* Interrupt captured value Register for PORTB */    
		#define IO_B          0x19      /* General purpose I/O Register for PORTB */ 
		#define OLATB         0x1A      /* Output latch Register for PORTB */

#endif          //BANK=0 macro endif






/******************************
* Prototypes
******************************/
void portex_setup(void);
void portex_write(uint8_t reg, uint8_t data);
uint8_t portex_read(uint8_t reg);




#endif
