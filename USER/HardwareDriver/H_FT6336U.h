/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : H_FT6336U.h
  * @brief          : 
  * @author         : UF4OVER
  * @date           : 2025/11/2
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 UF4.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef STM32F4_4SPI_H_FT6336U_H
#define STM32F4_4SPI_H_FT6336U_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "i2c.h"
#include "main.h"
#include <stdbool.h>

/* FT6336U I2C 7-bit address */
#define FT6336_I2C_ADDR        (0x38U)

/* FT6336U Registers */
#define FT_REG_DEV_MODE        0x00U
#define FT_REG_GEST_ID         0x01U
#define FT_REG_TD_STATUS       0x02U  /* Number of touch points [3:0] */

#define FT_REG_P1_XH           0x03U
#define FT_REG_P1_XL           0x04U
#define FT_REG_P1_YH           0x05U
#define FT_REG_P1_YL           0x06U

#define FT_REG_P2_XH           0x09U
#define FT_REG_P2_XL           0x0AU
#define FT_REG_P2_YH           0x0BU
#define FT_REG_P2_YL           0x0CU

#define FT_REG_TH_GROUP        0x80U  /* Touch threshold */
#define FT_REG_PERIOD_ACTIVE   0x88U
#define FT_REG_PERIOD_MONITOR  0x89U
#define FT_REG_G_MODE          0xA4U  /* Interrupt mode */

/* G_MODE values */
#define FT_G_MODE_POLLING      0x00U
#define FT_G_MODE_TRIGGER      0x01U  /* One-shot interrupt on new data */
#define FT_G_MODE_PULSE        0x02U

/* Exported API --------------------------------------------------------------*/
void MX_FT6336_Init(I2C_HandleTypeDef *hi2c);
uint8_t MX_FT6336_Get_TD_Status(void);
bool MX_FT6336_Get_Touch1_Position(uint16_t *x, uint16_t *y);

/* Low-level helpers */
HAL_StatusTypeDef MX_FT6336_Read(uint8_t reg, uint8_t *buf, uint16_t len);
HAL_StatusTypeDef MX_FT6336_Write(uint8_t reg, const uint8_t *data, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif //STM32F4_4SPI_H_FT6336U_H
