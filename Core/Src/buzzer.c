#include "buzzer.h"
extern TIM_HandleTypeDef htim4;
void Buzzer_SetFrequency(uint32_t freq)
{
	uint32_t arr;
	if(freq == 0)
  {
		return;
	}
	arr = (1000000 / freq) - 1;
	/* 修改PWM周期 */
	__HAL_TIM_SET_AUTORELOAD(&htim4,arr);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,(arr + 1) / 2);
	__HAL_TIM_SET_COUNTER(&htim4,0);
}

void Buzzer_init(void)
{
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	Buzzer_off();
}

void Buzzer_on(void)
{
	Buzzer_SetFrequency(2000);
}

void Buzzer_off(void)
{
	uint32_t arr;
	arr = __HAL_TIM_GET_AUTORELOAD(&htim4);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,arr + 1);
}
