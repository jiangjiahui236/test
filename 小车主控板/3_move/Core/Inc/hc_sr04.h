#ifndef _HC_SR04_H
#define _HC_SR04_H
#include "main.h"
#include "tim.h"
#include "NiMing_UpperConputer.h"
#include "Kalman.h"

extern uint32_t dis_1,dis_2,dis_3;//超声波测距

void HcSr04_TIM_start(void);//开启接收中断函数
void HcSr04_start_1(void);//发送超声波
void HcSr04_start_2(void);//发送超声波
void HcSr04_start_3(void);//发送超声波
void HcSr04_Delay(uint16_t i);
#endif
