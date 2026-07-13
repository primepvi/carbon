#include "cb_runtime/components/component.h"
#include <cb_runtime/components/sprite.h>
#include <stdlib.h>

Sprite *sprite_with_texture(Texture *texture, Vec2 position, Vec2 scale) {
  Sprite *sprite = malloc(sizeof(Sprite));
  sprite->texture = texture;
  sprite->position = position;
  sprite->scale = scale;

  sprite->flip_x = false;
  sprite->flip_y = false;

  return sprite;
}

Sprite *sprite_with_color(Color color, Vec2 position, Vec2 scale) {
  Sprite *sprite = malloc(sizeof(Sprite));
  sprite->color = color;
  sprite->position = position;
  sprite->scale = scale;

  sprite->flip_x = false;
  sprite->flip_y = false;

  return sprite;
}

void sprite_destroy(Sprite *sprite) { free(sprite); }

void sprite_move(Sprite *sprite, Vec2 delta) {
  sprite->position = vec2_add(sprite->position, delta);
}

void sprite_scale(Sprite *sprite, f32 scalar) {
  sprite->scale = vec2_scale(sprite->scale, scalar);
}

void sprite_flip_horizontal(Sprite *sprite) {
  sprite->flip_x = !sprite->flip_x;
}

void sprite_flip_vertical(Sprite *sprite) { sprite->flip_y = !sprite->flip_y; }

b8 sprite_component_kind_comparator(void *current, void *_expected) {
  return ((Component*)current)->kind == COMPONENT_SPRITE;
};
