/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : H_FLASH_STORAGE.h
 * @brief          : FLASH storage for PID parameters and configuration
 * @author         : UF4OVER
 * @date           : 2025/10/30
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 UF4.
 * All rights reserved.
 *
 * This module provides functions to save and load PID parameters to/from
 * the STM32F4 internal FLASH memory. It uses the last sector of FLASH
 * for parameter storage.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef STM32F407_LM5175_H_FLASH_STORAGE_H
#define STM32F407_LM5175_H_FLASH_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/**
 * @brief PID parameters storage structure
 */
typedef struct {
    float kp;              // Proportional gain
    float ki;              // Integral gain
    float kd;              // Derivative gain
    float vset_default;    // Default voltage setpoint (V)
    float iset_default;    // Default current setpoint (A)
    uint32_t crc;          // CRC32 checksum for validation
} PID_FlashParams_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

// FLASH sector for parameter storage
// Using Sector 11 (last sector) of STM32F407VET6
// Sector 11: 0x080E0000 - 0x080FFFFF (128KB)
#define FLASH_PARAM_SECTOR          FLASH_SECTOR_11
#define FLASH_PARAM_ADDRESS         0x080E0000

// Magic number to identify valid parameter data
#define FLASH_PARAM_MAGIC           0x50494441  // "PIDA" in hex

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/**
 * @brief Initialize FLASH storage module
 */
void FLASH_Storage_Init(void);

/**
 * @brief Save PID parameters to FLASH
 * @param params: Pointer to PID parameters structure
 * @return true if save was successful
 */
bool FLASH_Storage_SaveParams(const PID_FlashParams_t *params);

/**
 * @brief Load PID parameters from FLASH
 * @param params: Pointer to PID parameters structure to fill
 * @return true if load was successful and data is valid
 */
bool FLASH_Storage_LoadParams(PID_FlashParams_t *params);

/**
 * @brief Erase parameter storage area
 * @return true if erase was successful
 */
bool FLASH_Storage_EraseParams(void);

/**
 * @brief Check if valid parameters exist in FLASH
 * @return true if valid parameters are stored
 */
bool FLASH_Storage_HasValidParams(void);

/**
 * @brief Get default PID parameters
 * @param params: Pointer to PID parameters structure to fill
 */
void FLASH_Storage_GetDefaults(PID_FlashParams_t *params);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif // STM32F407_LM5175_H_FLASH_STORAGE_H
