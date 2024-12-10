#ifndef INTRUSIVE_SET_H
#define INTRUSIVE_SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct intrusive_set_s intrusive_set_t;
typedef struct intrusive_set_node_s intrusive_set_node_t;

typedef size_t (*intrusive_set_hash_cb)(const void *key, void *data);
typedef bool (*intrusive_set_equal_cb)(const void *key, const intrusive_set_node_t *node, void *data);

struct intrusive_set_s {
  size_t len;
  intrusive_set_node_t **buckets;
  size_t mask;
  intrusive_set_hash_cb hash;
  intrusive_set_equal_cb equal;
  void *data;
};

struct intrusive_set_node_s {
  intrusive_set_node_t *next;
};

static inline void
intrusive_set_init (intrusive_set_t *set, intrusive_set_node_t **buckets, size_t len, void *data, intrusive_set_hash_cb hash, intrusive_set_equal_cb equal) {
  assert((len & (len - 1)) == 0 && "Bucket count must be a power of 2");

  set->len = 0;
  set->buckets = buckets;
  set->mask = len - 1;
  set->data = data;
  set->hash = hash;
  set->equal = equal;

  memset(set->buckets, 0, sizeof(intrusive_set_node_t *) * len);
}

static inline bool
intrusive_set_empty (const intrusive_set_t *set) {
  return set->len == 0;
}

static inline intrusive_set_node_t *
intrusive_set_get (const intrusive_set_t *set, const void *key) {
  intrusive_set_node_t *node = set->buckets[set->hash(key, set->data) & set->mask];

  while (node != NULL && !set->equal(key, node, set->data)) {
    node = node->next;
  }

  return node;
}

static inline bool
intrusive_set_has (const intrusive_set_t *set, const void *key) {
  return intrusive_set_get(set, key) != NULL;
}

static inline void
intrusive_set_add (intrusive_set_t *set, const void *key, intrusive_set_node_t *node) {
  intrusive_set_node_t **bucket = &set->buckets[set->hash(key, set->data) & set->mask];

  for (intrusive_set_node_t *next = *bucket, *prev = NULL; next != NULL; prev = next, next = next->next) {
    if (set->equal(key, next, set->data)) {
      if (prev) {
        prev->next = node;
      } else {
        *bucket = node;
      }

      node->next = next->next;
      next->next = NULL;

      return;
    }
  }

  node->next = *bucket;

  *bucket = node;

  set->len++;
}

static inline bool
intrusive_set_delete (intrusive_set_t *set, const void *key) {
  intrusive_set_node_t **bucket = &set->buckets[set->hash(key, set->data) & set->mask];

  for (intrusive_set_node_t *next = *bucket, *prev = NULL; next != NULL; prev = next, next = next->next) {
    if (set->equal(key, next, set->data)) {
      if (prev) {
        prev->next = next->next;
      } else {
        *bucket = next->next;
      }

      next->next = NULL;

      set->len--;

      return true;
    }
  }

  return false;
}

#define intrusive_set_for_each(cursor, idx, set) \
  for ( \
    size_t idx = 0; \
    idx <= (set)->mask; \
    idx++ \
  ) \
    for ( \
      intrusive_set_node_t *cursor = (set)->buckets[idx], *__next = cursor ? cursor->next : NULL; \
      cursor; \
      cursor = __next, __next = cursor ? cursor->next : NULL \
    )

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_SET_H
