/*
 * @brief: 页面操作相关函数的头文件
 * @file: ldesk_sys_page_opr.h
 * @author: moecly
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

int ldesk_sys_disp_page_from_id(uint32_t id, void *create_params,
                                void *del_params, lv_scr_load_anim_t load_anim);

/*
 * @brief: 加载页面到屏幕
 * @param page: 页面对象指针
 */
void ldesk_sys_load_page(struct page_object *page,
                         lv_scr_load_anim_t load_anim);

/*
 * @brief: 根据ID加载页面到屏幕
 * @param id: 页面ID
 * @return: 成功返回0，失败返回-1
 */
int ldesk_sys_load_page_from_id(uint32_t id, lv_scr_load_anim_t load_anim);

/*
 * @brief: 创建页面
 * @param id: 页面ID
 * @return: 成功返回0，失败返回-1
 */
int ldesk_sys_create_page_from_id(uint32_t id, void *data);

int ldesk_sys_create_page(struct page_object *page, void *data);

int ldesk_sys_exit_page_from_id(uint32_t id, void *data);

int ldesk_sys_exit_page(struct page_object *page, void *data);

#endif // !__LDESK_SYS_PAGE_OPR_H_
