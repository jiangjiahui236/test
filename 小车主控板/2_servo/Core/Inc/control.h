#ifndef __CONTROL_H 
#define __CONTROL_H

#include "mpu9250.h"
#include "pid.h"
#include "hc_sr04.h"

extern volatile int keep_dis_1_flag,keep_dis_2_flag,keep_dis_3_flag,keep_dis_23_flag;
extern int move_flag;
extern int keep_yaw_flag;
extern int IR_1_flag,IR_2_flag,IR_3_flag,IR_4_flag;
extern int target_speek[4];
extern int basic_speek;
extern float yaw_set;
extern int dis_target;
extern int start_flag;

void advance(int value);
void transverse(int value);
void clockwise(int value);
void restart(void);
void keep_yaw(void);
void keep_dis_1(void);
void keep_dis_2(void);
void keep_dis_3(void);
void keep_dis_23(void);

#endif
