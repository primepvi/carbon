#include <cb_engine/core/array_list.h>
#include <cb_engine/core/logger.h>
#include <stdlib.h>
#include <string.h>

ArrayList *array_list_new(u32 buf_capacity, u32 element_size) {
  ArrayList *array = malloc(sizeof(ArrayList));
  array->buf = calloc(buf_capacity, element_size);
  array->buf_capacity = buf_capacity;
  array->buf_length = 0;
  array->element_size = element_size;

  return array;
}

void array_list_destroy(ArrayList *array) {
  free(array->buf);
  free(array);
}

void array_list_push(ArrayList *array, void *element) {
  if (array->buf_length >= array->buf_capacity) {
    array->buf_capacity *= 2;
    array->buf = realloc(array->buf, array->element_size * array->buf_capacity);
  }

  memcpy((u8 *)array->buf + (array->buf_length++) * array->element_size,
         element, array->element_size);
}

b8 array_list_replace(ArrayList *array, u32 index, void *element) {
  if (index >= array->buf_length) {
    return false;
  }

  memcpy((u8 *)array->buf + index * array->element_size, element,
         array->element_size);
  return true;
}

void *array_list_pop(ArrayList *array) {
  if (array->buf_length == 0) {
    return NULL;
  }

  array->buf_length -= 1;
  return (u8 *)array->buf + array->buf_length * array->element_size;
}

void *array_list_at(ArrayList *array, u32 index) {
  if (index >= array->buf_length) {
    return NULL;
  }

  return (u8 *)array->buf + index * array->element_size;
}

u32 array_list_length(ArrayList *array) { return array->buf_length; }
u32 array_list_capacity(ArrayList *array) { return array->buf_capacity; }
