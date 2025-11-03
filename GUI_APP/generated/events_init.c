/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include "gui_guider.h"
#include "START_INTERFACE_Event.h"
#include "MAIN_INTERFACE_Event.h"
#include "SEETING_INTERFACE_Event.h"

void events_init_START(lv_ui *ui)
{
    START_INTERFACE_events_init(ui);
}

void events_init_MAIN(lv_ui *ui)
{
    MAIN_INTERFACE_events_init(ui);
}

void events_init_SEETING(lv_ui *ui)
{
    SEETING_INTERFACE_events_init(ui);
}

void events_init(lv_ui *ui)
{
    events_init_START(ui);
    events_init_MAIN(ui);
    events_init_SEETING(ui);
}
