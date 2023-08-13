#include "main.h"
#include "iic.h"
#include "FDC2214.h"
#include "STM32OledKey.h"
#include "isr.h"

//��.c�ļ�������FDC2214ͨ�ŵĺ���

u16 C_Data = 0;
u8 Receive_Date[2];

u32 C_CHO_data_final = 0;
//FDC2214��ʼ���ĺ������£�
void FDC_Start(void)  
{    
			FDC_write_reg(0x08,0x8329);  //(CHx_RCOUNT*16)/55M ==9.76ms��,ÿ10ms���ҿ��Զ�һ��ֵ
			FDC_write_reg(0x09,0x8329);
			FDC_write_reg(0x0A,0x8329);	
			FDC_write_reg(0x0B,0x8329);

			FDC_write_reg(0x10,0x000A);  //����4��ͨ����С�ȶ�ʱ��
			FDC_write_reg(0x11,0x000A);
			FDC_write_reg(0x12,0x000A);
			FDC_write_reg(0x13,0x000A);

			FDC_write_reg(0x14,0x1001);  //ʱ�ӳ���1�����ô�����Ƶ����0.01M��8.5M֮��
			FDC_write_reg(0x15,0x1001);
			FDC_write_reg(0x16,0x1001);
			FDC_write_reg(0x17,0x1001);

			FDC_write_reg(0x19,0x0000);  //�������жϱ�־λ
			FDC_write_reg(0x1B,0xC20D);  //ʹ��0,1,2,3ͨ�����Ҵ�������Ϊ10M

			FDC_write_reg(0x1E,0x8000);  //����4��ͨ������������
			FDC_write_reg(0x1F,0x8000);
			FDC_write_reg(0x20,0x8000);
			FDC_write_reg(0x21,0x8000);


			FDC_write_reg(0x1A,0x1401);	//ʹ��FDC2214,��ȡ�ڲ�ʱ��Ϊ�ο�ʱ��
}




//��FDC2214�Ĵ���д�ĺ������£�
//���� FDC_Address_W =0x54
void FDC_write_reg(u8 addr,u16 value)   //addr Ϊ�Ĵ�����ַ��valueΪ��Ҫд��ļĴ������� 
{ 
	   FDC2214_IIC_Start();                    //����START�ź�
	   FDC2214_IIC_Send_Byte(FDC_Address_W);   //���ʹӻ���ַ��д�ź�
	   FDC2214_IIC_Wait_Ack();                 //�ȴ�ACK
	   FDC2214_IIC_Send_Byte(addr);            //������Ҫд��ļĴ�����ַ
	   FDC2214_IIC_Wait_Ack();                 //�ȴ�ACK
	   FDC2214_IIC_Send_Byte(value>>8);        //���͸�8λ����
	   FDC2214_IIC_Wait_Ack();                 //�ȴ�ACK
	   FDC2214_IIC_Send_Byte(value&0xFF);      //���͵�8λ����
	   FDC2214_IIC_Wait_Ack();                 //�ȴ�ACK
     FDC2214_IIC_Stop();                     //����STOP�ź�
	   HAL_Delay(1);
}

//��FDC2214��16λ���ݵĺ������£�
//FDC_Address_W =0x54
//FDC_Address_R =0x55
//Receive_Date[] Ϊ�������ݵ�����
//C_Data Ϊһ��16λ�޷��ŵ�����
u16 FDC_read_reg(u8 addr)
{
	
	
		 FDC2214_IIC_Start();                    //����START�ź�
		 FDC2214_IIC_Send_Byte(FDC_Address_W);   //����д����
		 FDC2214_IIC_Wait_Ack();		
		 FDC2214_IIC_Send_Byte(addr);            //������Ҫ���ļĴ����ĵ�ַ
		 FDC2214_IIC_Wait_Ack();
	
		 FDC2214_IIC_Start();
		 FDC2214_IIC_Send_Byte(FDC_Address_R);  //���Ͷ�����
		 FDC2214_IIC_Wait_Ack();
	     
	   Receive_Date[0]=FDC2214_IIC_Read_Byte(1);  //����8λ
		 Receive_Date[1]=FDC2214_IIC_Read_Byte(0);  //����8λ
		 FDC2214_IIC_Stop();	                    //����STOP�ź�
		 C_Data=(Receive_Date[0]<<8)+ Receive_Date[1];
		 return C_Data;
}

//��FDC2214����8λ���ݵĺ������£�
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

//��FDC2214����8λ���ݵĺ������£�
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
