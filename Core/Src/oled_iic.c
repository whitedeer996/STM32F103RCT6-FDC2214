#include "oled_iic.h"


//I2C��ʼ�ź�
void IIC_Start(void)
{
	IIC_SDA_OUT();//SDA����Ϊ���
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	delay_us(4);
 	IIC_SDA(0);//START:when CLK is 1,DATA change form 1 to 0 
	delay_us(4);
	IIC_SCL(0);
}

//I2Cֹͣ�ź�
void IIC_Stop(void)
{
	IIC_SDA_OUT();//SDA����Ϊ���
	IIC_SCL(1);
	IIC_SDA(0);//STOP:when CLK is 1 DATA change form 0 to 1
	delay_us(4);
	 
	IIC_SDA(1);		
	delay_us(4);	
}

//�ȴ�Ӧ���źŵ���
//����ֵ�� 1������Ӧ��ʧ��
// 0������Ӧ��ɹ�
unsigned char IIC_Wait_Ack(void)
{
//	unsigned char ucErrTime=0;
	IIC_SDA_IN();//SDA����Ϊ����
	IIC_SDA(1);//delay_us(1);
	IIC_SCL(1);//delay_us(1);
//	while(READ_SDA)
//	{
//		ucErrTime++;
//		if(ucErrTime>250)
//		{
//			IIC_Stop();
//			return 1;
//		}
//	}
	IIC_SCL(0);	
	return 0;
} 
//���� ACK Ӧ��
void IIC_Ack(void)
{
	IIC_SCL(0);
	IIC_SDA_OUT();//SDA���	
	IIC_SDA(0);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}
//������ ACK Ӧ��
void IIC_NAck(void)
{
	IIC_SDA_OUT();//SDA���	
	IIC_SCL(0);
	IIC_SDA(1);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
	delay_us(2);
}

//IIC ����һ���ֽ�
//����ֵΪ  �ӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(unsigned char txd)
{
	unsigned char t;
	IIC_SDA_OUT();//SDA���											
	IIC_SCL(0);					//SCL���Ϳ�ʼ���ݴ���
	for(t = 0; t < 8; t++)
	{
	IIC_SDA((txd & 0x80) >> 7);
	txd <<= 1;
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
	delay_us(2);
	}
}

//I2C��1���ֽ�,ack=1ʱ,���� ACK,ack=0,����NACK
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	IIC_SDA_IN();														//SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		IIC_SCL(0);
		delay_us(2);
		IIC_SCL(1);
		delay_us(2);
    receive <<= 1;
    if (READ_SDA) receive++;
	}
	if (!ack)
		IIC_NAck();													//����nACK
	else
		IIC_Ack();													//����ACK
	
	return receive;
}



