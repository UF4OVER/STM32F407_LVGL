/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : H_TEMP.h
 * @brief          :
 * @author         : UF4OVER
 * @date           : 2025/10/29
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 UF4.
 * All rights reserved.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
//
// Created by 33974 on 2025/10/29.
//

#ifndef STM32F407_LM5175_H_TEMP_H
#define STM32F407_LM5175_H_TEMP_H

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

#define NTC_BETA 3380.0     // β值
#define NTC_R25 10.0        // 25°C时的标称电阻值(kΩ)
#define NTC_R 10.0          // 串联电阻值(kΩ)
#define NTC_VREF 3.3            // 参考电压(V)
#define ABSOLUTE_ZERO 273.15 // 绝对零度

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

float adcToTemperature(uint32_t adc_value);
float GetTemperature(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif // STM32F407_LM5175_H_TEMP_H
