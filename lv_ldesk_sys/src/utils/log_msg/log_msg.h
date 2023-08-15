#ifndef __LOG_MSG_H_
#define __LOG_MSG_H_

#include "stdarg.h"
#include "stdio.h"

typedef enum {
  INFO,
  WARNING,
  DEBUG,
  ERROR,
} LOG_LEVEL;

#define PRINT_LOG(format)                                                      \
  va_list format##_args;                                                       \
  va_start(format##_args, format);                                             \
  vprintf(format, format##_args);                                              \
  va_end(format##_args);

#define DLOG_CURR()                                                            \
  dlog("debug file: %s function: %s line: %d\n", __FILE__, __FUNCTION__, __LINE__);

#define ELOG_CURR()                                                            \
  elog("error file: %s function: %s line: %d\n", __FILE__, __FUNCTION__, __LINE__);

#define WLOG_CURR()                                                            \
  wlog("warning file: %s function: %s line: %d\n", __FILE__, __FUNCTION__, __LINE__);

#define ILOG_CURR()                                                            \
  ilog("info file: %s function: %s line: %d\n", __FILE__, __FUNCTION__, __LINE__);

void log_msg(LOG_LEVEL lv, const char *format, ...);
void dlog(const char *format, ...);
void elog(const char *format, ...);
void wlog(const char *format, ...);
void ilog(const char *format, ...);

#endif // !__LOG_MSG_H_