/*
 * @brief: 状态栏模块头文件，定义了状态栏相关结构和函数接口
 * @file: status_bar.h
 */

#ifndef __STATUS_BAR_H
#define __STATUS_BAR_H

#include "../../ldesk_sys.h"
#include <stdint.h>

// 状态栏类型枚举
typedef enum {
  STATUS_BAR, // 状态栏
  TIME,       // 时间
  TITLE       // 页面名称
} STATUS_BAR_TYPE;

// 状态栏状态枚举
typedef enum {
  STATUS_BAR_DISABLE, // 状态栏禁用
  STATUS_BAR_ENABLE,  // 状态栏启用
} STATUS_BAR_STATE;

// 状态栏项目结构
typedef struct {
  uint8_t id;    // 项目ID
  uint8_t state; // 项目状态
} bar_item;

// 状态栏元素结构
typedef struct {
  bar_item status_bar; // 状态栏项目
  bar_item time;       // 时间项目
  bar_item title;      // 页面名称项目
} bar_elem;

// 状态栏实例结构
typedef struct {
  lv_obj_t *bar;   // 状态栏对象
  uint8_t is_show; // 是否显示状态栏
  void (*set_state)(STATUS_BAR_TYPE type,
                    STATUS_BAR_STATE state); // 设置状态栏或项目的状态
  void (*set_parent)(lv_obj_t *parent);      // 设置状态栏的父对象
  void (*set_title)(const char *title);      // 设置状态栏的标题
} status_bar;

/*
 * @brief: 获取状态栏实例
 * @return: 状态栏实例指针
 */
status_bar *status_bar_instance(void);

#endif // !__STATUS_BAR_H
