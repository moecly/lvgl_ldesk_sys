/*
 * @brief: 应用页面的头文件，定义应用页面的初始化函数接口
 * @file: ldesk_sys_page_apps.h
 * @author: moecly
 */

#ifndef __LDESK_SYS_PAGE_APPS_H_
#define __LDESK_SYS_PAGE_APPS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager/ldesk_sys_manager.h"
#include "lv_ldesk_sys_conf.h"
#include "lvgl/lvgl.h"

enum {
  SHOW,
  HIDE,
};

/**
 * @brief 初始化应用页面
 * @param root 页面的根GUI对象
 * @return 返回初始化结果，0 表示成功，其他值表示失败
 */
int page_apps_init(page_gui *root, void *data);
int page_apps_exit(page_gui *gui, void *data);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__LDESK_SYS_PAGE_APPS_H_
