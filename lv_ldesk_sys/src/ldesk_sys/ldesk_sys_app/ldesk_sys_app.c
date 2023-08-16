/*
 * @brief: 应用管理系统模块，包括应用列表的管理
 * @file: ldesk_sys_app.c
 * @author: moecly
 */

#include "ldesk_sys_app.h"
#include "lv_ldesk_sys/src/utils/list/list.h"
#include <stdint.h>

// 应用列表
static pn_list *apps_list;

/*
 * @brief: 初始化应用管理系统
 */
void ldesk_sys_app_init(void) { apps_list = list_new(); }

/*
 * @brief: 向应用列表中添加一个应用项
 * @param app: 待添加的应用项指针
 */
void add_app_item(app_item *app) { list_push_to_tail(apps_list, app); }

/*
 * @brief: 根据索引从应用列表中获取一个应用项
 * @param index: 应用项在列表中的索引
 * @return: 获取的应用项指针
 */
app_item *get_app_from_index(uint32_t index) {
  return (app_item *)list_get_val_from_index(apps_list, index);
}

/*
 * @brief: 获取应用列表的长度
 * @return: 应用列表的长度
 */
uint32_t get_apps_length(void) { return list_get_length(apps_list); }
