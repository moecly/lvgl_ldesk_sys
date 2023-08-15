#ifndef __LDESK_SYS_PAGE_OPR_H_
#define __LDESK_SYS_PAGE_OPR_H_

#include "ldesk_sys.h"

void set_status_bar(int state);
void set_status_bar_state(int type, int state);
void set_status_bar_time(int state);
void set_status_bar_title(int state);
void set_status_bar_title_text(char *title);
void set_status_bar_parent(lv_obj_t *parent);

#endif // !__LDESK_SYS_PAGE_OPR_H_
