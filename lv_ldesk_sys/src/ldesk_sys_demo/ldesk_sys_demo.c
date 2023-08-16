/*
 * @brief: LDesk系统演示的初始化文件
 * @file: ldesk_sys_demo.c
 * @author: moecly
 */

#include "ldesk_sys_demo.h"
#include "src/core/lv_disp.h"
#include <stdint.h>

// 预定义的应用项数组
static app_item apps[] = {
    {.name = "Book", .icon = "Book"},
    {.name = "Arduboy", .icon = "Arduboy"},
    {.name = "NES", .icon = "NES"},
    {.name = "Setting", .icon = "Setting"},
    {.name = "Calculator", .icon = "Calculator"},
    {.name = "Calendar", .icon = "Calendar"},
    {.name = "Arduboy", .icon = "Arduboy"},
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
  apps_init();
  ldesk_sys_disp_page_from_id(PAGE_APPS, NULL, NULL,
                              LV_SCR_LOAD_ANIM_MOVE_RIGHT);
}
