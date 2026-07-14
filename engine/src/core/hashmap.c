#include <cb_engine/core/hashmap.h>
#include <cb_engine/types.h>

#include <stdlib.h>
#include <string.h>

// FNV
static u64 hashmap_hash(const char *key) {
  u64 hash = 14695981039346656037ULL;

  while (*key) {
    hash ^= (u8)*key++;
    hash *= 1099511628211ULL;
  }

  return hash;
}

HashMap *hashmap_new(u32 capacity) {
  HashMap *hashmap = malloc(sizeof(HashMap));
  hashmap->entries = calloc(capacity, sizeof(HashMapEntry));
  hashmap->entries_capacity = capacity;
  hashmap->entries_len = 0;

  return hashmap;
}

void hashmap_destroy(HashMap *map) {
  for (u32 i = 0; i < map->entries_capacity; i++) {
    HashMapEntry *entry = &map->entries[i];
    if (entry->state == HASHMAP_ENTRY_OCCUPIED) {
      free(entry->key);
      free(entry->value);
    }
  }

  free(map->entries);
  free(map);
}

void hashmap_put(HashMap *map, const char *key, u32 element_size, void *value) {
  if (map->entries_len >= map->entries_capacity) {
    hashmap_grow_capacity(map, 2);
  }

  u64 key_hash = hashmap_hash(key);
  u64 index = key_hash % map->entries_capacity;

  while (true) {
    HashMapEntry *entry = &map->entries[index];

    // insert
    if (entry->state == HASHMAP_ENTRY_EMPTY ||
        entry->state == HASHMAP_ENTRY_REMOVED) {
      entry->state = HASHMAP_ENTRY_OCCUPIED;
      entry->key = strdup(key);
      entry->value = malloc(element_size);
      memcpy(entry->value, value, element_size);
      map->entries_len++;
      return;
    }

    // update
    if (entry->state == HASHMAP_ENTRY_OCCUPIED &&
        strcmp(entry->key, key) == 0) {
      memcpy(entry->value, value, element_size);
      return;
    }

    index = (index + 1) % map->entries_capacity;
  }
}

void *hashmap_get(HashMap *map, const char *key) {
  u64 key_hash = hashmap_hash(key);
  u64 index = key_hash % map->entries_capacity;
  u64 start_index = index;

  void *result = NULL;

  do {
    HashMapEntry *entry = &map->entries[index];

    if (entry->state == HASHMAP_ENTRY_EMPTY) {
      break;
    }

    if (entry->state == HASHMAP_ENTRY_OCCUPIED &&
        strcmp(entry->key, key) == 0) {
      result = entry->value;
      break;
    }

    index = (index + 1) % map->entries_capacity;
  } while (index != start_index);

  return result;
}

void *hashmap_remove(HashMap *map, const char *key) {
  u64 key_hash = hashmap_hash(key);
  u64 index = key_hash % map->entries_capacity;
  u64 start_index = index;

  void *result = NULL;

  do {
    HashMapEntry *entry = &map->entries[index];

    if (entry->state == HASHMAP_ENTRY_EMPTY) {
      break;
    }

    if (entry->state == HASHMAP_ENTRY_OCCUPIED &&
        strcmp(entry->key, key) == 0) {
      free(entry->key);
      map->entries_len--;
      result = entry->value;

      entry->state = HASHMAP_ENTRY_REMOVED;
      entry->value = NULL;
      entry->key = NULL;

      break;
    }

    index = (index + 1) % map->entries_capacity;
  } while (index != start_index);

  return result;
}

b8 hashmap_has(HashMap *map, const char *key) {
  u64 key_hash = hashmap_hash(key);
  u64 index = key_hash % map->entries_capacity;
  u64 start_index = index;

  b8 result = false;

  do {
    HashMapEntry *entry = &map->entries[index];

    if (entry->state == HASHMAP_ENTRY_EMPTY) {
      break;
    }

    if (entry->state == HASHMAP_ENTRY_OCCUPIED &&
        strcmp(entry->key, key) == 0) {
      result = true;
      break;
    }

    index = (index + 1) % map->entries_capacity;
  } while (index != start_index);

  return result;
}

void hashmap_grow_capacity(HashMap *map, u32 factor) {
  u32 new_len = 0;
  u32 new_capacity = map->entries_capacity * factor;
  HashMapEntry *new_entries = calloc(new_capacity, sizeof(HashMapEntry));

  for (u32 i = 0; i < map->entries_capacity; i++) {
    HashMapEntry *entry = &map->entries[i];
    if (entry->state != HASHMAP_ENTRY_OCCUPIED) {
      continue;
    }

    u64 key_hash = hashmap_hash(entry->key);
    u64 index = key_hash % new_capacity;

    while (new_entries[index].state == HASHMAP_ENTRY_OCCUPIED) {
      index = (index + 1) % new_capacity;
    }

    new_entries[index] = *entry;
    new_len++;
  }

  free(map->entries);

  map->entries = new_entries;
  map->entries_capacity = new_capacity;
  map->entries_len = new_len;
}
