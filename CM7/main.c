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
// #include "cmsis_os.h"
// #include "dcmi.h"
// #include "eth.h"
// #include "fdcan.h"
// #include "i2c.h"
// #include "usart.h"
// #include "quadspi.h"
// #include "sai.h"
// #include "sdmmc.h"
// #include "spi.h"
// #include "usb_otg.h"
// #include "gpio.h"
// #include "fmc.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_hsem.h"

#define CFG_HW_STOP_MODE_SEMID                                  4
#define CFG_HW_STOP_MODE_MASK_SEMID                            (1 << CFG_HW_STOP_MODE_SEMID)

void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

int main(void)
{
    __HAL_RCC_HSEM_CLK_ENABLE();
    SystemCoreClockUpdate();
    HAL_Init();

    /* Configure the System clock source, PLL Multiplier and Divider factors,
       AHB/APBx prescalers and Flash settings */
    SystemClock_Config();
    SystemCoreClockUpdate();

    HAL_RCCEx_EnableBootCore(RCC_BOOT_C2);

    /* Check wether CM4 boot in parallel with CM7. If CM4 was gated but CM7 trigger the CM4 boot. No need to wait for synchronization.
       otherwise CM7 should wakeup CM4 when system clocks initialization is done.  */
    if (READ_BIT(SYSCFG->UR1, SYSCFG_UR1_BCM4)) {
        LL_HSEM_1StepLock(HSEM, CFG_HW_STOP_MODE_SEMID);
        /*Release HSEM in order to notify the CPU2(CM4)*/
        LL_HSEM_ReleaseLock(HSEM, CFG_HW_STOP_MODE_SEMID, 0);
    } else {
        LL_RCC_ForceCM4Boot();
    }
    /* wait until CPU2 wakes up from stop mode */
    while (LL_RCC_D2CK_IsReady() == 0);



    // osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
    // MX_FREERTOS_Init();
    /* Start scheduler */
    // osKernelStart();
    while(1){

    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /* Supply configuration update enable */
    HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);
    /* Configure the main internal regulator output voltage */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI48;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 5;   // 5 MHz
    RCC_OscInitStruct.PLL.PLLN = 192; // 960 MHz
    RCC_OscInitStruct.PLL.PLLP = 2;   // PLLCLK = SYSCLK = 480 MHz
    RCC_OscInitStruct.PLL.PLLQ = 116;  // PLL1Q used for FDCAN = 10 MHz
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /* Select PLL as system clock source and configure bus clocks dividers */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
                                  RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_D3PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        Error_Handler();
    }

  #if DEVICE_USBDEVICE
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        Error_Handler();
    }

    HAL_PWREx_EnableUSBVoltageDetector();
  #endif /* DEVICE_USBDEVICE */

    __HAL_RCC_CSI_ENABLE() ;

    __HAL_RCC_SYSCFG_CLK_ENABLE() ;

    HAL_EnableCompensationCell();

    return; // OK
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_GPIOK_CLK_ENABLE();
    GPIO_InitStructure.Pin = GPIO_PIN_7;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init( GPIOK, &GPIO_InitStructure );
    /* Infinite loop */
    while(1) {
        HAL_Delay(500);
        HAL_GPIO_TogglePin(GPIOK, GPIO_PIN_7);
    }
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
