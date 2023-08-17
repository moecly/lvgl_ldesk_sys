/*
 * @brief: LVGL动画处理模块头文件，提供动画相关的宏和函数
 * @file: lvgl_anim.h
 * @author: moecly
 */

#ifndef __LVGL_ANIM_H_
#define __LVGL_ANIM_H_

/**
 * @brief: 添加线性动画
 * @param a: 动画实例
 * @param exec_cb: 执行回调函数
 * @param path_cb: 路径回调函数
 * @param ready_cb: 完成回调函数
 * @param time: 动画时长
 * @param back_time: 回播时长
 * @param delay: 延迟
 * @param var: 动画变量
 * @param begin: 起始值
 * @param end: 结束值
 * @param repeatcnt: 重复次数
 */
#include "lvgl/lvgl.h"

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

/**
 * @brief: 设置对象的角度
 * @param obj: 目标对象
 * @param v: 角度值
 */
static inline void set_angle(void *obj, int32_t v) {
  lv_arc_set_value((lv_obj_t *)obj, (int32_t)v);
}

/**
 * @brief: 设置图像对象的角度
 * @param img: 图像对象
 * @param v: 角度值
 */
static inline void set_img_angle(void *img, int32_t v) {
  lv_img_set_angle(img, v);
}

/**
 * @brief: 动画执行回调函数，用于调整对象的透明度
 * @param var: 目标对象
 * @param v: 透明度值
 */
static inline void anim_opa_cb(void *var, int32_t v) {
  lv_obj_set_style_opa(var, v, LV_PART_MAIN);
}

/**
 * @brief: 动画执行回调函数，用于调整对象的y坐标
 * @param var: 目标对象
 * @param v: y坐标值
 */
static inline void anim_y_cb(void *var, int32_t v) { lv_obj_set_y(var, v); }

/**
 * @brief: 动画执行回调函数，用于调整对象的x坐标
 * @param var: 目标对象
 * @param v: x坐标值
 */
static inline void anim_x_cb(void *var, int32_t v) { lv_obj_set_x(var, v); }

#endif // !__LVGL_ANIM_H_
