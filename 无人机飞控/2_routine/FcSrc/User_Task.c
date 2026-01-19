#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "control.h"

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
    if (rc_in.no_signal == 0)
    {
//        //判断第6通道拨杆位置 1300<CH_6<1700
//        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1300 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1700)
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
				case 0:{Task_time_dly_cnt_ms = 0;}break;
				//切换程控模式
				case 1:{mission_step += LX_Change_Mode(2);}break;/////////////////////////
				//解锁和初始化
				case 2:{all_data_init();mission_step += FC_Unlock();}break;
				case 3:{User_Task_Delay(2000);}break;
				//起飞
				case 4:{mission_step += OneKey_Takeoff(100);}break;
				case 5:{User_Task_Delay(3000);}break;
				case 6:{mission_step=10;}break;
				
				case 10:{my_give_vel_x=30;User_Task_Delay(3000);}break;
				case 11:{my_give_vel_x=0;User_Task_Delay(3000);}break;
				case 12:{mission_step=999;}break;
				
				
				
				//一键降落
				case 999:{OneKey_Land();}break;
				default:break;
			}
		}
		else
		{
			mission_step = 0;
		}
	}
    ////////////////////////////////////////////////////////////////////////
}
