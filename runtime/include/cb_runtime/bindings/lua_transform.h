#ifndef CB_LUA_TRANSFORM_H
#define CB_LUA_TRANSFORM_H

#include <cb_runtime/components/transform.h>
#include <lua.h>

void lua_push_transform(lua_State *L, Transform *transform);
void lua_transform_bind(lua_State *L);

#endif
