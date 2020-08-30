#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"

osThreadId_t test_A_handle;
const osThreadAttr_t test_A_attributes = {
    .name = "test_A",
    .stack_size = (uint32_t)128 * 4,
    .priority = (osPriority_t) osPriorityHigh
};

osThreadId_t test_B_handle;
const osThreadAttr_t test_B_attributes = {
    .name = "test_B",
    .stack_size = (uint32_t)128 * 4,
    .priority = (osPriority_t) osPriorityHigh
};

void test_A(void *argument);
void test_B(void *argument);

void test_A(void *argument) {
}

void test_B(void *argument) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = LED_B_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(LED_B_GPIO_Port, &GPIO_InitStructure);
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);
    /* Infinite loop */
    while(1) {
        osDelay(1000);
        HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
    }
}

void setup() {
   // osThreadNew(test_A, NULL, &test_A_attributes);
   osThreadNew(test_B, NULL, &test_B_attributes);
}

void loop() {
}
