#include "main.h"
#include "Menu.h"
#include "STM32OledKey.h"


static unsigned char cLocationX=0,cLocationY=2;//��¼��һ����ʾ����

void MainMenu(void)
{
	OLED_ShowString(0,0,"Chan_0:",8);
	OLED_ShowString(0,1,"Chan_1:",8);
	OLED_ShowString(0,2,"Chan_2:",8);
	OLED_ShowString(0,3,"Chan_3:",8);
	OLED_ShowString(0,5,"PaperNum:",10);
//  OLED_ShowChar(55,5,'5',10);//��ʾKp
	
//	  OLED_ShowChar(16,2,'K',16);//��ʾKp
//	  OLED_ShowChar(24,3,'p',8);//
//	  OLED_ShowChar(32,3,'=',12);//
//	
//	  OLED_ShowChar(16,4,'K',16);//��ʾKi
//	  OLED_ShowChar(24,5,'i',8);//
//	  OLED_ShowChar(32,5,'=',12);//

//		OLED_ShowChar(16,6,'K',16);//��ʾKd
//	  OLED_ShowChar(24,7,'d',8);//
//	  OLED_ShowChar(32,7,'=',12);//

//	  OLED_ShowCHinese (cLocationX,cLocationY,4); 	//��ʾ�м�仯�Ŀ���
}

//0.96��OLED���ΰ�
//K1 K2 K3 K4 K5 �� �� �� �� ����
// |  |  |  |  |  |  |  |  |  |
//77 6F 67 5F 57 76 66 56 5E 6E 
void DispPic(unsigned char cKeyNum)//��ʾ�����ƶ���ͼ��
{

	static unsigned char cPicIndex = 4;//��״�±꣬4-10ʵ����״��12-18���Ŀ���
	static unsigned char bPicFlag1=0;//��ʾ�������ǹ���	
	static unsigned char bPicFlag2=0;//��ʾʵ�Ļ��ǿ���ͼ��

	#if(OLEDSIZE==0)//0.96��OLED����10���������������򰴼���
	{	
		//0.96��OLED���ΰ�
		//K1 K2 K3 K4 K5 �� �� �� �� ����
		// |  |  |  |  |  |  |  |  |  |
		//77 6F 67 5F 57 76 66 56 5E 6E 
		if(cKeyNum==0x6E)//���򰴼����м䰴��
		{ 
			     if(cLocationX==0&&cLocationY==2)
			      { 

			      }
						
						if(cLocationX==0&&cLocationY==4)
			      {

			      }
						
						if(cLocationX==0&&cLocationY==6)
			      {  
							
			      }			
			 
					 if(cLocationX==100&&cLocationY==2)
						{ 

						}	
							
					if(cLocationX==100&&cLocationY==4)
						{

						}
							
					if(cLocationX==100&&cLocationY==6)
					 { 
					 
					 }
			         						
			(bPicFlag1==0)? (bPicFlag1=1):(bPicFlag1=0);//��¼����ʾʵ�Ļ��ǿ��ģ�0ʵ���ƶ���1���Ĳ���
			if(bPicFlag1==0)
				OLED_ShowCHinese (cLocationX,cLocationY,4);    //ʵ��Բ
			else
				OLED_ShowCHinese (cLocationX,cLocationY,12);    //����Բ
		}
		else
		{		
			OLED_ShowCHinese (cLocationX,cLocationY,20); 	//�����ϴ���ʾ��ͼ��	
		


    switch (cKeyNum)
			{//����4���ж�Ϊ�ı�����ֵ
				case 0x76://��
					if(cLocationX==0)cLocationX=100;
					else cLocationX=0;
					break;
				case 0x56://��
					if(cLocationX==0)cLocationX=100;
					else cLocationX=0;
					break;
				case 0x66://��
					cLocationY = cLocationY - 2;
					break;
				case 0x5E://��
					cLocationY = cLocationY + 2;
					break;
				
				//����Ϊ�ı���״
				case 0x77://K1
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=4;
					break;
				case 0x6F://K2
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=5;			
					break;
				case 0x67://K3
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=6;			
					break;			
				case 0x5F://K4
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=7;			
					break;
				case 0x57://K5
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=8;			
					break;				
				default:;
			}
			
			if(cLocationX>=128)cLocationX=0;//��������
			if(cLocationY<2)cLocationY=6;
			else if(cLocationY>7)cLocationY=2;
			
			if(bPicFlag2==0)
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex); 	//��ʾ����ͼ��	
			else
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex+8); 	//��ʾʵ��ͼ��			
		}	
	}
	#else//1.30��OLED���ΰ壬��12������
	{
		//1.30��OLED���ΰ�
		// 1  2  3  4  5  6  7  8  9  *  0  #
		// |  |  |  |  |  |  |  |  |  |	 | 
		//77 76 75 6F 6E 6D 67 66 65 5F 5E 5D 
		if(cKeyNum==0x6E)//���򰴼����м䰴��
		{
			(bPicFlag1==0)? (bPicFlag1=1):(bPicFlag1=0);
			if(bPicFlag1==0)
				OLED_ShowCHinese (113,0,11);
			else
				OLED_ShowCHinese (113,0,11+8);				
		}
		else
		{		
			OLED_ShowCHinese (cLocationX,cLocationY,20); 	//�����ϴ���ʾ��ͼ��	
		
			switch (cKeyNum)
			{
				case 0x6F://4
					if(cLocationX==0)cLocationX=128;
					cLocationX = cLocationX-4;
					break;
				case 0x6D://6
					cLocationX = cLocationX+4;
					break;
				case 0x76://2
					cLocationY = cLocationY - 1;
					break;
				case 0x66://8
					cLocationY = cLocationY + 1;
					break;
				case 0x77://1
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=4;
					break;
				case 0x75://3
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=5;			
					break;
				case 0x67://7
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=6;			
					break;			
				case 0x65://9
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=7;			
					break;
				case 0x5F://*
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=8;			
					break;	
				case 0x5E://0
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=9;			
					break;	
				case 0x5D://#
					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
//					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
					cPicIndex=10;			
					break;					
				default:;
			}	
		}
			if(cLocationX>=128)cLocationX=0;//��������
			if(cLocationY<2)cLocationY=5;
			else if(cLocationY>5)cLocationY=2;
			
			if(bPicFlag2==0)
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex); 	//��ʾͼ��	
			else
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex+8); 	//��ʾͼ��					
		}			
		
		
	#endif
}

//			switch (cKeyNum)
//			{//����4���ж�Ϊ�ı�����ֵ
//				case 0x76://��
//					if(cLocationX==0)cLocationX=128;  //��ѭ��
//					if(bPicFlag1==0)cLocationX = cLocationX-4;
//					break;
//				case 0x56://��
//					if(bPicFlag1==0)cLocationX = cLocationX+4;        //��ѭ��
//					break;
//				
//				case 0x66://��
//					if(bPicFlag1==0)cLocationY = cLocationY - 2; break;      //��ѭ��
//				  if(bPicFlag1==1 && cLocationX==0 &&cLocationY==2) //KPF =1; //PIDKP(KPF); //pid.kp=pid.kp+0.1;
//				     //OLED_Showdecimal(45,7,pid.kp,2,2,14);
//				     break;
//				  if(bPicFlag1==1 && cLocationX==0 &&cLocationY==4) //pid.ki=pid.ki+0.1;
//				     //OLED_Showdecimal(45,7,pid.ki,2,2,14);
//					    break;
//				  if(bPicFlag1==1 && cLocationX==0 &&cLocationY==6) //pid.kd=pid.kd+0.1;
//             //OLED_Showdecimal(45,7,pid.kd,2,2,14);
//					   break;	
//				
//				case 0x5E://��
//					if(bPicFlag1==0)cLocationY = cLocationY + 2;break ;       //��ѭ��
//					if(bPicFlag1==1 && cLocationX==0 && cLocationY==2) //KPF =2;//PIDKP(KPF);//pid.kp=pid.kp-0.1;
//				    // OLED_Showdecimal(45,7,pid.kp,2,2,14);
//				     break;
//				  if(bPicFlag1==1 && cLocationX==0 && cLocationY==4) //pid.ki=pid.ki-0.1;
//				     //OLED_Showdecimal(45,7,pid.ki,2,2,14);
//					   break;
//				  if(bPicFlag1==1 && cLocationX==0 && cLocationY==6) //pid.kd=pid.kd-0.1;
//             //OLED_Showdecimal(45,7,pid.kd,2,2,14);
//					   break;				
//				
				
//				//����Ϊ�ı���״
//				case 0x77://K1
//					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
//					cPicIndex=4;
//					break;
//				case 0x6F://K2
//					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
//					cPicIndex=5;			
//					break;
//				case 0x67://K3
//					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
//					cPicIndex=6;			
//					break;			
//				case 0x5F://K4
//					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
//					cPicIndex=7;			
//					break;
//				case 0x57://K5
//					(bPicFlag2==0)? (bPicFlag2=1):(bPicFlag2=0);
//					cPicIndex=8;			
//					break;				
//				default:;
//			}	


