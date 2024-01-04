#include <stdbool.h>

#include "../include/intrusive/stack.h"

void
intrusive_stack_init (intrusive_stack_t *stack) {
  stack->len = 0;
  stack->tail = NULL;
}

bool
intrusive_stack_empty (const intrusive_stack_t *list) {
  return list->len == 0;
}

void
intrusive_stack_push (intrusive_stack_t *stack, intrusive_stack_node_t *node) {
  node->prev = stack->tail;

  stack->tail = node;

  stack->len++;
}

intrusive_stack_node_t *
intrusive_stack_peek (intrusive_stack_t *stack) {
  return stack->tail;
}

intrusive_stack_node_t *
intrusive_stack_pop (intrusive_stack_t *stack) {
  intrusive_stack_node_t *node = stack->tail;

  if (node == NULL) return NULL;

  stack->tail = node->prev;

  node->prev = NULL;

  stack->len--;

  return node;
}
