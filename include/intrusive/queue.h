#ifndef INTRUSIVE_QUEUE_H
#define INTRUSIVE_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

typedef struct intrusive_queue_s intrusive_queue_t;
typedef struct intrusive_queue_node_s intrusive_queue_node_t;

struct intrusive_queue_s {
  size_t len;
  intrusive_queue_node_t *head;
  intrusive_queue_node_t *tail;
};

struct intrusive_queue_node_s {
  intrusive_queue_node_t *next;
};

void
intrusive_queue_init (intrusive_queue_t *queue);

bool
intrusive_queue_empty (const intrusive_queue_t *queue);

void
intrusive_queue_push (intrusive_queue_t *queue, intrusive_queue_node_t *node);

intrusive_queue_node_t *
intrusive_queue_peek (intrusive_queue_t *queue);

intrusive_queue_node_t *
intrusive_queue_pop (intrusive_queue_t *queue);

#define intrusive_queue_for_each(cursor, queue) \
  for ( \
    intrusive_queue_node_t *cursor = (queue)->head, *__next = cursor ? cursor->next : NULL; \
    cursor; \
    cursor = __next, __next = cursor ? cursor->next : NULL \
  )

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_QUEUE_H
