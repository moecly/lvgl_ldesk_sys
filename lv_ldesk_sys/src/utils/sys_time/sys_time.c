#include "sys_time.h"

static time_t currentTime;
static struct tm *localTime;

int get_hour(void) {
  // 获取当前系统时间
  currentTime = time(NULL);

  // 将当前时间转换为本地时间结构体
  localTime = localtime(&currentTime);

  // 获取小时
  int res = localTime->tm_hour;
  return res;
}

int get_minute(void) {
  // 获取当前系统时间
  currentTime = time(NULL);

  // 将当前时间转换为本地时间结构体
  localTime = localtime(&currentTime);

  // 获取分钟
  int res = localTime->tm_min;
  return res;
}
