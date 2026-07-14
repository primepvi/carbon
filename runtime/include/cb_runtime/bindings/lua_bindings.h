#ifndef CB_LUA_BINDINGS_H
#define CB_LUA_BINDINGS_H

#include <lua.h>

typedef struct {
    const char *name;
    int value;
} LuaEnumValue;

void lua_bind(lua_State *L);
void lua_bind_enum(lua_State *L, const char *name, const LuaEnumValue *values);

#endif
