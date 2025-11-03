#include "SEETING_INTERFACE_Event.h"

static void SEETING_BACK_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        if(guider_ui.MAIN) lv_scr_load(guider_ui.MAIN);
    }
}

void SEETING_INTERFACE_events_init(lv_ui *ui)
{
    if(ui->SEETING_BACK_BTN) {
        lv_obj_add_event_cb(ui->SEETING_BACK_BTN, SEETING_BACK_event_handler, LV_EVENT_ALL, NULL);
    }
}

