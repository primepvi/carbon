#ifndef CB_ASSETS_H
#define CB_ASSETS_H

#include <cb_engine/core/hashmap.h>
#include <cb_engine/gl/texture.h>
#include <cb_engine/types.h>

typedef struct {
  HashMap *textures;
} Assets;

Assets *assets_new(void);
void assets_destroy(Assets *assets);

Texture *assets_load_texture(Assets *assets, const char *path, const char *name);
Texture *assets_get_texture(Assets *assets, const char *name);
b8 assets_has_texture(Assets *assets, const char *name);

#endif
