#include <assert.h>
#include <stdio.h>

#include "../../include/intrusive.h"
#include "../../include/intrusive/queue.h"

int
main () {
  struct node {
    int value;
    intrusive_queue_node_t node;
  };

  struct node a = {1};
  struct node b = {2};
  struct node c = {3};

  intrusive_queue_t list;
  intrusive_queue_init(&list);

  intrusive_queue_push(&list, &a.node);
  intrusive_queue_push(&list, &b.node);
  intrusive_queue_push(&list, &c.node);

  int i = 0;

  intrusive_queue_for_each(next, &list) {
    struct node *n = intrusive_entry(next, struct node, node);

    printf("n->value=%d\n", n->value);

    assert(++i == n->value);
  }

  assert(i == 3);
}
