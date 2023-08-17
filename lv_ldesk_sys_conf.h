/**
 * @file lv_demo_conf.h
 * Configuration file for v8.0.0
 *
 */
/*
 * COPY THIS FILE AS lv_demo_conf.h
 */

#if 1 /*Set it to "1" to enable the content*/

#ifndef LV_LDESK_SYS_CONF_H
#define LV_LDESK_SYS_CONF_H

/*******************
 * GENERAL SETTING
 *******************/
#define LV_EX_PRINTF 1 /*Enable printf-ing data in demoes and examples*/
#define LV_EX_KEYBOARD                                                         \
  1 /*Add PC keyboard support to some examples (`lv_drivers` repository is     \
       required)*/
#define LV_EX_MOUSEWHEEL                                                       \
  1 /*Add 'encoder' (mouse wheel) support to some examples (`lv_drivers`       \
       repository is required)*/

/*********************
 * LDESK SYS USAGE
 *********************/
#define LDESK_SYS_DEMO 1

#define GUI_WIDTH 280
#define GUI_HEIGHT 240
#define PAGE_SWITCH_TIME 500

#if LDESK_SYS_DEMO

/* apps */
#define APPS_ROW_NUM 3
#define APPS_BACKGROUND_COLOR lv_color_white()
/* apps icon */
#define APPS_APP_SPACING 10
#define APPS_APP_SELECT_NEW_Y 15
#define APPS_ICON_BG_COLOR lv_color_black()
#define APPS_ICON_FONT_COLOR lv_palette_main(LV_PALETTE_DEEP_PURPLE)
#define APPS_APP_SHADOW_COLOR lv_palette_main(LV_PALETTE_BLUE)
#define APPS_APP_SHADOW_WIDTH 30
#define APPS_APP_ICON_ANIM_DURATION 250
/* app label */
#define APPS_APP_NAME_HEIGHT 80
#define APPS_APP_NAME_BOTTOM_SPACING 10
#define APPS_APP_NAME_FONT_SIZE lv_font_montserrat_22
#define APPS_APP_NAME_FONT_COLOR lv_palette_main(LV_PALETTE_BLUE)
#define APPS_APP_NAME_START_LOCA 25
#define APPS_APP_NAME_ANIM_DURATION 500
#define APPS_APP_NAME_ANIM_DELAY 300

/* status bar */
#define USE_STATUS_BAR 1
/* status bar configs */
#define STATUS_BAR_HEIGHT 30
#define STATUS_BAR_START_LOCA -32
#define STATUS_BAR_ANIM_DURATION 500
#define STATUS_BAR_ANIM_DELAY 500
#define STATUS_BAR_TEXT_COLOR lv_color_black()
#define STATUS_BAR_BG_COLOR lv_color_white()
/* status bar time configs */
#define SHOW_STATUS_BAR_TIME 1
#define STATUS_BAR_TIME_TEXT_SIZE lv_font_montserrat_22
#define STATUS_BAR_TIME_X_SPACING 5
#define STATUS_BAR_TIME_y_SPACING 3
/* status bar title config */
#define SHOW_STATUS_BAR_TITLE 1
#define STATUS_BAR_TITLE_TEXT_SIZE lv_font_montserrat_22
#define STATUS_BAR_TITLE_X_SPACING 0
#define STATUS_BAR_TITLE_y_SPACING 3

#endif

#endif /*LV_EX_CONF_H */

#endif /*End of "Content enable"*/
