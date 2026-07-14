#ifndef CB_SPRITE_H
#define CB_SPRITE_H

#include <cb_engine/gl/texture.h>
#include <cb_engine/math/vec2.h>
#include <cb_engine/math/color.h>

#include <cb_runtime/components/component.h>

typedef struct {
  TextureHandle texture_handle;
  Color color;
  
  Vec2 position;
  Vec2 scale;

  b8 flip_x, flip_y;
} Sprite;

Sprite sprite_with_texture(TextureHandle texture_handle, Vec2 position, Vec2 scale);
Sprite sprite_with_color(Color color, Vec2 position, Vec2 scale);

void sprite_move(Sprite *sprite, Vec2 delta);
void sprite_scale(Sprite *sprite, f32 scalar);

void sprite_flip_horizontal(Sprite *sprite);
void sprite_flip_vertical(Sprite *sprite);

b8 sprite_component_kind_comparator(void *current);

#endif
