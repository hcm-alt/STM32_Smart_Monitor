#include "ultrasonic.h"
extern TIM_HandleTypeDef htim2;

void Ultrasonic_Start(void)
{
	HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin,GPIO_PIN_RESET);
}

void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim2,0); //CNT清零
	while(__HAL_TIM_GET_COUNTER(&htim2) < us);
}