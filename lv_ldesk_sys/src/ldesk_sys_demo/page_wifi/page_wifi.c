#include "page_wifi.h"
#include "lv_ldesk_sys/src/utils/log_msg/log_msg.h"
#include "src/core/lv_obj_pos.h"
#include "src/misc/lv_color.h"
#include "src/widgets/lv_label.h"

static lv_obj_t *page_self_gui;
static char *PAGE_NAME = "wifi";

/**
 * @brief 页面初始化函数
 * @param gui 页面的GUI对象
 * @return 返回初始化结果，0 表示成功，其他值表示失败
 */
int page_wifi_init(lv_obj_t *gui, void *data) {
  page_self_gui = gui;
  lv_obj_set_style_bg_color(page_self_gui, lv_color_white(), LV_PART_MAIN);

  lv_obj_t *label = lv_label_create(page_self_gui);
  lv_label_set_text(label, "hello");
  lv_obj_center(label);

  // 设置状态栏
#ifdef USE_STATUS_BAR
  // 设置状态栏为启用
  // 设置状态栏的父对象、时间显示等
  set_status_bar_parent(page_self_gui);
  DLOG_CURR();
  lv_anim_del_all();
  set_status_bar(STATUS_BAR_ENABLE);

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

int page_wifi_exit(lv_obj_t *gui, void *data) {
  // 设置状态栏
#ifdef USE_STATUS_BAR
  // 设置状态栏为禁用
  // 设置状态栏的父对象、时间显示等
  set_status_bar(STATUS_BAR_DISABLE);

#ifdef SHOW_STATUS_BAR_TIME
  set_status_bar_time(STATUS_BAR_DISABLE);
#endif // !SHOW_STATUS_BAR_TIME

#ifdef SHOW_STATUS_BAR_TITLE
  set_status_bar_title(STATUS_BAR_DISABLE);
  set_status_bar_title_text("");
#endif // !SHOW_STATUS_BAR_TITLE

#endif // SHOW_STATUS_BAR_TIME
  
  return 0;
}
