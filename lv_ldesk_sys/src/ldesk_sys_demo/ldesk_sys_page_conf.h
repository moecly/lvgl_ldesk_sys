#ifndef __LDESK_SYS_PAGE_CONF_H_
#define __LDESK_SYS_PAGE_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_ldesk_sys.h"

#define PAGE_INIT_DEF(TAG) page_##TAG##_init

enum PAGE_ID {
  PAGE_NULL = -1,
  PAGE_APPS,
};

extern struct page_object page_apps;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__LDESK_SYS_PAGE_CONF_H_