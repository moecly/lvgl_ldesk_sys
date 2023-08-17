/*
 * @brief: 桌面系统管理模块，用于管理页面对象和操作
 * @file: ldesk_sys_manager.c
 * @author: moecly
 */

#include "ldesk_sys_manager.h"
#include "lv_ldesk_sys/src/ldesk_sys/components/status_bar/status_bar.h"
#include "lv_ldesk_sys/src/utils/list/list.h"
#include "lv_ldesk_sys/src/utils/log_msg/log_msg.h"
#include "src/core/lv_disp.h"
#include "src/core/lv_obj_tree.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>

static pn_list *page_list;

/*
 * @brief: 初始化桌面系统
 *        初始化页面列表
 */
void ldesk_sys_init(void) { page_list = list_new(); }

/*
 * @brief: 向桌面系统中添加一个页面对象
 * @param page: 待添加的页面对象指针
 */
void ldesk_sys_add_page(page_object *page) {
  list_push_to_tail(page_list, page);
}

/*
 * @brief: 获取页面的GUI对象
 * @param page: 页面对象指针
 * @return: 返回页面的GUI对象
 */
page_gui *get_page_gui(page_object *page) { return page->gui; }

/*
 * @brief: 根据ID获取页面的GUI对象
 * @param id: 页面的ID
 * @return: 返回页面的GUI对象，若获取失败则返回NULL
 */
page_gui *get_page_gui_from_id(page_id id) {
  page_object *page = ldesk_sys_get_page_from_id(id);
  if (validate_pointer(page)) {
    ELOG_CURR();
    return NULL;
  }
  return get_page_gui(page);
}

/*
 * @brief: 根据ID获取页面对象
 * @param id: 页面的ID
 * @return: 返回页面对象指针，若获取失败则返回NULL
 */
page_object *ldesk_sys_get_page_from_id(page_id id) {
  page_object *res;
  list_node *nd;
  each_node_for_linked(nd, LIST_HEAD_NODE(page_list), next) {
    if (nd == LIST_TAIL(page_list))
      break;

    res = (page_object *)NODE_VAL(nd);
    if (res->id == id)
      return res;
  }

  ELOG_CURR();
  return NULL;
}
