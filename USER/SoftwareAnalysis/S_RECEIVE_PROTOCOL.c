/**
 ******************************************************************************
 * @file           : S_RECEIVE_PROTOCOL.c
 * @brief          :
 * @author         : UF4OVER
 * @date           : 2025/10/30
 ******************************************************************************
 * @attention
 *
 *
 * Copyright (c) 2025 UF4.
 * All rights reserved.
 *
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "S_RECEIVE_PROTOCOL.h"
#include "GLOBAL_CONFIG.h"

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

static tlv_parser_t uart_parser;
static tlv_parser_t usb_parser;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief Initialize TLV receiver
 * @param interface Communication interface type (UART or USB)
 */
void FloatReceive_Init(tlv_interface_t interface)
{
    if (interface == TLV_INTERFACE_UART) {
        TLV_InitParser(&uart_parser, TLV_INTERFACE_UART, FloatReceive_FrameCallback);
    } else if (interface == TLV_INTERFACE_USB) {
        TLV_InitParser(&usb_parser, TLV_INTERFACE_USB, FloatReceive_FrameCallback);
    }
}

/**
 * @brief Get UART parser
 */
tlv_parser_t* FloatReceive_GetUARTParser(void)
{
    return &uart_parser;
}

/**
 * @brief Get USB parser
 */
tlv_parser_t* FloatReceive_GetUSBParser(void)
{
    return &usb_parser;
}

/**
 * @brief Send ACK frame
 */
void FloatReceive_SendAck(uint8_t frame_id, tlv_interface_t interface)
{
    uint8_t ack_frame[20];
    uint16_t ack_size;

    TLV_BuildAckFrame(frame_id, ack_frame, &ack_size);

}

/**
 * @brief Send NACK frame
 */
void FloatReceive_SendNack(uint8_t frame_id, tlv_interface_t interface)
{
    uint8_t nack_frame[20];
    uint16_t nack_size;

    TLV_BuildNackFrame(frame_id, nack_frame, &nack_size);

}

/**
 * @brief TLV帧回调——接收到有效帧时调用
 */
void FloatReceive_FrameCallback(uint8_t frame_id, uint8_t *data, uint8_t length, tlv_interface_t interface)
{
    /* Parse TLV entries from data segment */
    tlv_entry_t tlv_entries[10];
    uint8_t tlv_count = TLV_ParseData(data, length, tlv_entries, 10);

    for (uint8_t i = 0; i < tlv_count; i++) {
        switch (tlv_entries[i].type) {
        case INFO_VSET:

        case INFO_ISET:

        case TLV_TYPE_CONTROL_CMD:

        default:
            break;
        }
    }

    FloatReceive_SendAck(frame_id, interface);
}

/* USER CODE END 0 */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Exported functions --------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
