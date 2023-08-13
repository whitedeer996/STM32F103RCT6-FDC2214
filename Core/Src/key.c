#include "key.h"
#include "STM32OledKey.h"


uint8_t StartTest_Flag = 0;
Key_Mode TestKey_Start;



void State_Machine(Key_Mode self)
{
	 self.Level = HAL_GPIO_ReadPin(TestKey_GPIO_Port,TestKey_Pin);
//   printf("%d",self.Level);
	 switch(self.State)
	 {
			 //状态0：没有按键按下
			 case CHECK:
					 if(self.Level == 0)//有按键按下
					 {
							 self.State = COMFIRM;//转入状态1
							 self.Event = 0;//空事件
					 }
					 else
					 {
							 self.Event = 0;//空事件
					 }
					 break;
			 //状态1：按键按下确认
			 case COMFIRM:
					 if(self.Level == 0)//确认和上次相同，即 PA0 确实按下
					 {
							 self.State = RELEASE;//转入状态2
							 self.Event = 1;//按下事件
					 }
					 else
					 {
							 self.State = CHECK;//转入状态0，即 误触
							 self.Event = 0;//空事件
					 }
					 break;
			 //状态2：按键按下
			 case RELEASE:
					 if(self.Level == 1)//按键释放，端口低电平
					 {
							 self.State = CHECK;//转入状态0
							 self.Event = 2;//松开事件
					 }
					 else if(self.Level == 0)
					 {
							 self.State = RELEASE;//维持状态2
							 self.Event = 3;//按下后未松开事件
					 }
					 break;

			}//switch
//     if(self.Event == 1)
//		 {
////		     StartTest_Flag = 1;
////			   printf("%d",StartTest_Flag);
//			   HAL_GPIO_TogglePin(TestLED_GPIO_Port,TestLED_Pin);
////			   OledKeyBeep(300);
//		 }

}
