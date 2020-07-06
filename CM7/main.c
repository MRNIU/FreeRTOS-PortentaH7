
// This file is a part of MRNIU/FreeRTOS-PortentaH7 (https://github.com/MRNIU/FreeRTOS-PortentaH7).
//
// main.c for MRNIU/FreeRTOS-PortentaH7.

#include "main.h"
#include "cmsis_os.h"
#include "dcmi.h"
#include "eth.h"
#include "fdcan.h"
#include "i2c.h"
#include "usart.h"
#include "quadspi.h"
#include "sai.h"
#include "sdmmc.h"
#include "spi.h"
#include "usb_otg.h"
#include "gpio.h"
#include "fmc.h"

void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

int main(void) {
    __HAL_RCC_HSEM_CLK_ENABLE();
    SystemCoreClockUpdate();

    /* Enable I-Cache */
	SCB_EnableICache();
	/* Enable D-Cache */
	SCB_EnableDCache();

    HAL_Init();

    /* Configure the System clock source, PLL Multiplier and Divider factors,
       AHB/APBx prescalers and Flash settings */
    SystemClock_Config();
    SystemCoreClockUpdate();

    MX_GPIO_Init();
    MX_DCMI_Init();
    MX_ETH_Init();
    MX_FDCAN1_Init();
    MX_FMC_Init();
    MX_I2C1_Init();
    MX_I2C3_Init();
    MX_LPUART1_UART_Init();
    MX_UART4_Init();
    MX_UART7_Init();
    MX_USART6_UART_Init();
    MX_QUADSPI_Init();
    MX_SAI1_Init();
    MX_SAI4_Init();
    // MX_SDMMC1_SD_Init();
    MX_SPI2_Init();
    // MX_USB_OTG_FS_HCD_Init();
    // MX_USB_OTG_HS_HCD_Init();

    osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
    MX_FREERTOS_Init();
    /* Start scheduler */
    osKernelStart();
}

void SystemClock_Config(void) {
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

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        Error_Handler();
    }

    HAL_PWREx_EnableUSBVoltageDetector();

    __HAL_RCC_CSI_ENABLE() ;

    __HAL_RCC_SYSCFG_CLK_ENABLE() ;

    HAL_EnableCompensationCell();

    return; // OK
}

void Error_Handler(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = LED_G_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init( LED_G_GPIO_Port, &GPIO_InitStructure );
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 1);
    /* Infinite loop */
    while(1) {
        osDelay(500);
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
    }
    return;
}
