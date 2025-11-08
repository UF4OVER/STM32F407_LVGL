#ifndef ST7796_H
#define ST7796_H

#include "main.h"

#define ST7796_SCREEN_HEIGHT  480
#define ST7796_SCREEN_WIDTH 	320

#define HORIZONTAL_IMAGE	    0
#define VERTICAL_IMAGE		    1

//SPI INSTANCE
extern SPI_HandleTypeDef hspi2;
#define LEOPARD_BOARD							  &hspi2


#define LCD_CS_PORT								LCD_CS_GPIO_Port
#define LCD_CS_PIN								LCD_CS_Pin

#define LCD_DC_PORT								LCD_DC_GPIO_Port
#define LCD_DC_PIN								LCD_DC_Pin

#define	LCD_RST_PORT							LCD_RST_GPIO_Port
#define	LCD_RST_PIN								LCD_RST_Pin

#define BURST_MAX_SIZE 	   500

#define BLACK              0x0000
#define NAVY               0x000F
#define DARKGREEN          0x03E0
#define DARKCYAN           0x03EF
#define MAROON             0x7800
#define PURPLE             0x780F
#define OLIVE              0x7BE0
#define LIGHTGREY          0xC618
#define DARKGREY           0x7BEF
#define BLUE               0x001F
#define GREEN              0x07E0
#define CYAN               0x07FF
#define RED                0xF800
#define MAGENTA            0xF81F
#define YELLOW             0xFFE0
#define WHITE              0xFFFF
#define ORANGE             0xFD20
#define GREENYELLOW        0xAFE5
#define PINK               0xF81F

#define SCREEN_VERTICAL_1		0
#define SCREEN_HORIZONTAL_1		1
#define SCREEN_VERTICAL_2		2
#define SCREEN_HORIZONTAL_2		3

void ST7796_SPI_Init(void);
void ST7796_SPI_Send(unsigned char SPI_Data);
void ST7796_Write_Command(uint8_t Command);
void ST7796_Write_Data(uint8_t Data);
void ST7796_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
void ST7796_Reset(void);
void ST7796_Set_Rotation(uint8_t Rotation);
void ST7796_Enable(void);
void ST7796_Init(void);
void ST7796_Fill_Screen(uint16_t Colour);
void ST7796_Draw_Colour(uint16_t Colour);
void ST7796_Draw_Pixel(uint16_t X,uint16_t Y,uint16_t Colour);
void ST7796_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);
void ST7796_Draw_Rectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour);
void ST7796_Draw_Horizontal_Line(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Colour);
void ST7796_Draw_Vertical_Line(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Colour);
void LCD_Send_Data_DMA(uint16_t x, uint16_t y, uint16_t x_end, uint16_t y_end, uint8_t *p);
void DMA_ST7796_Draw_Pixel(uint16_t X,uint16_t Y,uint16_t x_end, uint16_t y_end);
void ST7796_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void ST7796_Draw_Filled_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void ST7796_Draw_Hollow_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour);
void ST7796_Draw_Filled_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour);
void ST7796_Draw_Char(char Character, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);
void ST7796_Draw_Text(const char* Text, uint8_t X, uint8_t Y, uint16_t Colour, uint16_t Size, uint16_t Background_Colour);
void ST7796_Draw_Filled_Rectangle_Size_Text(uint16_t X0, uint16_t Y0, uint16_t Size_X, uint16_t Size_Y, uint16_t Colour);
void ST7796_Draw_Image(const char* Image_Array, uint8_t Orientation);
void ST7796_PushColors(uint16_t *pColors, uint32_t size);

#endif