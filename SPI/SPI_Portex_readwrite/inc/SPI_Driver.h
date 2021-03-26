#include <stdint.h>

#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#define CS_LOW		(GPIOB->DATA &=~ (1<<5))
#define CS_HI			(GPIOB->DATA |=(1<<5))


/* Prototypes */

void SPI_init(uint8_t cpha, uint8_t cpol, uint8_t no_of_bytes);

void SPI_transmit(uint16_t data);


uint8_t SPI_receive(void);

uint8_t SPI_transmit_receive(uint8_t data);



#endif