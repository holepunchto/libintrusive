#include <assert.h>
#include <stdio.h>

#include "../include/intrusive.h"
#include "../include/intrusive/ring.h"

int
main () {
  struct node {
    int value;
    intrusive_ring_t ring;
  };

  struct node a = {1};
  struct node b = {2};
  struct node c = {3};

  intrusive_ring_init(&a.ring);
  intrusive_ring_init(&b.ring);
  intrusive_ring_init(&c.ring);

  intrusive_ring_link(&a.ring, intrusive_ring_link(&b.ring, &c.ring));

  int i = 0;

  intrusive_ring_for_each(next, &a.ring) {
    struct node *n = intrusive_entry(next, struct node, ring);

    printf("n->value=%d\n", n->value);

    assert(++i == n->value);
  }

  assert(i == 3);
}
