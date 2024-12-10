#include <assert.h>
#include <stdio.h>

#include "../../include/intrusive.h"
#include "../../include/intrusive/list.h"

int
main () {
  struct node {
    int value;
    intrusive_list_node_t node;
  };

  struct node a = {1};
  struct node b = {2};
  struct node c = {3};

  intrusive_list_t list;
  intrusive_list_init(&list);

  intrusive_list_append(&list, &a.node);
  intrusive_list_append(&list, &b.node);
  intrusive_list_append(&list, &c.node);

  int i = 0;

  intrusive_list_for_each(next, &list) {
    struct node *n = intrusive_entry(next, struct node, node);

    printf("n->value=%d\n", n->value);

    assert(++i == n->value);
  }

  assert(i == 3);
}
