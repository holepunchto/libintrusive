#ifndef INTRUSIVE_RING_H
#define INTRUSIVE_RING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct intrusive_ring_s intrusive_ring_t;

struct intrusive_ring_s {
  intrusive_ring_t *prev;
  intrusive_ring_t *next;
};

void
intrusive_ring_init (intrusive_ring_t *ring);

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
    intrusive_ring_t *__start = (ring), *cursor = __start; \
    cursor != NULL; \
    cursor = cursor->next == __start ? NULL : cursor->next \
  )

#define intrusive_ring_for_each_reverse(cursor, ring) \
  for ( \
    intrusive_ring_t *__start = (ring), *cursor = __start; \
    cursor != NULL; \
    cursor = cursor->prev == __start ? NULL : cursor->prev \
  )

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_RING_H
