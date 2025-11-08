/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : S_RECEIVE_PROTOCOL.h
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

#ifndef STM32F407_LM5175_S_RECEIVE_PROTOCOL_H
#define STM32F407_LM5175_S_RECEIVE_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "S_TLV_PROTOCOL.h"
#include "stdint.h"
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#define SYNC0 0xFF
#define SYNC1 0xFF
#define CMD_TYPE_CONTROL 0x00  // 0x00: Control command
#define CMD_TYPE_ACK     0xFF  // 0xFF: Acknowledge

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

typedef tlv_interface_t comm_interface_t;
#define COMM_INTERFACE_UART TLV_INTERFACE_UART
#define COMM_INTERFACE_USB  TLV_INTERFACE_USB

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/**
 * @brief Initialize TLV receiver for a specific interface
 * @param interface Communication interface (UART or USB)
 */
void FloatReceive_Init(tlv_interface_t interface);

/**
 * @brief Get TLV parser for UART interface
 * @return Pointer to UART TLV parser
 */
tlv_parser_t* FloatReceive_GetUARTParser(void);

/**
 * @brief Get TLV parser for USB interface
 * @return Pointer to USB TLV parser
 */
tlv_parser_t* FloatReceive_GetUSBParser(void);

/**
 * @brief Send ACK frame
 * @param frame_id Frame ID to acknowledge
 * @param interface Communication interface
 */
void FloatReceive_SendAck(uint8_t frame_id, tlv_interface_t interface);

/**
 * @brief Send NACK frame
 * @param frame_id Frame ID to negative acknowledge
 * @param interface Communication interface
 */
void FloatReceive_SendNack(uint8_t frame_id, tlv_interface_t interface);

/**
 * @brief TLV frame callback - called when a valid frame is received
 * @param frame_id Frame ID
 * @param data Pointer to TLV data segment
 * @param length Length of data segment
 * @param interface Communication interface
 */
void FloatReceive_FrameCallback(uint8_t frame_id, uint8_t *data, uint8_t length, tlv_interface_t interface);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif // STM32F407_LM5175_S_RECEIVE_PROTOCOL_H
