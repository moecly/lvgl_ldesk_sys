/*
 * @brief: 页面操作相关函数的头文件
 * @file: ldesk_sys_page_opr.h
 */

#ifndef __LDESK_SYS_PAGE_OPR_H_
#define __LDESK_SYS_PAGE_OPR_H_

#include "../ldesk_sys.h"

/**
 * @brief 设置状态栏的状态为启用或禁用
 * @param state 状态栏状态
 */
void set_status_bar(int state);

/**
 * @brief 设置状态栏的状态
 * @param type 状态栏类型
 * @param state 状态栏状态
 */
void set_status_bar_state(int type, int state);

/**
 * @brief 设置状态栏时间的显示状态
 * @param state 时间显示状态
 */
void set_status_bar_time(int state);

/**
 * @brief 设置状态栏标题的显示状态
 * @param state 标题显示状态
 */
void set_status_bar_title(int state);

/**
 * @brief 设置状态栏标题文本
 * @param title 标题文本
 */
void set_status_bar_title_text(char *title);

/**
 * @brief 设置状态栏的父对象
 * @param parent 父对象
 */
void set_status_bar_parent(lv_obj_t *parent);

#endif // !__LDESK_SYS_PAGE_OPR_H_
