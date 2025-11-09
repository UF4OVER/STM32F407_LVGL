/**
  ******************************************************************************
  * @file           : H_TOUCH.c
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
#include "H_TOUCH.h"
#include "H_FT6336U.h"
#include "H_ST7796.h"
#include "i2c.h"
#include "main.h"
#include <stdio.h>

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
static volatile bool s_touch_irq = false;
static uint16_t s_last_x = 0, s_last_y = 0;
static uint8_t s_last_cnt = 0;
static uint8_t s_rotation = SCREEN_HORIZONTAL_1; // default
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
static void map_coord(uint16_t rx, uint16_t ry, uint16_t *mx, uint16_t *my)
{
    uint16_t x = rx, y = ry;
    switch(s_rotation) {
        case SCREEN_VERTICAL_1:     // 320x480, 原始
            break;
        case SCREEN_HORIZONTAL_1:
            x = ry; // invert X axis after swap
            y = (ST7796_SCREEN_WIDTH - 1) - rx;
            break;
        case SCREEN_VERTICAL_2:
            x = (ST7796_SCREEN_WIDTH-1) - rx;
            y = (ST7796_SCREEN_HEIGHT-1) - ry;
            break;
        case SCREEN_HORIZONTAL_2:
        default:
            x = (ST7796_SCREEN_HEIGHT-1) - ry;
            y = (ST7796_SCREEN_WIDTH-1) - rx;
            break;
    }
    if(mx) *mx = x;
    if(my) *my = y;
}

void MX_TOUCH_Init_With_Rotation(uint8_t rotation)
{
    s_rotation = rotation;
    MX_TOUCH_Init();
}

void MX_TOUCH_Set_Rotation(uint8_t rotation)
{
    s_rotation = rotation;
}

void MX_TOUCH_Init(void)
{
    // Reset FT6336U
    HAL_GPIO_WritePin(FT_RST_GPIO_Port, FT_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(FT_RST_GPIO_Port, FT_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(50);

    // Init controller over I2C
    MX_FT6336_Init(&hi2c1);

    // Clear any pending EXTI on INT pin
    __HAL_GPIO_EXTI_CLEAR_IT(FT_INT_Pin);
}

uint8_t MX_TOUCH_Get_Status(void)
{
    s_last_cnt = MX_FT6336_Get_TD_Status();
    if(s_last_cnt > 0) {
        uint16_t x=0, y=0;
        if(MX_FT6336_Get_Touch1_Position(&x,&y)) {
            s_last_x = x; s_last_y = y; // raw cache
        }
    }
    return s_last_cnt;
}

void MX_TOUCH_Get_Position(uint16_t *x, uint16_t *y)
{
    uint16_t mx=0, my=0;
    map_coord(s_last_x, s_last_y, &mx, &my);
    if(x) *x = mx;
    if(y) *y = my;
}
bool MX_TOUCH_Is_Interrupted(void)
{
    return s_touch_irq;
}

void MX_TOUCH_Clear_Interrupt(void)
{
    s_touch_irq = false;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == FT_INT_Pin) {
        s_touch_irq = true;
    }
}
/* USER CODE END 1 */
