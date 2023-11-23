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
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

#include "key.h"
#include "led.h"
#include "ws2812.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	uint8_t RE_BUFF[10];//Define the IIC receive buffer
	uint8_t TR_BUFF[10];//Define the IIC transmit  buffer
	int pwm=75;//Define duty cycle parameters (initial duty cycle 75%)
	uint8_t Mode=Manu_mode;//Defining the mode of operation(Initial mode is manual)
	uint8_t x1,x2,x3;//Defining random parameters(RGB Randomized Light Effect Code)
	uint8_t power_on=1;//Define power-up flag bits
	int seed=0;//Define random seed values£¬supplied by timer
	int temp;//Define temperature data buffer
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
  MX_GPIO_Init();//LED, key pin initialization
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();//Fan PWM Generator Initialization
  MX_TIM3_Init();//RGB PWM Generator Initialization
  MX_TIM14_Init();//1 millisecond timer
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim14);//Enable Timer Interrupt
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);//Enable Fan pwm channel

	rgb_show(6,T_3);//Set RGB initial light effect (255,255,0)
	
  while (1)
  {
	
		HAL_I2C_Slave_Receive(&hi2c1, RE_BUFF, 2, 50);//Receive IIC commands and data (Command: RE_BUFF[0]; Data:RE_BUFF[1])

		if(RE_BUFF[0]==0x01)//Command received as 0x01: start of IIC communication
		{
			TR_BUFF[0]=RE_BUFF[1];
			HAL_I2C_Slave_Transmit(&hi2c1, TR_BUFF, 1,50);//Return to ready command: 0x00
//			time_count=IIC_OK;
			
			power_on=0;//Waiting for power-up handshake to end
			Mode=Auto_mode;//The IIC handshake data is received and the mode is set to auto mode.
			RE_BUFF[0]=0;
		}
		
		if(RE_BUFF[0]==0x02)//Command received as 0x02: Query the current operating mode
		{
			TR_BUFF[0]=Mode;
			HAL_I2C_Slave_Transmit(&hi2c1, TR_BUFF, 1,50);//Returns the current operating mode
		}
		
		if(RE_BUFF[0]==0x03)//Command received as 0x03:Receive temperature data
		{
			temp=RE_BUFF[1];
			if(Mode==Auto_mode)// If it is currently in auto mode, it receives the temperature data and sets the fan PWM according to the temperature
			{
				if(temp<40)
					pwm=40;
				else if(temp>=40&&temp<50)
					pwm=50;
				else if(temp>=50&&temp<55)
					pwm=75;
				else if(temp>=55&&temp<60)
					pwm=90;
				else if(temp>=60)
					pwm=100;
			}
		}
		
		if(power_on==1)//Handshake data not received, set mode to manual mode
		{
			Mode=Manu_mode;
		}
		
//		else if(power_on==0)
//		{
////			if
//			Mode=Auto_mode;
////			power_on=0;
//		}
		key_scanf();


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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
