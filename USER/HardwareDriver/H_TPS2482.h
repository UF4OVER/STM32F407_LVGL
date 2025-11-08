/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : H_TPS2482.h
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

#ifndef STM32F407_LM5175_H_TPS2482_H
#define STM32F407_LM5175_H_TPS2482_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
/* USER CODE BEGIN Includes */

#include "i2c.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef struct {
    float Vbus;   // V
    float Current;       // A
    float Power;         // W
    float shunt_voltage; // V
} TpsData;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* --- I2C 地址设置（A0=A1=GND）--- */
#define TPS2482_I2C_ADDR          (0x40 << 1)

#define TPS2482_REG_CONFIG        0x00
#define TPS2482_REG_SHUNT_V       0x01
#define TPS2482_REG_BUS_V         0x02
#define TPS2482_REG_POWER         0x03
#define TPS2482_REG_CURRENT       0x04
#define TPS2482_REG_CALIB         0x05  // Calibration 寄存器

#define TPS2482_RSHUNT            0.007f        // 采样电阻 0.007Ω
#define TPS2482_CURRENT_LSB       0.00061f      // 610 µA/bit
#define TPS2482_BUS_V_LSB         0.00125f      // 1.25 mV/bit
#define TPS2482_SHUNT_V_LSB       0.0000025f    // 2.5 µV/bit

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

void TPS2482_Init(I2C_HandleTypeDef *hi2c);
void TPS2482_ReadData(I2C_HandleTypeDef *hi2c, TpsData *data);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif // STM32F407_LM5175_H_TPS2482_H
