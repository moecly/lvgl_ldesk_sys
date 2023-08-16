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

#include "../ldesk_sys.h"

/**
 * @brief 初始化应用页面
 * @param root 页面的根GUI对象
 * @return 返回初始化结果，0 表示成功，其他值表示失败
 */
int page_apps_init(lv_obj_t *root);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__LDESK_SYS_PAGE_APPS_H_
