#ifndef __ISR_H__
#define __ISR_H__

#include "main.h"

extern int CNumDisplay;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
#endif 
