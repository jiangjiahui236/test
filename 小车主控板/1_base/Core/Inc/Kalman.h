#ifndef Kalman_H
#define Kalman_H



//struct 
//{
//    float Last_P; //上次估计协方差 不可以为0
//    float Now_P;  //当前估计协方差
//    float out;    //卡尔曼滤波输出
//    float Kg;     //卡尔曼增益
//    float Q;      //过程噪声协方差
//    float R;      //观测噪声协方差
//}kfp;

void Kalman_Init(void);
float KalmanFilter(float input);



#endif
