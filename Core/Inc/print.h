#ifndef STM32F4_4SPI_PRINT_H
#define STM32F4_4SPI_PRINT_H

#endif //STM32F4_4SPI_PRINT_H

// Created by 33974 on 2024/12/24.
//  @Project : STM32F4_4SPI
//  @Time    : 2024 - 12-24 14:43
//  @FileName: print.py
//  @Software: Clion 2024
//  @System  : Windows 11 23H2
//  @Author  : 33974
//  @Contact : ${EMAIL}
// -------------------------------
#include "stdio.h"
#include "gpio.h"
#include "usart.h"
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE {
    HAL_UART_Transmit(&huart2, (uint8_t *) &ch, 1, 0xFFFF);//阻塞方式打印,串口1
    return ch;
}