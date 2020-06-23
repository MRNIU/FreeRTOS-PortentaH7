/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_R_Pin GPIO_PIN_5
#define LED_R_GPIO_Port GPIOK
#define GPIO6_Pin GPIO_PIN_10
#define GPIO6_GPIO_Port GPIOG
#define GPIO3_Pin GPIO_PIN_5
#define GPIO3_GPIO_Port GPIOD
#define GPIO2_Pin GPIO_PIN_4
#define GPIO2_GPIO_Port GPIOD
#define VIDEO_ALT_Pin GPIO_PIN_4
#define VIDEO_ALT_GPIO_Port GPIOK
#define RST_ETH_Pin GPIO_PIN_15
#define RST_ETH_GPIO_Port GPIOJ
#define LED_G_Pin GPIO_PIN_6
#define LED_G_GPIO_Port GPIOK
#define VIDEO_CABLE_Pin GPIO_PIN_3
#define VIDEO_CABLE_GPIO_Port GPIOK
#define GPIO4_Pin GPIO_PIN_3
#define GPIO4_GPIO_Port GPIOE
#define LED_B_Pin GPIO_PIN_7
#define LED_B_GPIO_Port GPIOK
#define BT_DEV_WAKE_Pin GPIO_PIN_14
#define BT_DEV_WAKE_GPIO_Port GPIOJ
#define BT_ON_Pin GPIO_PIN_12
#define BT_ON_GPIO_Port GPIOJ
#define GPIO0_Pin GPIO_PIN_13
#define GPIO0_GPIO_Port GPIOC
#define BT_SEL_Pin GPIO_PIN_8
#define BT_SEL_GPIO_Port GPIOI
#define BT_HOST_WAKE_Pin GPIO_PIN_13
#define BT_HOST_WAKE_GPIO_Port GPIOJ
#define U4_RTS_Pin GPIO_PIN_10
#define U4_RTS_GPIO_Port GPIOI
#define CRYPTO_EN_Pin GPIO_PIN_12
#define CRYPTO_EN_GPIO_Port GPIOI
#define U4_CTS_Pin GPIO_PIN_13
#define U4_CTS_GPIO_Port GPIOI
#define LPU_RTS_Pin GPIO_PIN_14
#define LPU_RTS_GPIO_Port GPIOI
#define GPIO5_Pin GPIO_PIN_3
#define GPIO5_GPIO_Port GPIOG
#define VIDEO_EN_Pin GPIO_PIN_2
#define VIDEO_EN_GPIO_Port GPIOK
#define OSCEN_Pin GPIO_PIN_1
#define OSCEN_GPIO_Port GPIOH
#define PMIC_INT_Pin GPIO_PIN_0
#define PMIC_INT_GPIO_Port GPIOK
#define PMIC_STBY_Pin GPIO_PIN_0
#define PMIC_STBY_GPIO_Port GPIOJ
#define OTG_EN_Pin GPIO_PIN_6
#define OTG_EN_GPIO_Port GPIOJ
#define LPU_CTS_Pin GPIO_PIN_15
#define LPU_CTS_GPIO_Port GPIOI
#define WL_ON_Pin GPIO_PIN_1
#define WL_ON_GPIO_Port GPIOJ
#define WL_HOST_WAKE_Pin GPIO_PIN_5
#define WL_HOST_WAKE_GPIO_Port GPIOJ
#define VIDEO_RSTN_Pin GPIO_PIN_3
#define VIDEO_RSTN_GPIO_Port GPIOJ
#define RST_USB_Pin GPIO_PIN_4
#define RST_USB_GPIO_Port GPIOJ
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
