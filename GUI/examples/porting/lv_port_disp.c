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
#include "ST7796.h"
#include "PRINT.h"
/*********************
 *      DEFINES
 *********************/

#define MY_DISP_HOR_RES 320
#define MY_DISP_VER_RES 480

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
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    /**
     * LVGL 需要一个缓冲区，用于在内部绘制 widget。
     * 稍后，此缓冲区将传递给显示驱动程序的“flush_cb”，以将其内容复制到显示器。
     * 缓冲区必须大于 1 个显示行
     *
     * 有 3 种缓冲配置：
     * 1.创建一个缓冲区：
     * LVGL 将在此处绘制显示屏的内容并将其写入您的显示屏
     *
     * 2.创建 TWO 缓冲区：
     * LVGL 会将显示器的内容绘制到缓冲区并将其写入您的显示器。
     * 您应该使用 DMA 将缓冲区的内容写入显示器。
     * 它将使 LVGL 能够将屏幕的下一部分绘制到另一个缓冲区，同时
     * 数据正在从第一个缓冲区发送。它使渲染和刷新并行。
     *
     * 3.双缓冲
     * 设置 2 个屏幕大小的缓冲区并设置 disp_drv.full_refresh = 1。
     * 这样 LVGL 将始终以 'flush_cb' 提供整个渲染屏幕
     * 并且你只需要更改帧缓冲区的地址。
     */

    /* Example for 1) */
//    static lv_disp_draw_buf_t draw_buf_dsc_1;
//    static lv_color_t buf_1[MY_DISP_HOR_RES * 10];                          /*A buffer for 10 rows*/
//    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 10);   /*Initialize the display buffer*/

//    /* Example for 2) */
    static lv_disp_draw_buf_t draw_buf_dsc_2;
    static lv_color_t buf_2_1[MY_DISP_HOR_RES * 10];                        /*A buffer for 10 rows*/
    static lv_color_t buf_2_2[MY_DISP_HOR_RES * 10];                        /*An other buffer for 10 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * 10);   /*Initialize the display buffer*/

//    /* Example for 3) also set disp_drv.full_refresh = 1 below*/
//    static lv_disp_draw_buf_t draw_buf_dsc_3;
//    static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];            /*A screen sized buffer*/
//    static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];            /*Another screen sized buffer*/
//    lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2,
//                          MY_DISP_VER_RES * LV_VER_RES_MAX);   /*Initialize the display buffer*/

    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_2;

    /*Required for Example 3)*/
    //disp_drv.full_refresh = 1;

    /* 如果您有 GPU，请用颜色填充内存数组。
     * 请注意，在 lv_conf.h 中，您可以启用在 LVGL 中具有内置支持的 GPU。
     * 但是，如果你有不同的 GPU，则可以与此回调一起使用。*/
    //disp_drv.gpu_fill_cb = gpu_fill;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*初始化您的显示器和所需的外围设备.*/
static void disp_init(void)
{
    ST7796S_LcdInit();

}

volatile bool disp_flush_enabled = true;

/* 当 LVGL 调用 disp_flush（） 时启用更新屏幕（刷新过程）
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* 当 LVGL 调用 disp_flush（） 时禁用更新屏幕（刷新过程）
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*将内部缓冲区的内容刷新到显示屏上的特定区域
 *您可以使用 DMA 或任何硬件加速在后台执行此操作，但
 *完成后必须调用 lv_disp_flush_ready（）
 * */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{   Print_Printf("进入刷屏函数\n");
    if(!disp_flush_enabled) {
        lv_disp_flush_ready(disp_drv);
        return;
    }

    uint16_t x1 = area->x1;
    uint16_t y1 = area->y1;
    uint16_t x2 = area->x2;
    uint16_t y2 = area->y2;

    uint32_t size = (x2 - x1 + 1) * (y2 - y1 + 1);

    LCD_SetAddress(x1, y1, x2, y2);
    Print_Printf("进入刷屏 %d %d %d %d\n", x1, y1, x2, y2);
    LCD_PushColors_DMA(disp_drv, (uint16_t*)color_p, size);
    Print_Printf("刷屏完成\n");
}

/*OPTIONAL: GPU INTERFACE*/

/*如果您的 MCU 具有硬件加速器 （GPU），则可以使用它来用颜色填充内存*/
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//                    const lv_area_t * fill_area, lv_color_t color)
//{
//    /*这是一个示例代码，应该由您的 GPU 完成*/
//    int32_t x, y;
//    dest_buf += dest_width * fill_area->y1; /*转到第一行*/
//
//    for(y = fill_area->y1; y <= fill_area->y2; y++) {
//        for(x = fill_area->x1; x <= fill_area->x2; x++) {
//            dest_buf[x] = color;
//        }
//        dest_buf+=dest_width;    /*转到下一行*/
//    }
//}

#else /*Enable this file at the top*/

/*这个虚拟的 typedef 纯粹是为了沉默 -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
