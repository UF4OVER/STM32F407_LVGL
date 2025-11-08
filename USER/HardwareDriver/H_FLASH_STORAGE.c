/**
 ******************************************************************************
 * @file           : H_FLASH_STORAGE.c
 * @brief          : FLASH storage implementation
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

/* Includes ------------------------------------------------------------------*/
#include "H_FLASH_STORAGE.h"
#include "GLOBAL_CONFIG.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/

/**
 * @brief FLASH storage header structure
 */
typedef struct {
    uint32_t magic;            // Magic number for validation
    uint32_t version;          // Version number
    PID_FlashParams_t params;  // PID parameters
} __attribute__((packed)) FLASH_Storage_t;

/* Private define ------------------------------------------------------------*/
#define FLASH_STORAGE_VERSION    1

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static uint32_t calculate_crc32(const uint8_t *data, uint32_t length);
static bool flash_write_data(uint32_t address, const void *data, uint32_t length);
static bool flash_read_data(uint32_t address, void *data, uint32_t length);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief Calculate CRC32 checksum
 * @note Uses software CRC calculation (can be replaced with hardware CRC if available)
 */
static uint32_t calculate_crc32(const uint8_t *data, uint32_t length)
{
    uint32_t crc = 0xFFFFFFFF;
    
    for(uint32_t i = 0; i < length; i++) {
        crc ^= data[i];
        for(uint8_t j = 0; j < 8; j++) {
            if(crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc = crc >> 1;
            }
        }
    }
    
    return ~crc;
}

/**
 * @brief Write data to FLASH
 */
static bool flash_write_data(uint32_t address, const void *data, uint32_t length)
{
    HAL_StatusTypeDef status;
    const uint32_t *pData = (const uint32_t *)data;
    uint32_t words = (length + 3) / 4; // Round up to word boundary
    
    for(uint32_t i = 0; i < words; i++) {
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, 
                                   address + (i * 4), 
                                   pData[i]);
        if(status != HAL_OK) {
            return false;
        }
    }
    
    return true;
}

/**
 * @brief Read data from FLASH
 */
static bool flash_read_data(uint32_t address, void *data, uint32_t length)
{
    memcpy(data, (void *)address, length);
    return true;
}

/* External functions --------------------------------------------------------*/

/**
 * @brief Initialize FLASH storage module
 */
void FLASH_Storage_Init(void)
{
    // Nothing special needed for initialization
    // HAL FLASH is already initialized by HAL_Init()
}

/**
 * @brief Save PID parameters to FLASH
 */
bool FLASH_Storage_SaveParams(const PID_FlashParams_t *params)
{
    if(params == NULL) return false;
    
    HAL_StatusTypeDef status;
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t sectorError = 0;
    
    // Prepare storage structure
    FLASH_Storage_t storage;
    storage.magic = FLASH_PARAM_MAGIC;
    storage.version = FLASH_STORAGE_VERSION;
    storage.params = *params;
    
    // Calculate CRC (excluding the CRC field itself)
    uint32_t crc_length = offsetof(PID_FlashParams_t, crc);
    storage.params.crc = calculate_crc32((const uint8_t *)&storage.params, crc_length);
    
    // Unlock FLASH
    status = HAL_FLASH_Unlock();
    if(status != HAL_OK) {
        return false;
    }
    
    // Erase sector
    eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInit.Sector = FLASH_PARAM_SECTOR;
    eraseInit.NbSectors = 1;
    eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3; // 2.7V to 3.6V
    
    status = HAL_FLASHEx_Erase(&eraseInit, &sectorError);
    if(status != HAL_OK) {
        HAL_FLASH_Lock();
        return false;
    }
    
    // Write data
    bool write_ok = flash_write_data(FLASH_PARAM_ADDRESS, 
                                     &storage, 
                                     sizeof(FLASH_Storage_t));
    
    // Lock FLASH
    HAL_FLASH_Lock();
    
    return write_ok;
}

/**
 * @brief Load PID parameters from FLASH
 */
bool FLASH_Storage_LoadParams(PID_FlashParams_t *params)
{
    if(params == NULL) return false;
    
    FLASH_Storage_t storage;
    
    // Read data from FLASH
    if(!flash_read_data(FLASH_PARAM_ADDRESS, &storage, sizeof(FLASH_Storage_t))) {
        return false;
    }
    
    // Validate magic number
    if(storage.magic != FLASH_PARAM_MAGIC) {
        return false;
    }
    
    // Validate version
    if(storage.version != FLASH_STORAGE_VERSION) {
        return false;
    }
    
    // Validate CRC
    uint32_t crc_length = offsetof(PID_FlashParams_t, crc);
    uint32_t calculated_crc = calculate_crc32((const uint8_t *)&storage.params, crc_length);
    
    if(calculated_crc != storage.params.crc) {
        return false;
    }
    
    // Copy valid parameters
    *params = storage.params;
    
    return true;
}

/**
 * @brief Erase parameter storage area
 */
bool FLASH_Storage_EraseParams(void)
{
    HAL_StatusTypeDef status;
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t sectorError = 0;
    
    // Unlock FLASH
    status = HAL_FLASH_Unlock();
    if(status != HAL_OK) {
        return false;
    }
    
    // Erase sector
    eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInit.Sector = FLASH_PARAM_SECTOR;
    eraseInit.NbSectors = 1;
    eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    
    status = HAL_FLASHEx_Erase(&eraseInit, &sectorError);
    
    // Lock FLASH
    HAL_FLASH_Lock();
    
    return (status == HAL_OK);
}

/**
 * @brief Check if valid parameters exist in FLASH
 */
bool FLASH_Storage_HasValidParams(void)
{
    FLASH_Storage_t storage;
    
    // Read magic number and version
    if(!flash_read_data(FLASH_PARAM_ADDRESS, &storage, sizeof(uint32_t) * 2)) {
        return false;
    }
    
    return (storage.magic == FLASH_PARAM_MAGIC && 
            storage.version == FLASH_STORAGE_VERSION);
}

/**
 * @brief Get default PID parameters
 */
void FLASH_Storage_GetDefaults(PID_FlashParams_t *params)
{
    if(params == NULL) return;
    
    params->kp = START_KP;
    params->ki = START_KI;
    params->kd = START_KD;
    params->vset_default = 5.0f;  // Default 5V
    params->iset_default = 1.0f;  // Default 1A
    params->crc = 0; // Will be calculated when saved
}

/* Exported functions --------------------------------------------------------*/
