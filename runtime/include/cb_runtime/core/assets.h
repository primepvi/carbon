#ifndef CB_ASSETS_H
#define CB_ASSETS_H

#include "cb_runtime/components/collider.h"
#include <cb_engine/core/array_list.h>
#include <cb_engine/core/hashmap.h>
#include <cb_engine/gl/texture.h>
#include <cb_engine/types.h>

#include <cb_runtime/components/component.h>
#include <cb_runtime/components/script.h>
#include <cb_runtime/components/sprite.h>
#include <cb_runtime/components/transform.h>

typedef struct {
  ArrayList *textures;
  ArrayList *scripts;
  ArrayList *sprites;
  ArrayList *transforms;
  ArrayList *colliders;

  HashMap *components;
} Assets;

Assets *assets_new(void);
void assets_destroy(Assets *assets);

CB_API Component assets_load_texture(Assets *assets, const char *path,
                                     const char *name);
CB_API Component assets_load_script(Assets *assets, const char *path,
                                    const char *name);
CB_API Component assets_load_sprite(Assets *assets, Sprite sprite,
                                    const char *name);
CB_API Component assets_load_transform(Assets *assets, Transform transform,
                                       const char *name);
CB_API Component assets_load_collider(Assets *assets, Collider collider,
                                      const char *name);

CB_API Texture *assets_get_texture(Assets *assets, ComponentHandle handle);
CB_API Script *assets_get_script(Assets *assets, ComponentHandle handle);
CB_API Sprite *assets_get_sprite(Assets *assets, ComponentHandle handle);
CB_API Transform *assets_get_transform(Assets *assets, ComponentHandle handle);
CB_API Collider *assets_get_collider(Assets *assets, ComponentHandle handle);

CB_API ComponentHandle assets_get_component_handle(Assets *assets,
                                                   ComponentKind kind,
                                                   const char *name);
CB_API b8 assets_has_component(Assets *assets, ComponentKind kind,
                               const char *name);

#endif
