/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "i2s.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
uint8_t znak;
//uint8_t info_zwrotna[50];
//uint16_t dlugosc_info;

uint8_t flag=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		//tryby servo baza
		if(znak=='a')
		{
			flag=1;
		}
		else if(znak=='b')
		{
			flag=2;
		}
		else if(znak=='c')
		{
			flag=3;
		}

		else if(znak=='d')
		{
			flag=4;
		}

		//tryby servo kolanko
		if(znak=='e')
		{
			flag=5;
		}
		else if(znak=='f')
		{
			flag=6;
		}
		else if(znak=='g')
		{
			flag=7;
		}
		else if(znak=='h')
		{
			flag=8;
		}

		//tryby servo lokiec
		if(znak=='i')
		{
			flag=9;
		}
		else if(znak=='j')
		{
			flag=10;
		}
		else if(znak=='k')
		{
			flag=11;
		}
		else if(znak=='l')
		{
			flag=12;
		}

		//tryby servo przedramie
		if(znak=='m')
		{
			flag=13;
		}
		else if(znak=='n')
		{
			flag=14;
		}
		else if(znak=='o')
		{
			flag=15;
		}
		else if(znak=='p')
		{
			flag=16;
		}

		//tryby servo nadgarstek
		if(znak=='r')
		{
			flag=17;
		}
		else if(znak=='s')
		{
			flag=18;
		}
		else if(znak=='t')
		{
			flag=19;
		}
		else if(znak=='u')
		{
			flag=20;
		}

		//tryby servo palce
		if(znak=='w')//zamkniete
		{
			flag=21;
		}
		else if(znak=='x')//szeroko
		{
			flag=22;
		}
		else if(znak=='y')
		{
			flag=23;
		}
		else if(znak=='z')
		{
			flag=24;
		}

		HAL_UART_Receive_IT(&huart2, &znak, 1);


	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_I2C1_Init();
  MX_I2S2_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_USB_HOST_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart2, &znak, 1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
    //serwo baza
    if(flag==1)//prawo
    {
    	htim1.Instance->CCR1=75;
    	HAL_Delay(1000);
    }

    if(flag==2) //lewo
    {
    	htim1.Instance->CCR1=125;
    	HAL_Delay(1000);

    }

    if(flag==3)//auto
    {
    	htim1.Instance->CCR1=75;
    	HAL_Delay(1000);

    	htim1.Instance->CCR1=125;
    	HAL_Delay(1000);
    }

    if(flag==4)//stop
    {
    	htim1.Instance->CCR1=25;
    	HAL_Delay(1000);
    }


    //serwo kolanko
    if(flag==5)//przod
    {
    	htim1.Instance->CCR2=75;
    	HAL_Delay(1000);
    }

    if(flag==6)//tyl
    {
    	htim1.Instance->CCR2=125;
    	HAL_Delay(1000);
    }

    if(flag==7)//auto
    {
    	htim1.Instance->CCR2=75;
        HAL_Delay(1000);

        htim1.Instance->CCR2=125;
        HAL_Delay(1000);
    }

    if(flag==8)//stop
    {
        htim1.Instance->CCR2=25;
        HAL_Delay(1000);
    }


    //serwo lokiec
    if(flag==9)//tyl
    {
    	htim1.Instance->CCR3=75;
    	HAL_Delay(1000);
    }

    if(flag==10)//przod
    {
    	htim1.Instance->CCR3=125;
    	HAL_Delay(1000);
    }

    if(flag==11)//auto
    {
    	htim1.Instance->CCR3=75;
        HAL_Delay(1000);

        htim1.Instance->CCR3=125;
        HAL_Delay(1000);
    }

    if(flag==12)//stop
    {
        htim1.Instance->CCR3=25;
        HAL_Delay(1000);
    }


    //serwo przedramie
    if(flag==13)//lewo
    {
        htim1.Instance->CCR4=75;
        HAL_Delay(1000);
    }

    if(flag==14)//prawo
    {
    	htim1.Instance->CCR4=125;
    	HAL_Delay(1000);
    }

    if(flag==15)//auto
    {
    	htim1.Instance->CCR4=75;
    	HAL_Delay(1000);

    	htim1.Instance->CCR4=125;
    	HAL_Delay(1000);
    }

    if(flag==16)//stop
    {
    	htim1.Instance->CCR4=25;
    	HAL_Delay(1000);
    }


    //serwo nadgarstek
    if(flag==17)//dol
    {
        htim3.Instance->CCR1=75;
        HAL_Delay(1000);
    }

    if(flag==18)//góra
    {
    	htim3.Instance->CCR1=125;
    	HAL_Delay(1000);
    }

    if(flag==19)//auto
    {
    	htim3.Instance->CCR1=75;
    	HAL_Delay(1000);

    	htim3.Instance->CCR1=125;
    	HAL_Delay(1000);
    }

    if(flag==20)
    {
    	htim3.Instance->CCR1=25;
    	HAL_Delay(1000);
    }


    //serwo palce
    if(flag==21)
    {
        htim3.Instance->CCR2=75;
        HAL_Delay(1000);
    }

    if(flag==22)
    {
       htim3.Instance->CCR2=125;
       HAL_Delay(1000);
    }

    if(flag==23)//auto
    {
    	htim3.Instance->CCR2=75;
        HAL_Delay(1000);

        htim3.Instance->CCR2=125;
        HAL_Delay(1000);
    }

     if(flag==24)
     {
        htim3.Instance->CCR2=25;
        HAL_Delay(1000);
     }

    //demo kodu na slidery
    /* int poczatkowa_pozycja=75;
     * if(servo=='s1')
    {
    	int nowa_pozycja_serva;
    	if(poczatkowa_pozycja<nowa_pozycja_serva)
    	{
    		for(int i=poczatkowa_pozycja; i<=nowa_pozycja_serva;i++)
    		{
    			htim1.Instance->CCR1=i;
    			HAL_Delay(100);
    		}
    	}
    	HAL_Delay(1000);
    			//htim1.Instance->CCR1=poczatkowa_pozycja;
    			//poczatkowa_pozycja++;
    			//HAL_Delay(100);
    		//}
    	if(poczatkowa_pozycja>nowa_pozycja_serva)
    	{
    		for(int i=poczatkowa_pozycja; i>=nowa_pozycja_serva;i--)
    		{
    			htim1.Instance->CCR1=i;
    			HAL_Delay(100);
    		}
    		HAL_Delay(1000);
    	}
    	poczatkowa_pozycja=nowa_pozycja_serva;
    }*/
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 200;
  PeriphClkInitStruct.PLLI2S.PLLI2SM = 5;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		if(znak=='1')
		{
			HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
			sprintf(info_zwrotna, "on\n");
			dlugosc_info=2;
		}
		else if(znak=='2')
		{
			HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
			sprintf(info_zwrotna, "off\n");
			dlugosc_info=3;
		}
		HAL_UART_Receive_IT(&huart2, &znak, 1);
		HAL_UART_Transmit_IT(&huart2, &info_zwrotna, dlugosc_info);
	}
}*/
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
