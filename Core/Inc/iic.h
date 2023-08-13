#ifndef __IIC_H
#define __IIC_H

#include "sys.h"

//IO口方向
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
 
//IO操作函数	 
#define FDC2214_IIC_SCL    PBout(6) //SCL
#define FDC2214_IIC_SDA    PBout(7) //SDA	 
#define FDC2214_READ_SDA   PBin(7)  //SDA输入
 
//IIC函数
void FDC2214_IIC_Init(void);                			 
void FDC2214_IIC_Start(void);				
void FDC2214_IIC_Stop(void);	  			
void FDC2214_IIC_Send_Byte(u8 txd);			
u8 FDC2214_IIC_Read_Byte(unsigned char ack);
u8 FDC2214_IIC_Wait_Ack(void); 				
void FDC2214_IIC_Ack(void);					
void FDC2214_IIC_NAck(void);	

#endif
