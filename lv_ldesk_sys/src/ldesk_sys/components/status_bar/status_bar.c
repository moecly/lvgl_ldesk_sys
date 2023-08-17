/*
 * @brief: 状态栏模块，用于管理状态栏显示和操作
 * @file: status_bar.c
 * @author: moecly
 */

#include "status_bar.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager/ldesk_sys_manager.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_page_opr/ldesk_sys_page_opr.h"
#include "lv_ldesk_sys/src/ldesk_sys_demo/ldesk_sys_page_conf/ldesk_sys_page_conf.h"
#include "lv_ldesk_sys/src/utils/utils.h"
#include "src/core/lv_event.h"
#include <string.h>

/* 全局状态栏实例 */
static status_bar *bar;

/* 全局状态栏元素 */
static bar_elem elem;

static page_id target_page_id = PAGE_NULL;

static void exit_ready_cb(struct _lv_anim_t *anim) {
  if (bar->exit_cb)
    bar->exit_cb(anim);
}

/*
 * @brief: 函数用于显示或隐藏状态栏，并使用动画实现平滑的过渡效果
 * @params is_show:
 *      STATUS_BAR_ENABLE显示
 *      STATUS_BAR_DISABLE不显示
 */
static void set_show(lv_obj_t *obj, int is_show) {
  /* 创建一个 LVGL 动画对象 */
  lv_anim_t anim;

  /* 如果需要显示状态栏，且当前状态为隐藏状态 */
  if (is_show == STATUS_BAR_ENABLE &&
      elem.status_bar.state == STATUS_BAR_DISABLE) {
    /* 添加一个动画：从隐藏状态移动到显示状态 */
    ANIM_LINE_ADD(&anim, anim_y_cb, lv_anim_path_overshoot, NULL,
                  STATUS_BAR_ANIM_DURATION, 0, STATUS_BAR_ANIM_DELAY, obj,
                  STATUS_BAR_START_LOCA, 0, 0);
    lv_anim_start(&anim); /* 启动动画 */
  }

  /* 如果需要隐藏状态栏，且当前状态为显示状态 */
  if (is_show == STATUS_BAR_DISABLE &&
      elem.status_bar.state == STATUS_BAR_ENABLE) {
    /* 添加一个动画：从显示状态移动到隐藏状态 */
    ANIM_LINE_ADD(&anim, anim_y_cb, lv_anim_path_overshoot, exit_ready_cb,
                  STATUS_BAR_ANIM_DURATION, 0, STATUS_BAR_ANIM_DELAY, obj, 0,
                  STATUS_BAR_START_LOCA, 0);
    /* 启动动画 */
    lv_anim_start(&anim);
  }
}

/*
 * @brief: 设置状态栏的状态
 * @param state: 状态栏状态
 */
static void bar_set_state(STATUS_BAR_STATE state) {
  /* 在这里进行状态栏的状态设置操作 */
  set_show(bar->bar, state);
  elem.status_bar.state = state;
}

/*
 * @brief: 设置时间的状态
 * @param state: 时间状态
 */
static void time_set_state(STATUS_BAR_STATE state) {
  lv_obj_t *obj = bar->bar;
  lv_obj_t *time = lv_obj_get_child(obj, elem.time.id);
  set_show(time, state);
  elem.time.state = state;
}

static void title_set_state(STATUS_BAR_STATE state) {
  lv_obj_t *obj = bar->bar;
  lv_obj_t *title = lv_obj_get_child(obj, elem.title.id);
  set_show(title, state);
  elem.title.state = state;
}

static void ret_btn_set_state(STATUS_BAR_STATE state) {
  lv_obj_t *obj = bar->bar;
  lv_obj_t *ret_btn = lv_obj_get_child(obj, elem.ret_btn.id);
  set_show(ret_btn, state);
  elem.ret_btn.state = state;
}

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

  if (type == TITLE)
    title_set_state(state);

  if (type == RET_BTN)
    ret_btn_set_state(state);
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
  int hour = get_hour();     /* 获取小时 */
  int minute = get_minute(); /* 获取分钟 */
  char hour_str[32];
  char minute_str[32];
  char symbol_str[32] = {' ', ':', ' '};
  char time_str[32];
  time_str[0] = '\0';
  int_num_to_str(hour_str, hour);     /* 将小时转换为字符串 */
  int_num_to_str(minute_str, minute); /* 将分钟转换为字符串 */

  /*
   * 格式化小时和分钟的显示
   */
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
 * @brief 设置状态栏文本颜色
 * @param value: 颜色值
 */
static void status_bar_set_text_color(lv_color_t value) {
  lv_obj_t *obj;
  lv_obj_t *parent = bar->bar;

  /* set time font color */
  obj = lv_obj_get_child(parent, elem.time.id);
  lv_obj_set_style_text_color(obj, value, LV_PART_MAIN);

  /* set title font color */
  obj = lv_obj_get_child(parent, elem.title.id);
  lv_obj_set_style_text_color(obj, value, LV_PART_MAIN);

  /* set ret btn label color */
  lv_obj_t *rer_btn = lv_obj_get_child(parent, elem.ret_btn.id);
  obj = lv_obj_get_child(rer_btn, elem.ret_label.id);
  lv_obj_set_style_text_color(obj, value, LV_PART_MAIN);
}

/*
 * @brief 设置状态栏背景颜色
 * @param value: 颜色值
 */
static void status_bar_set_bg_color(lv_color_t value) {
  lv_obj_t *obj = bar->bar;
  lv_obj_set_style_bg_color(obj, value, LV_PART_MAIN);

  lv_obj_t *ret_btn = lv_obj_get_child(obj, elem.ret_btn.id);
  lv_obj_set_style_bg_color(ret_btn, value, LV_PART_MAIN);
}

static void event_cb(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED && target_page_id != PAGE_NULL) {
    ldesk_sys_switch_page_from_id(target_page_id, PAGE_SWITCH_ANIM);
  }
}

/*
 * @brief: 初始化状态栏
 */
static void status_bar_init(void) {
  /* 创建状态栏对象 */
  bar->bar = lv_obj_create(lv_scr_act());

  /*
   *进行状态栏的样式设置
   */
  elem.status_bar.state = STATUS_BAR_ENABLE;
  lv_obj_set_size(bar->bar, GUI_WIDTH, STATUS_BAR_HEIGHT);
  lv_obj_set_style_border_width(bar->bar, 0, 0);
  lv_obj_set_style_pad_all(bar->bar, 0, 0);
  lv_obj_set_style_opa(bar->bar, LV_OPA_COVER, 0);
  lv_obj_set_style_border_side(
      bar->bar,
      LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT, 0);
  lv_obj_align(bar->bar, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_clear_flag(bar->bar, LV_OBJ_FLAG_SCROLLABLE);

  /* 创建时间标签 */
  lv_obj_t *label_time = lv_label_create(bar->bar);
  elem.time.id = lv_obj_get_child_id(label_time);

  /*
   * 设置时间标签的样式
   */
  elem.time.state = STATUS_BAR_ENABLE;
  lv_label_set_text(label_time, "07 : 00");
  lv_obj_set_size(label_time, LV_SIZE_CONTENT, STATUS_BAR_HEIGHT);
  lv_obj_set_style_text_font(label_time, &STATUS_BAR_TIME_TEXT_SIZE, 0);
  lv_obj_set_style_text_color(label_time, STATUS_BAR_TEXT_COLOR, 0);
  lv_obj_align(label_time, LV_ALIGN_LEFT_MID, STATUS_BAR_TIME_X_SPACING,
               STATUS_BAR_TIME_Y_SPACING);

  /* 创建页面名称标签 */
  lv_obj_t *label_title = lv_label_create(bar->bar);
  elem.title.id = lv_obj_get_child_id(label_title);

  /*
   * 设置页面名称标签的样式
   */
  elem.title.state = STATUS_BAR_ENABLE;
  lv_label_set_text(label_title, "");
  lv_obj_set_size(label_title, LV_SIZE_CONTENT, STATUS_BAR_HEIGHT);
  lv_obj_set_style_text_font(label_title, &STATUS_BAR_TITLE_TEXT_SIZE, 0);
  lv_obj_set_style_text_color(label_title, STATUS_BAR_TEXT_COLOR, 0);
  lv_obj_align(label_title, LV_ALIGN_CENTER, STATUS_BAR_TITLE_X_SPACING,
               STATUS_BAR_TITLE_Y_SPACING);

  /* 创建页面名称标签 */
  lv_obj_t *ret_btn = lv_btn_create(bar->bar);
  lv_obj_t *ret_label = lv_label_create(ret_btn);
  elem.ret_btn.id = lv_obj_get_child_id(ret_btn);
  elem.ret_label.id = lv_obj_get_child_id(ret_label);
  lv_obj_set_size(ret_btn, LV_SIZE_CONTENT, STATUS_BAR_HEIGHT);
  lv_obj_add_event_cb(ret_btn, event_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_align(ret_btn, LV_ALIGN_RIGHT_MID, STATUS_BAR_RET_BTN_X_SPACING,
               STATUS_BAR_RET_BTN_Y_SPACING);
  lv_label_set_text(ret_label, "back");
  lv_obj_center(ret_label);
  lv_obj_set_style_text_font(ret_label, &STATUS_BAR_RET_BTN_TEXT_SIZE, 0);
  lv_obj_set_style_text_color(ret_label, STATUS_BAR_TEXT_COLOR, 0);

  /* 设置字体颜色和背景颜色 */
  status_bar_set_text_color(STATUS_BAR_TEXT_COLOR);
  status_bar_set_bg_color(STATUS_BAR_BG_COLOR);

  /*
   * 创建定时器
   */
  lv_timer_t *lv_timer = lv_timer_create(status_bar_time_task, 1200, NULL);
  UNUSED(lv_timer);
}

void status_bar_set_target_page_id(page_id id) { target_page_id = id; }

/*
 * @brief: 获取状态栏实例
 * @return: 状态栏实例指针
 */
status_bar *status_bar_instance(void) {
  if (bar)
    return bar;

  /*
   * 创建状态栏实例并进行初始化
   */
  bar = MALLOC_FUNC(status_bar);
  bar->set_state = status_bar_set_state;
  bar->set_parent = status_bar_set_parent;
  bar->set_title = status_bar_set_title;
  bar->set_bg_color = status_bar_set_bg_color;
  bar->set_text_color = status_bar_set_text_color;
  bar->exit_cb = NULL;
  status_bar_init();
  status_bar_set_state(STATUS_BAR, STATUS_BAR_DISABLE);
  status_bar_set_state(TIME, STATUS_BAR_DISABLE);
  status_bar_set_state(TITLE, STATUS_BAR_DISABLE);
  status_bar_set_state(RET_BTN, STATUS_BAR_DISABLE);

  return bar;
}
