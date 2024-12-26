// -------------------------------
// Created by 33974 on 2024/12/27.
//  @Project : STM32F4_4SPI
//  @Time    : 2024 - 12-27 00:10
//  @FileName:
//  @Software: Clion 2024
//  @System  : Windows 11 23H2
//  @Author  : 33974
//  @Contact : ${EMAIL}
// -------------------------------

#include "ST7796.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"

#define FT6X36_ADDR 0x38 << 1  // 设备I2C地址（7位地址，需要左移1位）
#define REG_TD_STATUS 0x02     // 触摸状态寄存器
#define SCREEN_WIDTH  LCD_W  // 替换为实际屏幕宽度
#define SCREEN_HEIGHT LCD_H  // 替换为实际屏幕高度

#define FT_RST_L HAL_GPIO_WritePin(FT, FT_RST_Pin, GPIO_PIN_RESET)
#define FT_RST_H HAL_GPIO_WritePin(FT, FT_RST_Pin, GPIO_PIN_SET)
void FT6X36_Init();
void ReadTouchData();
void GetTouchPoint(uint16_t *x, uint16_t *y);