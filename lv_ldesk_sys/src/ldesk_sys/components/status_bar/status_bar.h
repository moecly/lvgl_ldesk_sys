#ifndef __STATUS_BAR_H
#define __STATUS_BAR_H

#include "../../ldesk_sys.h"
#include <stdint.h>

typedef enum { STATUS_BAR, TIME, TITLE } STATUS_BAR_TYPE;

typedef enum {
  STATUS_BAR_DISABLE,
  STATUS_BAR_ENABLE,
} STATUS_BAR_STATE;

typedef struct {
  uint8_t id;
  uint8_t state;
} bar_item;

typedef struct {
  bar_item status_bar;
  bar_item time;
  bar_item title;
} bar_elem;

typedef struct {
  lv_obj_t *bar;
  uint8_t is_show;
  void (*set_state)(STATUS_BAR_TYPE type,
                    STATUS_BAR_STATE state); // ENABLE ; DISABLE
  void (*set_parent)(lv_obj_t *parent);
  void (*set_title)(const char *title);
} status_bar;

status_bar *status_bar_instance(void);

#endif // !__STATUS_BAR_H