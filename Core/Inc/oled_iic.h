#ifndef __OLEDIIC_H__
#define __OLEDIIC_H__

#include "main.h"
#include "sys.h"

/*******************************IIC���IO�ڲ���**************************************/
//IO�ڷ���
#define IIC_SDA_IN()  {OledData_GPIO_Port->CRH&=0XFFFFFF0F;OledData_GPIO_Port->CRH|=(unsigned int)8<<4;}		//����SDA����
#define IIC_SDA_OUT() {OledData_GPIO_Port->CRH&=0XFFFFFF0F;OledData_GPIO_Port->CRH|=(unsigned int)3<<4;}		//����SDA���

//IO�ڲ���
#define IIC_SCL(n)    (n?HAL_GPIO_WritePin(OledClk_GPIO_Port,OledClk_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(OledClk_GPIO_Port,OledClk_Pin,GPIO_PIN_RESET)) //SCL
#define IIC_SDA(n)    (n?HAL_GPIO_WritePin(OledData_GPIO_Port,OledData_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(OledData_GPIO_Port,OledData_Pin,GPIO_PIN_RESET))//SDA	 
#define READ_SDA 			 HAL_GPIO_ReadPin(OledData_GPIO_Port,OledData_Pin) //SDA����

/*****************************IIC����***************************************/
void IIC_Start(void); //�����ź�
void IIC_Stop(void); //ֹͣ�ź�
void IIC_Send_Byte(unsigned char txd); //����һ���ֽ�
unsigned char IIC_Read_Byte(unsigned char ack); //��ȡһ���ֽ�
unsigned char IIC_Wait_Ack(void);	//�ȴ�Ӧ��
void IIC_Ack(void);	//����Ӧ��
void IIC_NAck(void);	//������Ӧ��


#endif

