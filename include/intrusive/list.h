#ifndef INTRUSIVE_LIST_H
#define INTRUSIVE_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

typedef struct intrusive_list_s intrusive_list_t;
typedef struct intrusive_list_node_s intrusive_list_node_t;

struct intrusive_list_s {
  size_t len;
  intrusive_list_node_t *head;
  intrusive_list_node_t *tail;
};

struct intrusive_list_node_s {
  intrusive_list_node_t *prev;
  intrusive_list_node_t *next;
};

void
intrusive_list_init (intrusive_list_t *list);

bool
intrusive_list_empty (const intrusive_list_t *list);

size_t
intrusive_list_index_of (const intrusive_list_t *list, const intrusive_list_node_t *node);

intrusive_list_node_t *
intrusive_list_at (const intrusive_list_t *list, size_t index);

void
intrusive_list_prepend (intrusive_list_t *list, intrusive_list_node_t *node);

void
intrusive_list_append (intrusive_list_t *list, intrusive_list_node_t *node);

#define intrusive_list_for_each(cursor, list) \
  for ( \
    intrusive_list_node_t *cursor = (list)->head; \
    cursor != NULL; \
    cursor = cursor->next \
  )

#define intrusive_list_for_each_reverse(cursor, list) \
  for ( \
    intrusive_list_node_t *cursor = (list)->tail; \
    cursor != NULL; \
    cursor = cursor->prev \
  )

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_LIST_H
