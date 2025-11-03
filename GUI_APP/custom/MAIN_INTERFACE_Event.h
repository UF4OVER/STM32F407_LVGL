#ifndef MAIN_INTERFACE_EVENT_H
#define MAIN_INTERFACE_EVENT_H

#include "lvgl.h"
#include "gui_guider.h"

/* Input limit macros (can be overridden in build settings or before including this header) */
#ifndef OVP_MIN_V
#define OVP_MIN_V 0.00f
#endif
#ifndef OVP_MAX_V
#define OVP_MAX_V 60.00f
#endif
#ifndef OCP_MIN_A
#define OCP_MIN_A 0.00f
#endif
#ifndef OCP_MAX_A
#define OCP_MAX_A 20.00f
#endif

/* Tiny clamp helper for doubles */
static inline double clampd(double v, double lo, double hi)
{
    if(v < lo) return lo;
    if(v > hi) return hi;
    return v;
}

#ifdef __cplusplus
extern "C" {
#endif

void MAIN_INTERFACE_events_init(lv_ui *ui);

#ifdef __cplusplus
}
#endif

#endif // MAIN_INTERFACE_EVENT_H
