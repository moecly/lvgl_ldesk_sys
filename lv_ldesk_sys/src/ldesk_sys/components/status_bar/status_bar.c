/*
 * @brief: 状态栏模块，用于管理状态栏显示和操作
 * @file: status_bar.c
 * @author: moecly
 */

#include "status_bar.h"
#include "lv_ldesk_sys/src/utils/log_msg/log_msg.h"
#include <string.h>

// 全局状态栏实例
static status_bar *bar;

// 全局状态栏元素
static bar_elem elem;

/*
 * @brief: 设置状态栏的状态
 * @param state: 状态栏状态
 */
static void bar_set_state(STATUS_BAR_STATE state) {
  // 在这里进行状态栏的状态设置操作
}

/*
 * @brief: 设置时间的状态
 * @param state: 时间状态
 */
static void time_set_state(STATUS_BAR_STATE state) { elem.time.state = state; }

/*
 * @brief: 设置状态栏或时间的状态
 * @param type: 状态栏类型
 * @param state: 状态
 */
static void status_bar_set_state(STATUS_BAR_TYPE type, STATUS_BAR_STATE state) {
  if (type == STATUS_BAR)
    bar_set_state(state);

  if (type == TIME)
    time_set_state(state);
}

/*
 * @brief: 设置状态栏的父对象
 * @param parent: 父对象
 */
static void status_bar_set_parent(lv_obj_t *parent) {
  lv_obj_set_parent(bar->bar, parent);
}

/*
 * @brief: 设置状态栏标题文本
 * @param title: 标题文本
 */
static void status_bar_set_title(const char *title) {
  lv_obj_t *obj = lv_obj_get_child(bar->bar, elem.title.id);
  lv_label_set_text(obj, title);
}

/*
 * @brief: 设置时间显示
 */
static void set_time(void) {
  lv_obj_t *obj = lv_obj_get_child(bar->bar, elem.time.id);
  int hour = get_hour();     // 获取小时
  int minute = get_minute(); // 获取分钟
  char hour_str[32];
  char minute_str[32];
  char symbol_str[32] = {' ', ':', ' '};
  char time_str[32];
  time_str[0] = '\0';
  int_num_to_str(hour_str, hour);     // 将小时转换为字符串
  int_num_to_str(minute_str, minute); // 将分钟转换为字符串

  // 格式化小时和分钟的显示
  if (hour < 10) {
    char tmp[32];
    char ch[2] = {'0', '\0'};
    strcpy(tmp, hour_str);
    hour_str[0] = '\0';
    strcpy(hour_str, ch);
    strcat(hour_str, tmp);
  }

  if (minute < 10) {
    char tmp[32];
    char ch[2] = {'0', '\0'};
    strcpy(tmp, minute_str);
    minute_str[0] = '\0';
    strcpy(minute_str, ch);
    strcat(minute_str, tmp);
  }

  strcat(hour_str, symbol_str);
  strcat(hour_str, minute_str);
  strcat(time_str, hour_str);
  lv_label_set_text(obj, time_str);
  dlog("time: %s\n", time_str);
}

/*
 * @brief: 定时器回调函数，更新时间显示
 * @param timer: 定时器实例
 */
static void status_bar_time_task(lv_timer_t *timer) {
  if (elem.time.state == STATUS_BAR_ENABLE)
    set_time();
}

/*
 * @brief: 初始化状态栏
 */
static void status_bar_init(void) {
  // 创建状态栏对象
  bar->bar = lv_obj_create(lv_scr_act());

  // 进行状态栏的样式设置
  lv_obj_set_size(bar->bar, GUI_WIDTH, STATUS_BAR_HEIGHT);
  lv_obj_set_style_border_width(bar->bar, 0, 0);
  lv_obj_set_style_pad_all(bar->bar, 0, 0);
  lv_obj_set_style_opa(bar->bar, LV_OPA_COVER, 0);
  lv_obj_set_style_border_side(
      bar->bar,
      LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT, 0);
  lv_obj_align(bar->bar, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_clear_flag(bar->bar, LV_OBJ_FLAG_SCROLLABLE);

  // 创建时间标签
  lv_obj_t *label_time = lv_label_create(bar->bar);
  elem.time.id = lv_obj_get_child_id(label_time);

  // 设置时间标签的样式
  lv_label_set_text(label_time, "07 : 00");
  lv_obj_set_size(label_time, LV_SIZE_CONTENT, STATUS_BAR_HEIGHT);
  lv_obj_set_style_text_font(label_time, &STATUS_BAR_TIME_TEXT_SIZE, 0);
  lv_obj_set_style_text_color(label_time, lv_palette_main(LV_PALETTE_BLUE), 0);
  lv_obj_align(label_time, LV_ALIGN_LEFT_MID, STATUS_BAR_TIME_X_SPACING,
               STATUS_BAR_TIME_y_SPACING);

  // 创建页面名称标签
  lv_obj_t *label_title = lv_label_create(bar->bar);
  elem.title.id = lv_obj_get_child_id(label_title);

  // 设置页面名称标签的样式
  lv_label_set_text(label_title, "");
  lv_obj_set_size(label_title, LV_SIZE_CONTENT, STATUS_BAR_HEIGHT);
  lv_obj_set_style_text_font(label_title, &STATUS_BAR_TITLE_TEXT_SIZE, 0);
  lv_obj_set_style_text_color(label_title, lv_palette_main(LV_PALETTE_BLUE), 0);
  lv_obj_align(label_title, LV_ALIGN_CENTER, STATUS_BAR_TITLE_X_SPACING,
               STATUS_BAR_TITLE_y_SPACING);

  // 创建定时器
  lv_timer_t *lv_timer = lv_timer_create(status_bar_time_task, 1200, NULL);
  UNUSED(lv_timer);
}

/*
 * @brief: 获取状态栏实例
 * @return: 状态栏实例指针
 */
status_bar *status_bar_instance(void) {
  if (bar)
    return bar;

  // 创建状态栏实例并进行初始化
  bar = MALLOC_FUNC(status_bar);
  bar->set_state = status_bar_set_state;
  bar->set_parent = status_bar_set_parent;
  bar->set_title = status_bar_set_title;
  status_bar_init();

  return bar;
}
