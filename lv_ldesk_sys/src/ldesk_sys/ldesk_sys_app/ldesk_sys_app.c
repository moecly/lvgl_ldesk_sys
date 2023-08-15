#include "ldesk_sys_app.h"
#include "lv_ldesk_sys/src/utils/list/list.h"
#include <stdint.h>

static pn_list *apps_list;

void ldesk_sys_app_init(void) { apps_list = list_new(); }

void add_app_item(app_item *app) { list_push_to_tail(apps_list, app); }

app_item *get_app_from_index(uint32_t index) {
  return (app_item *)list_get_val_from_index(apps_list, index);
}

uint32_t get_apps_length(void) { return list_get_length(apps_list); }
