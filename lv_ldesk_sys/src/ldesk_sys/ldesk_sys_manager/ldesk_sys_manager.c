/*
 * @brief: 桌面系统管理模块，用于管理页面对象和操作
 * @file: ldesk_sys_manager.c
 * @author: moecly
 */

#include "ldesk_sys_manager.h"
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
 * @brief: 根据ID创建一个页面
 * @param id: 页面的ID
 * @return: 返回页面创建状态，成功返回0，失败返回-1
 */
int ldesk_sys_create_page(uint32_t id) {
  page_object *page = ldesk_sys_get_page_from_id(id);

  // 创建页面GUI对象
  page->gui = lv_obj_create(NULL);
  lv_obj_set_size(page->gui, GUI_WIDTH, GUI_HEIGHT);
  lv_obj_set_style_bg_color(page->gui, lv_color_white(), LV_PART_MAIN);
  lv_obj_clear_flag(page->gui, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_center(page->gui);

  // 调用页面初始化句柄函数
  if (validate_pointer(page)) {
    ELOG_CURR();
    return -1;
  }
  return page->ops.init_handle(get_page_gui(page));
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
page_gui *get_page_gui_from_id(uint32_t id) {
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
page_object *ldesk_sys_get_page_from_id(uint32_t id) {
  page_object *res;
  list_node *nd;
  each_node_for_linked(nd, LIST_HEAD_NODE(page_list), next) {
    res = (page_object *)NODE_VAL(nd);
    if (res->id == id)
      return res;
  }
  ELOG_CURR();
  return NULL;
}

/*
 * @brief: 加载页面到屏幕
 * @param page: 页面对象指针
 */
void ldesk_sys_load_page(page_object *page) { lv_scr_load(page->gui); }

/*
 * @brief: 根据ID加载页面到屏幕
 * @param id: 页面的ID
 * @return: 返回页面加载状态，成功返回0，失败返回-1
 */
int ldesk_sys_load_page_from_id(uint32_t id) {
  page_object *page = ldesk_sys_get_page_from_id(id);
  if (validate_pointer(page)) {
    ELOG_CURR();
    return -1;
  }
  ldesk_sys_load_page(page);
  return 0;
}
