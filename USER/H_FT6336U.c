/**
  ******************************************************************************
  * @file           : H_FT6336U.c
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

/* Includes ------------------------------------------------------------------*/
#include "H_FT6336U.h"
#include <string.h>

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
static I2C_HandleTypeDef *s_ft_i2c = NULL;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Exported functions --------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/* Local helpers */
static inline uint16_t make12(uint8_t high, uint8_t low)
{
    return (uint16_t)(((high & 0x0Fu) << 8) | low);
}

void MX_FT6336_Init(I2C_HandleTypeDef *hi2c)
{
    s_ft_i2c = hi2c;
    uint8_t g_mode = FT_G_MODE_TRIGGER;
    (void)MX_FT6336_Write(FT_REG_G_MODE, &g_mode, 1);
    uint8_t th = 22;
    (void)MX_FT6336_Write(FT_REG_TH_GROUP, &th, 1);
}

uint8_t MX_FT6336_Get_TD_Status(void)
{
    uint8_t v = 0;
    if(MX_FT6336_Read(FT_REG_TD_STATUS, &v, 1) != HAL_OK) return 0;
    return v & 0x0Fu;
}

bool MX_FT6336_Get_Touch1_Position(uint16_t *x, uint16_t *y)
{
    if(!x || !y) return false;
    uint8_t buf[4];
    if(MX_FT6336_Read(FT_REG_P1_XH, buf, 4) != HAL_OK) return false;
    uint16_t tx = make12(buf[0], buf[1]);
    uint16_t ty = make12(buf[2], buf[3]);
    *x = tx;
    *y = ty;
    return true;
}

HAL_StatusTypeDef MX_FT6336_Read(uint8_t reg, uint8_t *buf, uint16_t len)
{
    if(s_ft_i2c == NULL) return HAL_ERROR;
    return HAL_I2C_Mem_Read(s_ft_i2c, (FT6336_I2C_ADDR << 1), reg, I2C_MEMADD_SIZE_8BIT, buf, len, 100);
}

HAL_StatusTypeDef MX_FT6336_Write(uint8_t reg, const uint8_t *data, uint16_t len)
{
    if(s_ft_i2c == NULL) return HAL_ERROR;
    return HAL_I2C_Mem_Write(s_ft_i2c, (FT6336_I2C_ADDR << 1), reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)data, len, 100);
}
