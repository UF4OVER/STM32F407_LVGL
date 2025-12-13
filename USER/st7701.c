#include "st7701.h"
#include <stdio.h>

#define ST7701_LOG(fmt, ...)   printf("[LCD] " fmt "\r\n", ##__VA_ARGS__)
#define ST7701_ERR(fmt, ...)   printf("[LCD][ERROR] " fmt "\r\n", ##__VA_ARGS__)


static bool st7701WriteCmd(uint8_t data);
static bool st7701WriteData(uint8_t data);
static bool st7701InitRegs(void);


bool st7701Init(void)
{
  ST7701_LOG("Init start");
  bool ok = st7701InitRegs();
  if (ok)
  {
    ST7701_LOG("Init success");
  }
  else
  {
    ST7701_ERR("Init failed");
  }
  return ok;
}

bool st7701InitRegs(void) {
	ST7701_LOG("Reset pulse");
	HAL_GPIO_WritePin(GPIOE, TP_RST_Pin|SPI3_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOE, TP_RST_Pin|SPI3_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOE, TP_RST_Pin|SPI3_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	ST7701_LOG("Command 0x11 (sleep out)");
	if (!st7701WriteCmd (0x11))
	{
		return false;
	}
	HAL_Delay(100);


	//	//-----------------------------------Initial setting----------------------------------------------//
	//	st7701WriteCmd (0xFF);
	//	st7701WriteData (0x77);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x10);
	//	st7701WriteCmd (0xC0);
	//	st7701WriteData (0x3B);
	//	st7701WriteData (0x00);
	//	st7701WriteCmd (0xC1);
	//	st7701WriteData (0x0D);
	//	st7701WriteData (0x02);
	//
	//	st7701WriteCmd (0xC2);
	//	st7701WriteData (0x21);
	//	st7701WriteData (0x08);
	//	st7701WriteCmd (0xCC);
	//	st7701WriteData (0x10);
	//	st7701WriteCmd (0xB0);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x05);
	//	st7701WriteData (0x0F);
	//	st7701WriteData (0x0D);
	//	st7701WriteData (0x13);
	//	st7701WriteData (0x07);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0x08);
	//
	//	st7701WriteData (0x09);
	//	st7701WriteData (0x1E);
	//	st7701WriteData (0x05);
	//	st7701WriteData (0x12);
	//	st7701WriteData (0x10);
	//	st7701WriteData (0xA7);
	//	st7701WriteData (0x2F);
	//	st7701WriteData (0x18);
	//	st7701WriteCmd (0xB1);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x0F);
	//	st7701WriteData (0x17);
	//	st7701WriteData (0x0C);
	//	st7701WriteData (0x0D);
	//	st7701WriteData (0x05);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0x08);
	//	st7701WriteData (0x08);
	//	st7701WriteData (0x1E);
	//	st7701WriteData (0x05);
	//	st7701WriteData (0x13);
	//
	//	st7701WriteData (0x11);
	//	st7701WriteData (0xA7);
	//	st7701WriteData (0x2F);
	//	st7701WriteData (0x18);
	//	st7701WriteCmd (0xFF);
	//	st7701WriteData (0x77);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x11);
	//	st7701WriteCmd (0xB0);
	//	st7701WriteData (0x4D);
	//	st7701WriteCmd (0xB1);
	//	st7701WriteData (0x4F);
	//	st7701WriteCmd (0xB2);
	//	st7701WriteData (0x07);
	//	st7701WriteCmd (0xB3);
	//	st7701WriteData (0x80);
	//	st7701WriteCmd (0xB5);
	//	st7701WriteData (0x47);
	//	st7701WriteCmd (0xB7);
	//	st7701WriteData (0x85);
	//	st7701WriteCmd (0xB8);
	//	st7701WriteData (0x21);
	//	st7701WriteCmd (0xB9);
	//	st7701WriteData (0x10);
	//	st7701WriteCmd (0xC1);
	//	st7701WriteData (0x78);
	//	st7701WriteCmd (0xC2);
	//	st7701WriteData (0x78);
	//	st7701WriteCmd (0xD0);
	//	st7701WriteData (0x88);
	//	HAL_Delay (100);
	//	st7701WriteCmd (0xE0);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x02);
	//
	//	st7701WriteCmd (0xE1);
	//	st7701WriteData (0x08);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x0A);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x07);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x09);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x33);
	//	st7701WriteData (0x33);
	//	st7701WriteCmd (0xE2);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteCmd (0xE3);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x33);
	//	st7701WriteData (0x33);
	//	st7701WriteCmd (0xE4);
	//	st7701WriteData (0x44);
	//	st7701WriteData (0x44);
	//	st7701WriteCmd (0xE5);
	//	st7701WriteData (0x0E);
	//	st7701WriteData (0x2D);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x10);
	//	st7701WriteData (0x2D);
	//
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0A);
	//	st7701WriteData (0x2D);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0C);
	//	st7701WriteData (0x2D);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0xA0);
	//	st7701WriteCmd (0xE6);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x33);
	//	st7701WriteData (0x33);
	//	st7701WriteCmd (0xE7);
	//	st7701WriteData (0x44);
	//	st7701WriteData (0x44);
	//	st7701WriteCmd (0xE8);
	//	st7701WriteData (0x0D);
	//	st7701WriteData (0x2D);
	//	st7701WriteData (0xA0);
	//
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0F);
	//	st7701WriteData (0x2D);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x09);
	//	st7701WriteData (0x2D);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0B);
	//	st7701WriteData (0x2D);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0xA0);
	//	st7701WriteCmd (0xEB);
	//	st7701WriteData (0x02);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0xE4);
	//	st7701WriteData (0xE4);
	//	st7701WriteData (0x44);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x40);
	//	st7701WriteCmd (0xEC);
	//	st7701WriteData (0x02);
	//	st7701WriteData (0x01);
	//	st7701WriteCmd (0xED);
	//	st7701WriteData (0xAB);
	//	st7701WriteData (0x89);
	//	st7701WriteData (0x76);
	//	st7701WriteData (0x54);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0xFF);
	//	st7701WriteData (0xFF);
	//
	//	st7701WriteData (0xFF);
	//	st7701WriteData (0xFF);
	//	st7701WriteData (0xFF);
	//	st7701WriteData (0xFF);
	//	st7701WriteData (0x10);
	//	st7701WriteData (0x45);
	//	st7701WriteData (0x67);
	//	st7701WriteData (0x98);
	//	st7701WriteData (0xBA);
	//	st7701WriteCmd (0xFF);
	//	st7701WriteData (0x77);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteCmd (0x11);
	//	st7701WriteCmd (0x36);
	//	st7701WriteData (0x00);
	//	st7701WriteCmd (0x29);
	//


	//-----------------------------------Initial setting ESP32 not worked----------------------------------------------//
	//	st7701WriteCmd (0xFF);
	//	st7701WriteData (0x77);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x10);
	//	// added by manufacture
	//	st7701WriteCmd (0xC0);
	//	st7701WriteData (0x3B);
	//	st7701WriteData (0x00);
	//
	//	st7701WriteCmd (0xC1);
	//	st7701WriteData (0x0D);
	//	st7701WriteData (0x02);
	//
	//	st7701WriteCmd (0xC2);
	//	st7701WriteData (0x31);
	//	st7701WriteData (0x05);
	//	// changed by manufacture//
	//	st7701WriteCmd (0xCD);
	//	st7701WriteData (0x00);
	//	// Positive Voltage Gamma Control
	//	st7701WriteCmd (0xB0);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0x18);
	//	st7701WriteData (0x0E);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0x06);
	//	st7701WriteData (0x07);
	//	st7701WriteData (0x08);
	//	st7701WriteData (0x07);
	//	st7701WriteData (0x22);
	//	st7701WriteData (0x04);
	//	st7701WriteData (0x12);
	//	st7701WriteData (0x0F);
	//	st7701WriteData (0xAA);
	//	st7701WriteData (0x31);
	//	st7701WriteData (0x18);
	//	// Negative Voltage Gamma Control
	//	st7701WriteCmd (0xB1);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0x19);
	//	st7701WriteData (0x0E);
	//	st7701WriteData (0x12);
	//	st7701WriteData (0x07);
	//	st7701WriteData (0x08);
	//	st7701WriteData (0x08);
	//	st7701WriteData (0x08);
	//	st7701WriteData (0x22);
	//	st7701WriteData (0x04);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0xA9);
	//	st7701WriteData (0x32);
	//	st7701WriteData (0x18);
	//
	//	st7701WriteCmd (0xFF);
	//	st7701WriteData (0x77);
	//	st7701WriteData (0x01);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x11);
	//
	//	st7701WriteCmd (0xB0);
	//	st7701WriteData (0x60);
	//
	//	st7701WriteCmd (0xB1);
	//	st7701WriteData (0x32);
	//
	//	st7701WriteCmd (0xB2);
	//	st7701WriteData (0x07);
	//
	//	st7701WriteCmd (0xB3);
	//	st7701WriteData (0x80);
	//
	//	st7701WriteCmd (0xB5);
	//	st7701WriteData (0x49);
	//
	//	st7701WriteCmd (0xB7);
	//	st7701WriteData (0x85);
	//
	//	st7701WriteCmd (0xB8);
	//	st7701WriteData (0x21);
	//
	////	st7701WriteCmd (0xB9);
	////	st7701WriteData (0x10);
	//
	//	st7701WriteCmd (0xC1);
	//	st7701WriteData (0x78);
	//
	//	st7701WriteCmd (0xC2);
	//	st7701WriteData (0x78);
	//
	////	st7701WriteCmd (0xD0);
	////	st7701WriteData (0x88);
	////	HAL_Delay (100);
	//
	//	st7701WriteCmd (0xE0);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x1B);
	//	st7701WriteData (0x02);
	//
	//	st7701WriteCmd (0xE1);
	//	st7701WriteData (0x08);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x07);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x44);
	//	st7701WriteData (0x44);
	//
	//	st7701WriteCmd (0xE2);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0x44);
	//	st7701WriteData (0x44);
	//	st7701WriteData (0xED);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0xEC);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//
	//
	//	st7701WriteCmd (0xE3);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0x11);
	//
	//	st7701WriteCmd (0xE4);
	//	st7701WriteData (0x44);
	//	st7701WriteData (0x44);
	//
	//	st7701WriteCmd (0xE5);
	//	st7701WriteData (0x0A);
	//	st7701WriteData (0xE9);
	//	st7701WriteData (0xD8);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0C);
	//	st7701WriteData (0xEB);
	//	st7701WriteData (0xD8);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0E);
	//	st7701WriteData (0xED);
	//	st7701WriteData (0xD8);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x10);
	//	st7701WriteData (0xEF);
	//	st7701WriteData (0xD8);
	//	st7701WriteData (0xA0);
	//
	//	st7701WriteCmd (0xE6);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x00);
	//	st7701WriteData (0x11);
	//	st7701WriteData (0x11);
	//
	//	st7701WriteCmd (0xE7);
	//	st7701WriteData (0x44);
	//	st7701WriteData (0x44);
	//
	//	st7701WriteCmd (0xE8);
	//	st7701WriteData (0x09);
	//	st7701WriteData (0xE8);
	//	st7701WriteData (0xD8);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0B);
	//	st7701WriteData (0xEA);
	//	st7701WriteData (0xD8);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0D);
	//	st7701WriteData (0xEC);
	//	st7701WriteData (0xD8);
	//	st7701WriteData (0xA0);
	//	st7701WriteData (0x0F);
	//	st7701WriteData (0xEE);
	//	st7701WriteData (0xD8);
	//	st7701WriteData (0xA0);
	//
	//	st7701WriteCmd(0xEB);
	//	st7701WriteData(0x02);
	//	st7701WriteData(0x00);
	//	st7701WriteData(0xE4);
	//	st7701WriteData(0xE4);
	//	st7701WriteData(0x88);
	//	st7701WriteData(0x00);
	//	st7701WriteData(0x40);
	//
	//	st7701WriteCmd(0xEC);
	//	st7701WriteData(0x3C);
	//	st7701WriteData(0x00);
	//
	//	st7701WriteCmd(0xED);
	//	st7701WriteData(0xAB);
	//	st7701WriteData(0x89);
	//	st7701WriteData(0x76);
	//	st7701WriteData(0x54);
	//	st7701WriteData(0x02);
	//	st7701WriteData(0xFF);
	//	st7701WriteData(0xFF);
	//	st7701WriteData(0xFF);
	//	st7701WriteData(0xFF);
	//	st7701WriteData(0xFF);
	//	st7701WriteData(0xFF);
	//	st7701WriteData(0x20);
	//	st7701WriteData(0x45);
	//	st7701WriteData(0x67);
	//	st7701WriteData(0x98);
	//	st7701WriteData(0xBA);
	//
	//	st7701WriteCmd(0x36);
	//	st7701WriteData(0x00);
	//
	//	//-----------VAP & VAN---------------
	st7701WriteCmd(0xFF);
	st7701WriteData(0x77);
	st7701WriteData(0x01);
	st7701WriteData(0x00);
	st7701WriteData(0x00);
	st7701WriteData(0x13);

	st7701WriteCmd(0xE5);
	st7701WriteData(0xE4);

	st7701WriteCmd(0xFF);
	st7701WriteData(0x77);
	st7701WriteData(0x01);
	st7701WriteData(0x00);
	st7701WriteData(0x00);
	st7701WriteData(0x00);


	ST7701_LOG("Pixel format");
	st7701WriteCmd(0x3A);   //0x70 RGB888, 0x60 RGB666, 0x50 RGB565
	st7701WriteData(0x60);

	st7701WriteCmd(0x21);   //Display Inversion On

	ST7701_LOG("Exit sleep");
	st7701WriteCmd(0x11);   //Sleep Out
	HAL_Delay(100);

	bool ret;

	ret = st7701WriteCmd(0x29);   //Display On

	HAL_Delay(50);

	return ret;
}
bool st7701WriteCmd(uint8_t data)
{
	bool ret = true;
	uint16_t tx_data;

	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);

	tx_data = (0<<8) | data;
	HAL_SPI_Transmit(&hspi3, (const uint8_t *)&tx_data, 1, 10);

	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
	return ret;
}

bool st7701WriteData(uint8_t data)
{
	bool ret = true;
	uint16_t tx_data;

	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);

	tx_data = (1<<8) | data;
	HAL_SPI_Transmit(&hspi3, (const uint8_t *)&tx_data, 1, 10);

	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
	return ret;
}
