#ifndef _FONT_SYMBOL_DEF_H
#define _FONT_SYMBOL_DEF_H

/**
 * @alarm_on                f0a2
 * @alarm_off               f1f7
 * @sound_on                f028
 * @sound_off               f026
 * @nes                     f11b
 * @power_off               f011
 * @arduboy                 f000
 * @calculator              f1ec
 * @calendar                f073
 * @setting                 f085
 * @about                   f05a
 * @gps                     f124
 * @book                    f02d
 *
 *
 *
 *
 * 0xf0a2,0xf1f7,0xf028,0xf026,0xf11b,0xf011,0xf000,0xf1ec,0xf073,0xf085,0xf05a,0xf124,0xf02d
 */

// #define SYMBOL_SETTING LV_SYMBOL_SETTINGS
// #define SYMBOL_GPS LV_SYMBOL_GPS
#define SYMBOL_WIFI LV_SYMBOL_WIFI

#define SYMBOL_ALARM_ON "\xef\x82\xa2"
#define SYMBOL_ALARM_OFF "\xef\x87\xb7"
#define SYMBOL_SOUND_ON "\xef\x80\xa8"
#define SYMBOL_SOUND_OFF "\xef\x80\xa6"
#define SYMBOL_NES "\xef\x84\x9b"
#define SYMBOL_POWER_OFF "\xef\x80\x91"
#define SYMBOL_ARDUBOY "\xef\x80\x80"
#define SYMBOL_CALC "\xef\x87\xac"
#define SYMBOL_CALENDAR "\xef\x81\xb3"
#define SYMBOL_SETTING "\xef\x82\x85"
#define SYMBOL_ABOUT "\xef\x81\x9a"
#define SYMBOL_GPS "\xef\x84\xa4"
#define SYMBOL_BOOK "\xef\x80\xad"

#endif