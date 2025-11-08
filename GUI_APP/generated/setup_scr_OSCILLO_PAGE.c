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



void setup_scr_OSCILLO_PAGE(lv_ui *ui)
{
    //Write codes OSCILLO_PAGE
    ui->OSCILLO_PAGE = lv_obj_create(NULL);
    lv_obj_set_size(ui->OSCILLO_PAGE, 480, 320);
    lv_obj_set_scrollbar_mode(ui->OSCILLO_PAGE, LV_SCROLLBAR_MODE_OFF);

    //Write style for OSCILLO_PAGE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_chart_1
    ui->OSCILLO_PAGE_chart_1 = lv_chart_create(ui->OSCILLO_PAGE);
    lv_chart_set_type(ui->OSCILLO_PAGE_chart_1, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui->OSCILLO_PAGE_chart_1, 30, 20);
    lv_chart_set_point_count(ui->OSCILLO_PAGE_chart_1, 5);
    lv_chart_set_range(ui->OSCILLO_PAGE_chart_1, LV_CHART_AXIS_PRIMARY_Y, 0, 30);
    lv_chart_set_range(ui->OSCILLO_PAGE_chart_1, LV_CHART_AXIS_SECONDARY_Y, 0, 10);
    lv_chart_set_zoom_x(ui->OSCILLO_PAGE_chart_1, 256);
    lv_chart_set_zoom_y(ui->OSCILLO_PAGE_chart_1, 256);
    lv_obj_set_style_size(ui->OSCILLO_PAGE_chart_1, 0, LV_PART_INDICATOR);
    lv_obj_set_pos(ui->OSCILLO_PAGE_chart_1, 0, 0);
    lv_obj_set_size(ui->OSCILLO_PAGE_chart_1, 360, 320);
    lv_obj_set_scrollbar_mode(ui->OSCILLO_PAGE_chart_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for OSCILLO_PAGE_chart_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_chart_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_chart_1, lv_color_hex(0xf9f9f9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_chart_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_chart_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->OSCILLO_PAGE_chart_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->OSCILLO_PAGE_chart_1, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->OSCILLO_PAGE_chart_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_chart_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->OSCILLO_PAGE_chart_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->OSCILLO_PAGE_chart_1, lv_color_hex(0x999999), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->OSCILLO_PAGE_chart_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_chart_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for OSCILLO_PAGE_chart_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_chart_1, lv_color_hex(0x151212), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_chart_1, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_chart_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->OSCILLO_PAGE_chart_1, 2, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->OSCILLO_PAGE_chart_1, lv_color_hex(0xe8e8e8), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->OSCILLO_PAGE_chart_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_cont_1
    ui->OSCILLO_PAGE_cont_1 = lv_obj_create(ui->OSCILLO_PAGE);
    lv_obj_set_pos(ui->OSCILLO_PAGE_cont_1, 370, 0);
    lv_obj_set_size(ui->OSCILLO_PAGE_cont_1, 100, 320);
    lv_obj_set_scrollbar_mode(ui->OSCILLO_PAGE_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for OSCILLO_PAGE_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->OSCILLO_PAGE_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->OSCILLO_PAGE_cont_1, lv_color_hex(0x535353), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->OSCILLO_PAGE_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_cont_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_BACK_OSCILLO_BTU
    ui->OSCILLO_PAGE_BACK_OSCILLO_BTU = lv_btn_create(ui->OSCILLO_PAGE_cont_1);
    ui->OSCILLO_PAGE_BACK_OSCILLO_BTU_label = lv_label_create(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU);
    lv_label_set_text(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU_label, "BACK");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, 5, 286);
    lv_obj_set_size(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, 50, 25);

    //Write style for OSCILLO_PAGE_BACK_OSCILLO_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, lv_color_hex(0xa0983e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_AUTO_BTU
    ui->OSCILLO_PAGE_AUTO_BTU = lv_btn_create(ui->OSCILLO_PAGE_cont_1);
    ui->OSCILLO_PAGE_AUTO_BTU_label = lv_label_create(ui->OSCILLO_PAGE_AUTO_BTU);
    lv_label_set_text(ui->OSCILLO_PAGE_AUTO_BTU_label, "AUTO");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_AUTO_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->OSCILLO_PAGE_AUTO_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->OSCILLO_PAGE_AUTO_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->OSCILLO_PAGE_AUTO_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->OSCILLO_PAGE_AUTO_BTU, 5, 133);
    lv_obj_set_size(ui->OSCILLO_PAGE_AUTO_BTU, 40, 27);

    //Write style for OSCILLO_PAGE_AUTO_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_AUTO_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_AUTO_BTU, lv_color_hex(0x53b947), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_AUTO_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_AUTO_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_AUTO_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_AUTO_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_AUTO_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_AUTO_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_AUTO_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_AUTO_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_RIGHT_BTU
    ui->OSCILLO_PAGE_RIGHT_BTU = lv_btn_create(ui->OSCILLO_PAGE_cont_1);
    ui->OSCILLO_PAGE_RIGHT_BTU_label = lv_label_create(ui->OSCILLO_PAGE_RIGHT_BTU);
    lv_label_set_text(ui->OSCILLO_PAGE_RIGHT_BTU_label, "RG");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_RIGHT_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->OSCILLO_PAGE_RIGHT_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->OSCILLO_PAGE_RIGHT_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->OSCILLO_PAGE_RIGHT_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->OSCILLO_PAGE_RIGHT_BTU, 5, 169);
    lv_obj_set_size(ui->OSCILLO_PAGE_RIGHT_BTU, 40, 25);

    //Write style for OSCILLO_PAGE_RIGHT_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_RIGHT_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_RIGHT_BTU, lv_color_hex(0x19bdda), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_RIGHT_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_RIGHT_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_RIGHT_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_RIGHT_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_RIGHT_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_RIGHT_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_RIGHT_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_RIGHT_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_LEFT_BTU
    ui->OSCILLO_PAGE_LEFT_BTU = lv_btn_create(ui->OSCILLO_PAGE_cont_1);
    ui->OSCILLO_PAGE_LEFT_BTU_label = lv_label_create(ui->OSCILLO_PAGE_LEFT_BTU);
    lv_label_set_text(ui->OSCILLO_PAGE_LEFT_BTU_label, "LF");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_LEFT_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->OSCILLO_PAGE_LEFT_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->OSCILLO_PAGE_LEFT_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->OSCILLO_PAGE_LEFT_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->OSCILLO_PAGE_LEFT_BTU, 5, 203);
    lv_obj_set_size(ui->OSCILLO_PAGE_LEFT_BTU, 40, 25);

    //Write style for OSCILLO_PAGE_LEFT_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_LEFT_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_LEFT_BTU, lv_color_hex(0x19bdda), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_LEFT_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_LEFT_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_LEFT_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_LEFT_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_LEFT_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_LEFT_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_LEFT_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_LEFT_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_DOWN_BTU
    ui->OSCILLO_PAGE_DOWN_BTU = lv_btn_create(ui->OSCILLO_PAGE_cont_1);
    ui->OSCILLO_PAGE_DOWN_BTU_label = lv_label_create(ui->OSCILLO_PAGE_DOWN_BTU);
    lv_label_set_text(ui->OSCILLO_PAGE_DOWN_BTU_label, "DO");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_DOWN_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->OSCILLO_PAGE_DOWN_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->OSCILLO_PAGE_DOWN_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->OSCILLO_PAGE_DOWN_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->OSCILLO_PAGE_DOWN_BTU, 51, 168);
    lv_obj_set_size(ui->OSCILLO_PAGE_DOWN_BTU, 40, 25);

    //Write style for OSCILLO_PAGE_DOWN_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_DOWN_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_DOWN_BTU, lv_color_hex(0x19bdda), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_DOWN_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_DOWN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_DOWN_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_DOWN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_DOWN_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_DOWN_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_DOWN_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_DOWN_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_UP_BTU
    ui->OSCILLO_PAGE_UP_BTU = lv_btn_create(ui->OSCILLO_PAGE_cont_1);
    ui->OSCILLO_PAGE_UP_BTU_label = lv_label_create(ui->OSCILLO_PAGE_UP_BTU);
    lv_label_set_text(ui->OSCILLO_PAGE_UP_BTU_label, "UP");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_UP_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->OSCILLO_PAGE_UP_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->OSCILLO_PAGE_UP_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->OSCILLO_PAGE_UP_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->OSCILLO_PAGE_UP_BTU, 51, 203);
    lv_obj_set_size(ui->OSCILLO_PAGE_UP_BTU, 40, 25);

    //Write style for OSCILLO_PAGE_UP_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_UP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_UP_BTU, lv_color_hex(0x19bdda), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_UP_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_UP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_UP_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_UP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_UP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_UP_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_UP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_UP_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_STOP_BTU
    ui->OSCILLO_PAGE_STOP_BTU = lv_btn_create(ui->OSCILLO_PAGE_cont_1);
    ui->OSCILLO_PAGE_STOP_BTU_label = lv_label_create(ui->OSCILLO_PAGE_STOP_BTU);
    lv_label_set_text(ui->OSCILLO_PAGE_STOP_BTU_label, "STOP");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_STOP_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->OSCILLO_PAGE_STOP_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->OSCILLO_PAGE_STOP_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->OSCILLO_PAGE_STOP_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->OSCILLO_PAGE_STOP_BTU, 51, 133);
    lv_obj_set_size(ui->OSCILLO_PAGE_STOP_BTU, 40, 27);

    //Write style for OSCILLO_PAGE_STOP_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_STOP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->OSCILLO_PAGE_STOP_BTU, lv_color_hex(0xff5871), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->OSCILLO_PAGE_STOP_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_STOP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_STOP_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_STOP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_STOP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_STOP_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_STOP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_STOP_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_2
    ui->OSCILLO_PAGE_label_2 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_2, "00.00");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_2, 34, 2);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_2, 40, 15);

    //Write style for OSCILLO_PAGE_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_2, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_3
    ui->OSCILLO_PAGE_label_3 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_3, "00.00");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_3, 34, 18);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_3, 40, 15);

    //Write style for OSCILLO_PAGE_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_3, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_5
    ui->OSCILLO_PAGE_label_5 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_5, "00.00");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_5, 34, 50);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_5, 40, 15);

    //Write style for OSCILLO_PAGE_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_5, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_4
    ui->OSCILLO_PAGE_label_4 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_4, "00.00");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_4, 34, 34);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_4, 40, 15);

    //Write style for OSCILLO_PAGE_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_4, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_7
    ui->OSCILLO_PAGE_label_7 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_7, "00.00");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_7, 34, 82);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_7, 40, 15);

    //Write style for OSCILLO_PAGE_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_7, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_6
    ui->OSCILLO_PAGE_label_6 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_6, "00.00");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_6, 34, 66);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_6, 40, 15);

    //Write style for OSCILLO_PAGE_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_6, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_8
    ui->OSCILLO_PAGE_label_8 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_8, "Amp:");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_8, -2, 50);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_8, 40, 15);

    //Write style for OSCILLO_PAGE_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_8, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_9
    ui->OSCILLO_PAGE_label_9 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_9, "Duty:");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_9, -2, 17);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_9, 40, 15);

    //Write style for OSCILLO_PAGE_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_9, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_10
    ui->OSCILLO_PAGE_label_10 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_10, "Freq:");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_10, -2, 2);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_10, 40, 15);

    //Write style for OSCILLO_PAGE_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_10, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_10, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_11
    ui->OSCILLO_PAGE_label_11 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_11, "Avg:");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_11, -2, 65);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_11, 40, 15);

    //Write style for OSCILLO_PAGE_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_11, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_11, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_12
    ui->OSCILLO_PAGE_label_12 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_12, "Vpp:");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_12, -2, 33);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_12, 40, 15);

    //Write style for OSCILLO_PAGE_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_12, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_12, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_13
    ui->OSCILLO_PAGE_label_13 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_13, "Vmin:");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_13, -2, 98);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_13, 40, 15);

    //Write style for OSCILLO_PAGE_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_13, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_13, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_14
    ui->OSCILLO_PAGE_label_14 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_14, "Vmax:");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_14, -2, 81);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_14, 40, 15);

    //Write style for OSCILLO_PAGE_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_14, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_14, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_15
    ui->OSCILLO_PAGE_label_15 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_15, "00.00");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_15, 34, 98);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_15, 40, 15);

    //Write style for OSCILLO_PAGE_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_15, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_15, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_15, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_16
    ui->OSCILLO_PAGE_label_16 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_16, "V");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_16, 79, 98);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_16, 15, 15);

    //Write style for OSCILLO_PAGE_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_16, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_16, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_16, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_17
    ui->OSCILLO_PAGE_label_17 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_17, "V");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_17, 79, 82);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_17, 15, 15);

    //Write style for OSCILLO_PAGE_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_17, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_17, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_17, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_19
    ui->OSCILLO_PAGE_label_19 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_19, "V");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_19, 79, 50);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_19, 15, 15);

    //Write style for OSCILLO_PAGE_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_19, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_19, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_19, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_18
    ui->OSCILLO_PAGE_label_18 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_18, "V");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_18, 79, 66);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_18, 15, 15);

    //Write style for OSCILLO_PAGE_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_18, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_18, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_18, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_21
    ui->OSCILLO_PAGE_label_21 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_21, "%");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_21, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_21, 79, 18);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_21, 15, 15);

    //Write style for OSCILLO_PAGE_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_21, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_21, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_21, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_20
    ui->OSCILLO_PAGE_label_20 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_20, "V");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_20, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_20, 79, 34);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_20, 15, 15);

    //Write style for OSCILLO_PAGE_label_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_20, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_20, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_20, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_label_22
    ui->OSCILLO_PAGE_label_22 = lv_label_create(ui->OSCILLO_PAGE_cont_1);
    lv_label_set_text(ui->OSCILLO_PAGE_label_22, "Hz");
    lv_label_set_long_mode(ui->OSCILLO_PAGE_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->OSCILLO_PAGE_label_22, 79, 2);
    lv_obj_set_size(ui->OSCILLO_PAGE_label_22, 15, 15);

    //Write style for OSCILLO_PAGE_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->OSCILLO_PAGE_label_22, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->OSCILLO_PAGE_label_22, &lv_font_blender_pro_bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->OSCILLO_PAGE_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->OSCILLO_PAGE_label_22, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->OSCILLO_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes OSCILLO_PAGE_line_1
    ui->OSCILLO_PAGE_line_1 = lv_line_create(ui->OSCILLO_PAGE);
    static lv_point_t OSCILLO_PAGE_line_1[] = {{0, 0},{96, 0},};
    lv_line_set_points(ui->OSCILLO_PAGE_line_1, OSCILLO_PAGE_line_1, 2);
    lv_obj_set_pos(ui->OSCILLO_PAGE_line_1, 373, 123);
    lv_obj_set_size(ui->OSCILLO_PAGE_line_1, 100, 2);

    //Write style for OSCILLO_PAGE_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->OSCILLO_PAGE_line_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->OSCILLO_PAGE_line_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->OSCILLO_PAGE_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->OSCILLO_PAGE_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of OSCILLO_PAGE.


    //Update current screen layout.
    lv_obj_update_layout(ui->OSCILLO_PAGE);

    //Init events for screen.
    events_init_OSCILLO_PAGE(ui);
}
