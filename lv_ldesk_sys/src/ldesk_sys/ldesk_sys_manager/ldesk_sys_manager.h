/*
 * @brief: 系统管理模块头文件，定义页面对象和管理函数声明
 * @file: ldesk_sys_manager.h
 * @author: moecly
 */

#ifndef __LDESK_SYS_MANAGER_H_
#define __LDESK_SYS_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

#ifndef page_gui
#define page_gui lv_obj_t
#endif // !page_gui

#ifndef page_id
#define page_id int
#endif // !page_id

/*
 * 页面操作句柄结构体
 */
typedef struct {
  int (*init_handle)(page_gui *gui, void *data); /* 初始化句柄函数指针 */
  int (*exit_handle)(page_gui *gui, void *data); /* 初始化句柄函数指针 */
} page_ops;

/*
 * 页面对象结构体
 */
typedef struct {
  page_id id;   /* 页面ID */
  char *name;    /* 页面名称 */
  page_gui *gui; /* 页面GUI对象 */
  page_ops ops;  /* 页面操作句柄 */
} page_object;

/*
 * @brief: 向页面列表中添加页面对象
 * @param page: 待添加的页面对象指针
 */
void ldesk_sys_add_page(page_object *page);

/*
 * @brief: 初始化系统管理模块
 */
void ldesk_sys_init(void);

/*
 * @brief: 根据ID获取页面对象
 * @param id: 页面ID
 * @return: 页面对象指针，若不存在则返回NULL
 */
page_object *ldesk_sys_get_page_from_id(page_id id);

/*
 * @brief: 根据ID获取页面GUI对象
 * @param id: 页面ID
 * @return: 页面GUI对象指针，若不存在则返回NULL
 */
page_gui *get_page_gui_from_id(page_id id);

/*
 * @brief: 获取页面GUI对象
 * @param page: 页面对象指针
 * @return: 页面GUI对象指针
 */
page_gui *get_page_gui(page_object *page);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__LDESK_SYS_MANAGER_H_
