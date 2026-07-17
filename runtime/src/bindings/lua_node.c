#include <cb_runtime/bindings/lua_node.h>
#include <cb_runtime/bindings/lua_transform.h>
#include <cb_runtime/core/runtime.h>

#include <lauxlib.h>
#include <string.h>

static i32 lua_node_find_component(lua_State *L) {
  Node *node = luaL_checkudata(L, 1, "Node");
  const char *component_name = luaL_checkstring(L, 2);

  Assets *assets = runtime_get_assets();

  if (strcmp(component_name, "Transform") == 0) {
    ComponentHandle handle = node_find_component(node, COMPONENT_TRANSFORM);
    Transform *transform = assets_get_transform(assets, handle);
    lua_push_transform(L, transform);

    return 1;
  }

  return 0;
}

static i32 lua_node_index(lua_State *L) {
  Node *node = luaL_checkudata(L, 1, "Node");
  const char *key = luaL_checkstring(L, 2);

  if (strcmp(key, "name") == 0) {
    lua_pushstring(L, node->name);
    return 1;
  }

  if (strcmp(key, "parent") == 0) {
    lua_push_node(L, scene_get_node(runtime_get_scene(), node->parent));
    return 1;
  }

  if (strcmp(key, "FindComponent") == 0) {
    lua_pushcfunction(L, lua_node_find_component);
    return 1;
  }
  
  return 0;
}

void lua_push_node(lua_State *L, Node *node) {
  if (node == NULL)
    return lua_pushnil(L);

  Node *node_data = lua_newuserdatauv(L, sizeof(Node), 0);
  *node_data = *node;

  luaL_getmetatable(L, "Node");
  lua_setmetatable(L, -2);
}

void lua_node_bind(lua_State *L) {
  luaL_newmetatable(L, "Node");

  lua_pushcfunction(L, lua_node_index);
  lua_setfield(L, -2, "__index");

  lua_pop(L, 1);
}
