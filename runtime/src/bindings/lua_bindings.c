#include <cb_runtime/bindings/lua_bindings.h>
#include <cb_runtime/bindings/lua_transform.h>
#include <cb_runtime/bindings/lua_input.h>
#include <cb_runtime/bindings/lua_vec2.h>
#include <cb_runtime/bindings/lua_node.h>

void lua_bind_enum(lua_State *L, const char *name, const LuaEnumValue *values) {
  lua_newtable(L);

  for (int i = 0; values[i].name != NULL; i++) {
    lua_pushinteger(L, values[i].value);
    lua_setfield(L, -2, values[i].name);
  }

  lua_setglobal(L, name);
}

void lua_bind(lua_State *L) {
  lua_vec2_bind(L);
  lua_transform_bind(L);
  lua_input_bind(L);
  lua_node_bind(L);
}
