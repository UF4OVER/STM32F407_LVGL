/*
* Copyright 2025 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *START;
	bool START_del;
	lv_obj_t *START_img_1;
	lv_obj_t *START_start_label;
	lv_obj_t *MAIN;
	bool MAIN_del;
	lv_obj_t *MAIN_ILIMMODE_LIST;
	lv_obj_t *MAIN_cont_1;
	lv_obj_t *MAIN_NAME_INFO;
	lv_obj_t *MAIN_label_2;
	lv_obj_t *MAIN_HW_INFO;
	lv_obj_t *MAIN_cont_2;
	lv_obj_t *MAIN_label_6;
	lv_obj_t *MAIN_VBUS_INFO;
	lv_obj_t *MAIN_label_8;
	lv_obj_t *MAIN_IBUS_INFO;
	lv_obj_t *MAIN_label_10;
	lv_obj_t *MAIN_label_11;
	lv_obj_t *MAIN_label_12;
	lv_obj_t *MAIN_PBUS__INFO;
	lv_obj_t *MAIN_label_14;
	lv_obj_t *MAIN_cont_3;
	lv_obj_t *MAIN_label_23;
	lv_obj_t *MAIN_VOUT_INFO;
	lv_obj_t *MAIN_label_21;
	lv_obj_t *MAIN_IOUT_INFO;
	lv_obj_t *MAIN_label_19;
	lv_obj_t *MAIN_label_18;
	lv_obj_t *MAIN_label_17;
	lv_obj_t *MAIN_POUT_INFO;
	lv_obj_t *MAIN_label_15;
	lv_obj_t *MAIN_cont_4;
	lv_obj_t *MAIN_ISET_SPINBOX;
	lv_obj_t *MAIN_ISET_SPINBOX_btn;
	lv_obj_t *MAIN_ISET_SPINBOX_btn_minus;
	lv_obj_t *MAIN_VSET_SPINBOX;
	lv_obj_t *MAIN_VSET_SPINBOX_btn;
	lv_obj_t *MAIN_VSET_SPINBOX_btn_minus;
	lv_obj_t *MAIN_label_24;
	lv_obj_t *MAIN_label_25;
	lv_obj_t *MAIN_cont_5;
	lv_obj_t *MAIN_label_28;
	lv_obj_t *MAIN_label_26;
	lv_obj_t *MAIN_TEMP_INFO;
	lv_obj_t *MAIN_label_30;
	lv_obj_t *MAIN_EFFECT_INFO;
	lv_obj_t *MAIN_FAN_INFO;
	lv_obj_t *MAIN_label_40;
	lv_obj_t *MAIN_BLE_INFO;
	lv_obj_t *MAIN_START_BTU;
	lv_obj_t *MAIN_START_BTU_label;
	lv_obj_t *MAIN_OVP_BTU;
	lv_obj_t *MAIN_OVP_BTU_label;
	lv_obj_t *MAIN_OCP_BTU;
	lv_obj_t *MAIN_OCP_BTU_label;
	lv_obj_t *MAIN_cont_6;
	lv_obj_t *MAIN_AH_INFO;
	lv_obj_t *MAIN_label_35;
	lv_obj_t *MAIN_label_36;
	lv_obj_t *MAIN_WH_INFO;
	lv_obj_t *MAIN_TIME_INFO;
	lv_obj_t *MAIN_label_39;
	lv_obj_t *MAIN_LLIMMODE_LIST;
	lv_obj_t *MAIN_cont_7;
	lv_obj_t *MAIN_label_49;
	lv_obj_t *MAIN_STATE_INFO;
	lv_obj_t *MAIN_SET_BTU;
	lv_obj_t *MAIN_SET_BTU_label;
	lv_obj_t *MAIN_MEUN_BTU;
	lv_obj_t *MAIN_MEUN_BTU_label;
	lv_obj_t *MAIN_FAN_BTU;
	lv_obj_t *MAIN_FAN_BTU_label;
	lv_obj_t *MAIN_btn_7;
	lv_obj_t *MAIN_btn_7_label;
	lv_obj_t *MAIN_COMP_BTU;
	lv_obj_t *MAIN_COMP_BTU_label;
	lv_obj_t *SEETING;
	bool SEETING_del;
	lv_obj_t *SEETING_SET_MEUN;
	lv_obj_t *SEETING_SET_MEUN_sidebar_page;
	lv_obj_t *SEETING_SET_MEUN_subpage_1;
	lv_obj_t *SEETING_SET_MEUN_cont_1;
	lv_obj_t *SEETING_SET_MEUN_label_1;
	lv_obj_t *SEETING_SET_MEUN_subpage_2;
	lv_obj_t *SEETING_SET_MEUN_cont_2;
	lv_obj_t *SEETING_SET_MEUN_label_2;
	lv_obj_t *SEETING_SET_MEUN_subpage_3;
	lv_obj_t *SEETING_SET_MEUN_cont_3;
	lv_obj_t *SEETING_SET_MEUN_label_3;
	lv_obj_t *SEETING_SET_MEUN_subpage_4;
	lv_obj_t *SEETING_SET_MEUN_cont_4;
	lv_obj_t *SEETING_SET_MEUN_label_4;
	lv_obj_t *SEETING_SET_MEUN_subpage_5;
	lv_obj_t *SEETING_SET_MEUN_cont_5;
	lv_obj_t *SEETING_SET_MEUN_label_5;

		// --- Added: SETTING subpage content ---
		// Subpage 1: BLE & WiFi
		lv_obj_t *SEETING_BLE_row;
		lv_obj_t *SEETING_BLE_label;
		lv_obj_t *SEETING_BLE_switch;
		lv_obj_t *SEETING_WIFI_row;
		lv_obj_t *SEETING_WIFI_label;
		lv_obj_t *SEETING_WIFI_switch;

		// Subpage 2: Device & Info
		lv_obj_t *SEETING_DEVICE_row_name;
		lv_obj_t *SEETING_DEVICE_label_name;
		lv_obj_t *SEETING_DEVICE_row_sn;
		lv_obj_t *SEETING_DEVICE_label_sn;
		lv_obj_t *SEETING_DEVICE_row_fw;
		lv_obj_t *SEETING_DEVICE_label_fw;

		// Subpage 3: Themes
		lv_obj_t *SEETING_THEME_row_dark;
		lv_obj_t *SEETING_THEME_label_dark;
		lv_obj_t *SEETING_THEME_switch_dark;
		lv_obj_t *SEETING_THEME_row_contrast;
		lv_obj_t *SEETING_THEME_label_contrast;
		lv_obj_t *SEETING_THEME_switch_contrast;

		// Subpage 4: PID & Info
		lv_obj_t *SEETING_PID_row_enable;
		lv_obj_t *SEETING_PID_label_enable;
		lv_obj_t *SEETING_PID_switch_enable;
		lv_obj_t *SEETING_PID_row_kp;
		lv_obj_t *SEETING_PID_label_kp;
		lv_obj_t *SEETING_PID_row_ki;
		lv_obj_t *SEETING_PID_label_ki;
		lv_obj_t *SEETING_PID_row_kd;
		lv_obj_t *SEETING_PID_label_kd;

		// Subpage 5: Boot Version
		lv_obj_t *SEETING_BOOT_row_ver;
		lv_obj_t *SEETING_BOOT_label_ver;

		// Back button on SETTING screen
		lv_obj_t *SEETING_BACK_BTN;
		lv_obj_t *SEETING_BACK_BTN_label;
	}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_START(lv_ui *ui);
void setup_scr_MAIN(lv_ui *ui);
void setup_scr_SEETING(lv_ui *ui);
LV_IMG_DECLARE(_4b2557acd3a9c3c4c0847bc3d36e804_alpha_450x150);

LV_FONT_DECLARE(lv_font_blender_pro_bold_18)
LV_FONT_DECLARE(lv_font_blender_pro_bold_16)
LV_FONT_DECLARE(lv_font_blender_pro_bold_20)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_blender_pro_bold_26)
LV_FONT_DECLARE(lv_font_blender_pro_bold_24)

// --- UI Color Palette (centralized) ---
#ifndef UI_COLOR_SCREEN_BG
#define UI_COLOR_SCREEN_BG          0x8e8e8e
#endif
#ifndef UI_COLOR_SIDEBAR_BG
#define UI_COLOR_SIDEBAR_BG         0xdaf2f8
#endif
#ifndef UI_COLOR_ROW_BG
#define UI_COLOR_ROW_BG             0xf5f5f5
#endif
#ifndef UI_COLOR_BACK_BTN_BG
#define UI_COLOR_BACK_BTN_BG        0x303030
#endif
#ifndef UI_COLOR_BACK_BTN_TEXT
#define UI_COLOR_BACK_BTN_TEXT      0xffffff
#endif
#ifndef UI_COLOR_MENU_TEXT
#define UI_COLOR_MENU_TEXT          0x151212
#endif
#ifndef UI_COLOR_MENU_TEXT_CHECK
#define UI_COLOR_MENU_TEXT_CHECK    0x9ab700
#endif
#ifndef UI_COLOR_MENU_CHECK_BG
#define UI_COLOR_MENU_CHECK_BG      0x00e0b8
#endif
#ifndef UI_COLOR_TITLE_TEXT
#define UI_COLOR_TITLE_TEXT         0x41485a
#endif
#ifndef UI_COLOR_TITLE_BG
#define UI_COLOR_TITLE_BG           0xffffff
#endif

#ifdef __cplusplus
}
#endif
#endif
