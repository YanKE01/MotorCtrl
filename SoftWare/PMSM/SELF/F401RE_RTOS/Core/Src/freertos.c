/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "foc.h"
#include "as5600.h"
#include "pid.h"
#include "multi_button.h"
#include "variable.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int temp = 0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
uint32_t defaultTaskBuffer[128];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId heartTaskHandle;
uint32_t heartTaskBuffer[128];
osStaticThreadDef_t heartTaskControlBlock;
osThreadId focTaskHandle;
uint32_t focTaskBuffer[512];
osStaticThreadDef_t focTaskControlBlock;
osThreadId buttonTaskHandle;
uint32_t buttonTaskBuffer[128];
osStaticThreadDef_t buttonTaskControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const *argument);
void HeartTaskEntry(void const *argument);
void focTaskEntry(void const *argument);
void buttonTaskEntry(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityLow, 0, 128, defaultTaskBuffer, &defaultTaskControlBlock);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of heartTask */
  osThreadStaticDef(heartTask, HeartTaskEntry, osPriorityNormal, 0, 128, heartTaskBuffer, &heartTaskControlBlock);
  heartTaskHandle = osThreadCreate(osThread(heartTask), NULL);

  /* definition and creation of focTask */
  osThreadStaticDef(focTask, focTaskEntry, osPriorityHigh, 0, 512, focTaskBuffer, &focTaskControlBlock);
  focTaskHandle = osThreadCreate(osThread(focTask), NULL);

  /* definition and creation of buttonTask */
  osThreadStaticDef(buttonTask, buttonTaskEntry, osPriorityNormal, 0, 128, buttonTaskBuffer, &buttonTaskControlBlock);
  buttonTaskHandle = osThreadCreate(osThread(buttonTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for (;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_HeartTaskEntry */
/**
 * @brief Function implementing the heartTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_HeartTaskEntry */
void HeartTaskEntry(void const *argument)
{
  /* USER CODE BEGIN HeartTaskEntry */
  /* Infinite loop */
  for (;;)
  {
    HAL_GPIO_TogglePin(FLASH_LED_GPIO_Port, FLASH_LED_Pin);
    osDelay(1000);
  }
  /* USER CODE END HeartTaskEntry */
}

/* USER CODE BEGIN Header_focTaskEntry */
/**
 * @brief Function implementing the focTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_focTaskEntry */
void focTaskEntry(void const *argument)
{
  /* USER CODE BEGIN focTaskEntry */
  /* Infinite loop */
  for (;;)
  {

    if (focParameter.isStart)
    {
	  focParameter.angleEl+=0.01f;
      AntiParkOperation(&focParameter.ualpha, &focParameter.ubeta, 0, 3, focParameter.angleEl);
      focParameter.sector = JudgeSector(focParameter.ualpha, focParameter.ubeta);
      SvpwmOperation(&focParameter.tcmp1, &focParameter.tcmp2, &focParameter.tcmp3, focParameter.ualpha, focParameter.ubeta, focParameter.sector, focParameter.udc, focParameter.tpwm);
//      focParameter.velocity = (focParameter.angleMc - focParameter.angleMcPrev) / 0.001f;
//      focParameter.velocityLpf = Lpf(focParameter.velocity);
//      focParameter.angleMcPrev = focParameter.angleMc;
    }

    osDelay(1);
  }
  /* USER CODE END focTaskEntry */
}

/* USER CODE BEGIN Header_buttonTaskEntry */
/**
 * @brief Function implementing the buttonTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_buttonTaskEntry */
void buttonTaskEntry(void const *argument)
{
  /* USER CODE BEGIN buttonTaskEntry */
  /* Infinite loop */
  for (;;)
  {
    button_ticks();
    osDelay(50);
  }
  /* USER CODE END buttonTaskEntry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
