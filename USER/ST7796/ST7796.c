#include "ST7796.h"
#include "FONT.h"
#include "spi.h"

ST7796S_LcdSetting LcdSetting;
extern DMA_HandleTypeDef hdma_spi1_tx;

static SPI_HandleTypeDef *LCD_SPI_PTR = &LCD_SPI; // 全局指针，用于 DMA 回调

void ST7796S_LcdReset() {
    LCD_RST_CLR;
    HAL_Delay(100);
    LCD_RST_SET;
    HAL_Delay(50);
}

/*写命令*/
void ST7796S_LcdWriteCommand(uint8_t cmd){
    LCD_CS_CLR;
    LCD_DC_CLR;
    HAL_SPI_Transmit(&LCD_SPI, &cmd, 1, HAL_MAX_DELAY);
    LCD_CS_SET;
}
// 发送 8 位数据（寄存器数据）
void ST7796S_LcdWriteData(uint8_t data) {
    LCD_CS_CLR;
    LCD_DC_SET;
    HAL_SPI_Transmit(&LCD_SPI, &data, 1, HAL_MAX_DELAY);
}
/*写数据*/
void ST7796S_LcdWriteData16(uint16_t data){
    LCD_CS_CLR;
    LCD_DC_SET;
    HAL_SPI_Transmit(&LCD_SPI, (uint16_t*)&data, 1, HAL_MAX_DELAY);
    LCD_CS_SET;
}

// 写单个 8 位寄存器（命令+数据）
void ST7796S_LcdWriteReg(uint8_t reg, uint8_t data){
    LCD_CS_CLR;
    LCD_DC_CLR;   // 命令模式
    HAL_SPI_Transmit(&LCD_SPI, &reg, 1, HAL_MAX_DELAY);
    LCD_DC_SET;   // 数据模式
    HAL_SPI_Transmit(&LCD_SPI, &data, 1, HAL_MAX_DELAY);
    LCD_CS_SET;
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
void Lcd_WriteData_16Bit(uint16_t data)
{
    LCD_CS_CLR;
    LCD_DC_SET;
    HAL_SPI_Transmit(LCD_SPI_PTR, (uint16_t *)&data, 1, HAL_MAX_DELAY);
    LCD_CS_SET;
}

// 设置显示区域
void LCD_SetWindows(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1){
    uint8_t buf[4];

    ST7796S_LcdWriteCommand(LcdSetting.setxcmd);
    buf[0] = x0 >> 8; buf[1] = x0 & 0xFF;
    buf[2] = x1 >> 8; buf[3] = x1 & 0xFF;
    LCD_CS_CLR; LCD_DC_SET;
    HAL_SPI_Transmit(&LCD_SPI, buf, 4, HAL_MAX_DELAY);
    LCD_CS_SET;

    ST7796S_LcdWriteCommand(LcdSetting.setycmd);
    buf[0] = y0 >> 8; buf[1] = y0 & 0xFF;
    buf[2] = y1 >> 8; buf[3] = y1 & 0xFF;
    LCD_CS_CLR; LCD_DC_SET;
    HAL_SPI_Transmit(&LCD_SPI, buf, 4, HAL_MAX_DELAY);
    LCD_CS_SET;

    LCD_WriteRAM_Prepare();
}

/*清屏*/
void LCD_Clear(uint16_t color){
    LCD_SetWindows(0,0,LcdSetting.width-1,LcdSetting.height-1);

    static uint16_t buf[128];
    for(int i=0;i<128;i++) buf[i] = color;

    uint32_t total = LcdSetting.width * LcdSetting.height;
    while(total){
        uint32_t n = total>128 ? 128 : total;
        LCD_PushColors_DMA(buf,n);
        while(HAL_SPI_GetState(&LCD_SPI)!=HAL_SPI_STATE_READY);
        total -= n;
    }
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

void LCD_DrawPixel(uint16_t x,uint16_t y,uint16_t color){
    LCD_SetWindows(x,y,x,y);
    LCD_PushColors_DMA(&color,1);
}

void LCD_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size) {
    uint16_t char_buf[5*8*size*size]; // 最多放大 size*size 的像素
    int idx = 0;

    for(int i=0; i<6; i++) {
        uint8_t line = (i==5)?0x0:Font[(c*5)+i];
        for(int j=0; j<8; j++) {
            uint16_t color = (line & 0x1) ? textColor : bgColor;
            for(int dx=0; dx<size; dx++)
                for(int dy=0; dy<size; dy++)
                    char_buf[idx++] = color;
            line >>= 1;
        }
    }
    LCD_SetWindows(x, y, x + 5*size - 1, y + 8*size - 1);
    LCD_PushColors_DMA(char_buf, idx);
    while(HAL_SPI_GetState(&LCD_SPI) != HAL_SPI_STATE_READY);
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
void LCD_PushColors(uint16_t *color, uint32_t size)
{
    LCD_CS_CLR;
    LCD_DC_SET;
    HAL_SPI_Transmit(LCD_SPI_PTR, color, size, HAL_MAX_DELAY);
    LCD_CS_SET;
}
// DMA 批量发送 GRAM 数据
void LCD_PushColors_DMA(uint16_t *color, uint32_t size){
    LCD_CS_CLR;
    LCD_DC_SET;
    HAL_SPI_Transmit_DMA(&LCD_SPI, color, size); // size 单位：16bit 元素
}

