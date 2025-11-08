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



void setup_scr_CHART_PAGE(lv_ui *ui)
{
    //Write codes CHART_PAGE
    ui->CHART_PAGE = lv_obj_create(NULL);
    lv_obj_set_size(ui->CHART_PAGE, 480, 320);
    lv_obj_set_scrollbar_mode(ui->CHART_PAGE, LV_SCROLLBAR_MODE_OFF);

    //Write style for CHART_PAGE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->CHART_PAGE, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->CHART_PAGE, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->CHART_PAGE, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes CHART_PAGE_UI_CHART
    ui->CHART_PAGE_UI_CHART = lv_chart_create(ui->CHART_PAGE);
    lv_chart_set_type(ui->CHART_PAGE_UI_CHART, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui->CHART_PAGE_UI_CHART, 30, 20);
    lv_chart_set_point_count(ui->CHART_PAGE_UI_CHART, 3);
    lv_chart_set_range(ui->CHART_PAGE_UI_CHART, LV_CHART_AXIS_PRIMARY_Y, 0, 30);
    lv_chart_set_axis_tick(ui->CHART_PAGE_UI_CHART, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 4, true, 30);
    lv_chart_set_range(ui->CHART_PAGE_UI_CHART, LV_CHART_AXIS_SECONDARY_Y, 0, 10);
    lv_chart_set_axis_tick(ui->CHART_PAGE_UI_CHART, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 4, true, 12);
    lv_chart_set_zoom_x(ui->CHART_PAGE_UI_CHART, 256);
    lv_chart_set_zoom_y(ui->CHART_PAGE_UI_CHART, 256);
    lv_obj_set_style_size(ui->CHART_PAGE_UI_CHART, 0, LV_PART_INDICATOR);
    ui->CHART_PAGE_UI_CHART_0 = lv_chart_add_series(ui->CHART_PAGE_UI_CHART, lv_color_hex(0x000000), LV_CHART_AXIS_PRIMARY_Y);
#if LV_USE_FREEMASTER == 0
    lv_chart_set_next_value(ui->CHART_PAGE_UI_CHART, ui->CHART_PAGE_UI_CHART_0, 0);
    lv_chart_set_next_value(ui->CHART_PAGE_UI_CHART, ui->CHART_PAGE_UI_CHART_0, 0);
    lv_chart_set_next_value(ui->CHART_PAGE_UI_CHART, ui->CHART_PAGE_UI_CHART_0, 0);
#endif
    ui->CHART_PAGE_UI_CHART_1 = lv_chart_add_series(ui->CHART_PAGE_UI_CHART, lv_color_hex(0x000000), LV_CHART_AXIS_SECONDARY_Y);
#if LV_USE_FREEMASTER == 0
    lv_chart_set_next_value(ui->CHART_PAGE_UI_CHART, ui->CHART_PAGE_UI_CHART_1, 0);
    lv_chart_set_next_value(ui->CHART_PAGE_UI_CHART, ui->CHART_PAGE_UI_CHART_1, 0);
    lv_chart_set_next_value(ui->CHART_PAGE_UI_CHART, ui->CHART_PAGE_UI_CHART_1, 0);
#endif
    lv_obj_set_pos(ui->CHART_PAGE_UI_CHART, 31, 12);
    lv_obj_set_size(ui->CHART_PAGE_UI_CHART, 400, 300);
    lv_obj_set_scrollbar_mode(ui->CHART_PAGE_UI_CHART, LV_SCROLLBAR_MODE_OFF);

    //Write style for CHART_PAGE_UI_CHART, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->CHART_PAGE_UI_CHART, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->CHART_PAGE_UI_CHART, lv_color_hex(0xf9f9f9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->CHART_PAGE_UI_CHART, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->CHART_PAGE_UI_CHART, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->CHART_PAGE_UI_CHART, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->CHART_PAGE_UI_CHART, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->CHART_PAGE_UI_CHART, lv_color_hex(0x999999), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->CHART_PAGE_UI_CHART, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->CHART_PAGE_UI_CHART, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for CHART_PAGE_UI_CHART, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->CHART_PAGE_UI_CHART, lv_color_hex(0x151212), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->CHART_PAGE_UI_CHART, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->CHART_PAGE_UI_CHART, 255, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->CHART_PAGE_UI_CHART, 2, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->CHART_PAGE_UI_CHART, lv_color_hex(0xe8e8e8), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->CHART_PAGE_UI_CHART, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write codes CHART_PAGE_BACK_CHART_BTU
    ui->CHART_PAGE_BACK_CHART_BTU = lv_btn_create(ui->CHART_PAGE);
    ui->CHART_PAGE_BACK_CHART_BTU_label = lv_label_create(ui->CHART_PAGE_BACK_CHART_BTU);
    lv_label_set_text(ui->CHART_PAGE_BACK_CHART_BTU_label, "BACK");
    lv_label_set_long_mode(ui->CHART_PAGE_BACK_CHART_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->CHART_PAGE_BACK_CHART_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->CHART_PAGE_BACK_CHART_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->CHART_PAGE_BACK_CHART_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->CHART_PAGE_BACK_CHART_BTU, 52, 18);
    lv_obj_set_size(ui->CHART_PAGE_BACK_CHART_BTU, 52, 27);

    //Write style for CHART_PAGE_BACK_CHART_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->CHART_PAGE_BACK_CHART_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->CHART_PAGE_BACK_CHART_BTU, lv_color_hex(0xa0983e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->CHART_PAGE_BACK_CHART_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->CHART_PAGE_BACK_CHART_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->CHART_PAGE_BACK_CHART_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->CHART_PAGE_BACK_CHART_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->CHART_PAGE_BACK_CHART_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->CHART_PAGE_BACK_CHART_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->CHART_PAGE_BACK_CHART_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->CHART_PAGE_BACK_CHART_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of CHART_PAGE.


    //Update current screen layout.
    lv_obj_update_layout(ui->CHART_PAGE);

    //Init events for screen.
    events_init_CHART_PAGE(ui);
}
