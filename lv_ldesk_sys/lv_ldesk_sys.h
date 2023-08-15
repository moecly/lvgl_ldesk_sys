/**
 * @file lv_examples.h
 *
 */

#ifndef __LV_LDESK_SYS_H_
#define __LV_LDESK_SYS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "../lvgl/lvgl.h"
#endif

#if defined(LV_LDESK_SYS_CONF_PATH)
#define __LV_TO_STR_AUX(x) #x
#define __LV_TO_STR(x) __LV_TO_STR_AUX(x)
#include __LV_TO_STR(LV_LDESK_SYS_CONF_PATH)
#undef __LV_TO_STR_AUX
#undef __LV_TO_STR
#elif defined(LV_LDESK_SYS_CONF_INCLUDE_SIMPLE)
#include "lv_ldesk_sys_conf.h"
#else
#include "../lv_ldesk_sys_conf.h"
#endif

#include "src/ldesk_sys/ldesk_sys.h"
#include "src/ldesk_sys_demo/ldesk_sys_demo.h"
#include "src/utils/utils.h"

/*********************
 *      DEFINES
 *********************/
/*Test  lvgl version*/
#if LV_VERSION_CHECK(8, 0, 0) == 0
#error "lv_demo: Wrong lvgl version"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_H*/
