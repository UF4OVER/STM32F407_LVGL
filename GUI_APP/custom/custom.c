// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "gui_guider.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void splash_timer_cb(lv_timer_t * timer);

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    // Schedule transition to MAIN after splash animation finishes.
    // Duration is 1000 ms; add a small margin.
    lv_timer_t * t = lv_timer_create(splash_timer_cb, 1100, ui);
    (void)t;
}

static void splash_timer_cb(lv_timer_t * timer)
{
    lv_ui * ui = (lv_ui *)timer->user_data;

    // Create MAIN screen if not created yet
    if(ui->MAIN == NULL || ui->MAIN_del){
        setup_scr_MAIN(ui);
        ui->MAIN_del = false;
    }

    // Load MAIN screen
    lv_scr_load_anim(ui->MAIN, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);

    // Optionally delete START to free memory
    if(ui->START){
        lv_obj_del(ui->START);
        ui->START = NULL;
        ui->START_del = true;
    }

    // Once executed, no need to run again
    lv_timer_del(timer);
}
