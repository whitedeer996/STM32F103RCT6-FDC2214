/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "oled_iic.h"
#include "STM32OledKey.h"
#include "Menu.h"
#include "string.h"
#include "iic.h"
#include "FDC2214.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
//	u8 lcd_id[12];
	u16 C_date=0;
	u16 ID=0;
 
	u16 C_CH0_data=0;
	u16 C_CH0_data_low=0;
//  u32 C_CHO_data_final = 0;
	
	u16 C_CH1_data=0;
	u16 C_CH1_data_low=0;
	u32 C_CH1_data_final=0;
	
	u16 C_CH2_data=0;
	u16 C_CH2_data_low=0;
	u32 C_CH2_data_final=0;
	
	u16 C_CH3_data=0;
	u16 C_CH3_data_low=0;
	u32 C_CH3_data_final=0;


	

	
	
	


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM7_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	OledKeyInit(); //OLED、按键CH455、蜂鸣器初始化 
	MainMenu();    //主菜单初始化	
	FDC2214_IIC_Init();//FDC_IIC初始化	
	FDC_Start();       //FDC初始化	
	printf("Success!!!\r\n");
  __HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE); //清除定时器初始化过程中的更新中断标志，避免定时器一启动就进入中断
	HAL_TIM_Base_Start_IT(&htim7);//使能定时器7更新中断并启动定时器		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

			HAL_Delay(100);
			C_date = FDC_read_reg(0x7E);       //读取ID  
			ID =  FDC_read_reg(0x7F);	        //读取ID
			if(C_date!=0xFF00 && ID!=0xFF00)           //显示ID
			{		
//          printf("%d ,%d \r\n",C_date,ID);				
//					OLED_ShowNum(139,350,ID,5,24,0);	
//					OLED_ShowNum(139,380,C_date,5,24,0);
			 }  		 
//       HAL_Delay(100);
			

         
				
					if(C_date==0x5449 && ID==0x3055)    //当为相应ID时才读取寄存器的值
					{				
							//读通道0数值	
						 C_CH0_data = FDC_read_reg(0x00)&0xFFF;
						 C_CH0_data_low = FDC_read_reg(0x01);
						 C_CHO_data_final =((C_CH0_data<<16)+C_CH0_data_low);
							//读通道1数值		
						 HAL_Delay(50);
						 C_CH1_data = FDC_read_reg(0x02)&0xFFF;
						 C_CH1_data_low = FDC_read_reg(0x03);
						 C_CH1_data_final =((C_CH1_data<<16)+C_CH1_data_low);	
						//读通道2数值
						 HAL_Delay(50);
						 C_CH2_data=FDC_read_reg(0x04)&0xFFF;
						 C_CH2_data_low = FDC_read_reg(0x05);
						 C_CH2_data_final =((C_CH2_data<<16)+C_CH2_data_low);
						
							//读通道3数值		 
							HAL_Delay(50);
						 C_CH3_data=FDC_read_reg(0x06)&0xFFF;
						 C_CH3_data_low = FDC_read_reg(0x07);
						 C_CH3_data_final =((C_CH3_data<<16)+C_CH3_data_low);

						 
						//显示相应通道读出来的值			
							OLED_ShowNum(40,0,C_CHO_data_final,10,8);
							OLED_ShowNum(40,1,C_CH1_data_final,9,8);
							OLED_ShowNum(40,2,C_CH2_data_final,9,8);
							OLED_ShowNum(40,3,C_CH3_data_final,9,8);
							
			//          printf("%d \r\n",C_CHO_data_final/1000000);

					 }
			     

						 
		 
    /* USER CODE BEGIN 3 */
  }//while
  /* USER CODE END 3 */
}//main

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void delay_us(__IO unsigned int delay)
{
    int last, curr, val;
    int temp;
    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
              val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){};//循环发送,直到发送完毕   
    USART1->DR = (unsigned char) ch;      
	return ch;
}
#endif 
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
