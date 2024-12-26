#include "i2c.h"
#include "ST7796.h"
#include "FT6336.h"

HAL_StatusTypeDef I2C_WriteRegister(uint8_t DevAddress, uint8_t RegAddress, uint8_t *pData, uint16_t Size) {
    return HAL_I2C_Mem_Write(&hi2c1, DevAddress, RegAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef I2C_ReadRegister(uint8_t DevAddress, uint8_t RegAddress, uint8_t *pData, uint16_t Size) {
    return HAL_I2C_Mem_Read(&hi2c1, DevAddress, RegAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

void FT6X36_Init(void) {
    FT_RST_L;
    HAL_Delay(1);
    FT_RST_H;
    HAL_Delay(50);

    HAL_StatusTypeDef ret;

    // 设置 DEVICE_MODE 为 0x00（正常模式）

    ret = I2C_WriteRegister(FT6X36_ADDR, 0x00, 0x00,1);
    if (ret == HAL_OK) {
        LCD_DrawString(0,3, "FT6X36_Init_Step_1!", LCD_RED);
    }

    // 设置 ID_G_MODE 为 0x00（启用中断输出）
    ret = I2C_WriteRegister(FT6X36_ADDR, 0xA4, 0x00,1);
    if (ret == HAL_OK) {
        LCD_DrawString(0,5, "FT6X36_Init_Step_2!", LCD_RED);
    }

}

static void AdjustTouchCoordinates(uint16_t *x, uint16_t *y) {
    uint16_t rawX = *x;
    uint16_t rawY = *y;

    // 根据触摸屏和屏幕方向进行调整，以下为常见几种情况

    // 情况 1：触摸屏 X 和 Y 坐标需要互换
//    *x = rawY;
//    *y = rawX;

    // 情况 2：X 或 Y 坐标需要翻转
    *x = SCREEN_WIDTH - rawX;
    *y = SCREEN_HEIGHT - rawY;

    // 情况 3：坐标需要缩放到屏幕分辨率
    // 假设触摸屏的分辨率为 TOUCH_WIDTH 和 TOUCH_HEIGHT
//#define TOUCH_WIDTH  LCD_W  // 替换为触摸屏的实际分辨率
//#define TOUCH_HEIGHT LCD_H
//
//    *x = (*x * SCREEN_WIDTH) / TOUCH_WIDTH;
//    *y = (*y * SCREEN_HEIGHT) / TOUCH_HEIGHT;
}

void ReadTouchData(void) { // 测试触摸屏数据
    uint8_t touchStatus = 0;
    uint8_t touchData[4];  // X和Y的高、低字节

    // 读取触摸状态寄存器
    I2C_ReadRegister(FT6X36_ADDR, REG_TD_STATUS, &touchStatus, 1);
    uint8_t touchCount = touchStatus & 0x0F;  // 触摸点数量
    if (touchCount > 0) {
        I2C_ReadRegister(FT6X36_ADDR, 0x03, touchData, 4);
        uint16_t x = ((touchData[0] & 0x0F) << 8) | touchData[1];
        uint16_t y = ((touchData[2] & 0x0F) << 8) | touchData[3];
        AdjustTouchCoordinates(&x, &y);
        LCD_DrawPixel(x, y, 0xFFFF);
    }
}

void GetTouchPoint(uint16_t *x, uint16_t *y) {
    uint8_t touchStatus = 0;
    uint8_t touchData[4];  // X和Y的高、低字节

    // 读取触摸状态寄存器
    I2C_ReadRegister(FT6X36_ADDR, REG_TD_STATUS, &touchStatus, 1);
    uint8_t touchCount = touchStatus & 0x0F;  // 触摸点数量
    if (touchCount > 0) {
        I2C_ReadRegister(FT6X36_ADDR, 0x03, touchData, 4);
        *x = ((touchData[0] & 0x0F) << 8) | touchData[1];
        *y = ((touchData[2] & 0x0F) << 8) | touchData[3];
        AdjustTouchCoordinates(x, y); // 调整坐标
    }
}