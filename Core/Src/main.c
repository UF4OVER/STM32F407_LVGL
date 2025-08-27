/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "i2c.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_examples.h"

#include "ST7796.h"
#include "FT6336.h"
#include "TOUCH.h"


//#include "lv_port_disp.h"
//#include "lv_examples.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
/* USER CODE END Includes */

volatile uint8_t touchNeedDraw = 0;  // 新增全局标志

void SystemClock_Config(void);

volatile uint8_t touchDetected = 0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == FT_INT_Pin) {
        touchNeedDraw = 1;  // 设置触摸标志
    }
}

int main(void)
{

    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_SPI1_Init();
    MX_SPI2_Init();
    MX_USART2_UART_Init();

    MX_TIM6_Init();
    HAL_TIM_Base_Start_IT(&htim6);
    ST7796S_LcdInit();

    // 初始化触摸屏
    if(TP_Init() != 0) {
        // 初始化失败处理
        LCD_DrawString(0, 0, "TOUCH INIT FAIL", LCD_RED);
        while(1);  // 停止程序
    }

    // 清屏
    LCD_Clear(LCD_BLACK);

    while (1)
    {
        // 检查触摸标志
        if(touchNeedDraw) {
            LCD_DrawString(0, 0, "TOUCH DETECTED", LCD_WHITE);
            // 扫描触摸点
            if(FT6336_Scan()) {
                LCD_DrawString(0, 10, "TOUCH DETECTED", LCD_WHITE);
                // 绘制所有有效触摸点
                for(uint8_t i=0; i<CTP_MAX_TOUCH; i++) {
                    if(tp_dev.sta & (1<<i)) {  // 检查该点是否有效
                        LCD_DrawString(0, 20, "OK", LCD_WHITE);
                        // 绘制半径5像素的红色圆点
                        LCD_DrawPoint(tp_dev.x[i], tp_dev.y[i]);
                    }
                }
            }
            touchNeedDraw = 0;  // 清除标志
        }
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

#pragma clang diagnostic pop