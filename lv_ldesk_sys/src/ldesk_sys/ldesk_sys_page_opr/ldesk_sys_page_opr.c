/*
 * @brief: 页面操作相关函数的实现文件
 * @file: ldesk_sys_page_opr.c
 */

#include "ldesk_sys_page_opr.h"
#include "lv_ldesk_sys/src/ldesk_sys/components/status_bar/status_bar.h"

/**
 * @brief 设置状态栏的状态
 * @param type 状态栏类型
 * @param state 状态栏状态
 */
void set_status_bar_state(int type, int state) {
  status_bar_instance()->set_state(type, state);
}

/**
 * @brief 设置状态栏的状态为启用或禁用
 * @param state 状态栏状态
 */
void set_status_bar(int state) { set_status_bar_state(STATUS_BAR, state); }

/**
 * @brief 设置状态栏的父对象
 * @param parent 父对象
 */
void set_status_bar_parent(lv_obj_t *parent) {
  status_bar_instance()->set_parent(parent);
}

/**
 * @brief 设置状态栏时间的显示状态
 * @param state 时间显示状态
 */
void set_status_bar_time(int state) { set_status_bar_state(TIME, state); }

/**
 * @brief 设置状态栏标题的显示状态
 * @param state 标题显示状态
 */
void set_status_bar_title(int state) { set_status_bar_state(TITLE, state); }

/**
 * @brief 设置状态栏标题文本
 * @param title 标题文本
 */
void set_status_bar_title_text(char *title) {
  status_bar_instance()->set_title(title);
}
