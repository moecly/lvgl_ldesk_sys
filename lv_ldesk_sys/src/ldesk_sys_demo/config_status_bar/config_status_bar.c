#include "config_status_bar.h"

void status_bar_init(page_gui *page, char *name) {
  /* 设置状态栏 */
#ifdef USE_STATUS_BAR
  /*
   * 设置状态栏的父对象、时间显示等
   * 设置状态栏为启用
   */
  set_status_bar_parent(page);
  set_status_bar(STATUS_BAR_ENABLE);

#ifdef SHOW_STATUS_BAR_TIME
  set_status_bar_time(STATUS_BAR_ENABLE);
#endif // !SHOW_STATUS_BAR_TIME

#ifdef SHOW_STATUS_BAR_TITLE
  set_status_bar_title(STATUS_BAR_ENABLE);
  set_status_bar_title_text(name);
#endif // !SHOW_STATUS_BAR_TITLE

#ifdef SHOW_STATUS_BAR_RET_BTN
  set_status_bar_ret_btn(STATUS_BAR_ENABLE);
#endif // !SHOW_STATUS_BAR_RET_BTN

#endif // SHOW_STATUS_BAR_TIME
}

void status_bar_exit(void) {
  /* 设置状态栏 */
#ifdef USE_STATUS_BAR
  /*
   * 设置状态栏为禁用
   */
  set_status_bar(STATUS_BAR_DISABLE);

#ifdef SHOW_STATUS_BAR_TIME
  set_status_bar_time(STATUS_BAR_DISABLE);
#endif // !SHOW_STATUS_BAR_TIME

#ifdef SHOW_STATUS_BAR_TITLE
  set_status_bar_title(STATUS_BAR_DISABLE);
#endif // !SHOW_STATUS_BAR_TITLE

#ifdef SHOW_STATUS_BAR_RET_BTN
  set_status_bar_ret_btn(STATUS_BAR_DISABLE);
#endif // !SHOW_STATUS_BAR_RET_BTN

#endif // SHOW_STATUS_BAR_TIME
}
