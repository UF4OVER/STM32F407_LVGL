
#include "FT6336.h"
#include "stm32f4xx_hal.h"

#define TP_PRES_DOWN 0x80
#define TP_CATH_PRES 0x40

typedef struct
{
    uint8_t (*init)(void);
    uint8_t (*scan)(void);
    uint16_t x[CTP_MAX_TOUCH];
    uint16_t y[CTP_MAX_TOUCH];
    uint8_t  sta;
}_m_tp_dev;

extern _m_tp_dev tp_dev;

uint8_t TP_Init(void);
