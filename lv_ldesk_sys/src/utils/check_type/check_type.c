#include "check_type.h"

int check_int_type(int *val) { return 0; }

int is_valid_val(data_type type, void *val) {
  if (type == INT_TYPE)
    return check_int_type(val);
  return -1;
}