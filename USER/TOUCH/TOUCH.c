#include "touch.h"
#include "math.h"

_m_tp_dev tp_dev = {
        TP_Init,
        FT6336_Scan,  // 初始化时直接赋值
        {0},
        {0},
        0,
};


uint8_t TP_Init(void)
{
    if(FT6336_Init())
    {
        return 1;
    }
    tp_dev.scan=FT6336_Scan;	//扫描函数指向GT911触摸屏扫描
    return 0;
}
