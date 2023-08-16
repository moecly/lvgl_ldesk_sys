/*
 * @brief: 通用工具模块，包含各个子模块的头文件引用
 * @file: utils.h
 * @author: moecly
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_ldesk_sys.h"

#include "common/common.h"       // 引用通用功能模块
#include "list/list.h"           // 引用链表数据结构模块
#include "log_msg/log_msg.h"     // 引用日志消息模块
#include "lvgl_anim/lvgl_anim.h" // 引用LVGL动画模块
#include "str_util/str_util.h"   // 引用字符串处理工具模块
#include "sys_time/sys_time.h"   // 引用系统时间模块

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // !__UTILS_H_
