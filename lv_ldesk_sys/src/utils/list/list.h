#ifndef __LIST_H_
#define __LIST_H_

#include "../utils.h"
#include "stdlib.h"
#include <stdint.h>

typedef struct list_node {
  struct list_node *prev;
  struct list_node *next;
  void *val;
} list_node;

typedef struct {
  list_node *head;
  list_node *tail;
  uint32_t len;
} pn_list;

#ifndef NULL
#define NULL (void *)0
#endif // !NULL

#ifndef SET_NODE
#define SET_NODE(src, dst, property) src->property = dst;
#endif // !SET_NODE

#ifndef SET_NODE_NEXT
#define SET_NODE_NEXT(src, dst) SET_NODE(src, dst, next)
#endif // !SET_NODE_NEXT

#ifndef SET_NODE_PREV
#define SET_NODE_PREV(src, dst) SET_NODE(src, dst, prev)
#endif // !SET_NODE_PREV

#ifndef SET_LIST_LEN
#define SET_LIST_LEN(list, length) list->len = length
#endif // !SET_LIST_LEN

#ifndef GET_LIST_LEN
#define GET_LIST_LEN(list) list->len
#endif // !GET_LIST_LEN

#ifndef LIST_HEAD
#define LIST_HEAD(list) (list->head)
#endif // !LIST_HEAD

#ifndef LIST_TAIL
#define LIST_TAIL(list) (list->tail)
#endif // !LIST_TAIL

#ifndef LIST_HEAD_NODE
#define LIST_HEAD_NODE(list) NODE_NEXT(LIST_HEAD(list))
#endif // !LIST_HEAD_NODE

#ifndef LIST_TAIL_NODE
#define LIST_TAIL_NODE(list) NODE_PREV(LIST_TAIL(list))
#endif // !LIST_HEAD_NODE

#ifndef NODE_PREV
#define NODE_PREV(nd) (nd->prev)
#endif // !NODE_PREV

#ifndef NODE_NEXT
#define NODE_NEXT(nd) (nd->next)
#endif // !NODE_PREV

#ifndef NODE_VAL
#define NODE_VAL(nd) (nd->val)
#endif // !NODE_VAL

#ifndef LIST_INIT
#define LIST_INIT(list)                                                        \
  list = MALLOC_FUNC(pn_list);                                                 \
  SET_LIST_LEN(list, 0);                                                       \
  LIST_TAIL(list) = MALLOC_FUNC(list_node);                                    \
  LIST_HEAD(list) = MALLOC_FUNC(list_node);                                    \
  SET_NODE_NEXT(LIST_HEAD(list), LIST_TAIL(list));                             \
  SET_NODE_PREV(LIST_TAIL(list), LIST_HEAD(list));                             \
  SET_NODE_PREV(LIST_HEAD(list), NULL);                                        \
  SET_NODE_NEXT(LIST_TAIL(list), NULL);
#endif // !LIST_INIT

#ifndef LIST_CREATE
#define LIST_CREATE(list) LIST_INIT(list)
#endif // !LIST_CREATE

#ifndef LIST_FREE
#define LIST_FREE(list)                                                        \
  list_node *list##_nd = LIST_HEAD(list);                                      \
  list_node *list##_tmp_nd = list##_nd;                                        \
  while (list##_nd) {                                                          \
    list##_tmp_nd = NODE_NEXT(list##_nd);                                      \
    FREE_FUNC(list##_nd);                                                      \
    list##_nd = list##_tmp_nd;                                                 \
  }                                                                            \
  FREE_FUNC(list)
#endif // !LIST_FREE

pn_list *list_new(void);
void list_free(pn_list *list);
void list_push_node_to_head(pn_list *list, list_node *nd);
void list_push_node_to_tail(pn_list *list, list_node *nd);
void list_push_to_head(pn_list *list, void *val);
void list_push_to_tail(pn_list *list, void *val);
void *list_get_node_from_index(pn_list *list, uint32_t idx);
void *list_get_val_from_index(pn_list *list, uint32_t idx);
uint32_t list_get_length(pn_list *list);

#endif // !__LIST_H_