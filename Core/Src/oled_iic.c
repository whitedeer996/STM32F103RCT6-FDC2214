#include "oled_iic.h"


//I2C起始信号
void IIC_Start(void)
{
	IIC_SDA_OUT();//SDA设置为输出
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	delay_us(4);
 	IIC_SDA(0);//START:when CLK is 1,DATA change form 1 to 0 
	delay_us(4);
	IIC_SCL(0);
}

//I2C停止信号
void IIC_Stop(void)
{
	IIC_SDA_OUT();//SDA设置为输出
	IIC_SCL(1);
	IIC_SDA(0);//STOP:when CLK is 1 DATA change form 0 to 1
	delay_us(4);
	 
	IIC_SDA(1);		
	delay_us(4);	
}

//等待应答信号到来
//返回值： 1，接收应答失败
// 0，接收应答成功
unsigned char IIC_Wait_Ack(void)
{
//	unsigned char ucErrTime=0;
	IIC_SDA_IN();//SDA设置为输入
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
//产生 ACK 应答
void IIC_Ack(void)
{
	IIC_SCL(0);
	IIC_SDA_OUT();//SDA输出	
	IIC_SDA(0);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}
//不产生 ACK 应答
void IIC_NAck(void)
{
	IIC_SDA_OUT();//SDA输出	
	IIC_SCL(0);
	IIC_SDA(1);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
	delay_us(2);
}

//IIC 发送一个字节
//返回值为  从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(unsigned char txd)
{
	unsigned char t;
	IIC_SDA_OUT();//SDA输出											
	IIC_SCL(0);					//SCL拉低开始数据传输
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

//I2C读1个字节,ack=1时,发送 ACK,ack=0,发送NACK
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	IIC_SDA_IN();														//SDA设置为输入
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
		IIC_NAck();													//发送nACK
	else
		IIC_Ack();													//发送ACK
	
	return receive;
}



