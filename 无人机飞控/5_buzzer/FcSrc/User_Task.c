#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "control.h"
#include "mode.h"
#include "get_data.h"
#include "my_uart.h"

void UserTask_OneKeyCmd(void)
{
    //////////////////////////////////////////////////////////////////////
    //一键起飞/降落例程
    //////////////////////////////////////////////////////////////////////
    //用静态变量记录一键起飞/降落指令已经执行。
    static u8 one_key_land_f = 1, one_key_mission_f = 0;
//    static u8 one_key_takeoff_f = 1;
//    static u8 mission_step;
    //判断有遥控信号才执行
//    if (rc_in.no_signal == 0)
//    {
//        //判断第6通道拨杆位置 1300<CH_6<1700
//        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1200)
//        {
//            //还没有执行
//            if (one_key_takeoff_f == 0)
//            {
//                //标记已经执行
//                one_key_takeoff_f =
//                    //执行一键起飞
//                    OneKey_Takeoff(100); //参数单位：厘米； 0：默认上位机设置的高度。
//            }
//        }
//        else
//        {
//            //复位标记，以便再次执行
//            one_key_takeoff_f = 0;
//        }
        //
        //判断第6通道拨杆位置 1700<CH_6<2200，右拨杆向下
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1700 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 2200)
        {
            //还没有执行
            if (one_key_land_f == 0)
            {
                //标记已经执行
                one_key_land_f =
                    //执行一键降落
                    OneKey_Land();
            }
        }
        else
        {
            //复位标记，以便再次执行
            one_key_land_f = 0;
        }
	//判断第6通道拨杆位置 800<CH_6<1200，右拨杆向上
		if(rc_in.rc_ch.st_data.ch_[ch_6_aux2]>800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2]<1200)
		{
			//还没有执行
			if(one_key_mission_f ==0)
			{
				//标记已经执行
				one_key_mission_f = 1;
				//开始流程
				mission_step = 1;
			}
		}
		else
		{
			//复位标记，以便再次执行
			one_key_mission_f = 0;		
		}
		//
		if(one_key_mission_f==1)
		{
			switch(mission_step)
			{
				
				///////////////////////////////////////////mdoe 0试飞///////////////////////////////////////////
				case 0:{Task_time_dly_cnt_ms = 0;}break;
				//切换程控模式
				case 1:{mission_step += LX_Change_Mode(2);}break;/////////////////////////
				//解锁和初始化
				case 2:{all_data_init();mode_select(0);mission_step += FC_Unlock();}break;
				case 3:{yaw_now=yaw;User_Task_Delay(2000);}break;
				//起飞
				case 4:{mission_step += OneKey_Takeoff(160);}break;
				case 5:{User_Task_Delay(2000);}break;
				//进入测试模式
				case 6:{mission_step=10;}break;////////////////////////////////
				
				case 10:{
					mode_select(2);//选择飞行模式
					time_cnt_ms=0;
					hight_target=150;
					dis_x_now=dis_x;//记录当前数据
					dis_y_now=dis_y;
					yaw_target=yaw_now;
					mission_step++;}break;
//				case 11:{yaw_target=yaw_now+triangualr_wave(90);User_Task_Delay(30000);}break;//角度来回
//				case 11:{hight_target=100+square_wave(30);User_Task_Delay(30000);}break;//高度来回
				case 11:{dis_x_target=dis_x_now+triangualr_wave(200) ;dis_y_target=dis_y_now;User_Task_Delay(30000);}break;//定高定角度xy来回
//				case 11:{User_Task_Delay(30000);}break;//跟随OpenMV
				case 12:{mission_step=999;}break;
				///////////////////////////////////////////基础试飞///////////////////////////////////////////
				
				
				//一键降落
//				case 999:{mode_select(0);OneKey_Land();}break;
				case 999:{mode_select(0);OneKey_Land();}break;
				default:break;
			}
		}
		else
		{
			mission_step = 0;
		}
	
    ////////////////////////////////////////////////////////////////////////
}
