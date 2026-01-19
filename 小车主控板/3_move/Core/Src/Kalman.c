#include "Kalman.h"

/* Kalman *  卡尔曼结构体函数 */

//void Kalman_Init()
//{
//	 Last_P = 1;		//k-1时刻的系统协方差	
//	 Now_P = 0;		//k时刻系统估计协方差 
//	 out = 0;			//状态变量的预测值
//	 Kg = 0;		    //卡尔曼增益
//	 Q = 0;        //过程噪声协方差
//	 R = 0.01;     //观测噪声方差
//	
//}


//float KalmanFilter(float input)
//{
//   //预测协方差方程：k时刻系统估计协方差 = k-1时刻的系统协方差 + 过程噪声协方差
//    Now_P =  Last_P +  Q;
//	 //卡尔曼增益方程: 卡尔曼增益 = k时刻系统估计协方差 / （k时刻系统估计协方差 + 观测噪声方差）
//    Kg =  Now_P / ( Now_P +  R);
//	 //更新最优方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
//    out =  out +  Kg * (input - out);
//   //更新协方差方程：本次的系统协方差付给 >LastP 为下一次运算做准备
//    Last_P = (1- Kg) *  Now_P;
//   return  out;
//}


float	Last_P = 1  ,		//k-1时刻的系统协方差	
   	Now_P = 1,		//k时刻系统估计协方差 
	  out = 1,			//状态变量的预测值
	  Kg = 1,	    //卡尔曼增益
	  Q = 1,        //过程噪声协方差
	  R = 0.1;     //观测噪声方差


float KalmanFilter(float input)
{
   //预测协方差方程：k时刻系统估计协方差 = k-1时刻的系统协方差 + 过程噪声协方差
    Now_P =  Last_P +  Q;
	 //卡尔曼增益方程: 卡尔曼增益 = k时刻系统估计协方差 / （k时刻系统估计协方差 + 观测噪声方差）
    Kg =  Now_P / ( Now_P +  R);
	 //更新最优方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
    out =  out +  Kg * (input - out);
   //更新协方差方程：本次的系统协方差付给 >LastP 为下一次运算做准备
    Last_P = (1- Kg) *  Now_P;
   return  out;
}


//  while (1)
//  {
//		KalmanFilter(distance);
//		printf("%f",distance);
//		delay_ms(100);
//  }
