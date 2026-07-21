#ifndef CB_LUA_COLOR_H
#define CB_LUA_COLOR_H

#include <cb_engine/math/color.h>
#include <lua.h>

typedef struct {
  Color *ptr;
  Color value;
} LuaColor;

void lua_push_color(lua_State *L, Color color);
void lua_push_color_ptr(lua_State *L, Color *color);
void lua_color_bind(lua_State *L);

#endif
