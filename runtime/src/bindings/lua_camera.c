#include <cb_engine/types.h>

#include <cb_runtime/bindings/lua_camera.h>
#include <cb_runtime/bindings/lua_vec2.h>
#include <cb_runtime/core/runtime.h>

#include <lauxlib.h>
#include <string.h>

static i32 lua_camera_index(lua_State *L) {
  const char *key = luaL_checkstring(L, 2);
  Camera *camera = *(Camera **)luaL_checkudata(L, 1, "Camera");

  if (strcmp(key, "position") == 0) {
    lua_push_vec2_ptr(L, &camera->position);
    return 1;
  }

  if (strcmp(key, "viewport") == 0) {
    lua_push_vec2_ptr(L, &camera->viewport);
    return 1;
  }

  if (strcmp(key, "zoom") == 0) {
    lua_pushnumber(L, camera->zoom);
    return 1;
  }

  return 0;
}

static i32 lua_camera_new_index(lua_State *L) {
  Camera *camera = *(Camera **)luaL_checkudata(L, 1, "Camera");
  const char *key = luaL_checkstring(L, 2);

  if (strcmp(key, "position") == 0) {
    LuaVec2 *position = luaL_checkudata(L, 3, "Vec2");
    camera_set_position(camera, *position->ptr);
  } else if (strcmp(key, "viewport") == 0) {
    LuaVec2 *viewport = luaL_checkudata(L, 3, "Vec2");
    camera_set_viewport(camera, *viewport->ptr);
  } else if (strcmp(key, "zoom") == 0) {
    f32 zoom = luaL_checknumber(L, 3);
    camera->zoom = zoom;
  }

  return 0;
}

void lua_push_camera(lua_State *L, Camera *camera) {
  Camera **camera_data = lua_newuserdatauv(L, sizeof(Camera *), 0);
  *camera_data = camera;

  luaL_getmetatable(L, "Camera");
  lua_setmetatable(L, -2);
}

void lua_camera_bind(lua_State *L) {
  luaL_newmetatable(L, "Camera");

  lua_pushcfunction(L, lua_camera_index);
  lua_setfield(L, -2, "__index");

  lua_pushcfunction(L, lua_camera_new_index);
  lua_setfield(L, -2, "__newindex");

  lua_pop(L, 1);
}
