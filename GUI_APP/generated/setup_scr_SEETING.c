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


void setup_scr_SEETING(lv_ui *ui)
{
	//Write codes SEETING
	ui->SEETING = lv_obj_create(NULL);
	lv_obj_set_size(ui->SEETING, 480, 320);
	lv_obj_set_scrollbar_mode(ui->SEETING, LV_SCROLLBAR_MODE_OFF);

	//Write style for SEETING, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->SEETING, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->SEETING, lv_color_hex(UI_COLOR_SCREEN_BG), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes SEETING_SET_MEUN
	ui->SEETING_SET_MEUN = lv_menu_create(ui->SEETING);

	//Create sidebar page for menu SEETING_SET_MEUN
	ui->SEETING_SET_MEUN_sidebar_page = lv_menu_page_create(ui->SEETING_SET_MEUN, "SETTING");
	lv_menu_set_sidebar_page(ui->SEETING_SET_MEUN, ui->SEETING_SET_MEUN_sidebar_page);

	//Create subpage for SEETING_SET_MEUN
	ui->SEETING_SET_MEUN_subpage_1 = lv_menu_page_create(ui->SEETING_SET_MEUN, NULL);
	ui->SEETING_SET_MEUN_cont_1 = lv_menu_cont_create(ui->SEETING_SET_MEUN_sidebar_page);
	ui->SEETING_SET_MEUN_label_1 = lv_label_create(ui->SEETING_SET_MEUN_cont_1);
	lv_label_set_text(ui->SEETING_SET_MEUN_label_1, "BLE & WIFI");
	lv_obj_set_size(ui->SEETING_SET_MEUN_label_1, LV_PCT(100), LV_SIZE_CONTENT);
	// set font for sidebar label
	lv_obj_set_style_text_font(ui->SEETING_SET_MEUN_label_1, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_menu_set_load_page_event(ui->SEETING_SET_MEUN, ui->SEETING_SET_MEUN_cont_1, ui->SEETING_SET_MEUN_subpage_1);
	// Set default main page to the first subpage
	lv_menu_set_page(ui->SEETING_SET_MEUN, ui->SEETING_SET_MEUN_subpage_1);

	//Create subpage for SEETING_SET_MEUN
	ui->SEETING_SET_MEUN_subpage_2 = lv_menu_page_create(ui->SEETING_SET_MEUN, NULL);
	ui->SEETING_SET_MEUN_cont_2 = lv_menu_cont_create(ui->SEETING_SET_MEUN_sidebar_page);
	ui->SEETING_SET_MEUN_label_2 = lv_label_create(ui->SEETING_SET_MEUN_cont_2);
	lv_label_set_text(ui->SEETING_SET_MEUN_label_2, "DEVICE INFO");
	lv_obj_set_size(ui->SEETING_SET_MEUN_label_2, LV_PCT(100), LV_SIZE_CONTENT);
	// set font for sidebar label
	lv_obj_set_style_text_font(ui->SEETING_SET_MEUN_label_2, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_menu_set_load_page_event(ui->SEETING_SET_MEUN, ui->SEETING_SET_MEUN_cont_2, ui->SEETING_SET_MEUN_subpage_2);

	//Create subpage for SEETING_SET_MEUN
	ui->SEETING_SET_MEUN_subpage_3 = lv_menu_page_create(ui->SEETING_SET_MEUN, NULL);
	ui->SEETING_SET_MEUN_cont_3 = lv_menu_cont_create(ui->SEETING_SET_MEUN_sidebar_page);
	ui->SEETING_SET_MEUN_label_3 = lv_label_create(ui->SEETING_SET_MEUN_cont_3);
	lv_label_set_text(ui->SEETING_SET_MEUN_label_3, "THEMES");
	lv_obj_set_size(ui->SEETING_SET_MEUN_label_3, LV_PCT(100), LV_SIZE_CONTENT);
	// set font for sidebar label
	lv_obj_set_style_text_font(ui->SEETING_SET_MEUN_label_3, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_menu_set_load_page_event(ui->SEETING_SET_MEUN, ui->SEETING_SET_MEUN_cont_3, ui->SEETING_SET_MEUN_subpage_3);

	//Create subpage for SEETING_SET_MEUN
	ui->SEETING_SET_MEUN_subpage_4 = lv_menu_page_create(ui->SEETING_SET_MEUN, NULL);
	ui->SEETING_SET_MEUN_cont_4 = lv_menu_cont_create(ui->SEETING_SET_MEUN_sidebar_page);
	ui->SEETING_SET_MEUN_label_4 = lv_label_create(ui->SEETING_SET_MEUN_cont_4);
	lv_label_set_text(ui->SEETING_SET_MEUN_label_4, "PID INFO");
	lv_obj_set_size(ui->SEETING_SET_MEUN_label_4, LV_PCT(100), LV_SIZE_CONTENT);
	// set font for sidebar label
	lv_obj_set_style_text_font(ui->SEETING_SET_MEUN_label_4, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_menu_set_load_page_event(ui->SEETING_SET_MEUN, ui->SEETING_SET_MEUN_cont_4, ui->SEETING_SET_MEUN_subpage_4);

	//Create subpage for SEETING_SET_MEUN
	ui->SEETING_SET_MEUN_subpage_5 = lv_menu_page_create(ui->SEETING_SET_MEUN, NULL);
	ui->SEETING_SET_MEUN_cont_5 = lv_menu_cont_create(ui->SEETING_SET_MEUN_sidebar_page);
	ui->SEETING_SET_MEUN_label_5 = lv_label_create(ui->SEETING_SET_MEUN_cont_5);
	lv_label_set_text(ui->SEETING_SET_MEUN_label_5, "BOOT VERSION");
	lv_obj_set_size(ui->SEETING_SET_MEUN_label_5, LV_PCT(100), LV_SIZE_CONTENT);
	// set font for sidebar label
	lv_obj_set_style_text_font(ui->SEETING_SET_MEUN_label_5, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_menu_set_load_page_event(ui->SEETING_SET_MEUN, ui->SEETING_SET_MEUN_cont_5, ui->SEETING_SET_MEUN_subpage_5);
	lv_obj_set_pos(ui->SEETING_SET_MEUN, 0, 0);
	lv_obj_set_size(ui->SEETING_SET_MEUN, 480, 320);
	lv_obj_set_scrollbar_mode(ui->SEETING_SET_MEUN, LV_SCROLLBAR_MODE_OFF);

	// Set fixed spacing between rows on sidebar and subpages
	static lv_style_t style_SEETING_page_gap;
	ui_init_style(&style_SEETING_page_gap);
	lv_style_set_pad_row(&style_SEETING_page_gap, 8);
	lv_obj_add_style(ui->SEETING_SET_MEUN_sidebar_page, &style_SEETING_page_gap, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_subpage_1, &style_SEETING_page_gap, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_subpage_2, &style_SEETING_page_gap, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_subpage_3, &style_SEETING_page_gap, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_subpage_4, &style_SEETING_page_gap, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_subpage_5, &style_SEETING_page_gap, LV_PART_MAIN|LV_STATE_DEFAULT);

	// Reusable BG style for each option row
	static lv_style_t style_SEETING_row_bg_main_default;
	ui_init_style(&style_SEETING_row_bg_main_default);
	lv_style_set_bg_opa(&style_SEETING_row_bg_main_default, 255);
	lv_style_set_bg_color(&style_SEETING_row_bg_main_default, lv_color_hex(UI_COLOR_ROW_BG));
	lv_style_set_radius(&style_SEETING_row_bg_main_default, 6);
	lv_style_set_border_width(&style_SEETING_row_bg_main_default, 0);
	lv_style_set_shadow_width(&style_SEETING_row_bg_main_default, 0);
	lv_style_set_pad_left(&style_SEETING_row_bg_main_default, 12);
	lv_style_set_pad_right(&style_SEETING_row_bg_main_default, 12);
	lv_style_set_pad_top(&style_SEETING_row_bg_main_default, 8);
	lv_style_set_pad_bottom(&style_SEETING_row_bg_main_default, 8);

	// Add content to subpage 1: BLE & WIFI (with switches)
	ui->SEETING_BLE_row = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_1);
	lv_obj_set_width(ui->SEETING_BLE_row, LV_PCT(100));
	lv_obj_set_flex_flow(ui->SEETING_BLE_row, LV_FLEX_FLOW_ROW);
	lv_obj_add_style(ui->SEETING_BLE_row, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_BLE_label = lv_label_create(ui->SEETING_BLE_row);
	lv_label_set_text(ui->SEETING_BLE_label, "Enable BLE");
	lv_obj_set_style_text_font(ui->SEETING_BLE_label, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_flex_grow(ui->SEETING_BLE_label, 1);
	ui->SEETING_BLE_switch = lv_switch_create(ui->SEETING_BLE_row);

	ui->SEETING_WIFI_row = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_1);
	lv_obj_set_width(ui->SEETING_WIFI_row, LV_PCT(100));
	lv_obj_set_flex_flow(ui->SEETING_WIFI_row, LV_FLEX_FLOW_ROW);
	lv_obj_add_style(ui->SEETING_WIFI_row, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_WIFI_label = lv_label_create(ui->SEETING_WIFI_row);
	lv_label_set_text(ui->SEETING_WIFI_label, "Enable Wi-Fi");
	lv_obj_set_style_text_font(ui->SEETING_WIFI_label, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_flex_grow(ui->SEETING_WIFI_label, 1);
	ui->SEETING_WIFI_switch = lv_switch_create(ui->SEETING_WIFI_row);

	// Add content to subpage 2: DEVICE INFO
	ui->SEETING_DEVICE_row_name = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_2);
	lv_obj_set_width(ui->SEETING_DEVICE_row_name, LV_PCT(100));
	lv_obj_add_style(ui->SEETING_DEVICE_row_name, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_DEVICE_label_name = lv_label_create(ui->SEETING_DEVICE_row_name);
	lv_label_set_text(ui->SEETING_DEVICE_label_name, "Name: UF4OVER POWER");
	lv_obj_set_style_text_font(ui->SEETING_DEVICE_label_name, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui->SEETING_DEVICE_row_sn = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_2);
	lv_obj_set_width(ui->SEETING_DEVICE_row_sn, LV_PCT(100));
	lv_obj_add_style(ui->SEETING_DEVICE_row_sn, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_DEVICE_label_sn = lv_label_create(ui->SEETING_DEVICE_row_sn);
	lv_label_set_text(ui->SEETING_DEVICE_label_sn, "SN: 0000-0000");
	lv_obj_set_style_text_font(ui->SEETING_DEVICE_label_sn, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui->SEETING_DEVICE_row_fw = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_2);
	lv_obj_set_width(ui->SEETING_DEVICE_row_fw, LV_PCT(100));
	lv_obj_add_style(ui->SEETING_DEVICE_row_fw, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_DEVICE_label_fw = lv_label_create(ui->SEETING_DEVICE_row_fw);
	lv_label_set_text(ui->SEETING_DEVICE_label_fw, "FW: 1.41.120");
	lv_obj_set_style_text_font(ui->SEETING_DEVICE_label_fw, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);

	// Add content to subpage 3: THEMES (with switches)
	ui->SEETING_THEME_row_dark = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_3);
	lv_obj_set_width(ui->SEETING_THEME_row_dark, LV_PCT(100));
	lv_obj_set_flex_flow(ui->SEETING_THEME_row_dark, LV_FLEX_FLOW_ROW);
	lv_obj_add_style(ui->SEETING_THEME_row_dark, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_THEME_label_dark = lv_label_create(ui->SEETING_THEME_row_dark);
	lv_label_set_text(ui->SEETING_THEME_label_dark, "Dark mode");
	lv_obj_set_style_text_font(ui->SEETING_THEME_label_dark, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_flex_grow(ui->SEETING_THEME_label_dark, 1);
	ui->SEETING_THEME_switch_dark = lv_switch_create(ui->SEETING_THEME_row_dark);

	ui->SEETING_THEME_row_contrast = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_3);
	lv_obj_set_width(ui->SEETING_THEME_row_contrast, LV_PCT(100));
	lv_obj_set_flex_flow(ui->SEETING_THEME_row_contrast, LV_FLEX_FLOW_ROW);
	lv_obj_add_style(ui->SEETING_THEME_row_contrast, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_THEME_label_contrast = lv_label_create(ui->SEETING_THEME_row_contrast);
	lv_label_set_text(ui->SEETING_THEME_label_contrast, "High contrast");
	lv_obj_set_style_text_font(ui->SEETING_THEME_label_contrast, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_flex_grow(ui->SEETING_THEME_label_contrast, 1);
	ui->SEETING_THEME_switch_contrast = lv_switch_create(ui->SEETING_THEME_row_contrast);

	// Add content to subpage 4: PID INFO (toggle + info rows)
	ui->SEETING_PID_row_enable = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_4);
	lv_obj_set_width(ui->SEETING_PID_row_enable, LV_PCT(100));
	lv_obj_set_flex_flow(ui->SEETING_PID_row_enable, LV_FLEX_FLOW_ROW);
	lv_obj_add_style(ui->SEETING_PID_row_enable, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_PID_label_enable = lv_label_create(ui->SEETING_PID_row_enable);
	lv_label_set_text(ui->SEETING_PID_label_enable, "Enable PID");
	lv_obj_set_style_text_font(ui->SEETING_PID_label_enable, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_flex_grow(ui->SEETING_PID_label_enable, 1);
	ui->SEETING_PID_switch_enable = lv_switch_create(ui->SEETING_PID_row_enable);

	ui->SEETING_PID_row_kp = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_4);
	lv_obj_set_width(ui->SEETING_PID_row_kp, LV_PCT(100));
	lv_obj_add_style(ui->SEETING_PID_row_kp, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_PID_label_kp = lv_label_create(ui->SEETING_PID_row_kp);
	lv_label_set_text(ui->SEETING_PID_label_kp, "Kp: 1.00");
	lv_obj_set_style_text_font(ui->SEETING_PID_label_kp, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui->SEETING_PID_row_ki = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_4);
	lv_obj_set_width(ui->SEETING_PID_row_ki, LV_PCT(100));
	lv_obj_add_style(ui->SEETING_PID_row_ki, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_PID_label_ki = lv_label_create(ui->SEETING_PID_row_ki);
	lv_label_set_text(ui->SEETING_PID_label_ki, "Ki: 0.10");
	lv_obj_set_style_text_font(ui->SEETING_PID_label_ki, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);

	ui->SEETING_PID_row_kd = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_4);
	lv_obj_set_width(ui->SEETING_PID_row_kd, LV_PCT(100));
	lv_obj_add_style(ui->SEETING_PID_row_kd, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_PID_label_kd = lv_label_create(ui->SEETING_PID_row_kd);
	lv_label_set_text(ui->SEETING_PID_label_kd, "Kd: 0.01");
	lv_obj_set_style_text_font(ui->SEETING_PID_label_kd, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);

	// Add content to subpage 5: BOOT VERSION
	ui->SEETING_BOOT_row_ver = lv_menu_cont_create(ui->SEETING_SET_MEUN_subpage_5);
	lv_obj_set_width(ui->SEETING_BOOT_row_ver, LV_PCT(100));
	lv_obj_add_style(ui->SEETING_BOOT_row_ver, &style_SEETING_row_bg_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->SEETING_BOOT_label_ver = lv_label_create(ui->SEETING_BOOT_row_ver);
	lv_label_set_text(ui->SEETING_BOOT_label_ver, "Bootloader: v1.0.0");
	lv_obj_set_style_text_font(ui->SEETING_BOOT_label_ver, &lv_font_blender_pro_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);

	// Back button
	ui->SEETING_BACK_BTN = lv_btn_create(ui->SEETING);
	ui->SEETING_BACK_BTN_label = lv_label_create(ui->SEETING_BACK_BTN);
	lv_label_set_text(ui->SEETING_BACK_BTN_label, "BACK");
	lv_obj_align(ui->SEETING_BACK_BTN_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->SEETING_BACK_BTN, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->SEETING_BACK_BTN, 400, 285);
	lv_obj_set_size(ui->SEETING_BACK_BTN, 70, 30);
	lv_obj_set_scrollbar_mode(ui->SEETING_BACK_BTN, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_bg_opa(ui->SEETING_BACK_BTN, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->SEETING_BACK_BTN, lv_color_hex(UI_COLOR_BACK_BTN_BG), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->SEETING_BACK_BTN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->SEETING_BACK_BTN, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->SEETING_BACK_BTN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->SEETING_BACK_BTN, lv_color_hex(UI_COLOR_BACK_BTN_TEXT), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->SEETING_BACK_BTN, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->SEETING_BACK_BTN, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for SEETING_SET_MEUN, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->SEETING_SET_MEUN, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->SEETING_SET_MEUN, lv_color_hex(UI_COLOR_SCREEN_BG), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->SEETING_SET_MEUN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->SEETING_SET_MEUN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_SEETING_SET_MEUN_extra_sidebar_page_main_default
	static lv_style_t style_SEETING_SET_MEUN_extra_sidebar_page_main_default;
	ui_init_style(&style_SEETING_SET_MEUN_extra_sidebar_page_main_default);

	lv_style_set_bg_opa(&style_SEETING_SET_MEUN_extra_sidebar_page_main_default, 255);
	lv_style_set_bg_color(&style_SEETING_SET_MEUN_extra_sidebar_page_main_default, lv_color_hex(UI_COLOR_SIDEBAR_BG));
	lv_style_set_radius(&style_SEETING_SET_MEUN_extra_sidebar_page_main_default, 0);
	lv_obj_add_style(ui->SEETING_SET_MEUN_sidebar_page, &style_SEETING_SET_MEUN_extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_SEETING_SET_MEUN_extra_option_btns_main_default
	static lv_style_t style_SEETING_SET_MEUN_extra_option_btns_main_default;
	ui_init_style(&style_SEETING_SET_MEUN_extra_option_btns_main_default);

	lv_style_set_text_color(&style_SEETING_SET_MEUN_extra_option_btns_main_default, lv_color_hex(UI_COLOR_MENU_TEXT));
	lv_style_set_text_font(&style_SEETING_SET_MEUN_extra_option_btns_main_default, &lv_font_blender_pro_bold_16);
	lv_style_set_text_align(&style_SEETING_SET_MEUN_extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_top(&style_SEETING_SET_MEUN_extra_option_btns_main_default, 10);
	lv_style_set_pad_bottom(&style_SEETING_SET_MEUN_extra_option_btns_main_default, 10);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_5, &style_SEETING_SET_MEUN_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_4, &style_SEETING_SET_MEUN_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_3, &style_SEETING_SET_MEUN_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_2, &style_SEETING_SET_MEUN_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_1, &style_SEETING_SET_MEUN_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write style state: LV_STATE_CHECKED for &style_SEETING_SET_MEUN_extra_option_btns_main_checked
	static lv_style_t style_SEETING_SET_MEUN_extra_option_btns_main_checked;
	ui_init_style(&style_SEETING_SET_MEUN_extra_option_btns_main_checked);

	lv_style_set_text_color(&style_SEETING_SET_MEUN_extra_option_btns_main_checked, lv_color_hex(UI_COLOR_MENU_TEXT_CHECK));
	// keep checked bg color consistent (macro)
	lv_style_set_bg_color(&style_SEETING_SET_MEUN_extra_option_btns_main_checked, lv_color_hex(UI_COLOR_MENU_CHECK_BG));
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_5, &style_SEETING_SET_MEUN_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_4, &style_SEETING_SET_MEUN_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_3, &style_SEETING_SET_MEUN_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_2, &style_SEETING_SET_MEUN_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_add_style(ui->SEETING_SET_MEUN_cont_1, &style_SEETING_SET_MEUN_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_SEETING_SET_MEUN_extra_main_title_main_default
	static lv_style_t style_SEETING_SET_MEUN_extra_main_title_main_default;
	ui_init_style(&style_SEETING_SET_MEUN_extra_main_title_main_default);

	lv_style_set_text_color(&style_SEETING_SET_MEUN_extra_main_title_main_default, lv_color_hex(UI_COLOR_TITLE_TEXT));
	lv_style_set_text_font(&style_SEETING_SET_MEUN_extra_main_title_main_default, &lv_font_blender_pro_bold_16);
	lv_style_set_text_align(&style_SEETING_SET_MEUN_extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_bg_opa(&style_SEETING_SET_MEUN_extra_main_title_main_default, 255);
	lv_style_set_bg_color(&style_SEETING_SET_MEUN_extra_main_title_main_default, lv_color_hex(UI_COLOR_TITLE_BG));
	lv_style_set_pad_top(&style_SEETING_SET_MEUN_extra_main_title_main_default, 0);
	lv_style_set_pad_bottom(&style_SEETING_SET_MEUN_extra_main_title_main_default, 0);
	lv_obj_add_style(lv_menu_get_sidebar_header(ui->SEETING_SET_MEUN), &style_SEETING_SET_MEUN_extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Update current screen layout.
	lv_obj_update_layout(ui->SEETING);

}
