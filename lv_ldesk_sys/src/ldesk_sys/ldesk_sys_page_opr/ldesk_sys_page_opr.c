/*
 * @brief: 页面操作相关函数的实现文件
 * @file: ldesk_sys_page_opr.c
 * @author: moecly
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

/*
 * @brief: 根据页面 ID 切换显示不同页面，并执行相关操作
 */
int ldesk_sys_disp_page_from_id(uint32_t id, void *create_params,
                                void *del_params,
                                lv_scr_load_anim_t load_anim) {
  int ret;
  static uint32_t old_id = -1;

  if (old_id == id)
    return 0;

  ret = ldesk_sys_create_page_from_id(id, (void *)&create_params);
  if (ret) {
    ELOG_CURR();
    return -1;
  }

  ret = ldesk_sys_load_page_from_id(id, load_anim);
  if (ret) {
    ELOG_CURR();
    return -1;
  }

  if (old_id != -1)
    ldesk_sys_exit_page_from_id(old_id, (void *)&del_params);

  old_id = id;
  return 0;
}

/*
 * @brief: 退出页面对象以及相关资源
 */
int ldesk_sys_exit_page(page_object *page, void *data) {
  int ret;

  /* 调用页面初始化句柄函数 */
  if (validate_pointer(page)) {
    ELOG_CURR();
    return -1;
  }

  /* 调用页面操作中的退出句柄函数，执行页面特定的退出操作 */
  ret = page->ops.exit_handle(get_page_gui(page), data);
  if (ret) {
    ELOG_CURR();
    return -1;
  }

  return 0;
}

/*
 * 根据页面 ID 退出页面对象及相关资源
 */
int ldesk_sys_exit_page_from_id(uint32_t id, void *data) {
  page_object *page = ldesk_sys_get_page_from_id(id);
  dlog("del page id = %d\n", id);
  return ldesk_sys_exit_page(page, data);
}

/*
 * @brief: 根据ID创建一个页面
 * @param id: 页面的ID
 * @return: 返回页面创建状态，成功返回0，失败返回-1
 */
int ldesk_sys_create_page_from_id(uint32_t id, void *data) {
  page_object *page = ldesk_sys_get_page_from_id(id);
  dlog("create page id = %d\n", id);
  return ldesk_sys_create_page(page, data);
}

/*
 * @brief: 加载页面到屏幕
 * @param page: 页面对象指针
 */
void ldesk_sys_load_page(page_object *page, lv_scr_load_anim_t load_anim) {
  lv_scr_load_anim(page->gui, load_anim, PAGE_SWITCH_TIME, 0, 1);
}

/*
 * @brief: 根据ID加载页面到屏幕
 * @param id: 页面的ID
 * @return: 返回页面加载状态，成功返回0，失败返回-1
 */
int ldesk_sys_load_page_from_id(uint32_t id, lv_scr_load_anim_t load_anim) {
  page_object *page = ldesk_sys_get_page_from_id(id);
  if (validate_pointer(page)) {
    ELOG_CURR();
    return -1;
  }
  ldesk_sys_load_page(page, load_anim);
  return 0;
}

/*
 * 创建一个页面对象，并初始化页面的GUI部分和数据
 */
int ldesk_sys_create_page(page_object *page, void *data) {
  /* 调用页面初始化句柄函数 */
  if (validate_pointer(page)) {
    /* 记录错误日志，说明是在哪里发生了指针无效的情况 */
    ELOG_CURR();
    /* 返回错误代码 */
    return -1;
  }

  /* 创建页面GUI对象 */
  page->gui = lv_obj_create(NULL);

  /*
   * 设置gui属性
   */
  lv_obj_set_size(page->gui, GUI_WIDTH, GUI_HEIGHT);
  lv_obj_set_style_bg_color(page->gui, lv_color_white(), LV_PART_MAIN);
  lv_obj_clear_flag(page->gui, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_center(page->gui);

  /* 调用页面的初始化句柄函数来进行页面特定的初始化 */
  return page->ops.init_handle(get_page_gui(page), NULL);
}
