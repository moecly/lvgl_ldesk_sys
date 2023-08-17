/*
 * @brief: 页面配置文件的实现
 * @file: ldesk_sys_page_conf.c
 * @author: moecly
 */

#include "ldesk_sys_page_conf.h"

/**
 * @brief 页面对象的定义与初始化
 */
page_object page_apps = {
    .id = PAGE_APPS,
    .name = "apps",
    .ops.init_handle = PAGE_INIT_DEF(apps),
    .ops.exit_handle = PAGE_EXIT_DEF(apps),
};

page_object page_setting = {
    .id = PAGE_SETTING,
    .name = "setting",
    .ops.init_handle = PAGE_INIT_DEF(setting),
    .ops.exit_handle = PAGE_EXIT_DEF(setting),
};

page_object page_wifi = {
    .id = PAGE_WIFI,
    .name = "wifi",
    .ops.init_handle = PAGE_INIT_DEF(wifi),
    .ops.exit_handle = PAGE_EXIT_DEF(wifi),
};
