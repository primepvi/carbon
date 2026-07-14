#include <cb_engine/core/logger.h>
#include <cb_runtime/components/script.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <string.h>

Script script_new(const char *path, lua_State *lua_vm) {
  Script script = {0};
  script.path = strdup(path);
  script.ref = CB_INVALID_LUA_SCRIPT_REF;

  if (luaL_dofile(lua_vm, path) != LUA_OK) {
    CB_ERROR("Cannot load script at path %s.", path);
    return script;
  }

  script.ref = luaL_ref(lua_vm, LUA_REGISTRYINDEX);
  return script;
}

void script_destroy(Script *script, lua_State *lua_vm) {
  luaL_unref(lua_vm, LUA_REGISTRYINDEX, script->ref);
  free(script->path);
}
