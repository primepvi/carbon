#ifndef CB_SCENE_H
#define CB_SCENE_H

#include <cb_engine/core/array_list.h>
#include <cb_engine/renderer/renderer.h>

#include <cb_runtime/core/node.h>
#include <cb_runtime/components/sprite.h>

typedef struct {
  char *name;
  Node *root;
  
  ArrayList *sprites;
} Scene;

Scene *scene_new(const char *name);
void scene_destroy(Scene *scene);
void scene_render(Scene *scene, Renderer *renderer);
void scene_append_node(Scene *scene, Node *node);
ComponentHandle scene_register_sprite(Scene *scene, Sprite *sprite);

#endif
