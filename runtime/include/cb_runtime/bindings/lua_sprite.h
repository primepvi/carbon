#ifndef CB_LUA_SPRITE_H
#define CB_LUA_SPRITE_H

#include <cb_runtime/components/sprite.h>
#include <lua.h>

void lua_push_sprite(lua_State *L, Sprite *sprite);
void lua_sprite_bind(lua_State *L);

#endif
