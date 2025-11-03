/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"


void setup_scr_START(lv_ui *ui)
{
	//Write codes START
	ui->START = lv_obj_create(NULL);
	lv_obj_set_size(ui->START, 480, 320);
	lv_obj_set_scrollbar_mode(ui->START, LV_SCROLLBAR_MODE_OFF);

	//Write style for START, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->START, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->START, lv_color_hex(0x0e0e0e), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes START_start_kangtao
	ui->START_start_kangtao = lv_animimg_create(ui->START);
	// set animation images
	lv_animimg_set_src(ui->START_start_kangtao, (const void **) START_start_kangtao_imgs, 1);
	// play once
	lv_animimg_set_duration(ui->START_start_kangtao, 1000); // set desired duration in ms
	lv_animimg_set_repeat_count(ui->START_start_kangtao, 1);
	lv_img_set_src(ui->START_start_kangtao, START_start_kangtao_imgs[0]);
	lv_obj_set_pos(ui->START_start_kangtao, 90, 110);
	lv_obj_set_size(ui->START_start_kangtao, 300, 100);
	lv_obj_set_scrollbar_mode(ui->START_start_kangtao, LV_SCROLLBAR_MODE_OFF);

	// Start the animation
	lv_animimg_start(ui->START_start_kangtao);

	// Transition timer is handled in custom.c to keep generated files clean

	//Update current screen layout.
	lv_obj_update_layout(ui->START);


	//Init events for screen.
	events_init_START(ui);
}
