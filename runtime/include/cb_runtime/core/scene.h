#ifndef CB_SCENE_H
#define CB_SCENE_H

#include <cb_engine/core/array_list.h>
#include <cb_engine/renderer/renderer.h>

#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/node.h>

#define SCENE_ROOT_NODE_HANDLE 0

typedef struct {
  char *name;
  Node *root;

  ArrayList *nodes;
  ArrayList *sprites;
} Scene;

Scene *scene_new(const char *name);
void scene_destroy(Scene *scene);
void scene_render(Scene *scene, Renderer *renderer);

Component scene_create_component(Scene *scene, ComponentKind kind,
                                       void *data);

NodeHandle scene_find_node(Scene *scene, const char *name);
NodeHandle scene_node_create(Scene *scene, const char *name);
NodeHandle scene_node_find_child(Scene *scene, NodeHandle parent_handle, const char *name);
void scene_node_attach_component(Scene *scene, NodeHandle node_handle,
                                 Component *component);


#endif
