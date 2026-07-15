#ifndef CB_SPRITE_H
#define CB_SPRITE_H

#include <cb_engine/gl/texture.h>
#include <cb_engine/math/vec2.h>
#include <cb_engine/math/color.h>

#include <cb_runtime/components/component.h>

typedef struct {
  ComponentHandle texture_handle;
  Color color;
  b8 flip_x, flip_y;
} Sprite;

CB_API Sprite sprite_create(ComponentHandle texture_handle, Color color, b8 flip_x, b8 flip_y);

CB_API void sprite_flip_horizontal(Sprite *sprite);
CB_API void sprite_flip_vertical(Sprite *sprite);

b8 sprite_component_kind_comparator(void *current);

#endif
