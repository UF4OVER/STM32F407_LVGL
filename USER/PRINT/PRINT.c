// Created by 33974 on 2025/9/3.
//

#include "PRINT.h"
#include "main.h"  // 包含HAL库和GPIO定义
#include <stdarg.h>  // 支持可变参数
#include <stdio.h>

// 外部声明的串口句柄（需在main.c中定义）
extern UART_HandleTypeDef huart1;

// 串口初始化函数
void Print_Init(uint32_t baud_rate) {
    // UART参数配置
    huart1.Instance = USART1;
    huart1.Init.BaudRate = baud_rate;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;  // 启用发送和接收
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    // 初始化UART
    HAL_UART_Init(&huart1);
}

// 发送单个字符
void Print_Char(char c) {
    HAL_UART_Transmit(&huart1, (uint8_t*)&c, 1, HAL_MAX_DELAY);
}

// 发送字符串
void Print_String(const char *str) {
    while (*str) {
        Print_Char(*str++);
    }
}

// 格式化打印函数（类似printf）
void Print_Printf(const char *format, ...) {
    char buffer[128];  // 缓冲区
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    Print_String(buffer);
}

