#include <stdint.h>

#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#define CS_LOW		(GPIOD->DATA &=~ (1<<1))
#define CS_HI			(GPIOD->DATA |=(1<<1))


/* Prototypes */

void SPI_init(uint8_t cpha, uint8_t cpol, uint8_t no_of_bytes);

void SPI_transmit(uint8_t data);

uint8_t SPI_transmit_receive(uint8_t data);



#endif