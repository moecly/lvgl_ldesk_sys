/*
 * @brief: 应用页面实现文件，定义应用页面的初始化和事件处理函数
 * @file: ldesk_sys_page_apps.c
 * @author: moecly
 */

#include "ldesk_sys_page_apps.h"
#include "stdio.h"
#include <stdint.h>

// 页面GUI对象
static page_gui *page_self_gui;

// 应用列表行容器
static lv_obj_t *cont_row_app;

// 应用名称标签
static lv_obj_t *label_name;

// 页面名称
static char *PAGE_NAME = "apps";

// 应用图标大小
static uint32_t app_obj_size = 0;

/**
 * @brief 添加阴影效果到图标
 * @param obj 要添加阴影效果的对象
 */
static void icon_add_shadow(lv_obj_t *obj) {
  lv_obj_set_style_shadow_width(obj, APPS_APP_SHADOW_WIDTH, LV_PART_MAIN);
  lv_obj_set_style_shadow_color(obj, lv_palette_main(LV_PALETTE_BLUE),
                                LV_PART_MAIN);
}

/**
 * @brief 移除图标的阴影效果
 * @param obj 要移除阴影效果的对象
 */
static void icon_remove_shadow(lv_obj_t *obj) {
  lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);
  lv_obj_set_style_shadow_color(obj, lv_color_white(), LV_PART_MAIN);
}

/**
 * @brief 切换应用
 * @param id 要切换的应用ID
 */
static void switch_app(uint32_t id) {
  static uint32_t old_id = -1;
  static int old_y = -1;
  static int new_y = -1;
  lv_obj_t *parent = cont_row_app;
  lv_obj_t *old_child = lv_obj_get_child(parent, old_id);
  lv_obj_t *child = lv_obj_get_child(parent, id);
  app_item *app = get_app_from_index(id);
  uint32_t to_x = 0;

  if (old_id == -1) {
    old_y = lv_obj_get_y(child);
    new_y = old_y - APPS_APP_SELECT_NEW_Y;

    lv_obj_t *id0_obj = lv_obj_get_child(cont_row_app, 0);
    lv_obj_align(id0_obj, LV_ALIGN_TOP_LEFT, 0, old_y);
  }

  if (id > 1)
    to_x = (id - 1) * (app_obj_size + APPS_APP_SPACING);
  else
    to_x = 0;

  lv_obj_scroll_to_x(parent, to_x, LV_ANIM_ON);
  lv_label_set_text(label_name, app->name);

  // 打开应用
  if (old_id == id)
    return;

  icon_remove_shadow(old_child);
  icon_add_shadow(child);

  dlog("old_y = %d\n, new_y = %d\n", old_y, new_y);
  lv_anim_t anim0;
  ANIM_LINE_ADD(&anim0, anim_y_cb, lv_anim_path_overshoot, NULL, 250, 0, 50,
                child, old_y, new_y, 0);
  lv_anim_start(&anim0);

  lv_anim_t anim1;
  ANIM_LINE_ADD(&anim1, anim_y_cb, lv_anim_path_overshoot, NULL, 250, 0, 0,
                lv_obj_get_child(parent, old_id), new_y, old_y, 0);
  lv_anim_start(&anim1);

  old_id = id;
}

/**
 * @brief 滚动事件处理函数
 * @param e 事件对象
 */
static void event_scroll_end_handler(lv_event_t *e) {}

/**
 * @brief 按键事件处理函数
 * @param e 事件对象
 */
static void event_key_handler(lv_event_t *e) {}

/**
 * @brief 点击事件处理函数
 * @param e 事件对象
 */
static void event_clicked_handler(lv_event_t *e) {
  lv_obj_t *target = e->current_target;
  uint32_t id = lv_obj_get_child_id(target);
  switch_app(id);
}

/**
 * @brief 通用事件处理函数
 * @param e 事件对象
 */
static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  dlog("%s: code = %d\n", PAGE_NAME, code);

  if (code == LV_EVENT_SCROLL_END)
    event_scroll_end_handler(e);

  if (code == LV_EVENT_KEY)
    event_key_handler(e);

  if (code == LV_EVENT_CLICKED)
    event_clicked_handler(e);
}

/**
 * @brief 页面初始化函数
 * @param gui 页面的GUI对象
 * @return 返回初始化结果，0 表示成功，其他值表示失败
 */
int page_apps_init(page_gui *gui) {
  page_self_gui = gui;

  // 创建应用列表行容器
  // 设置行容器的样式、事件处理等
  cont_row_app = lv_obj_create(page_self_gui);
  lv_group_add_obj(lv_group_get_default(), cont_row_app);
  // lv_obj_add_event_cb(cont_row_app, event_handler, LV_EVENT_KEY, NULL);
  lv_obj_add_event_cb(cont_row_app, event_handler, LV_EVENT_SCROLL_END, NULL);
  lv_obj_set_size(cont_row_app, GUI_WIDTH,
                  GUI_HEIGHT - APPS_APP_NAME_HEIGHT - STATUS_BAR_HEIGHT);
  lv_obj_set_style_border_width(cont_row_app, 0, 0);
  lv_obj_set_style_bg_opa(cont_row_app, LV_OPA_0,
                          LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(cont_row_app, LV_OPA_0,
                          LV_PART_SCROLLBAR | LV_STATE_SCROLLED);
  lv_obj_set_style_pad_all(cont_row_app, APPS_APP_SPACING, 0);
  lv_obj_center(cont_row_app);

  // 创建应用图标和名称标签
  // 设置图标和名称标签的样式、事件处理等
  uint32_t i;
  app_obj_size =
      (GUI_WIDTH - ((APPS_ROW_NUM + 1) * APPS_APP_SPACING)) / APPS_ROW_NUM;
  uint32_t len = get_apps_length();
  lv_obj_t *old_obj = NULL;

  for (i = 0; i < len; i++) {
    lv_obj_t *obj;
    lv_obj_t *label;
    app_item *app = get_app_from_index(i);

    obj = lv_obj_create(cont_row_app);
    lv_group_add_obj(lv_group_get_default(), obj);
    lv_obj_add_event_cb(obj, event_handler, LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb(obj, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(obj, app_obj_size, app_obj_size);
    lv_obj_set_style_radius(obj, LV_PCT(50), LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    if (old_obj)
      lv_obj_align_to(obj, old_obj, LV_ALIGN_OUT_RIGHT_TOP, APPS_APP_SPACING,
                      0);
    else
      lv_obj_align(obj, LV_ALIGN_LEFT_MID, 0, 0);

    label = lv_label_create(obj);
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_DEEP_PURPLE),
                                LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &APPS_ICON_FONT_SIZE, LV_PART_MAIN);
    lv_label_set_text(label, app->icon);
    lv_obj_center(label);
    old_obj = obj;
  }

  app_item *app = get_app_from_index(0);
  label_name = lv_label_create(page_self_gui);
  lv_label_set_text(label_name, app->name);
  lv_obj_set_style_text_color(label_name, lv_palette_main(LV_PALETTE_BLUE),
                              LV_PART_MAIN);
  lv_obj_set_style_text_font(label_name, &APPS_APP_NAME_FONT_SIZE,
                             LV_PART_MAIN);
  lv_obj_align(label_name, LV_ALIGN_BOTTOM_MID, 0,
               -APPS_APP_NAME_BOTTOM_SPACING);

  /* set focus */
  lv_group_focus_obj(cont_row_app);

  // 切换到第一个应用
  switch_app(0);

  // 设置状态栏
#ifdef USE_STATUS_BAR
  // 设置状态栏为启用
  // 设置状态栏的父对象、时间显示等
  set_status_bar(STATUS_BAR_ENABLE);
  set_status_bar_parent(page_self_gui);

#ifdef SHOW_STATUS_BAR_TIME
  set_status_bar_time(STATUS_BAR_ENABLE);
#endif // !SHOW_STATUS_BAR_TIME

#ifdef SHOW_STATUS_BAR_TITLE
  set_status_bar_title(STATUS_BAR_ENABLE);
  set_status_bar_title_text(PAGE_NAME);
#endif // !SHOW_STATUS_BAR_TITLE

#endif // SHOW_STATUS_BAR_TIME

  return 0;
}
