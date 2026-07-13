#ifndef CB_ARRAY_LIST_H
#define CB_ARRAY_LIST_H

#include "../types.h"

typedef struct {
  void *buf;
  u32 buf_length, buf_capacity;
  u32 element_size;
} ArrayList;

typedef b8(*ArrayListComparatorFn)(void *current, void *expected);

ArrayList *array_list_new(u32 buf_capacity, u32 element_size);
void array_list_destroy(ArrayList *array);

u32 array_list_push(ArrayList *array, void *element);
b8 array_list_replace(ArrayList *array, u32 index, void *element);
void *array_list_pop(ArrayList *array);
void *array_list_at(ArrayList *array, u32 index);
i32 array_list_find_index(ArrayList *array, ArrayListComparatorFn comparator, void *element);

u32 array_list_length(ArrayList *array);
u32 array_list_capacity(ArrayList *array);

#endif
