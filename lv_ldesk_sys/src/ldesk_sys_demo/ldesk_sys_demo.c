#include "ldesk_sys_demo.h"

void ldesk_sys_demo_init(void) {
  ldesk_sys_init();
  ldesk_sys_add_page(&page_apps);
  ldesk_sys_create_page(PAGE_APPS);
  ldesk_sys_load_page_from_id(PAGE_APPS);

/* set status bar */
#ifdef USE_STATUS_BAR
  set_status_bar(STATUS_BAR_ENABLE);

#ifdef SHOW_STATUS_BAR_TIME
  set_status_bar_time(STATUS_BAR_ENABLE);
#endif // !SHOW_STATUS_BAR_TIME

#ifdef SHOW_STATUS_BAR_TITLE
  set_status_bar_title(STATUS_BAR_ENABLE);
#endif // !SHOW_STATUS_BAR_TITLE

#endif // SHOW_STATUS_BAR_TIME
}
