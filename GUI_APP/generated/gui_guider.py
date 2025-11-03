# Copyright 2025 NXP
# NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=480,h=320)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(480*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 480
disp_drv.ver_res = 320
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%02d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%02d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%02d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%02d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

def START_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

def MAIN_ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)

# Create START
START = lv.obj()
START.set_size(480, 320)
START.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for START, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
START.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
START.set_style_bg_color(lv.color_hex(0x0e0e0e), lv.PART.MAIN|lv.STATE.DEFAULT)

# Create START_start_kangtao
START_start_kangtao = lv.animimg(START)
START_start_kangtao.set_start_cb(startPos)
START_start_kangtao_imgs = [None]*1
START_start_kangtao_imgs[0] = load_image(r"E:\lvgl_project\LM32\generated\MicroPython\4b2557acd3a9c3c4c0847bc3d36e804_300_100.png")
START_start_kangtao.set_src(START_start_kangtao_imgs, 1, False)
START_start_kangtao.set_duration(30*1)
START_start_kangtao.set_repeat_count(lv.ANIM_REPEAT.INFINITE)
lv.img.__cast__(START_start_kangtao).set_src(START_start_kangtao_imgs[0])
START_start_kangtao.set_pos(90, 110)
START_start_kangtao.set_size(300, 100)
START_start_kangtao.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)

START.update_layout()
# Create MAIN
MAIN = lv.obj()
g_kb_MAIN = lv.keyboard(MAIN)
g_kb_MAIN.add_event_cb(lambda e: MAIN_ta_event_cb(e, g_kb_MAIN), lv.EVENT.ALL, None)
g_kb_MAIN.add_flag(lv.obj.FLAG.HIDDEN)
g_kb_MAIN.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN.set_size(480, 320)
MAIN.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN.set_style_bg_color(lv.color_hex(0x8e8e8e), lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_ILIMMODE_LIST
MAIN_ILIMMODE_LIST = lv.dropdown(MAIN)
MAIN_ILIMMODE_LIST.set_options("CC\nCV")
MAIN_ILIMMODE_LIST.set_pos(340, 113)
MAIN_ILIMMODE_LIST.set_size(68, 30)
MAIN_ILIMMODE_LIST.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_ILIMMODE_LIST, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_ILIMMODE_LIST.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ILIMMODE_LIST.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MAIN_ILIMMODE_LIST, Part: lv.PART.SELECTED, State: lv.STATE.CHECKED.
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked = lv.style_t()
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.init()
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.set_text_color(lv.color_hex(0xffffff))
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.set_text_font(test_font("montserratMedium", 12))
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.set_border_width(1)
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.set_border_opa(255)
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.set_border_color(lv.color_hex(0xe1e6ee))
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.set_radius(3)
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.set_bg_opa(255)
style_MAIN_ILIMMODE_LIST_extra_list_selected_checked.set_bg_color(lv.color_hex(0x00a1b5))
MAIN_ILIMMODE_LIST.get_list().add_style(style_MAIN_ILIMMODE_LIST_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)
# Set style for MAIN_ILIMMODE_LIST, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MAIN_ILIMMODE_LIST_extra_list_main_default = lv.style_t()
style_MAIN_ILIMMODE_LIST_extra_list_main_default.init()
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_max_height(90)
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_text_color(lv.color_hex(0x0D3055))
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_text_font(test_font("montserratMedium", 12))
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_border_width(1)
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_border_opa(255)
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_border_color(lv.color_hex(0xe1e6ee))
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_radius(3)
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_bg_opa(255)
style_MAIN_ILIMMODE_LIST_extra_list_main_default.set_bg_color(lv.color_hex(0xffffff))
MAIN_ILIMMODE_LIST.get_list().add_style(style_MAIN_ILIMMODE_LIST_extra_list_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MAIN_ILIMMODE_LIST, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default = lv.style_t()
style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default.init()
style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default.set_radius(3)
style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default.set_bg_opa(255)
style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default.set_bg_color(lv.color_hex(0x00ff00))
MAIN_ILIMMODE_LIST.get_list().add_style(style_MAIN_ILIMMODE_LIST_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create MAIN_cont_1
MAIN_cont_1 = lv.obj(MAIN)
MAIN_cont_1.set_pos(5, 5)
MAIN_cont_1.set_size(470, 30)
MAIN_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_1.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_1.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_NAME_INFO
MAIN_NAME_INFO = lv.label(MAIN_cont_1)
MAIN_NAME_INFO.set_text("UF4OVER POWER")
MAIN_NAME_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_NAME_INFO.set_pos(3, 5)
MAIN_NAME_INFO.set_size(150, 20)
MAIN_NAME_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_NAME_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_NAME_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_NAME_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_2
MAIN_label_2 = lv.label(MAIN_cont_1)
MAIN_label_2.set_text("FW:")
MAIN_label_2.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_2.set_pos(345, 5)
MAIN_label_2.set_size(36, 20)
MAIN_label_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_HW_INFO
MAIN_HW_INFO = lv.label(MAIN_cont_1)
MAIN_HW_INFO.set_text("1.41.120")
MAIN_HW_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_HW_INFO.set_pos(387, 5)
MAIN_HW_INFO.set_size(70, 20)
MAIN_HW_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_HW_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_HW_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_HW_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_cont_2
MAIN_cont_2 = lv.obj(MAIN)
MAIN_cont_2.set_pos(5, 42)
MAIN_cont_2.set_size(180, 100)
MAIN_cont_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_cont_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_cont_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_2.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_2.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_label_6
MAIN_label_6 = lv.label(MAIN_cont_2)
MAIN_label_6.set_text("VBUS:")
MAIN_label_6.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_6.set_pos(5, 0)
MAIN_label_6.set_size(70, 30)
MAIN_label_6.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_VBUS_INFO
MAIN_VBUS_INFO = lv.label(MAIN_cont_2)
MAIN_VBUS_INFO.set_text("00.00")
MAIN_VBUS_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_VBUS_INFO.set_pos(75, 0)
MAIN_VBUS_INFO.set_size(70, 30)
MAIN_VBUS_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_VBUS_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_VBUS_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VBUS_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_8
MAIN_label_8 = lv.label(MAIN_cont_2)
MAIN_label_8.set_text("IBUS:")
MAIN_label_8.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_8.set_pos(5, 32)
MAIN_label_8.set_size(70, 30)
MAIN_label_8.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_IBUS_INFO
MAIN_IBUS_INFO = lv.label(MAIN_cont_2)
MAIN_IBUS_INFO.set_text("00.00")
MAIN_IBUS_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_IBUS_INFO.set_pos(75, 32)
MAIN_IBUS_INFO.set_size(70, 30)
MAIN_IBUS_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_IBUS_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_IBUS_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IBUS_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_10
MAIN_label_10 = lv.label(MAIN_cont_2)
MAIN_label_10.set_text("V")
MAIN_label_10.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_10.set_pos(150, 0)
MAIN_label_10.set_size(30, 30)
MAIN_label_10.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_11
MAIN_label_11 = lv.label(MAIN_cont_2)
MAIN_label_11.set_text("A")
MAIN_label_11.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_11.set_pos(150, 32)
MAIN_label_11.set_size(30, 30)
MAIN_label_11.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_11.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_11.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_12
MAIN_label_12 = lv.label(MAIN_cont_2)
MAIN_label_12.set_text("PBUS:")
MAIN_label_12.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_12.set_pos(5, 65)
MAIN_label_12.set_size(70, 30)
MAIN_label_12.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_12.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PBUS__INFO
MAIN_PBUS__INFO = lv.label(MAIN_cont_2)
MAIN_PBUS__INFO.set_text("00.00")
MAIN_PBUS__INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_PBUS__INFO.set_pos(75, 65)
MAIN_PBUS__INFO.set_size(70, 30)
MAIN_PBUS__INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PBUS__INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PBUS__INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PBUS__INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_14
MAIN_label_14 = lv.label(MAIN_cont_2)
MAIN_label_14.set_text("W")
MAIN_label_14.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_14.set_pos(150, 65)
MAIN_label_14.set_size(30, 30)
MAIN_label_14.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_14.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_14.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_cont_3
MAIN_cont_3 = lv.obj(MAIN)
MAIN_cont_3.set_pos(5, 150)
MAIN_cont_3.set_size(180, 100)
MAIN_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_cont_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_3.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_3.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_label_23
MAIN_label_23 = lv.label(MAIN_cont_3)
MAIN_label_23.set_text("VOUT:")
MAIN_label_23.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_23.set_pos(5, 0)
MAIN_label_23.set_size(70, 30)
MAIN_label_23.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_23.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_23.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_VOUT_INFO
MAIN_VOUT_INFO = lv.label(MAIN_cont_3)
MAIN_VOUT_INFO.set_text("00.00")
MAIN_VOUT_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_VOUT_INFO.set_pos(75, 0)
MAIN_VOUT_INFO.set_size(70, 30)
MAIN_VOUT_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_VOUT_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_VOUT_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VOUT_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_21
MAIN_label_21 = lv.label(MAIN_cont_3)
MAIN_label_21.set_text("IOUT:")
MAIN_label_21.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_21.set_pos(5, 32)
MAIN_label_21.set_size(70, 30)
MAIN_label_21.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_21, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_21.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_21.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_IOUT_INFO
MAIN_IOUT_INFO = lv.label(MAIN_cont_3)
MAIN_IOUT_INFO.set_text("00.00")
MAIN_IOUT_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_IOUT_INFO.set_pos(75, 32)
MAIN_IOUT_INFO.set_size(70, 30)
MAIN_IOUT_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_IOUT_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_IOUT_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_IOUT_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_19
MAIN_label_19 = lv.label(MAIN_cont_3)
MAIN_label_19.set_text("V")
MAIN_label_19.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_19.set_pos(150, 0)
MAIN_label_19.set_size(30, 30)
MAIN_label_19.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_19, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_19.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_19.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_18
MAIN_label_18 = lv.label(MAIN_cont_3)
MAIN_label_18.set_text("A")
MAIN_label_18.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_18.set_pos(150, 32)
MAIN_label_18.set_size(30, 32)
MAIN_label_18.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_18, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_18.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_18.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_17
MAIN_label_17 = lv.label(MAIN_cont_3)
MAIN_label_17.set_text("POUT:")
MAIN_label_17.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_17.set_pos(5, 65)
MAIN_label_17.set_size(70, 30)
MAIN_label_17.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_17, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_17.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_17.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_POUT_INFO
MAIN_POUT_INFO = lv.label(MAIN_cont_3)
MAIN_POUT_INFO.set_text("00.00")
MAIN_POUT_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_POUT_INFO.set_pos(75, 65)
MAIN_POUT_INFO.set_size(70, 30)
MAIN_POUT_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_POUT_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_POUT_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_POUT_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_15
MAIN_label_15 = lv.label(MAIN_cont_3)
MAIN_label_15.set_text("W")
MAIN_label_15.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_15.set_pos(150, 65)
MAIN_label_15.set_size(30, 30)
MAIN_label_15.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_15, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_15.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_15.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_cont_4
MAIN_cont_4 = lv.obj(MAIN)
MAIN_cont_4.set_pos(205, 150)
MAIN_cont_4.set_size(270, 102)
MAIN_cont_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_cont_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_cont_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_4.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_4.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_ISET_SPINBOX
MAIN_ISET_SPINBOX = lv.spinbox(MAIN_cont_4)
MAIN_ISET_SPINBOX.set_width(70)
MAIN_ISET_SPINBOX.set_height(40)
MAIN_ISET_SPINBOX.set_digit_format(4, 2)
MAIN_ISET_SPINBOX.step_prev()
MAIN_ISET_SPINBOX.set_range(-9999, 9999)
MAIN_ISET_SPINBOX_height = MAIN_ISET_SPINBOX.get_height()
MAIN_ISET_SPINBOX_btn = lv.btn(MAIN_cont_4)
MAIN_ISET_SPINBOX_btn.set_size(MAIN_ISET_SPINBOX_height, MAIN_ISET_SPINBOX_height)
MAIN_ISET_SPINBOX_btn.set_style_bg_img_src(lv.SYMBOL.PLUS, 0)
MAIN_ISET_SPINBOX_btn.add_event_cb(lambda e: spinbox_increment_event_cb(e, MAIN_ISET_SPINBOX), lv.EVENT.ALL, None)
MAIN_ISET_SPINBOX_btn_minus = lv.btn(MAIN_cont_4)
MAIN_ISET_SPINBOX_btn_minus.set_size(MAIN_ISET_SPINBOX_height, MAIN_ISET_SPINBOX_height)
MAIN_ISET_SPINBOX_btn_minus.set_style_bg_img_src(lv.SYMBOL.MINUS, 0)
MAIN_ISET_SPINBOX_btn_minus.add_event_cb(lambda e: spinbox_decrement_event_cb(e, MAIN_ISET_SPINBOX), lv.EVENT.ALL, None)
MAIN_ISET_SPINBOX.set_pos(137, 56)
MAIN_ISET_SPINBOX_btn.align_to(MAIN_ISET_SPINBOX, lv.ALIGN.OUT_RIGHT_MID, 5, 0)
MAIN_ISET_SPINBOX_btn_minus.align_to(MAIN_ISET_SPINBOX, lv.ALIGN.OUT_LEFT_MID, -5, 0)
MAIN_ISET_SPINBOX.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_ISET_SPINBOX, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_ISET_SPINBOX.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MAIN_ISET_SPINBOX, Part: lv.PART.CURSOR, State: lv.STATE.DEFAULT.
MAIN_ISET_SPINBOX.set_style_text_color(lv.color_hex(0xffffff), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_text_font(test_font("montserratMedium", 12), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_bg_opa(255, lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.CURSOR|lv.STATE.DEFAULT)
# Set style for MAIN_ISET_SPINBOX, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MAIN_ISET_SPINBOX_extra_btns_main_default = lv.style_t()
style_MAIN_ISET_SPINBOX_extra_btns_main_default.init()
style_MAIN_ISET_SPINBOX_extra_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_MAIN_ISET_SPINBOX_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_MAIN_ISET_SPINBOX_extra_btns_main_default.set_bg_opa(255)
style_MAIN_ISET_SPINBOX_extra_btns_main_default.set_bg_color(lv.color_hex(0x2195f6))
style_MAIN_ISET_SPINBOX_extra_btns_main_default.set_border_width(0)
style_MAIN_ISET_SPINBOX_extra_btns_main_default.set_radius(5)
MAIN_ISET_SPINBOX_btn.add_style(style_MAIN_ISET_SPINBOX_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_ISET_SPINBOX_btn_minus.add_style(style_MAIN_ISET_SPINBOX_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_VSET_SPINBOX
MAIN_VSET_SPINBOX = lv.spinbox(MAIN_cont_4)
MAIN_VSET_SPINBOX.set_width(70)
MAIN_VSET_SPINBOX.set_height(40)
MAIN_VSET_SPINBOX.set_digit_format(4, 2)
MAIN_VSET_SPINBOX.step_prev()
MAIN_VSET_SPINBOX.set_range(-9999, 9999)
MAIN_VSET_SPINBOX_height = MAIN_VSET_SPINBOX.get_height()
MAIN_VSET_SPINBOX_btn = lv.btn(MAIN_cont_4)
MAIN_VSET_SPINBOX_btn.set_size(MAIN_VSET_SPINBOX_height, MAIN_VSET_SPINBOX_height)
MAIN_VSET_SPINBOX_btn.set_style_bg_img_src(lv.SYMBOL.PLUS, 0)
MAIN_VSET_SPINBOX_btn.add_event_cb(lambda e: spinbox_increment_event_cb(e, MAIN_VSET_SPINBOX), lv.EVENT.ALL, None)
MAIN_VSET_SPINBOX_btn_minus = lv.btn(MAIN_cont_4)
MAIN_VSET_SPINBOX_btn_minus.set_size(MAIN_VSET_SPINBOX_height, MAIN_VSET_SPINBOX_height)
MAIN_VSET_SPINBOX_btn_minus.set_style_bg_img_src(lv.SYMBOL.MINUS, 0)
MAIN_VSET_SPINBOX_btn_minus.add_event_cb(lambda e: spinbox_decrement_event_cb(e, MAIN_VSET_SPINBOX), lv.EVENT.ALL, None)
MAIN_VSET_SPINBOX.set_pos(137, 8)
MAIN_VSET_SPINBOX_btn.align_to(MAIN_VSET_SPINBOX, lv.ALIGN.OUT_RIGHT_MID, 5, 0)
MAIN_VSET_SPINBOX_btn_minus.align_to(MAIN_VSET_SPINBOX, lv.ALIGN.OUT_LEFT_MID, -5, 0)
MAIN_VSET_SPINBOX.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_VSET_SPINBOX, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_VSET_SPINBOX.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MAIN_VSET_SPINBOX, Part: lv.PART.CURSOR, State: lv.STATE.DEFAULT.
MAIN_VSET_SPINBOX.set_style_text_color(lv.color_hex(0xffffff), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_text_font(test_font("montserratMedium", 12), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_bg_opa(255, lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.CURSOR|lv.STATE.DEFAULT)
# Set style for MAIN_VSET_SPINBOX, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MAIN_VSET_SPINBOX_extra_btns_main_default = lv.style_t()
style_MAIN_VSET_SPINBOX_extra_btns_main_default.init()
style_MAIN_VSET_SPINBOX_extra_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_MAIN_VSET_SPINBOX_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_MAIN_VSET_SPINBOX_extra_btns_main_default.set_bg_opa(255)
style_MAIN_VSET_SPINBOX_extra_btns_main_default.set_bg_color(lv.color_hex(0x2195f6))
style_MAIN_VSET_SPINBOX_extra_btns_main_default.set_border_width(0)
style_MAIN_VSET_SPINBOX_extra_btns_main_default.set_radius(5)
MAIN_VSET_SPINBOX_btn.add_style(style_MAIN_VSET_SPINBOX_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_VSET_SPINBOX_btn_minus.add_style(style_MAIN_VSET_SPINBOX_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_24
MAIN_label_24 = lv.label(MAIN_cont_4)
MAIN_label_24.set_text("VSET:")
MAIN_label_24.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_24.set_pos(9, 11)
MAIN_label_24.set_size(70, 30)
MAIN_label_24.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_24, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_24.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_24.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_25
MAIN_label_25 = lv.label(MAIN_cont_4)
MAIN_label_25.set_text("ISET:")
MAIN_label_25.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_25.set_pos(9, 58)
MAIN_label_25.set_size(70, 30)
MAIN_label_25.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_25, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_25.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_text_font(test_font("blender_pro_bold", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_25.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_cont_5
MAIN_cont_5 = lv.obj(MAIN)
MAIN_cont_5.set_pos(5, 292)
MAIN_cont_5.set_size(470, 25)
MAIN_cont_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_cont_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_cont_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_5.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_5.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_label_28
MAIN_label_28 = lv.label(MAIN_cont_5)
MAIN_label_28.set_text("TEMP:")
MAIN_label_28.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_28.set_pos(7, 5)
MAIN_label_28.set_size(50, 20)
MAIN_label_28.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_28, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_28.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_28.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_26
MAIN_label_26 = lv.label(MAIN_cont_5)
MAIN_label_26.set_text("FAN:")
MAIN_label_26.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_26.set_pos(272, 5)
MAIN_label_26.set_size(40, 20)
MAIN_label_26.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_26, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_26.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_26.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_TEMP_INFO
MAIN_TEMP_INFO = lv.label(MAIN_cont_5)
MAIN_TEMP_INFO.set_text("00.00C")
MAIN_TEMP_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_TEMP_INFO.set_pos(64, 5)
MAIN_TEMP_INFO.set_size(60, 20)
MAIN_TEMP_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_TEMP_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_TEMP_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TEMP_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_30
MAIN_label_30 = lv.label(MAIN_cont_5)
MAIN_label_30.set_text("N:")
MAIN_label_30.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_30.set_pos(163, 5)
MAIN_label_30.set_size(20, 20)
MAIN_label_30.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_30, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_30.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_30.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_EFFECT_INFO
MAIN_EFFECT_INFO = lv.label(MAIN_cont_5)
MAIN_EFFECT_INFO.set_text("90%")
MAIN_EFFECT_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_EFFECT_INFO.set_pos(180, 5)
MAIN_EFFECT_INFO.set_size(40, 20)
MAIN_EFFECT_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_EFFECT_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_EFFECT_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_EFFECT_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_FAN_INFO
MAIN_FAN_INFO = lv.label(MAIN_cont_5)
MAIN_FAN_INFO.set_text("OFF")
MAIN_FAN_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_FAN_INFO.set_pos(312, 5)
MAIN_FAN_INFO.set_size(35, 20)
MAIN_FAN_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_FAN_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_FAN_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_40
MAIN_label_40 = lv.label(MAIN_cont_5)
MAIN_label_40.set_text("BLE:")
MAIN_label_40.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_40.set_pos(366, 5)
MAIN_label_40.set_size(40, 20)
MAIN_label_40.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_40, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_40.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_40.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_BLE_INFO
MAIN_BLE_INFO = lv.label(MAIN_cont_5)
MAIN_BLE_INFO.set_text("OFF")
MAIN_BLE_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_BLE_INFO.set_pos(409, 5)
MAIN_BLE_INFO.set_size(35, 20)
MAIN_BLE_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_BLE_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_BLE_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_BLE_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_START_BTU
MAIN_START_BTU = lv.btn(MAIN)
MAIN_START_BTU_label = lv.label(MAIN_START_BTU)
MAIN_START_BTU_label.set_text("RUN")
MAIN_START_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_START_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_START_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_START_BTU.set_pos(205, 42)
MAIN_START_BTU.set_size(60, 30)
MAIN_START_BTU.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_START_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_START_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_START_BTU.set_style_bg_color(lv.color_hex(0x00cb0b), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_START_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_START_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_START_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_START_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_START_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_START_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MAIN_START_BTU, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
MAIN_START_BTU.set_style_bg_opa(254, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_START_BTU.set_style_bg_color(lv.color_hex(0xce001f), lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_START_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_START_BTU.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_START_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_START_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_START_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.PRESSED)

# Create MAIN_OVP_BTU
MAIN_OVP_BTU = lv.btn(MAIN)
MAIN_OVP_BTU_label = lv.label(MAIN_OVP_BTU)
MAIN_OVP_BTU_label.set_text("OVP:24.00V")
MAIN_OVP_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_OVP_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_OVP_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_OVP_BTU.set_pos(205, 78)
MAIN_OVP_BTU.set_size(125, 30)
MAIN_OVP_BTU.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_OVP_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_OVP_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OVP_BTU.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OVP_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OVP_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OVP_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OVP_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OVP_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OVP_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_OCP_BTU
MAIN_OCP_BTU = lv.btn(MAIN)
MAIN_OCP_BTU_label = lv.label(MAIN_OCP_BTU)
MAIN_OCP_BTU_label.set_text("OCP:05.00A")
MAIN_OCP_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_OCP_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_OCP_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_OCP_BTU.set_pos(205, 113)
MAIN_OCP_BTU.set_size(125, 30)
MAIN_OCP_BTU.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_OCP_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_OCP_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OCP_BTU.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OCP_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OCP_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OCP_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OCP_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OCP_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_OCP_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_cont_6
MAIN_cont_6 = lv.obj(MAIN)
MAIN_cont_6.set_pos(340, 42)
MAIN_cont_6.set_size(135, 63)
MAIN_cont_6.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_cont_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_cont_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_6.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_6.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_AH_INFO
MAIN_AH_INFO = lv.label(MAIN_cont_6)
MAIN_AH_INFO.set_text("0000.000")
MAIN_AH_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_AH_INFO.set_pos(7, 3)
MAIN_AH_INFO.set_size(80, 20)
MAIN_AH_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_AH_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_AH_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_AH_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_35
MAIN_label_35 = lv.label(MAIN_cont_6)
MAIN_label_35.set_text("AH")
MAIN_label_35.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_35.set_pos(90, 3)
MAIN_label_35.set_size(36, 20)
MAIN_label_35.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_35, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_35.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_35.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_36
MAIN_label_36 = lv.label(MAIN_cont_6)
MAIN_label_36.set_text("WH")
MAIN_label_36.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_36.set_pos(90, 23)
MAIN_label_36.set_size(36, 20)
MAIN_label_36.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_36, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_36.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_36.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_WH_INFO
MAIN_WH_INFO = lv.label(MAIN_cont_6)
MAIN_WH_INFO.set_text("0000.000")
MAIN_WH_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_WH_INFO.set_pos(7, 23)
MAIN_WH_INFO.set_size(80, 20)
MAIN_WH_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_WH_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_WH_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_WH_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_TIME_INFO
MAIN_TIME_INFO = lv.label(MAIN_cont_6)
MAIN_TIME_INFO.set_text("00000.00")
MAIN_TIME_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_TIME_INFO.set_pos(7, 43)
MAIN_TIME_INFO.set_size(80, 20)
MAIN_TIME_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_TIME_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_TIME_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_TIME_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_label_39
MAIN_label_39 = lv.label(MAIN_cont_6)
MAIN_label_39.set_text("TM")
MAIN_label_39.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_39.set_pos(90, 43)
MAIN_label_39.set_size(36, 20)
MAIN_label_39.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_39, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_39.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_39.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_LLIMMODE_LIST
MAIN_LLIMMODE_LIST = lv.dropdown(MAIN)
MAIN_LLIMMODE_LIST.set_options("CCM\nDCM")
MAIN_LLIMMODE_LIST.set_pos(415, 113)
MAIN_LLIMMODE_LIST.set_size(60, 30)
MAIN_LLIMMODE_LIST.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_LLIMMODE_LIST, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_LLIMMODE_LIST.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_pad_left(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_pad_right(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_LLIMMODE_LIST.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MAIN_LLIMMODE_LIST, Part: lv.PART.SELECTED, State: lv.STATE.CHECKED.
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked = lv.style_t()
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.init()
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.set_text_color(lv.color_hex(0xffffff))
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.set_text_font(test_font("montserratMedium", 12))
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.set_border_width(1)
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.set_border_opa(255)
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.set_border_color(lv.color_hex(0xe1e6ee))
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.set_radius(3)
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.set_bg_opa(255)
style_MAIN_LLIMMODE_LIST_extra_list_selected_checked.set_bg_color(lv.color_hex(0x00a1b5))
MAIN_LLIMMODE_LIST.get_list().add_style(style_MAIN_LLIMMODE_LIST_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)
# Set style for MAIN_LLIMMODE_LIST, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MAIN_LLIMMODE_LIST_extra_list_main_default = lv.style_t()
style_MAIN_LLIMMODE_LIST_extra_list_main_default.init()
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_max_height(90)
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_text_color(lv.color_hex(0x0D3055))
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_text_font(test_font("montserratMedium", 12))
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_border_width(1)
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_border_opa(255)
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_border_color(lv.color_hex(0xe1e6ee))
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_radius(3)
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_bg_opa(255)
style_MAIN_LLIMMODE_LIST_extra_list_main_default.set_bg_color(lv.color_hex(0xffffff))
MAIN_LLIMMODE_LIST.get_list().add_style(style_MAIN_LLIMMODE_LIST_extra_list_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MAIN_LLIMMODE_LIST, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default = lv.style_t()
style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default.init()
style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default.set_radius(3)
style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default.set_bg_opa(255)
style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default.set_bg_color(lv.color_hex(0x00ff00))
MAIN_LLIMMODE_LIST.get_list().add_style(style_MAIN_LLIMMODE_LIST_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create MAIN_cont_7
MAIN_cont_7 = lv.obj(MAIN)
MAIN_cont_7.set_pos(5, 260)
MAIN_cont_7.set_size(180, 25)
MAIN_cont_7.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_cont_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_cont_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_7.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_7.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_7.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_cont_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_label_49
MAIN_label_49 = lv.label(MAIN_cont_7)
MAIN_label_49.set_text("STATE:")
MAIN_label_49.set_long_mode(lv.label.LONG.WRAP)
MAIN_label_49.set_pos(2, 3)
MAIN_label_49.set_size(65, 20)
MAIN_label_49.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_label_49, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_label_49.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_label_49.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_STATE_INFO
MAIN_STATE_INFO = lv.label(MAIN_cont_7)
MAIN_STATE_INFO.set_text("NORMAL")
MAIN_STATE_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_STATE_INFO.set_pos(85, 4)
MAIN_STATE_INFO.set_size(75, 20)
MAIN_STATE_INFO.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_STATE_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_STATE_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_STATE_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_SET_BTU
MAIN_SET_BTU = lv.btn(MAIN)
MAIN_SET_BTU_label = lv.label(MAIN_SET_BTU)
MAIN_SET_BTU_label.set_text("SET")
MAIN_SET_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_SET_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_SET_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_SET_BTU.set_pos(415, 257)
MAIN_SET_BTU.set_size(60, 30)
MAIN_SET_BTU.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_SET_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_SET_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_SET_BTU.set_style_bg_color(lv.color_hex(0x303030), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_SET_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_SET_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_SET_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_SET_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_SET_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_SET_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_MEUN_BTU
MAIN_MEUN_BTU = lv.btn(MAIN)
MAIN_MEUN_BTU_label = lv.label(MAIN_MEUN_BTU)
MAIN_MEUN_BTU_label.set_text("MENU")
MAIN_MEUN_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_MEUN_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_MEUN_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_MEUN_BTU.set_pos(348, 257)
MAIN_MEUN_BTU.set_size(60, 30)
MAIN_MEUN_BTU.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_MEUN_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_MEUN_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_MEUN_BTU.set_style_bg_color(lv.color_hex(0x303030), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_MEUN_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_MEUN_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_MEUN_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_MEUN_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_MEUN_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_MEUN_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_FAN_BTU
MAIN_FAN_BTU = lv.btn(MAIN)
MAIN_FAN_BTU_label = lv.label(MAIN_FAN_BTU)
MAIN_FAN_BTU_label.set_text("AUTO")
MAIN_FAN_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_FAN_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_FAN_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_FAN_BTU.set_pos(270, 257)
MAIN_FAN_BTU.set_size(60, 30)
MAIN_FAN_BTU.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_FAN_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_FAN_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_BTU.set_style_bg_color(lv.color_hex(0x00cc38), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_FAN_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MAIN_FAN_BTU, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
MAIN_FAN_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_FAN_BTU.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_FAN_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_FAN_BTU.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_FAN_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_FAN_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_FAN_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.PRESSED)

# Create MAIN_btn_7
MAIN_btn_7 = lv.btn(MAIN)
MAIN_btn_7_label = lv.label(MAIN_btn_7)
MAIN_btn_7_label.set_text("MENU")
MAIN_btn_7_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_btn_7_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_btn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_btn_7.set_pos(205, 257)
MAIN_btn_7.set_size(60, 30)
MAIN_btn_7.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_btn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_btn_7.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_btn_7.set_style_bg_color(lv.color_hex(0x303030), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_btn_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_btn_7.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_btn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_btn_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_btn_7.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_btn_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_COMP_BTU
MAIN_COMP_BTU = lv.btn(MAIN)
MAIN_COMP_BTU_label = lv.label(MAIN_COMP_BTU)
MAIN_COMP_BTU_label.set_text("COMP")
MAIN_COMP_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_COMP_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_COMP_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_COMP_BTU.set_pos(270, 42)
MAIN_COMP_BTU.set_size(60, 30)
MAIN_COMP_BTU.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_COMP_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_COMP_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_COMP_BTU.set_style_bg_color(lv.color_hex(0xb4b4b4), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_COMP_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_COMP_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_COMP_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_COMP_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_COMP_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_COMP_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MAIN_COMP_BTU, Part: lv.PART.MAIN, State: lv.STATE.PRESSED.
MAIN_COMP_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_COMP_BTU.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_COMP_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_COMP_BTU.set_style_radius(5, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_COMP_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_COMP_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.PRESSED)
MAIN_COMP_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.PRESSED)

MAIN.update_layout()

def START_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        #Update pos for widget START_start_kangtao
        START_start_kangtao.update_layout()
        #Write animation: START_start_kangtao move in x direction
        START_start_kangtao_x = lv.anim_t()
        START_start_kangtao_x.init()
        START_start_kangtao_x.set_var(START_start_kangtao)
        START_start_kangtao_x.set_time(1000)
        START_start_kangtao_x.set_delay(200)
        START_start_kangtao_x.set_custom_exec_cb(lambda e,val: anim_x_cb(START_start_kangtao,val))
        START_start_kangtao_x.set_values(START_start_kangtao.get_x(), 0)
        START_start_kangtao_x.set_path_cb(lv.anim_t.path_ease_in)
        START_start_kangtao_x.set_repeat_count(1)
        START_start_kangtao_x.start()
        #Write animation: START_start_kangtao move in y direction
        START_start_kangtao_y = lv.anim_t()
        START_start_kangtao_y.set_var(START_start_kangtao)
        START_start_kangtao_y.set_time(1000)
        START_start_kangtao_y.set_delay(200)
        START_start_kangtao_y.set_custom_exec_cb(lambda e,val: anim_y_cb(START_start_kangtao,val))
        START_start_kangtao_y.set_values(START_start_kangtao.get_y(), 0)
        START_start_kangtao_y.set_path_cb(lv.anim_t.path_ease_in)
        START_start_kangtao_y.set_repeat_count(1)
        START_start_kangtao_y.start()

START.add_event_cb(lambda e: START_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(START)

while SDL.check():
    time.sleep_ms(5)

