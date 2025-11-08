/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"

#if LV_USE_FS_RAWFS

const rawfs_size_t rawfs_file_count = 3;
rawfs_file_t rawfs_files[3] = {
	0x0, 0, 138004, "/Kang_Tao_Logo_02_CP2077.bin",
	0x21b14, 0, 1732, "/offline_24px.bin",
	0x221d8, 0, 1732, "/temperature_24px.bin",

};

#endif  /*LV_USE_FS_RAWFS*/ 