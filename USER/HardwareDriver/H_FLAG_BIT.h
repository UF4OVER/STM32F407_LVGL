/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : h_FLAG_BIT.h
 * @brief          :
 * @author         : UF4OVER
 * @date           : 2025/10/30
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 UF4.
 * All rights reserved.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef STM32F407_LM5175_H_FLAG_BIT_H
#define STM32F407_LM5175_H_FLAG_BIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
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

#define LED1_ON     HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
#define LED1_OFF    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

#define LED2_ON     HAL_GPIO_WritePin(LED1_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
#define LED2_OFF    HAL_GPIO_WritePin(LED1_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

#define LED3_ON     HAL_GPIO_WritePin(LED1_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
#define LED3_OFF    HAL_GPIO_WritePin(LED1_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);

#define LED4_ON     HAL_GPIO_WritePin(LED1_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
#define LED4_OFF    HAL_GPIO_WritePin(LED1_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);

#define TPS2482_ON     HAL_GPIO_WritePin(TPS_ENA_GPIO_Port, TPS_ENA_Pin, GPIO_PIN_SET);
#define TPS2482_OFF    HAL_GPIO_WritePin(TPS_ENA_GPIO_Port, TPS_ENA_Pin, GPIO_PIN_RESET);

#define FAN_ON     HAL_GPIO_WritePin(FAN_CTRL_GPIO_Port, FAN_CTRL_Pin, GPIO_PIN_SET);
#define FAN_OFF    HAL_GPIO_WritePin(FAN_CTRL_GPIO_Port, FAN_CTRL_Pin, GPIO_PIN_RESET);

#define WIFI_ON     HAL_GPIO_WritePin(WIFI_EN_GPIO_Port, WIFI_EN_Pin, GPIO_PIN_SET);
#define WIFI_OFF    HAL_GPIO_WritePin(WIFI_EN_GPIO_Port, WIFI_EN_Pin, GPIO_PIN_RESET);

#define LED1_TOGGLE  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
#define LED2_TOGGLE  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED2_Pin);
#define LED3_TOGGLE  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED3_Pin);
#define LED4_TOGGLE  HAL_GPIO_TogglePin(LED1_GPIO_Port, LED4_Pin);
#define TPS2482_TOGGLE  HAL_GPIO_TogglePin(TPS_ENA_GPIO_Port, TPS_ENA_Pin);
#define FAN_TOGGLE  HAL_GPIO_TogglePin(FAN_CTRL_GPIO_Port, FAN_CTRL_Pin);
#define WIFI_TOGGLE  HAL_GPIO_TogglePin(WIFI_EN_GPIO_Port, WIFI_EN_Pin);

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif // STM32F407_LM5175_H_FLAG_BIT_H
