#ifndef CB_RECT_H
#define CB_RECT_H

#include "vec2.h"

typedef struct {
  Vec2 position;
  Vec2 size;
} Rect;

#define RECT(x, y, width, height)                                              \
  (Rect) { .position = VEC2(x, y), .size = VEC2(width, height) }

b8 rect_contains(Rect rect, Vec2 point);
b8 rect_intersects(Rect a, Rect b);

#endif
