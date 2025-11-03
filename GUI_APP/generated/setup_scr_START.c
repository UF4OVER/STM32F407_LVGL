/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
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


void setup_scr_START(lv_ui *ui)
{
	//Write codes START
	ui->START = lv_obj_create(NULL);
	lv_obj_set_size(ui->START, 480, 320);
	lv_obj_set_scrollbar_mode(ui->START, LV_SCROLLBAR_MODE_OFF);

	//Write style for START, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->START, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->START, lv_color_hex(0x0e0e0e), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes START_img_1
	ui->START_img_1 = lv_img_create(ui->START);
	lv_obj_add_flag(ui->START_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->START_img_1, &_4b2557acd3a9c3c4c0847bc3d36e804_alpha_450x150);
	lv_img_set_pivot(ui->START_img_1, 50,50);
	lv_img_set_angle(ui->START_img_1, 0);
	lv_obj_set_pos(ui->START_img_1, 15, 49);
	lv_obj_set_size(ui->START_img_1, 450, 150);
	lv_obj_set_scrollbar_mode(ui->START_img_1, LV_SCROLLBAR_MODE_OFF);
	//Update pos for widget START_img_1
	lv_obj_update_layout(ui->START_img_1);
	//Write animation: START_img_1 move in x direction
	lv_anim_t START_img_1_x;
	lv_anim_init(&START_img_1_x);
	lv_anim_set_var(&START_img_1_x, ui->START_img_1);
	lv_anim_set_time(&START_img_1_x, 1000);
	lv_anim_set_exec_cb(&START_img_1_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
	lv_anim_set_values(&START_img_1_x, lv_obj_get_x(ui->START_img_1), 15);
	lv_anim_set_path_cb(&START_img_1_x, lv_anim_path_linear);
	lv_anim_start(&START_img_1_x);
	//Write animation: START_img_1 move in y direction
	lv_anim_t START_img_1_y;
	lv_anim_init(&START_img_1_y);
	lv_anim_set_var(&START_img_1_y, ui->START_img_1);
	lv_anim_set_time(&START_img_1_y, 1000);
	lv_anim_set_exec_cb(&START_img_1_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
	lv_anim_set_values(&START_img_1_y, lv_obj_get_y(ui->START_img_1), 200);
	lv_anim_set_path_cb(&START_img_1_y, lv_anim_path_linear);
	lv_anim_start(&START_img_1_y);

	//Write style for START_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->START_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes START_start_label
	ui->START_start_label = lv_label_create(ui->START);
	lv_label_set_text(ui->START_start_label, "The Device is Collecting Hardware Packets....");
	lv_label_set_long_mode(ui->START_start_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->START_start_label, 31, 216);
	lv_obj_set_size(ui->START_start_label, 419, 32);
	lv_obj_set_scrollbar_mode(ui->START_start_label, LV_SCROLLBAR_MODE_OFF);

	//Write style for START_start_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->START_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->START_start_label, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->START_start_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->START_start_label, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->START_start_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->START_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->START_start_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->START_start_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->START_start_label, lv_color_hex(0xa1511c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->START_start_label, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->START_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->START_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->START_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->START_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->START);

	
	//Init events for screen.
	events_init_START(ui);
}
