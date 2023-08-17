#include "page_wifi.h"
#include "lv_ldesk_sys/src/ldesk_sys/components/status_bar/status_bar.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_page_opr/ldesk_sys_page_opr.h"
#include "lv_ldesk_sys/src/ldesk_sys_demo/config_status_bar/config_status_bar.h"
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
int page_wifi_init(page_gui *gui, void *data) {
  page_self_gui = gui;
  lv_obj_set_style_bg_color(page_self_gui, lv_color_white(), LV_PART_MAIN);

  lv_obj_t *label = lv_label_create(page_self_gui);
  lv_label_set_text(label, "wifi");
  lv_obj_center(label);

  status_bar_init(page_self_gui, PAGE_NAME);
  return 0;
}

int page_wifi_exit(page_gui *gui, void *data) {
  status_bar_exit();
  return 0;
}
