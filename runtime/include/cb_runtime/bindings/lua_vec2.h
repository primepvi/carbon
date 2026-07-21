#ifndef CB_LUA_VEC2_H
#define CB_LUA_VEC2_H

#include <cb_engine/math/vec2.h>
#include <lua.h>

typedef struct {
  Vec2 *ptr;
  Vec2 value;
} LuaVec2;

void lua_push_vec2(lua_State *L, Vec2 vec);
void lua_push_vec2_ptr(lua_State *L, Vec2 *vec);
void lua_vec2_bind(lua_State *L);

#endif
