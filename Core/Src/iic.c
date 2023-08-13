#include "main.h"
#include "iic.h"

//void FDC2214_IIC_Init(void)�����ǳ�ʼ�� SCL��SDA��������
void FDC2214_IIC_Init(void)
{					     
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	 
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  HAL_GPIO_WritePin(GPIOB, FDC2214_CLK_Pin|FDC2214_SDA_Pin, GPIO_PIN_RESET);
	 
		GPIO_InitStruct.Pin = FDC2214_CLK_Pin|FDC2214_SDA_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//void FDC2214_IIC_Start(void) �����ǲ���START�ź�
void FDC2214_IIC_Start(void)
{
		SDA_OUT();     
		FDC2214_IIC_SDA=1;	  	  
		FDC2214_IIC_SCL=1;
		delay_us(4);
		FDC2214_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
		delay_us(4);
		FDC2214_IIC_SCL=0;
}	

//void FDC2214_IIC_Stop(void)�����ǲ���STOP�ź�
void FDC2214_IIC_Stop(void)
{
		SDA_OUT();
		FDC2214_IIC_SCL=0;
		FDC2214_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
		delay_us(4);
		FDC2214_IIC_SCL=1; 
		FDC2214_IIC_SDA=1;
		delay_us(4);							   	
}
   
//u8 FDC2214_IIC_Wait_Ack(void)�����ǽ��մӻ����͵�ACK
u8 FDC2214_IIC_Wait_Ack(void)
{
		u8 ucErrTime=0;
		SDA_IN();      
		FDC2214_IIC_SDA=1;delay_us(1);	   
		FDC2214_IIC_SCL=1;delay_us(1);	 
		while(FDC2214_READ_SDA)
		{
			ucErrTime++;
			if(ucErrTime>250)
			{
				FDC2214_IIC_Stop();
				return 1;
			}
		}
		FDC2214_IIC_SCL=0;	   
		return 0;  
} 

//Set up AC;K void FDC2214_IIC_Ack(void)�����������������ݺ����Ӧ���ź�
void FDC2214_IIC_Ack(void)
{
		FDC2214_IIC_SCL=0;
		SDA_OUT();
		FDC2214_IIC_SDA=0;
		delay_us(2);
		FDC2214_IIC_SCL=1;
		delay_us(2);
		FDC2214_IIC_SCL=0;
}
//Set up NACK(NO ACK);void FDC2214_IIC_NAck(void) �����������������ݺ󲻲���Ӧ���ź�    
void FDC2214_IIC_NAck(void)
{
		FDC2214_IIC_SCL=0;
		SDA_OUT();
		FDC2214_IIC_SDA=1;
		delay_us(2);
		FDC2214_IIC_SCL=1;
		delay_us(2);
		FDC2214_IIC_SCL=0;
}					 				     
//IIC Send Byte;voiFDC2214_d IIC_Send_Byte(u8 txd) �����Ƿ���һ���ֽڵ�����
void FDC2214_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	  SDA_OUT(); 	    
    FDC2214_IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
				//IIC_SDA=(txd&0x80)>>7;
				if((txd&0x80)>>7)
					FDC2214_IIC_SDA=1;
				else
					FDC2214_IIC_SDA=0;
				txd<<=1; 	  
				delay_us(2);   
				FDC2214_IIC_SCL=1;
				delay_us(2); 
				FDC2214_IIC_SCL=0;	
				delay_us(2);
    }	 
} 	    
//ack = 0 send Nack  ack = 1 send ACK FDC2214_;u8 IIC_Read_Byte(unsigned char ack)�����ǽ���һ���ֽڵ����� 
u8 FDC2214_IIC_Read_Byte(unsigned char ack)
{
		unsigned char i,receive=0;
		SDA_IN();
		for(i=0;i<8;i++ )
		{
			FDC2214_IIC_SCL=0; 
			delay_us(2);
			FDC2214_IIC_SCL=1;
			receive<<=1;
			if(FDC2214_READ_SDA)receive++;   
			delay_us(1); 
		}					 
			if (!ack)
					FDC2214_IIC_NAck();
			else
					FDC2214_IIC_Ack(); 
			return receive;
}
