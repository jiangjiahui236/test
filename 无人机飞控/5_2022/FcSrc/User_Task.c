#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "control.h"
#include "mode.h"
#include "get_data.h"
#include "my_uart.h"

int cnt;

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
					task_select(0);//选择定位坐标数字
					hight_target=150;
					yaw_target=yaw_now;
					dis_x_now=dis_x-dis_x_location+OpenMV_data_1;//赛道坐标原点所在的光流坐标值
					dis_y_now=dis_y-dis_y_location+OpenMV_data_2;
					task_select(task_1);
//					dis_x_target=dis_x_now+dis_x_location;//要去到的光流坐标值
//					dis_y_target=dis_y_now+dis_y_location;
					dis_x_target=dis_x+200;
					dis_y_target=dis_y;
					mission_step++;}break;
				case 11:{
					if((dis_x_target-dis_x)>-5&&(dis_x_target-dis_x)<5&&(dis_y_target-dis_y)>-5&&(dis_y_target-dis_y)<5) cnt++; else cnt=0;
					if(cnt>=25) mission_step++;}break;//光流数据到定位
				case 12:{mission_step=999;}break;
				
				
				case 20:{
					mode_select(3);//选择对准模式
					hight_target=80;
					mission_step++;}break;
				case 21:{
					if((hight_target-hight)>-5&&(hight_target-hight)<5) cnt++; else cnt=0;
					if(cnt>=5) mission_step++;}break;//高度达标
				case 22:{
					if(OpenMV_data_0==1&&OpenMV_data_1>-5&&OpenMV_data_1<5&&OpenMV_data_2>-5&&OpenMV_data_2<5) cnt++; else cnt=0;
					if(cnt>=5) mission_step++;}break;//对准达标
				case 23:{User_Task_Delay(3000);}break;//悬停
				case 24:{hight_target=150;User_Task_Delay(3000);}break;//恢复高度
				case 25:{mission_step=30;}break;
				
				
				case 30:{
					mode_select(2);//选择飞行模式
					dis_x_now=dis_x-dis_x_location+OpenMV_data_1;//赛道坐标原点所在的光流坐标值
					dis_y_now=dis_y-dis_y_location+OpenMV_data_2;
					task_select(task_2);//选择定位坐标数字
					dis_x_target=dis_x_now+dis_x_location;//要去到的光流坐标值
					dis_y_target=dis_y_now+dis_y_location;
					mission_step++;}break;
				case 31:{
					if((dis_x_target-dis_x)>-5&&(dis_x_target-dis_x)<5&&(dis_y_target-dis_y)>-5&&(dis_y_target-dis_y)<5) cnt++; else cnt=0;
					if(cnt>=25) mission_step++;}break;//光流数据到定位
				case 32:{mission_step=40;}break;
				
				
				case 40:{
					mode_select(3);//选择对准模式
					hight_target=80;
					mission_step++;}break;
				case 41:{
					if((hight_target-hight)>-5&&(hight_target-hight)<5) cnt++; else cnt=0;
					if(cnt>=5) mission_step++;}break;//高度达标
				case 42:{
					if(OpenMV_data_0==1&&OpenMV_data_1>-5&&OpenMV_data_1<5&&OpenMV_data_2>-5&&OpenMV_data_2<5) cnt++; else cnt=0;
					if(cnt>=5) mission_step++;}break;//对准达标
				case 43:{User_Task_Delay(3000);}break;//悬停
				case 44:{hight_target=150;User_Task_Delay(3000);}break;//恢复高度
				case 45:{mission_step=50;}break;
				
				
				case 50:{
					mode_select(2);//选择飞行模式
					dis_x_now=dis_x-dis_x_location+OpenMV_data_1;//赛道坐标原点所在的光流坐标值
					dis_y_now=dis_y-dis_y_location+OpenMV_data_2;
					task_select(0);//选择定位坐标数字
					dis_x_target=dis_x_now+dis_x_location;//要去到的光流坐标值
					dis_y_target=dis_y_now+dis_y_location;
					mission_step++;}break;
				case 51:{
					if((dis_x_target-dis_x)>-5&&(dis_x_target-dis_x)<5&&(dis_y_target-dis_y)>-5&&(dis_y_target-dis_y)<5) cnt++; else cnt=0;
					if(cnt>=25) mission_step++;}break;//光流数据到定位
				case 52:{mission_step=999;}break;
				
				///////////////////////////////////////////基础试飞///////////////////////////////////////////
				
				
				//一键降落
				case 999:{mode_select(3);OneKey_Land();}break;
				default:break;
			}
		}
		else
		{
			mission_step = 0;
		}
	
    ////////////////////////////////////////////////////////////////////////
}
