#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "control.h"
#include "mode.h"
#include "get_data.h"
#include "my_uart.h"
#include "KEY.h"
#include "mbotLinuxUsart.h"
#include "Ano_Scheduler.h"
#include "buzzer.h"

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
				case 3:{User_Task_Delay(2000);}break;
				//起飞
				case 4:
					{
						set_dis_zero();//坐标初始化
						dis_x_target=0;
						dis_y_target=0;
						hight_target=150;//定高
						yaw_target=yaw;//定角度
						mode_select(2);//起飞
						User_Task_Delay(3000);
					}break;
					case 5:{mission_step=10;}break;
//				//OpenMV定位起点
//				case 5:{dis_target_ref=0;mode_select(3);mission_step++;}break;
//				case 6:{if(OpenMV_data_1>-5&&OpenMV_data_1<5&&OpenMV_data_2>-5&&OpenMV_data_2<5) cnt++;else cnt=0;
//					if(cnt>=25){mission_step++;cnt=0;beep_bsp(1);}}break;
//				//重新建图
//				case 7:{KEY_1=1;User_Task_Delay(500);}break;
//				case 8:{KEY_1=0;if(radar_wait_time<=10)mission_step++;}break;
//				case 9:{beep_bsp(0);mission_step=10;}break;////////////////////////////////
				
				case 10:{
					mode_select(4);//选择飞行模式
					dis_target_ref=1;
					time_cnt_ms=0;
//					//选择坐标原点
//					dis_x_zore_fix=dis_x;
//					dis_y_zore_fix=dis_y;
					mission_step++;}break;
				case 11:{dis_target_select(dis_target_ref);User_Task_Delay(500);}break;//更新目标，选择坐标模式
				case 12:{
					if(dis_x_target-radar_data_1>-10&&dis_x_target-radar_data_1<10&&dis_y_target-radar_data_2>-10&&dis_y_target-radar_data_2<10)cnt++;else cnt=0;//到达目标
					if(cnt>=25){mission_step++;cnt=0;}
				}break;
				case 13:{
					if(dis_target_ref<12){dis_target_ref++;mission_step=11;}//更新目标编号
					else mission_step=19;//到达目标11后
				}break;
				case 19:{hight_target=10;if(hight<20)mission_step=999;}break;
				///////////////////////////////////////////基础试飞///////////////////////////////////////////
				
				
				//一键降落
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
