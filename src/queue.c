#include <stdbool.h>

#include "../include/intrusive/queue.h"

void
intrusive_queue_init (intrusive_queue_t *queue) {
  queue->len = 0;
  queue->head = NULL;
}

bool
intrusive_queue_empty (const intrusive_queue_t *list) {
  return list->len == 0;
}

void
intrusive_queue_push (intrusive_queue_t *queue, intrusive_queue_node_t *node) {
  if (!queue->head) {
    queue->head = node;
  } else {
    queue->tail->next = node;
  }

  queue->tail = node;

  node->next = NULL;

  queue->len++;
}

intrusive_queue_node_t *
intrusive_queue_peek (intrusive_queue_t *queue) {
  return queue->head;
}

intrusive_queue_node_t *
intrusive_queue_pop (intrusive_queue_t *queue) {
  intrusive_queue_node_t *node = queue->head;

  if (node == NULL) return NULL;

  if (!node->next) {
    queue->tail = NULL;
  }

  queue->head = node->next;

  node->next = NULL;

  queue->len--;

  return node;
}
