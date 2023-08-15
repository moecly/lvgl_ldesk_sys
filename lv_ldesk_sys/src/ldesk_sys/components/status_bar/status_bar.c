#include "status_bar.h"
#include "lv_ldesk_sys/src/utils/log_msg/log_msg.h"
#include <string.h>

static status_bar *bar;

static bar_elem elem;

static void bar_set_state(STATUS_BAR_STATE state) {}

static void time_set_state(STATUS_BAR_STATE state) { elem.time.state = state; }

static void status_bar_set_state(STATUS_BAR_TYPE type, STATUS_BAR_STATE state) {
  if (type == STATUS_BAR)
    bar_set_state(state);

  if (type == TIME)
    time_set_state(state);
}

static void status_bar_set_parent(lv_obj_t *parent) {
  lv_obj_set_parent(bar->bar, parent);
}

static void status_bar_set_title(const char *title) {
  lv_obj_t *obj = lv_obj_get_child(bar->bar, elem.title.id);
  lv_label_set_text(obj, title);
}

static void set_time(void) {
  lv_obj_t *obj = lv_obj_get_child(bar->bar, elem.time.id);
  int hour = get_hour();
  int minute = get_minute();
  char hour_str[32];
  char minute_str[32];
  char symbol_str[32] = {' ', ':', ' '};
  char time_str[32];
  time_str[0] = '\0';
  int_num_to_str(hour_str, hour);
  int_num_to_str(minute_str, minute);

  if (hour < 10) {
    char tmp[32];
    char ch[2] = {'0', '\0'};
    strcpy(tmp, hour_str);
    hour_str[0] = '\0';
    strcpy(hour_str, ch);
    DLOG_CURR();
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

static void status_bar_time_task(lv_timer_t *timer) {
  if (elem.time.state == STATUS_BAR_ENABLE)
    set_time();
}

static void status_bar_init(void) {
  // 状态栏
  bar->bar = lv_obj_create(lv_scr_act());
  lv_obj_set_size(bar->bar, GUI_WIDTH, STATUS_BAR_HEIGHT);
  lv_obj_set_style_border_width(bar->bar, 0, 0);
  lv_obj_set_style_pad_all(bar->bar, 0, 0);
  lv_obj_set_style_opa(bar->bar, LV_OPA_COVER, 0);
  lv_obj_set_style_border_side(
      bar->bar,
      LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT, 0);
  lv_obj_align(bar->bar, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_clear_flag(bar->bar, LV_OBJ_FLAG_SCROLLABLE);

  // 时间
  lv_obj_t *label_time = lv_label_create(bar->bar);
  elem.time.id = lv_obj_get_child_id(label_time);
  lv_label_set_text(label_time, "07 : 00");
  lv_obj_set_size(label_time, LV_SIZE_CONTENT, STATUS_BAR_HEIGHT);
  lv_obj_set_style_text_font(label_time, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_color(label_time, lv_palette_main(LV_PALETTE_BLUE), 0);
  lv_obj_align(label_time, LV_ALIGN_LEFT_MID, STATUS_BAR_TIME_X_SPACING,
               STATUS_BAR_TIME_y_SPACING);

  // 页面名称
  lv_obj_t *label_title = lv_label_create(bar->bar);
  elem.title.id = lv_obj_get_child_id(label_title);
  lv_label_set_text(label_title, "");
  lv_obj_set_size(label_title, LV_SIZE_CONTENT, STATUS_BAR_HEIGHT);
  lv_obj_set_style_text_font(label_title, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_color(label_title, lv_palette_main(LV_PALETTE_BLUE), 0);
  lv_obj_align(label_title, LV_ALIGN_CENTER, STATUS_BAR_TITLE_X_SPACING,
               STATUS_BAR_TITLE_y_SPACING);

  lv_timer_t *lv_timer = lv_timer_create(status_bar_time_task, 1200, NULL);
  UNUSED(lv_timer);
}

status_bar *status_bar_instance(void) {
  if (bar)
    return bar;

  bar = MALLOC_FUNC(status_bar);
  bar->set_state = status_bar_set_state;
  bar->set_parent = status_bar_set_parent;
  bar->set_title = status_bar_set_title;
  status_bar_init();

  return bar;
}
