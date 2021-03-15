#include <stdio.h>
#include <stdint.h>

#ifndef _PC_COMM_H_
#define _PC_COMM_H_

void PC_Comm_init(unsigned int baud);

int send_char(uint8_t data);

int rec_char(void);


#endif		//_PC_COMM_H_