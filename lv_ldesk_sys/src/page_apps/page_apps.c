#include "page_apps.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_page_opr.h"
#include "lv_ldesk_sys/src/utils/common/common.h"
#include "lv_ldesk_sys/src/utils/log_msg/log_msg.h"
#include "src/core/lv_event.h"
#include "src/core/lv_obj.h"
#include "src/core/lv_obj_pos.h"
#include "src/core/lv_obj_scroll.h"
#include "src/core/lv_obj_tree.h"
#include "src/font/lv_font.h"
#include "src/misc/lv_anim.h"
#include "src/widgets/lv_label.h"
#include "stdio.h"
#include <stdint.h>

static page_gui *page_self_gui;
static lv_obj_t *cont_row_app;
static lv_obj_t *label_name;
static char *PAGE_NAME = "apps";
static uint32_t app_obj_size = 0;

static const char *app_names[] = {"Book",       "Arduboy",  "NES",     "GPS",
                                  "Calculator", "Calendar", "Setting", "About"};

static void icon_add_shadow(lv_obj_t *obj) {
  lv_obj_set_style_shadow_width(obj, APPS_SHADOW_WIDTH, LV_PART_MAIN);
  lv_obj_set_style_shadow_color(obj, lv_palette_main(LV_PALETTE_BLUE),
                                LV_PART_MAIN);
}

static void icon_remove_shadow(lv_obj_t *obj) {
  lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);
  lv_obj_set_style_shadow_color(obj, lv_color_white(), LV_PART_MAIN);
}

static void switch_app(uint32_t id) {
  static uint32_t old_id = -1;
  static int old_y = -1;
  static int new_y = -1;
  lv_obj_t *parent = cont_row_app;
  lv_obj_t *old_child = lv_obj_get_child(parent, old_id);
  lv_obj_t *child = lv_obj_get_child(parent, id);
  uint32_t to_x = 0;

  if (old_id == -1) {
    old_y = lv_obj_get_y(child);
    new_y = old_y - APPS_APP_SELECT_NEW_Y;

    lv_obj_t *id0_obj = lv_obj_get_child(cont_row_app, 0);
    lv_obj_align(id0_obj, LV_ALIGN_TOP_LEFT, 0, old_y);
  }

  if (id > 1)
    to_x = (id - 1) * (app_obj_size + APPS_SPACING);
  else
    to_x = 0;

  lv_obj_scroll_to_x(parent, to_x, LV_ANIM_ON);
  lv_label_set_text(label_name, app_names[id]);

  /* open app */
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

static void event_scroll_end_handler(lv_event_t *e) {}

static void event_key_handler(lv_event_t *e) {}

static void event_clicked_handler(lv_event_t *e) {
  lv_obj_t *target = e->current_target;
  uint32_t id = lv_obj_get_child_id(target);
  switch_app(id);
}

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

int page_apps_init(page_gui *gui) {
  page_self_gui = gui;

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
  lv_obj_set_style_pad_all(cont_row_app, APPS_SPACING, 0);
  lv_obj_center(cont_row_app);

  uint32_t i;
  app_obj_size =
      (GUI_WIDTH - ((APPS_ROW_NUM + 1) * APPS_SPACING)) / APPS_ROW_NUM;
  uint32_t len = sizeof(app_names) / sizeof(app_names[0]);
  lv_obj_t *old_obj = NULL;

  for (i = 0; i < len; i++) {
    lv_obj_t *obj;
    lv_obj_t *label;

    obj = lv_obj_create(cont_row_app);
    lv_group_add_obj(lv_group_get_default(), obj);
    lv_obj_add_event_cb(obj, event_handler, LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb(obj, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(obj, app_obj_size, app_obj_size);
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

  /* set focus */
  lv_group_focus_obj(cont_row_app);

  switch_app(0);

/* set status bar */
#ifdef USE_STATUS_BAR
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