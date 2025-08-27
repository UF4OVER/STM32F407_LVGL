
#include "FT6336.h"
#include "TOUCH.h"
#include "string.h"
#include "ST7796.h"

extern uint8_t touch_flag;
extern I2C_HandleTypeDef hi2c1;

#define FT6336_I2C        hi2c1  // 替换为你的I2C句柄
#define FT6336_ADDR       0x38   // FT6336的I2C地址（7位地址，不含读写位）

uint8_t FT6336_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
    uint8_t data[len + 1];
    data[0] = reg & 0xFF;  // 寄存器地址（低8位）
    memcpy(&data[1], buf, len);  // 写入的数据

    // 使用HAL_I2C_Master_Transmit
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(
            &FT6336_I2C,          // I2C句柄（如hi2c1）
            FT6336_ADDR << 1,     // 设备地址（左移1位，HAL库自动处理读写位）
            data,                 // 数据缓冲区（地址+数据）
            len + 1,              // 数据长度（地址1字节 + 数据len字节）
            HAL_MAX_DELAY         // 超时时间（可自定义）
    );

    return (status == HAL_OK) ? 0 : 1;  // 成功返回0，失败返回1
}

void FT6336_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
    uint8_t reg_addr = reg & 0xFF;
    HAL_I2C_Master_Transmit(
            &FT6336_I2C,
            FT6336_ADDR << 1,
            &reg_addr,  // 寄存器地址
            1,          // 地址长度（1字节）
            HAL_MAX_DELAY
    );

    // 再读取数据（读模式）
    HAL_I2C_Master_Receive(
            &FT6336_I2C,
            FT6336_ADDR << 1 | 0x01,  // 读模式（地址 | 0x01）
            buf,                       // 数据缓冲区
            len,                       // 读取长度
            HAL_MAX_DELAY
    );
}

uint8_t FT6336_Init(void)
{
    uint8_t temp[2];

    FT_RST_OFF;				//复位
    HAL_Delay(10);
    FT_RST_ON;				//释放复位
    HAL_Delay(500);
    FT6336_RD_Reg(FT_ID_G_FOCALTECH_ID,&temp[0],1);
    if(temp[0]!=0x11)
    {
        return 1;
    }
    FT6336_RD_Reg(FT_ID_G_CIPHER_MID,&temp[0],2);
    if(temp[0]!=0x26)
    {
        return 1;
    }
    if((temp[1]!=0x00)&&(temp[1]!=0x01)&&(temp[1]!=0x02))
    {
        return 1;
    }
    FT6336_RD_Reg(FT_ID_G_CIPHER_HIGH,&temp[0],1);
    if(temp[0]!=0x64)
    {
        return 1;
    }
    return 0;
}

const uint16_t FT6336_TPX_TBL[2]={FT_TP1_REG,FT_TP2_REG};

uint8_t FT6336_Scan(void)
{
    uint8_t buf[4];
    uint8_t i=0;
    uint8_t res=0;
    uint8_t temp;
    uint8_t mode;
    static uint8_t t=0;//控制查询间隔,从而降低CPU占用率
    t++;
    if((t%10)==0||t<10)//空闲时,每进入10次CTP_Scan函数才检测1次,从而节省CPU使用率
    {
        FT6336_RD_Reg(FT_REG_NUM_FINGER,&mode,1);//读取触摸点的状态
        if(mode&&(mode<3))
        {
            temp=0XFF<<mode;//将点的个数转换为1的位数,匹配tp_dev.sta定义
            tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES;
            for(i=0;i<CTP_MAX_TOUCH;i++)
            {
                FT6336_RD_Reg(FT6336_TPX_TBL[i],buf,4);	//读取XY坐标值
                if(tp_dev.sta&(1<<i))	//触摸有效?
                {
                    switch(LCD_DIRECTION)
                    {
                        case 0:
                            tp_dev.x[i]=((uint16_t)(buf[0]&0X0F)<<8)+buf[1];
                            tp_dev.y[i]=((uint16_t)(buf[2]&0X0F)<<8)+buf[3];
                            break;
                        case 1:
                            tp_dev.y[i]=LcdSetting.height-(((uint16_t)(buf[0]&0X0F)<<8)+buf[1]);
                            tp_dev.x[i]=((uint16_t)(buf[2]&0X0F)<<8)+buf[3];
                            break;
                        case 2:
                            tp_dev.x[i]=LcdSetting.width-(((uint16_t)(buf[0]&0X0F)<<8)+buf[1]);
                            tp_dev.y[i]=LcdSetting.height-(((uint16_t)(buf[2]&0X0F)<<8)+buf[3]);
                            break;
                        case 3:
                            tp_dev.y[i]=((uint16_t)(buf[0]&0X0F)<<8)+buf[1];
                            tp_dev.x[i]=LcdSetting.width-(((uint16_t)(buf[2]&0X0F)<<8)+buf[3]);
                            break;
                    }
                }
            }
            res=1;
            if(tp_dev.x[0]==0 && tp_dev.y[0]==0)mode=0;	//读到的数据都是0,则忽略此次数据
            t=0;		//触发一次,则会最少连续监测10次,从而提高命中率
        }
    }
    if(mode==0)//无触摸点按下
    {
        if(tp_dev.sta&TP_PRES_DOWN)	//之前是被按下的
        {
            tp_dev.sta&=~(1<<7);	//标记按键松开
        }else						//之前就没有被按下
        {
            tp_dev.x[0]=0xffff;
            tp_dev.y[0]=0xffff;
            tp_dev.sta&=0XE0;	//清除点有效标记
        }
    }
    if(t>240)t=10;//重新从10开始计数
    return res;
}