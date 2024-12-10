#ifndef INTRUSIVE_STACK_H
#define INTRUSIVE_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#define intrusive_stack_for_each(cursor, stack) \
  for ( \
    intrusive_stack_node_t *cursor = (stack)->head, *__next = cursor ? cursor->next : NULL; \
    cursor; \
    cursor = __next, __next = cursor ? cursor->next : NULL \
  )

typedef struct intrusive_stack_s intrusive_stack_t;
typedef struct intrusive_stack_node_s intrusive_stack_node_t;

struct intrusive_stack_s {
  size_t len;
  intrusive_stack_node_t *tail;
};

struct intrusive_stack_node_s {
  intrusive_stack_node_t *prev;
};

static inline void
intrusive_stack_init (intrusive_stack_t *stack) {
  stack->len = 0;
  stack->tail = NULL;
}

static inline bool
intrusive_stack_empty (const intrusive_stack_t *list) {
  return list->len == 0;
}

static inline void
intrusive_stack_push (intrusive_stack_t *stack, intrusive_stack_node_t *node) {
  node->prev = stack->tail;

  stack->tail = node;

  stack->len++;
}

static inline intrusive_stack_node_t *
intrusive_stack_peek (intrusive_stack_t *stack) {
  return stack->tail;
}

static inline intrusive_stack_node_t *
intrusive_stack_pop (intrusive_stack_t *stack) {
  intrusive_stack_node_t *node = stack->tail;

  if (node == NULL) return NULL;

  stack->tail = node->prev;

  node->prev = NULL;

  stack->len--;

  return node;
}

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_STACK_H
