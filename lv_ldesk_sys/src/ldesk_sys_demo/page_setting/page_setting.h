#ifndef __PAGE_SETTING_H_
#define __PAGE_SETTING_H_

#include "lv_ldesk_sys/src/ldesk_sys/ldesk_sys_manager/ldesk_sys_manager.h"
#include "lvgl/lvgl.h"

int page_setting_init(page_gui *gui, void *data);
int page_setting_exit(page_gui *gui, void *data);

#endif // !__PAGE_SETTING_H_