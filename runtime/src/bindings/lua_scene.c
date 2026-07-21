#include <cb_engine/types.h>

#include <cb_runtime/bindings/lua_camera.h>
#include <cb_runtime/bindings/lua_node.h>
#include <cb_runtime/bindings/lua_scene.h>
#include <cb_runtime/core/runtime.h>

#include <lauxlib.h>
#include <string.h>

static i32 lua_scene_get_current(lua_State *L) {
  lua_push_scene(L, runtime_get_scene());
  return 1;
}

static i32 lua_scene_index(lua_State *L) {
  const char *key = luaL_checkstring(L, 2);
  Scene *scene = *(Scene **)luaL_checkudata(L, 1, "Scene");

  if (strcmp(key, "name") == 0) {
    lua_pushstring(L, scene->name);
    return 1;
  }

  if (strcmp(key, "root") == 0) {
    lua_push_node(L, scene->root);
    return 1;
  }

  if (strcmp(key, "camera") == 0) {
    lua_push_camera(L, &scene->camera);
    return 1;
  }

  return 0;
}

void lua_push_scene(lua_State *L, Scene *scene) {
  Scene **scene_data = lua_newuserdatauv(L, sizeof(Scene *), 0);
  *scene_data = scene;

  luaL_getmetatable(L, "Scene");
  lua_setmetatable(L, -2);
}


void lua_scene_bind(lua_State *L) {
  luaL_newmetatable(L, "Scene");

  lua_pushcfunction(L, lua_scene_index);
  lua_setfield(L, -2, "__index");

  lua_pop(L, 1);

  lua_newtable(L);
  lua_pushcfunction(L, lua_scene_get_current);
  lua_setfield(L, -2, "GetCurrent");

  lua_setglobal(L, "Scene");
}
