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
#include "gui_guider.h"

static void START_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	default:
		break;
	}
}
void events_init_START(lv_ui *ui)
{
	if(ui->START) {
		lv_obj_add_event_cb(ui->START, START_event_handler, LV_EVENT_ALL, NULL);
	}
}

static void nav_load_screen(lv_obj_t * scr)
{
    if(scr) lv_scr_load(scr);
}

static void MAIN_SET_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        nav_load_screen(guider_ui.SEETING);
    }
}

static void SEETING_BACK_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        nav_load_screen(guider_ui.MAIN);
    }
}

void events_init_MAIN(lv_ui *ui)
{
    if(ui->MAIN_SET_BTU) {
        lv_obj_add_event_cb(ui->MAIN_SET_BTU, MAIN_SET_event_handler, LV_EVENT_ALL, NULL);
    }
}

void events_init_SEETING(lv_ui *ui)
{
    if(ui->SEETING_BACK_BTN) {
        lv_obj_add_event_cb(ui->SEETING_BACK_BTN, SEETING_BACK_event_handler, LV_EVENT_ALL, NULL);
    }
}

void events_init(lv_ui *ui)
{
    events_init_START(ui);
    events_init_MAIN(ui);
    events_init_SEETING(ui);
}
