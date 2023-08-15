#include "ldesk_sys_page_opr.h"
#include "lv_ldesk_sys/src/ldesk_sys/components/status_bar/status_bar.h"

void set_status_bar_state(int type, int state) {
  status_bar_instance()->set_state(type, state);
}

void set_status_bar(int state) { set_status_bar_state(STATUS_BAR, state); }

void set_status_bar_parent(lv_obj_t *parent) {
  status_bar_instance()->set_parent(parent);
}

void set_status_bar_time(int state) { set_status_bar_state(TIME, state); }

void set_status_bar_title(int state) { set_status_bar_state(TITLE, state); }

void set_status_bar_title_text(char *title) {
  status_bar_instance()->set_title(title);
}
