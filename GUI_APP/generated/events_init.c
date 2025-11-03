/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"


static void START_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SCREEN_LOADED:
	{
		//Write animation: START_start_kangtao move in x direction
		lv_anim_t START_start_kangtao_anim_x;
		lv_anim_init(&START_start_kangtao_anim_x);
		lv_anim_set_var(&START_start_kangtao_anim_x, guider_ui.START_start_kangtao);
		lv_anim_set_time(&START_start_kangtao_anim_x, 1000);
		lv_anim_set_delay(&START_start_kangtao_anim_x, 200);
		lv_anim_set_exec_cb(&START_start_kangtao_anim_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
		lv_anim_set_values(&START_start_kangtao_anim_x, lv_obj_get_x(guider_ui.START_start_kangtao), 0);
		lv_anim_set_path_cb(&START_start_kangtao_anim_x, &lv_anim_path_ease_in);
		START_start_kangtao_anim_x.repeat_cnt = 1;
		lv_anim_start(&START_start_kangtao_anim_x);
		//Write animation: START_start_kangtao move in y direction
		lv_anim_t START_start_kangtao_anim_y;
		lv_anim_init(&START_start_kangtao_anim_y);
		lv_anim_set_var(&START_start_kangtao_anim_y, guider_ui.START_start_kangtao);
		lv_anim_set_time(&START_start_kangtao_anim_y, 1000);
		lv_anim_set_delay(&START_start_kangtao_anim_y, 200);
		lv_anim_set_exec_cb(&START_start_kangtao_anim_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
		lv_anim_set_values(&START_start_kangtao_anim_y, lv_obj_get_y(guider_ui.START_start_kangtao), 0);
		lv_anim_set_path_cb(&START_start_kangtao_anim_y, &lv_anim_path_ease_in);
		START_start_kangtao_anim_y.repeat_cnt = 1;
		lv_anim_start(&START_start_kangtao_anim_y);
		break;
	}
	default:
		break;
	}
}
void events_init_START(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->START, START_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
