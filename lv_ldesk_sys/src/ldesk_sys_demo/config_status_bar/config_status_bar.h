#ifndef __CONFIG_STATUS_BAR_H_
#define __CONFIG_STATUS_BAR_H_

#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager/ldesk_sys_manager.h"
#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_page_opr/ldesk_sys_page_opr.h"
#include "lv_ldesk_sys_conf.h"

void status_bar_init(page_gui *page, char *name);
void status_bar_exit(void);

#endif // !__CONFIG_STATUS_BAR_H_