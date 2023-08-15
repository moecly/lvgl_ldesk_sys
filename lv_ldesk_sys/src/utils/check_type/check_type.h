#ifndef __CHECK_TYPE_H_
#define __CHECK_TYPE_H_

#include "../utils.h"

typedef enum {
  INT_TYPE,
} data_type;

int is_valid_val(data_type type, void *val);
int check_int_type(int *val);

#endif // !__CHECK_TYPE_H_