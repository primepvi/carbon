#ifndef CB_SCENE_H
#define CB_SCENE_H

#include <cb_engine/core/array_list.h>
#include <cb_engine/renderer/renderer.h>

#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/assets.h>
#include <cb_runtime/core/camera.h>
#include <cb_runtime/core/node.h>

#define SCENE_ROOT_NODE_HANDLE 0

typedef struct {
  char *name;
  Node *root;

  ArrayList *nodes;
  Camera camera;
} Scene;

typedef struct {
  Node *node;
  
  Script *script;
  Sprite *sprite;
  Transform *transform;
  Collider *collider;
} SceneRenderable;

CB_API Scene *scene_new(const char *name, Camera camera);
CB_API Scene *scene_from_json(Assets *assets, Camera camera, const char *path);

CB_API void scene_destroy(Scene *scene);

CB_API Camera *scene_get_camera(Scene *scene);

CB_API ArrayList *scene_make_renderables(Scene *scene);
CB_API void scene_draw(Scene *scene, Renderer *renderer,
                       ArrayList *renderables);
CB_API void scene_update(Scene *scene, ArrayList *renderables);
CB_API void scene_physics_update(Scene *scene, ArrayList *renderables);

CB_API Node *scene_get_node(Scene *scene, NodeHandle handle);
CB_API NodeHandle scene_find_node(Scene *scene, const char *name);
CB_API NodeHandle scene_node_create(Scene *scene, const char *name);
CB_API NodeHandle scene_node_find_child(Scene *scene, NodeHandle parent_handle,
                                        const char *name);
CB_API void scene_node_attach_component(Scene *scene, NodeHandle node_handle,
                                        Component component);

#endif
