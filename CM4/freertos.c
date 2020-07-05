
// This file is a part of MRNIU/FreeRTOS-PortentaH7 (https://github.com/MRNIU/FreeRTOS-PortentaH7).
//
// freertos.c for MRNIU/FreeRTOS-PortentaH7.

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "stm32h7xx_hal_gpio.h"

osThreadId_t cm4_task_handle;
const osThreadAttr_t cm4_task_attributes = {
  .name = "cm4_task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void);

void MX_FREERTOS_Init(void) {
    cm4_task_handle = osThreadNew(StartDefaultTask, NULL, &cm4_task_attributes);
}

void StartDefaultTask(void *argument) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = LED_B_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(LED_B_GPIO_Port, &GPIO_InitStructure);
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, 1);
    /* Infinite loop */
    while(1) {
        HAL_Delay(1000);
        HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
    }
}
