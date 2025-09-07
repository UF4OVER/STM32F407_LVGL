//
// Created by 33974 on 2025/9/3.
//

#ifndef STM32F4_4SPI_PRINT_H
#define STM32F4_4SPI_PRINT_H

#include "stm32f4xx_hal.h"  // HAL库基础头文件
#include <stdarg.h>         // 用于可变参数函数

// 串口句柄外部声明（需在main.c或其他文件中定义）
extern UART_HandleTypeDef huart1;

// 串口初始化函数
void Print_Init(uint32_t baud_rate);
void Print_Char(char c);
void Print_String(const char *str);

// 格式化打印函数（类似printf）
void Print_Printf(const char *format, ...);

#endif //STM32F4_4SPI_PRINT_H
