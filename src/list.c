#include <stdbool.h>

#include "../include/intrusive/list.h"

void
intrusive_list_init (intrusive_list_t *list) {
  list->len = 0;
  list->head = NULL;
  list->tail = NULL;
}

bool
intrusive_list_empty (const intrusive_list_t *list) {
  return list->len == 0;
}

size_t
intrusive_list_index_of (const intrusive_list_t *list, const intrusive_list_node_t *node) {
  if (list->tail == node) return list->len - 1;

  size_t i = 0;

  intrusive_list_for_each(next, list) {
    if (next == node) return i;

    i++;
  }

  return (size_t) -1;
}

intrusive_list_node_t *
intrusive_list_at (const intrusive_list_t *list, size_t index) {
  size_t i;

  if (index < list->len / 2) {
    i = 0;

    intrusive_list_for_each(node, list) {
      if (i == index) return node;

      i++;
    }
  } else {
    i = list->len - 1;

    intrusive_list_for_each_reverse(node, list) {
      if (i == index) return node;

      i--;
    }
  }

  return NULL;
}

static inline void
intrusive_list__cut (intrusive_list_t *list, intrusive_list_node_t *from, intrusive_list_node_t *to, size_t len) {
  if (from == NULL) return;

  if (list->head == from) {
    list->head = to->next;
  } else {
    from->prev->next = to->next;
  }

  if (list->tail == to) {
    list->tail = from->prev;
  } else {
    to->next->prev = from->prev;
  }

  from->prev = NULL;
  to->next = NULL;

  list->len -= len;
}

static inline void
intrusive_list__paste (intrusive_list_t *list, intrusive_list_node_t *left, intrusive_list_node_t *from, intrusive_list_node_t *to, intrusive_list_node_t *right, size_t len) {
  if (from == NULL) return;

  if (left) {
    left->next = from;
  } else {
    list->head = from;
  }

  if (right) {
    right->prev = to;
  } else {
    list->tail = to;
  }

  from->prev = left;
  to->next = right;

  list->len += len;
}

void
intrusive_list_prepend (intrusive_list_t *list, intrusive_list_node_t *node) {
  intrusive_list__paste(list, NULL, node, node, list->head, 1);
}

void
intrusive_list_append (intrusive_list_t *list, intrusive_list_node_t *node) {
  intrusive_list__paste(list, list->tail, node, node, NULL, 1);
}
