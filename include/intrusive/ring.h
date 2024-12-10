#ifndef INTRUSIVE_RING_H
#define INTRUSIVE_RING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#define intrusive_ring_for_each(cursor, ring) \
  for ( \
    intrusive_ring_t *__start = (ring), *cursor = __start, *__next = cursor ? cursor->next : NULL; \
    cursor; \
    cursor = __next == __start ? NULL : __next, __next = cursor ? cursor->next : NULL \
  )

#define intrusive_ring_for_each_reverse(cursor, ring) \
  for ( \
    intrusive_ring_t *__start = (ring), *cursor = __start, *__prev = cursor ? cursor->prev : NULL; \
    cursor; \
    cursor = __prev == __start ? NULL : __prev, __prev = cursor ? cursor->prev : NULL \
  )

typedef struct intrusive_ring_s intrusive_ring_t;

struct intrusive_ring_s {
  intrusive_ring_t *prev;
  intrusive_ring_t *next;
};

static inline void
intrusive_ring_init (intrusive_ring_t *ring) {
  ring->next = ring;
  ring->prev = ring;
}

static inline bool
intrusive_ring_empty (intrusive_ring_t *ring) {
  return ring == ring->next;
}

static inline intrusive_ring_t *
intrusive_ring_link (intrusive_ring_t *left, intrusive_ring_t *right) {
  intrusive_ring_t *next = left->next;
  intrusive_ring_t *prev = right->prev;

  left->next = right;
  right->prev = left;
  next->prev = prev;
  prev->next = next;

  return next;
}

static inline intrusive_ring_t *
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

static inline intrusive_ring_t *
intrusive_ring_unlink (intrusive_ring_t *ring, int count) {
  if (count <= 0) return NULL;

  return intrusive_ring_link(ring, intrusive_ring_move(ring, count + 1));
}

static inline intrusive_ring_t *
intrusive_ring_remove (intrusive_ring_t *ring) {
  intrusive_ring_t *next = intrusive_ring_link(ring, ring);

  if (next == ring) return NULL;

  return next;
}

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_RING_H
