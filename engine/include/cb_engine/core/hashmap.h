#ifndef CB_HASHMAP_H
#define CB_HASHMAP_H

#include "../types.h"

typedef enum {
  HASHMAP_ENTRY_EMPTY = 0,
  HASHMAP_ENTRY_OCCUPIED,
  HASHMAP_ENTRY_REMOVED,
} HashMapEntryState;

typedef struct {
  char *key;
  void *value;
  HashMapEntryState state;
} HashMapEntry;

typedef struct {
  HashMapEntry *entries;
  u32 entries_capacity;
  u32 entries_len;
} HashMap;

CB_API HashMap *hashmap_new(u32 capacity);
CB_API void hashmap_destroy(HashMap *map);
void hashmap_grow_capacity(HashMap *map, u32 factor);

CB_API void hashmap_put(HashMap *map, const char *string, void *value);
CB_API void *hashmap_get(HashMap *map, const char *string);
CB_API void *hashmap_remove(HashMap *map, const char *string);
CB_API b8 hashmap_has(HashMap *map, const char *string);

#endif
