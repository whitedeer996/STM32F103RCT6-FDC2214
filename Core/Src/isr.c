#include "isr.h"
#include "main.h"
#include "math.h"
#include "tim.h"
#include "key.h"
#include "STM32OledKey.h"
#include "FDC2214.h"

int CNumDisplay = 0,CNumDisplay_before = 0,CNumDisplay_now = 0;
unsigned char Test_Adjust = 0;

int INT10ms_Count = 0x00;
int INT100ms_Count = 0;




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

		
	if(htim->Instance == TIM7)//1ms÷–∂œ
	{
		INT10ms_Count++;
		if(StartTest_Flag == 1)INT100ms_Count++;
		
		if(INT10ms_Count == 10)
		{			
			 INT10ms_Count = 0;	
		 
       State_Machine(TestKey_Start);
			 if(TestKey_Start.Event == 1)
			 {
//					 StartTest_Flag = 1;
					 HAL_GPIO_TogglePin(TestLED_GPIO_Port,TestLED_Pin);
			 }			
		}
		
		if(INT100ms_Count == 10)
		{
			 INT100ms_Count = 0;
			 CNumDisplay_now = FDC_CNum_To_PaperNum(C_CHO_data_final);
			 if(CNumDisplay_before == CNumDisplay_now)
			 {
				 Test_Adjust = Test_Adjust << 1; 
			 }
			 CNumDisplay_before = CNumDisplay_now;
			 if(Test_Adjust == 0xFF)
			 {
					OLED_ShowNum(55,5,CNumDisplay,2,10);
//					OledKeyBeep(500);
					StartTest_Flag = 0;
			 }
		}			
    

	
		


	}//htim->Instance == TIM7
	
}//TIM_Callback

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_7)
  {

  }
	if (GPIO_Pin == GPIO_PIN_6)
  {

  }
  
//	if(GPIO_Pin == OledINT_Pin)
//	{
//			OledKeyFlag = 1;
//  		HAL_GPIO_TogglePin(TestLed_GPIO_Port,TestLed_Pin); 		
//	}

}
