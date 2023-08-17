/*
 * @brief: LDesk系统演示的头文件
 * @file: ldesk_sys_demo.h
 * @author: moecly
 */

#ifndef __LDESK_SYS_DEMO_H_
#define __LDESK_SYS_DEMO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "fonts/font_symbol_def.h"
#include "ldesk_sys_page_conf/ldesk_sys_page_conf.h"
#include "lvgl/lvgl.h"
#include "page_setting/page_setting.h"
#include "page_wifi/page_wifi.h"
#include "lv_ldesk_sys/src/utils/utils.h"

LV_FONT_DECLARE(font_symbol_14);
LV_FONT_DECLARE(font_symbol_32)

/**
 * @brief LDesk系统演示的初始化函数声明
 */
void ldesk_sys_demo_init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__LDESK_SYS_DEMO_H_
