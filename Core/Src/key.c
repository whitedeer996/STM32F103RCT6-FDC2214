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
			 //״̬0��û�а�������
			 case CHECK:
					 if(self.Level == 0)//�а�������
					 {
							 self.State = COMFIRM;//ת��״̬1
							 self.Event = 0;//���¼�
					 }
					 else
					 {
							 self.Event = 0;//���¼�
					 }
					 break;
			 //״̬1����������ȷ��
			 case COMFIRM:
					 if(self.Level == 0)//ȷ�Ϻ��ϴ���ͬ���� PA0 ȷʵ����
					 {
							 self.State = RELEASE;//ת��״̬2
							 self.Event = 1;//�����¼�
					 }
					 else
					 {
							 self.State = CHECK;//ת��״̬0���� ��
							 self.Event = 0;//���¼�
					 }
					 break;
			 //״̬2����������
			 case RELEASE:
					 if(self.Level == 1)//�����ͷţ��˿ڵ͵�ƽ
					 {
							 self.State = CHECK;//ת��״̬0
							 self.Event = 2;//�ɿ��¼�
					 }
					 else if(self.Level == 0)
					 {
							 self.State = RELEASE;//ά��״̬2
							 self.Event = 3;//���º�δ�ɿ��¼�
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
