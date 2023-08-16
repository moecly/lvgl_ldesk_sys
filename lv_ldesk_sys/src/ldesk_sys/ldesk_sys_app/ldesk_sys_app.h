/*
 * @brief: 应用管理系统模块头文件，定义应用项结构和管理函数声明
 * @file: ldesk_sys_app.h
 * @author: moecly
 */

#ifndef __LDESK_SYS_APP_H_
#define __LDESK_SYS_APP_H_

#include "../ldesk_sys.h" // Include the main LDesk system header

// 应用项结构体
typedef struct {
  char *name; // 应用名称
  char *icon; // 应用图标
  uint32_t page_id;
} app_item;

/*
 * @brief: 向应用列表中添加一个应用项
 * @param app: 待添加的应用项指针
 */
void add_app_item(app_item *app);

/*
 * @brief: 初始化应用管理系统
 */
void ldesk_sys_app_init(void);

/*
 * @brief: 根据索引从应用列表中获取一个应用项
 * @param index: 应用项在列表中的索引
 * @return: 获取的应用项指针
 */
app_item *get_app_from_index(uint32_t index);

/*
 * @brief: 获取应用列表的长度
 * @return: 应用列表的长度
 */
uint32_t get_apps_number(void);

#endif // !__LDESK_SYS_APP_H_
