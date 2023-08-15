#include "ldesk_sys_demo.h"
#include <stdint.h>

static app_item apps[] = {
    {.name = "Book", .icon = "Book"},
    {.name = "Arduboy", .icon = "Arduboy"},
    {.name = "NES", .icon = "NES"},
    {.name = "Setting", .icon = "Setting"},
    {.name = "Calculator", .icon = "Calculator"},
    {.name = "Calendar", .icon = "Calendar"},
    {.name = "Arduboy", .icon = "Arduboy"},
};

static void apps_init(void) {
  ldesk_sys_app_init();
  uint32_t len = ARRAY_LEN(apps);
  uint32_t i = 0;
  for (; i < len; i++) {
    add_app_item(&apps[i]);
  }
}

void ldesk_sys_demo_init(void) {
  ldesk_sys_init();
  ldesk_sys_add_page(&page_apps);
  apps_init();
  ldesk_sys_create_page(PAGE_APPS);
  ldesk_sys_load_page_from_id(PAGE_APPS);
}
