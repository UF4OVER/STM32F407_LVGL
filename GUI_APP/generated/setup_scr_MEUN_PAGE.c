/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_MEUN_PAGE(lv_ui *ui)
{
    //Write codes MEUN_PAGE
    ui->MEUN_PAGE = lv_obj_create(NULL);
    lv_obj_set_size(ui->MEUN_PAGE, 480, 320);
    lv_obj_set_scrollbar_mode(ui->MEUN_PAGE, LV_SCROLLBAR_MODE_OFF);

    //Write style for MEUN_PAGE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MEUN_PAGE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes MEUN_PAGE_MEUN_
    ui->MEUN_PAGE_MEUN_ = lv_menu_create(ui->MEUN_PAGE);

    //Create sidebar page for menu MEUN_PAGE_MEUN_
    ui->MEUN_PAGE_MEUN__sidebar_page = lv_menu_page_create(ui->MEUN_PAGE_MEUN_, "SETTING");
    lv_menu_set_sidebar_page(ui->MEUN_PAGE_MEUN_, ui->MEUN_PAGE_MEUN__sidebar_page);
    lv_obj_set_scrollbar_mode(ui->MEUN_PAGE_MEUN__sidebar_page, LV_SCROLLBAR_MODE_OFF);

    //Create subpage for MEUN_PAGE_MEUN_
    ui->MEUN_PAGE_MEUN__subpage_1 = lv_menu_page_create(ui->MEUN_PAGE_MEUN_, NULL);
    ui->MEUN_PAGE_MEUN__cont_1 = lv_menu_cont_create(ui->MEUN_PAGE_MEUN__sidebar_page);
    ui->MEUN_PAGE_MEUN__label_1 = lv_label_create(ui->MEUN_PAGE_MEUN__cont_1);
    lv_label_set_text(ui->MEUN_PAGE_MEUN__label_1, "BLE&WIFI");
    lv_obj_set_size(ui->MEUN_PAGE_MEUN__label_1, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->MEUN_PAGE_MEUN__subpage_1, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->MEUN_PAGE_MEUN_, ui->MEUN_PAGE_MEUN__cont_1, ui->MEUN_PAGE_MEUN__subpage_1);

    //Create subpage for MEUN_PAGE_MEUN_
    ui->MEUN_PAGE_MEUN__subpage_2 = lv_menu_page_create(ui->MEUN_PAGE_MEUN_, NULL);
    ui->MEUN_PAGE_MEUN__cont_2 = lv_menu_cont_create(ui->MEUN_PAGE_MEUN__sidebar_page);
    ui->MEUN_PAGE_MEUN__label_2 = lv_label_create(ui->MEUN_PAGE_MEUN__cont_2);
    lv_label_set_text(ui->MEUN_PAGE_MEUN__label_2, "PID_INFO");
    lv_obj_set_size(ui->MEUN_PAGE_MEUN__label_2, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->MEUN_PAGE_MEUN__subpage_2, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->MEUN_PAGE_MEUN_, ui->MEUN_PAGE_MEUN__cont_2, ui->MEUN_PAGE_MEUN__subpage_2);

    //Create subpage for MEUN_PAGE_MEUN_
    ui->MEUN_PAGE_MEUN__subpage_3 = lv_menu_page_create(ui->MEUN_PAGE_MEUN_, NULL);
    ui->MEUN_PAGE_MEUN__cont_3 = lv_menu_cont_create(ui->MEUN_PAGE_MEUN__sidebar_page);
    ui->MEUN_PAGE_MEUN__label_3 = lv_label_create(ui->MEUN_PAGE_MEUN__cont_3);
    lv_label_set_text(ui->MEUN_PAGE_MEUN__label_3, "DEVICE_INFO");
    lv_obj_set_size(ui->MEUN_PAGE_MEUN__label_3, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->MEUN_PAGE_MEUN__subpage_3, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->MEUN_PAGE_MEUN_, ui->MEUN_PAGE_MEUN__cont_3, ui->MEUN_PAGE_MEUN__subpage_3);
    lv_event_send(ui->MEUN_PAGE_MEUN__cont_1, LV_EVENT_CLICKED, NULL);
    lv_obj_set_pos(ui->MEUN_PAGE_MEUN_, 0, 0);
    lv_obj_set_size(ui->MEUN_PAGE_MEUN_, 480, 320);
    lv_obj_set_scrollbar_mode(ui->MEUN_PAGE_MEUN_, LV_SCROLLBAR_MODE_OFF);

    //Write style for MEUN_PAGE_MEUN_, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MEUN_PAGE_MEUN_, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MEUN_PAGE_MEUN_, lv_color_hex(0xcccccc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MEUN_PAGE_MEUN_, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MEUN_PAGE_MEUN_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MEUN_PAGE_MEUN_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default
    static lv_style_t style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default;
    ui_init_style(&style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default);

    lv_style_set_bg_opa(&style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default, 255);
    lv_style_set_bg_color(&style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default, lv_color_hex(0xf2f2f2));
    lv_style_set_bg_grad_dir(&style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_radius(&style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default, 0);
    lv_obj_add_style(ui->MEUN_PAGE_MEUN__sidebar_page, &style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_MEUN_PAGE_MEUN__extra_option_btns_main_default
    static lv_style_t style_MEUN_PAGE_MEUN__extra_option_btns_main_default;
    ui_init_style(&style_MEUN_PAGE_MEUN__extra_option_btns_main_default);

    lv_style_set_text_color(&style_MEUN_PAGE_MEUN__extra_option_btns_main_default, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_MEUN_PAGE_MEUN__extra_option_btns_main_default, &lv_font_Alatsi_Regular_18);
    lv_style_set_text_opa(&style_MEUN_PAGE_MEUN__extra_option_btns_main_default, 255);
    lv_style_set_text_align(&style_MEUN_PAGE_MEUN__extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(&style_MEUN_PAGE_MEUN__extra_option_btns_main_default, 6);
    lv_style_set_pad_bottom(&style_MEUN_PAGE_MEUN__extra_option_btns_main_default, 7);
    lv_obj_add_style(ui->MEUN_PAGE_MEUN__cont_3, &style_MEUN_PAGE_MEUN__extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->MEUN_PAGE_MEUN__cont_2, &style_MEUN_PAGE_MEUN__extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->MEUN_PAGE_MEUN__cont_1, &style_MEUN_PAGE_MEUN__extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_MEUN_PAGE_MEUN__extra_option_btns_main_checked
    static lv_style_t style_MEUN_PAGE_MEUN__extra_option_btns_main_checked;
    ui_init_style(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked);

    lv_style_set_text_color(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, &lv_font_Alatsi_Regular_20);
    lv_style_set_text_opa(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, 255);
    lv_style_set_text_align(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, LV_TEXT_ALIGN_CENTER);
    lv_style_set_border_width(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, 2);
    lv_style_set_border_opa(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, 255);
    lv_style_set_border_color(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, lv_color_hex(0x000000));
    lv_style_set_border_side(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, 2);
    lv_style_set_bg_opa(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, 255);
    lv_style_set_bg_color(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, lv_color_hex(0xd2d2d2));
    lv_style_set_bg_grad_dir(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, LV_GRAD_DIR_HOR);
    lv_style_set_bg_grad_color(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, lv_color_hex(0xffffff));
    lv_style_set_bg_main_stop(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, 0);
    lv_style_set_bg_grad_stop(&style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, 255);
    lv_obj_add_style(ui->MEUN_PAGE_MEUN__cont_3, &style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->MEUN_PAGE_MEUN__cont_2, &style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->MEUN_PAGE_MEUN__cont_1, &style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_MEUN_PAGE_MEUN__extra_main_title_main_default
    static lv_style_t style_MEUN_PAGE_MEUN__extra_main_title_main_default;
    ui_init_style(&style_MEUN_PAGE_MEUN__extra_main_title_main_default);

    lv_style_set_text_color(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, lv_color_hex(0x3f4657));
    lv_style_set_text_font(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, &lv_font_Alatsi_Regular_25);
    lv_style_set_text_opa(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, 255);
    lv_style_set_text_align(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_bg_opa(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, 255);
    lv_style_set_bg_color(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, lv_color_hex(0xd0d0d0));
    lv_style_set_bg_grad_dir(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_pad_top(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, 7);
    lv_style_set_pad_bottom(&style_MEUN_PAGE_MEUN__extra_main_title_main_default, 7);
    lv_menu_t * MEUN_PAGE_MEUN__menu= (lv_menu_t *)ui->MEUN_PAGE_MEUN_;
    lv_obj_t * MEUN_PAGE_MEUN__title = MEUN_PAGE_MEUN__menu->sidebar_header_title;
    lv_obj_set_size(MEUN_PAGE_MEUN__title, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_style(lv_menu_get_sidebar_header(ui->MEUN_PAGE_MEUN_), &style_MEUN_PAGE_MEUN__extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);







    //Write codes MEUN_PAGE_BACK_SET_BTU
    ui->MEUN_PAGE_BACK_SET_BTU = lv_btn_create(ui->MEUN_PAGE);
    ui->MEUN_PAGE_BACK_SET_BTU_label = lv_label_create(ui->MEUN_PAGE_BACK_SET_BTU);
    lv_label_set_text(ui->MEUN_PAGE_BACK_SET_BTU_label, "BACK");
    lv_label_set_long_mode(ui->MEUN_PAGE_BACK_SET_BTU_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->MEUN_PAGE_BACK_SET_BTU_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->MEUN_PAGE_BACK_SET_BTU, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->MEUN_PAGE_BACK_SET_BTU_label, LV_PCT(100));
    lv_obj_set_pos(ui->MEUN_PAGE_BACK_SET_BTU, 404, 285);
    lv_obj_set_size(ui->MEUN_PAGE_BACK_SET_BTU, 71, 30);

    //Write style for MEUN_PAGE_BACK_SET_BTU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->MEUN_PAGE_BACK_SET_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->MEUN_PAGE_BACK_SET_BTU, lv_color_hex(0x6c6c6c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->MEUN_PAGE_BACK_SET_BTU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->MEUN_PAGE_BACK_SET_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->MEUN_PAGE_BACK_SET_BTU, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->MEUN_PAGE_BACK_SET_BTU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->MEUN_PAGE_BACK_SET_BTU, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->MEUN_PAGE_BACK_SET_BTU, &lv_font_blender_pro_bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->MEUN_PAGE_BACK_SET_BTU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->MEUN_PAGE_BACK_SET_BTU, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of MEUN_PAGE.


    //Update current screen layout.
    lv_obj_update_layout(ui->MEUN_PAGE);

    //Init events for screen.
    events_init_MEUN_PAGE(ui);
}
