/*
 * @brief: 页面配置文件的实现
 * @file: ldesk_sys_page_conf.c
 */

#include "ldesk_sys_page_conf.h"

/**
 * @brief 页面对象的定义与初始化
 */
page_object page_apps = {
    .id = PAGE_APPS,
    .name = "apps",
    .ops.init_handle = PAGE_INIT_DEF(apps),
};
