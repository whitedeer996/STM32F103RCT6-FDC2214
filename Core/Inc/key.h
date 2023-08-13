#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "sys.h"

typedef enum
{
   CHECK=0,//0Ϊ�������״̬
   COMFIRM = 1,//1Ϊ����ȷ��״̬
   RELEASE = 2,//2Ϊ�����ͷ�״̬
}KEY_STATE;

typedef struct
{
   u8 Level;//��ƽ״̬
   u8 State;//0Ϊ�������״̬��1Ϊ����ȷ��״̬��2Ϊ�����ͷ�״̬
   u8 Event;//��Ӧ���¼�
}Key_Mode;



extern Key_Mode TestKey_Start;
extern uint8_t StartTest_Flag;


void State_Machine(Key_Mode self);












#endif
