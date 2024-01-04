#ifndef INTRUSIVE_SET_H
#define INTRUSIVE_SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

typedef struct intrusive_set_s intrusive_set_t;
typedef struct intrusive_set_node_s intrusive_set_node_t;

typedef size_t (*intrusive_set_hash_cb)(const void *key, void *data);
typedef bool (*intrusive_set_equal_cb)(const void *key, const intrusive_set_node_t *node, void *data);

struct intrusive_set_s {
  size_t len;
  intrusive_set_node_t **buckets;
  size_t buckets_len;
  intrusive_set_hash_cb hash;
  intrusive_set_equal_cb equal;
  void *data;
};

struct intrusive_set_node_s {
  intrusive_set_node_t *next;
};

void
intrusive_set_init (intrusive_set_t *set, intrusive_set_node_t **buckets, size_t buckets_len, void *data, intrusive_set_hash_cb hash, intrusive_set_equal_cb equal);

bool
intrusive_set_empty (const intrusive_set_t *set);

intrusive_set_node_t *
intrusive_set_get (const intrusive_set_t *set, const void *key);

bool
intrusive_set_has (const intrusive_set_t *set, const void *key);

void
intrusive_set_add (intrusive_set_t *set, const void *key, intrusive_set_node_t *node);

bool
intrusive_set_delete (intrusive_set_t *set, const void *key);

#define intrusive_set_for_each(cursor, idx, set) \
  for ( \
    size_t idx = 0; \
    idx < (set)->buckets_len; \
    idx++ \
  ) \
    for ( \
      cursor = (set)->buckets[idx]; \
      cursor != NULL; \
      cursor = cursor->next \
    )

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_SET_H
