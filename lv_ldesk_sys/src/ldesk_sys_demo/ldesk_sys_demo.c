#include "ldesk_sys_demo.h"

void ldesk_sys_demo_init(void) {
  ldesk_sys_init();
  ldesk_sys_add_page(&page_apps);
  ldesk_sys_create_page(PAGE_APPS);
  ldesk_sys_load_page_from_id(PAGE_APPS);


}
