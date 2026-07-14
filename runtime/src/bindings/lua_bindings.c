#include <cb_runtime/bindings/lua_bindings.h>
#include <cb_runtime/bindings/lua_input.h>

void lua_bind_enum(lua_State *L, const char *name, const LuaEnumValue *values) {
  lua_newtable(L);

  for (int i = 0; values[i].name != NULL; i++) {
    lua_pushinteger(L, values[i].value);
    lua_setfield(L, -2, values[i].name);
  }

  lua_setglobal(L, name);
}

void lua_bind(lua_State *L) { lua_input_bind(L); }
