/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : GLOBAL_CONFIG.h
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
#ifndef STM32F407_LM5175_GLOBAL_CONFIG_H
#define STM32F407_LM5175_GLOBAL_CONFIG_H

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

#define MAX_VOLTAGE 27.0F
#define MIN_VOLTAGE 1.0F
#define MAX_CURRENT 7.0F
#define MIN_CURRENT 0.05F

#define SHORT_CIRCUIT_VOLTAGE 0.8F

#define OVER_TEMP 40.0F

#define VSET_DAC_CHANNEL DAC_CHANNEL_1
#define ISET_DAC_CHANNEL DAC_CHANNEL_2

#define START_KP 100.0F
#define START_KI 10.0F
#define START_KD 1.0F
#define FREQ_OF_CONTROL 100
// Anti-windup limits
#define INTEGRAL_MIN        (-500.0f)
#define INTEGRAL_MAX        500.0f

// LM5175 circuit parameters for DAC to Vout conversion
#define VREF                0.8f      // Reference voltage (V)
#define R1                  82000.0f  // R1 resistor (Ω) VOUT
#define R2                  3300.0f   // R2 resistor (Ω) GND
#define R3                  10000.0f  // R3 resistor (Ω) VADC
#define DAC_VREF            3.3f      // DAC reference voltage (V)

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* INFO ID  */
typedef enum
{
    INFO_VBUS = 0X01,
    INFO_IBUS = 0X03,
    INFO_PBUS = 0X05,
    INFO_BUS = 0X07,
    INFO_VOUT = 0X11,
    INFO_IOUT = 0X13,
    INFO_POUT = 0X15,
    INFO_OUT = 0X17,
    INFO_VSET = 0X09,
    INFO_ISET = 0X19,
} INFO_ID_t;

typedef enum
{
    SENSOR_FAN = 0X21,
    SENSOR_TPS = 0X22,
    SENSOR_INA = 0X23,
    SENSOR_TEMP = 0X24,
} SENSOR_ID_t;

typedef enum
{
    RAW_DAC1 = 0X31,
    RAW_DAC2 = 0X32,
    RAW_ADC = 0X33,
    RAW_PID1 = 0X34,
    RAW_PID2 = 0X35,
} RAW_ID_t;

typedef enum
{
    DEVICE_NAME = 0XDA,
    DEVICE_UID = 0XDB,
    DEVICE_REV = 0XDC,
    DEVICE_FLASH = 0XDE,
    DEVICE_ESPID = 0XDF,
    DEVICE_ESPFU = 0XFF,
} BOARD_ID_t;

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

#endif // STM32F407_LM5175_GLOBAL_CONFIG_H
