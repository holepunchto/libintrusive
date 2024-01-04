#include <stdbool.h>
#include <stddef.h>

#include "../include/intrusive/ring.h"

void
intrusive_ring_init (intrusive_ring_t *ring) {
  ring->next = ring;
  ring->prev = ring;
}

bool
intrusive_ring_empty (intrusive_ring_t *ring) {
  return ring == ring->next;
}

intrusive_ring_t *
intrusive_ring_link (intrusive_ring_t *left, intrusive_ring_t *right) {
  intrusive_ring_t *next = left->next;
  intrusive_ring_t *prev = right->prev;

  left->next = right;
  right->prev = left;
  next->prev = prev;
  prev->next = next;

  return next;
}

intrusive_ring_t *
intrusive_ring_move (intrusive_ring_t *ring, int count) {
  if (count < 0) {
    for (int i = 0; i > count; i--) {
      ring = ring->prev;
    }
  } else if (count > 0) {
    for (int i = 0; i < count; i++) {
      ring = ring->next;
    }
  }

  return ring;
}

intrusive_ring_t *
intrusive_ring_unlink (intrusive_ring_t *ring, int count) {
  if (count <= 0) return NULL;

  return intrusive_ring_link(ring, intrusive_ring_move(ring, count + 1));
}

intrusive_ring_t *
intrusive_ring_remove (intrusive_ring_t *ring) {
  intrusive_ring_t *next = intrusive_ring_link(ring, ring);

  if (next == ring) return NULL;

  return next;
}
