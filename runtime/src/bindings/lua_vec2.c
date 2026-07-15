#include <cb_engine/math/vec2.h>
#include <cb_engine/types.h>
#include <cb_runtime/bindings/lua_vec2.h>

#include <lauxlib.h>
#include <string.h>

static i32 lua_vec2_new(lua_State *L) {
  f32 x = luaL_checknumber(L, 1);
  f32 y = luaL_checknumber(L, 2);

  Vec2 *vec = lua_newuserdatauv(L, sizeof(Vec2), 0);
  vec->x = x;
  vec->y = y;

  luaL_getmetatable(L, "Vec2");
  lua_setmetatable(L, -2);

  return 1;
}

static i32 lua_vec2_normalize(lua_State *L) {
  Vec2 *vec = luaL_checkudata(L, 1, "Vec2");
  Vec2 *vec_normalized = lua_newuserdatauv(L, sizeof(Vec2), 0);
  *vec_normalized = vec2_normalize(*vec);

  luaL_getmetatable(L, "Vec2");
  lua_setmetatable(L, -2);

  return 1;
}

static i32 lua_vec2_scale(lua_State *L) {
  Vec2 *vec = luaL_checkudata(L, 1, "Vec2");
  f32 scalar = luaL_checknumber(L, 2);
  
  Vec2 *vec_scaled = lua_newuserdatauv(L, sizeof(Vec2), 0);
  *vec_scaled = vec2_scale(*vec, scalar);

  luaL_getmetatable(L, "Vec2");
  lua_setmetatable(L, -2);

  return 1;
}

static i32 lua_vec2_index(lua_State *L) {
  Vec2 *vec = luaL_checkudata(L, 1, "Vec2");
  const char *key = luaL_checkstring(L, 2);

  if (strcmp(key, "x") == 0) {
    lua_pushnumber(L, vec->x);
    return 1;
  }

  if (strcmp(key, "y") == 0) {
    lua_pushnumber(L, vec->y);
    return 1;
  }

  return 0;
}

static i32 lua_vec2_new_index(lua_State *L) {
  Vec2 *vec = luaL_checkudata(L, 1, "Vec2");
  const char *key = luaL_checkstring(L, 2);
  f32 value = luaL_checknumber(L, 3);

  if (strcmp(key, "x") == 0)
    vec->x = value;
  else if (strcmp(key, "y") == 0)
    vec->y = value;

  return 0;
}

void lua_vec2_bind(lua_State *L) {
  luaL_newmetatable(L, "Vec2");

  lua_pushcfunction(L, lua_vec2_index);
  lua_setfield(L, -2, "__index");

  lua_pushcfunction(L, lua_vec2_new_index);
  lua_setfield(L, -2, "__newindex");

  lua_pop(L, 1);

  lua_newtable(L);
  lua_pushcfunction(L, lua_vec2_new);
  lua_setfield(L, -2, "new");

  Vec2 *vec2_zero_data = lua_newuserdatauv(L, sizeof(Vec2), 0);
  *vec2_zero_data = VEC2_ZERO;

  luaL_getmetatable(L, "Vec2");
  lua_setmetatable(L, -2);
  lua_setfield(L, -2, "zero");

  Vec2 *vec2_one_data = lua_newuserdatauv(L, sizeof(Vec2), 0);
  *vec2_one_data = VEC2_ONE;

  luaL_getmetatable(L, "Vec2");
  lua_setmetatable(L, -2);
  lua_setfield(L, -2, "one");

  lua_pushcfunction(L, lua_vec2_normalize);
  lua_setfield(L, -2, "normalize");

  lua_pushcfunction(L, lua_vec2_scale);
  lua_setfield(L, -2, "scale");

  lua_setglobal(L, "Vec2");
}
