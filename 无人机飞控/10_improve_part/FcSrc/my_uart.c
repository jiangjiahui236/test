//////////////////////////////////////////////////////////////////////
/*
串口通信
*/
//////////////////////////////////////////////////////////////////////

#include "my_uart.h"
#include "Drv_Uart.h"
#include "get_data.h"
#include "mode.h"
#include "mbotLinuxUsart.h"
#include "KEY.h"

int16_t test_data_1,test_data_2;
int16_t OpenMV_data_0,OpenMV_data_1,OpenMV_data_2;

int16_t OpenMV_help_fix_x,OpenMV_help_fix_y;

unsigned char car_data_0,car_data_1,fire_x,fire_y;

void MY_urst1_Receive(uint8_t data)
{
	static int data_cnt=0;
	static uint8_t  data_1,data_2,data_3,data_4;
	if((data_cnt==0)&&(data==0x0A))data_cnt=1;
	else if(data_cnt==1){data_1=data;data_cnt=2;}
	else if(data_cnt==2){data_2=data;data_cnt=3;}
	else if(data_cnt==3){data_3=data;data_cnt=4;}
	else if(data_cnt==4){data_4=data;data_cnt=0;}
	else data_cnt=0;
	test_data_1 = data_2;
	test_data_1<<=8;
	test_data_1 |=data_1;
	test_data_2 = data_4;
	test_data_2<<=8;
	test_data_2 |=data_3;
}

void MY_urst1_car_Receive(uint8_t data)
{
	static int data_cnt=0;
	if((data_cnt==0)&&(data==0x0A))data_cnt=1;
	else if(data_cnt==1){car_data_0=data;data_cnt=2;}
	else if(data_cnt==2){car_data_1=data;data_cnt=3;}
	else data_cnt=0;
	
	if(car_data_0==2){fire_x=car_data_1%6;fire_y=car_data_1/6+1;}
}

void MY_urst1_Send_xy(void)
{
	u8 Buf[]={0x0A,0x01,radar_data_1/10,radar_data_2/10};
//	u8 Buf[]={0x0A,0x01,3,4};
	DrvUart1SendBuf(Buf,sizeof(Buf));
}

void MY_urst1_Send_fire(void)
{
	u8 Buf[]={0x0A,0x02,radar_data_1/10,radar_data_2/10};
//	u8 Buf[]={0x0A,0x02,5,6};
	DrvUart1SendBuf(Buf,sizeof(Buf));
}

void MY_urst2_Send(int to_OpenMV_data_0)
{
	u8 Buf[]={to_OpenMV_data_0,0x0A};
	DrvUart2SendBuf(Buf,sizeof(Buf));
}

void MY_urst2_Receive(uint8_t data)
{
	static int data_cnt=0;
	static uint8_t  data_1,data_2,data_3,data_4,data_5;
	if((data_cnt==0)&&(data==0x0A))data_cnt=1;
	else if(data_cnt==1){data_1=data;data_cnt=2;}
	else if(data_cnt==2){data_2=data;data_cnt=3;}
	else if(data_cnt==3){data_3=data;data_cnt=4;}
	else if(data_cnt==4){data_4=data;data_cnt=5;}
	else if(data_cnt==5){data_5=data;data_cnt=0;}
	else data_cnt=0;
	OpenMV_data_0 = data_1;
	
	if(OpenMV_data_0!=9)
	{
		int mode;
		mode=dis_group[1][dis_target_ref];
		if(KEY_2!=0)mode=KEY_2;
		if(OpenMV_data_0==mode)//只接收对应模式的数据
		{
			OpenMV_data_1 = data_3;
			OpenMV_data_1<<=8;
			OpenMV_data_1 |=data_2;
			OpenMV_data_2 = data_5;
			OpenMV_data_2<<=8;
			OpenMV_data_2 |=data_4;
			
			
			if(mode==1)//黑色方块
			{
				OpenMV_data_1=-(OpenMV_data_1-160)/240.0*hight;
				OpenMV_data_2=(OpenMV_data_2-120)/240.0*hight;
			}
			if(mode==2)//上边界
			{
				OpenMV_data_1=OpenMV_data_1/240.0*hight;
//				OpenMV_help_fix_y=320-radar_data_2_original-OpenMV_data_1;//通过openmv修正激光雷达的数据
			}
			if(mode==3)//右边界
			{
				OpenMV_data_1=OpenMV_data_1/240.0*hight;
//				OpenMV_help_fix_x=400-radar_data_1_original-OpenMV_data_1;//通过openmv修正激光雷达的数据
			}
			
			
			
			
			
			
			
//			//OpenMV换算为实际距离,普通镜头
//			OpenMV_data_1=(OpenMV_data_1-60)/120.0*hight;
//			OpenMV_data_2=(OpenMV_data_2-80)/160.0*hight*4.0/3.0;
//			//OpenMV换算为实际距离,广角镜头
//			OpenMV_data_1=(OpenMV_data_1-60)/120.0*hight*5.0/3.0;
//			OpenMV_data_2=(OpenMV_data_2-80)/160.0*hight*5.0/3.0*4.0/3.0;
		}
	}
	else
	{
		OpenMV_data_1=0;
		OpenMV_data_2=0;
	}
}

