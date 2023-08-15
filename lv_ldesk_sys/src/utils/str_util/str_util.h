#ifndef __STR_UTIL_H_
#define __STR_UTIL_H_

#include "../utils.h"
#include "stdio.h"
#include "string.h"

typedef struct {
} str_ops;

typedef struct {
  char *val;
  str_ops ops;
} str_objs;

void int_num_to_str(char *str, int num);

#endif // !__STR_UTIL_H_