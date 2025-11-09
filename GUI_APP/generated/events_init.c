/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void START_PAGE_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.MAIN_PAGE, guider_ui.MAIN_PAGE_del, &guider_ui.START_PAGE_del, setup_scr_MAIN_PAGE, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

void events_init_START_PAGE (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->START_PAGE, START_PAGE_event_handler, LV_EVENT_ALL, ui);
}

static void MAIN_PAGE_CHART_BTU_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.CHART_PAGE, guider_ui.CHART_PAGE_del, &guider_ui.MAIN_PAGE_del, setup_scr_CHART_PAGE, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void MAIN_PAGE_MEUN_BTU_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.MEUN_PAGE, guider_ui.MEUN_PAGE_del, &guider_ui.MAIN_PAGE_del, setup_scr_MEUN_PAGE, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

static void MAIN_PAGE_OSC_BTU_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.OSCILLO_PAGE, guider_ui.OSCILLO_PAGE_del, &guider_ui.MAIN_PAGE_del, setup_scr_OSCILLO_PAGE, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false);
        break;
    }
    default:
        break;
    }
}

void events_init_MAIN_PAGE (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->MAIN_PAGE_CHART_BTU, MAIN_PAGE_CHART_BTU_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MAIN_PAGE_MEUN_BTU, MAIN_PAGE_MEUN_BTU_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->MAIN_PAGE_OSC_BTU, MAIN_PAGE_OSC_BTU_event_handler, LV_EVENT_ALL, ui);
}

static void MEUN_PAGE_BACK_SET_BTU_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.MAIN_PAGE, guider_ui.MAIN_PAGE_del, &guider_ui.MEUN_PAGE_del, setup_scr_MAIN_PAGE, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_MEUN_PAGE (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->MEUN_PAGE_BACK_SET_BTU, MEUN_PAGE_BACK_SET_BTU_event_handler, LV_EVENT_ALL, ui);
}

static void OSCILLO_PAGE_BACK_OSCILLO_BTU_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.MAIN_PAGE, guider_ui.MAIN_PAGE_del, &guider_ui.OSCILLO_PAGE_del, setup_scr_MAIN_PAGE, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_OSCILLO_PAGE (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->OSCILLO_PAGE_BACK_OSCILLO_BTU, OSCILLO_PAGE_BACK_OSCILLO_BTU_event_handler, LV_EVENT_ALL, ui);
}

static void CHART_PAGE_BACK_CHART_BTU_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.MAIN_PAGE, guider_ui.MAIN_PAGE_del, &guider_ui.CHART_PAGE_del, setup_scr_MAIN_PAGE, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_CHART_PAGE (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->CHART_PAGE_BACK_CHART_BTU, CHART_PAGE_BACK_CHART_BTU_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
