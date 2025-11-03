/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : H_TOUCH.h
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

#ifndef STM32F4_4SPI_H_TOUCH_H
#define STM32F4_4SPI_H_TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
void MX_TOUCH_Init(void);
void MX_TOUCH_Init_With_Rotation(uint8_t rotation);
void MX_TOUCH_Set_Rotation(uint8_t rotation);
uint8_t MX_TOUCH_Get_Status(void);     /* number of points (0..2) */
void MX_TOUCH_Get_Position(uint16_t *x, uint16_t *y); /* first point (mapped to rotation) */
bool MX_TOUCH_Is_Interrupted(void);
void MX_TOUCH_Clear_Interrupt(void);

/* Bare-metal quick test: draws small cross or returns latest coords */
void MX_TOUCH_Baremetal_Test_Tick(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif //STM32F4_4SPI_H_TOUCH_H
