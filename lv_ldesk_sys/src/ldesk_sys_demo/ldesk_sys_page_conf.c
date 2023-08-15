#include "ldesk_sys_page_conf.h"

page_object page_apps = {
    .id = PAGE_APPS,
    .name = "apps",
    .ops.init_handle = PAGE_INIT_DEF(apps),
};

