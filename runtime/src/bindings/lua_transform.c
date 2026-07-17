#include <cb_engine/types.h>
#include <cb_runtime/bindings/lua_transform.h>
#include <cb_runtime/bindings/lua_vec2.h>
#include <lauxlib.h>
#include <string.h>

static i32 lua_transform_index(lua_State *L) {
  Transform **transform = luaL_checkudata(L, 1, "Transform");
  const char *key = luaL_checkstring(L, 2);

  if (strcmp(key, "position") == 0) {
    lua_push_vec2(L, (*transform)->position);
    return 1;
  }

  if (strcmp(key, "scale") == 0) {
    lua_push_vec2(L, (*transform)->scale);
    return 1;
  }

  return 0;
}

static i32 lua_transform_new_index(lua_State *L) {
  Transform *transform = *(Transform **)luaL_checkudata(L, 1, "Transform");
  const char *key = luaL_checkstring(L, 2);
  Vec2 *value = luaL_checkudata(L, 3, "Vec2");

  if (strcmp(key, "position") == 0) {
    transform->previous_position = transform->position;
    transform->position = *value;
  } else if (strcmp(key, "scale") == 0) {
    transform->scale = *value;
  }

  return 0;
}

void lua_push_transform(lua_State *L, Transform *transform) {
  Transform **transform_data = lua_newuserdatauv(L, sizeof(Transform *), 0);
  *transform_data = transform;

  luaL_getmetatable(L, "Transform");
  lua_setmetatable(L, -2);
}

void lua_transform_bind(lua_State *L) {
  luaL_newmetatable(L, "Transform");

  lua_pushcfunction(L, lua_transform_index);
  lua_setfield(L, -2, "__index");

  lua_pushcfunction(L, lua_transform_new_index);
  lua_setfield(L, -2, "__newindex");

  lua_pop(L, 1);
}
