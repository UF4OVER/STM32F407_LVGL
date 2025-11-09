/*ST7796-ILI9488 Driver library for STM32*/
/* www.pepoya.ir*/
/* SAEED KOLIVAND*/

/* Includes ------------------------------------------------------------------*/
#include "H_ST7796.h"
#include "spi.h"
#include "gpio.h"
#include "main.h"
#include "H_FONT.h"

/* Global Variables ------------------------------------------------------------------*/
volatile uint16_t LCD_HEIGHT = ST7796_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ST7796_SCREEN_WIDTH;

/* Initialize SPI */
void ST7796_SPI_Init(void)
{
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);	//CS OFF
}

/*Send data (char) to LCD*/
void ST7796_SPI_Send(unsigned char SPI_Data)
{
    HAL_SPI_Transmit(LEOPARD_BOARD, &SPI_Data, 1, 10);
}

/* Send command (char) to LCD */
void ST7796_Write_Command(uint8_t Command)
{
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
    ST7796_SPI_Send(Command);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

/* Send Data (char) to LCD */
void ST7796_Write_Data(uint8_t Data)
{
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    ST7796_SPI_Send(Data);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

/* Set Address - Location block - to draw into */
void ST7796_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
    ST7796_Write_Command(0x2A);
    ST7796_Write_Data(X1>>8);
    ST7796_Write_Data(X1);
    ST7796_Write_Data(X2>>8);
    ST7796_Write_Data(X2);

    ST7796_Write_Command(0x2B);
    ST7796_Write_Data(Y1>>8);
    ST7796_Write_Data(Y1);
    ST7796_Write_Data(Y2>>8);
    ST7796_Write_Data(Y2);

    ST7796_Write_Command(0x2C);
}



/*HARDWARE RESET*/
void ST7796_Reset(void)
{
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}

/*Ser rotation of the screen - changes x0 and y0*/
void ST7796_Set_Rotation(uint8_t Rotation)
{
    uint8_t screen_rotation = Rotation;
    ST7796_Write_Command(0x36);
    HAL_Delay(1);

    switch(screen_rotation)
    {
        case SCREEN_VERTICAL_1:
            ST7796_Write_Data(0x40|0x08);
            LCD_WIDTH = 320;
            LCD_HEIGHT = 480;
            break;
        case SCREEN_HORIZONTAL_1:
            ST7796_Write_Data(0x20|0x08);
            LCD_WIDTH  = 480;
            LCD_HEIGHT = 320;
            break;
        case SCREEN_VERTICAL_2:
            ST7796_Write_Data(0x80|0x08);
            LCD_WIDTH  = 320;
            LCD_HEIGHT = 480;
            break;
        case SCREEN_HORIZONTAL_2:
            ST7796_Write_Data(0x40|0x80|0x20|0x08);
            LCD_WIDTH  = 480;
            LCD_HEIGHT = 320;
            break;
        default:
            //EXIT IF SCREEN ROTATION NOT VALID!
            break;
    }
}

/*Enable LCD display*/
void ST7796_Enable(void)
{
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}

/*Initialize LCD display*/
void ST7796_Init(void)
{

    ST7796_Enable();
    ST7796_SPI_Init();
    ST7796_Reset();

//SOFTWARE RESET
    ST7796_Write_Command(0x01);
    HAL_Delay(1000);

//POWER CONTROL A
    ST7796_Write_Command(0xCB);
    ST7796_Write_Data(0x39);
    ST7796_Write_Data(0x2C);
    ST7796_Write_Data(0x00);
    ST7796_Write_Data(0x34);
    ST7796_Write_Data(0x02);

//POWER CONTROL B
    ST7796_Write_Command(0xCF);
    ST7796_Write_Data(0x00);
    ST7796_Write_Data(0xC1);
    ST7796_Write_Data(0x30);

//DRIVER TIMING CONTROL A
    ST7796_Write_Command(0xE8);
    ST7796_Write_Data(0x85);
    ST7796_Write_Data(0x00);
    ST7796_Write_Data(0x78);

//DRIVER TIMING CONTROL B
    ST7796_Write_Command(0xEA);
    ST7796_Write_Data(0x00);
    ST7796_Write_Data(0x00);

//POWER ON SEQUENCE CONTROL
    ST7796_Write_Command(0xED);
    ST7796_Write_Data(0x64);
    ST7796_Write_Data(0x03);
    ST7796_Write_Data(0x12);
    ST7796_Write_Data(0x81);

//PUMP RATIO CONTROL
    ST7796_Write_Command(0xF7);
    ST7796_Write_Data(0x20);

//POWER CONTROL,VRH[5:0]
    ST7796_Write_Command(0xC0);
    ST7796_Write_Data(0x23);

//POWER CONTROL,SAP[2:0];BT[3:0]
    ST7796_Write_Command(0xC1);
    ST7796_Write_Data(0x10);

//VCM CONTROL
    ST7796_Write_Command(0xC5);
    ST7796_Write_Data(0x3E);
    ST7796_Write_Data(0x28);

//VCM CONTROL 2
    ST7796_Write_Command(0xC7);
    ST7796_Write_Data(0x86);

//MEMORY ACCESS CONTROL
    ST7796_Write_Command(0x36);
    ST7796_Write_Data(0x48);

//PIXEL FORMAT
    ST7796_Write_Command(0x3A);
    ST7796_Write_Data(0x55);

//FRAME RATIO CONTROL, STANDARD RGB COLOR
    ST7796_Write_Command(0xB1);
    ST7796_Write_Data(0x00);
    ST7796_Write_Data(0x18);

//DISPLAY FUNCTION CONTROL
    ST7796_Write_Command(0xB6);
    ST7796_Write_Data(0x08);
    ST7796_Write_Data(0x82);
    ST7796_Write_Data(0x27);

//3GAMMA FUNCTION DISABLE
    ST7796_Write_Command(0xF2);
    ST7796_Write_Data(0x00);

//GAMMA CURVE SELECTED
    ST7796_Write_Command(0x26);
    ST7796_Write_Data(0x01);

//POSITIVE GAMMA CORRECTION
    ST7796_Write_Command(0xE0);
    ST7796_Write_Data(0x0F);
    ST7796_Write_Data(0x31);
    ST7796_Write_Data(0x2B);
    ST7796_Write_Data(0x0C);
    ST7796_Write_Data(0x0E);
    ST7796_Write_Data(0x08);
    ST7796_Write_Data(0x4E);
    ST7796_Write_Data(0xF1);
    ST7796_Write_Data(0x37);
    ST7796_Write_Data(0x07);
    ST7796_Write_Data(0x10);
    ST7796_Write_Data(0x03);
    ST7796_Write_Data(0x0E);
    ST7796_Write_Data(0x09);
    ST7796_Write_Data(0x00);

//NEGATIVE GAMMA CORRECTION
    ST7796_Write_Command(0xE1);
    ST7796_Write_Data(0x00);
    ST7796_Write_Data(0x0E);
    ST7796_Write_Data(0x14);
    ST7796_Write_Data(0x03);
    ST7796_Write_Data(0x11);
    ST7796_Write_Data(0x07);
    ST7796_Write_Data(0x31);
    ST7796_Write_Data(0xC1);
    ST7796_Write_Data(0x48);
    ST7796_Write_Data(0x08);
    ST7796_Write_Data(0x0F);
    ST7796_Write_Data(0x0C);
    ST7796_Write_Data(0x31);
    ST7796_Write_Data(0x36);
    ST7796_Write_Data(0x0F);

//EXIT SLEEP
    ST7796_Write_Command(0x11);
    HAL_Delay(120);

//TURN ON DISPLAY
    ST7796_Write_Command(0x29);

//STARTING ROTATION
    ST7796_Set_Rotation(SCREEN_VERTICAL_1);
}


void ST7796_PushColors(uint16_t *color, uint32_t size){
    if (size == 0) return;

    uint32_t Buffer_Size = 0;
    if((size*2) < BURST_MAX_SIZE)
    {
        Buffer_Size = size*2;
    }
    else
    {
        Buffer_Size = BURST_MAX_SIZE;
    }

    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

    uint32_t Sending_Size = size*2;
    uint32_t Sending_in_Block = Sending_Size/Buffer_Size;
    uint32_t Remainder_from_block = Sending_Size%Buffer_Size;

    if(Sending_in_Block != 0)
    {
        for(uint32_t j = 0; j < (Sending_in_Block); j++)
        {
            HAL_SPI_Transmit(LEOPARD_BOARD, (unsigned char *)(color+(j*Buffer_Size/2)), Buffer_Size, 10);
        }
    }

    //REMAINDER!
    if(Remainder_from_block != 0)
    {
        HAL_SPI_Transmit(LEOPARD_BOARD, (unsigned char *)(color+(Sending_in_Block*Buffer_Size/2)), Remainder_from_block, 10);
    }

    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}
