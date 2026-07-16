#include <cb_engine/math/vec2.h>
#include <cb_engine/types.h>
#include <cb_runtime/bindings/lua_vec2.h>

#include <lauxlib.h>
#include <string.h>

static i32 lua_vec2_new(lua_State *L) {
  f32 x = luaL_checknumber(L, 1);
  f32 y = luaL_checknumber(L, 2);
  lua_push_vec2(L, VEC2(x, y));

  return 1;
}

static i32 lua_vec2_normalize(lua_State *L) {
  Vec2 *vec = luaL_checkudata(L, 1, "Vec2");
  lua_push_vec2(L, vec2_normalize(*vec));

  return 1;
}

static i32 lua_vec2_scale(lua_State *L) {
  Vec2 *vec = luaL_checkudata(L, 1, "Vec2");
  f32 scalar = luaL_checknumber(L, 2);
  lua_push_vec2(L, vec2_scale(*vec, scalar));

  return 1;
}

static i32 lua_vec2_add(lua_State *L) {
  Vec2 *a = luaL_checkudata(L, 1, "Vec2");
  Vec2 *b = luaL_checkudata(L, 2, "Vec2");

  lua_push_vec2(L, vec2_add(*a, *b));
  return 1;
}

static i32 lua_vec2_index(lua_State *L) {
  const char *key = luaL_checkstring(L, 2);

  if (strcmp(key, "x") == 0) {
    Vec2 *vec = luaL_checkudata(L, 1, "Vec2");
    lua_pushnumber(L, vec->x);
    return 1;
  }

  if (strcmp(key, "y") == 0) {
    Vec2 *vec = luaL_checkudata(L, 1, "Vec2");
    lua_pushnumber(L, vec->y);
    return 1;
  }

  if (strcmp(key, "normalize") == 0) {
    lua_pushcfunction(L, lua_vec2_normalize);
    return 1;
  }

  if (strcmp(key, "scale") == 0) {
    lua_pushcfunction(L, lua_vec2_scale);
    return 1;
  }

  if (strcmp(key, "add") == 0) {
    lua_pushcfunction(L, lua_vec2_add);
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

void lua_push_vec2(lua_State *L, Vec2 vec) {
  Vec2 *vec_data = lua_newuserdatauv(L, sizeof(Vec2), 0);
  *vec_data = vec;

  luaL_getmetatable(L, "Vec2");
  lua_setmetatable(L, -2);
}

void lua_vec2_bind(lua_State *L) {
  luaL_newmetatable(L, "Vec2");

  lua_pushcfunction(L, lua_vec2_index);
  lua_setfield(L, -2, "__index");

  lua_pushcfunction(L, lua_vec2_new_index);
  lua_setfield(L, -2, "__newindex");

  lua_pushcfunction(L, lua_vec2_add);
  lua_setfield(L, -2, "__add");

  lua_pop(L, 1);

  lua_newtable(L);
  lua_pushcfunction(L, lua_vec2_new);
  lua_setfield(L, -2, "new");

  lua_pushcfunction(L, lua_vec2_normalize);
  lua_setfield(L, -2, "normalize");

  lua_pushcfunction(L, lua_vec2_scale);
  lua_setfield(L, -2, "scale");

  lua_pushcfunction(L, lua_vec2_add);
  lua_setfield(L, -2, "add");

  lua_setglobal(L, "Vec2");
}
