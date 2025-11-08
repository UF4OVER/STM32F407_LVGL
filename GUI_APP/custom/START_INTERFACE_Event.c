#include "START_INTERFACE_Event.h"

static void START_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    default:
        break;
    }
}

void START_INTERFACE_events_init(lv_ui *ui)
{
    if(ui->START_PAGE) {
        lv_obj_add_event_cb(ui->START_PAGE, START_event_handler, LV_EVENT_ALL, NULL);
    }
}

