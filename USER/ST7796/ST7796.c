#include "main.h"
#include "stm32f4xx_hal_dma.h"
#include "ST7796.h"
#include "FONT.h"
#include "PRINT.h"

ST7796S_LcdSetting LcdSetting;

void ST7796S_LcdReset() {
    LCD_RST_CLR;
    HAL_Delay(100);
    LCD_RST_SET;
    HAL_Delay(50);
}

/*写命令*/
void ST7796S_LcdWriteCommand(uint8_t command) {
    LCD_CS_CLR;
    LCD_DC_CLR;
    HAL_SPI_Transmit(&LCD_SPI, &command, 1, 5);
    LCD_CS_SET;
}

/*写数据*/
void ST7796S_LcdWriteData(uint8_t data) {
    LCD_CS_CLR;
    LCD_DC_SET;
    HAL_SPI_Transmit(&LCD_SPI, &data, 1, 5);
    LCD_CS_SET;
}

/*向液晶屏特定寄存器写入数据*/
void ST7796S_LcdWriteReg(uint8_t registers, uint16_t data) {
    ST7796S_LcdWriteCommand(registers);
    ST7796S_LcdWriteData(data);
}


/*设置液晶屏的扫描方向
0代表竖屏，然后依次旋转90度
*/
void ST7796S_LcdDirection(uint8_t direction) {
    LcdSetting.setxcmd = 0x2A;
    LcdSetting.setycmd = 0x2B;
    LcdSetting.wramcmd = 0x2C;
    switch (direction) {
        case 0:
            LcdSetting.width = LCD_W;
            LcdSetting.height = LCD_H;
            ST7796S_LcdWriteReg(0x36, (1 << 3) | (1 << 6));
            LcdSetting.mode = 0;
            LcdSetting.xcmd = 0xd0;
            LcdSetting.ycmd = 0x90;
            break;
        case 1:
            LcdSetting.width = LCD_H;
            LcdSetting.height = LCD_W;
            ST7796S_LcdWriteReg(0x36, (1 << 3) | (1 << 5));
            LcdSetting.mode = 1;
            LcdSetting.xcmd = 0x90;
            LcdSetting.ycmd = 0xd0;
            break;
        case 2:
            LcdSetting.width = LCD_W;
            LcdSetting.height = LCD_H;
            ST7796S_LcdWriteReg(0x36, (1 << 3) | (1 << 7));
            LcdSetting.mode = 2;
            LcdSetting.xcmd = 0xd0;
            LcdSetting.ycmd = 0x90;
            break;
        case 3:
            LcdSetting.width = LCD_H;
            LcdSetting.height = LCD_W;
            ST7796S_LcdWriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 6) | (1 << 5));
            LcdSetting.mode = 3;
            LcdSetting.xcmd = 0x90;
            LcdSetting.ycmd = 0xd0;
            break;
        default:
            break;
    }
}

/*准备写入GRAM*/
void LCD_WriteRAM_Prepare(void) {
    ST7796S_LcdWriteCommand(LcdSetting.wramcmd);
}

/*写16位数据*/
void Lcd_WriteData_16Bit(uint16_t Data) {
    uint8_t n_Data1 = Data >> 8;
    uint8_t n_Data2 = Data & 0x00ff;
    uint8_t N_Data[2] = {n_Data1, n_Data2};
    LCD_CS_CLR;
    LCD_DC_SET;
    HAL_SPI_Transmit(&LCD_SPI, N_Data, sizeof(N_Data), 5);
    LCD_CS_SET;
}

/*设置显示窗口*/
void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd) {
    ST7796S_LcdWriteCommand(LcdSetting.setxcmd);

    ST7796S_LcdWriteData(xStar >> 8);
    ST7796S_LcdWriteData(0x00FF & xStar);
    ST7796S_LcdWriteData(xEnd >> 8);
    ST7796S_LcdWriteData(0x00FF & xEnd);
    ST7796S_LcdWriteCommand(LcdSetting.setycmd);

    ST7796S_LcdWriteData(yStar >> 8);
    ST7796S_LcdWriteData(0x00FF & yStar);
    ST7796S_LcdWriteData(yEnd >> 8);
    ST7796S_LcdWriteData(0x00FF & yEnd);

    LCD_WriteRAM_Prepare();
}

/*清屏*/
void LCD_Clear(uint16_t Color) {
    unsigned int i, m;
    LCD_SetWindows(0, 0, LcdSetting.width - 1, LcdSetting.height - 1);
    LCD_CS_CLR;
    LCD_DC_SET;
    for (i = 0; i < LcdSetting.height; i++) {
        for (m = 0; m < LcdSetting.width; m++) {
            Lcd_WriteData_16Bit(Color);
        }
    }
    LCD_CS_SET;
}


void ST7796S_LcdInit(void) {
    LCD_LED_ON;
    ST7796S_LcdReset();
    ST7796S_LcdWriteCommand(0xF0);
    ST7796S_LcdWriteData(0xC3);
    ST7796S_LcdWriteCommand(0xF0);
    ST7796S_LcdWriteData(0x96);
    ST7796S_LcdWriteCommand(0x36);
    ST7796S_LcdWriteData(0x68);
    ST7796S_LcdWriteCommand(0x3A);
    ST7796S_LcdWriteData(0x05);
    ST7796S_LcdWriteCommand(0xB0);
    ST7796S_LcdWriteData(0x80);
    ST7796S_LcdWriteCommand(0xB6);
    ST7796S_LcdWriteData(0x00);
    ST7796S_LcdWriteData(0x02);
    ST7796S_LcdWriteCommand(0xB5);
    ST7796S_LcdWriteData(0x02);
    ST7796S_LcdWriteData(0x03);
    ST7796S_LcdWriteData(0x00);
    ST7796S_LcdWriteData(0x04);
    ST7796S_LcdWriteCommand(0xB1);
    ST7796S_LcdWriteData(0x80);
    ST7796S_LcdWriteData(0x10);
    ST7796S_LcdWriteCommand(0xB4);
    ST7796S_LcdWriteData(0x00);
    ST7796S_LcdWriteCommand(0xB7);
    ST7796S_LcdWriteData(0xC6);
    ST7796S_LcdWriteCommand(0xC5);
    ST7796S_LcdWriteData(0x24);
    ST7796S_LcdWriteCommand(0xE4);
    ST7796S_LcdWriteData(0x31);
    ST7796S_LcdWriteCommand(0xE8);
    ST7796S_LcdWriteData(0x40);
    ST7796S_LcdWriteData(0x8A);
    ST7796S_LcdWriteData(0x00);
    ST7796S_LcdWriteData(0x00);
    ST7796S_LcdWriteData(0x29);
    ST7796S_LcdWriteData(0x19);
    ST7796S_LcdWriteData(0xA5);
    ST7796S_LcdWriteData(0x33);
    ST7796S_LcdWriteCommand(0xC2);
    ST7796S_LcdWriteCommand(0xA7);

    ST7796S_LcdWriteCommand(0xE0);
    ST7796S_LcdWriteData(0xF0);
    ST7796S_LcdWriteData(0x09);
    ST7796S_LcdWriteData(0x13);
    ST7796S_LcdWriteData(0x12);
    ST7796S_LcdWriteData(0x12);
    ST7796S_LcdWriteData(0x2B);
    ST7796S_LcdWriteData(0x3C);
    ST7796S_LcdWriteData(0x44);
    ST7796S_LcdWriteData(0x4B);
    ST7796S_LcdWriteData(0x1B);
    ST7796S_LcdWriteData(0x18);
    ST7796S_LcdWriteData(0x17);
    ST7796S_LcdWriteData(0x1D);
    ST7796S_LcdWriteData(0x21);

    ST7796S_LcdWriteCommand(0XE1);
    ST7796S_LcdWriteData(0xF0);
    ST7796S_LcdWriteData(0x09);
    ST7796S_LcdWriteData(0x13);
    ST7796S_LcdWriteData(0x0C);
    ST7796S_LcdWriteData(0x0D);
    ST7796S_LcdWriteData(0x27);
    ST7796S_LcdWriteData(0x3B);
    ST7796S_LcdWriteData(0x44);
    ST7796S_LcdWriteData(0x4D);
    ST7796S_LcdWriteData(0x0B);
    ST7796S_LcdWriteData(0x17);
    ST7796S_LcdWriteData(0x17);
    ST7796S_LcdWriteData(0x1D);
    ST7796S_LcdWriteData(0x21);

    ST7796S_LcdWriteCommand(0X36);
    ST7796S_LcdWriteData(0xEC);
    ST7796S_LcdWriteCommand(0xF0);
    ST7796S_LcdWriteData(0xC3);
    ST7796S_LcdWriteCommand(0xF0);
    ST7796S_LcdWriteData(0x69);
    ST7796S_LcdWriteCommand(0X13);
    ST7796S_LcdWriteCommand(0X11);
    ST7796S_LcdWriteCommand(0X29);

    ST7796S_LcdDirection(LCD_DIRECTION);
    LCD_InvertColors(0);
    LCD_Clear(0x0000);  //清屏为黑色
}


void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos) {
    LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

void LCD_DrawPoint(uint16_t x, uint16_t y) {
    LCD_SetCursor(x, y);//设置光标位置
    Lcd_WriteData_16Bit(0xFC23);
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    LCD_SetCursor(x, y);//设置光标位置
    Lcd_WriteData_16Bit(color);
}

void LCD_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    // clipping
    if ((x >= LCD_W) || (y >= LCD_H)) return;
    if ((x + w - 1) >= LCD_W) w = LCD_W - x;
    if ((y + h - 1) >= LCD_H) h = LCD_H - y;
    LCD_SetWindows(x, y, x + w - 1, y + h - 1);
    LCD_CS_CLR;
    LCD_DC_SET;
    for (y = h; y > 0; y--) {
        for (x = w; x > 0; x--) {
            Lcd_WriteData_16Bit(color);
        }
    }
    LCD_CS_SET;
}

void LCD_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size) {
    uint8_t line;
    int32_t i, j;
    if ((x >= LCD_W) ||
        (y >= LCD_H) ||
        ((x + 5 * size - 1) < 0) ||
        ((y + 8 * size - 1) < 0))
        return;

    for (i = 0; i < 6; i++) {
        if (i == 5)
            line = 0x0;
        else
            line = Font[(c * 5) + i];
        for (j = 0; j < 8; j++) {
            if (line & 0x1) {
                if (size == 1)
                    LCD_DrawPixel(x + i, y + j, textColor);
                else {
                    LCD_FillRectangle(x + (i * size), y + (j * size), size, size, textColor);
                }
            } else if (bgColor != textColor) {
                if (size == 1) // default size
                    LCD_DrawPixel(x + i, y + j, bgColor);
                else {  // big size
                    LCD_FillRectangle(x + i * size, y + j * size, size, size, bgColor);
                }
            }
            line >>= 1;
        }
    }
}


uint32_t LCD_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor) {
//
    uint32_t count = 0;
//    if (y > 15) return 0;
    while (*pt) {
        LCD_DrawCharS(x*12, y*12 , *pt, textColor, LCD_BLACK, 2);
        pt++;
        x = x + 1;
//        if (x > 20) return count;  // number of characters printed
        count++;
    }
    return count;  // number of characters printed
}

void LCD_InvertColors(int invert) {
    ST7796S_LcdWriteCommand(invert ? LCD_INVON : LCD_INVOFF);
}

/* 设置绘制区域 */
void LCD_SetAddress(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    ST7796S_LcdWriteCommand(LcdSetting.setxcmd);
    ST7796S_LcdWriteData(x0 >> 8);
    ST7796S_LcdWriteData(x0 & 0xFF);
    ST7796S_LcdWriteData(x1 >> 8);
    ST7796S_LcdWriteData(x1 & 0xFF);

    ST7796S_LcdWriteCommand(LcdSetting.setycmd);
    ST7796S_LcdWriteData(y0 >> 8);
    ST7796S_LcdWriteData(y0 & 0xFF);
    ST7796S_LcdWriteData(y1 >> 8);
    ST7796S_LcdWriteData(y1 & 0xFF);

    LCD_WriteRAM_Prepare();
}

// 修改后的批量发送函数（添加字节交换）
void LCD_PushColors(uint16_t *color, uint32_t size)
{
    LCD_CS_CLR;
    LCD_DC_SET; // 数据模式

    // 添加字节交换（关键修复）
    for(uint32_t i = 0; i < size; i++) {
        uint8_t swapped[] = {
                (color[i] >> 8) & 0xFF,  // 先发送高位字节
                color[i] & 0xFF           // 后发送低位字节
        };
        HAL_SPI_Transmit(&LCD_SPI, swapped, 2, HAL_MAX_DELAY);
    }

    LCD_CS_SET;
}

static void start_next_dma_transfer(void);

void LCD_PushColors_DMA(lv_disp_drv_t *drv, uint16_t *color, uint32_t size)
{
    Print_Printf("DMA_IN: %d pixels\n", size);
    dma_color_ptr = color;
    dma_pixels_remaining = size;
    dma_drv_ptr = drv;

    LCD_CS_CLR;
    LCD_DC_SET;

    start_next_dma_transfer();  // 启动第一次分块
}
static void start_next_dma_transfer(void)
{
    Print_Printf("DMA_TX: %d pixels\n", dma_pixels_remaining);
    if(dma_pixels_remaining == 0) {
        LCD_CS_SET;
        if(dma_drv_ptr) {
            lv_disp_flush_ready(dma_drv_ptr);
            Print_Printf("Flush ready called\n");
        }
        dma_drv_ptr = NULL;
        return;
    }

    uint32_t chunk = dma_pixels_remaining > DMA_CHUNK_PIXELS ? DMA_CHUNK_PIXELS : dma_pixels_remaining;
    Print_Printf("HAL_SPI_Transmit_DMA: %d pixels\n", chunk);

    for(uint32_t i=0; i<chunk; i++){
        spi_dma_buf[2*i]   = dma_color_ptr[i] >> 8;
        spi_dma_buf[2*i+1] = dma_color_ptr[i] & 0xFF;
    }

    dma_color_ptr += chunk;
    dma_pixels_remaining -= chunk;
    HAL_SPI_Transmit_DMA(&hspi1, spi_dma_buf, chunk * 2);
    Print_Printf("DMA_TX_DONE: %d pixels\n", chunk);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi == &LCD_SPI) {
        Print_Printf("HAL_SPI_TxCplt回调\n");
        // 继续下一次传输
        start_next_dma_transfer();
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi){
    if (hspi == &LCD_SPI) {
        Print_Printf("HAL_SPI_ErrorCallback\n");
        LCD_CS_SET;  // 出错时释放片选
        if (dma_drv_ptr) lv_disp_flush_ready(dma_drv_ptr);
        dma_drv_ptr = NULL;
    }
}
