/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ssd1306.h"
//#include "arm_math.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include "stdbool.h"

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
TIM_HandleTypeDef htim2;
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
/* USER CODE BEGIN PV */
int flag,j , alerte;
int a = 0;
uint8_t rx;
char str1[155]={0};
char DATEE [10] = {0}; 
char HEUREE [10] = {0}; 
char LOCASA [10] = {0}; 
int len;
char buffer[100];
int m = 0;
int i;
int Seconde = 0 ;
int Minute = 0 ;
int Heure = 0 ;
char ChronoSecond [5] = {0};
char ChronoMinute [5] = {0};
char ChronoHeure[5] = {0};
bool CHRONOMETRE = false ;
//heart
volatile uint32_t BPM;
char BPMM[3] = {0} ;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C1_Init(void);
static void Chrono(void) ;
static void CalculChrono(void) ;
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
if(huart==&huart2)
{
if(rx == 0x0A)
	flag=1;
str1[a]=rx;
//DATEE[a]=rx;
//HEUREE[a+10]=rx;
if (str1[a]=='$'){
	a=0;
	str1[a]=rx;	
}
if (str1[a]=='£'){
	a=0;
	str1[a]=rx;	
}
a++;

//if (str1[a] == '$'){
//a=0;
//str1[a]=rx;
//}
//else 

}
HAL_UART_Receive_IT(&huart2,&rx,1);
}

/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
if(htim==&htim2)
{
	sprintf(buffer,"%i Wellcome\r\n",i);
	i++;
		len=strlen(buffer);
		HAL_UART_Transmit(&huart2,buffer,len,100);
}
}
*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
uint8_t check;
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
  MX_USART2_UART_Init();
  MX_TIM2_Init();
	MX_I2C1_Init();

  MX_DMA_Init();
  MX_ADC1_Init();
	check = SSD1306_Init();
	SSD1306_GotoXY(10,0);
	SSD1306_Puts("Welcome" , &Font_11x18, 1);
	SSD1306_GotoXY(40,20);
	SSD1306_Puts("To" , &Font_11x18, 1);
	SSD1306_GotoXY(10,40);
	SSD1306_Puts("MediWatch" , &Font_11x18, 1);
	SSD1306_UpdateScreen();
  HAL_Delay(3000);
		SSD1306_Clear() ;
	/* USER CODE BEGIN 2 */
HAL_UART_Receive_IT(&huart2,&rx,1);
HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {				//test bouton 
		
		int Home = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3) ;
		int Left = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5) ;
		int Ent = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10) ;
		int Ret = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11) ;
		
		// fin test bouton

		// test menu 
		
		if (!Home){
		m= m + 1 ;
		HAL_Delay(300);
		}

		
		if (((m>2)||(m<0))&&((m!=10)&&(m!=11)&&(m!=15))){
			m=0;
		}

//		if (m==0){
//				//debut ADC
//			
//		HAL_ADC_Start(&hadc1);
//		//HAL_ADC_PollForConversion(&hadc1,100);
//		BPM = HAL_ADC_GetValue(&hadc1);
//		//HAL_ADC_Stop (&hadc1);
//		//HAL_Delay(500);

//		//Fin ADC
//			
//	sprintf(BPMM , "%.2d" , BPM );
//	SSD1306_GotoXY(0,20);
//	SSD1306_Puts("BPM = ", &Font_11x18, 1);
//	SSD1306_GotoXY(50,20);
//	SSD1306_Puts(BPMM, &Font_11x18, 1);
//	SSD1306_GotoXY(0,20);
//	SSD1306_UpdateScreen();
//	SSD1306_Puts("       ", &Font_11x18, 1);
//	SSD1306_GotoXY(50,20);
//	SSD1306_Puts("       ", &Font_11x18, 1);
//			}
	//debut ADC
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,100);
		BPM = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop (&hadc1);


		//Fin ADC
		
	if (m == 1){
		
	SSD1306_GotoXY(10,15);
	SSD1306_Puts("             " , &Font_11x18, 1);
	SSD1306_GotoXY(0,35);
	SSD1306_Puts("             " , &Font_11x18, 1);
	SSD1306_GotoXY(15,30);
	SSD1306_Puts("             ", &Font_11x18, 1);
		
	SSD1306_GotoXY(15,20);
	SSD1306_Puts("Pulsation ", &Font_11x18, 1);
	SSD1306_GotoXY(15,40);
	SSD1306_Puts("Cardiaque ", &Font_11x18, 1);
	SSD1306_UpdateScreen();
	if (!Ent){
	SSD1306_Clear() ;
		
	sprintf(BPMM , "%.2d" , BPM );
	SSD1306_GotoXY(0,20);
	SSD1306_Puts("BPM =  ", &Font_11x18, 1);
	SSD1306_GotoXY(50,20);
	SSD1306_Puts(BPMM, &Font_11x18, 1);
	SSD1306_GotoXY(0,20);
	SSD1306_UpdateScreen();
	SSD1306_Puts("       ", &Font_11x18, 1);
	SSD1306_GotoXY(50,20);
	SSD1306_Puts("       ", &Font_11x18, 1);
	m=11;}
		}
				
	if (m == 2){
	SSD1306_GotoXY(10,15);
	SSD1306_Puts("             " , &Font_11x18, 1);
	SSD1306_GotoXY(0,35);
	SSD1306_Puts("             " , &Font_11x18, 1);
	SSD1306_GotoXY(15,20);
	SSD1306_Puts("             ", &Font_11x18, 1);
	SSD1306_GotoXY(15,40);
	SSD1306_Puts("             ", &Font_11x18, 1);
	SSD1306_GotoXY(1,30);
	SSD1306_Puts("Chronometre ", &Font_11x18, 1);
	SSD1306_UpdateScreen();
	SSD1306_GotoXY(1,30);
	SSD1306_Puts("            ", &Font_11x18, 1);
	if (!Ent){
		SSD1306_Clear() ;
	m=15;
	}
		}
		// fin

			if(flag==1)
			{

		if (m == 0){
		if (alerte == 1){
			
							
	SSD1306_GotoXY(1,5);
	SSD1306_Puts("                "  , &Font_11x18, 1);
	SSD1306_GotoXY(10,0);
	SSD1306_Puts("           ", &Font_11x18, 1);
	SSD1306_GotoXY(10,15);
	SSD1306_Puts("           " , &Font_11x18, 1);
	SSD1306_GotoXY(0,35);
	SSD1306_Puts("           " , &Font_11x18, 1);
	SSD1306_GotoXY(25,27);
	SSD1306_Puts( "ALERTE" , &Font_11x18, 1);
		}
		else{
	SSD1306_GotoXY(1,5);
	SSD1306_Puts("                "  , &Font_11x18, 1);
	SSD1306_GotoXY(20,30);
	SSD1306_Puts( "           " , &Font_11x18, 1);
	for(j=1;j<11;j++){
	DATEE[j-1] = str1[j] ;
		}	

	for(j=11;j<17;j++){
  HEUREE[j-11] = str1[j] ;
		}
	
		for(j=20;j<30;j++){
  LOCASA[j-20] = str1[j] ;
		}
				
//	
//	SSD1306_GotoXY(10,0);
//	SSD1306_Puts(DATEE, &Font_11x18, 1);
	SSD1306_GotoXY(25,15);
	SSD1306_Puts(HEUREE , &Font_11x18, 1);
	SSD1306_GotoXY(0,35);
	SSD1306_Puts(str1 , &Font_11x18, 1);
		}

	SSD1306_UpdateScreen();

		}
		
		int cop = strcmp(str1, "$ALERTE !!");
		
		if (cop == 0) {
			
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
		}
		else {
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
			alerte = 0 ;
		}

				for(j=0;j<60;j++){
		
			if((str1[j]=='$')  &&  (str1[j+1]=='A')  &&  (str1[j+2]=='L')  &&  (str1[j+3]=='E')  &&  (str1[j+4]=='R')&&  (str1[j+5]=='T')&&  (str1[j+6]=='E')&&  (str1[j+7]==' ')&&  (str1[j+8]=='!')&&  (str1[j+9]=='!') ){
			//HAL_Delay(1000);
			//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			alerte = 1 ;
		}}
//		
//		for(j=0;j<60;j++){
//		
//			if((str1[j]=='l')  &&  (str1[j+1]=='e')  &&  (str1[j+2]=='d')  &&  (str1[j+3]=='o')  &&  (str1[j+4]=='f')  &&  (str1[j+5]=='f') ){
//			//HAL_Delay(1000);
//			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);

//		
//			}}
		a=0;
				flag=0;
			}
			else {
						if (m == 0){
	SSD1306_GotoXY(1,5);
	SSD1306_Puts("              "  , &Font_11x18, 1);
	SSD1306_GotoXY(10,30);
	SSD1306_Puts("              "  , &Font_11x18, 1);
	SSD1306_GotoXY(30,30);
	SSD1306_Puts("              ", &Font_11x18, 1);	
	SSD1306_GotoXY(50,30);
	SSD1306_Puts("              ", &Font_11x18, 1);
	SSD1306_GotoXY(70,30);
	SSD1306_Puts("              ", &Font_11x18, 1);	
	SSD1306_GotoXY(90,30);
	SSD1306_Puts("              ", &Font_11x18, 1);
						
	SSD1306_GotoXY(10,15);
	SSD1306_Puts("Connectez" , &Font_11x18, 1);
	SSD1306_GotoXY(35,35);
	SSD1306_Puts("Vous" , &Font_11x18, 1);
	SSD1306_UpdateScreen();
		}

		}
				
	// debut  CHTONOMETRE
	if (m==15){
			Chrono();
	}
		//fin test menu
		if ((m==15)&&(!Left)){
			CHRONOMETRE = true ;
		}
		else if ((m==15)&&(!Ret)){
			CHRONOMETRE = false ;
			Seconde = 0 ;
			Minute = 0 ;
			Heure = 0 ;
		}
		
		
		//appelle du chrono calcul
			if ( CHRONOMETRE == true ){
				CalculChrono();
			}
		//fin chrono calcul
		// Fin CHRONOMETRE
			
																		
																		
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */

static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8000-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	  /*Configure GPIO pin : PC10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		  /*Configure GPIO pin : PC11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}
/* USER CODE BEGIN 4 */

/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
if(htim==&htim2)
{
//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	sprintf(buffer,"Wellcome\r\n");
		len=strlen(buffer);
		HAL_UART_Transmit(&huart2,buffer,len,100);
}
}
*/
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}




//KHEDMET FAREEES
void CalculChrono(void){
			//seconde
	Seconde += 1 ;
	HAL_Delay (1000);
	//minute
	if (Seconde == 60){
		Minute +=1 ;
		Seconde = 0;
	}
	//heure
		if (Minute == 60){
		Heure +=1 ;
		Minute = 0;
	}
	}

//Debut chrono
void Chrono(void){
	
	SSD1306_GotoXY(1,5);
	SSD1306_Puts("Chronometre"  , &Font_11x18, 1);
// int to string 
sprintf(ChronoSecond , "%.2d" , Seconde );
sprintf(ChronoMinute , "%.2d" , Minute );
sprintf(ChronoHeure , "%.2d" , Heure );
	SSD1306_GotoXY(10,30);
	SSD1306_Puts(ChronoHeure  , &Font_11x18, 1);

	SSD1306_GotoXY(30,30);
	SSD1306_Puts(" : ", &Font_11x18, 1);	

	SSD1306_GotoXY(50,30);
	SSD1306_Puts(ChronoMinute, &Font_11x18, 1);

	SSD1306_GotoXY(70,30);
	SSD1306_Puts(" : ", &Font_11x18, 1);	

	SSD1306_GotoXY(90,30);
	SSD1306_Puts(ChronoSecond, &Font_11x18, 1);
	SSD1306_UpdateScreen();

}

//fin Chrono





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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
