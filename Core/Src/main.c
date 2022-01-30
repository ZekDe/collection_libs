/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <ZekDe_defs.h>
#include <ZekDe_funcs.h>
#include "timeout.h"
#include "circularBuffer.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define us_PER_sec 1000000UL
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
timeout_t sBtnTimeout;
circularBuffer_t sSpecialBuffer;

// Scenario Control Vars
static ton_t sTon;
static ton_t sTon1;
static uint8_t bOperation = 0;
static _Bool oStart = false;
static _Bool oStop = false;
static _Bool oStartStop = false;
static _Bool oOut = false;
static _Bool oPistonMove = false;
static _Bool oPistonEndPoint = false;

static uint32_t buffer[5] = {0};

uint32_t systick = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void btnPressed(void);
void btnPressedOnce(void);
uint32_t to_us(uint32_t cyc);

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

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;


  if(eCBInit(&sSpecialBuffer,buffer, 5, sizeof(uint32_t)) == CB_FAILED)
  {
	  // never here
  }

  systick = 0;
  TIMEOUT_SET_INTERVAL(&sBtnTimeout,1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	oStart = LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0) != 0;
	// ignore the start button if it is pressed a few times or in any time
	vSeal(oStart, oStop, &oStartStop);
	oOut = oRisingEdgeDetection(oStartStop);

	// Network 1 - check everything and start the scenario
	MOVE((_Bool)((bOperation == 0) && oOut), bOperation, 1);

	// Network 2 - (S1-S2) Piston Forward
	oPistonMove = (_Bool)(bOperation == 1);
	MOVE(oTON(&sTon, (_Bool)(bOperation == 1), &systick, 3000), bOperation, 2);


	//Network 3 - (S2-S3) Has piston reached end?
	MOVE((_Bool)((bOperation == 2) && oPistonEndPoint), bOperation, 3);

	//Network 4 - END
	MOVE(oTON(&sTon1, (_Bool)(bOperation == 3), &systick,3000), bOperation, 0);

	// Network 5 - Stop the scenario
	MOVE(!oStartStop, bOperation, 0);


	// vTimeoutCheck function control
	if(oStartStop)
		{TIMEOUT_EN(&sBtnTimeout,true);}
		vTimeoutCheck(&sBtnTimeout, &systick, btnPressed);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_5)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(168000000);
  LL_SetSystemCoreClock(168000000);
}

/* USER CODE BEGIN 4 */
void btnPressed(void)
{
	TIMEOUT_EN(&sBtnTimeout, false);
	LL_GPIO_TogglePin(GPIOD, LL_GPIO_PIN_13);
//	CBWrite(&specialBuffer, (uint32_t*)&systick);
//	length = CBlength(&specialBuffer);

}
void btnPressedOnce(void)
{
//	CBRead(&specialBuffer, (uint32_t*)&testVal);
}

uint32_t to_us(uint32_t cyc)
{
	return cyc / (SystemCoreClock / us_PER_sec);
}
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

