#ifndef __ENCODER_H 
#define __ENCODER_H
#include "tim.h"

extern int Encoder[4];
extern long dis,dis_;

void Encoder_Init(void);
void GetEncoder(void);

#endif
