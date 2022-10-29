/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "obraz.c"

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

uint8_t bufor [6][64][16][8];		//wymiary ekranu z czego jest 16 lini poziomych x2
uint8_t przejsciowy[6][6144];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


//void panel (uint8_t z);


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
  MX_DMA_Init();
  /* USER CODE BEGIN 2 */









  //przejsciowy[0][6144] = sonic[18432];

  for (int g=0,d=48; g<18432; g+=576,d+=192)
  {
	  for (int f=0,k=0; f<6; f++,k+=96)
	  	  {
	  		  for (int z=0; z<96; z++)
	  		  {
	  			  przejsciowy[f][z+d] = sonic[z+k+g];
	  		  }
	  	  }
  }













for (int scena=0; scena<6; scena++)
{
for (int z=0; z<8; z++) {
	for (int m=0; m<16; m++) {
		for (int k=0; k<64; k++) { //tworzymy tablicę od najważniejszych pixeli


			bufor[scena][k][m][z]  =   	( (przejsciowy[scena] [k*3 + m*192 + 0		 ] & (1<<(7-z)) ) <<z ) >> 7 |
										( (przejsciowy[scena] [k*3 + m*192 + 1		 ] & (1<<(7-z)) ) <<z ) >> 6 |
										( (przejsciowy[scena] [k*3 + m*192 + 2		 ] & (1<<(7-z)) ) <<z ) >> 5 |
										( (przejsciowy[scena] [k*3 + m*192 + 0 + 3072] & (1<<(7-z)) ) <<z ) >> 4 |
										( (przejsciowy[scena] [k*3 + m*192 + 1 + 3072] & (1<<(7-z)) ) <<z ) >> 3 |
										( (przejsciowy[scena] [k*3 + m*192 + 2 + 3072] & (1<<(7-z)) ) <<z ) >> 2 ;
		}
	}
}
}



void panel (uint8_t z, uint8_t scena) {
for (uint8_t y=0; y<16; y++) {							//zapala odpowiednią linię na wyświetlaczu w jednym takcie
for (uint8_t g=0; g<64; g++) {							//wysyłanie danych równolegle

		GPIOF->ODR = bufor[scena][g][y][z];					//ustawienie bitów danych w 16-bitowym rejetrz e ODR (output data register)
		GPIOA->BSRR = 0x00000080; 						//ustawieni bitu CKL w 32-bitowym rejestrze BSRR (bit set/reset register)
		GPIOA->BSRR = 0x00800000; 						//usunięcie bitu CKL w 32-bitowym rejestrze BSRR (bit set/reset register)
}
		GPIOA->BSRR = 0x00000020;						//zgaszenie panelu
		GPIOA->BSRR = 0x00000040;						//wysprzęglenie danych na rejestru właściwy
		GPIOD->ODR=y;
		GPIOA->BSRR = 0x00400000;						//zasprzęglenie danych na rejest właściwy
		GPIOA->BSRR = 0x00200000;						//zaświecenie panelu
}
}




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


uint32_t czas = HAL_GetTick();
uint32_t a=0;



  while (1)
  {
	  //    PANEL PINOUT
	  //      R1 -- G1
	  //  	  B1 -- GND
	  //  	  R2 -- G2
	  //  	  B2 -- GND
	  //  	   A -- B
	  //  	   C -- D
	  //  	 CLK -- LAT
	  //  	  OE -- GND
	  panel (0,a);
	  panel (1,a);
	  panel (0,a);
	  panel (2,a);
	  panel (0,a);
	  panel (1,a);
	  panel (0,a);
	  panel (3,a);
	  panel (0,a);
	  panel (1,a);
	  panel (0,a);
	  panel (2,a);
	  panel (0,a);
	  panel (1,a);
	  panel (0,a);
	  panel (4,a);
	  panel (0,a);
	  panel (1,a);
	  panel (0,a);
	  panel (2,a);
	  panel (0,a);
	  panel (1,a);
	  panel (0,a);
	  panel (3,a);
	  panel (0,a);
	  panel (1,a);
	  panel (0,a);
	  panel (2,a);
	  panel (0,a);
	  panel (1,a);
	  panel (0,a);


	   if ((HAL_GetTick() - czas) > 70)
	   {
		   czas = HAL_GetTick();
		   if(a>=5){a=0;}
		   a++;
	   }




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */




/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM11 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM11) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
