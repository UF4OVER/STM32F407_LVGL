/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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
#define TFT_LED_Pin GPIO_PIN_4
#define TFT_LED_GPIO_Port GPIOA
#define TFT_SCL_Pin GPIO_PIN_5
#define TFT_SCL_GPIO_Port GPIOA
#define TFT_DC_Pin GPIO_PIN_6
#define TFT_DC_GPIO_Port GPIOA
#define TFT_SDA_Pin GPIO_PIN_7
#define TFT_SDA_GPIO_Port GPIOA
#define TFT_RST_Pin GPIO_PIN_4
#define TFT_RST_GPIO_Port GPIOC
#define TFT_CS_Pin GPIO_PIN_5
#define TFT_CS_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOD

#define FT_RST_Pin GPIO_PIN_4
#define FT GPIOB

#define FT_INT_Pin GPIO_PIN_5
#define FT GPIOB

#define FT_INT_EXTI_IRQn EXTI9_5_IRQn

#define FT_SCL_Pin GPIO_PIN_6
#define FT GPIOB

#define FT_SDA_Pin GPIO_PIN_7
#define FT GPIOB


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */