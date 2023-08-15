#include "log_msg.h"

static LOG_LEVEL level = DEBUG;

void log_msg(LOG_LEVEL lv, const char *format, ...) {
  if (lv > level)
    return;
  PRINT_LOG(format);
}

void dlog(const char *format, ...) {
  if (level < DEBUG)
    return;
  PRINT_LOG(format);
}

void elog(const char *format, ...) {
  if (level < ERROR)
    return;
  PRINT_LOG(format);
}

void wlog(const char *format, ...) {
  if (level < WARNING)
    return;
  PRINT_LOG(format);
}

void ilog(const char *format, ...) {
  if (level < INFO)
    return;
  PRINT_LOG(format);
}
