#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "sys.h"

typedef enum
{
   CHECK=0,//0为按键检测状态
   COMFIRM = 1,//1为按键确认状态
   RELEASE = 2,//2为按键释放状态
}KEY_STATE;

typedef struct
{
   u8 Level;//电平状态
   u8 State;//0为按键检测状态；1为按键确认状态；2为按键释放状态
   u8 Event;//相应的事件
}Key_Mode;



extern Key_Mode TestKey_Start;
extern uint8_t StartTest_Flag;


void State_Machine(Key_Mode self);












#endif
