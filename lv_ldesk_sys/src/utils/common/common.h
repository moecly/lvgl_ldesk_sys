#ifndef __COMMON_H_
#define __COMMON_H_

#include "stdio.h"

#ifndef MALLOC_FUNC
#define MALLOC_FUNC(property) (property *)malloc(sizeof(property))
#endif // !MALLOC_FUNC

#ifndef FREE_FUNC
#define FREE_FUNC free
#endif // !FREE_FUNC

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif // !UNUSED

#ifndef ARRAY_LEN
#define ARRAY_LEN(x) (sizeof(x) / sizeof(x[0]))
#endif // !ARRAY_LEN

#define each_node_for_linked(node, linked, property)                           \
  for (node = linked; node != NULL; node = node->property)

#define each_node_for_array(node, array)                                       \
  size_t array##_length = sizeof(array) / sizeof(array[0]);                    \
  for (size_t array##_index = 0, node = &array[array##_index];                 \
       array##_index < array##_length; array##_index++)

// 封装的函数，用于验证指针是否有效
int validate_pointer(void *ptr);

#endif // !__COMMON_H_