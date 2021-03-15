#include "TM4C123.h"                    // Device header
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "I2C_Driver.h"
#include <tgmath.h>

void I2C_init(uint8_t mode)
{
	SYSCTL->RCGCI2C |= SYSCTL_RCGCI2C_I2C1;
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_GPIOA;
	
	// PA6 --> SCL,   PA7 --> SDA
	GPIOA->AFSEL |= 1<<6 | 1<<7;
	GPIOA->PCTL |= 3<<24 | 3<<28;
	
	GPIOA->DEN |= 1<<6 | 1<<7;
	GPIOA->ODR |= 1<<7;					//Open Drain configuration on SDA
	
	I2C1->MCR |= I2C_MCR_MFE;					//Master function enabled
	
	I2C1->MTPR = i2c_tpr(mode);
	
}

uint8_t i2c_tpr(uint8_t mode)
{
	float sysclk_freq,sysclk_per, scl_per;
	uint8_t tpr;
	
	sysclk_freq = SystemCoreClock * powf(10,-6);
	sysclk_per = 1/(sysclk_freq*powf(10,6));
	
	switch(mode)
	{
		case SM : scl_per = powf(10,-5);
							break;
		
		case FM : scl_per = 0.25 * powf(10,-5);
							break;
		
		case FMP:	scl_per = powf(10,-6);
							break;
		
		default : scl_per = powf(10,-5);
							break;
	}
	
	tpr = (scl_per/(2*10*sysclk_per)) - 1;
	
	return tpr;
}


void i2c_begin(uint8_t slav_add)
{
	I2C1->MSA = slav_add;
	
	//I2C1->MCS = I2C_MCS_RUN;
}

void i2c_write(uint8_t data, uint32_t condition)
{
	volatile  uint32_t readback;
	I2C1->MDR = data;
	
	I2C1->MCS = condition | I2C_MCS_RUN;
	
	readback = I2C1->MCS;
	
	while(I2C1->MCS & I2C_MCS_BUSY);
	
	
	if((I2C1->MCS & I2C_MCS_ERROR) != 0)				//check if ERROR bit is set by hardware
	{
		I2C1->MCS = I2C_MCS_STOP;
		
		while(I2C1->MCS & I2C_MCS_BUSY);
	}
	
	
}


uint8_t i2c_read(uint8_t condition)
{
	volatile  uint32_t readback;
	I2C1->MCS = I2C_MCS_RUN | condition;
	
	readback = I2C1->MCS;
	while(I2C1->MCS & I2C_MCS_BUSY);
	
	return (uint8_t) I2C1->MDR;
	/*
	if((I2C0->MCS & I2C_MCS_ERROR) != 0)				//If error
	{
		I2C1->MCS = I2C_MCS_STOP;
		
		while(I2C1->MCS & I2C_MCS_BUSY);
		return 0;
	}
	else
	{
		return (uint8_t) I2C1->MDR;
	}
	*/
	
}


void i2c_stop(void)
{
	I2C1->MCS = 0;
}