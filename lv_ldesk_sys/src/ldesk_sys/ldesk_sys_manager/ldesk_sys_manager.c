#include "ldesk_sys_manager.h"
#include "stdio.h"
#include <stdint.h>
#include <string.h>

static pn_list *page_list;

void ldesk_sys_init(void) { page_list = list_new(); }

void ldesk_sys_add_page(page_object *page) {
  list_push_to_tail(page_list, page);
}

int ldesk_sys_create_page(uint32_t id) {
  page_object *page = ldesk_sys_get_page_from_id(id);

  page->gui = lv_obj_create(NULL);
  lv_obj_set_size(page->gui, GUI_WIDTH, GUI_HEIGHT);
  lv_obj_set_style_bg_color(page->gui, lv_color_white(), LV_PART_MAIN);
  lv_obj_clear_flag(page->gui, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_center(page->gui);

  if (validate_pointer(page)) {
    ELOG_CURR();
    return -1;
  }
  return page->ops.init_handle(get_page_gui(page));
}

page_gui *get_page_gui(page_object *page) { return page->gui; }

page_gui *get_page_gui_from_id(uint32_t id) {
  page_object *page = ldesk_sys_get_page_from_id(id);
  if (validate_pointer(page)) {
    ELOG_CURR();
    return NULL;
  }
  return get_page_gui(page);
}

page_object *ldesk_sys_get_page_from_id(uint32_t id) {
  page_object *res;
  list_node *nd;
  each_node_for_linked(nd, LIST_HEAD_NODE(page_list), next) {
    res = (page_object *)NODE_VAL(nd);
    if (res->id == id)
      return res;
  }
  ELOG_CURR();
  return NULL;
}

void ldesk_sys_load_page(page_object *page) { lv_scr_load(page->gui); }

int ldesk_sys_load_page_from_id(uint32_t id) {
  page_object *page = ldesk_sys_get_page_from_id(id);
  if (validate_pointer(page)) {
    ELOG_CURR();
    return -1;
  }
  ldesk_sys_load_page(page);
  // set_status_bar_title_text(page->name);
  return 0;
}
