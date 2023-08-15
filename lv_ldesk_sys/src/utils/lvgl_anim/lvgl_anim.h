#ifndef __LVGL_ANIMI_H_
#define __LVGL_ANIMI_H_

#include "../utils.h"

#define ANIM_LINE_ADD(a, exec_cb, path_cb, ready_cb, time, back_time, delay,   \
                      var, begin, end, repeatcnt)                              \
  do {                                                                         \
    lv_anim_init(a);                                                           \
    lv_anim_set_exec_cb(a, exec_cb);                                           \
    if (path_cb != NULL)                                                       \
      lv_anim_set_path_cb(a, path_cb);                                         \
    if (ready_cb != NULL)                                                      \
      lv_anim_set_ready_cb(a, ready_cb);                                       \
    lv_anim_set_time(a, time);                                                 \
    lv_anim_set_playback_time(a, back_time);                                   \
    lv_anim_set_delay(a, delay);                                               \
    lv_anim_set_var(a, var);                                                   \
    lv_anim_set_values(a, begin, end);                                         \
    lv_anim_set_repeat_count(a, repeatcnt);                                    \
  } while (0);

static inline void set_angle(void *obj, int32_t v) {
  lv_arc_set_value((lv_obj_t *)obj, (int32_t)v);
}

static inline void set_img_angle(void *img, int32_t v) {
  lv_img_set_angle(img, v);
}

static inline void anim_opa_cb(void *var, int32_t v) {
  lv_obj_set_style_opa(var, v, LV_PART_MAIN);
}

static inline void anim_y_cb(void *var, int32_t v) { lv_obj_set_y(var, v); }

static inline void anim_x_cb(void *var, int32_t v) { lv_obj_set_x(var, v); }

#endif // !__LVGL_ANIMI_H_