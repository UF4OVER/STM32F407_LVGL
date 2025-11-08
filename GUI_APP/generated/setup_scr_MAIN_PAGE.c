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



void setup_scr_MAIN_PAGE(lv_ui *ui)
{
    //Write codes MAIN_PAGE
    ui->MAIN_PAGE = lv_obj_create(NULL);
    lv_obj_set_size(ui->MAIN_PAGE, 480, 320);
    lv_obj_set_scrollbar_mode(ui->MAIN_PAGE, LV_SCROLLBAR_MODE_OFF);

    //Write style for MAIN_PAGE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE, 252, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_cont_1
    ui->MAIN_PAGE_cont_1 = lv_obj_create(ui->MAIN_PAGE);
    lv_obj_set_pos(ui->MAIN_PAGE_cont_1, 10, 6);
    lv_obj_set_size(ui->MAIN_PAGE_cont_1, 460, 25);
    lv_obj_set_scrollbar_mode(ui->MAIN_PAGE_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for MAIN_PAGE_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_cont_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_NAME_INFO
    ui->MAIN_PAGE_NAME_INFO = lv_label_create(ui->MAIN_PAGE_cont_1);
    lv_label_set_text(ui->MAIN_PAGE_NAME_INFO, "UF4 POWER");
    lv_label_set_long_mode(ui->MAIN_PAGE_NAME_INFO, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_NAME_INFO, 3, 3);
    lv_obj_set_size(ui->MAIN_PAGE_NAME_INFO, 89, 20);

    //Write style for MAIN_PAGE_NAME_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_NAME_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_NAME_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_NAME_INFO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_NAME_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_HW_LABEL
    ui->MAIN_PAGE_HW_LABEL = lv_label_create(ui->MAIN_PAGE_cont_1);
    lv_label_set_text(ui->MAIN_PAGE_HW_LABEL, "1.00.002\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_HW_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_HW_LABEL, 380, 3);
    lv_obj_set_size(ui->MAIN_PAGE_HW_LABEL, 70, 20);

    //Write style for MAIN_PAGE_HW_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_HW_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_HW_LABEL, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_HW_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_HW_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_HW_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_46
    ui->MAIN_PAGE_label_46 = lv_label_create(ui->MAIN_PAGE_cont_1);
    lv_label_set_text(ui->MAIN_PAGE_label_46, "HWID:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_46, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_46, 316, 3);
    lv_obj_set_size(ui->MAIN_PAGE_label_46, 70, 20);

    //Write style for MAIN_PAGE_label_46, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_46, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_46, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_46, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_46, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_46, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_cont_3
    ui->MAIN_PAGE_cont_3 = lv_obj_create(ui->MAIN_PAGE);
    lv_obj_set_pos(ui->MAIN_PAGE_cont_3, 10, 38);
    lv_obj_set_size(ui->MAIN_PAGE_cont_3, 100, 60);
    lv_obj_set_scrollbar_mode(ui->MAIN_PAGE_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for MAIN_PAGE_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_cont_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_cont_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_AH_LABEL
    ui->MAIN_PAGE_AH_LABEL = lv_label_create(ui->MAIN_PAGE_cont_3);
    lv_label_set_text(ui->MAIN_PAGE_AH_LABEL, "0000.00");
    lv_label_set_long_mode(ui->MAIN_PAGE_AH_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_AH_LABEL, 2, 2);
    lv_obj_set_size(ui->MAIN_PAGE_AH_LABEL, 70, 20);

    //Write style for MAIN_PAGE_AH_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_AH_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_AH_LABEL, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_AH_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_AH_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_AH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_WH_LABEL
    ui->MAIN_PAGE_WH_LABEL = lv_label_create(ui->MAIN_PAGE_cont_3);
    lv_label_set_text(ui->MAIN_PAGE_WH_LABEL, "0000.00");
    lv_label_set_long_mode(ui->MAIN_PAGE_WH_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_WH_LABEL, 2, 20);
    lv_obj_set_size(ui->MAIN_PAGE_WH_LABEL, 70, 20);

    //Write style for MAIN_PAGE_WH_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_WH_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_WH_LABEL, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_WH_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_WH_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_WH_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_TM_LABEL
    ui->MAIN_PAGE_TM_LABEL = lv_label_create(ui->MAIN_PAGE_cont_3);
    lv_label_set_text(ui->MAIN_PAGE_TM_LABEL, "0000.00");
    lv_label_set_long_mode(ui->MAIN_PAGE_TM_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_TM_LABEL, 2, 38);
    lv_obj_set_size(ui->MAIN_PAGE_TM_LABEL, 70, 20);

    //Write style for MAIN_PAGE_TM_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_TM_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_TM_LABEL, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_TM_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_TM_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_TM_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_22
    ui->MAIN_PAGE_label_22 = lv_label_create(ui->MAIN_PAGE_cont_3);
    lv_label_set_text(ui->MAIN_PAGE_label_22, "AH");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_22, 71, 2);
    lv_obj_set_size(ui->MAIN_PAGE_label_22, 25, 20);

    //Write style for MAIN_PAGE_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_22, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_22, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_22, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_23
    ui->MAIN_PAGE_label_23 = lv_label_create(ui->MAIN_PAGE_cont_3);
    lv_label_set_text(ui->MAIN_PAGE_label_23, "WH");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_23, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_23, 71, 20);
    lv_obj_set_size(ui->MAIN_PAGE_label_23, 25, 20);

    //Write style for MAIN_PAGE_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_23, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_23, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_23, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_24
    ui->MAIN_PAGE_label_24 = lv_label_create(ui->MAIN_PAGE_cont_3);
    lv_label_set_text(ui->MAIN_PAGE_label_24, "TM");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_24, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_24, 70, 38);
    lv_obj_set_size(ui->MAIN_PAGE_label_24, 25, 20);

    //Write style for MAIN_PAGE_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_24, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_24, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_24, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_cont_5
    ui->MAIN_PAGE_cont_5 = lv_obj_create(ui->MAIN_PAGE);
    lv_obj_set_pos(ui->MAIN_PAGE_cont_5, 187, 290);
    lv_obj_set_size(ui->MAIN_PAGE_cont_5, 283, 20);
    lv_obj_set_scrollbar_mode(ui->MAIN_PAGE_cont_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for MAIN_PAGE_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_cont_5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_cont_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_CHART_BTU
    ui->MAIN_PAGE_CHART_BTU = lv_btn_create(ui->MAIN_PAGE);
    ui->MAIN_PAGE_CHART_BTU_label = lv_label_create(ui->MAIN_PAGE_CHART_BTU);
    lv_label_set_text(ui->MAIN_PAGE_CHART_BTU_label, "CHART");
    lv_label_set_long_mode(ui->MAIN_PAGE_CHART_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_CHART_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_CHART_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_CHART_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_CHART_BTU, 292, 109);
    lv_obj_set_size(ui->MAIN_PAGE_CHART_BTU, 70, 30);

    //Write style for MAIN_PAGE_CHART_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_CHART_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_CHART_BTU, lv_color_hex(0x66b73b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_CHART_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_CHART_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_CHART_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_CHART_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_CHART_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_CHART_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_CHART_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_CHART_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_FAN_BTU
    ui->MAIN_PAGE_FAN_BTU = lv_btn_create(ui->MAIN_PAGE);
    lv_obj_add_flag(ui->MAIN_PAGE_FAN_BTU, LV_OBJ_FLAG_CHECKABLE);
    ui->MAIN_PAGE_FAN_BTU_label = lv_label_create(ui->MAIN_PAGE_FAN_BTU);
    lv_label_set_text(ui->MAIN_PAGE_FAN_BTU_label, "FAN");
    lv_label_set_long_mode(ui->MAIN_PAGE_FAN_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_FAN_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_FAN_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_FAN_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_FAN_BTU, 187, 253);
    lv_obj_set_size(ui->MAIN_PAGE_FAN_BTU, 67, 30);

    //Write style for MAIN_PAGE_FAN_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_FAN_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_FAN_BTU, lv_color_hex(0x3bb790), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_FAN_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_FAN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_FAN_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_FAN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_FAN_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_FAN_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_FAN_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_FAN_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_MEUN_BTU
    ui->MAIN_PAGE_MEUN_BTU = lv_btn_create(ui->MAIN_PAGE);
    ui->MAIN_PAGE_MEUN_BTU_label = lv_label_create(ui->MAIN_PAGE_MEUN_BTU);
    lv_label_set_text(ui->MAIN_PAGE_MEUN_BTU_label, "MEUN");
    lv_label_set_long_mode(ui->MAIN_PAGE_MEUN_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_MEUN_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_MEUN_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_MEUN_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_MEUN_BTU, 258, 253);
    lv_obj_set_size(ui->MAIN_PAGE_MEUN_BTU, 67, 30);

    //Write style for MAIN_PAGE_MEUN_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_MEUN_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_MEUN_BTU, lv_color_hex(0x3b78b7), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_MEUN_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_MEUN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_MEUN_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_MEUN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_MEUN_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_MEUN_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_MEUN_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_MEUN_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_SET_BTU
    ui->MAIN_PAGE_SET_BTU = lv_btn_create(ui->MAIN_PAGE);
    ui->MAIN_PAGE_SET_BTU_label = lv_label_create(ui->MAIN_PAGE_SET_BTU);
    lv_label_set_text(ui->MAIN_PAGE_SET_BTU_label, "SET");
    lv_label_set_long_mode(ui->MAIN_PAGE_SET_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_SET_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_SET_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_SET_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_SET_BTU, 292, 72);
    lv_obj_set_size(ui->MAIN_PAGE_SET_BTU, 70, 30);

    //Write style for MAIN_PAGE_SET_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_SET_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_SET_BTU, lv_color_hex(0xb73b4e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_SET_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_SET_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_SET_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_SET_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_SET_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_SET_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_SET_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_SET_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_IMODE_LIST
    ui->MAIN_PAGE_IMODE_LIST = lv_dropdown_create(ui->MAIN_PAGE);
    lv_dropdown_set_options(ui->MAIN_PAGE_IMODE_LIST, "CC\nCV");
    lv_obj_set_pos(ui->MAIN_PAGE_IMODE_LIST, 350, 38);
    lv_obj_set_size(ui->MAIN_PAGE_IMODE_LIST, 55, 30);

    //Write style for MAIN_PAGE_IMODE_LIST, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MAIN_PAGE_IMODE_LIST, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_IMODE_LIST, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_IMODE_LIST, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_IMODE_LIST, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_IMODE_LIST, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_IMODE_LIST, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_IMODE_LIST, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_IMODE_LIST, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_IMODE_LIST, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_IMODE_LIST, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_IMODE_LIST, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_IMODE_LIST, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked
    static lv_style_t style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked;
    ui_init_style(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked);

    lv_style_set_border_width(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_PAGE_IMODE_LIST), &style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_MAIN_PAGE_IMODE_LIST_extra_list_main_default
    static lv_style_t style_MAIN_PAGE_IMODE_LIST_extra_list_main_default;
    ui_init_style(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default);

    lv_style_set_max_height(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, 90);
    lv_style_set_text_color(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, 255);
    lv_style_set_border_width(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, 255);
    lv_style_set_border_color(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_PAGE_IMODE_LIST), &style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default
    static lv_style_t style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default;
    ui_init_style(&style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default);

    lv_style_set_radius(&style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_PAGE_IMODE_LIST), &style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_MMODE_LIST
    ui->MAIN_PAGE_MMODE_LIST = lv_dropdown_create(ui->MAIN_PAGE);
    lv_dropdown_set_options(ui->MAIN_PAGE_MMODE_LIST, "DCM\nCCM");
    lv_obj_set_pos(ui->MAIN_PAGE_MMODE_LIST, 410, 38);
    lv_obj_set_size(ui->MAIN_PAGE_MMODE_LIST, 60, 30);

    //Write style for MAIN_PAGE_MMODE_LIST, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MAIN_PAGE_MMODE_LIST, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_MMODE_LIST, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_MMODE_LIST, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_MMODE_LIST, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_MMODE_LIST, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_MMODE_LIST, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_MMODE_LIST, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_MMODE_LIST, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_MMODE_LIST, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_MMODE_LIST, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_MMODE_LIST, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_MMODE_LIST, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked
    static lv_style_t style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked;
    ui_init_style(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked);

    lv_style_set_border_width(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, 3);
    lv_style_set_bg_opa(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, 255);
    lv_style_set_bg_color(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, lv_color_hex(0x00a1b5));
    lv_style_set_bg_grad_dir(&style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_PAGE_MMODE_LIST), &style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_MAIN_PAGE_MMODE_LIST_extra_list_main_default
    static lv_style_t style_MAIN_PAGE_MMODE_LIST_extra_list_main_default;
    ui_init_style(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default);

    lv_style_set_max_height(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, 90);
    lv_style_set_text_color(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, 255);
    lv_style_set_border_width(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, 255);
    lv_style_set_border_color(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, 3);
    lv_style_set_bg_opa(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, 255);
    lv_style_set_bg_color(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_PAGE_MMODE_LIST), &style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default
    static lv_style_t style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default;
    ui_init_style(&style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default);

    lv_style_set_radius(&style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default, 255);
    lv_style_set_bg_color(&style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
    lv_style_set_bg_grad_dir(&style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_PAGE_MMODE_LIST), &style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_START_BTU
    ui->MAIN_PAGE_START_BTU = lv_btn_create(ui->MAIN_PAGE);
    lv_obj_add_flag(ui->MAIN_PAGE_START_BTU, LV_OBJ_FLAG_CHECKABLE);
    ui->MAIN_PAGE_START_BTU_label = lv_label_create(ui->MAIN_PAGE_START_BTU);
    lv_label_set_text(ui->MAIN_PAGE_START_BTU_label, "START\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_START_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_START_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_START_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_START_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_START_BTU, 187, 38);
    lv_obj_set_size(ui->MAIN_PAGE_START_BTU, 75, 30);

    //Write style for MAIN_PAGE_START_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_START_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_START_BTU, lv_color_hex(0x66b73b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_START_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_START_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_START_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_START_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_START_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_START_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_START_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_START_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_COMP_BTU
    ui->MAIN_PAGE_COMP_BTU = lv_btn_create(ui->MAIN_PAGE);
    lv_obj_add_flag(ui->MAIN_PAGE_COMP_BTU, LV_OBJ_FLAG_CHECKABLE);
    ui->MAIN_PAGE_COMP_BTU_label = lv_label_create(ui->MAIN_PAGE_COMP_BTU);
    lv_label_set_text(ui->MAIN_PAGE_COMP_BTU_label, "COMP");
    lv_label_set_long_mode(ui->MAIN_PAGE_COMP_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_COMP_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_COMP_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_COMP_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_COMP_BTU, 270, 38);
    lv_obj_set_size(ui->MAIN_PAGE_COMP_BTU, 75, 30);

    //Write style for MAIN_PAGE_COMP_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_COMP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_COMP_BTU, lv_color_hex(0x66b73b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_COMP_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_COMP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_COMP_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_COMP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_COMP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_COMP_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_COMP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_COMP_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_cont_4
    ui->MAIN_PAGE_cont_4 = lv_obj_create(ui->MAIN_PAGE);
    lv_obj_set_pos(ui->MAIN_PAGE_cont_4, 10, 103);
    lv_obj_set_size(ui->MAIN_PAGE_cont_4, 170, 100);
    lv_obj_set_scrollbar_mode(ui->MAIN_PAGE_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for MAIN_PAGE_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_cont_4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_cont_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_2
    ui->MAIN_PAGE_label_2 = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_label_2, "IBUS:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_2, 5, 38);
    lv_obj_set_size(ui->MAIN_PAGE_label_2, 60, 25);

    //Write style for MAIN_PAGE_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_2, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_VBUS_LABEL
    ui->MAIN_PAGE_VBUS_LABEL = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_VBUS_LABEL, "00.00");
    lv_label_set_long_mode(ui->MAIN_PAGE_VBUS_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_VBUS_LABEL, 70, 5);
    lv_obj_set_size(ui->MAIN_PAGE_VBUS_LABEL, 60, 25);

    //Write style for MAIN_PAGE_VBUS_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_VBUS_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_VBUS_LABEL, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_VBUS_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_VBUS_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_VBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_3
    ui->MAIN_PAGE_label_3 = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_label_3, "PBUS:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_3, 5, 70);
    lv_obj_set_size(ui->MAIN_PAGE_label_3, 60, 25);

    //Write style for MAIN_PAGE_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_3, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_7
    ui->MAIN_PAGE_label_7 = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_label_7, "V\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_7, 130, 5);
    lv_obj_set_size(ui->MAIN_PAGE_label_7, 30, 25);

    //Write style for MAIN_PAGE_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_7, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_PBUS_LABEL
    ui->MAIN_PAGE_PBUS_LABEL = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_PBUS_LABEL, "00.00");
    lv_label_set_long_mode(ui->MAIN_PAGE_PBUS_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_PBUS_LABEL, 69, 70);
    lv_obj_set_size(ui->MAIN_PAGE_PBUS_LABEL, 60, 25);

    //Write style for MAIN_PAGE_PBUS_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_PBUS_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_PBUS_LABEL, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_PBUS_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_PBUS_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_PBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_8
    ui->MAIN_PAGE_label_8 = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_label_8, "A");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_8, 130, 38);
    lv_obj_set_size(ui->MAIN_PAGE_label_8, 30, 25);

    //Write style for MAIN_PAGE_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_8, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_IBUS_LABEL
    ui->MAIN_PAGE_IBUS_LABEL = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_IBUS_LABEL, "00.00\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_IBUS_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_IBUS_LABEL, 70, 37);
    lv_obj_set_size(ui->MAIN_PAGE_IBUS_LABEL, 60, 25);

    //Write style for MAIN_PAGE_IBUS_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_IBUS_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_IBUS_LABEL, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_IBUS_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_IBUS_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_IBUS_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_9
    ui->MAIN_PAGE_label_9 = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_label_9, "W\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_9, 130, 70);
    lv_obj_set_size(ui->MAIN_PAGE_label_9, 30, 25);

    //Write style for MAIN_PAGE_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_9, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_1
    ui->MAIN_PAGE_label_1 = lv_label_create(ui->MAIN_PAGE_cont_4);
    lv_label_set_text(ui->MAIN_PAGE_label_1, "VBUS:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_1, 5, 5);
    lv_obj_set_size(ui->MAIN_PAGE_label_1, 60, 25);

    //Write style for MAIN_PAGE_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_1, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_cont_6
    ui->MAIN_PAGE_cont_6 = lv_obj_create(ui->MAIN_PAGE);
    lv_obj_set_pos(ui->MAIN_PAGE_cont_6, 10, 210);
    lv_obj_set_size(ui->MAIN_PAGE_cont_6, 170, 100);
    lv_obj_set_scrollbar_mode(ui->MAIN_PAGE_cont_6, LV_SCROLLBAR_MODE_OFF);

    //Write style for MAIN_PAGE_cont_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_cont_6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_cont_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_cont_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_cont_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_33
    ui->MAIN_PAGE_label_33 = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_label_33, "IOUT:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_33, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_33, 5, 38);
    lv_obj_set_size(ui->MAIN_PAGE_label_33, 60, 25);

    //Write style for MAIN_PAGE_label_33, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_33, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_33, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_33, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_33, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_VOUT_LABEL
    ui->MAIN_PAGE_VOUT_LABEL = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_VOUT_LABEL, "00.00");
    lv_label_set_long_mode(ui->MAIN_PAGE_VOUT_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_VOUT_LABEL, 70, 5);
    lv_obj_set_size(ui->MAIN_PAGE_VOUT_LABEL, 60, 25);

    //Write style for MAIN_PAGE_VOUT_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_VOUT_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_VOUT_LABEL, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_VOUT_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_VOUT_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_VOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_31
    ui->MAIN_PAGE_label_31 = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_label_31, "POUT:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_31, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_31, 5, 70);
    lv_obj_set_size(ui->MAIN_PAGE_label_31, 60, 25);

    //Write style for MAIN_PAGE_label_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_31, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_31, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_31, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_30
    ui->MAIN_PAGE_label_30 = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_label_30, "V\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_30, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_30, 130, 5);
    lv_obj_set_size(ui->MAIN_PAGE_label_30, 30, 25);

    //Write style for MAIN_PAGE_label_30, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_30, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_30, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_30, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_30, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_POUT_LABEL
    ui->MAIN_PAGE_POUT_LABEL = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_POUT_LABEL, "00.00");
    lv_label_set_long_mode(ui->MAIN_PAGE_POUT_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_POUT_LABEL, 70, 70);
    lv_obj_set_size(ui->MAIN_PAGE_POUT_LABEL, 60, 25);

    //Write style for MAIN_PAGE_POUT_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_POUT_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_POUT_LABEL, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_POUT_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_POUT_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_POUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_28
    ui->MAIN_PAGE_label_28 = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_label_28, "A");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_28, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_28, 130, 38);
    lv_obj_set_size(ui->MAIN_PAGE_label_28, 30, 25);

    //Write style for MAIN_PAGE_label_28, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_28, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_28, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_28, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_28, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_IOUT_LABEL
    ui->MAIN_PAGE_IOUT_LABEL = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_IOUT_LABEL, "00.00\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_IOUT_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_IOUT_LABEL, 70, 38);
    lv_obj_set_size(ui->MAIN_PAGE_IOUT_LABEL, 60, 25);

    //Write style for MAIN_PAGE_IOUT_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_IOUT_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_IOUT_LABEL, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_IOUT_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_IOUT_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_IOUT_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_26
    ui->MAIN_PAGE_label_26 = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_label_26, "W\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_26, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_26, 130, 70);
    lv_obj_set_size(ui->MAIN_PAGE_label_26, 30, 25);

    //Write style for MAIN_PAGE_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_26, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_26, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_26, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_25
    ui->MAIN_PAGE_label_25 = lv_label_create(ui->MAIN_PAGE_cont_6);
    lv_label_set_text(ui->MAIN_PAGE_label_25, "VOUT:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_25, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_25, 5, 5);
    lv_obj_set_size(ui->MAIN_PAGE_label_25, 60, 25);

    //Write style for MAIN_PAGE_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_25, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_25, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_25, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_25, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_cont_7
    ui->MAIN_PAGE_cont_7 = lv_obj_create(ui->MAIN_PAGE);
    lv_obj_set_pos(ui->MAIN_PAGE_cont_7, 187, 145);
    lv_obj_set_size(ui->MAIN_PAGE_cont_7, 283, 100);
    lv_obj_set_scrollbar_mode(ui->MAIN_PAGE_cont_7, LV_SCROLLBAR_MODE_OFF);

    //Write style for MAIN_PAGE_cont_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_cont_7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_cont_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_cont_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_cont_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_IET_SPINBOX
    ui->MAIN_PAGE_IET_SPINBOX = lv_spinbox_create(ui->MAIN_PAGE_cont_7);
    lv_obj_set_pos(ui->MAIN_PAGE_IET_SPINBOX, 115, 50);
    lv_obj_set_width(ui->MAIN_PAGE_IET_SPINBOX, 70);
    lv_obj_set_height(ui->MAIN_PAGE_IET_SPINBOX, 40);
    lv_spinbox_set_digit_format(ui->MAIN_PAGE_IET_SPINBOX, 5, 3);
    lv_spinbox_set_range(ui->MAIN_PAGE_IET_SPINBOX, -99999, 99999);
    lv_coord_t MAIN_PAGE_IET_SPINBOX_h = lv_obj_get_height(ui->MAIN_PAGE_IET_SPINBOX);
    ui->MAIN_PAGE_IET_SPINBOX_btn_plus = lv_btn_create(ui->MAIN_PAGE_cont_7);
    lv_obj_set_size(ui->MAIN_PAGE_IET_SPINBOX_btn_plus, MAIN_PAGE_IET_SPINBOX_h, MAIN_PAGE_IET_SPINBOX_h);
    lv_obj_align_to(ui->MAIN_PAGE_IET_SPINBOX_btn_plus, ui->MAIN_PAGE_IET_SPINBOX, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->MAIN_PAGE_IET_SPINBOX_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->MAIN_PAGE_IET_SPINBOX_btn_plus, lv_MAIN_PAGE_IET_SPINBOX_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->MAIN_PAGE_IET_SPINBOX_btn_minus = lv_btn_create(ui->MAIN_PAGE_cont_7);
    lv_obj_set_size(ui->MAIN_PAGE_IET_SPINBOX_btn_minus, MAIN_PAGE_IET_SPINBOX_h, MAIN_PAGE_IET_SPINBOX_h);
    lv_obj_align_to(ui->MAIN_PAGE_IET_SPINBOX_btn_minus, ui->MAIN_PAGE_IET_SPINBOX, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->MAIN_PAGE_IET_SPINBOX_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->MAIN_PAGE_IET_SPINBOX_btn_minus, lv_MAIN_PAGE_IET_SPINBOX_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->MAIN_PAGE_IET_SPINBOX, 115, 50);

    //Write style for MAIN_PAGE_IET_SPINBOX, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_IET_SPINBOX, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_IET_SPINBOX, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_IET_SPINBOX, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_IET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MAIN_PAGE_IET_SPINBOX, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MAIN_PAGE_IET_SPINBOX, lv_color_hex(0x919191), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MAIN_PAGE_IET_SPINBOX, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_IET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_IET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_IET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_IET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_IET_SPINBOX, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_IET_SPINBOX, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_IET_SPINBOX, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_IET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_IET_SPINBOX, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_IET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for MAIN_PAGE_IET_SPINBOX, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MAIN_PAGE_IET_SPINBOX, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_IET_SPINBOX, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_IET_SPINBOX, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_IET_SPINBOX, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_IET_SPINBOX, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_IET_SPINBOX, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default
    static lv_style_t style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default;
    ui_init_style(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default);

    lv_style_set_text_color(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, 0);
    lv_style_set_radius(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, 0);
    lv_obj_add_style(ui->MAIN_PAGE_IET_SPINBOX_btn_plus, &style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->MAIN_PAGE_IET_SPINBOX_btn_minus, &style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_VET_SPINBOX
    ui->MAIN_PAGE_VET_SPINBOX = lv_spinbox_create(ui->MAIN_PAGE_cont_7);
    lv_obj_set_pos(ui->MAIN_PAGE_VET_SPINBOX, 115, 5);
    lv_obj_set_width(ui->MAIN_PAGE_VET_SPINBOX, 70);
    lv_obj_set_height(ui->MAIN_PAGE_VET_SPINBOX, 40);
    lv_spinbox_set_digit_format(ui->MAIN_PAGE_VET_SPINBOX, 5, 3);
    lv_spinbox_set_range(ui->MAIN_PAGE_VET_SPINBOX, -99999, 99999);
    lv_coord_t MAIN_PAGE_VET_SPINBOX_h = lv_obj_get_height(ui->MAIN_PAGE_VET_SPINBOX);
    ui->MAIN_PAGE_VET_SPINBOX_btn_plus = lv_btn_create(ui->MAIN_PAGE_cont_7);
    lv_obj_set_size(ui->MAIN_PAGE_VET_SPINBOX_btn_plus, MAIN_PAGE_VET_SPINBOX_h, MAIN_PAGE_VET_SPINBOX_h);
    lv_obj_align_to(ui->MAIN_PAGE_VET_SPINBOX_btn_plus, ui->MAIN_PAGE_VET_SPINBOX, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->MAIN_PAGE_VET_SPINBOX_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->MAIN_PAGE_VET_SPINBOX_btn_plus, lv_MAIN_PAGE_VET_SPINBOX_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->MAIN_PAGE_VET_SPINBOX_btn_minus = lv_btn_create(ui->MAIN_PAGE_cont_7);
    lv_obj_set_size(ui->MAIN_PAGE_VET_SPINBOX_btn_minus, MAIN_PAGE_VET_SPINBOX_h, MAIN_PAGE_VET_SPINBOX_h);
    lv_obj_align_to(ui->MAIN_PAGE_VET_SPINBOX_btn_minus, ui->MAIN_PAGE_VET_SPINBOX, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->MAIN_PAGE_VET_SPINBOX_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->MAIN_PAGE_VET_SPINBOX_btn_minus, lv_MAIN_PAGE_VET_SPINBOX_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->MAIN_PAGE_VET_SPINBOX, 115, 5);

    //Write style for MAIN_PAGE_VET_SPINBOX, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_VET_SPINBOX, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_VET_SPINBOX, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_VET_SPINBOX, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_VET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->MAIN_PAGE_VET_SPINBOX, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->MAIN_PAGE_VET_SPINBOX, lv_color_hex(0x8b8b8b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->MAIN_PAGE_VET_SPINBOX, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_VET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_VET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_VET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_VET_SPINBOX, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_VET_SPINBOX, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_VET_SPINBOX, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_VET_SPINBOX, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_VET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_VET_SPINBOX, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_VET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for MAIN_PAGE_VET_SPINBOX, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->MAIN_PAGE_VET_SPINBOX, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_VET_SPINBOX, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_VET_SPINBOX, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_VET_SPINBOX, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_VET_SPINBOX, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_VET_SPINBOX, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default
    static lv_style_t style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default;
    ui_init_style(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default);

    lv_style_set_text_color(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, 0);
    lv_style_set_radius(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, 0);
    lv_obj_add_style(ui->MAIN_PAGE_VET_SPINBOX_btn_plus, &style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->MAIN_PAGE_VET_SPINBOX_btn_minus, &style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_34
    ui->MAIN_PAGE_label_34 = lv_label_create(ui->MAIN_PAGE_cont_7);
    lv_label_set_text(ui->MAIN_PAGE_label_34, "VSET:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_34, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_34, 5, 10);
    lv_obj_set_size(ui->MAIN_PAGE_label_34, 60, 25);

    //Write style for MAIN_PAGE_label_34, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_34, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_34, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_34, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_34, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_34, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_35
    ui->MAIN_PAGE_label_35 = lv_label_create(ui->MAIN_PAGE_cont_7);
    lv_label_set_text(ui->MAIN_PAGE_label_35, "ISET:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_35, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_35, 5, 55);
    lv_obj_set_size(ui->MAIN_PAGE_label_35, 60, 25);

    //Write style for MAIN_PAGE_label_35, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_35, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_35, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_35, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_35, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_36
    ui->MAIN_PAGE_label_36 = lv_label_create(ui->MAIN_PAGE_cont_7);
    lv_label_set_text(ui->MAIN_PAGE_label_36, "V");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_36, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_36, 238, 10);
    lv_obj_set_size(ui->MAIN_PAGE_label_36, 25, 25);

    //Write style for MAIN_PAGE_label_36, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_36, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_36, &lv_font_blender_pro_bold_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_36, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_36, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_37
    ui->MAIN_PAGE_label_37 = lv_label_create(ui->MAIN_PAGE_cont_7);
    lv_label_set_text(ui->MAIN_PAGE_label_37, "A");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_37, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_37, 238, 55);
    lv_obj_set_size(ui->MAIN_PAGE_label_37, 25, 25);

    //Write style for MAIN_PAGE_label_37, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_37, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_37, &lv_font_blender_pro_bold_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_37, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_37, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_37, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_cont_8
    ui->MAIN_PAGE_cont_8 = lv_obj_create(ui->MAIN_PAGE);
    lv_obj_set_pos(ui->MAIN_PAGE_cont_8, 115, 38);
    lv_obj_set_size(ui->MAIN_PAGE_cont_8, 65, 60);
    lv_obj_set_scrollbar_mode(ui->MAIN_PAGE_cont_8, LV_SCROLLBAR_MODE_OFF);

    //Write style for MAIN_PAGE_cont_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_cont_8, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_cont_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_cont_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_cont_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_MCU_TEMP_LABEL
    ui->MAIN_PAGE_MCU_TEMP_LABEL = lv_label_create(ui->MAIN_PAGE_cont_8);
    lv_label_set_text(ui->MAIN_PAGE_MCU_TEMP_LABEL, "00.0");
    lv_label_set_long_mode(ui->MAIN_PAGE_MCU_TEMP_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_MCU_TEMP_LABEL, 27, 39);
    lv_obj_set_size(ui->MAIN_PAGE_MCU_TEMP_LABEL, 30, 15);

    //Write style for MAIN_PAGE_MCU_TEMP_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_MCU_TEMP_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_MCU_TEMP_LABEL, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_MCU_TEMP_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_MCU_TEMP_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_MCU_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_WIFIORBLE_LABEL
    ui->MAIN_PAGE_WIFIORBLE_LABEL = lv_label_create(ui->MAIN_PAGE_cont_8);
    lv_label_set_text(ui->MAIN_PAGE_WIFIORBLE_LABEL, "OFF");
    lv_label_set_long_mode(ui->MAIN_PAGE_WIFIORBLE_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_WIFIORBLE_LABEL, 27, 8);
    lv_obj_set_size(ui->MAIN_PAGE_WIFIORBLE_LABEL, 30, 15);

    //Write style for MAIN_PAGE_WIFIORBLE_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_WIFIORBLE_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_WIFIORBLE_LABEL, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_WIFIORBLE_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_WIFIORBLE_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_WIFIORBLE_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_40
    ui->MAIN_PAGE_label_40 = lv_label_create(ui->MAIN_PAGE);
    lv_label_set_text(ui->MAIN_PAGE_label_40, "FAN:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_40, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_40, 187, 290);
    lv_obj_set_size(ui->MAIN_PAGE_label_40, 40, 20);

    //Write style for MAIN_PAGE_label_40, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_40, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_40, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_40, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_40, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_FAN_LABEL
    ui->MAIN_PAGE_FAN_LABEL = lv_label_create(ui->MAIN_PAGE);
    lv_label_set_text(ui->MAIN_PAGE_FAN_LABEL, "0000");
    lv_label_set_long_mode(ui->MAIN_PAGE_FAN_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_FAN_LABEL, 227, 290);
    lv_obj_set_size(ui->MAIN_PAGE_FAN_LABEL, 40, 20);

    //Write style for MAIN_PAGE_FAN_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_FAN_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_FAN_LABEL, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_FAN_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_FAN_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_FAN_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_42
    ui->MAIN_PAGE_label_42 = lv_label_create(ui->MAIN_PAGE);
    lv_label_set_text(ui->MAIN_PAGE_label_42, "RPM");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_42, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_42, 267, 290);
    lv_obj_set_size(ui->MAIN_PAGE_label_42, 40, 20);

    //Write style for MAIN_PAGE_label_42, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_42, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_42, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_42, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_42, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_42, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_43
    ui->MAIN_PAGE_label_43 = lv_label_create(ui->MAIN_PAGE);
    lv_label_set_text(ui->MAIN_PAGE_label_43, "TEMP:");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_43, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_43, 357, 290);
    lv_obj_set_size(ui->MAIN_PAGE_label_43, 48, 20);

    //Write style for MAIN_PAGE_label_43, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_43, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_43, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_43, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_43, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_43, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_TEMP_LABEL
    ui->MAIN_PAGE_TEMP_LABEL = lv_label_create(ui->MAIN_PAGE);
    lv_label_set_text(ui->MAIN_PAGE_TEMP_LABEL, "00.0");
    lv_label_set_long_mode(ui->MAIN_PAGE_TEMP_LABEL, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_TEMP_LABEL, 405, 290);
    lv_obj_set_size(ui->MAIN_PAGE_TEMP_LABEL, 40, 20);

    //Write style for MAIN_PAGE_TEMP_LABEL, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_TEMP_LABEL, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_TEMP_LABEL, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_TEMP_LABEL, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_TEMP_LABEL, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_TEMP_LABEL, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_label_45
    ui->MAIN_PAGE_label_45 = lv_label_create(ui->MAIN_PAGE);
    lv_label_set_text(ui->MAIN_PAGE_label_45, "C");
    lv_label_set_long_mode(ui->MAIN_PAGE_label_45, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->MAIN_PAGE_label_45, 452, 290);
    lv_obj_set_size(ui->MAIN_PAGE_label_45, 13, 20);

    //Write style for MAIN_PAGE_label_45, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_label_45, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_label_45, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_label_45, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_label_45, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_label_45, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_OVP_BTU
    ui->MAIN_PAGE_OVP_BTU = lv_btn_create(ui->MAIN_PAGE);
    ui->MAIN_PAGE_OVP_BTU_label = lv_label_create(ui->MAIN_PAGE_OVP_BTU);
    lv_label_set_text(ui->MAIN_PAGE_OVP_BTU_label, "OVP: 00.00V\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_OVP_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_OVP_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_OVP_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_OVP_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_OVP_BTU, 187, 72);
    lv_obj_set_size(ui->MAIN_PAGE_OVP_BTU, 100, 30);

    //Write style for MAIN_PAGE_OVP_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_OVP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_OVP_BTU, lv_color_hex(0xacacac), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_OVP_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_OVP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_OVP_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_OVP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_OVP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_OVP_BTU, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_OVP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_OVP_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_OCP_BTU
    ui->MAIN_PAGE_OCP_BTU = lv_btn_create(ui->MAIN_PAGE);
    ui->MAIN_PAGE_OCP_BTU_label = lv_label_create(ui->MAIN_PAGE_OCP_BTU);
    lv_label_set_text(ui->MAIN_PAGE_OCP_BTU_label, "OCP: 00.00A\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_OCP_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_OCP_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_OCP_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_OCP_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_OCP_BTU, 187, 109);
    lv_obj_set_size(ui->MAIN_PAGE_OCP_BTU, 100, 30);

    //Write style for MAIN_PAGE_OCP_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_OCP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_OCP_BTU, lv_color_hex(0xacacac), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_OCP_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_OCP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_OCP_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_OCP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_OCP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_OCP_BTU, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_OCP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_OCP_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_VOLTM_BTU
    ui->MAIN_PAGE_VOLTM_BTU = lv_btn_create(ui->MAIN_PAGE);
    ui->MAIN_PAGE_VOLTM_BTU_label = lv_label_create(ui->MAIN_PAGE_VOLTM_BTU);
    lv_label_set_text(ui->MAIN_PAGE_VOLTM_BTU_label, "VOLTM\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_VOLTM_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_VOLTM_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_VOLTM_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_VOLTM_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_VOLTM_BTU, 410, 253);
    lv_obj_set_size(ui->MAIN_PAGE_VOLTM_BTU, 60, 30);

    //Write style for MAIN_PAGE_VOLTM_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_VOLTM_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_VOLTM_BTU, lv_color_hex(0xff4461), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_VOLTM_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_VOLTM_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_VOLTM_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_VOLTM_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_VOLTM_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_VOLTM_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_VOLTM_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_VOLTM_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_OSCILLO_BTU
    ui->MAIN_PAGE_OSCILLO_BTU = lv_btn_create(ui->MAIN_PAGE);
    ui->MAIN_PAGE_OSCILLO_BTU_label = lv_label_create(ui->MAIN_PAGE_OSCILLO_BTU);
    lv_label_set_text(ui->MAIN_PAGE_OSCILLO_BTU_label, "OSCILLO\n");
    lv_label_set_long_mode(ui->MAIN_PAGE_OSCILLO_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MAIN_PAGE_OSCILLO_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MAIN_PAGE_OSCILLO_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MAIN_PAGE_OSCILLO_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MAIN_PAGE_OSCILLO_BTU, 330, 253);
    lv_obj_set_size(ui->MAIN_PAGE_OSCILLO_BTU, 70, 30);

    //Write style for MAIN_PAGE_OSCILLO_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MAIN_PAGE_OSCILLO_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MAIN_PAGE_OSCILLO_BTU, lv_color_hex(0xe32dff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MAIN_PAGE_OSCILLO_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MAIN_PAGE_OSCILLO_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_OSCILLO_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MAIN_PAGE_OSCILLO_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MAIN_PAGE_OSCILLO_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MAIN_PAGE_OSCILLO_BTU, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MAIN_PAGE_OSCILLO_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MAIN_PAGE_OSCILLO_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_WIFIORBLE_IMG
    ui->MAIN_PAGE_WIFIORBLE_IMG = lv_img_create(ui->MAIN_PAGE);
    lv_obj_add_flag(ui->MAIN_PAGE_WIFIORBLE_IMG, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->MAIN_PAGE_WIFIORBLE_IMG, &_offline_24px_alpha_24x24);
    lv_img_set_pivot(ui->MAIN_PAGE_WIFIORBLE_IMG, 50,50);
    lv_img_set_angle(ui->MAIN_PAGE_WIFIORBLE_IMG, 0);
    lv_obj_set_pos(ui->MAIN_PAGE_WIFIORBLE_IMG, 115, 38);
    lv_obj_set_size(ui->MAIN_PAGE_WIFIORBLE_IMG, 24, 24);

    //Write style for MAIN_PAGE_WIFIORBLE_IMG, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->MAIN_PAGE_WIFIORBLE_IMG, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->MAIN_PAGE_WIFIORBLE_IMG, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->MAIN_PAGE_WIFIORBLE_IMG, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_WIFIORBLE_IMG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->MAIN_PAGE_WIFIORBLE_IMG, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MAIN_PAGE_TEMP_IMG
    ui->MAIN_PAGE_TEMP_IMG = lv_img_create(ui->MAIN_PAGE);
    lv_obj_add_flag(ui->MAIN_PAGE_TEMP_IMG, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->MAIN_PAGE_TEMP_IMG, &_temperature_24px_alpha_24x24);
    lv_img_set_pivot(ui->MAIN_PAGE_TEMP_IMG, 50,50);
    lv_img_set_angle(ui->MAIN_PAGE_TEMP_IMG, 0);
    lv_obj_set_pos(ui->MAIN_PAGE_TEMP_IMG, 115, 72);
    lv_obj_set_size(ui->MAIN_PAGE_TEMP_IMG, 24, 24);

    //Write style for MAIN_PAGE_TEMP_IMG, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->MAIN_PAGE_TEMP_IMG, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->MAIN_PAGE_TEMP_IMG, lv_color_hex(0x2e2e2e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->MAIN_PAGE_TEMP_IMG, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MAIN_PAGE_TEMP_IMG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->MAIN_PAGE_TEMP_IMG, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of MAIN_PAGE.


    //Update current screen layout.
    lv_obj_update_layout(ui->MAIN_PAGE);

    //Init events for screen.
    events_init_MAIN_PAGE(ui);
}
