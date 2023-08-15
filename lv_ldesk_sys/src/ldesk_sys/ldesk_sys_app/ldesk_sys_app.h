#ifndef __LDESK_SYS_APP_H_
#define __LDESK_SYS_APP_H_

#include "../ldesk_sys.h"

typedef struct {
  char *name;
  char *icon;
} app_item;

void add_app_item(app_item *app);
void ldesk_sys_app_init(void);
app_item *get_app_from_index(uint32_t index);
uint32_t get_apps_length(void);

#endif // !__LDESK_SYS_APP_H_