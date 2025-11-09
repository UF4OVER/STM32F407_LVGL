/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include <stdbool.h>
#include "H_ST7796.h"
/*********************
 *      DEFINES
 *********************/

#define MY_DISP_HOR_RES 480
#define MY_DISP_VER_RES 320

//#ifndef MY_DISP_HOR_RES
//    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
//    #define MY_DISP_HOR_RES    320
//#endif
//
//#ifndef MY_DISP_VER_RES
//    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen height, default value 240 is used for now.
//    #define MY_DISP_VER_RES    240
//#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//        const lv_area_t * fill_area, lv_color_t color);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{

    disp_init();

    __attribute__((section(".ccmram"))) static lv_disp_draw_buf_t draw_buf_dsc_2;
    __attribute__((section(".ccmram"))) static lv_color_t buf_2_1[MY_DISP_HOR_RES * 30];                        /*A buffer for 30 rows (was 10)*/
    __attribute__((section(".ccmram"))) static lv_color_t buf_2_2[MY_DISP_HOR_RES * 30];                        /*Another buffer for 30 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * 30);   /*初始化显示缓冲区*/

    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/


    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_2;

    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*初始化您的显示器和所需的外围设备.*/
static void disp_init(void)
{
   ST7796_Init();
   ST7796_Set_Rotation(SCREEN_HORIZONTAL_1);
}

volatile bool disp_flush_enabled = true;


void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p){
    uint16_t x1 = area->x1;
    uint16_t y1 = area->y1;
    uint16_t x2 = area->x2;
    uint16_t y2 = area->y2;

    uint32_t size = (x2-x1+1)*(y2-y1+1);
    ST7796_Set_Address(x1,y1,x2,y2);

    ST7796_PushColors((uint16_t*)color_p, size);
    lv_disp_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*这个虚拟的 typedef 纯粹是为了沉默 -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
