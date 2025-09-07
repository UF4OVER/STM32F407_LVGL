#ifndef __FT6336_H
#define __FT6336_H
#include "stm32f4xx_hal.h"

#define CTP_MAX_TOUCH 2

#define FT_RST_OFF    				HAL_GPIO_WritePin(T_SCL_GPIO_Port, T_RST_Pin, GPIO_PIN_RESET);
#define FT_RST_ON    				HAL_GPIO_WritePin(T_SCL_GPIO_Port, T_RST_Pin, GPIO_PIN_SET);

#define FT_INT                  HAL_GPIO_ReadPin(FT, FT_INT_Pin);

#define FT_CMD_WR 				0X70
#define FT_CMD_RD 				0X71

#define FT_DEVIDE_MODE 			0x00
#define FT_REG_NUM_FINGER       0x02

#define FT_TP1_REG 				0X03
#define FT_TP2_REG 				0X09

#define FT_ID_G_CIPHER_MID      0x9F
#define FT_ID_G_CIPHER_LOW      0xA0
#define	FT_ID_G_LIB_VERSION		0xA1
#define FT_ID_G_CIPHER_HIGH     0xA3
#define FT_ID_G_MODE 			0xA4
#define FT_ID_G_FOCALTECH_ID    0xA8
#define FT_ID_G_THGROUP			0x80
#define FT_ID_G_PERIODACTIVE	0x88

uint8_t FT6336_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
void FT6336_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t FT6336_Init(void);
uint8_t FT6336_Scan(void);

#endif