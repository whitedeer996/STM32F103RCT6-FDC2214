#include "main.h"
#include "iic.h"

//void FDC2214_IIC_Init(void)函数是初始化 SCL，SDA两个引脚
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

//void FDC2214_IIC_Start(void) 函数是产生START信号
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

//void FDC2214_IIC_Stop(void)函数是产生STOP信号
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
   
//u8 FDC2214_IIC_Wait_Ack(void)函数是接收从机发送的ACK
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

//Set up AC;K void FDC2214_IIC_Ack(void)函数是主机读完数据后产生应答信号
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
//Set up NACK(NO ACK);void FDC2214_IIC_NAck(void) 函数是主机读完数据后不产生应答信号    
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
//IIC Send Byte;voiFDC2214_d IIC_Send_Byte(u8 txd) 函数是发送一个字节的数据
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
//ack = 0 send Nack  ack = 1 send ACK FDC2214_;u8 IIC_Read_Byte(unsigned char ack)函数是接收一个字节的数据 
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
