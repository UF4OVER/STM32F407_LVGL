/*
 * lcd.h
 *
 *  Created on: Dec 31, 2020
 *      Author: ch
 */

#ifndef LIB_LCD_LCD_H_
#define LIB_LCD_LCD_H_
#include "main.h"
#include "stdlib.h"

extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;

//LCD重要参数集
typedef struct {
	uint16_t width;	 //LCD 宽度
	uint16_t height;	 //LCD 高度
	uint16_t id;		 //LCD ID
	uint8_t dir;		 //横屏还是竖屏控制：0，竖屏；1，横屏。
	uint32_t pixsize;	//每个像素所占字节数
} _lcd_dev;

typedef struct { // Data stored PER GLYPH
	uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
	uint8_t  width, height;    // Bitmap dimensions in pixels
	uint8_t  xAdvance;         // Distance to advance cursor (x axis)
	int8_t   xOffset, yOffset; // Dist from cursor position to UL corner
} GFXglyph;

typedef struct { // Data stored for FONT AS A WHOLE:
	uint8_t  *bitmap;      // Glyph bitmaps, concatenated
	GFXglyph *glyph;       // Glyph array
	uint8_t   first, last; // ASCII extents
	uint8_t   yAdvance;    // Newline distance (y axis)
} GFXfont;

//LCD参数
extern _lcd_dev lcddev; //管理LCD重要参数
//LCD的画笔颜色和背景色
extern uint32_t POINT_COLOR; //默认红色
extern uint32_t BACK_COLOR;	//背景颜色.默认为白色

//LCD MPU保护参数
#define LCD_REGION_NUMBER MPU_REGION_NUMBER0  //LCD使用region0
#define LCD_ADDRESS_START (0xC0000000)		  //LCD区的首地址
#define LCD_REGION_SIZE MPU_REGION_SIZE_256MB //LCD区大小

//画笔颜色
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40 //棕色
#define BRRED 0XFC07 //棕红色
#define GRAY 0X8430	 //灰色
//GUI颜色

#define DARKBLUE 0X01CF	 //深蓝色
#define LIGHTBLUE 0X7D7C //浅蓝色
#define GRAYBLUE 0X5458	 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE 0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE 0X2B12	 //浅棕蓝色(选择条目的反色)

#define LTDC_WIDTH 480
#define LTDC_HEIGHT 480
#define LTDC_PIXSIZE 2
extern uint16_t ltdc_lcd_framebuf[480][480];
//#define LCD_LED(n) (n ? HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET)) //LCD背光PB5

//uint16_t LTDC_PanelID_Read(void);
void LTDC_Switch(uint8_t sw);

void LCD_Init(void);													  //初始化
void LCD_Clear(uint32_t color);											  //清屏
void LCD_Rect_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color);
void LCD_Font(uint16_t x, uint16_t y, const char *text, const GFXfont *p_font, uint8_t size, uint32_t color24);
void LCD_DisplayOn(void);												  //开显示
void LCD_DisplayOff(void);												  //关显示
void LCD_DrawPoint(uint16_t x, uint16_t y);										  //画点
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r);								  //画圆
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);						  //画线
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);					  //画矩形
void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color);				  //填充单色
void LCD_Color_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);		  //填充指定颜色
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode);				  //显示一个字符
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size);				  //显示一个数字
void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode);		  //显示 数字
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p); //显示一个字符串,12/16字体

#endif /* LIB_LCD_LCD_H_ */
