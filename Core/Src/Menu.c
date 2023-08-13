#include "main.h"
#include "Menu.h"
#include "STM32OledKey.h"


static unsigned char cLocationX=0,cLocationY=2;//记录上一次显示坐标

void MainMenu(void)
{
	OLED_ShowString(0,0,"Chan_0:",8);
	OLED_ShowString(0,1,"Chan_1:",8);
	OLED_ShowString(0,2,"Chan_2:",8);
	OLED_ShowString(0,3,"Chan_3:",8);
	OLED_ShowString(0,5,"PaperNum:",10);
//  OLED_ShowChar(55,5,'5',10);//显示Kp
	
//	  OLED_ShowChar(16,2,'K',16);//显示Kp
//	  OLED_ShowChar(24,3,'p',8);//
//	  OLED_ShowChar(32,3,'=',12);//
//	
//	  OLED_ShowChar(16,4,'K',16);//显示Ki
//	  OLED_ShowChar(24,5,'i',8);//
//	  OLED_ShowChar(32,5,'=',12);//

//		OLED_ShowChar(16,6,'K',16);//显示Kd
//	  OLED_ShowChar(24,7,'d',8);//
//	  OLED_ShowChar(32,7,'=',12);//

//	  OLED_ShowCHinese (cLocationX,cLocationY,4); 	//显示中间变化的开关
}

//0.96寸OLED调参板
//K1 K2 K3 K4 K5 左 上 右 下 按下
// |  |  |  |  |  |  |  |  |  |
//77 6F 67 5F 57 76 66 56 5E 6E 
void DispPic(unsigned char cKeyNum)//显示可以移动的图形
{

	static unsigned char cPicIndex = 4;//形状下标，4-10实心形状，12-18空心开关
	static unsigned char bPicFlag1=0;//显示开锁还是关锁	
	static unsigned char bPicFlag2=0;//显示实心还是空心图形

	#if(OLEDSIZE==0)//0.96寸OLED，有10个按键（包括五向按键）
	{	
		//0.96寸OLED调参板
		//K1 K2 K3 K4 K5 左 上 右 下 按下
		// |  |  |  |  |  |  |  |  |  |
		//77 6F 67 5F 57 76 66 56 5E 6E 
		if(cKeyNum==0x6E)//五向按键，中间按下
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
			         						
			(bPicFlag1==0)? (bPicFlag1=1):(bPicFlag1=0);//记录下显示实心还是空心，0实心移动，1空心操作
			if(bPicFlag1==0)
				OLED_ShowCHinese (cLocationX,cLocationY,4);    //实心圆
			else
				OLED_ShowCHinese (cLocationX,cLocationY,12);    //空心圆
		}
		else
		{		
			OLED_ShowCHinese (cLocationX,cLocationY,20); 	//擦除上次显示的图形	
		


    switch (cKeyNum)
			{//以下4个判断为改变坐标值
				case 0x76://左
					if(cLocationX==0)cLocationX=100;
					else cLocationX=0;
					break;
				case 0x56://右
					if(cLocationX==0)cLocationX=100;
					else cLocationX=0;
					break;
				case 0x66://上
					cLocationY = cLocationY - 2;
					break;
				case 0x5E://下
					cLocationY = cLocationY + 2;
					break;
				
				//以下为改变形状
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
			
			if(cLocationX>=128)cLocationX=0;//调整坐标
			if(cLocationY<2)cLocationY=6;
			else if(cLocationY>7)cLocationY=2;
			
			if(bPicFlag2==0)
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex); 	//显示空心图形	
			else
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex+8); 	//显示实心图形			
		}	
	}
	#else//1.30寸OLED调参板，有12个按键
	{
		//1.30寸OLED调参板
		// 1  2  3  4  5  6  7  8  9  *  0  #
		// |  |  |  |  |  |  |  |  |  |	 | 
		//77 76 75 6F 6E 6D 67 66 65 5F 5E 5D 
		if(cKeyNum==0x6E)//五向按键，中间按下
		{
			(bPicFlag1==0)? (bPicFlag1=1):(bPicFlag1=0);
			if(bPicFlag1==0)
				OLED_ShowCHinese (113,0,11);
			else
				OLED_ShowCHinese (113,0,11+8);				
		}
		else
		{		
			OLED_ShowCHinese (cLocationX,cLocationY,20); 	//擦除上次显示的图形	
		
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
			if(cLocationX>=128)cLocationX=0;//调整坐标
			if(cLocationY<2)cLocationY=5;
			else if(cLocationY>5)cLocationY=2;
			
			if(bPicFlag2==0)
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex); 	//显示图形	
			else
				OLED_ShowCHinese (cLocationX,cLocationY,cPicIndex+8); 	//显示图形					
		}			
		
		
	#endif
}

//			switch (cKeyNum)
//			{//以下4个判断为改变坐标值
//				case 0x76://左
//					if(cLocationX==0)cLocationX=128;  //左循环
//					if(bPicFlag1==0)cLocationX = cLocationX-4;
//					break;
//				case 0x56://右
//					if(bPicFlag1==0)cLocationX = cLocationX+4;        //右循环
//					break;
//				
//				case 0x66://上
//					if(bPicFlag1==0)cLocationY = cLocationY - 2; break;      //上循环
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
//				case 0x5E://下
//					if(bPicFlag1==0)cLocationY = cLocationY + 2;break ;       //下循环
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
				
//				//以下为改变形状
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


