#include "main.h"
#include "iic.h"
#include "FDC2214.h"
#include "STM32OledKey.h"
#include "isr.h"

//本.c文件配置与FDC2214通信的函数

u16 C_Data = 0;
u8 Receive_Date[2];

u32 C_CHO_data_final = 0;
//FDC2214初始化的函数如下：
void FDC_Start(void)  
{    
			FDC_write_reg(0x08,0x8329);  //(CHx_RCOUNT*16)/55M ==9.76ms，,每10ms左右可以读一次值
			FDC_write_reg(0x09,0x8329);
			FDC_write_reg(0x0A,0x8329);	
			FDC_write_reg(0x0B,0x8329);

			FDC_write_reg(0x10,0x000A);  //设置4个通道最小稳定时间
			FDC_write_reg(0x11,0x000A);
			FDC_write_reg(0x12,0x000A);
			FDC_write_reg(0x13,0x000A);

			FDC_write_reg(0x14,0x1001);  //时钟除以1，设置传感器频率在0.01M到8.5M之间
			FDC_write_reg(0x15,0x1001);
			FDC_write_reg(0x16,0x1001);
			FDC_write_reg(0x17,0x1001);

			FDC_write_reg(0x19,0x0000);  //不设置中断标志位
			FDC_write_reg(0x1B,0xC20D);  //使能0,1,2,3通道，且带宽设置为10M

			FDC_write_reg(0x1E,0x8000);  //设置4个通道的驱动电流
			FDC_write_reg(0x1F,0x8000);
			FDC_write_reg(0x20,0x8000);
			FDC_write_reg(0x21,0x8000);


			FDC_write_reg(0x1A,0x1401);	//使能FDC2214,且取内部时钟为参考时钟
}




//向FDC2214寄存器写的函数如下：
//这里 FDC_Address_W =0x54
void FDC_write_reg(u8 addr,u16 value)   //addr 为寄存器地址，value为需要写入的寄存器数据 
{ 
	   FDC2214_IIC_Start();                    //产生START信号
	   FDC2214_IIC_Send_Byte(FDC_Address_W);   //发送从机地址和写信号
	   FDC2214_IIC_Wait_Ack();                 //等待ACK
	   FDC2214_IIC_Send_Byte(addr);            //发送需要写入的寄存器地址
	   FDC2214_IIC_Wait_Ack();                 //等待ACK
	   FDC2214_IIC_Send_Byte(value>>8);        //发送高8位数据
	   FDC2214_IIC_Wait_Ack();                 //等待ACK
	   FDC2214_IIC_Send_Byte(value&0xFF);      //发送低8位数据
	   FDC2214_IIC_Wait_Ack();                 //等待ACK
     FDC2214_IIC_Stop();                     //产生STOP信号
	   HAL_Delay(1);
}

//从FDC2214读16位数据的函数如下：
//FDC_Address_W =0x54
//FDC_Address_R =0x55
//Receive_Date[] 为接收数据的数组
//C_Data 为一个16位无符号的整型
u16 FDC_read_reg(u8 addr)
{
	
	
		 FDC2214_IIC_Start();                    //产生START信号
		 FDC2214_IIC_Send_Byte(FDC_Address_W);   //发送写命令
		 FDC2214_IIC_Wait_Ack();		
		 FDC2214_IIC_Send_Byte(addr);            //发送需要读的寄存器的地址
		 FDC2214_IIC_Wait_Ack();
	
		 FDC2214_IIC_Start();
		 FDC2214_IIC_Send_Byte(FDC_Address_R);  //发送读命令
		 FDC2214_IIC_Wait_Ack();
	     
	   Receive_Date[0]=FDC2214_IIC_Read_Byte(1);  //读高8位
		 Receive_Date[1]=FDC2214_IIC_Read_Byte(0);  //读低8位
		 FDC2214_IIC_Stop();	                    //产生STOP信号
		 C_Data=(Receive_Date[0]<<8)+ Receive_Date[1];
		 return C_Data;
}

//从FDC2214读高8位数据的函数如下：
u8 FDC_read_reg_high(u8 addr)
{
		 FDC2214_IIC_Start();
		 FDC2214_IIC_Send_Byte(FDC_Address_W);   
		 FDC2214_IIC_Wait_Ack();		
		 FDC2214_IIC_Send_Byte(addr);
		 FDC2214_IIC_Wait_Ack();
	
		 FDC2214_IIC_Start();
		 FDC2214_IIC_Send_Byte(FDC_Address_R);  
		 FDC2214_IIC_Wait_Ack();
	     
		 Receive_Date[0]=FDC2214_IIC_Read_Byte(1);
		 Receive_Date[1]=FDC2214_IIC_Read_Byte(0);
		 FDC2214_IIC_Stop();	
		 return Receive_Date[0];
}

//从FDC2214读低8位数据的函数如下：
u8 FDC_read_reg_low(u8 addr)
{
		 FDC2214_IIC_Start();
		 FDC2214_IIC_Send_Byte(FDC_Address_W);   
		 FDC2214_IIC_Wait_Ack();		
		 FDC2214_IIC_Send_Byte(addr);
		 FDC2214_IIC_Wait_Ack();

		 FDC2214_IIC_Start();
		 FDC2214_IIC_Send_Byte(FDC_Address_R);  
		 FDC2214_IIC_Wait_Ack();
		 
		 Receive_Date[0]=FDC2214_IIC_Read_Byte(1);
		 Receive_Date[1]=FDC2214_IIC_Read_Byte(0);
		 FDC2214_IIC_Stop();	
		 return Receive_Date[1];
}

int FDC_CNum_To_PaperNum(u32 CNum)
{
	 static int CNumPolish = 0;
	 CNum = CNum/1000000;
	 if(CNum >= 149.5 && CNum <= 151.5) CNumPolish = 0;
	 if(CNum >= 163.5 && CNum <= 166.5) CNumPolish = 1;
	 if(CNum >= 171.5 && CNum <= 174.0) CNumPolish = 2;
	 if(CNum >= 177.5 && CNum <= 178.5) CNumPolish = 3;
	 if(CNum >= 183.5 && CNum <= 186.0) CNumPolish = 4;
	 if(CNum >= 188.4 && CNum <= 190.4) CNumPolish = 5;
	 if(CNum >= 192.4 && CNum <= 193.9) CNumPolish = 6;
	 if(CNum >= 196.4 && CNum <= 197.6) CNumPolish = 7;
	 if(CNum >= 199.0 && CNum <= 200.3) CNumPolish = 8;
   if(CNum >= 201.8 && CNum <= 203.5) CNumPolish = 9;
	 if(CNum >= 204.9 && CNum <= 206.2) CNumPolish = 10;
		
	 return CNumPolish;

}
