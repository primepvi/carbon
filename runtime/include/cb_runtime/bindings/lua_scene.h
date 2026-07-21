#ifndef CB_LUA_SCENE_H
#define CB_LUA_SCENE_H

#include <cb_runtime/core/scene.h>
#include <lua.h>

void lua_push_scene(lua_State *L, Scene *scene);
void lua_scene_bind(lua_State *L);

#endif
