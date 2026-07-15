#ifndef CB_TRANSFORM_H
#define CB_TRANSFORM_H

#include <cb_engine/math/vec2.h>

typedef struct {
  Vec2 position;
  Vec2 scale;
} Transform;

CB_API Transform transform_create(Vec2 position, Vec2 scale);
b8 transform_component_kind_comparator(void *current);

#endif
