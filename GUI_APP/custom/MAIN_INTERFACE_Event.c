#include "MAIN_INTERFACE_Event.h"
 #include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void MAIN_SET_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        if(guider_ui.MEUN_PAGE) lv_scr_load(guider_ui.MEUN_PAGE);
    }
}

static void MAIN_START_toggle_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_VALUE_CHANGED) return;

    lv_obj_t * btn = lv_event_get_target(e);
    if(!btn) return;

    lv_obj_t * list = guider_ui.MAIN_PAGE_MMODE_LIST;

    if(lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        if(guider_ui.MAIN_PAGE_START_BTU_label) lv_label_set_text(guider_ui.MAIN_PAGE_START_BTU_label, "STOP");
        lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF1122), LV_PART_MAIN | LV_STATE_CHECKED);

        /* 禁用 MAIN_MAIN_LLIMMODE_LIST */
        if(list) {
            lv_obj_add_state(list, LV_STATE_DISABLED);
            lv_obj_clear_flag(list, LV_OBJ_FLAG_CLICKABLE);
            // 设置颜色为灰色
            lv_obj_set_style_bg_color(list, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DISABLED);
        }

    } else {
        if(guider_ui.MAIN_PAGE_START_BTU_label) lv_label_set_text(guider_ui.MAIN_PAGE_START_BTU_label, "RUN");
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x22CC22), LV_PART_MAIN | LV_STATE_DEFAULT);

        /* 启用 MAIN_MAIN_LLIMMODE_LIST */
        if(list) {
            lv_obj_clear_state(list, LV_STATE_DISABLED);
            lv_obj_add_flag(list, LV_OBJ_FLAG_CLICKABLE);
        }
    }
}

static void MAIN_PAGE_FAN_BTU_toggle_handler(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_VALUE_CHANGED) return;

    lv_obj_t * btn = lv_event_get_target(e);
    if(!btn) return;

    if(lv_obj_has_state(btn, LV_STATE_CHECKED)) {
        if(guider_ui.MAIN_PAGE_FAN_BTU_label) lv_label_set_text(guider_ui.MAIN_PAGE_FAN_BTU_label, "MANU");
        lv_obj_set_style_bg_color(btn, lv_color_hex(0xFF1122), LV_PART_MAIN | LV_STATE_CHECKED);


    } else {
        if(guider_ui.MAIN_PAGE_FAN_BTU_label) lv_label_set_text(guider_ui.MAIN_PAGE_FAN_BTU_label, "AUTO");
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x22CC22), LV_PART_MAIN | LV_STATE_DEFAULT);


    }
}



/* 辅助：只保留数字和最多一个小数点，结果写入 dst，并返回 dst */
static char * sanitize_numeric(const char * src, char * dst, size_t dst_len)
{
    if(!src || !dst || dst_len == 0) return dst;
    size_t di = 0;
    int seen_dot = 0;
    for(size_t i = 0; src[i] != '\0' && di + 1 < dst_len; ++i) {
        char c = src[i];
        if(c >= '0' && c <= '9') {
            dst[di++] = c;
        } else if(c == '.' && !seen_dot) {
            seen_dot = 1;
            /* 避止小数点为第一位，允许 ".5" -> "0.5" 由格式化处理 */
            dst[di++] = c;
        }
        /* 其它字符忽略 */
    }
    dst[di] = '\0';
    return dst;
}

static lv_obj_t * ovp_ta = NULL;
static lv_obj_t * ovp_kb = NULL;

static void ovp_kb_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_READY) {
        /* 确认：把 textarea 的数字内容解析并按 "OVP:xx.xxV" 写回标签 */
        if(ovp_ta && guider_ui.MAIN_PAGE_OVP_BTU_label) {
            const char * txt = lv_textarea_get_text(ovp_ta);
            char clean[32];
            sanitize_numeric(txt ? txt : "", clean, sizeof(clean));

            /* 若为空则不修改 */
            if(clean[0] != '\0') {
                char * endp = NULL;
                double val = strtod(clean, &endp);
                (void)endp;
                /* 限幅到 [OVP_MIN_V, OVP_MAX_V] */
                val = clampd(val, (double)OVP_MIN_V, (double)OVP_MAX_V);
                char buf[32];
                snprintf(buf, sizeof(buf), "OVP:%05.2fV", val);
                lv_label_set_text(guider_ui.MAIN_PAGE_OVP_BTU_label, buf);
            }
        }
    }

    /* READY 或 CANCEL 都要销毁输入控件 */
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        if(ovp_kb) {
            lv_obj_del(ovp_kb);
            ovp_kb = NULL;
        }
        if(ovp_ta) {
            lv_obj_del(ovp_ta);
            ovp_ta = NULL;
        }
    }
}

static void ovp_ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_VALUE_CHANGED) return;

    if(!ovp_ta) return;

    const char * cur = lv_textarea_get_text(ovp_ta);
    if(!cur) return;

    char clean[32];
    sanitize_numeric(cur, clean, sizeof(clean));
    if(strcmp(clean, cur) != 0) {
        /* 如果过滤后与当前不同，替换内容并把光标移到末尾 */
        lv_textarea_set_text(ovp_ta, clean);
        lv_textarea_set_cursor_pos(ovp_ta, (int32_t)strlen(clean));
    }
}
// c
static void create_ovp_input_widgets(void)
{
    /* 如果已经存在则不用重复创建 */
    if(ovp_ta || ovp_kb) return;

    lv_obj_t * parent = lv_scr_act();
    /* 创建单行文本输入框 */
    ovp_ta = lv_textarea_create(parent);
    lv_obj_set_width(ovp_ta, 180);
    lv_obj_align(ovp_ta, LV_ALIGN_CENTER, 0, -60);
    lv_textarea_set_one_line(ovp_ta, true);
    lv_textarea_set_max_length(ovp_ta, 16);
    /* 仅接受数字和小数点（若当前 LVGL 版本支持）*/
    lv_textarea_set_accepted_chars(ovp_ta, "0123456789.");
    lv_obj_add_event_cb(ovp_ta, ovp_ta_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /* 预填充数值部分（从标签提取数字） */
    if(guider_ui.MAIN_PAGE_OVP_BTU_label) {
        const char * cur = lv_label_get_text(guider_ui.MAIN_PAGE_OVP_BTU_label);
        if(cur) {
            const char * p = cur;
            while(*p && (*p < '0' || *p > '9') && *p != '.') ++p;
            char buf[32] = {0};
            size_t i = 0;
            while(*p && ( ((*p) >= '0' && (*p) <= '9') || (*p) == '.' ) && i + 1 < sizeof(buf)) {
                buf[i++] = *p++;
            }
            buf[i] = '\0';
            if(buf[0] != '\0') lv_textarea_set_text(ovp_ta, buf);
        }
    }

    /* 创建数字键盘并关联到 textarea */
    ovp_kb = lv_keyboard_create(parent);
    /* 尝试设置为数字模式（若当前 LVGL 版本支持） */
    lv_keyboard_set_mode(ovp_kb, LV_KEYBOARD_MODE_NUMBER);
    lv_keyboard_set_textarea(ovp_kb, ovp_ta);
    lv_obj_align(ovp_kb, LV_ALIGN_CENTER, 0, 60);
    /* 重要修复：使用 LV_EVENT_ALL 或分别注册每个事件，避免按位或无效导致回调不触发 */
    lv_obj_add_event_cb(ovp_kb, ovp_kb_event_cb, LV_EVENT_ALL, NULL);
}
static void MAIN_PAGE_OVP_BTU_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_CLICKED) return;

    /* 点击时显示数字输入（键盘 + 文本框） 只需要数字键盘
     * 默认文本是	lv_label_set_text(ui->MAIN_PAGE_OVP_BTU_label, "OVP:24.00V");
     * 用户只能编辑数字部分，可以在回调中处理格式化
     例如只允许输入数字和小数点，最终保存时加上前缀 "OVP:" 和后缀 "V"
     这里简化处理，只让用户输入数字部分，格式化留给 READY 事件处理
    */
    create_ovp_input_widgets();
}

/* ===================== OCP 输入逻辑 ===================== */
static lv_obj_t * ocp_ta = NULL;
static lv_obj_t * ocp_kb = NULL;

static void ocp_kb_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_READY) {
        if(ocp_ta && guider_ui.MAIN_PAGE_OCP_BTU_label) {
            const char * txt = lv_textarea_get_text(ocp_ta);
            char clean[32];
            sanitize_numeric(txt ? txt : "", clean, sizeof(clean));
            if(clean[0] != '\0') {
                char * endp = NULL;
                double val = strtod(clean, &endp);
                (void)endp;
                /* 限幅到 [OCP_MIN_A, OCP_MAX_A] */
                val = clampd(val, (double)OCP_MIN_A, (double)OCP_MAX_A);
                char buf[32];
                snprintf(buf, sizeof(buf), "OCP:%05.2fA", val);
                lv_label_set_text(guider_ui.MAIN_PAGE_OCP_BTU_label, buf);
            }
        }
    }

    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        if(ocp_kb) { lv_obj_del(ocp_kb); ocp_kb = NULL; }
        if(ocp_ta) { lv_obj_del(ocp_ta); ocp_ta = NULL; }
    }
}

static void ocp_ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_VALUE_CHANGED) return;
    if(!ocp_ta) return;

    const char * cur = lv_textarea_get_text(ocp_ta);
    if(!cur) return;

    char clean[32];
    sanitize_numeric(cur, clean, sizeof(clean));
    if(strcmp(clean, cur) != 0) {
        lv_textarea_set_text(ocp_ta, clean);
        lv_textarea_set_cursor_pos(ocp_ta, (int32_t)strlen(clean));
    }
}

static void create_ocp_input_widgets(void)
{
    if(ocp_ta || ocp_kb) return;

    lv_obj_t * parent = lv_scr_act();
    ocp_ta = lv_textarea_create(parent);
    lv_obj_set_width(ocp_ta, 180);
    lv_obj_align(ocp_ta, LV_ALIGN_CENTER, 0, -60);
    lv_textarea_set_one_line(ocp_ta, true);
    lv_textarea_set_max_length(ocp_ta, 16);
    lv_textarea_set_accepted_chars(ocp_ta, "0123456789.");
    lv_obj_add_event_cb(ocp_ta, ocp_ta_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /* 从标签预填数值部分 */
    if(guider_ui.MAIN_PAGE_OCP_BTU_label) {
        const char * cur = lv_label_get_text(guider_ui.MAIN_PAGE_OCP_BTU_label);
        if(cur) {
            const char * p = cur;
            while(*p && (*p < '0' || *p > '9') && *p != '.') ++p;
            char buf[32] = {0};
            size_t i = 0;
            while(*p && ( ((*p) >= '0' && (*p) <= '9') || (*p) == '.' ) && i + 1 < sizeof(buf)) {
                buf[i++] = *p++;
            }
            buf[i] = '\0';
            if(buf[0] != '\0') lv_textarea_set_text(ocp_ta, buf);
        }
    }

    ocp_kb = lv_keyboard_create(parent);
    lv_keyboard_set_mode(ocp_kb, LV_KEYBOARD_MODE_NUMBER);
    lv_keyboard_set_textarea(ocp_kb, ocp_ta);
    lv_obj_align(ocp_kb, LV_ALIGN_CENTER, 0, 60);
    lv_obj_add_event_cb(ocp_kb, ocp_kb_event_cb, LV_EVENT_ALL, NULL);
}

static void MAIN_PAGE_OCP_BTU_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_CLICKED) return;
    create_ocp_input_widgets();
}


void MAIN_INTERFACE_events_init(lv_ui *ui)
{
    if(ui->MAIN_PAGE_SET_BTU) {
        lv_obj_add_event_cb(ui->MAIN_PAGE_SET_BTU, MAIN_SET_event_handler, LV_EVENT_ALL, NULL);
    }

    if(ui->MAIN_PAGE_START_BTU) {
        lv_obj_add_flag(ui->MAIN_PAGE_START_BTU, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_add_event_cb(ui->MAIN_PAGE_START_BTU, MAIN_START_toggle_handler, LV_EVENT_VALUE_CHANGED, NULL);
    }
    if (ui->MAIN_PAGE_FAN_BTU) {
        lv_obj_add_flag(ui->MAIN_PAGE_FAN_BTU, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_add_event_cb(ui->MAIN_PAGE_FAN_BTU, MAIN_PAGE_FAN_BTU_toggle_handler, LV_EVENT_VALUE_CHANGED, NULL);
    }
    if(ui->MAIN_PAGE_OVP_BTU) {
        lv_obj_add_event_cb(ui->MAIN_PAGE_OVP_BTU, MAIN_PAGE_OVP_BTU_event_handler, LV_EVENT_ALL, NULL);
    }
    if(ui->MAIN_PAGE_OCP_BTU) {
        lv_obj_add_event_cb(ui->MAIN_PAGE_OCP_BTU, MAIN_PAGE_OCP_BTU_event_handler, LV_EVENT_ALL, NULL);
    }

}