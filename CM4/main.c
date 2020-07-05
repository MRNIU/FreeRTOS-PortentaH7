
// This file is a part of MRNIU/FreeRTOS-PortentaH7 (https://github.com/MRNIU/FreeRTOS-PortentaH7).
//
// main.c for MRNIU/FreeRTOS-PortentaH7.

#include "main.h"
#include "cmsis_os.h"
#include "i2s.h"
#include "gpio.h"
#include "fmc.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_hsem.h"
#include "stm32h7xx_ll_cortex.h"
#include "Legacy/stm32_hal_legacy.h"

#define CFG_HW_STOP_MODE_SEMID                                  4
#define CFG_HW_STOP_MODE_MASK_SEMID                            (1 << CFG_HW_STOP_MODE_SEMID)

void MX_FREERTOS_Init(void);

int main(void) {
    __HAL_RCC_HSEM_CLK_ENABLE();

    // Update the SystemCoreClock variable.
    SystemCoreClockUpdate();
    HAL_Init();

    osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
    MX_FREERTOS_Init();
    /* Start scheduler */
    osKernelStart();
}

void Error_Handler(void) {
    while(1) {
    }
}
