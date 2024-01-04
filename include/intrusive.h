#ifndef INTRUSIVE_H
#define INTRUSIVE_H

#ifdef __cplusplus
extern "C" {
#endif

#define intrusive_entry(ptr, type, member) \
  ( \
    (type *) ((char *) ptr - offsetof(type, member)) \
  )

#include "intrusive/list.h"
#include "intrusive/queue.h"
#include "intrusive/ring.h"
#include "intrusive/set.h"
#include "intrusive/stack.h"

#ifdef __cplusplus
}
#endif

#endif // INTRUSIVE_H
