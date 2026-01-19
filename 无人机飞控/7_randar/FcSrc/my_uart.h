#ifndef __MT_UART_H
#define __MT_UART_H

#include "stdint.h"

extern int16_t OpenMV_data_0,OpenMV_data_1,OpenMV_data_2;
extern int8_t to_OpenMV_data_0;

void MY_urst1_Receive(uint8_t data);
void MY_urst2_Send(void);
void MY_urst2_Receive(uint8_t data);

#endif
