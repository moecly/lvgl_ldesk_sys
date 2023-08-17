/*
 * @brief: LDesk系统演示的初始化文件
 * @file: ldesk_sys_demo.c
 * @author: moecly
 */

#include "ldesk_sys_demo.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_app/ldesk_sys_app.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager/ldesk_sys_manager.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_page_opr/ldesk_sys_page_opr.h"
#include "lv_ldesk_sys/src/ldesk_sys_demo/ldesk_sys_page_conf/ldesk_sys_page_conf.h"
#include <stdint.h>

// 预定义的应用项数组
static app_item apps[] = {
    {
        .name = "GPS",
        .icon = SYMBOL_GPS,
        .font = (lv_font_t *)&font_symbol_32,
        .target_page_id = PAGE_NULL,
    },
    {
        .name = "WIFI",
        .icon = SYMBOL_WIFI,
        .font = (lv_font_t *)&lv_font_montserrat_32,
        .target_page_id = PAGE_WIFI,
    },
    {
        .name = "Setting",
        .icon = SYMBOL_SETTING,
        .font = (lv_font_t *)&font_symbol_32,
        .target_page_id = PAGE_SETTING,
    },
    {
        .name = "Calculator",
        .icon = SYMBOL_CALC,
        .font = (lv_font_t *)&font_symbol_32,
        .target_page_id = PAGE_NULL,
    },
    {
        .name = "Calendar",
        .icon = SYMBOL_CALENDAR,
        .font = (lv_font_t *)&font_symbol_32,
        .target_page_id = PAGE_NULL,
    },
};

/**
 * @brief 初始化应用列表
 */
static void apps_init(void) {
  ldesk_sys_app_init();
  uint32_t len = ARRAY_LEN(apps);
  uint32_t i = 0;
  for (; i < len; i++) {
    add_app_item(&apps[i]);
  }
}

/**
 * @brief LDesk系统演示的初始化函数
 */
void ldesk_sys_demo_init(void) {
  ldesk_sys_init();
  ldesk_sys_add_page(&page_apps);
  ldesk_sys_add_page(&page_setting);
  ldesk_sys_add_page(&page_wifi);
  apps_init();
  ldesk_sys_enter_page_from_id(PAGE_APPS);
}
