#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include "../include/intrusive/set.h"

void
intrusive_set_init (intrusive_set_t *set, intrusive_set_node_t **buckets, size_t len, void *data, intrusive_set_hash_cb hash, intrusive_set_equal_cb equal) {
  assert((len & (len - 1)) == 0);

  set->len = 0;
  set->buckets = buckets;
  set->mask = len - 1;
  set->data = data;
  set->hash = hash;
  set->equal = equal;
}

bool
intrusive_set_empty (const intrusive_set_t *set) {
  return set->len == 0;
}

intrusive_set_node_t *
intrusive_set_get (const intrusive_set_t *set, const void *key) {
  intrusive_set_node_t *node = set->buckets[set->hash(key, set->data) & set->mask];

  while (node != NULL && !set->equal(key, node, set->data)) {
    node = node->next;
  }

  return node;
}

bool
intrusive_set_has (const intrusive_set_t *set, const void *key) {
  return intrusive_set_get(set, key) != NULL;
}

void
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

bool
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
