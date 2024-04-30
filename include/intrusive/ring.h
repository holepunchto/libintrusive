#ifndef INTRUSIVE_RING_H
#define INTRUSIVE_RING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

typedef struct intrusive_ring_s intrusive_ring_t;

struct intrusive_ring_s {
  intrusive_ring_t *prev;
  intrusive_ring_t *next;
};

void
intrusive_ring_init (intrusive_ring_t *ring);

bool
intrusive_ring_empty (intrusive_ring_t *ring);

intrusive_ring_t *
intrusive_ring_link (intrusive_ring_t *left, intrusive_ring_t *right);

intrusive_ring_t *
intrusive_ring_move (intrusive_ring_t *ring, int count);

intrusive_ring_t *
intrusive_ring_unlink (intrusive_ring_t *ring, int count);

intrusive_ring_t *
intrusive_ring_remove (intrusive_ring_t *ring);

#define intrusive_ring_for_each(cursor, ring) \
  for ( \
    intrusive_ring_t *__start = (ring), *cursor = __start, *__next = cursor ? cursor->next : NULL; \
    cursor; \
    cursor = __next == __start ? NULL : next, __next = cursor ? cursor->next : NULL \
  )

#define intrusive_ring_for_each_reverse(cursor, ring) \
  for ( \
    intrusive_ring_t *__start = (ring), *cursor = __start, *__prev = cursor ? cursor->prev : NULL; \
    cursor; \
    cursor = __prev == __start ? NULL : __prev, __prev = cursor ? cursor->prev : NULL \
  )

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_RING_H
