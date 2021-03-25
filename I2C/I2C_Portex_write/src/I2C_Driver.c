#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "I2C_Driver.h"
#include <tgmath.h>

void I2C_init(uint8_t mode)
{
	SYSCTL->RCGCI2C |= SYSCTL_RCGCI2C_I2C1;				//clock I2C module 1
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOA;		// I2C1 is available on GPIOA, so enable clock to GPIOA
	
	// PA6 --> SCL,   PA7 --> SDA									refer Port Mux Control(PMC) encoding scheme pg 650-651
	GPIOA->AFSEL |= 1<<6 | 1<<7;									//GPIOA pin 6 and 7 are selected as Alternate function
	GPIOA->PCTL |= 3<<24 | 3<<28;									//PMC encoding scheme for I2C1 SCL and SDA
	
	GPIOA->DEN |= 1<<6 | 1<<7;			//enable PA6 and PA7 as digital logic pins
	GPIOA->ODR |= 1<<7;							//Open Drain configuration on SDA (PA7), I2C port
	
	I2C1->MCR |= I2C_MCR_MFE;					//configure device as Master, I2C_MCR(Master Configuration) on Pg 1031
	
	I2C1->MTPR = i2c_tpr(mode);				//Master Timer Period register for setting I2C bit rate, Pg 1026
	
}

/*==================================================================================================================*/

/* calculate TPR for I2C_MTPR register depending on mode*/
uint8_t i2c_tpr(uint8_t mode)									
{
	float sysclk_freq,sysclk_per, scl_per;
	uint8_t tpr;
	
	sysclk_freq = SystemCoreClock * powf(10,-6);
	
	sysclk_per = 1/(sysclk_freq*powf(10,6));				//time period  = 1 / sysclk_freq
	
	switch(mode)			//calculate time period of SCL line depending on mode
	{
		case SM : scl_per = powf(10,-5);					// 1/(100 kbps) for Standard mode
							break;
		
		case FM : scl_per = 0.25 * powf(10,-5);				// 1/(400 kbps)		for Fast mode
							break;
		
		case FMP:	scl_per = powf(10,-6);						// 1/(1 Mbps)		for Fast Mode Plus
							break;
		
		default : scl_per = powf(10,-5);
							break;
	}
	
	tpr = (scl_per/(2*10*sysclk_per)) - 1;				//formula for TPR in I2C_MTPR register on Pg 1026
	
	return tpr;
}

/*==================================================================================================================*/


void i2c_begin(uint8_t slav_add)							//function to set slave address on Master Slave Address register
{
	I2C1->MSA = slav_add;					//set slave address
}

/*==================================================================================================================*/

void i2c_write(uint8_t data, uint32_t condition)			//data to write to slave, condition = start/stop
{
	volatile  uint32_t readback;			//dummy variable
	
	I2C1->MDR = data;									//set up Data to be written to slave in Master Data Register
	
	I2C1->MCS = condition | I2C_MCS_RUN;			//write to MCS - RUN and condition
	
	readback = I2C1->MCS;								//read MCS just to make sure 
	
	while(I2C1->MCS & I2C_MCS_BUSY);			//wait if I2C bus is Busy, i.e, write/read operation is still going on
	
	
}

/*==================================================================================================================*/

uint8_t i2c_read(uint8_t condition)
{
	volatile  uint32_t readback;
	I2C1->MCS = I2C_MCS_RUN | condition;			
	
	readback = I2C1->MCS;
	while(I2C1->MCS & I2C_MCS_BUSY);			//wait if I2C bus is Busy, i.e, write/read operation is still going on
	
	return (uint8_t) I2C1->MDR;						//read Master Data Register and return it's value
	
}

/*==================================================================================================================*/

void i2c_stop(void)
{
	I2C1->MCS = 0;						//RUN = 0
}