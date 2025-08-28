//
// Created by 33974 on 2024/12/20.
//

#ifndef STM32F4_4SPI_ST7796_H
#define STM32F4_4SPI_ST7796_H



#include "main.h"
#include "spi.h"
#include "hal/lv_hal.h"


#define LCD_CS_PORT TFT_CS_GPIO_Port
#define LCD_CS_PIN TFT_CS_Pin
#define LCD_RST_PORT TFT_RST_GPIO_Port
#define LCD_RST_PIN TFT_RST_Pin
#define LCD_DC_PORT TFT_DC_GPIO_Port
#define LCD_DC_PIN TFT_DC_Pin

#define LCD_RST_CLR HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_RESET)
#define LCD_RST_SET HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_SET)

#define LCD_CS_CLR HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_RESET)
#define LCD_CS_SET HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_SET)

#define LCD_DC_CLR HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_RESET)
#define LCD_DC_SET HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_SET)

#define LCD_LED_ON HAL_GPIO_WritePin(TFT_LED_GPIO_Port,TFT_LED_Pin,GPIO_PIN_SET)
#define LCD_LED_OFF HAL_GPIO_WritePin(TFT_LED_GPIO_Port,TFT_LED_Pin,GPIO_PIN_RESET)

#define LCD_SPI hspi1 //SPI定义
#define LCD_SPI_DMA hdma_spi1_tx
#define LCD_W 320 //宽度
#define LCD_H 480 //高度
#define LCD_DIRECTION 2 //方向

// Color definitions
#define LCD_BLACK   0x0000
#define LCD_BLUE    0x001F
#define LCD_RED     0xF800
#define LCD_GREEN   0x07E0
#define LCD_CYAN    0x07FF
#define LCD_MAGENTA 0xF81F
#define LCD_YELLOW  0xFFE0
#define LCD_WHITE   0xFFFF
#define LCD_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#define LCD_INVOFF  0x20 //颜色反转
#define LCD_INVON   0x21  //颜色反转

typedef struct {
    uint16_t width;        //液晶屏的宽度
    uint16_t height;    //液晶屏的高度
    uint16_t id;        //液晶屏的ID
    uint8_t wramcmd;    //ST996S写GRAM指令
    uint8_t setxcmd;   //ST996S设置X坐标指令
    uint8_t setycmd;   //ST996S设置Y坐标指令
    uint8_t mode;
    uint8_t xcmd;
    uint8_t ycmd;
    uint8_t calibration;
} ST7796S_LcdSetting;  //液晶屏的一些重要参数，没注释的代表触摸屏的功能

extern ST7796S_LcdSetting LcdSetting;

extern volatile lv_disp_drv_t *g_disp_drv; // 保持与main.c一致


void ST7796S_LcdDirection(uint8_t direction);

void ST7796S_LcdInit(void);

/*清屏*/
void LCD_Clear(uint16_t Color);

void LCD_DrawPoint(uint16_t x, uint16_t y);

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

void LCD_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void LCD_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size);

uint32_t LCD_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor);

void LCD_SetWindows(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1);

void LCD_InvertColors(int invert);

void LCD_SetAddress(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void LCD_PushColors(uint16_t *color, uint32_t size);

void LCD_PushColors_DMA(uint16_t *color, uint32_t size);


#endif //STM32F4_4SPI_ST7796_H