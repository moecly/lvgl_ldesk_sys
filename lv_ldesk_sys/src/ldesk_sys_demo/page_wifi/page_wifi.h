#ifndef __PAGE_WIFI_INIT_H_
#define __PAGE_WIFI_INIT_H_

#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager/ldesk_sys_manager.h"
#include "lv_ldesk_sys_conf.h"
#include "lvgl/lvgl.h"

int page_wifi_init(page_gui *gui, void *data);
int page_wifi_exit(page_gui *gui, void *data);

#endif // !__PAGE_WIFI_INIT_H_