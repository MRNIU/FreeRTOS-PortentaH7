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
#include "cmsis_os.h"
#include "i2s.h"
#include "gpio.h"
#include "fmc.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_hsem.h"
#include "stm32h7xx_ll_cortex.h"
#include "Legacy/stm32_hal_legacy.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* HW semaphore Complement ID list defined in hw_conf.h from STM32WB */
/* Index of the semaphore used to manage the entry Stop Mode procedure */
#define CFG_HW_STOP_MODE_SEMID                                  4
#define CFG_HW_STOP_MODE_MASK_SEMID                            (1 << CFG_HW_STOP_MODE_SEMID)

void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

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
    __HAL_RCC_HSEM_CLK_ENABLE();
    __HAL_RCC_FLASH_C2_ALLOCATE();

    /* Check wether CM4 boot in parallel with CM7. If CM4 was gated but CM7 trigger the CM4 boot. No need to wait for synchronization.
     otherwise wait for CM7, which is in charge of sytem clock configuration */
    if (!LL_RCC_IsCM4BootForced()) {
        /* CM4 boots at the same time than CM7. It is necessary to synchronize with CM7, by mean of HSEM, that CM7 finishes its initialization.  */

        /* Activate HSEM notification for Cortex-M4*/
        LL_HSEM_EnableIT_C2IER(HSEM, CFG_HW_STOP_MODE_MASK_SEMID);

        /*
        * Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for
        * Cortex-M7 to perform system initialization (system clock config,
        * external memory configuration.. )
        */

        /* Select the domain Power Down DeepSleep */
        LL_PWR_SetRegulModeDS(LL_PWR_REGU_DSMODE_MAIN);
        /* Keep DSTOP mode when D2 domain enters Deepsleep */
        LL_PWR_CPU_SetD2PowerMode(LL_PWR_CPU_MODE_D2STOP);
        LL_PWR_CPU2_SetD2PowerMode(LL_PWR_CPU2_MODE_D2STOP);
        /* Set SLEEPDEEP bit of Cortex System Control Register */
        LL_LPM_EnableDeepSleep();

        /* Ensure that all instructions done before entering STOP mode */
        __DSB();
        __ISB();
        /* Request Wait For Event */
        __WFE();

        /* Reset SLEEPDEEP bit of Cortex System Control Register,
        * the following LL API Clear SLEEPDEEP bit of Cortex
        * System Control Register
        */
        LL_LPM_EnableSleep();

        /* Clear HSEM flag */
        LL_HSEM_DisableIT_C2IER(HSEM, CFG_HW_STOP_MODE_MASK_SEMID);
        LL_HSEM_ClearFlag_C2ICR(HSEM, CFG_HW_STOP_MODE_MASK_SEMID);
    }
      // Update the SystemCoreClock variable.
      SystemCoreClockUpdate();
      HAL_Init();

  while (1)
  {

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
  while(1){

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
