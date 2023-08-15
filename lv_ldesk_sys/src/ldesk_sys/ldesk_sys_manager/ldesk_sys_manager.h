/*
 * @brief: 系统管理模块头文件，定义页面对象和管理函数声明
 * @file: ldesk_sys_manager.h
 */

#ifndef __LDESK_SYS_MANAGER_H_
#define __LDESK_SYS_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../ldesk_sys.h"

#ifndef page_gui
#define page_gui lv_obj_t
#endif // !page_gui

// 页面操作句柄结构体
typedef struct {
  int (*init_handle)(page_gui *gui); // 初始化句柄函数指针
} page_ops;

// 页面对象结构体
typedef struct page_object {
  uint32_t id;   // 页面ID
  char *name;    // 页面名称
  page_gui *gui; // 页面GUI对象
  page_ops ops;  // 页面操作句柄
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
 * @brief: 创建页面
 * @param id: 页面ID
 * @return: 成功返回0，失败返回-1
 */
int ldesk_sys_create_page(uint32_t id);

/*
 * @brief: 根据ID获取页面对象
 * @param id: 页面ID
 * @return: 页面对象指针，若不存在则返回NULL
 */
page_object *ldesk_sys_get_page_from_id(uint32_t id);

/*
 * @brief: 根据ID获取页面GUI对象
 * @param id: 页面ID
 * @return: 页面GUI对象指针，若不存在则返回NULL
 */
page_gui *get_page_gui_from_id(uint32_t id);

/*
 * @brief: 获取页面GUI对象
 * @param page: 页面对象指针
 * @return: 页面GUI对象指针
 */
page_gui *get_page_gui(page_object *page);

/*
 * @brief: 加载页面到屏幕
 * @param page: 页面对象指针
 */
void ldesk_sys_load_page(page_object *page);

/*
 * @brief: 根据ID加载页面到屏幕
 * @param id: 页面ID
 * @return: 成功返回0，失败返回-1
 */
int ldesk_sys_load_page_from_id(uint32_t id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__LDESK_SYS_MANAGER_H_
