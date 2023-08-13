#ifndef __STM32OLEDKEY_H__
#define __STM32OLEDKEY_H__

#include "OLED_Font.h"
#include "stm32f1xx_hal.h"

#define OLEDSIZE 0 //0-Ϊ0.96��OLED���ΰ壬1Ϊ1.30��OLED���ΰ�
#define OLEDTYPE1106 0//0-OLEDΪSH1106���أ�0-OLEDΪSSD1306���أ�

/***********************************
ģ������
	VCC:3.3V
	SDA:PB9
	SCL:PB8
	INT:PB15
	GND:GND
˵����
	1.�������£������жϣ�ͨ��IIC���ͻذ���ֵ����ͬ������Ӧ��ͬ��ֵ
	2.�ж������Դ��������裬��ɨ�赽�������£���Ϊ�͵�ƽ���ʽӵ��ⲿ�жϣ��½��ش���
	3.�Դ�Ӳ��������ֱ�Ӷ�ȡ��ֵ�жϼ���
	4.OLED���밴������iic�ӿڣ�����������
	5.CH455оƬ����ϵͳ�����е����Ⱥ��߶Ρ��˶�ģʽָ��������ܣ�ģ��û�нӣ���OLED�޹�
	6.OLED��һ����һ�ᰵ������Ӳ�����⣬������
********************************CH455оƬ����*************************************/
// ����ϵͳ��������
#define CH455_BIT_ENABLE	0x01		// ����/�ر�λ
#define CH455_BIT_SLEEP		0x04		// ˯�߿���λ
#define CH455_BIT_7SEG		0x08		// 7�ο���λ
#define CH455_BIT_INTENS1	0x10		// 1������
#define CH455_BIT_INTENS2	0x20		// 2������
#define CH455_BIT_INTENS3	0x30		// 3������
#define CH455_BIT_INTENS4	0x40		// 4������
#define CH455_BIT_INTENS5	0x50		// 5������
#define CH455_BIT_INTENS6	0x60		// 6������
#define CH455_BIT_INTENS7	0x70		// 7������
#define CH455_BIT_INTENS8	0x00		// 8������

#define CH455_SYSOFF	0x00		// �ر���ʾ���رռ���
#define CH455_SYSON		CH455_BIT_ENABLE 	// ������ʾ������
#define CH455_SLEEPOFF	CH455_SYSOFF	// �ر�˯��
#define CH455_SLEEPON	( CH455_SYSOFF | CH455_BIT_SLEEP )	// ����˯��
#define CH455_7SEG_ON	( CH455_SYSON | CH455_BIT_7SEG )	// �����߶�ģʽ
#define CH455_8SEG_ON	( CH455_SYSON | 0x00 )	// �����˶�ģʽ
#define CH455_SYSON_4	( CH455_SYSON | CH455_BIT_INTENS4 )	// ������ʾ�����̡�4������
#define CH455_SYSON_8	( CH455_SYSON | CH455_BIT_INTENS8 )	// ������ʾ�����̡�8������

// ��������������
#define CH455_DIG0		0x68			// �����λ0��ʾ,�����8λ����
#define CH455_DIG1		0x6A			// �����λ1��ʾ,�����8λ����
#define CH455_DIG2		0x6C			// �����λ2��ʾ,�����8λ����
#define CH455_DIG3		0x6E			// �����λ3��ʾ,�����8λ����

// ���������������ֽ�1
#define CH455_GET_KEY	0x4F					// ��ȡ����ֵ

//д�����ֽ�1
#define CH455_WriteCmd 0x48      //д������

// CH455�ӿڶ��壨�Ѿ������㵽��д�����ֽ�1�У�
#define		CH455_I2C_ADDR		0x40			// CH455�ĵ�ַ
#define		CH455_I2C_MASK		0x3E			// CH455�ĸ��ֽ���������

/*****************************OLED����������******************************************/
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness 0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	 

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


/*****************************CH455����**************************************/
void OledKeyInit(void); //OLED��CH455��ʼ������
void CH455_Write(unsigned char cmd);  //CH455д����
unsigned char CH455_ReadKeyCode(void);  //CH455��ȡ����ֵ


/*����ֵ������ͬ������ֵ��һ��������Ӳ����·��ͬ��У׼���ɣ�
����1--> 119  ����2--> 118  ����3--> 117
����4--> 111  ����5--> 110  ����6--> 109
����7--> 103  ����8--> 102  ����9--> 101
����*--> 95   ����0--> 94   ����#--> 93 
*/

/****************************OLED���ƺ���**********************************/
void OLED_Init(void);
void OLED_IIC_Write_Command(unsigned char IIC_Command);
void OLED_IIC_Write_Data(unsigned char IIC_Data);
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);
void fill_picture(unsigned char fill_Data);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Display_On(void);//����ʾ
void OLED_Display_Off(void);//�ر���ʾ
void OLED_Clear(void);//��������
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char size);//��ʾ�ַ�
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size);//��ʾ����
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char size);//��ʾ�ַ���
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no);  //��ʾ����
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]); //��ʾͼƬ
unsigned long oled_pow(unsigned char m,unsigned char n); 
void OLED_Showdecimal(unsigned char x,unsigned char y,float num,unsigned char z_len,unsigned char f_len,unsigned char size2);//��ʾС��
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);//����
void OledKeyBeep( unsigned int time);
	

#endif

