#include "lcd.h"
#include "stdlib.h"
#include "font.h"
//#include "usart.h"
//#include "ltdc.h"
#include "stdio.h"
//#include "dma2d.h"

//LTDC中需要实现清屏，画点，区域填充单色，区域填充指定色块函数。

//LCD的画笔颜色和背景色
uint32_t POINT_COLOR = 0xFF000000; //画笔颜色
uint32_t BACK_COLOR = 0xFFFFFFFF;  //背景色

//管理LCD重要参数

//初始化为RGB屏480*272，横屏，每个像素2字节
_lcd_dev lcddev = { .id = 0X7701, .width = 480, .height = 480, .dir = 2, .pixsize = 2, };

__attribute__((section(".LCD_RAM_Section"))) uint16_t ltdc_lcd_framebuf[480][480]; //__attribute__((section(".RAM_D1"))); //ltdc缓冲区buf

//打开LCD开关
//lcd_switch:1 打开,0，关闭
void LTDC_Switch(uint8_t sw) {
	if (sw == 1)
		__HAL_LTDC_ENABLE(&hltdc);
	else if (sw == 0)
		__HAL_LTDC_DISABLE(&hltdc);
}

//画点函数
//x,y:坐标
//color:颜色
void LTDC_Draw_Point(uint16_t x, uint16_t y, uint32_t color) {
	if (lcddev.dir)												 //横屏
	{
		*(uint16_t*) ((uint32_t) ltdc_lcd_framebuf + lcddev.pixsize * (lcddev.width * y + x)) = color;
	} else //竖屏
	{
		*(uint16_t*) ((uint32_t) ltdc_lcd_framebuf + lcddev.pixsize * (lcddev.width * (lcddev.height - x - 1) + y)) = color;
	}
}


uint16_t LTDC_PanelID_Read(void) {

}

//设置LCD显示方向
//dir:0,竖屏；1,横屏
void LCD_Display_Dir(uint8_t dir) {
	lcddev.dir = dir;        //横屏/竖屏
	if (dir == 0)	   //竖屏
			{
		lcddev.width = lcddev.height;
		lcddev.height = lcddev.width;
	} else if (dir == 1) //横屏
			{
		lcddev.width = lcddev.width;
		lcddev.height = lcddev.height;
	}
}

//LCD开启显示
void LCD_DisplayOn(void) {
	LTDC_Switch(1); //开启LCD
}
//LCD关闭显示
void LCD_DisplayOff(void) {
	LTDC_Switch(0); //关闭LCD
}
//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
void LCD_DrawPoint(uint16_t x, uint16_t y) {
	LTDC_Draw_Point(x, y, POINT_COLOR);
}

//初始化lcd
void LCD_Init(void) {
	lcddev.id = 0X7701;
	lcddev.width = 480;
	lcddev.height = 480;
	lcddev.dir = 1;
	lcddev.pixsize = 2;
//			LTDC_PanelID_Read();
	printf("LCD ID:%#x\r\n", lcddev.id);
}

//清屏函数
//color:要清屏的填充色
void LCD_Clear(uint32_t color) {
	LCD_Rect_Fill(0, 0, lcddev.width - 1, lcddev.height - 1, color);
}

//Fill a specified area with a single color
//(sx,sy),(ex,ey): Coordinates of the diagonal corners of the filled rectangle. The area size is: (ex - sx + 1) * (ey - sy + 1)
//color: The color to be filled
void LCD_Rect_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color) {
	uint32_t psx, psy, pex, pey; //以LCD面板为基准的坐标系,不随横竖屏变化而变化
	uint32_t timeout = 0;
	uint16_t offline;
	uint32_t addr;


		psx = sx;
		psy = sy;
		pex = sx+ex-1;
		pey = sy+ey-1;

	offline = lcddev.width - (pex - psx + 1);
	addr = ((uint32_t) ltdc_lcd_framebuf + lcddev.pixsize * (lcddev.width * psy + psx));
	RCC->AHB1ENR |= 1 << 23;								//使能DM2D时钟
	DMA2D->CR = 3 << 16;									//寄存器到存储器模式
	DMA2D->OPFCCR = LTDC_PIXEL_FORMAT_RGB565;							//设置颜色格式
	DMA2D->OOR = offline;									//设置行偏移
	DMA2D->CR &= ~(1 << 0);									//先停止DMA2D
	DMA2D->OMAR = addr;										//输出存储器地址
	DMA2D->NLR = (pey - psy + 1) | ((pex - psx + 1) << 16); //设定行数寄存器
	DMA2D->OCOLR = color;									//设定输出颜色寄存器
	DMA2D->CR |= 1 << 0;									//启动DMA2D
	while ((DMA2D->ISR & (1 << 1)) == 0)					//等待传输完成
	{
		timeout++;
		if (timeout > 0X1FFFFF)
			break; //超时退出
	}
	DMA2D->IFCR |= 1 << 1; //清除传输完成标志
}

//在指定区域内填充指定颜色块
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)
//color:要填充的颜色
void LCD_Color_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color) {
	uint32_t psx, psy, pex, pey; //以LCD面板为基准的坐标系,不随横竖屏变化而变化
	uint32_t timeout = 0;
	uint16_t offline;
	uint32_t addr;
	//坐标系转换
	if (lcddev.dir) //横屏
	{
		psx = sx;
		psy = sy;
		pex = ex;
		pey = ey;
	} else //竖屏
	{
		psx = sy;
		psy = lcddev.height - ex - 1;
		pex = ey;
		pey = lcddev.height - sx - 1;
	}
	offline = lcddev.width - (pex - psx + 1);
	addr = ((uint32_t) ltdc_lcd_framebuf + lcddev.pixsize * (lcddev.width * psy + psx));
	__HAL_DMA2D_CLEAR_FLAG(&hdma2d, DMA2D_FLAG_TC);			//清除传输完成标志
	RCC->AHB1ENR |= 1 << 23;								//使能DM2D时钟
	DMA2D->CR &= ~(DMA2D_CR_START);							//先停止 DMA2D
	DMA2D->CR = DMA2D_M2M;									//存储器到存储器模式
	DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_RGB565;							//设置颜色格式
	DMA2D->FGOR = 0;										//前景层行偏移为0
	DMA2D->OOR = offline;									//设置行偏移
	DMA2D->CR &= ~(1 << 0);									//先停止DMA2D
	DMA2D->FGMAR = (uint32_t) color;								//源地址
	DMA2D->OMAR = addr;										//输出存储器地址
	DMA2D->NLR = (pey - psy + 1) | ((pex - psx + 1) << 16); //设定行数寄存器
	DMA2D->CR |= 1 << 0;									//启动DMA2D
	while ((DMA2D->ISR & (1 << 1)) == 0)					//等待传输完成
	{
		timeout++;
		if (timeout > 0X1FFFFF)
			break; //超时退出
	}
	DMA2D->IFCR |= 1 << 1; //清除传输完成标志
}

//画线
//x1,y1:起点坐标
//x2,y2:终点坐标
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	uint16_t t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2 - x1; //计算坐标增量
	delta_y = y2 - y1;
	uRow = x1;
	uCol = y1;
	if (delta_x > 0)
		incx = 1; //设置单步方向
	else if (delta_x == 0)
		incx = 0; //垂直线
	else {
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; //水平线
	else {
		incy = -1;
		delta_y = -delta_y;
	}
	if (delta_x > delta_y)
		distance = delta_x; //选取基本增量坐标轴
	else
		distance = delta_y;
	for (t = 0; t <= distance + 1; t++) //画线输出
			{
		LCD_DrawPoint(uRow, uCol); //画点
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance) {
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance) {
			yerr -= distance;
			uCol += incy;
		}
	}
}
//画矩形
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	LCD_DrawLine(x1, y1, x2, y1);
	LCD_DrawLine(x1, y1, x1, y2);
	LCD_DrawLine(x1, y2, x2, y2);
	LCD_DrawLine(x2, y1, x2, y2);
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r) {
	int a, b;
	int di;
	a = 0;
	b = r;
	di = 3 - (r << 1); //判断下个点位置的标志
	while (a <= b) {
		LCD_DrawPoint(x0 + a, y0 - b); //5
		LCD_DrawPoint(x0 + b, y0 - a); //0
		LCD_DrawPoint(x0 + b, y0 + a); //4
		LCD_DrawPoint(x0 + a, y0 + b); //6
		LCD_DrawPoint(x0 - a, y0 + b); //1
		LCD_DrawPoint(x0 - b, y0 + a);
		LCD_DrawPoint(x0 - a, y0 - b); //2
		LCD_DrawPoint(x0 - b, y0 - a); //7
		a++;
		//使用Bresenham算法画圆
		if (di < 0)
			di += 4 * a + 6;
		else {
			di += 10 + 4 * (a - b);
			b--;
		}
	}
}
//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24/32
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint8_t mode) {
	uint8_t temp, t1, t;
	uint16_t y0 = y;
	uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2); //得到字体一个字符对应点阵集所占的字节数
	num = num - ' ';                                           //得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for (t = 0; t < csize; t++) {
		if (size == 12)
			temp = asc2_1206[num][t]; //调用1206字体
		else if (size == 16)
			temp = asc2_1608[num][t]; //调用1608字体
		else if (size == 24)
			temp = asc2_2412[num][t]; //调用2412字体
		else if (size == 32)
			temp = asc2_3216[num][t]; //调用3216字体
		else
			return; //没有的字库
		for (t1 = 0; t1 < 8; t1++) {
			if (temp & 0x80)
				LTDC_Draw_Point(x, y, POINT_COLOR);
			else if (mode == 0)
				LTDC_Draw_Point(x, y, BACK_COLOR);
			temp <<= 1;
			y++;
			if (y >= lcddev.height)
				return; //超区域了
			if ((y - y0) == size) {
				y = y0;
				x++;
				if (x >= lcddev.width)
					return; //超区域了
				break;
			}
		}
	}
}
//m^n函数
//返回值:m^n次方.
uint32_t LCD_Pow(uint8_t m, uint8_t n) {
	uint32_t result = 1;
	while (n--)
		result *= m;
	return result;
}
//显示数字,高位为0,则不显示
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//color:颜色
//num:数值(0~4294967295);
void LCD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size) {
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++) {
		temp = (num / LCD_Pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1)) {
			if (temp == 0) {
				LCD_ShowChar(x + (size / 2) * t, y, ' ', size, 0);
				continue;
			} else
				enshow = 1;
		}
		LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, 0);
	}
}
//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode) {
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++) {
		temp = (num / LCD_Pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1)) {
			if (temp == 0) {
				if (mode & 0X80)
					LCD_ShowChar(x + (size / 2) * t, y, '0', size, mode & 0X01);
				else
					LCD_ShowChar(x + (size / 2) * t, y, ' ', size, mode & 0X01);
				continue;
			} else
				enshow = 1;
		}
		LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, mode & 0X01);
	}
}
//显示字符串
//x,y:起点坐标
//width,height:区域大小
//size:字体大小
//*p:字符串起始地址
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint8_t *p) {
	uint8_t x0 = x;
	width += x;
	height += y;
	while ((*p <= '~') && (*p >= ' ')) //判断是不是非法字符!
	{
		if (x >= width) {
			x = x0;
			y += size;
		}
		if (y >= height)
			break; //退出
		LCD_ShowChar(x, y, *p, size, 0);
		x += size / 2;
		p++;
	}
}






void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph, const GFXfont *font, uint8_t size, uint32_t color24)
{
	uint8_t  *bitmap = font -> bitmap;
	uint16_t bo = glyph -> bitmapOffset;
	uint8_t bits = 0, bit = 0;
	uint16_t set_pixels = 0;
	uint8_t  cur_x, cur_y;
	for (cur_y = 0; cur_y < glyph -> height; cur_y++)
	{
		for (cur_x = 0; cur_x < glyph -> width; cur_x++)
		{
			if (bit == 0)
			{
				bits = (*(const unsigned char *)(&bitmap[bo++]));
				bit  = 0x80;
			}
			if (bits & bit) set_pixels++;
			else if (set_pixels > 0)
			{
				LCD_Rect_Fill(x + (glyph -> yOffset + cur_x - set_pixels) * size, y + (glyph -> xOffset + cur_y) * size, size * set_pixels, size, color24);
				set_pixels = 0;
			}
			bit >>= 1;
		}
		if (set_pixels > 0)
		{
			LCD_Rect_Fill(x + (glyph -> yOffset + cur_x-set_pixels) * size, y + (glyph -> xOffset + cur_y) * size, size * set_pixels, size, color24);
			set_pixels = 0;
		}
	}
}

void LCD_Font(uint16_t x, uint16_t y, const char *text, const GFXfont *p_font, uint8_t size, uint32_t color24)
{
	int16_t cursor_x = x;
	int16_t cursor_y = y;
	GFXfont font;
	memcpy(&font, p_font, sizeof(GFXfont));
	for (uint16_t text_pos = 0; text_pos < strlen(text); text_pos++)
	{
		char c = text[text_pos];
		if (c == '\n')
		{
			cursor_x = x;
			cursor_y += font.yAdvance * size;
		}
		else if (c >= font.first && c <= font.last && c != '\r')
		{
			GFXglyph glyph;
			memcpy(&glyph, &font.glyph[c - font.first], sizeof(GFXglyph));
			LCD_Char(cursor_x, cursor_y, &glyph, &font, size, color24);
			cursor_x += glyph.xAdvance * size;
		}
	}
}

