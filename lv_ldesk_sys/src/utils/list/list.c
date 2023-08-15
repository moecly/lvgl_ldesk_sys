#include "list.h"

pn_list *list_new(void) {
  pn_list *ret;
  LIST_CREATE(ret);
  return ret;
}

void list_free(pn_list *list) { LIST_FREE(list); }

void list_push_node_to_head(pn_list *list, list_node *nd) {
  SET_NODE_NEXT(nd, NODE_NEXT(LIST_HEAD(list)));
  SET_NODE_PREV(nd, LIST_HEAD(list));
  SET_NODE_PREV(NODE_NEXT(LIST_HEAD(list)), nd);
  SET_NODE_NEXT(LIST_HEAD(list), nd);
  SET_LIST_LEN(list, GET_LIST_LEN(list) + 1);
}

void list_push_node_to_tail(pn_list *list, list_node *nd) {
  SET_NODE_NEXT(nd, LIST_TAIL(list));
  SET_NODE_PREV(nd, NODE_PREV(LIST_TAIL(list)));
  SET_NODE_NEXT(NODE_PREV(LIST_TAIL(list)), nd);
  SET_NODE_PREV(LIST_TAIL(list), nd);
  SET_LIST_LEN(list, GET_LIST_LEN(list) + 1);
}

void list_push_to_head(pn_list *list, void *val) {
  list_node *nd = MALLOC_FUNC(list_node);
  nd->val = (void *)val;
  list_push_node_to_head(list, nd);
}

void list_push_to_tail(pn_list *list, void *val) {
  list_node *nd = MALLOC_FUNC(list_node);
  nd->val = (void *)val;
  list_push_node_to_tail(list, nd);
}