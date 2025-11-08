/**
 ******************************************************************************
 * @file           : H_TPS2482.c
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

/* Includes ------------------------------------------------------------------*/
#include "H_TPS2482.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

TpsData tps_data;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

static void TPS2482_WriteReg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t value);
static uint16_t TPS2482_ReadReg(I2C_HandleTypeDef *hi2c, uint8_t reg);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief 初始化 TPS2482
 */
void TPS2482_Init(I2C_HandleTypeDef *hi2c)
{
    // 默认配置寄存器：连续测量模式，默认平均时间（0x4127）
    TPS2482_WriteReg(hi2c, TPS2482_REG_CONFIG, 0x4127);

    // 计算并写入校准寄存器
    uint16_t cal = (uint16_t)(0.00512f / (TPS2482_CURRENT_LSB * TPS2482_RSHUNT));
    TPS2482_WriteReg(hi2c, TPS2482_REG_CALIB, cal);
}

/**
 * @brief 读取电压、电流、功率
 */
void TPS2482_ReadData(I2C_HandleTypeDef *hi2c, TpsData *data)
{
    int16_t rawBus, rawShunt, rawCurrent, rawPower;

    rawShunt   = (int16_t)TPS2482_ReadReg(hi2c, TPS2482_REG_SHUNT_V);
    rawBus     = (int16_t)TPS2482_ReadReg(hi2c, TPS2482_REG_BUS_V);
    rawCurrent = (int16_t)TPS2482_ReadReg(hi2c, TPS2482_REG_CURRENT);
    rawPower   = (int16_t)TPS2482_ReadReg(hi2c, TPS2482_REG_POWER);

    data->shunt_voltage = rawShunt * TPS2482_SHUNT_V_LSB;
    data->Vbus   = rawBus   * TPS2482_BUS_V_LSB;
    data->Current       = rawCurrent * TPS2482_CURRENT_LSB;
    data->Power         = rawPower * (TPS2482_CURRENT_LSB * 25.0f); // 25 为固定比例因子
}

static void TPS2482_WriteReg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t value)
{
    uint8_t buf[3];
    buf[0] = reg;
    buf[1] = (value >> 8) & 0xFF;
    buf[2] = value & 0xFF;
    HAL_I2C_Master_Transmit(hi2c, TPS2482_I2C_ADDR, buf, 3, HAL_MAX_DELAY);
}

static uint16_t TPS2482_ReadReg(I2C_HandleTypeDef *hi2c, uint8_t reg)
{
    uint8_t buf[2];
    HAL_I2C_Master_Transmit(hi2c, TPS2482_I2C_ADDR, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(hi2c, TPS2482_I2C_ADDR, buf, 2, HAL_MAX_DELAY);
    return (buf[0] << 8) | buf[1];
}


/* USER CODE END 0 */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Exported functions --------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
