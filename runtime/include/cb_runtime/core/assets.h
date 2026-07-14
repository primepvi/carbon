#ifndef CB_ASSETS_H
#define CB_ASSETS_H

#include <cb_engine/core/array_list.h>
#include <cb_engine/core/hashmap.h>
#include <cb_engine/gl/texture.h>
#include <cb_engine/types.h>
#include <cb_runtime/components/sprite.h>

#include <cb_runtime/components/component.h>
#include <cb_runtime/components/script.h>

typedef struct {
  ArrayList *textures;
  HashMap *textures_handles;

  ArrayList *scripts;
  HashMap *scripts_handles;

  ArrayList *sprites;
  HashMap *sprites_handles;
} Assets;

Assets *assets_new(void);
void assets_destroy(Assets *assets);

Component assets_load_texture(Assets *assets, const char *path,
                              const char *name);
Component assets_load_script(Assets *assets, const char *path,
                             const char *name);
Component assets_load_sprite(Assets *assets, Sprite sprite, const char *name);

Texture *assets_get_texture(Assets *assets, ComponentHandle handle);
Script *assets_get_script(Assets *assets, ComponentHandle handle);
Sprite *assets_get_sprite(Assets *assets, ComponentHandle handle);

ComponentHandle assets_get_component_handle(Assets *assets, ComponentKind kind,
                                            const char *name);
b8 assets_has_component(Assets *assets, ComponentKind kind, const char *name);

#endif
