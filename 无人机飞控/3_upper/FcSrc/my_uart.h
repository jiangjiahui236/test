#ifndef __MT_UART_H
#define __MT_UART_H

#include "stdint.h"

void MY_urst1_Receive(uint8_t data);
void MY_urst2_Send(void);
void MY_urst2_Receive(uint8_t data);

#endif
