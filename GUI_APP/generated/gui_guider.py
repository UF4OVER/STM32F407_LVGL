# Copyright 2025 NXP
# NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
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
buf1_1 = bytearray(480*320*4)
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
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
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

# Create START_PAGE
START_PAGE = lv.obj()
START_PAGE.set_size(480, 320)
START_PAGE.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for START_PAGE, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
START_PAGE.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
START_PAGE.set_style_bg_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
START_PAGE.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create START_PAGE_img_1
START_PAGE_img_1 = lv.img(START_PAGE)
START_PAGE_img_1.set_src("B:MicroPython/_Kang_Tao_Logo_02_CP2077_alpha_460x100.bin")
START_PAGE_img_1.add_flag(lv.obj.FLAG.CLICKABLE)
START_PAGE_img_1.set_pivot(50,50)
START_PAGE_img_1.set_angle(0)
START_PAGE_img_1.set_pos(10, 110)
START_PAGE_img_1.set_size(460, 100)
# Set style for START_PAGE_img_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
START_PAGE_img_1.set_style_img_recolor_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
START_PAGE_img_1.set_style_img_recolor(lv.color_hex(0xf79508), lv.PART.MAIN|lv.STATE.DEFAULT)
START_PAGE_img_1.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
START_PAGE_img_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
START_PAGE_img_1.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

START_PAGE.update_layout()
# Create MAIN_PAGE
MAIN_PAGE = lv.obj()
MAIN_PAGE.set_size(480, 320)
MAIN_PAGE.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PAGE, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE.set_style_bg_opa(252, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE.set_style_bg_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_cont_1
MAIN_PAGE_cont_1 = lv.obj(MAIN_PAGE)
MAIN_PAGE_cont_1.set_pos(10, 6)
MAIN_PAGE_cont_1.set_size(460, 25)
MAIN_PAGE_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PAGE_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_cont_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_PAGE_NAME_INFO
MAIN_PAGE_NAME_INFO = lv.label(MAIN_PAGE_cont_1)
MAIN_PAGE_NAME_INFO.set_text("UF4 POWER")
MAIN_PAGE_NAME_INFO.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_NAME_INFO.set_width(lv.pct(100))
MAIN_PAGE_NAME_INFO.set_pos(3, 3)
MAIN_PAGE_NAME_INFO.set_size(89, 20)
# Set style for MAIN_PAGE_NAME_INFO, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_NAME_INFO.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_NAME_INFO.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_HW_LABEL
MAIN_PAGE_HW_LABEL = lv.label(MAIN_PAGE_cont_1)
MAIN_PAGE_HW_LABEL.set_text("1.00.001")
MAIN_PAGE_HW_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_HW_LABEL.set_width(lv.pct(100))
MAIN_PAGE_HW_LABEL.set_pos(387, 3)
MAIN_PAGE_HW_LABEL.set_size(70, 20)
# Set style for MAIN_PAGE_HW_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_HW_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_HW_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_cont_3
MAIN_PAGE_cont_3 = lv.obj(MAIN_PAGE)
MAIN_PAGE_cont_3.set_pos(10, 38)
MAIN_PAGE_cont_3.set_size(100, 60)
MAIN_PAGE_cont_3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PAGE_cont_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_cont_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_PAGE_AH_LABEL
MAIN_PAGE_AH_LABEL = lv.label(MAIN_PAGE_cont_3)
MAIN_PAGE_AH_LABEL.set_text("0000.00")
MAIN_PAGE_AH_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_AH_LABEL.set_width(lv.pct(100))
MAIN_PAGE_AH_LABEL.set_pos(2, 2)
MAIN_PAGE_AH_LABEL.set_size(70, 20)
# Set style for MAIN_PAGE_AH_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_AH_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_AH_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_WH_LABEL
MAIN_PAGE_WH_LABEL = lv.label(MAIN_PAGE_cont_3)
MAIN_PAGE_WH_LABEL.set_text("0000.00")
MAIN_PAGE_WH_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_WH_LABEL.set_width(lv.pct(100))
MAIN_PAGE_WH_LABEL.set_pos(2, 20)
MAIN_PAGE_WH_LABEL.set_size(70, 20)
# Set style for MAIN_PAGE_WH_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_WH_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_WH_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_TM_LABEL
MAIN_PAGE_TM_LABEL = lv.label(MAIN_PAGE_cont_3)
MAIN_PAGE_TM_LABEL.set_text("0000.00")
MAIN_PAGE_TM_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_TM_LABEL.set_width(lv.pct(100))
MAIN_PAGE_TM_LABEL.set_pos(2, 38)
MAIN_PAGE_TM_LABEL.set_size(70, 20)
# Set style for MAIN_PAGE_TM_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_TM_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TM_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_22
MAIN_PAGE_label_22 = lv.label(MAIN_PAGE_cont_3)
MAIN_PAGE_label_22.set_text("AH")
MAIN_PAGE_label_22.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_22.set_width(lv.pct(100))
MAIN_PAGE_label_22.set_pos(71, 2)
MAIN_PAGE_label_22.set_size(25, 20)
# Set style for MAIN_PAGE_label_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_22.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_22.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_23
MAIN_PAGE_label_23 = lv.label(MAIN_PAGE_cont_3)
MAIN_PAGE_label_23.set_text("WH")
MAIN_PAGE_label_23.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_23.set_width(lv.pct(100))
MAIN_PAGE_label_23.set_pos(71, 20)
MAIN_PAGE_label_23.set_size(25, 20)
# Set style for MAIN_PAGE_label_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_23.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_23.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_24
MAIN_PAGE_label_24 = lv.label(MAIN_PAGE_cont_3)
MAIN_PAGE_label_24.set_text("TM")
MAIN_PAGE_label_24.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_24.set_width(lv.pct(100))
MAIN_PAGE_label_24.set_pos(70, 38)
MAIN_PAGE_label_24.set_size(25, 20)
# Set style for MAIN_PAGE_label_24, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_24.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_24.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_cont_5
MAIN_PAGE_cont_5 = lv.obj(MAIN_PAGE)
MAIN_PAGE_cont_5.set_pos(187, 290)
MAIN_PAGE_cont_5.set_size(283, 20)
MAIN_PAGE_cont_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PAGE_cont_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_cont_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_CHART_BTU
MAIN_PAGE_CHART_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_CHART_BTU_label = lv.label(MAIN_PAGE_CHART_BTU)
MAIN_PAGE_CHART_BTU_label.set_text("CHART")
MAIN_PAGE_CHART_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_CHART_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_CHART_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_CHART_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_pos(292, 109)
MAIN_PAGE_CHART_BTU.set_size(70, 30)
# Set style for MAIN_PAGE_CHART_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_CHART_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_bg_color(lv.color_hex(0x66b73b), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_CHART_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_FAN_BTU
MAIN_PAGE_FAN_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_FAN_BTU.add_flag(lv.obj.FLAG.CHECKABLE)
MAIN_PAGE_FAN_BTU_label = lv.label(MAIN_PAGE_FAN_BTU)
MAIN_PAGE_FAN_BTU_label.set_text("FAN")
MAIN_PAGE_FAN_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_FAN_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_FAN_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_FAN_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_pos(187, 253)
MAIN_PAGE_FAN_BTU.set_size(67, 30)
# Set style for MAIN_PAGE_FAN_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_FAN_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_bg_color(lv.color_hex(0x3bb790), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_MEUN_BTU
MAIN_PAGE_MEUN_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_MEUN_BTU_label = lv.label(MAIN_PAGE_MEUN_BTU)
MAIN_PAGE_MEUN_BTU_label.set_text("MEUN")
MAIN_PAGE_MEUN_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_MEUN_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_MEUN_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_MEUN_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_pos(258, 253)
MAIN_PAGE_MEUN_BTU.set_size(67, 30)
# Set style for MAIN_PAGE_MEUN_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_MEUN_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_bg_color(lv.color_hex(0x3b78b7), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MEUN_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_SET_BTU
MAIN_PAGE_SET_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_SET_BTU_label = lv.label(MAIN_PAGE_SET_BTU)
MAIN_PAGE_SET_BTU_label.set_text("SET")
MAIN_PAGE_SET_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_SET_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_SET_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_SET_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_pos(292, 72)
MAIN_PAGE_SET_BTU.set_size(70, 30)
# Set style for MAIN_PAGE_SET_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_SET_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_bg_color(lv.color_hex(0xb73b4e), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_SET_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_IMODE_LIST
MAIN_PAGE_IMODE_LIST = lv.dropdown(MAIN_PAGE)
MAIN_PAGE_IMODE_LIST.set_options("CC\nCV")
MAIN_PAGE_IMODE_LIST.set_pos(350, 38)
MAIN_PAGE_IMODE_LIST.set_size(55, 30)
# Set style for MAIN_PAGE_IMODE_LIST, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_IMODE_LIST.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_pad_top(6, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IMODE_LIST.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MAIN_PAGE_IMODE_LIST, Part: lv.PART.SELECTED, State: lv.STATE.CHECKED.
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked = lv.style_t()
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.init()
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.set_border_width(1)
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.set_border_opa(255)
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.set_border_color(lv.color_hex(0xe1e6ee))
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.set_border_side(lv.BORDER_SIDE.FULL)
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.set_radius(3)
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.set_bg_opa(255)
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.set_bg_color(lv.color_hex(0x00a1b5))
style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
MAIN_PAGE_IMODE_LIST.get_list().add_style(style_MAIN_PAGE_IMODE_LIST_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)
# Set style for MAIN_PAGE_IMODE_LIST, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default = lv.style_t()
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.init()
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_max_height(90)
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_text_color(lv.color_hex(0x0D3055))
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_text_font(test_font("montserratMedium", 12))
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_text_opa(255)
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_border_width(1)
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_border_opa(255)
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_border_color(lv.color_hex(0xe1e6ee))
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_border_side(lv.BORDER_SIDE.FULL)
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_radius(3)
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_bg_opa(255)
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_bg_color(lv.color_hex(0xffffff))
style_MAIN_PAGE_IMODE_LIST_extra_list_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
MAIN_PAGE_IMODE_LIST.get_list().add_style(style_MAIN_PAGE_IMODE_LIST_extra_list_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MAIN_PAGE_IMODE_LIST, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default = lv.style_t()
style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default.init()
style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default.set_radius(3)
style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default.set_bg_opa(255)
style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default.set_bg_color(lv.color_hex(0x00ff00))
style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
MAIN_PAGE_IMODE_LIST.get_list().add_style(style_MAIN_PAGE_IMODE_LIST_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create MAIN_PAGE_MMODE_LIST
MAIN_PAGE_MMODE_LIST = lv.dropdown(MAIN_PAGE)
MAIN_PAGE_MMODE_LIST.set_options("DCM\nCCM")
MAIN_PAGE_MMODE_LIST.set_pos(410, 38)
MAIN_PAGE_MMODE_LIST.set_size(60, 30)
# Set style for MAIN_PAGE_MMODE_LIST, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_MMODE_LIST.set_style_text_color(lv.color_hex(0x0D3055), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_pad_top(6, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_pad_left(6, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_pad_right(6, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_MMODE_LIST.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for MAIN_PAGE_MMODE_LIST, Part: lv.PART.SELECTED, State: lv.STATE.CHECKED.
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked = lv.style_t()
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.init()
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.set_border_width(1)
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.set_border_opa(255)
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.set_border_color(lv.color_hex(0xe1e6ee))
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.set_border_side(lv.BORDER_SIDE.FULL)
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.set_radius(3)
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.set_bg_opa(255)
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.set_bg_color(lv.color_hex(0x00a1b5))
style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
MAIN_PAGE_MMODE_LIST.get_list().add_style(style_MAIN_PAGE_MMODE_LIST_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)
# Set style for MAIN_PAGE_MMODE_LIST, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default = lv.style_t()
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.init()
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_max_height(90)
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_text_color(lv.color_hex(0x0D3055))
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_text_font(test_font("montserratMedium", 12))
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_text_opa(255)
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_border_width(1)
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_border_opa(255)
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_border_color(lv.color_hex(0xe1e6ee))
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_border_side(lv.BORDER_SIDE.FULL)
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_radius(3)
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_bg_opa(255)
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_bg_color(lv.color_hex(0xffffff))
style_MAIN_PAGE_MMODE_LIST_extra_list_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
MAIN_PAGE_MMODE_LIST.get_list().add_style(style_MAIN_PAGE_MMODE_LIST_extra_list_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MAIN_PAGE_MMODE_LIST, Part: lv.PART.SCROLLBAR, State: lv.STATE.DEFAULT.
style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default = lv.style_t()
style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default.init()
style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default.set_radius(3)
style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default.set_bg_opa(255)
style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default.set_bg_color(lv.color_hex(0x00ff00))
style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
MAIN_PAGE_MMODE_LIST.get_list().add_style(style_MAIN_PAGE_MMODE_LIST_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# Create MAIN_PAGE_START_BTU
MAIN_PAGE_START_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_START_BTU.add_flag(lv.obj.FLAG.CHECKABLE)
MAIN_PAGE_START_BTU_label = lv.label(MAIN_PAGE_START_BTU)
MAIN_PAGE_START_BTU_label.set_text("START\n")
MAIN_PAGE_START_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_START_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_START_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_START_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_pos(187, 38)
MAIN_PAGE_START_BTU.set_size(75, 30)
# Set style for MAIN_PAGE_START_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_START_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_bg_color(lv.color_hex(0x66b73b), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_START_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_COMP_BTU
MAIN_PAGE_COMP_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_COMP_BTU.add_flag(lv.obj.FLAG.CHECKABLE)
MAIN_PAGE_COMP_BTU_label = lv.label(MAIN_PAGE_COMP_BTU)
MAIN_PAGE_COMP_BTU_label.set_text("COMP")
MAIN_PAGE_COMP_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_COMP_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_COMP_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_COMP_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_pos(270, 38)
MAIN_PAGE_COMP_BTU.set_size(75, 30)
# Set style for MAIN_PAGE_COMP_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_COMP_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_bg_color(lv.color_hex(0x66b73b), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_COMP_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_cont_4
MAIN_PAGE_cont_4 = lv.obj(MAIN_PAGE)
MAIN_PAGE_cont_4.set_pos(10, 103)
MAIN_PAGE_cont_4.set_size(170, 100)
MAIN_PAGE_cont_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PAGE_cont_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_cont_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_PAGE_label_2
MAIN_PAGE_label_2 = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_label_2.set_text("IBUS:")
MAIN_PAGE_label_2.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_2.set_width(lv.pct(100))
MAIN_PAGE_label_2.set_pos(5, 38)
MAIN_PAGE_label_2.set_size(60, 25)
# Set style for MAIN_PAGE_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_VBUS_LABEL
MAIN_PAGE_VBUS_LABEL = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_VBUS_LABEL.set_text("00.00")
MAIN_PAGE_VBUS_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_VBUS_LABEL.set_width(lv.pct(100))
MAIN_PAGE_VBUS_LABEL.set_pos(70, 5)
MAIN_PAGE_VBUS_LABEL.set_size(60, 25)
# Set style for MAIN_PAGE_VBUS_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_VBUS_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VBUS_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_3
MAIN_PAGE_label_3 = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_label_3.set_text("PBUS:")
MAIN_PAGE_label_3.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_3.set_width(lv.pct(100))
MAIN_PAGE_label_3.set_pos(5, 70)
MAIN_PAGE_label_3.set_size(60, 25)
# Set style for MAIN_PAGE_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_7
MAIN_PAGE_label_7 = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_label_7.set_text("V\n")
MAIN_PAGE_label_7.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_7.set_width(lv.pct(100))
MAIN_PAGE_label_7.set_pos(130, 5)
MAIN_PAGE_label_7.set_size(30, 25)
# Set style for MAIN_PAGE_label_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_PBUS_LABEL
MAIN_PAGE_PBUS_LABEL = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_PBUS_LABEL.set_text("00.00")
MAIN_PAGE_PBUS_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_PBUS_LABEL.set_width(lv.pct(100))
MAIN_PAGE_PBUS_LABEL.set_pos(70, 70)
MAIN_PAGE_PBUS_LABEL.set_size(60, 25)
# Set style for MAIN_PAGE_PBUS_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_PBUS_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_PBUS_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_8
MAIN_PAGE_label_8 = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_label_8.set_text("A")
MAIN_PAGE_label_8.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_8.set_width(lv.pct(100))
MAIN_PAGE_label_8.set_pos(130, 38)
MAIN_PAGE_label_8.set_size(30, 25)
# Set style for MAIN_PAGE_label_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_IBUS_LABEL
MAIN_PAGE_IBUS_LABEL = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_IBUS_LABEL.set_text("00.00\n")
MAIN_PAGE_IBUS_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_IBUS_LABEL.set_width(lv.pct(100))
MAIN_PAGE_IBUS_LABEL.set_pos(70, 37)
MAIN_PAGE_IBUS_LABEL.set_size(60, 25)
# Set style for MAIN_PAGE_IBUS_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_IBUS_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IBUS_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_9
MAIN_PAGE_label_9 = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_label_9.set_text("W\n")
MAIN_PAGE_label_9.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_9.set_width(lv.pct(100))
MAIN_PAGE_label_9.set_pos(130, 70)
MAIN_PAGE_label_9.set_size(30, 25)
# Set style for MAIN_PAGE_label_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_1
MAIN_PAGE_label_1 = lv.label(MAIN_PAGE_cont_4)
MAIN_PAGE_label_1.set_text("VBUS:")
MAIN_PAGE_label_1.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_1.set_width(lv.pct(100))
MAIN_PAGE_label_1.set_pos(5, 5)
MAIN_PAGE_label_1.set_size(60, 25)
# Set style for MAIN_PAGE_label_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_cont_6
MAIN_PAGE_cont_6 = lv.obj(MAIN_PAGE)
MAIN_PAGE_cont_6.set_pos(10, 210)
MAIN_PAGE_cont_6.set_size(170, 100)
MAIN_PAGE_cont_6.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PAGE_cont_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_cont_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_PAGE_label_33
MAIN_PAGE_label_33 = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_label_33.set_text("IOUT:")
MAIN_PAGE_label_33.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_33.set_width(lv.pct(100))
MAIN_PAGE_label_33.set_pos(5, 38)
MAIN_PAGE_label_33.set_size(60, 25)
# Set style for MAIN_PAGE_label_33, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_33.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_33.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_VOUT_LABEL
MAIN_PAGE_VOUT_LABEL = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_VOUT_LABEL.set_text("00.00")
MAIN_PAGE_VOUT_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_VOUT_LABEL.set_width(lv.pct(100))
MAIN_PAGE_VOUT_LABEL.set_pos(70, 5)
MAIN_PAGE_VOUT_LABEL.set_size(60, 25)
# Set style for MAIN_PAGE_VOUT_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_VOUT_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOUT_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_31
MAIN_PAGE_label_31 = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_label_31.set_text("POUT:")
MAIN_PAGE_label_31.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_31.set_width(lv.pct(100))
MAIN_PAGE_label_31.set_pos(5, 70)
MAIN_PAGE_label_31.set_size(60, 25)
# Set style for MAIN_PAGE_label_31, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_31.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_31.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_30
MAIN_PAGE_label_30 = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_label_30.set_text("V\n")
MAIN_PAGE_label_30.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_30.set_width(lv.pct(100))
MAIN_PAGE_label_30.set_pos(130, 5)
MAIN_PAGE_label_30.set_size(30, 25)
# Set style for MAIN_PAGE_label_30, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_30.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_30.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_POUT_LABEL
MAIN_PAGE_POUT_LABEL = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_POUT_LABEL.set_text("00.00")
MAIN_PAGE_POUT_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_POUT_LABEL.set_width(lv.pct(100))
MAIN_PAGE_POUT_LABEL.set_pos(70, 70)
MAIN_PAGE_POUT_LABEL.set_size(60, 25)
# Set style for MAIN_PAGE_POUT_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_POUT_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_POUT_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_28
MAIN_PAGE_label_28 = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_label_28.set_text("A")
MAIN_PAGE_label_28.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_28.set_width(lv.pct(100))
MAIN_PAGE_label_28.set_pos(130, 38)
MAIN_PAGE_label_28.set_size(30, 25)
# Set style for MAIN_PAGE_label_28, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_28.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_28.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_IOUT_LABEL
MAIN_PAGE_IOUT_LABEL = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_IOUT_LABEL.set_text("00.00\n")
MAIN_PAGE_IOUT_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_IOUT_LABEL.set_width(lv.pct(100))
MAIN_PAGE_IOUT_LABEL.set_pos(70, 38)
MAIN_PAGE_IOUT_LABEL.set_size(60, 25)
# Set style for MAIN_PAGE_IOUT_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_IOUT_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IOUT_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_26
MAIN_PAGE_label_26 = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_label_26.set_text("W\n")
MAIN_PAGE_label_26.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_26.set_width(lv.pct(100))
MAIN_PAGE_label_26.set_pos(130, 70)
MAIN_PAGE_label_26.set_size(30, 25)
# Set style for MAIN_PAGE_label_26, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_26.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_26.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_25
MAIN_PAGE_label_25 = lv.label(MAIN_PAGE_cont_6)
MAIN_PAGE_label_25.set_text("VOUT:")
MAIN_PAGE_label_25.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_25.set_width(lv.pct(100))
MAIN_PAGE_label_25.set_pos(5, 5)
MAIN_PAGE_label_25.set_size(60, 25)
# Set style for MAIN_PAGE_label_25, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_25.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_25.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_cont_7
MAIN_PAGE_cont_7 = lv.obj(MAIN_PAGE)
MAIN_PAGE_cont_7.set_pos(187, 145)
MAIN_PAGE_cont_7.set_size(283, 100)
MAIN_PAGE_cont_7.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PAGE_cont_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_cont_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create MAIN_PAGE_IET_SPINBOX
MAIN_PAGE_IET_SPINBOX = lv.spinbox(MAIN_PAGE_cont_7)
MAIN_PAGE_IET_SPINBOX.set_width(70)
MAIN_PAGE_IET_SPINBOX.set_height(40)
MAIN_PAGE_IET_SPINBOX.set_digit_format(5, 3)
MAIN_PAGE_IET_SPINBOX.set_range(-99999, 99999)
MAIN_PAGE_IET_SPINBOX_height = MAIN_PAGE_IET_SPINBOX.get_height()
MAIN_PAGE_IET_SPINBOX_btn_plus = lv.btn(MAIN_PAGE_cont_7)
MAIN_PAGE_IET_SPINBOX_btn_plus.set_size(MAIN_PAGE_IET_SPINBOX_height, MAIN_PAGE_IET_SPINBOX_height)
MAIN_PAGE_IET_SPINBOX_btn_plus.set_style_bg_img_src(lv.SYMBOL.PLUS, 0)
MAIN_PAGE_IET_SPINBOX_btn_plus.add_event_cb(lambda e: spinbox_increment_event_cb(e, MAIN_PAGE_IET_SPINBOX), lv.EVENT.ALL, None)
MAIN_PAGE_IET_SPINBOX_btn_minus = lv.btn(MAIN_PAGE_cont_7)
MAIN_PAGE_IET_SPINBOX_btn_minus.set_size(MAIN_PAGE_IET_SPINBOX_height, MAIN_PAGE_IET_SPINBOX_height)
MAIN_PAGE_IET_SPINBOX_btn_minus.set_style_bg_img_src(lv.SYMBOL.MINUS, 0)
MAIN_PAGE_IET_SPINBOX_btn_minus.add_event_cb(lambda e: spinbox_decrement_event_cb(e, MAIN_PAGE_IET_SPINBOX), lv.EVENT.ALL, None)
MAIN_PAGE_IET_SPINBOX.set_pos(115, 50)
MAIN_PAGE_IET_SPINBOX_btn_plus.align_to(MAIN_PAGE_IET_SPINBOX, lv.ALIGN.OUT_RIGHT_MID, 5, 0)
MAIN_PAGE_IET_SPINBOX_btn_minus.align_to(MAIN_PAGE_IET_SPINBOX, lv.ALIGN.OUT_LEFT_MID, -5, 0)
# Set style for MAIN_PAGE_IET_SPINBOX, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_IET_SPINBOX.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_border_color(lv.color_hex(0x919191), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_pad_top(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_pad_right(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_pad_bottom(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_pad_left(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MAIN_PAGE_IET_SPINBOX, Part: lv.PART.CURSOR, State: lv.STATE.DEFAULT.
MAIN_PAGE_IET_SPINBOX.set_style_text_color(lv.color_hex(0xffffff), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_text_font(test_font("montserratMedium", 12), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_text_opa(255, lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_bg_opa(255, lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.CURSOR|lv.STATE.DEFAULT)
# Set style for MAIN_PAGE_IET_SPINBOX, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default = lv.style_t()
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.init()
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_text_opa(255)
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_bg_opa(255)
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_bg_color(lv.color_hex(0x2195f6))
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_border_width(0)
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_radius(5)
style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default.set_shadow_width(0)
MAIN_PAGE_IET_SPINBOX_btn_plus.add_style(style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_IET_SPINBOX_btn_minus.add_style(style_MAIN_PAGE_IET_SPINBOX_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_VET_SPINBOX
MAIN_PAGE_VET_SPINBOX = lv.spinbox(MAIN_PAGE_cont_7)
MAIN_PAGE_VET_SPINBOX.set_width(70)
MAIN_PAGE_VET_SPINBOX.set_height(40)
MAIN_PAGE_VET_SPINBOX.set_digit_format(5, 3)
MAIN_PAGE_VET_SPINBOX.set_range(-99999, 99999)
MAIN_PAGE_VET_SPINBOX_height = MAIN_PAGE_VET_SPINBOX.get_height()
MAIN_PAGE_VET_SPINBOX_btn_plus = lv.btn(MAIN_PAGE_cont_7)
MAIN_PAGE_VET_SPINBOX_btn_plus.set_size(MAIN_PAGE_VET_SPINBOX_height, MAIN_PAGE_VET_SPINBOX_height)
MAIN_PAGE_VET_SPINBOX_btn_plus.set_style_bg_img_src(lv.SYMBOL.PLUS, 0)
MAIN_PAGE_VET_SPINBOX_btn_plus.add_event_cb(lambda e: spinbox_increment_event_cb(e, MAIN_PAGE_VET_SPINBOX), lv.EVENT.ALL, None)
MAIN_PAGE_VET_SPINBOX_btn_minus = lv.btn(MAIN_PAGE_cont_7)
MAIN_PAGE_VET_SPINBOX_btn_minus.set_size(MAIN_PAGE_VET_SPINBOX_height, MAIN_PAGE_VET_SPINBOX_height)
MAIN_PAGE_VET_SPINBOX_btn_minus.set_style_bg_img_src(lv.SYMBOL.MINUS, 0)
MAIN_PAGE_VET_SPINBOX_btn_minus.add_event_cb(lambda e: spinbox_decrement_event_cb(e, MAIN_PAGE_VET_SPINBOX), lv.EVENT.ALL, None)
MAIN_PAGE_VET_SPINBOX.set_pos(115, 5)
MAIN_PAGE_VET_SPINBOX_btn_plus.align_to(MAIN_PAGE_VET_SPINBOX, lv.ALIGN.OUT_RIGHT_MID, 5, 0)
MAIN_PAGE_VET_SPINBOX_btn_minus.align_to(MAIN_PAGE_VET_SPINBOX, lv.ALIGN.OUT_LEFT_MID, -5, 0)
# Set style for MAIN_PAGE_VET_SPINBOX, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_VET_SPINBOX.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_border_color(lv.color_hex(0x8b8b8b), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_pad_top(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_pad_right(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_pad_bottom(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_pad_left(2, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MAIN_PAGE_VET_SPINBOX, Part: lv.PART.CURSOR, State: lv.STATE.DEFAULT.
MAIN_PAGE_VET_SPINBOX.set_style_text_color(lv.color_hex(0xffffff), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_text_font(test_font("montserratMedium", 12), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_text_opa(255, lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_bg_opa(255, lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.CURSOR|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.CURSOR|lv.STATE.DEFAULT)
# Set style for MAIN_PAGE_VET_SPINBOX, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default = lv.style_t()
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.init()
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_text_color(lv.color_hex(0xffffff))
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_text_font(test_font("montserratMedium", 12))
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_text_opa(255)
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_bg_opa(255)
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_bg_color(lv.color_hex(0x2195f6))
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_border_width(0)
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_radius(5)
style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default.set_shadow_width(0)
MAIN_PAGE_VET_SPINBOX_btn_plus.add_style(style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VET_SPINBOX_btn_minus.add_style(style_MAIN_PAGE_VET_SPINBOX_extra_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_34
MAIN_PAGE_label_34 = lv.label(MAIN_PAGE_cont_7)
MAIN_PAGE_label_34.set_text("VSET:")
MAIN_PAGE_label_34.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_34.set_width(lv.pct(100))
MAIN_PAGE_label_34.set_pos(5, 10)
MAIN_PAGE_label_34.set_size(60, 25)
# Set style for MAIN_PAGE_label_34, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_34.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_34.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_35
MAIN_PAGE_label_35 = lv.label(MAIN_PAGE_cont_7)
MAIN_PAGE_label_35.set_text("ISET:")
MAIN_PAGE_label_35.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_35.set_width(lv.pct(100))
MAIN_PAGE_label_35.set_pos(5, 55)
MAIN_PAGE_label_35.set_size(60, 25)
# Set style for MAIN_PAGE_label_35, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_35.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_text_font(test_font("blender_pro_bold", 24), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_35.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_36
MAIN_PAGE_label_36 = lv.label(MAIN_PAGE_cont_7)
MAIN_PAGE_label_36.set_text("V")
MAIN_PAGE_label_36.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_36.set_width(lv.pct(100))
MAIN_PAGE_label_36.set_pos(238, 10)
MAIN_PAGE_label_36.set_size(25, 25)
# Set style for MAIN_PAGE_label_36, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_36.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_text_font(test_font("blender_pro_bold", 28), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_36.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_37
MAIN_PAGE_label_37 = lv.label(MAIN_PAGE_cont_7)
MAIN_PAGE_label_37.set_text("A")
MAIN_PAGE_label_37.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_37.set_width(lv.pct(100))
MAIN_PAGE_label_37.set_pos(238, 55)
MAIN_PAGE_label_37.set_size(25, 25)
# Set style for MAIN_PAGE_label_37, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_37.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_text_font(test_font("blender_pro_bold", 28), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_37.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_cont_8
MAIN_PAGE_cont_8 = lv.obj(MAIN_PAGE)
MAIN_PAGE_cont_8.set_pos(115, 38)
MAIN_PAGE_cont_8.set_size(65, 60)
MAIN_PAGE_cont_8.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MAIN_PAGE_cont_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_cont_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_cont_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_40
MAIN_PAGE_label_40 = lv.label(MAIN_PAGE)
MAIN_PAGE_label_40.set_text("FAN:")
MAIN_PAGE_label_40.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_40.set_width(lv.pct(100))
MAIN_PAGE_label_40.set_pos(187, 290)
MAIN_PAGE_label_40.set_size(40, 20)
# Set style for MAIN_PAGE_label_40, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_40.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_40.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_FAN_LABEL
MAIN_PAGE_FAN_LABEL = lv.label(MAIN_PAGE)
MAIN_PAGE_FAN_LABEL.set_text("0000")
MAIN_PAGE_FAN_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_FAN_LABEL.set_width(lv.pct(100))
MAIN_PAGE_FAN_LABEL.set_pos(227, 290)
MAIN_PAGE_FAN_LABEL.set_size(40, 20)
# Set style for MAIN_PAGE_FAN_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_FAN_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_FAN_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_42
MAIN_PAGE_label_42 = lv.label(MAIN_PAGE)
MAIN_PAGE_label_42.set_text("RPM")
MAIN_PAGE_label_42.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_42.set_width(lv.pct(100))
MAIN_PAGE_label_42.set_pos(267, 290)
MAIN_PAGE_label_42.set_size(40, 20)
# Set style for MAIN_PAGE_label_42, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_42.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_42.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_43
MAIN_PAGE_label_43 = lv.label(MAIN_PAGE)
MAIN_PAGE_label_43.set_text("TEMP:")
MAIN_PAGE_label_43.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_43.set_width(lv.pct(100))
MAIN_PAGE_label_43.set_pos(357, 290)
MAIN_PAGE_label_43.set_size(48, 20)
# Set style for MAIN_PAGE_label_43, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_43.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_43.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_TEMP_LABEL
MAIN_PAGE_TEMP_LABEL = lv.label(MAIN_PAGE)
MAIN_PAGE_TEMP_LABEL.set_text("00.0")
MAIN_PAGE_TEMP_LABEL.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_TEMP_LABEL.set_width(lv.pct(100))
MAIN_PAGE_TEMP_LABEL.set_pos(405, 290)
MAIN_PAGE_TEMP_LABEL.set_size(40, 20)
# Set style for MAIN_PAGE_TEMP_LABEL, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_TEMP_LABEL.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_TEMP_LABEL.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_label_45
MAIN_PAGE_label_45 = lv.label(MAIN_PAGE)
MAIN_PAGE_label_45.set_text("C")
MAIN_PAGE_label_45.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_label_45.set_width(lv.pct(100))
MAIN_PAGE_label_45.set_pos(452, 290)
MAIN_PAGE_label_45.set_size(13, 20)
# Set style for MAIN_PAGE_label_45, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_label_45.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_label_45.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_OVP_BTU
MAIN_PAGE_OVP_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_OVP_BTU_label = lv.label(MAIN_PAGE_OVP_BTU)
MAIN_PAGE_OVP_BTU_label.set_text("OVP: 00.00V\n")
MAIN_PAGE_OVP_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_OVP_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_OVP_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_OVP_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_pos(187, 72)
MAIN_PAGE_OVP_BTU.set_size(100, 30)
# Set style for MAIN_PAGE_OVP_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_OVP_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_bg_color(lv.color_hex(0xacacac), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OVP_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_OCP_BTU
MAIN_PAGE_OCP_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_OCP_BTU_label = lv.label(MAIN_PAGE_OCP_BTU)
MAIN_PAGE_OCP_BTU_label.set_text("OCP: 00.00A\n")
MAIN_PAGE_OCP_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_OCP_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_OCP_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_OCP_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_pos(187, 109)
MAIN_PAGE_OCP_BTU.set_size(100, 30)
# Set style for MAIN_PAGE_OCP_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_OCP_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_bg_color(lv.color_hex(0xacacac), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_text_font(test_font("blender_pro_bold", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OCP_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_VOLTM_BTU
MAIN_PAGE_VOLTM_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_VOLTM_BTU_label = lv.label(MAIN_PAGE_VOLTM_BTU)
MAIN_PAGE_VOLTM_BTU_label.set_text("VOLTM\n")
MAIN_PAGE_VOLTM_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_VOLTM_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_VOLTM_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_VOLTM_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_pos(410, 253)
MAIN_PAGE_VOLTM_BTU.set_size(60, 30)
# Set style for MAIN_PAGE_VOLTM_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_VOLTM_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_bg_color(lv.color_hex(0xff4461), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_VOLTM_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MAIN_PAGE_OSCILLO_BTU
MAIN_PAGE_OSCILLO_BTU = lv.btn(MAIN_PAGE)
MAIN_PAGE_OSCILLO_BTU_label = lv.label(MAIN_PAGE_OSCILLO_BTU)
MAIN_PAGE_OSCILLO_BTU_label.set_text("OSCILLO\n")
MAIN_PAGE_OSCILLO_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MAIN_PAGE_OSCILLO_BTU_label.set_width(lv.pct(100))
MAIN_PAGE_OSCILLO_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MAIN_PAGE_OSCILLO_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_pos(330, 253)
MAIN_PAGE_OSCILLO_BTU.set_size(70, 30)
# Set style for MAIN_PAGE_OSCILLO_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MAIN_PAGE_OSCILLO_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_bg_color(lv.color_hex(0xe32dff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MAIN_PAGE_OSCILLO_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

MAIN_PAGE.update_layout()
# Create MEUN_PAGE
MEUN_PAGE = lv.obj()
MEUN_PAGE.set_size(480, 320)
MEUN_PAGE.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MEUN_PAGE, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MEUN_PAGE.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MEUN_PAGE_MEUN_
MEUN_PAGE_MEUN_ = lv.menu(MEUN_PAGE)
MEUN_PAGE_MEUN__sidebar_page = lv.menu_page(MEUN_PAGE_MEUN_, "SETTING")
MEUN_PAGE_MEUN_.set_sidebar_page(MEUN_PAGE_MEUN__sidebar_page)
MEUN_PAGE_MEUN__sidebar_page.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
MEUN_PAGE_MEUN__subpage_0 = lv.menu_page(MEUN_PAGE_MEUN_, None)
MEUN_PAGE_MEUN__subpage_0.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
MEUN_PAGE_MEUN__cont_0 = lv.menu_cont(MEUN_PAGE_MEUN__sidebar_page)
MEUN_PAGE_MEUN__label_0 = lv.label(MEUN_PAGE_MEUN__cont_0)
MEUN_PAGE_MEUN__label_0.set_text("BLE&WIFI")
MEUN_PAGE_MEUN__label_0.set_size(lv.pct(100), lv.SIZE.CONTENT)
MEUN_PAGE_MEUN_.set_load_page_event(MEUN_PAGE_MEUN__cont_0, MEUN_PAGE_MEUN__subpage_0)
lv.event_send(MEUN_PAGE_MEUN__cont_0, lv.EVENT.CLICKED, None);MEUN_PAGE_MEUN__subpage_1 = lv.menu_page(MEUN_PAGE_MEUN_, None)
MEUN_PAGE_MEUN__subpage_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
MEUN_PAGE_MEUN__cont_1 = lv.menu_cont(MEUN_PAGE_MEUN__sidebar_page)
MEUN_PAGE_MEUN__label_1 = lv.label(MEUN_PAGE_MEUN__cont_1)
MEUN_PAGE_MEUN__label_1.set_text("PID_INFO")
MEUN_PAGE_MEUN__label_1.set_size(lv.pct(100), lv.SIZE.CONTENT)
MEUN_PAGE_MEUN_.set_load_page_event(MEUN_PAGE_MEUN__cont_1, MEUN_PAGE_MEUN__subpage_1)
MEUN_PAGE_MEUN__subpage_2 = lv.menu_page(MEUN_PAGE_MEUN_, None)
MEUN_PAGE_MEUN__subpage_2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
MEUN_PAGE_MEUN__cont_2 = lv.menu_cont(MEUN_PAGE_MEUN__sidebar_page)
MEUN_PAGE_MEUN__label_2 = lv.label(MEUN_PAGE_MEUN__cont_2)
MEUN_PAGE_MEUN__label_2.set_text("DEVICE_INFO")
MEUN_PAGE_MEUN__label_2.set_size(lv.pct(100), lv.SIZE.CONTENT)
MEUN_PAGE_MEUN_.set_load_page_event(MEUN_PAGE_MEUN__cont_2, MEUN_PAGE_MEUN__subpage_2)
MEUN_PAGE_MEUN_.set_pos(0, 0)
MEUN_PAGE_MEUN_.set_size(480, 320)
MEUN_PAGE_MEUN_.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for MEUN_PAGE_MEUN_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MEUN_PAGE_MEUN_.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_MEUN_.set_style_bg_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_MEUN_.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_MEUN_.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_MEUN_.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MEUN_PAGE_MEUN_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default = lv.style_t()
style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default.init()
style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default.set_bg_opa(255)
style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default.set_bg_color(lv.color_hex(0xf2f2f2))
style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default.set_radius(0)
MEUN_PAGE_MEUN__sidebar_page.add_style(style_MEUN_PAGE_MEUN__extra_sidebar_page_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MEUN_PAGE_MEUN_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MEUN_PAGE_MEUN__extra_option_btns_main_default = lv.style_t()
style_MEUN_PAGE_MEUN__extra_option_btns_main_default.init()
style_MEUN_PAGE_MEUN__extra_option_btns_main_default.set_text_color(lv.color_hex(0x000000))
style_MEUN_PAGE_MEUN__extra_option_btns_main_default.set_text_font(test_font("Alatsi_Regular", 18))
style_MEUN_PAGE_MEUN__extra_option_btns_main_default.set_text_opa(255)
style_MEUN_PAGE_MEUN__extra_option_btns_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_MEUN_PAGE_MEUN__extra_option_btns_main_default.set_pad_top(6)
style_MEUN_PAGE_MEUN__extra_option_btns_main_default.set_pad_bottom(7)
MEUN_PAGE_MEUN__cont_0.add_style(style_MEUN_PAGE_MEUN__extra_option_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_MEUN__cont_1.add_style(style_MEUN_PAGE_MEUN__extra_option_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_MEUN__cont_2.add_style(style_MEUN_PAGE_MEUN__extra_option_btns_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for MEUN_PAGE_MEUN_, Part: lv.PART.MAIN, State: lv.STATE.CHECKED.
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked = lv.style_t()
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.init()
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_text_color(lv.color_hex(0x000000))
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_text_font(test_font("Alatsi_Regular", 20))
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_text_opa(255)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_text_align(lv.TEXT_ALIGN.CENTER)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_border_width(2)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_border_opa(255)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_border_color(lv.color_hex(0x000000))
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_border_side(lv.BORDER_SIDE.BOTTOM)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_radius(2)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_bg_opa(255)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_bg_color(lv.color_hex(0xd2d2d2))
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_bg_grad_dir(lv.GRAD_DIR.HOR)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_bg_grad_color(lv.color_hex(0xffffff))
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_bg_main_stop(0)
style_MEUN_PAGE_MEUN__extra_option_btns_main_checked.set_bg_grad_stop(255)
MEUN_PAGE_MEUN__cont_0.add_style(style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)
MEUN_PAGE_MEUN__cont_1.add_style(style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)
MEUN_PAGE_MEUN__cont_2.add_style(style_MEUN_PAGE_MEUN__extra_option_btns_main_checked, lv.PART.MAIN|lv.STATE.CHECKED)
# Set style for MEUN_PAGE_MEUN_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
style_MEUN_PAGE_MEUN__extra_main_title_main_default = lv.style_t()
style_MEUN_PAGE_MEUN__extra_main_title_main_default.init()
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_text_color(lv.color_hex(0x3f4657))
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_text_font(test_font("Alatsi_Regular", 25))
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_text_opa(255)
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_bg_opa(255)
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_bg_color(lv.color_hex(0xd0d0d0))
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_pad_top(7)
style_MEUN_PAGE_MEUN__extra_main_title_main_default.set_pad_bottom(7)
MEUN_PAGE_MEUN__title = MEUN_PAGE_MEUN_.get_child(0)
MEUN_PAGE_MEUN__title.set_size(lv.pct(100), lv.SIZE.CONTENT)
MEUN_PAGE_MEUN_.get_sidebar_header().add_style(style_MEUN_PAGE_MEUN__extra_main_title_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create MEUN_PAGE_BACK_SET_BTU
MEUN_PAGE_BACK_SET_BTU = lv.btn(MEUN_PAGE)
MEUN_PAGE_BACK_SET_BTU_label = lv.label(MEUN_PAGE_BACK_SET_BTU)
MEUN_PAGE_BACK_SET_BTU_label.set_text("BACK")
MEUN_PAGE_BACK_SET_BTU_label.set_long_mode(lv.label.LONG.WRAP)
MEUN_PAGE_BACK_SET_BTU_label.set_width(lv.pct(100))
MEUN_PAGE_BACK_SET_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
MEUN_PAGE_BACK_SET_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_pos(404, 285)
MEUN_PAGE_BACK_SET_BTU.set_size(71, 30)
# Set style for MEUN_PAGE_BACK_SET_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
MEUN_PAGE_BACK_SET_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_bg_color(lv.color_hex(0x6c6c6c), lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_text_font(test_font("blender_pro_bold", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
MEUN_PAGE_BACK_SET_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

MEUN_PAGE.update_layout()
# Create OSCILLO_PAGE
OSCILLO_PAGE = lv.obj()
OSCILLO_PAGE.set_size(480, 320)
OSCILLO_PAGE.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for OSCILLO_PAGE, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE.set_style_bg_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_chart_1
OSCILLO_PAGE_chart_1 = lv.chart(OSCILLO_PAGE)
OSCILLO_PAGE_chart_1.set_type(lv.chart.TYPE.LINE)
OSCILLO_PAGE_chart_1.set_div_line_count(30, 20)
OSCILLO_PAGE_chart_1.set_point_count(5)
OSCILLO_PAGE_chart_1.set_range(lv.chart.AXIS.PRIMARY_Y, 0, 30)
OSCILLO_PAGE_chart_1.set_range(lv.chart.AXIS.SECONDARY_Y, 0, 10)
OSCILLO_PAGE_chart_1.set_zoom_x(256)
OSCILLO_PAGE_chart_1.set_zoom_y(256)
OSCILLO_PAGE_chart_1.set_style_size(0, lv.PART.INDICATOR)
OSCILLO_PAGE_chart_1.set_pos(0, 0)
OSCILLO_PAGE_chart_1.set_size(360, 320)
OSCILLO_PAGE_chart_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for OSCILLO_PAGE_chart_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_chart_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_bg_color(lv.color_hex(0xf9f9f9), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_border_color(lv.color_hex(0x717171), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_line_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_line_color(lv.color_hex(0x999999), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for OSCILLO_PAGE_chart_1, Part: lv.PART.TICKS, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_chart_1.set_style_text_color(lv.color_hex(0x151212), lv.PART.TICKS|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_text_font(test_font("montserratMedium", 12), lv.PART.TICKS|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_text_opa(255, lv.PART.TICKS|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_line_width(2, lv.PART.TICKS|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_line_color(lv.color_hex(0xe8e8e8), lv.PART.TICKS|lv.STATE.DEFAULT)
OSCILLO_PAGE_chart_1.set_style_line_opa(255, lv.PART.TICKS|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_cont_1
OSCILLO_PAGE_cont_1 = lv.obj(OSCILLO_PAGE)
OSCILLO_PAGE_cont_1.set_pos(370, 0)
OSCILLO_PAGE_cont_1.set_size(100, 320)
OSCILLO_PAGE_cont_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for OSCILLO_PAGE_cont_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_cont_1.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_border_color(lv.color_hex(0x535353), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_cont_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create OSCILLO_PAGE_BACK_OSCILLO_
OSCILLO_PAGE_BACK_OSCILLO_ = lv.btn(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_BACK_OSCILLO__label = lv.label(OSCILLO_PAGE_BACK_OSCILLO_)
OSCILLO_PAGE_BACK_OSCILLO__label.set_text("BACK")
OSCILLO_PAGE_BACK_OSCILLO__label.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_BACK_OSCILLO__label.set_width(lv.pct(100))
OSCILLO_PAGE_BACK_OSCILLO__label.align(lv.ALIGN.CENTER, 0, 0)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_pad_all(0, lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_pos(5, 286)
OSCILLO_PAGE_BACK_OSCILLO_.set_size(50, 25)
# Set style for OSCILLO_PAGE_BACK_OSCILLO_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_BACK_OSCILLO_.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_bg_color(lv.color_hex(0xa0983e), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_BACK_OSCILLO_.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_btn_2
OSCILLO_PAGE_btn_2 = lv.btn(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_btn_2_label = lv.label(OSCILLO_PAGE_btn_2)
OSCILLO_PAGE_btn_2_label.set_text("AUTO")
OSCILLO_PAGE_btn_2_label.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_btn_2_label.set_width(lv.pct(100))
OSCILLO_PAGE_btn_2_label.align(lv.ALIGN.CENTER, 0, 0)
OSCILLO_PAGE_btn_2.set_style_pad_all(0, lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_pos(5, 133)
OSCILLO_PAGE_btn_2.set_size(40, 27)
# Set style for OSCILLO_PAGE_btn_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_btn_2.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_bg_color(lv.color_hex(0x53b947), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_btn_3
OSCILLO_PAGE_btn_3 = lv.btn(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_btn_3_label = lv.label(OSCILLO_PAGE_btn_3)
OSCILLO_PAGE_btn_3_label.set_text("RG")
OSCILLO_PAGE_btn_3_label.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_btn_3_label.set_width(lv.pct(100))
OSCILLO_PAGE_btn_3_label.align(lv.ALIGN.CENTER, 0, 0)
OSCILLO_PAGE_btn_3.set_style_pad_all(0, lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_pos(5, 169)
OSCILLO_PAGE_btn_3.set_size(40, 25)
# Set style for OSCILLO_PAGE_btn_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_btn_3.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_bg_color(lv.color_hex(0x19bdda), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_btn_4
OSCILLO_PAGE_btn_4 = lv.btn(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_btn_4_label = lv.label(OSCILLO_PAGE_btn_4)
OSCILLO_PAGE_btn_4_label.set_text("LF")
OSCILLO_PAGE_btn_4_label.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_btn_4_label.set_width(lv.pct(100))
OSCILLO_PAGE_btn_4_label.align(lv.ALIGN.CENTER, 0, 0)
OSCILLO_PAGE_btn_4.set_style_pad_all(0, lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_pos(5, 203)
OSCILLO_PAGE_btn_4.set_size(40, 25)
# Set style for OSCILLO_PAGE_btn_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_btn_4.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_bg_color(lv.color_hex(0x19bdda), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_btn_5
OSCILLO_PAGE_btn_5 = lv.btn(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_btn_5_label = lv.label(OSCILLO_PAGE_btn_5)
OSCILLO_PAGE_btn_5_label.set_text("DO")
OSCILLO_PAGE_btn_5_label.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_btn_5_label.set_width(lv.pct(100))
OSCILLO_PAGE_btn_5_label.align(lv.ALIGN.CENTER, 0, 0)
OSCILLO_PAGE_btn_5.set_style_pad_all(0, lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_pos(51, 168)
OSCILLO_PAGE_btn_5.set_size(40, 25)
# Set style for OSCILLO_PAGE_btn_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_btn_5.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_bg_color(lv.color_hex(0x19bdda), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_btn_6
OSCILLO_PAGE_btn_6 = lv.btn(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_btn_6_label = lv.label(OSCILLO_PAGE_btn_6)
OSCILLO_PAGE_btn_6_label.set_text("UP")
OSCILLO_PAGE_btn_6_label.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_btn_6_label.set_width(lv.pct(100))
OSCILLO_PAGE_btn_6_label.align(lv.ALIGN.CENTER, 0, 0)
OSCILLO_PAGE_btn_6.set_style_pad_all(0, lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_pos(51, 203)
OSCILLO_PAGE_btn_6.set_size(40, 25)
# Set style for OSCILLO_PAGE_btn_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_btn_6.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_bg_color(lv.color_hex(0x19bdda), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_btn_7
OSCILLO_PAGE_btn_7 = lv.btn(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_btn_7_label = lv.label(OSCILLO_PAGE_btn_7)
OSCILLO_PAGE_btn_7_label.set_text("STOP")
OSCILLO_PAGE_btn_7_label.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_btn_7_label.set_width(lv.pct(100))
OSCILLO_PAGE_btn_7_label.align(lv.ALIGN.CENTER, 0, 0)
OSCILLO_PAGE_btn_7.set_style_pad_all(0, lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_pos(51, 133)
OSCILLO_PAGE_btn_7.set_size(40, 27)
# Set style for OSCILLO_PAGE_btn_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_btn_7.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_bg_color(lv.color_hex(0xff5871), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_btn_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_2
OSCILLO_PAGE_label_2 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_2.set_text("00.00")
OSCILLO_PAGE_label_2.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_2.set_width(lv.pct(100))
OSCILLO_PAGE_label_2.set_pos(34, 2)
OSCILLO_PAGE_label_2.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_3
OSCILLO_PAGE_label_3 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_3.set_text("00.00")
OSCILLO_PAGE_label_3.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_3.set_width(lv.pct(100))
OSCILLO_PAGE_label_3.set_pos(34, 18)
OSCILLO_PAGE_label_3.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_5
OSCILLO_PAGE_label_5 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_5.set_text("00.00")
OSCILLO_PAGE_label_5.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_5.set_width(lv.pct(100))
OSCILLO_PAGE_label_5.set_pos(34, 50)
OSCILLO_PAGE_label_5.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_5, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_5.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_5.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_4
OSCILLO_PAGE_label_4 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_4.set_text("00.00")
OSCILLO_PAGE_label_4.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_4.set_width(lv.pct(100))
OSCILLO_PAGE_label_4.set_pos(34, 34)
OSCILLO_PAGE_label_4.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_4, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_4.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_4.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_7
OSCILLO_PAGE_label_7 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_7.set_text("00.00")
OSCILLO_PAGE_label_7.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_7.set_width(lv.pct(100))
OSCILLO_PAGE_label_7.set_pos(34, 82)
OSCILLO_PAGE_label_7.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_7, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_7.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_7.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_6
OSCILLO_PAGE_label_6 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_6.set_text("00.00")
OSCILLO_PAGE_label_6.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_6.set_width(lv.pct(100))
OSCILLO_PAGE_label_6.set_pos(34, 66)
OSCILLO_PAGE_label_6.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_6, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_6.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_6.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_8
OSCILLO_PAGE_label_8 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_8.set_text("Amp:")
OSCILLO_PAGE_label_8.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_8.set_width(lv.pct(100))
OSCILLO_PAGE_label_8.set_pos(-2, 50)
OSCILLO_PAGE_label_8.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_8, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_8.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_8.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_9
OSCILLO_PAGE_label_9 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_9.set_text("Duty:")
OSCILLO_PAGE_label_9.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_9.set_width(lv.pct(100))
OSCILLO_PAGE_label_9.set_pos(-2, 17)
OSCILLO_PAGE_label_9.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_9, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_9.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_9.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_10
OSCILLO_PAGE_label_10 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_10.set_text("Freq:")
OSCILLO_PAGE_label_10.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_10.set_width(lv.pct(100))
OSCILLO_PAGE_label_10.set_pos(-2, 2)
OSCILLO_PAGE_label_10.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_10, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_10.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_10.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_11
OSCILLO_PAGE_label_11 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_11.set_text("Avg:")
OSCILLO_PAGE_label_11.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_11.set_width(lv.pct(100))
OSCILLO_PAGE_label_11.set_pos(-2, 65)
OSCILLO_PAGE_label_11.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_11, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_11.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_11.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_12
OSCILLO_PAGE_label_12 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_12.set_text("Vpp:")
OSCILLO_PAGE_label_12.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_12.set_width(lv.pct(100))
OSCILLO_PAGE_label_12.set_pos(-2, 33)
OSCILLO_PAGE_label_12.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_12, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_12.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_12.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_13
OSCILLO_PAGE_label_13 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_13.set_text("Vmin:")
OSCILLO_PAGE_label_13.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_13.set_width(lv.pct(100))
OSCILLO_PAGE_label_13.set_pos(-2, 98)
OSCILLO_PAGE_label_13.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_13, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_13.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_13.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_14
OSCILLO_PAGE_label_14 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_14.set_text("Vmax:")
OSCILLO_PAGE_label_14.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_14.set_width(lv.pct(100))
OSCILLO_PAGE_label_14.set_pos(-2, 81)
OSCILLO_PAGE_label_14.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_14, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_14.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_14.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_15
OSCILLO_PAGE_label_15 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_15.set_text("00.00")
OSCILLO_PAGE_label_15.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_15.set_width(lv.pct(100))
OSCILLO_PAGE_label_15.set_pos(34, 98)
OSCILLO_PAGE_label_15.set_size(40, 15)
# Set style for OSCILLO_PAGE_label_15, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_15.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_15.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_16
OSCILLO_PAGE_label_16 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_16.set_text("V")
OSCILLO_PAGE_label_16.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_16.set_width(lv.pct(100))
OSCILLO_PAGE_label_16.set_pos(79, 98)
OSCILLO_PAGE_label_16.set_size(15, 15)
# Set style for OSCILLO_PAGE_label_16, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_16.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_16.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_17
OSCILLO_PAGE_label_17 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_17.set_text("V")
OSCILLO_PAGE_label_17.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_17.set_width(lv.pct(100))
OSCILLO_PAGE_label_17.set_pos(79, 82)
OSCILLO_PAGE_label_17.set_size(15, 15)
# Set style for OSCILLO_PAGE_label_17, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_17.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_17.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_19
OSCILLO_PAGE_label_19 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_19.set_text("V")
OSCILLO_PAGE_label_19.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_19.set_width(lv.pct(100))
OSCILLO_PAGE_label_19.set_pos(79, 50)
OSCILLO_PAGE_label_19.set_size(15, 15)
# Set style for OSCILLO_PAGE_label_19, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_19.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_19.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_18
OSCILLO_PAGE_label_18 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_18.set_text("V")
OSCILLO_PAGE_label_18.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_18.set_width(lv.pct(100))
OSCILLO_PAGE_label_18.set_pos(79, 66)
OSCILLO_PAGE_label_18.set_size(15, 15)
# Set style for OSCILLO_PAGE_label_18, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_18.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_18.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_21
OSCILLO_PAGE_label_21 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_21.set_text("%")
OSCILLO_PAGE_label_21.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_21.set_width(lv.pct(100))
OSCILLO_PAGE_label_21.set_pos(79, 18)
OSCILLO_PAGE_label_21.set_size(15, 15)
# Set style for OSCILLO_PAGE_label_21, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_21.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_21.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_20
OSCILLO_PAGE_label_20 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_20.set_text("V")
OSCILLO_PAGE_label_20.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_20.set_width(lv.pct(100))
OSCILLO_PAGE_label_20.set_pos(79, 34)
OSCILLO_PAGE_label_20.set_size(15, 15)
# Set style for OSCILLO_PAGE_label_20, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_20.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_20.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_label_22
OSCILLO_PAGE_label_22 = lv.label(OSCILLO_PAGE_cont_1)
OSCILLO_PAGE_label_22.set_text("Hz")
OSCILLO_PAGE_label_22.set_long_mode(lv.label.LONG.WRAP)
OSCILLO_PAGE_label_22.set_width(lv.pct(100))
OSCILLO_PAGE_label_22.set_pos(79, 2)
OSCILLO_PAGE_label_22.set_size(15, 15)
# Set style for OSCILLO_PAGE_label_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_label_22.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_text_font(test_font("blender_pro_bold", 14), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_label_22.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create OSCILLO_PAGE_line_1
OSCILLO_PAGE_line_1 = lv.line(OSCILLO_PAGE)
OSCILLO_PAGE_line_1_line_points = [{"x":0, "y":0},{"x":96, "y":0},]
OSCILLO_PAGE_line_1.set_points(OSCILLO_PAGE_line_1_line_points, 2)
OSCILLO_PAGE_line_1.set_pos(373, 123)
OSCILLO_PAGE_line_1.set_size(100, 2)
# Set style for OSCILLO_PAGE_line_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
OSCILLO_PAGE_line_1.set_style_line_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_line_1.set_style_line_color(lv.color_hex(0x757575), lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_line_1.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
OSCILLO_PAGE_line_1.set_style_line_rounded(True, lv.PART.MAIN|lv.STATE.DEFAULT)

OSCILLO_PAGE.update_layout()
# Create CHART_PAGE
CHART_PAGE = lv.obj()
CHART_PAGE.set_size(480, 320)
CHART_PAGE.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for CHART_PAGE, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
CHART_PAGE.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE.set_style_bg_color(lv.color_hex(0xcccccc), lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create CHART_PAGE_UI_CHART
CHART_PAGE_UI_CHART = lv.chart(CHART_PAGE)
CHART_PAGE_UI_CHART.set_type(lv.chart.TYPE.LINE)
CHART_PAGE_UI_CHART.set_div_line_count(30, 20)
CHART_PAGE_UI_CHART.set_point_count(3)
CHART_PAGE_UI_CHART.set_range(lv.chart.AXIS.PRIMARY_Y, 0, 30)
CHART_PAGE_UI_CHART.set_axis_tick(lv.chart.AXIS.PRIMARY_Y, 10, 5, 5, 4, True, 30)
CHART_PAGE_UI_CHART.set_range(lv.chart.AXIS.SECONDARY_Y, 0, 10)
CHART_PAGE_UI_CHART.set_axis_tick(lv.chart.AXIS.SECONDARY_Y, 10, 5, 5, 4, True, 12)
CHART_PAGE_UI_CHART.set_zoom_x(256)
CHART_PAGE_UI_CHART.set_zoom_y(256)
CHART_PAGE_UI_CHART.set_style_size(0, lv.PART.INDICATOR)
CHART_PAGE_UI_CHART_series_0 = CHART_PAGE_UI_CHART.add_series(lv.color_hex(0x000000), lv.chart.AXIS.PRIMARY_Y)
CHART_PAGE_UI_CHART.set_next_value(CHART_PAGE_UI_CHART_series_0, 0)
CHART_PAGE_UI_CHART.set_next_value(CHART_PAGE_UI_CHART_series_0, 0)
CHART_PAGE_UI_CHART.set_next_value(CHART_PAGE_UI_CHART_series_0, 0)
CHART_PAGE_UI_CHART_series_1 = CHART_PAGE_UI_CHART.add_series(lv.color_hex(0x000000), lv.chart.AXIS.SECONDARY_Y)
CHART_PAGE_UI_CHART.set_next_value(CHART_PAGE_UI_CHART_series_1, 0)
CHART_PAGE_UI_CHART.set_next_value(CHART_PAGE_UI_CHART_series_1, 0)
CHART_PAGE_UI_CHART.set_next_value(CHART_PAGE_UI_CHART_series_1, 0)
CHART_PAGE_UI_CHART.set_pos(31, 12)
CHART_PAGE_UI_CHART.set_size(400, 300)
CHART_PAGE_UI_CHART.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for CHART_PAGE_UI_CHART, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
CHART_PAGE_UI_CHART.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_bg_color(lv.color_hex(0xf9f9f9), lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_line_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_line_color(lv.color_hex(0x999999), lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_line_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for CHART_PAGE_UI_CHART, Part: lv.PART.TICKS, State: lv.STATE.DEFAULT.
CHART_PAGE_UI_CHART.set_style_text_color(lv.color_hex(0x151212), lv.PART.TICKS|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_text_font(test_font("montserratMedium", 12), lv.PART.TICKS|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_text_opa(255, lv.PART.TICKS|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_line_width(2, lv.PART.TICKS|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_line_color(lv.color_hex(0xe8e8e8), lv.PART.TICKS|lv.STATE.DEFAULT)
CHART_PAGE_UI_CHART.set_style_line_opa(255, lv.PART.TICKS|lv.STATE.DEFAULT)

# Create CHART_PAGE_BACK_CHART_BTU
CHART_PAGE_BACK_CHART_BTU = lv.btn(CHART_PAGE)
CHART_PAGE_BACK_CHART_BTU_label = lv.label(CHART_PAGE_BACK_CHART_BTU)
CHART_PAGE_BACK_CHART_BTU_label.set_text("BACK")
CHART_PAGE_BACK_CHART_BTU_label.set_long_mode(lv.label.LONG.WRAP)
CHART_PAGE_BACK_CHART_BTU_label.set_width(lv.pct(100))
CHART_PAGE_BACK_CHART_BTU_label.align(lv.ALIGN.CENTER, 0, 0)
CHART_PAGE_BACK_CHART_BTU.set_style_pad_all(0, lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_pos(52, 18)
CHART_PAGE_BACK_CHART_BTU.set_size(52, 27)
# Set style for CHART_PAGE_BACK_CHART_BTU, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
CHART_PAGE_BACK_CHART_BTU.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_bg_color(lv.color_hex(0xa0983e), lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_radius(3, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_text_font(test_font("blender_pro_bold", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
CHART_PAGE_BACK_CHART_BTU.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

CHART_PAGE.update_layout()

def START_PAGE_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        lv.scr_load_anim(MAIN_PAGE, lv.SCR_LOAD_ANIM.OVER_BOTTOM, 200, 200, False)
START_PAGE.add_event_cb(lambda e: START_PAGE_event_handler(e), lv.EVENT.ALL, None)

def MAIN_PAGE_CHART_BTU_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(CHART_PAGE, lv.SCR_LOAD_ANIM.OVER_BOTTOM, 200, 200, False)
MAIN_PAGE_CHART_BTU.add_event_cb(lambda e: MAIN_PAGE_CHART_BTU_event_handler(e), lv.EVENT.ALL, None)

def MAIN_PAGE_MEUN_BTU_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(MEUN_PAGE, lv.SCR_LOAD_ANIM.OVER_BOTTOM, 200, 200, False)
MAIN_PAGE_MEUN_BTU.add_event_cb(lambda e: MAIN_PAGE_MEUN_BTU_event_handler(e), lv.EVENT.ALL, None)

def MAIN_PAGE_OSCILLO_BTU_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(OSCILLO_PAGE, lv.SCR_LOAD_ANIM.OVER_RIGHT, 200, 200, False)
MAIN_PAGE_OSCILLO_BTU.add_event_cb(lambda e: MAIN_PAGE_OSCILLO_BTU_event_handler(e), lv.EVENT.ALL, None)

def MEUN_PAGE_BACK_SET_BTU_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(MAIN_PAGE, lv.SCR_LOAD_ANIM.OVER_TOP, 200, 200, False)
MEUN_PAGE_BACK_SET_BTU.add_event_cb(lambda e: MEUN_PAGE_BACK_SET_BTU_event_handler(e), lv.EVENT.ALL, None)

def OSCILLO_PAGE_BACK_OSCILLO__event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(MAIN_PAGE, lv.SCR_LOAD_ANIM.OVER_LEFT, 200, 200, False)
OSCILLO_PAGE_BACK_OSCILLO_.add_event_cb(lambda e: OSCILLO_PAGE_BACK_OSCILLO__event_handler(e), lv.EVENT.ALL, None)

def CHART_PAGE_BACK_CHART_BTU_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(MAIN_PAGE, lv.SCR_LOAD_ANIM.OVER_TOP, 200, 200, False)
CHART_PAGE_BACK_CHART_BTU.add_event_cb(lambda e: CHART_PAGE_BACK_CHART_BTU_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(MAIN_PAGE)

while SDL.check():
    time.sleep_ms(5)

