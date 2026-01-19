#ifndef __MODE_H
#define __MODE_H

#include "stdint.h"
#include "control.h"

extern int my_mode;//飞行模式
extern int32_t hight_target,dis_x_target,dis_y_target,yaw_target;//数据目标
extern int32_t hight_now,dis_x_now,dis_y_now,yaw_now;//当前数据
extern int32_t test_flag,keep_hight_flag,keep_dis_x_flag,keep_dis_y_flag,keep_yaw_flag,keep_OpenMV_data_1,keep_OpenMV_data_2;//标志位

void mode_select(int mode);

#endif
