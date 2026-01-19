#include "simMath.h"

/**
  * @brief  取绝对值函数(float型)
  * @param  略
  * @retval 略
  */
float sim_FAbs(float x){return (x > 0) ? x : (-x);}
/**
  * @brief  取绝对值函数(int型)
  * @param  略
  * @retval 略
  */
int sim_Abs(int x){return (x > 0) ? x : (-x);}

/**
  * @brief  uchar转int
  * @param  s uchar类型
  * @retval 返回int类型
  */
int sim_Int(uint8_t s){return s-48;}
/**
  * @brief  检查是否为数字
  * @param  s uchar类型
  * @retval 0 正确 1 错误
  */
uint8_t sim_Num_Check(uint8_t s) {if(s > 57 || s < 48) return 1; else return 0;}

void user_delay_us(uint16_t us)
{
	for(; us > 0; us--)
	{
		for(uint8_t i = 50; i > 0; i--)
		{
			;
		}
	}
}
