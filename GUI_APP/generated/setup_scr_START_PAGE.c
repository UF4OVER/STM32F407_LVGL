/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_START_PAGE(lv_ui *ui)
{
    //Write codes START_PAGE
    ui->START_PAGE = lv_obj_create(NULL);
    lv_obj_set_size(ui->START_PAGE, 480, 320);
    lv_obj_set_scrollbar_mode(ui->START_PAGE, LV_SCROLLBAR_MODE_OFF);

    //Write style for START_PAGE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->START_PAGE, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->START_PAGE, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->START_PAGE, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes START_PAGE_img_1
    ui->START_PAGE_img_1 = lv_img_create(ui->START_PAGE);
    lv_obj_add_flag(ui->START_PAGE_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->START_PAGE_img_1, &_Kang_Tao_Logo_02_CP2077_alpha_460x100);
    lv_img_set_pivot(ui->START_PAGE_img_1, 50,50);
    lv_img_set_angle(ui->START_PAGE_img_1, 0);
    lv_obj_set_pos(ui->START_PAGE_img_1, 11, 120);
    lv_obj_set_size(ui->START_PAGE_img_1, 460, 100);

    //Write style for START_PAGE_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->START_PAGE_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->START_PAGE_img_1, lv_color_hex(0xf79508), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->START_PAGE_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->START_PAGE_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->START_PAGE_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of START_PAGE.


    //Update current screen layout.
    lv_obj_update_layout(ui->START_PAGE);

    //Init events for screen.
    events_init_START_PAGE(ui);
}
