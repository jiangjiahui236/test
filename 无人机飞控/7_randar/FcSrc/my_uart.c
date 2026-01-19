//////////////////////////////////////////////////////////////////////
/*
串口通信
*/
//////////////////////////////////////////////////////////////////////

#include "my_uart.h"
#include "Drv_Uart.h"
#include "get_data.h"

int16_t test_data_1,test_data_2;
int16_t OpenMV_data_0,OpenMV_data_1,OpenMV_data_2;
int8_t to_OpenMV_data_0;

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

void MY_urst2_Send(void)
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
		OpenMV_data_1 = data_3;
		OpenMV_data_1<<=8;
		OpenMV_data_1 |=data_2;
		OpenMV_data_2 = data_5;
		OpenMV_data_2<<=8;
		OpenMV_data_2 |=data_4;
		
		OpenMV_data_1	=(OpenMV_data_1 + (2.2 *pit));
		OpenMV_data_2	=(OpenMV_data_2 - (2.2 *rol));		
		
		//OpenMV换算为实际距离,普通镜头
		OpenMV_data_1=-(OpenMV_data_1-80)/160.0*hight*4.0/3.0;
		OpenMV_data_2=-(60-OpenMV_data_2-16)/120.0*hight;
		
//		OpenMV_data_1-=80;
//		OpenMV_data_2-=60;
	}
	else
	{
		OpenMV_data_1=0;
		OpenMV_data_2=0;
	}
}

