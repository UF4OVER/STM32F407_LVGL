/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : S_TLV_PROTOCOL.h
 * @brief          :
 * @author         : UF4OVER
 * @date           : 2025/10/30
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 UF4.
 * All rights reserved.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef STM32F407_LM5175_S_TLV_PROTOCOL_H
#define STM32F407_LM5175_S_TLV_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stdint.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* Frame header and tail constants */
#define TLV_FRAME_HEADER_0      0xF0
#define TLV_FRAME_HEADER_1      0x0F
#define TLV_FRAME_TAIL_0        0xE0
#define TLV_FRAME_TAIL_1        0x0D

/* Frame structure sizes */
#define TLV_HEADER_SIZE         2   /* 0xF0 0x0F */
#define TLV_FRAME_ID_SIZE       1   /* Frame ID */
#define TLV_DATA_LEN_SIZE       1   /* Data length */
#define TLV_CRC_SIZE            2   /* CRC16 */
#define TLV_TAIL_SIZE           2   /* 0xE0 0x0D */
#define TLV_OVERHEAD_SIZE       (TLV_HEADER_SIZE + TLV_FRAME_ID_SIZE + TLV_DATA_LEN_SIZE + TLV_CRC_SIZE + TLV_TAIL_SIZE)

/* Maximum frame sizes */
#define TLV_MAX_DATA_LENGTH     240 /* Maximum TLV data segment length */
#define TLV_MAX_FRAME_SIZE      (TLV_OVERHEAD_SIZE + TLV_MAX_DATA_LENGTH)

/* TLV Type definitions */

#define TLV_TYPE_CONTROL_CMD    0x10  /* 1 byte command */
#define TLV_TYPE_INTEGER        0x20  /* int32 */
#define TLV_TYPE_STRING         0x30  /* UTF-8 text */
#define TLV_TYPE_ACK            0x06  /* ACK response */
#define TLV_TYPE_NACK           0x15  /* NACK response */

/* Control commands (for TLV_TYPE_CONTROL_CMD) */
#define TLV_CMD_OUTPUT_ON       0x01  /* Turn output ON */
#define TLV_CMD_OUTPUT_OFF      0x02  /* Turn output OFF */
#define TLV_CMD_MODE_CC         0x03  /* Switch to CC mode */
#define TLV_CMD_MODE_CV         0x04  /* Switch to CV mode */
#define TLV_CMD_ENTER_UART      0xAA  /* Enter UART mode */
#define TLV_CMD_EXIT_UART       0x55  /* Exit UART mode */
#define TLV_CMD_ENTER_USB       0xBB  /* Enter USB mode */
#define TLV_CMD_EXIT_USB        0x66  /* Exit USB mode */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* Parser states */
typedef enum {
    TLV_STATE_HEADER_0 = 0,
    TLV_STATE_HEADER_1,
    TLV_STATE_FRAME_ID,
    TLV_STATE_DATA_LEN,
    TLV_STATE_DATA,
    TLV_STATE_CRC_LOW,
    TLV_STATE_CRC_HIGH,
    TLV_STATE_TAIL_0,
    TLV_STATE_TAIL_1
} tlv_parser_state_t;

/* Communication interface type */
typedef enum {
    TLV_INTERFACE_UART = 0,
    TLV_INTERFACE_USB = 1
} tlv_interface_t;

/* TLV entry structure */
typedef struct {
    uint8_t type;           /* TLV type */
    uint8_t length;         /* TLV value length */
    uint8_t value[32];      /* TLV value (max 32 bytes per TLV) */
} tlv_entry_t;

/* Frame parser context */
typedef struct {
    tlv_parser_state_t state;
    uint8_t frame_id;
    uint8_t data_length;
    uint8_t data_buffer[TLV_MAX_DATA_LENGTH];
    uint16_t data_index;
    uint16_t crc_received;
    uint16_t crc_calculated;
    tlv_interface_t interface;

    /* Callback for received frame */
    void (*frame_callback)(uint8_t frame_id, uint8_t *data, uint8_t length, tlv_interface_t interface);
} tlv_parser_t;


/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/**
 * @brief Calculate CRC16-CCITT
 * @param data Pointer to data buffer
 * @param length Length of data
 * @return CRC16 value
 */
uint16_t TLV_CalculateCRC16(const uint8_t *data, uint16_t length);

/**
 * @brief Initialize TLV parser
 * @param parser Pointer to parser structure
 * @param interface Communication interface (UART or USB)
 * @param callback Callback function for received frames
 */
void TLV_InitParser(tlv_parser_t *parser, tlv_interface_t interface,
                    void (*callback)(uint8_t frame_id, uint8_t *data, uint8_t length, tlv_interface_t interface));

/**
 * @brief Process a single byte through the parser
 * @param parser Pointer to parser structure
 * @param byte Received byte
 */
void TLV_ProcessByte(tlv_parser_t *parser, uint8_t byte);

/**
 * @brief Build a TLV frame with multiple TLV entries
 * @param frame_id Frame ID for matching ACK
 * @param tlv_entries Array of TLV entries
 * @param tlv_count Number of TLV entries
 * @param output_buffer Output buffer for frame
 * @param output_size Pointer to store output frame size
 * @return true if successful, false if buffer overflow
 */
bool TLV_BuildFrame(uint8_t frame_id, const tlv_entry_t *tlv_entries, uint8_t tlv_count,
                    uint8_t *output_buffer, uint16_t *output_size);

/**
 * @brief Build an ACK frame
 * @param frame_id Frame ID to acknowledge
 * @param output_buffer Output buffer for ACK frame
 * @param output_size Pointer to store output frame size
 */
void TLV_BuildAckFrame(uint8_t frame_id, uint8_t *output_buffer, uint16_t *output_size);

/**
 * @brief Build a NACK frame
 * @param frame_id Frame ID to negative acknowledge
 * @param output_buffer Output buffer for NACK frame
 * @param output_size Pointer to store output frame size
 */
void TLV_BuildNackFrame(uint8_t frame_id, uint8_t *output_buffer, uint16_t *output_size);

/**
 * @brief Parse TLV data segment into individual TLV entries
 * @param data_buffer TLV data segment
 * @param data_length Length of data segment
 * @param tlv_entries Output array for parsed TLV entries
 * @param max_entries Maximum number of entries to parse
 * @return Number of TLV entries parsed
 */
uint8_t TLV_ParseData(const uint8_t *data_buffer, uint8_t data_length,
                      tlv_entry_t *tlv_entries, uint8_t max_entries);

/**
 * @brief Create a voltage TLV entry (scaled ×10000)
 * @param voltage Voltage value (float)
 * @param entry Pointer to TLV entry structure
 */
void TLV_CreateVoltageEntry(float voltage, tlv_entry_t *entry);

/**
 * @brief Create a current TLV entry (scaled ×10000)
 * @param current Current value (float)
 * @param entry Pointer to TLV entry structure
 */
void TLV_CreateCurrentEntry(float current, tlv_entry_t *entry);

/**
 * @brief Create a power TLV entry (scaled ×10000)
 * @param power Power value (float)
 * @param entry Pointer to TLV entry structure
 */
void TLV_CreatePowerEntry(float power, tlv_entry_t *entry);

/**
 * @brief Create a temperature TLV entry (scaled ×10000)
 * @param temperature Temperature value (float)
 * @param entry Pointer to TLV entry structure
 */
void TLV_CreateTemperatureEntry(float temperature, tlv_entry_t *entry);

/**
 * @brief Create a control command TLV entry
 * @param command Command byte
 * @param entry Pointer to TLV entry structure
 */
void TLV_CreateControlCmdEntry(uint8_t command, tlv_entry_t *entry);

/**
 * @brief Extract float value from int32 TLV (scaled ×10000)
 * @param entry Pointer to TLV entry structure
 * @return Float value
 */
float TLV_ExtractFloatValue(const tlv_entry_t *entry);

/**
 * @brief Extract int32 value from TLV
 * @param entry Pointer to TLV entry structure
 * @return int32 value
 */
int32_t TLV_ExtractInt32Value(const tlv_entry_t *entry);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif // STM32F407_LM5175_S_TLV_PROTOCOL_H
