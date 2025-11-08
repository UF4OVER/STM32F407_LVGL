/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
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
  
	lv_obj_t *START_PAGE;
	bool START_PAGE_del;
	lv_obj_t *START_PAGE_img_1;
	lv_obj_t *MAIN_PAGE;
	bool MAIN_PAGE_del;
	lv_obj_t *MAIN_PAGE_cont_1;
	lv_obj_t *MAIN_PAGE_NAME_INFO;
	lv_obj_t *MAIN_PAGE_HW_LABEL;
	lv_obj_t *MAIN_PAGE_label_46;
	lv_obj_t *MAIN_PAGE_cont_3;
	lv_obj_t *MAIN_PAGE_AH_LABEL;
	lv_obj_t *MAIN_PAGE_WH_LABEL;
	lv_obj_t *MAIN_PAGE_TM_LABEL;
	lv_obj_t *MAIN_PAGE_label_22;
	lv_obj_t *MAIN_PAGE_label_23;
	lv_obj_t *MAIN_PAGE_label_24;
	lv_obj_t *MAIN_PAGE_cont_5;
	lv_obj_t *MAIN_PAGE_CHART_BTU;
	lv_obj_t *MAIN_PAGE_CHART_BTU_label;
	lv_obj_t *MAIN_PAGE_FAN_BTU;
	lv_obj_t *MAIN_PAGE_FAN_BTU_label;
	lv_obj_t *MAIN_PAGE_MEUN_BTU;
	lv_obj_t *MAIN_PAGE_MEUN_BTU_label;
	lv_obj_t *MAIN_PAGE_SET_BTU;
	lv_obj_t *MAIN_PAGE_SET_BTU_label;
	lv_obj_t *MAIN_PAGE_IMODE_LIST;
	lv_obj_t *MAIN_PAGE_MMODE_LIST;
	lv_obj_t *MAIN_PAGE_START_BTU;
	lv_obj_t *MAIN_PAGE_START_BTU_label;
	lv_obj_t *MAIN_PAGE_COMP_BTU;
	lv_obj_t *MAIN_PAGE_COMP_BTU_label;
	lv_obj_t *MAIN_PAGE_cont_4;
	lv_obj_t *MAIN_PAGE_label_2;
	lv_obj_t *MAIN_PAGE_VBUS_LABEL;
	lv_obj_t *MAIN_PAGE_label_3;
	lv_obj_t *MAIN_PAGE_label_7;
	lv_obj_t *MAIN_PAGE_PBUS_LABEL;
	lv_obj_t *MAIN_PAGE_label_8;
	lv_obj_t *MAIN_PAGE_IBUS_LABEL;
	lv_obj_t *MAIN_PAGE_label_9;
	lv_obj_t *MAIN_PAGE_label_1;
	lv_obj_t *MAIN_PAGE_cont_6;
	lv_obj_t *MAIN_PAGE_label_33;
	lv_obj_t *MAIN_PAGE_VOUT_LABEL;
	lv_obj_t *MAIN_PAGE_label_31;
	lv_obj_t *MAIN_PAGE_label_30;
	lv_obj_t *MAIN_PAGE_POUT_LABEL;
	lv_obj_t *MAIN_PAGE_label_28;
	lv_obj_t *MAIN_PAGE_IOUT_LABEL;
	lv_obj_t *MAIN_PAGE_label_26;
	lv_obj_t *MAIN_PAGE_label_25;
	lv_obj_t *MAIN_PAGE_cont_7;
	lv_obj_t *MAIN_PAGE_IET_SPINBOX;
	lv_obj_t *MAIN_PAGE_IET_SPINBOX_btn_plus;
	lv_obj_t *MAIN_PAGE_IET_SPINBOX_btn_minus;
	lv_obj_t *MAIN_PAGE_VET_SPINBOX;
	lv_obj_t *MAIN_PAGE_VET_SPINBOX_btn_plus;
	lv_obj_t *MAIN_PAGE_VET_SPINBOX_btn_minus;
	lv_obj_t *MAIN_PAGE_label_34;
	lv_obj_t *MAIN_PAGE_label_35;
	lv_obj_t *MAIN_PAGE_label_36;
	lv_obj_t *MAIN_PAGE_label_37;
	lv_obj_t *MAIN_PAGE_cont_8;
	lv_obj_t *MAIN_PAGE_MCU_TEMP_LABEL;
	lv_obj_t *MAIN_PAGE_WIFIORBLE_LABEL;
	lv_obj_t *MAIN_PAGE_label_40;
	lv_obj_t *MAIN_PAGE_FAN_LABEL;
	lv_obj_t *MAIN_PAGE_label_42;
	lv_obj_t *MAIN_PAGE_label_43;
	lv_obj_t *MAIN_PAGE_TEMP_LABEL;
	lv_obj_t *MAIN_PAGE_label_45;
	lv_obj_t *MAIN_PAGE_OVP_BTU;
	lv_obj_t *MAIN_PAGE_OVP_BTU_label;
	lv_obj_t *MAIN_PAGE_OCP_BTU;
	lv_obj_t *MAIN_PAGE_OCP_BTU_label;
	lv_obj_t *MAIN_PAGE_VOLTM_BTU;
	lv_obj_t *MAIN_PAGE_VOLTM_BTU_label;
	lv_obj_t *MAIN_PAGE_OSCILLO_BTU;
	lv_obj_t *MAIN_PAGE_OSCILLO_BTU_label;
	lv_obj_t *MAIN_PAGE_WIFIORBLE_IMG;
	lv_obj_t *MAIN_PAGE_TEMP_IMG;
	lv_obj_t *MEUN_PAGE;
	bool MEUN_PAGE_del;
	lv_obj_t *MEUN_PAGE_MEUN_;
	lv_obj_t *MEUN_PAGE_MEUN__sidebar_page;
	lv_obj_t *MEUN_PAGE_MEUN__subpage_1;
	lv_obj_t *MEUN_PAGE_MEUN__cont_1;
	lv_obj_t *MEUN_PAGE_MEUN__label_1;
	lv_obj_t *MEUN_PAGE_MEUN__subpage_2;
	lv_obj_t *MEUN_PAGE_MEUN__cont_2;
	lv_obj_t *MEUN_PAGE_MEUN__label_2;
	lv_obj_t *MEUN_PAGE_MEUN__subpage_3;
	lv_obj_t *MEUN_PAGE_MEUN__cont_3;
	lv_obj_t *MEUN_PAGE_MEUN__label_3;
	lv_obj_t *MEUN_PAGE_BACK_SET_BTU;
	lv_obj_t *MEUN_PAGE_BACK_SET_BTU_label;
	lv_obj_t *OSCILLO_PAGE;
	bool OSCILLO_PAGE_del;
	lv_obj_t *OSCILLO_PAGE_chart_1;
	lv_obj_t *OSCILLO_PAGE_cont_1;
	lv_obj_t *OSCILLO_PAGE_BACK_OSCILLO_BTU;
	lv_obj_t *OSCILLO_PAGE_BACK_OSCILLO_BTU_label;
	lv_obj_t *OSCILLO_PAGE_AUTO_BTU;
	lv_obj_t *OSCILLO_PAGE_AUTO_BTU_label;
	lv_obj_t *OSCILLO_PAGE_RIGHT_BTU;
	lv_obj_t *OSCILLO_PAGE_RIGHT_BTU_label;
	lv_obj_t *OSCILLO_PAGE_LEFT_BTU;
	lv_obj_t *OSCILLO_PAGE_LEFT_BTU_label;
	lv_obj_t *OSCILLO_PAGE_DOWN_BTU;
	lv_obj_t *OSCILLO_PAGE_DOWN_BTU_label;
	lv_obj_t *OSCILLO_PAGE_UP_BTU;
	lv_obj_t *OSCILLO_PAGE_UP_BTU_label;
	lv_obj_t *OSCILLO_PAGE_STOP_BTU;
	lv_obj_t *OSCILLO_PAGE_STOP_BTU_label;
	lv_obj_t *OSCILLO_PAGE_label_2;
	lv_obj_t *OSCILLO_PAGE_label_3;
	lv_obj_t *OSCILLO_PAGE_label_5;
	lv_obj_t *OSCILLO_PAGE_label_4;
	lv_obj_t *OSCILLO_PAGE_label_7;
	lv_obj_t *OSCILLO_PAGE_label_6;
	lv_obj_t *OSCILLO_PAGE_label_8;
	lv_obj_t *OSCILLO_PAGE_label_9;
	lv_obj_t *OSCILLO_PAGE_label_10;
	lv_obj_t *OSCILLO_PAGE_label_11;
	lv_obj_t *OSCILLO_PAGE_label_12;
	lv_obj_t *OSCILLO_PAGE_label_13;
	lv_obj_t *OSCILLO_PAGE_label_14;
	lv_obj_t *OSCILLO_PAGE_label_15;
	lv_obj_t *OSCILLO_PAGE_label_16;
	lv_obj_t *OSCILLO_PAGE_label_17;
	lv_obj_t *OSCILLO_PAGE_label_19;
	lv_obj_t *OSCILLO_PAGE_label_18;
	lv_obj_t *OSCILLO_PAGE_label_21;
	lv_obj_t *OSCILLO_PAGE_label_20;
	lv_obj_t *OSCILLO_PAGE_label_22;
	lv_obj_t *OSCILLO_PAGE_line_1;
	lv_obj_t *CHART_PAGE;
	bool CHART_PAGE_del;
	lv_obj_t *CHART_PAGE_UI_CHART;
	lv_chart_series_t *CHART_PAGE_UI_CHART_0;
	lv_chart_series_t *CHART_PAGE_UI_CHART_1;
	lv_obj_t *CHART_PAGE_BACK_CHART_BTU;
	lv_obj_t *CHART_PAGE_BACK_CHART_BTU_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_START_PAGE(lv_ui *ui);
void setup_scr_MAIN_PAGE(lv_ui *ui);
void setup_scr_MEUN_PAGE(lv_ui *ui);
void setup_scr_OSCILLO_PAGE(lv_ui *ui);
void setup_scr_CHART_PAGE(lv_ui *ui);
LV_IMG_DECLARE(_Kang_Tao_Logo_02_CP2077_alpha_460x100);
LV_IMG_DECLARE(_offline_24px_alpha_24x24);
LV_IMG_DECLARE(_temperature_24px_alpha_24x24);

LV_FONT_DECLARE(lv_font_blender_pro_bold_18)
LV_FONT_DECLARE(lv_font_blender_pro_bold_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_blender_pro_bold_24)
LV_FONT_DECLARE(lv_font_blender_pro_bold_28)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_18)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_20)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_25)
LV_FONT_DECLARE(lv_font_blender_pro_bold_20)
LV_FONT_DECLARE(lv_font_blender_pro_bold_14)


#ifdef __cplusplus
}
#endif
#endif
