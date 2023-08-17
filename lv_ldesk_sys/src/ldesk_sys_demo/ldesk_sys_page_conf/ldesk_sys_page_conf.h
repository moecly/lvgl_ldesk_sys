/*
 * @brief: 页面配置头文件
 * @file: ldesk_sys_page_conf.h
 * @author: moecly
 */

#ifndef __LDESK_SYS_PAGE_CONF_H_
#define __LDESK_SYS_PAGE_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../ldesk_sys/ldesk_sys_page_apps/ldesk_sys_page_apps.h"
#include "../page_setting/page_setting.h"
#include "../page_wifi/page_wifi.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager/ldesk_sys_manager.h"
#include "lvgl/lvgl.h"

// 定义页面初始化函数宏
#define PAGE_INIT_DEF(TAG) page_##TAG##_init

// 定义页面退出函数宏
#define PAGE_EXIT_DEF(TAG) page_##TAG##_exit

// 页面ID枚举
typedef enum {
  PAGE_NULL = -1,
  PAGE_APPS,
  PAGE_SETTING,
  PAGE_WIFI,
} PAGE_ID;

// 声明页面对象
extern page_object page_apps;
extern page_object page_setting;
extern page_object page_wifi;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__LDESK_SYS_PAGE_CONF_H_
