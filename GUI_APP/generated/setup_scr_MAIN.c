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



lv_obj_t * MAIN_ISET_SPINBOX;
lv_obj_t * MAIN_VSET_SPINBOX;void setup_scr_MAIN(lv_ui *ui)
{
	//Write codes MAIN
	ui->MAIN = lv_obj_create(NULL);
	lv_obj_set_size(ui->MAIN, 480, 320);
	lv_obj_set_scrollbar_mode(ui->MAIN, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN, lv_color_hex(0x8e8e8e), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_ILIMMODE_LIST
	ui->MAIN_ILIMMODE_LIST = lv_dropdown_create(ui->MAIN);
	lv_dropdown_set_options(ui->MAIN_ILIMMODE_LIST, "CC\nCV");
	lv_obj_set_pos(ui->MAIN_ILIMMODE_LIST, 340, 113);
	lv_obj_set_size(ui->MAIN_ILIMMODE_LIST, 68, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_ILIMMODE_LIST, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_ILIMMODE_LIST, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->MAIN_ILIMMODE_LIST, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_ILIMMODE_LIST, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_ILIMMODE_LIST, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_ILIMMODE_LIST, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_ILIMMODE_LIST, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_ILIMMODE_LIST, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_ILIMMODE_LIST, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_ILIMMODE_LIST, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_ILIMMODE_LIST, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_ILIMMODE_LIST, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_MAIN_ILIMMODE_LIST_extra_list_selected_checked
	static lv_style_t style_MAIN_ILIMMODE_LIST_extra_list_selected_checked;
	ui_init_style(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked);
	
	lv_style_set_text_color(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, &lv_font_montserratMedium_12);
	lv_style_set_border_width(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
	lv_style_set_radius(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, 3);
	lv_style_set_bg_opa(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, 255);
	lv_style_set_bg_color(&style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, lv_color_hex(0x00a1b5));
	lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_ILIMMODE_LIST), &style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_MAIN_ILIMMODE_LIST_extra_list_main_default
	static lv_style_t style_MAIN_ILIMMODE_LIST_extra_list_main_default;
	ui_init_style(&style_MAIN_ILIMMODE_LIST_extra_list_main_default);
	
	lv_style_set_max_height(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, 90);
	lv_style_set_text_color(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, &lv_font_montserratMedium_12);
	lv_style_set_border_width(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, 255);
	lv_style_set_border_color(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_radius(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, 3);
	lv_style_set_bg_opa(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, 255);
	lv_style_set_bg_color(&style_MAIN_ILIMMODE_LIST_extra_list_main_default, lv_color_hex(0xffffff));
	lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_ILIMMODE_LIST), &style_MAIN_ILIMMODE_LIST_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default
	static lv_style_t style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default;
	ui_init_style(&style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default);
	
	lv_style_set_radius(&style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default, 255);
	lv_style_set_bg_color(&style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
	lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_ILIMMODE_LIST), &style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes MAIN_cont_1
	ui->MAIN_cont_1 = lv_obj_create(ui->MAIN);
	lv_obj_set_pos(ui->MAIN_cont_1, 5, 5);
	lv_obj_set_size(ui->MAIN_cont_1, 470, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_cont_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_cont_1, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_NAME_INFO
	ui->MAIN_NAME_INFO = lv_label_create(ui->MAIN_cont_1);
	lv_label_set_text(ui->MAIN_NAME_INFO, "UF4OVER POWER");
	lv_label_set_long_mode(ui->MAIN_NAME_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_NAME_INFO, 3, 5);
	lv_obj_set_size(ui->MAIN_NAME_INFO, 150, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_NAME_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_NAME_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_NAME_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_NAME_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_NAME_INFO, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_NAME_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_NAME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_2
	ui->MAIN_label_2 = lv_label_create(ui->MAIN_cont_1);
	lv_label_set_text(ui->MAIN_label_2, "FW:");
	lv_label_set_long_mode(ui->MAIN_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_2, 345, 5);
	lv_obj_set_size(ui->MAIN_label_2, 36, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_2, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_HW_INFO
	ui->MAIN_HW_INFO = lv_label_create(ui->MAIN_cont_1);
	lv_label_set_text(ui->MAIN_HW_INFO, "1.41.120");
	lv_label_set_long_mode(ui->MAIN_HW_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_HW_INFO, 387, 5);
	lv_obj_set_size(ui->MAIN_HW_INFO, 70, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_HW_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_HW_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_HW_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_HW_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_HW_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_HW_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_cont_2
	ui->MAIN_cont_2 = lv_obj_create(ui->MAIN);
	lv_obj_set_pos(ui->MAIN_cont_2, 5, 42);
	lv_obj_set_size(ui->MAIN_cont_2, 180, 100);
	lv_obj_set_scrollbar_mode(ui->MAIN_cont_2, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_cont_2, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_cont_2, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_6
	ui->MAIN_label_6 = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_label_6, "VBUS:");
	lv_label_set_long_mode(ui->MAIN_label_6, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_6, 5, 0);
	lv_obj_set_size(ui->MAIN_label_6, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_6, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_6, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_VBUS_INFO
	ui->MAIN_VBUS_INFO = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_VBUS_INFO, "00.00");
	lv_label_set_long_mode(ui->MAIN_VBUS_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_VBUS_INFO, 75, 0);
	lv_obj_set_size(ui->MAIN_VBUS_INFO, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_VBUS_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_VBUS_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_VBUS_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_VBUS_INFO, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_VBUS_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_VBUS_INFO, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_VBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_8
	ui->MAIN_label_8 = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_label_8, "IBUS:");
	lv_label_set_long_mode(ui->MAIN_label_8, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_8, 5, 32);
	lv_obj_set_size(ui->MAIN_label_8, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_8, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_8, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_8, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_IBUS_INFO
	ui->MAIN_IBUS_INFO = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_IBUS_INFO, "00.00");
	lv_label_set_long_mode(ui->MAIN_IBUS_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_IBUS_INFO, 75, 32);
	lv_obj_set_size(ui->MAIN_IBUS_INFO, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_IBUS_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_IBUS_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_IBUS_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_IBUS_INFO, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_IBUS_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_IBUS_INFO, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_IBUS_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_10
	ui->MAIN_label_10 = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_label_10, "V");
	lv_label_set_long_mode(ui->MAIN_label_10, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_10, 150, 0);
	lv_obj_set_size(ui->MAIN_label_10, 30, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_10, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_10, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_10, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_10, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_11
	ui->MAIN_label_11 = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_label_11, "A");
	lv_label_set_long_mode(ui->MAIN_label_11, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_11, 150, 32);
	lv_obj_set_size(ui->MAIN_label_11, 30, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_11, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_11, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_11, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_11, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_12
	ui->MAIN_label_12 = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_label_12, "PBUS:");
	lv_label_set_long_mode(ui->MAIN_label_12, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_12, 5, 65);
	lv_obj_set_size(ui->MAIN_label_12, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_12, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_12, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_12, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_12, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_PBUS__INFO
	ui->MAIN_PBUS__INFO = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_PBUS__INFO, "00.00");
	lv_label_set_long_mode(ui->MAIN_PBUS__INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_PBUS__INFO, 75, 65);
	lv_obj_set_size(ui->MAIN_PBUS__INFO, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_PBUS__INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_PBUS__INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_PBUS__INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_PBUS__INFO, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_PBUS__INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_PBUS__INFO, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_PBUS__INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_14
	ui->MAIN_label_14 = lv_label_create(ui->MAIN_cont_2);
	lv_label_set_text(ui->MAIN_label_14, "W");
	lv_label_set_long_mode(ui->MAIN_label_14, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_14, 150, 65);
	lv_obj_set_size(ui->MAIN_label_14, 30, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_14, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_14, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_14, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_14, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_cont_3
	ui->MAIN_cont_3 = lv_obj_create(ui->MAIN);
	lv_obj_set_pos(ui->MAIN_cont_3, 5, 150);
	lv_obj_set_size(ui->MAIN_cont_3, 180, 100);
	lv_obj_set_scrollbar_mode(ui->MAIN_cont_3, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_cont_3, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_cont_3, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_23
	ui->MAIN_label_23 = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_label_23, "VOUT:");
	lv_label_set_long_mode(ui->MAIN_label_23, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_23, 5, 0);
	lv_obj_set_size(ui->MAIN_label_23, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_23, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_23, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_23, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_23, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_23, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_VOUT_INFO
	ui->MAIN_VOUT_INFO = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_VOUT_INFO, "00.00");
	lv_label_set_long_mode(ui->MAIN_VOUT_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_VOUT_INFO, 75, 0);
	lv_obj_set_size(ui->MAIN_VOUT_INFO, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_VOUT_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_VOUT_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_VOUT_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_VOUT_INFO, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_VOUT_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_VOUT_INFO, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_VOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_21
	ui->MAIN_label_21 = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_label_21, "IOUT:");
	lv_label_set_long_mode(ui->MAIN_label_21, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_21, 5, 32);
	lv_obj_set_size(ui->MAIN_label_21, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_21, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_21, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_21, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_21, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_21, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_IOUT_INFO
	ui->MAIN_IOUT_INFO = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_IOUT_INFO, "00.00");
	lv_label_set_long_mode(ui->MAIN_IOUT_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_IOUT_INFO, 75, 32);
	lv_obj_set_size(ui->MAIN_IOUT_INFO, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_IOUT_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_IOUT_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_IOUT_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_IOUT_INFO, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_IOUT_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_IOUT_INFO, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_IOUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_19
	ui->MAIN_label_19 = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_label_19, "V");
	lv_label_set_long_mode(ui->MAIN_label_19, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_19, 150, 0);
	lv_obj_set_size(ui->MAIN_label_19, 30, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_19, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_19, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_19, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_19, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_19, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_18
	ui->MAIN_label_18 = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_label_18, "A");
	lv_label_set_long_mode(ui->MAIN_label_18, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_18, 150, 32);
	lv_obj_set_size(ui->MAIN_label_18, 30, 32);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_18, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_18, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_18, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_18, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_18, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_17
	ui->MAIN_label_17 = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_label_17, "POUT:");
	lv_label_set_long_mode(ui->MAIN_label_17, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_17, 5, 65);
	lv_obj_set_size(ui->MAIN_label_17, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_17, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_17, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_17, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_17, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_17, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_POUT_INFO
	ui->MAIN_POUT_INFO = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_POUT_INFO, "00.00");
	lv_label_set_long_mode(ui->MAIN_POUT_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_POUT_INFO, 75, 65);
	lv_obj_set_size(ui->MAIN_POUT_INFO, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_POUT_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_POUT_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_POUT_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_POUT_INFO, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_POUT_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_POUT_INFO, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_POUT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_15
	ui->MAIN_label_15 = lv_label_create(ui->MAIN_cont_3);
	lv_label_set_text(ui->MAIN_label_15, "W");
	lv_label_set_long_mode(ui->MAIN_label_15, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_15, 150, 65);
	lv_obj_set_size(ui->MAIN_label_15, 30, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_15, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_15, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_15, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_15, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_15, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_cont_4
	ui->MAIN_cont_4 = lv_obj_create(ui->MAIN);
	lv_obj_set_pos(ui->MAIN_cont_4, 205, 150);
	lv_obj_set_size(ui->MAIN_cont_4, 270, 102);
	lv_obj_set_scrollbar_mode(ui->MAIN_cont_4, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_cont_4, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_cont_4, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_ISET_SPINBOX
	ui->MAIN_ISET_SPINBOX = lv_spinbox_create(ui->MAIN_cont_4);
	lv_obj_set_pos(ui->MAIN_ISET_SPINBOX, 137, 56);
	lv_obj_set_width(ui->MAIN_ISET_SPINBOX, 70);
	lv_obj_set_height(ui->MAIN_ISET_SPINBOX, 40);
	lv_spinbox_set_digit_format(ui->MAIN_ISET_SPINBOX, 4, 2);
	lv_spinbox_set_range(ui->MAIN_ISET_SPINBOX, -9999, 9999);
	MAIN_ISET_SPINBOX = ui->MAIN_ISET_SPINBOX;
	lv_coord_t MAIN_ISET_SPINBOX_h = lv_obj_get_height(ui->MAIN_ISET_SPINBOX);
	ui->MAIN_ISET_SPINBOX_btn = lv_btn_create(ui->MAIN_cont_4);
	lv_obj_set_size(ui->MAIN_ISET_SPINBOX_btn, MAIN_ISET_SPINBOX_h, MAIN_ISET_SPINBOX_h);
	lv_obj_align_to(ui->MAIN_ISET_SPINBOX_btn, ui->MAIN_ISET_SPINBOX, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
	lv_obj_set_style_bg_img_src(ui->MAIN_ISET_SPINBOX_btn, LV_SYMBOL_PLUS, 0);
	lv_obj_add_event_cb(ui->MAIN_ISET_SPINBOX_btn, lv_MAIN_ISET_SPINBOX_increment_event_cb, LV_EVENT_ALL, NULL);
	ui->MAIN_ISET_SPINBOX_btn_minus = lv_btn_create(ui->MAIN_cont_4);
	lv_obj_set_size(ui->MAIN_ISET_SPINBOX_btn_minus, MAIN_ISET_SPINBOX_h, MAIN_ISET_SPINBOX_h);
	lv_obj_align_to(ui->MAIN_ISET_SPINBOX_btn_minus, ui->MAIN_ISET_SPINBOX, LV_ALIGN_OUT_LEFT_MID, -5, 0);
	lv_obj_set_style_bg_img_src(ui->MAIN_ISET_SPINBOX_btn_minus, LV_SYMBOL_MINUS, 0);
	lv_obj_add_event_cb(ui->MAIN_ISET_SPINBOX_btn_minus, lv_MAIN_ISET_SPINBOX_decrement_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(ui->MAIN_ISET_SPINBOX, 137, 56);
	lv_obj_set_scrollbar_mode(ui->MAIN_ISET_SPINBOX, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_ISET_SPINBOX, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_ISET_SPINBOX, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_ISET_SPINBOX, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_ISET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_ISET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_ISET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_ISET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_ISET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_ISET_SPINBOX, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_ISET_SPINBOX, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_ISET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_ISET_SPINBOX, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_ISET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for MAIN_ISET_SPINBOX, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->MAIN_ISET_SPINBOX, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_ISET_SPINBOX, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_ISET_SPINBOX, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_ISET_SPINBOX, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_MAIN_ISET_SPINBOX_extra_btns_main_default
	static lv_style_t style_MAIN_ISET_SPINBOX_extra_btns_main_default;
	ui_init_style(&style_MAIN_ISET_SPINBOX_extra_btns_main_default);
	
	lv_style_set_text_color(&style_MAIN_ISET_SPINBOX_extra_btns_main_default, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_MAIN_ISET_SPINBOX_extra_btns_main_default, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_MAIN_ISET_SPINBOX_extra_btns_main_default, 255);
	lv_style_set_bg_color(&style_MAIN_ISET_SPINBOX_extra_btns_main_default, lv_color_hex(0x2195f6));
	lv_style_set_border_width(&style_MAIN_ISET_SPINBOX_extra_btns_main_default, 0);
	lv_style_set_radius(&style_MAIN_ISET_SPINBOX_extra_btns_main_default, 5);
	lv_obj_add_style(ui->MAIN_ISET_SPINBOX_btn, &style_MAIN_ISET_SPINBOX_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->MAIN_ISET_SPINBOX_btn_minus, &style_MAIN_ISET_SPINBOX_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_VSET_SPINBOX
	ui->MAIN_VSET_SPINBOX = lv_spinbox_create(ui->MAIN_cont_4);
	lv_obj_set_pos(ui->MAIN_VSET_SPINBOX, 137, 8);
	lv_obj_set_width(ui->MAIN_VSET_SPINBOX, 70);
	lv_obj_set_height(ui->MAIN_VSET_SPINBOX, 40);
	lv_spinbox_set_digit_format(ui->MAIN_VSET_SPINBOX, 4, 2);
	lv_spinbox_set_range(ui->MAIN_VSET_SPINBOX, -9999, 9999);
	MAIN_VSET_SPINBOX = ui->MAIN_VSET_SPINBOX;
	lv_coord_t MAIN_VSET_SPINBOX_h = lv_obj_get_height(ui->MAIN_VSET_SPINBOX);
	ui->MAIN_VSET_SPINBOX_btn = lv_btn_create(ui->MAIN_cont_4);
	lv_obj_set_size(ui->MAIN_VSET_SPINBOX_btn, MAIN_VSET_SPINBOX_h, MAIN_VSET_SPINBOX_h);
	lv_obj_align_to(ui->MAIN_VSET_SPINBOX_btn, ui->MAIN_VSET_SPINBOX, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
	lv_obj_set_style_bg_img_src(ui->MAIN_VSET_SPINBOX_btn, LV_SYMBOL_PLUS, 0);
	lv_obj_add_event_cb(ui->MAIN_VSET_SPINBOX_btn, lv_MAIN_VSET_SPINBOX_increment_event_cb, LV_EVENT_ALL, NULL);
	ui->MAIN_VSET_SPINBOX_btn_minus = lv_btn_create(ui->MAIN_cont_4);
	lv_obj_set_size(ui->MAIN_VSET_SPINBOX_btn_minus, MAIN_VSET_SPINBOX_h, MAIN_VSET_SPINBOX_h);
	lv_obj_align_to(ui->MAIN_VSET_SPINBOX_btn_minus, ui->MAIN_VSET_SPINBOX, LV_ALIGN_OUT_LEFT_MID, -5, 0);
	lv_obj_set_style_bg_img_src(ui->MAIN_VSET_SPINBOX_btn_minus, LV_SYMBOL_MINUS, 0);
	lv_obj_add_event_cb(ui->MAIN_VSET_SPINBOX_btn_minus, lv_MAIN_VSET_SPINBOX_decrement_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(ui->MAIN_VSET_SPINBOX, 137, 8);
	lv_obj_set_scrollbar_mode(ui->MAIN_VSET_SPINBOX, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_VSET_SPINBOX, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_VSET_SPINBOX, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_VSET_SPINBOX, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_VSET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_VSET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_VSET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_VSET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_VSET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_VSET_SPINBOX, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_VSET_SPINBOX, &lv_font_blender_pro_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_VSET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_VSET_SPINBOX, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_VSET_SPINBOX, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for MAIN_VSET_SPINBOX, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->MAIN_VSET_SPINBOX, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_VSET_SPINBOX, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_VSET_SPINBOX, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_VSET_SPINBOX, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_MAIN_VSET_SPINBOX_extra_btns_main_default
	static lv_style_t style_MAIN_VSET_SPINBOX_extra_btns_main_default;
	ui_init_style(&style_MAIN_VSET_SPINBOX_extra_btns_main_default);
	
	lv_style_set_text_color(&style_MAIN_VSET_SPINBOX_extra_btns_main_default, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_MAIN_VSET_SPINBOX_extra_btns_main_default, &lv_font_montserratMedium_12);
	lv_style_set_bg_opa(&style_MAIN_VSET_SPINBOX_extra_btns_main_default, 255);
	lv_style_set_bg_color(&style_MAIN_VSET_SPINBOX_extra_btns_main_default, lv_color_hex(0x2195f6));
	lv_style_set_border_width(&style_MAIN_VSET_SPINBOX_extra_btns_main_default, 0);
	lv_style_set_radius(&style_MAIN_VSET_SPINBOX_extra_btns_main_default, 5);
	lv_obj_add_style(ui->MAIN_VSET_SPINBOX_btn, &style_MAIN_VSET_SPINBOX_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->MAIN_VSET_SPINBOX_btn_minus, &style_MAIN_VSET_SPINBOX_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_24
	ui->MAIN_label_24 = lv_label_create(ui->MAIN_cont_4);
	lv_label_set_text(ui->MAIN_label_24, "VSET:");
	lv_label_set_long_mode(ui->MAIN_label_24, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_24, 9, 11);
	lv_obj_set_size(ui->MAIN_label_24, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_24, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_24, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_24, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_24, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_24, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_25
	ui->MAIN_label_25 = lv_label_create(ui->MAIN_cont_4);
	lv_label_set_text(ui->MAIN_label_25, "ISET:");
	lv_label_set_long_mode(ui->MAIN_label_25, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_25, 9, 58);
	lv_obj_set_size(ui->MAIN_label_25, 70, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_25, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_25, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_25, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_25, &lv_font_blender_pro_bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_25, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_25, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_25, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_cont_5
	ui->MAIN_cont_5 = lv_obj_create(ui->MAIN);
	lv_obj_set_pos(ui->MAIN_cont_5, 5, 292);
	lv_obj_set_size(ui->MAIN_cont_5, 470, 25);
	lv_obj_set_scrollbar_mode(ui->MAIN_cont_5, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_cont_5, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_cont_5, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_28
	ui->MAIN_label_28 = lv_label_create(ui->MAIN_cont_5);
	lv_label_set_text(ui->MAIN_label_28, "TEMP:");
	lv_label_set_long_mode(ui->MAIN_label_28, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_28, 7, 5);
	lv_obj_set_size(ui->MAIN_label_28, 50, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_28, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_28, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_28, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_28, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_28, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_28, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_28, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_26
	ui->MAIN_label_26 = lv_label_create(ui->MAIN_cont_5);
	lv_label_set_text(ui->MAIN_label_26, "FAN:");
	lv_label_set_long_mode(ui->MAIN_label_26, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_26, 272, 5);
	lv_obj_set_size(ui->MAIN_label_26, 40, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_26, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_26, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_26, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_26, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_TEMP_INFO
	ui->MAIN_TEMP_INFO = lv_label_create(ui->MAIN_cont_5);
	lv_label_set_text(ui->MAIN_TEMP_INFO, "00.00C");
	lv_label_set_long_mode(ui->MAIN_TEMP_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_TEMP_INFO, 64, 5);
	lv_obj_set_size(ui->MAIN_TEMP_INFO, 60, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_TEMP_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_TEMP_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_TEMP_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_TEMP_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_TEMP_INFO, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_TEMP_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_TEMP_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_30
	ui->MAIN_label_30 = lv_label_create(ui->MAIN_cont_5);
	lv_label_set_text(ui->MAIN_label_30, "N:");
	lv_label_set_long_mode(ui->MAIN_label_30, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_30, 163, 5);
	lv_obj_set_size(ui->MAIN_label_30, 20, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_30, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_30, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_30, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_30, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_30, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_30, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_30, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_EFFECT_INFO
	ui->MAIN_EFFECT_INFO = lv_label_create(ui->MAIN_cont_5);
	lv_label_set_text(ui->MAIN_EFFECT_INFO, "90%");
	lv_label_set_long_mode(ui->MAIN_EFFECT_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_EFFECT_INFO, 180, 5);
	lv_obj_set_size(ui->MAIN_EFFECT_INFO, 40, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_EFFECT_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_EFFECT_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_EFFECT_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_EFFECT_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_EFFECT_INFO, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_EFFECT_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_EFFECT_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_FAN_INFO
	ui->MAIN_FAN_INFO = lv_label_create(ui->MAIN_cont_5);
	lv_label_set_text(ui->MAIN_FAN_INFO, "OFF");
	lv_label_set_long_mode(ui->MAIN_FAN_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_FAN_INFO, 312, 5);
	lv_obj_set_size(ui->MAIN_FAN_INFO, 35, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_FAN_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_FAN_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_FAN_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_FAN_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_FAN_INFO, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_FAN_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_FAN_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_40
	ui->MAIN_label_40 = lv_label_create(ui->MAIN_cont_5);
	lv_label_set_text(ui->MAIN_label_40, "BLE:");
	lv_label_set_long_mode(ui->MAIN_label_40, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_40, 366, 5);
	lv_obj_set_size(ui->MAIN_label_40, 40, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_40, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_40, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_40, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_40, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_40, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_40, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_BLE_INFO
	ui->MAIN_BLE_INFO = lv_label_create(ui->MAIN_cont_5);
	lv_label_set_text(ui->MAIN_BLE_INFO, "OFF");
	lv_label_set_long_mode(ui->MAIN_BLE_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_BLE_INFO, 409, 5);
	lv_obj_set_size(ui->MAIN_BLE_INFO, 35, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_BLE_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_BLE_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_BLE_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_BLE_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_BLE_INFO, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_BLE_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_BLE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_START_BTU
	ui->MAIN_START_BTU = lv_btn_create(ui->MAIN);
	ui->MAIN_START_BTU_label = lv_label_create(ui->MAIN_START_BTU);
	lv_label_set_text(ui->MAIN_START_BTU_label, "RUN");
	lv_label_set_long_mode(ui->MAIN_START_BTU_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->MAIN_START_BTU_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->MAIN_START_BTU, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->MAIN_START_BTU, 205, 42);
	lv_obj_set_size(ui->MAIN_START_BTU, 60, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_START_BTU, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_START_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_START_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_START_BTU, lv_color_hex(0x00cb0b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_START_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_START_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_START_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_START_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_START_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_START_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for MAIN_START_BTU, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_bg_opa(ui->MAIN_START_BTU, 254, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->MAIN_START_BTU, lv_color_hex(0xce001f), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_width(ui->MAIN_START_BTU, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_radius(ui->MAIN_START_BTU, 5, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->MAIN_START_BTU, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->MAIN_START_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->MAIN_START_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write codes MAIN_OVP_BTU
	ui->MAIN_OVP_BTU = lv_btn_create(ui->MAIN);
	ui->MAIN_OVP_BTU_label = lv_label_create(ui->MAIN_OVP_BTU);
	lv_label_set_text(ui->MAIN_OVP_BTU_label, "OVP:24.00V");
	lv_label_set_long_mode(ui->MAIN_OVP_BTU_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->MAIN_OVP_BTU_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->MAIN_OVP_BTU, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->MAIN_OVP_BTU, 205, 78);
	lv_obj_set_size(ui->MAIN_OVP_BTU, 125, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_OVP_BTU, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_OVP_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_OVP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_OVP_BTU, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_OVP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_OVP_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_OVP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_OVP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_OVP_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_OVP_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_OCP_BTU
	ui->MAIN_OCP_BTU = lv_btn_create(ui->MAIN);
	ui->MAIN_OCP_BTU_label = lv_label_create(ui->MAIN_OCP_BTU);
	lv_label_set_text(ui->MAIN_OCP_BTU_label, "OCP:05.00A");
	lv_label_set_long_mode(ui->MAIN_OCP_BTU_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->MAIN_OCP_BTU_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->MAIN_OCP_BTU, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->MAIN_OCP_BTU, 205, 113);
	lv_obj_set_size(ui->MAIN_OCP_BTU, 125, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_OCP_BTU, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_OCP_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_OCP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_OCP_BTU, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_OCP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_OCP_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_OCP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_OCP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_OCP_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_OCP_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_cont_6
	ui->MAIN_cont_6 = lv_obj_create(ui->MAIN);
	lv_obj_set_pos(ui->MAIN_cont_6, 340, 42);
	lv_obj_set_size(ui->MAIN_cont_6, 135, 63);
	lv_obj_set_scrollbar_mode(ui->MAIN_cont_6, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_cont_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_cont_6, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_cont_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_cont_6, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_AH_INFO
	ui->MAIN_AH_INFO = lv_label_create(ui->MAIN_cont_6);
	lv_label_set_text(ui->MAIN_AH_INFO, "0000.000");
	lv_label_set_long_mode(ui->MAIN_AH_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_AH_INFO, 7, 3);
	lv_obj_set_size(ui->MAIN_AH_INFO, 80, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_AH_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_AH_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_AH_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_AH_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_AH_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_AH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_35
	ui->MAIN_label_35 = lv_label_create(ui->MAIN_cont_6);
	lv_label_set_text(ui->MAIN_label_35, "AH");
	lv_label_set_long_mode(ui->MAIN_label_35, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_35, 90, 3);
	lv_obj_set_size(ui->MAIN_label_35, 36, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_35, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_35, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_35, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_35, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_35, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_35, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_36
	ui->MAIN_label_36 = lv_label_create(ui->MAIN_cont_6);
	lv_label_set_text(ui->MAIN_label_36, "WH");
	lv_label_set_long_mode(ui->MAIN_label_36, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_36, 90, 23);
	lv_obj_set_size(ui->MAIN_label_36, 36, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_36, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_36, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_36, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_36, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_36, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_36, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_WH_INFO
	ui->MAIN_WH_INFO = lv_label_create(ui->MAIN_cont_6);
	lv_label_set_text(ui->MAIN_WH_INFO, "0000.000");
	lv_label_set_long_mode(ui->MAIN_WH_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_WH_INFO, 7, 23);
	lv_obj_set_size(ui->MAIN_WH_INFO, 80, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_WH_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_WH_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_WH_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_WH_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_WH_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_WH_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_TIME_INFO
	ui->MAIN_TIME_INFO = lv_label_create(ui->MAIN_cont_6);
	lv_label_set_text(ui->MAIN_TIME_INFO, "00000.00");
	lv_label_set_long_mode(ui->MAIN_TIME_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_TIME_INFO, 7, 43);
	lv_obj_set_size(ui->MAIN_TIME_INFO, 80, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_TIME_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_TIME_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_TIME_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_TIME_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_TIME_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_TIME_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_39
	ui->MAIN_label_39 = lv_label_create(ui->MAIN_cont_6);
	lv_label_set_text(ui->MAIN_label_39, "TM");
	lv_label_set_long_mode(ui->MAIN_label_39, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_39, 90, 43);
	lv_obj_set_size(ui->MAIN_label_39, 36, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_39, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_39, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_39, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_39, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_39, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_39, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_LLIMMODE_LIST
	ui->MAIN_LLIMMODE_LIST = lv_dropdown_create(ui->MAIN);
	lv_dropdown_set_options(ui->MAIN_LLIMMODE_LIST, "CCM\nDCM");
	lv_obj_set_pos(ui->MAIN_LLIMMODE_LIST, 415, 113);
	lv_obj_set_size(ui->MAIN_LLIMMODE_LIST, 60, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_LLIMMODE_LIST, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_LLIMMODE_LIST, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->MAIN_LLIMMODE_LIST, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_LLIMMODE_LIST, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_LLIMMODE_LIST, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_LLIMMODE_LIST, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_LLIMMODE_LIST, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_LLIMMODE_LIST, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_LLIMMODE_LIST, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_LLIMMODE_LIST, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_LLIMMODE_LIST, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_LLIMMODE_LIST, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_MAIN_LLIMMODE_LIST_extra_list_selected_checked
	static lv_style_t style_MAIN_LLIMMODE_LIST_extra_list_selected_checked;
	ui_init_style(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked);
	
	lv_style_set_text_color(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, &lv_font_montserratMedium_12);
	lv_style_set_border_width(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
	lv_style_set_radius(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, 3);
	lv_style_set_bg_opa(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, 255);
	lv_style_set_bg_color(&style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, lv_color_hex(0x00a1b5));
	lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_LLIMMODE_LIST), &style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_MAIN_LLIMMODE_LIST_extra_list_main_default
	static lv_style_t style_MAIN_LLIMMODE_LIST_extra_list_main_default;
	ui_init_style(&style_MAIN_LLIMMODE_LIST_extra_list_main_default);
	
	lv_style_set_max_height(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, 90);
	lv_style_set_text_color(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, &lv_font_montserratMedium_12);
	lv_style_set_border_width(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, 255);
	lv_style_set_border_color(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_radius(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, 3);
	lv_style_set_bg_opa(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, 255);
	lv_style_set_bg_color(&style_MAIN_LLIMMODE_LIST_extra_list_main_default, lv_color_hex(0xffffff));
	lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_LLIMMODE_LIST), &style_MAIN_LLIMMODE_LIST_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default
	static lv_style_t style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default;
	ui_init_style(&style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default);
	
	lv_style_set_radius(&style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default, 255);
	lv_style_set_bg_color(&style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
	lv_obj_add_style(lv_dropdown_get_list(ui->MAIN_LLIMMODE_LIST), &style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes MAIN_cont_7
	ui->MAIN_cont_7 = lv_obj_create(ui->MAIN);
	lv_obj_set_pos(ui->MAIN_cont_7, 5, 260);
	lv_obj_set_size(ui->MAIN_cont_7, 180, 25);
	lv_obj_set_scrollbar_mode(ui->MAIN_cont_7, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_cont_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_cont_7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_cont_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_cont_7, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_label_49
	ui->MAIN_label_49 = lv_label_create(ui->MAIN_cont_7);
	lv_label_set_text(ui->MAIN_label_49, "STATE:");
	lv_label_set_long_mode(ui->MAIN_label_49, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_label_49, 2, 3);
	lv_obj_set_size(ui->MAIN_label_49, 65, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_label_49, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_label_49, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_label_49, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_label_49, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_label_49, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_label_49, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_label_49, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_STATE_INFO
	ui->MAIN_STATE_INFO = lv_label_create(ui->MAIN_cont_7);
	lv_label_set_text(ui->MAIN_STATE_INFO, "NORMAL");
	lv_label_set_long_mode(ui->MAIN_STATE_INFO, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->MAIN_STATE_INFO, 85, 4);
	lv_obj_set_size(ui->MAIN_STATE_INFO, 75, 20);
	lv_obj_set_scrollbar_mode(ui->MAIN_STATE_INFO, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_STATE_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_STATE_INFO, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_STATE_INFO, &lv_font_blender_pro_bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->MAIN_STATE_INFO, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_STATE_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_STATE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_SET_BTU
	ui->MAIN_SET_BTU = lv_btn_create(ui->MAIN);
	ui->MAIN_SET_BTU_label = lv_label_create(ui->MAIN_SET_BTU);
	lv_label_set_text(ui->MAIN_SET_BTU_label, "SET");
	lv_label_set_long_mode(ui->MAIN_SET_BTU_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->MAIN_SET_BTU_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->MAIN_SET_BTU, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->MAIN_SET_BTU, 415, 257);
	lv_obj_set_size(ui->MAIN_SET_BTU, 60, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_SET_BTU, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_SET_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_SET_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_SET_BTU, lv_color_hex(0x303030), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_SET_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_SET_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_SET_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_SET_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_SET_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_SET_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_MEUN_BTU
	ui->MAIN_MEUN_BTU = lv_btn_create(ui->MAIN);
	ui->MAIN_MEUN_BTU_label = lv_label_create(ui->MAIN_MEUN_BTU);
	lv_label_set_text(ui->MAIN_MEUN_BTU_label, "MENU");
	lv_label_set_long_mode(ui->MAIN_MEUN_BTU_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->MAIN_MEUN_BTU_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->MAIN_MEUN_BTU, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->MAIN_MEUN_BTU, 348, 257);
	lv_obj_set_size(ui->MAIN_MEUN_BTU, 60, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_MEUN_BTU, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_MEUN_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_MEUN_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_MEUN_BTU, lv_color_hex(0x303030), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_MEUN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_MEUN_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_MEUN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_MEUN_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_MEUN_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_MEUN_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_FAN_BTU
	ui->MAIN_FAN_BTU = lv_btn_create(ui->MAIN);
	ui->MAIN_FAN_BTU_label = lv_label_create(ui->MAIN_FAN_BTU);
	lv_label_set_text(ui->MAIN_FAN_BTU_label, "AUTO");
	lv_label_set_long_mode(ui->MAIN_FAN_BTU_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->MAIN_FAN_BTU_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->MAIN_FAN_BTU, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->MAIN_FAN_BTU, 270, 257);
	lv_obj_set_size(ui->MAIN_FAN_BTU, 60, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_FAN_BTU, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_FAN_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_FAN_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_FAN_BTU, lv_color_hex(0x00cc38), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_FAN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_FAN_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_FAN_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_FAN_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_FAN_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_FAN_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for MAIN_FAN_BTU, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_bg_opa(ui->MAIN_FAN_BTU, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->MAIN_FAN_BTU, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_width(ui->MAIN_FAN_BTU, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_radius(ui->MAIN_FAN_BTU, 5, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->MAIN_FAN_BTU, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->MAIN_FAN_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->MAIN_FAN_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write codes MAIN_btn_7
	ui->MAIN_btn_7 = lv_btn_create(ui->MAIN);
	ui->MAIN_btn_7_label = lv_label_create(ui->MAIN_btn_7);
	lv_label_set_text(ui->MAIN_btn_7_label, "MENU");
	lv_label_set_long_mode(ui->MAIN_btn_7_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->MAIN_btn_7_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->MAIN_btn_7, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->MAIN_btn_7, 205, 257);
	lv_obj_set_size(ui->MAIN_btn_7, 60, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_btn_7, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_btn_7, lv_color_hex(0x303030), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_btn_7, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_btn_7, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes MAIN_COMP_BTU
	ui->MAIN_COMP_BTU = lv_btn_create(ui->MAIN);
	ui->MAIN_COMP_BTU_label = lv_label_create(ui->MAIN_COMP_BTU);
	lv_label_set_text(ui->MAIN_COMP_BTU_label, "COMP");
	lv_label_set_long_mode(ui->MAIN_COMP_BTU_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->MAIN_COMP_BTU_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->MAIN_COMP_BTU, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->MAIN_COMP_BTU, 270, 42);
	lv_obj_set_size(ui->MAIN_COMP_BTU, 60, 30);
	lv_obj_set_scrollbar_mode(ui->MAIN_COMP_BTU, LV_SCROLLBAR_MODE_OFF);

	//Write style for MAIN_COMP_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->MAIN_COMP_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->MAIN_COMP_BTU, lv_color_hex(0xb4b4b4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->MAIN_COMP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->MAIN_COMP_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->MAIN_COMP_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->MAIN_COMP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->MAIN_COMP_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->MAIN_COMP_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for MAIN_COMP_BTU, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_bg_opa(ui->MAIN_COMP_BTU, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->MAIN_COMP_BTU, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_width(ui->MAIN_COMP_BTU, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_radius(ui->MAIN_COMP_BTU, 5, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->MAIN_COMP_BTU, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->MAIN_COMP_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->MAIN_COMP_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_PRESSED);

	//Update current screen layout.
	lv_obj_update_layout(ui->MAIN);

	
}
