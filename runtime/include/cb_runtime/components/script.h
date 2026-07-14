#ifndef CB_SCRIPT_H
#define CB_SCRIPT_H

#include <cb_runtime/components/component.h>
#include <lua.h>

#define CB_INVALID_LUA_SCRIPT_REF -1

typedef i32 LuaScriptReference;

typedef struct {
  char *path;
  LuaScriptReference ref;
} Script;

Script script_new(const char *path, lua_State *lua_vm);
void script_destroy(Script *script, lua_State *lua_vm);

#endif
