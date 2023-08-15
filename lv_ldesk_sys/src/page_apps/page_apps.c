#include "page_apps.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_page_opr.h"
#include "lv_ldesk_sys/src/utils/common/common.h"
#include "lv_ldesk_sys/src/utils/log_msg/log_msg.h"
#include "src/core/lv_event.h"
#include "src/font/lv_font.h"
#include "stdio.h"
#include <stdint.h>

static page_gui *page_self_gui;
static lv_obj_t *cont_row_app;
static lv_obj_t *label_name;

static const char *app_names[] = {"Book",       "Arduboy",  "NES",     "GPS",
                                  "Calculator", "Calendar", "Setting", "About"};

static void event_scroller_end_handler(lv_event_t *e) {
  // uint32_t x;
}

static void event_key_handler(lv_event_t *e) {}

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  dlog("apps code = %d\n", code);

  if (code == LV_EVENT_SCROLL_END)
    event_scroller_end_handler(e);

  if (code == LV_EVENT_KEY)
    event_key_handler(e);
}

int page_apps_init(page_gui *gui) {
  page_self_gui = gui;

  cont_row_app = lv_obj_create(page_self_gui);
  lv_group_add_obj(lv_group_get_default(), cont_row_app);
  lv_obj_add_event_cb(cont_row_app, event_handler, LV_EVENT_KEY, NULL);
  lv_obj_add_event_cb(cont_row_app, event_handler, LV_EVENT_SCROLL_END, NULL);
  lv_obj_set_size(cont_row_app, GUI_WIDTH,
                  GUI_HEIGHT - APPS_APP_NAME_HEIGHT - STATUS_BAR_HEIGHT);
  lv_obj_set_style_border_width(cont_row_app, 0, 0);
  lv_obj_set_style_bg_opa(cont_row_app, LV_OPA_0,
                          LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(cont_row_app, LV_OPA_0,
                          LV_PART_SCROLLBAR | LV_STATE_SCROLLED);
  lv_obj_set_style_pad_all(cont_row_app, APPS_SPACING, 0);
  lv_obj_center(cont_row_app);

  uint32_t i;
  uint32_t obj_size =
      (GUI_WIDTH - ((APPS_ROW_NUM + 1) * APPS_SPACING)) / APPS_ROW_NUM;
  uint32_t len = sizeof(app_names) / sizeof(app_names[0]);
  lv_obj_t *old_obj = NULL;

  for (i = 0; i < len; i++) {
    lv_obj_t *obj;
    lv_obj_t *label;

    obj = lv_obj_create(cont_row_app);
    lv_group_add_obj(lv_group_get_default(), obj);
    lv_obj_add_event_cb(obj, event_handler, LV_EVENT_KEY, NULL);
    lv_obj_set_size(obj, obj_size, obj_size);
    lv_obj_set_style_radius(obj, LV_PCT(50), LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    if (old_obj)
      lv_obj_align_to(obj, old_obj, LV_ALIGN_OUT_RIGHT_TOP, APPS_SPACING, 0);
    else
      lv_obj_align(obj, LV_ALIGN_LEFT_MID, 0, 0);

    label = lv_label_create(obj);
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_DEEP_PURPLE),
                                LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &APPS_ICON_FONT_SIZE, LV_PART_MAIN);
    lv_label_set_text(label, app_names[i]);
    lv_obj_center(label);
    old_obj = obj;
  }

  label_name = lv_label_create(page_self_gui);
  lv_label_set_text(label_name, app_names[0]);
  lv_obj_set_style_text_color(label_name, lv_palette_main(LV_PALETTE_BLUE),
                              LV_PART_MAIN);
  lv_obj_set_style_text_font(label_name, &APPS_APP_NAME_FONT_SIZE,
                             LV_PART_MAIN);
  lv_obj_align(label_name, LV_ALIGN_BOTTOM_MID, 0,
               -APPS_APP_NAME_BOTTOM_SPACING);

  return 0;
}