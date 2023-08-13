#include "main.h"
#include "oled_iic.h"
#include "STM32OledKey.h"


/*********************OLED������CH455����������ʼ������*********************************/
void OledKeyInit(void)
{
	OLED_Init(); //��ʼ��OLED
	OLED_Clear();	 //OLED����
	OledKeyBeep(500);	//���������
	CH455_Write(CH455_SYSON_8);//����ģ���ʼ��
//CH455��ʼ����������оƬд��һ�������źż���
}

/****************����������********************/
/*
   ��1��DIG0_DIG3ֱ�ӽ�GND
   ��2�����ĸ�λ��A��д�ߵ�ƽ�����ĸ�����ܶ�Ӧ��A�Σ� A�ζ�Ӧ����SEG0��оƬ��9��
   ��3�������贫���β�ʱ�䣬��λΪms
   ��4����Ϊ��̬ɨ�裬����Ҫ������λ��A��ȫ����һ�ſ���ʵ��ռ�ձȽ���Ϊ1����ʱ�������ſ�������
   ��5���������밴������ͬʱʹ�ã��ڷ��������������Ҫ�ڹط������������¶�CH455��ʼ��
*/
void OledKeyBeep( unsigned int time)
{
   IIC_Start();                //�����ź�
	 IIC_Send_Byte(CH455_DIG3);  //д�ֽ�1,Ѱ��Ҫд�ĵ�ַ��DIG3--DIG0�ĵ�ַ��6E,6C,6A,68
	 IIC_Ack();                  //����Ӧ���ź�
   IIC_Send_Byte(0x01);        //д�ֽ�2,   0000 0001������A�Σ���������
	 IIC_Ack(); 
	 IIC_Stop();
	
	 IIC_Start();                //�����ź�
	 IIC_Send_Byte(CH455_DIG2);  //д�ֽ�1
	 IIC_Ack();                  //����Ӧ���ź�
   IIC_Send_Byte(0x01);       //д�ֽ�2
	 IIC_Ack(); 
	 IIC_Stop();
	
	 IIC_Start();                //�����ź�
	 IIC_Send_Byte(CH455_DIG1);  //д�ֽ�1
	 IIC_Ack();                 //����Ӧ���ź�
   IIC_Send_Byte(0x01);        //д�ֽ�2
	 IIC_Ack(); 
	 IIC_Stop();
	
	 IIC_Start();                   //�����ź�
	 IIC_Send_Byte(CH455_DIG0);  //д�ֽ�1
	 IIC_Ack();                   //����Ӧ���ź�
   IIC_Send_Byte(0x01);         //д�ֽ�2
	 IIC_Ack(); 
	 IIC_Stop();	
	
	 HAL_Delay (time);

///�ط���������/
//   �ڷ����������Ҫ����CH455_Write(CH455_SYSON_8);���¶�CH455оƬ��ʼ��

	 IIC_Start();//�����ź�
	 IIC_Send_Byte(CH455_DIG3);  //д�ֽ�1
	 IIC_Ack();  //����Ӧ���ź�
   IIC_Send_Byte(0x00);//д�ֽ�2
	 IIC_Ack(); 
	 IIC_Stop();
	
	 IIC_Start();//�����ź�
	 IIC_Send_Byte(CH455_DIG2);  //д�ֽ�1
	 IIC_Ack();  //����Ӧ���ź�
   IIC_Send_Byte(0x00);//д�ֽ�2
	 IIC_Ack(); 
	 IIC_Stop();
	
	 IIC_Start();//�����ź�
	 IIC_Send_Byte(CH455_DIG1);  //д�ֽ�1
	 IIC_Ack();  //����Ӧ���ź�
   IIC_Send_Byte(0x00);//д�ֽ�2
	 IIC_Ack(); 
	 IIC_Stop();
	
	IIC_Start();//�����ź�
	  IIC_Send_Byte(CH455_DIG0);  //д�ֽ�1
	 IIC_Ack();  //����Ӧ���ź�
   IIC_Send_Byte(0x00);//д�ֽ�2
	 IIC_Ack(); 
	IIC_Stop();	
   CH455_Write(CH455_SYSON_8);
}
/***************************
CH455д��������
�������cmd������������ֽ�
����ִ�й��̣�1.���������ź�
							2.���͡�д����ֽڣ���01001000B����48H
							3.����Ӧ��1
							4.���;������1���ֽڣ�
							5.����Ӧ��2
							6.����ֹͣ�ź�
***************************/
void CH455_Write(unsigned char cmd)
{
	IIC_Start();//�����ź�
	IIC_Send_Byte(CH455_WriteCmd);  //д������ֽ�1
	IIC_Ack();  //����Ӧ���ź�
	IIC_Send_Byte(cmd);  //д������
	IIC_Ack();  //����Ӧ���ź�
	IIC_Stop(); //ֹͣ�ź�
}

/***************************
CH455���������������������룩
����ִ�й��̣�1.���������ź�
							2.���͡�������ֽ�1���� 01001111B����4FH
							3.����Ӧ��1
							4.��ȡ�ֽ�2�����尴�����룩
							5.����Ӧ��2
							6.����ֹͣ�ź�
***************************/
unsigned char CH455_ReadKeyCode(void)
{
	unsigned char KeyCode;
	IIC_Start();//�����ź�
	IIC_Send_Byte(CH455_GET_KEY);  //�����������ֽ�1
	IIC_Ack();  //����Ӧ���ź�
	KeyCode=IIC_Read_Byte(1); //��ȡ�ֽ�2������Ӧ���ź�
	IIC_Stop(); //ֹͣ�ź�
	
	return KeyCode;
}


/****************************OLED����*****************************************/
//OLEDд����
void OLED_IIC_Write_Command(unsigned char IIC_Command)
{

	IIC_Start();
  IIC_Send_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
  IIC_Send_Byte(0x00);			//write command
	IIC_Wait_Ack();	
  IIC_Send_Byte(IIC_Command); 
	IIC_Wait_Ack();	
  IIC_Stop();
}
//OLEDд����
void OLED_IIC_Write_Data(unsigned char IIC_Data)
{
	IIC_Start();
  IIC_Send_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
  IIC_Send_Byte(0x40);			//write data
	IIC_Wait_Ack();	
  IIC_Send_Byte(IIC_Data);
	IIC_Wait_Ack();	
  IIC_Stop();
}
//OLEDд�ַ����ַ������ݻ������
void OLED_WR_Byte(unsigned char data,unsigned char cmd)
{
	if(cmd)
	{
   OLED_IIC_Write_Data(data);
	}
	else
	{
	 OLED_IIC_Write_Command(data);
	}
}

void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}

//��������
	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	#if(!OLEDTYPE1106)//SSDC1306
	{	
		OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
		OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
	}
	#else//SH1106
	{	
		OLED_WR_Byte((((x+2)&0xf0)>>4)|0x10,OLED_CMD);
		OLED_WR_Byte(((x+2)&0x0f)|0x01,OLED_CMD); 
	}
	#endif
		
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		#if(!OLEDTYPE1106)//SSDC1306
		OLED_WR_Byte (0x02,OLED_CMD);      //������ʾλ�á��е͵�ַ
		#else//SH1106
		OLED_WR_Byte (0x02,OLED_CMD);      //������ʾλ�á��е͵�ַ
		#endif
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(size ==16)
		{
		if(x>Max_Column-1){x=0;y=y+2;}
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
		}
		else {	
		if(x>Max_Column-1){x=0;y=y+1;}
			OLED_Set_Pos(x,y);
			for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
			
		}
}
//m^n����
unsigned long oled_pow(unsigned char m,unsigned char n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}				  


//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size)
{         	
	unsigned char t,temp;
	unsigned char enshow=0;	
	if(size==16)            //F8*16
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size); 
	}
	else                   //F6*12
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+6*t,y,' ',size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+6*t,y,temp+'0',size); 
	}

} 
/**
  * @brief   ��ʾһ���ַ��Ŵ�
  * @param   x : uint8_t ��������� 
  * @param   y : uint8_t ��������� 
  * @param   chr : uint8_t *�ַ���ָ��
  * @param   size : 16��16*16�ַ���������6*8�ַ�
  * @retval  ��
  */
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char size)
{
	unsigned char j=0;
	if(size==16)
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
	else 
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],size);
			x+=6;
		if(x>120){x=0;y+=1;}
			j++;
	}
}
//��ʾ����
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//��ʾС��
//z_lenΪ������ʾλ����f_lenΪС����ʾλ����size2Ϊ�����С
void OLED_Showdecimal(unsigned char x,unsigned char y,float num,unsigned char z_len,unsigned char f_len,unsigned char size2)
{         	
	unsigned char t,temp;
	unsigned char enshow;
	int z_temp,f_temp;      
	z_temp=(int)num;
	//��������
	for(t=0;t<z_len;t++)
	{
		temp=(z_temp/oled_pow(10,z_len-t-1))%10;
		if(enshow==0 && t<(z_len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}
			else
			enshow=1;
		}
		OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
	//С����
	OLED_ShowChar(x+(size2/2)*(z_len),y,'.',size2); 
	
	f_temp=(int)((num-z_temp)*(oled_pow(10,f_len)));
  //С������
	for(t=0;t<f_len;t++)
	{
		temp=(f_temp/oled_pow(10,f_len-t-1))%10;
		OLED_ShowChar(x+(size2/2)*(t+z_len)+5,y,temp+'0',size2); 
	}
}

//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���	
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t)
{
	OLED_Set_Pos(x,y);
	OLED_WR_Byte(t,OLED_DATA);
	
}

//OLED��ʼ������
void OLED_Init(void)
{
//	OLED_IIC_Init();
	HAL_Delay(100);
//RESET THE OLED
 	#if 0
  OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set();
	#endif
					  
  OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	#if(!OLEDTYPE1106)//SSDC1306
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	#else//SH1106
	OLED_WR_Byte(0x00+2,OLED_CMD);//---set low column address
	#endif
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	

}
