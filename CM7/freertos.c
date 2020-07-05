
// This file is a part of MRNIU/FreeRTOS-PortentaH7 (https://github.com/MRNIU/FreeRTOS-PortentaH7).
//
// freertos.c for MRNIU/FreeRTOS-PortentaH7.

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

osThreadId_t cm7_task_handle;
const osThreadAttr_t cm7_task_attributes = {
    .name = "cm7_task",
    .priority = (osPriority_t) osPriorityHigh,
    .stack_size = 128 * 4
};

void StartM7DefaultTask(void *argument);

void MX_FREERTOS_Init(void);

void MX_FREERTOS_Init(void) {
    cm7_task_handle = osThreadNew(StartM7DefaultTask, NULL, &cm7_task_attributes);
}

void StartM7DefaultTask(void *argument) {
    // HAL_RCCEx_EnableBootCore(RCC_BOOT_C2);
    // GPIO_InitTypeDef GPIO_InitStructure;
    // GPIO_InitStructure.Pin = LED_R_Pin;
    // GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    // GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
    // HAL_GPIO_Init( LED_R_GPIO_Port, &GPIO_InitStructure );
    // HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, 1);
    // /* Infinite loop */
    // while(1) {
    //     HAL_Delay(500);
    //     HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
    // }
}
