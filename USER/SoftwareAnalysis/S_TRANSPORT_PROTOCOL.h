/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : S_TRANSPORT_PROTOCOL.h
 * @brief          :
 * @author         : UF4OVER
 * @date           : 2025/10/30
 ******************************************************************************
 * @attention
 *
 * Frame Structure:
 * [Frame Header 2B: 0xFF 0xFF]
 * [Frame ID 1B]
 * [Data Length 1B]
 * [Data Segment N bytes: TLV1 + TLV2 + ...]
 * [CRC16 2B]
 * [Frame Tail 2B: 0xED 0xED]
 *
 * Copyright (c) 2025 UF4.
 * All rights reserved.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
//
// Created by 33974 on 2025/10/30.
//

#ifndef STM32F407_LM5175_S_TRANSPORT_PROTOCOL_H
#define STM32F407_LM5175_S_TRANSPORT_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
/* USER CODE BEGIN Includes */

//#include "usart.h"
//
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

/**
 * @brief Send voltage, current, power, and temperature via UART using TLV protocol
 * @param huart UART handle
 * @param voltage Voltage value (V)
 * @param current Current value (A)
 * @param power Power value (W)
 * @param temperature Temperature value (°C)
 * @return Frame size sent, or negative on error
 */
//int TLV_SendMeasurementData(UART_HandleTypeDef *huart, float voltage, float current,
//                            float power, float temperature);

/**
 * @brief Send voltage setpoint via UART using TLV protocol
 * @param huart UART handle
 * @param voltage Voltage setpoint (V)
 * @return Frame size sent, or negative on error
 */
//int TLV_SendVoltageSetpoint(UART_HandleTypeDef *huart, float voltage);

/**
 * @brief Send current setpoint via UART using TLV protocol
 * @param huart UART handle
 * @param current Current setpoint (A)
 * @return Frame size sent, or negative on error
 */
//int TLV_SendCurrentSetpoint(UART_HandleTypeDef *huart, float current);

/**
 * @brief Send control command via UART using TLV protocol
 * @param huart UART handle
 * @param command Control command byte
 * @return Frame size sent, or negative on error
 */
//int TLV_SendControlCommand(UART_HandleTypeDef *huart, uint8_t command);

/**
 * @brief Send voltage, current, power, and temperature via UART DMA using TLV protocol
 * @param huart UART handle
 * @param voltage Voltage value (V)
 * @param current Current value (A)
 * @param power Power value (W)
 * @param temperature Temperature value (°C)
 * @return Frame size sent, or negative on error
// */
//int TLV_SendMeasurementDataDMA(UART_HandleTypeDef *huart, float voltage, float current,
//                               float power, float temperature);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif // STM32F407_LM5175_S_TRANSPORT_PROTOCOL_H
