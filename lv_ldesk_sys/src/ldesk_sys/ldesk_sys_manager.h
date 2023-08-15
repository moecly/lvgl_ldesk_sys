#ifndef __LDESK_SYS_MANAGER_H_
#define __LDESK_SYS_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ldesk_sys.h"

#ifndef page_gui
#define page_gui lv_obj_t
#endif // !page_gui

typedef struct {
  int (*init_handle)(page_gui *gui);
} page_ops;

typedef struct page_object {
  uint32_t id;
  char *name;
  page_gui *gui;
  page_ops ops;
} page_object;

void ldesk_sys_add_page(page_object *page);
void ldesk_sys_init(void);
int ldesk_sys_create_page(uint32_t id);
page_object *ldesk_sys_get_page_from_id(uint32_t id);
page_gui *get_page_gui_from_id(uint32_t id);
page_gui *get_page_gui(page_object *page);
void ldesk_sys_load_page(page_object *page);
int ldesk_sys_load_page_from_id(uint32_t id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__LDESK_SYS_MANAGER_H_