#include <cb_engine/math/color.h>
#include <cb_engine/types.h>
#include <cb_runtime/bindings/lua_color.h>

#include <lauxlib.h>
#include <string.h>

static i32 lua_color_rgb(lua_State *L) {
  f32 r = luaL_checknumber(L, 1);
  f32 g = luaL_checknumber(L, 2);
  f32 b = luaL_checknumber(L, 3);
  lua_push_color(L, RGB(r, g, b));

  return 1;
}

static i32 lua_color_rgba(lua_State *L) {
  f32 r = luaL_checknumber(L, 1);
  f32 g = luaL_checknumber(L, 2);
  f32 b = luaL_checknumber(L, 3);
  f32 a = luaL_checknumber(L, 4);
  lua_push_color(L, RGBA(r, g, b, a));

  return 1;
}

static i32 lua_color_index(lua_State *L) {
  LuaColor *color = luaL_checkudata(L, 1, "Color");
  const char *key = luaL_checkstring(L, 2);

  if (strcmp(key, "red") == 0) {
    lua_pushnumber(L, color->ptr->red);
    return 1;
  }

  if (strcmp(key, "green") == 0) {
    lua_pushnumber(L, color->ptr->green);
    return 1;
  }

  if (strcmp(key, "blue") == 0) {
    lua_pushnumber(L, color->ptr->blue);
    return 1;
  }

  if (strcmp(key, "alpha") == 0) {
    lua_pushnumber(L, color->ptr->alpha);
    return 1;
  }

  return 0;
}

static i32 lua_color_new_index(lua_State *L) {
  LuaColor *color = luaL_checkudata(L, 1, "Color");
  const char *key = luaL_checkstring(L, 2);
  f32 value = luaL_checknumber(L, 3);

  if (strcmp(key, "red") == 0)
    color->ptr->red = value;
  else if (strcmp(key, "green") == 0)
    color->ptr->green = value;
  else if (strcmp(key, "blue") == 0)
    color->ptr->blue = value;
  else if (strcmp(key, "alpha") == 0)
    color->ptr->alpha = value;

  return 0;
}

void lua_push_color(lua_State *L, Color color) {
  LuaColor *data = lua_newuserdatauv(L, sizeof(LuaColor), 0);
  data->value = color;
  data->ptr = &data->value;

  luaL_getmetatable(L, "Color");
  lua_setmetatable(L, -2);
}

void lua_push_color_ptr(lua_State *L, Color *color) {
  LuaColor *data = lua_newuserdatauv(L, sizeof(LuaColor), 0);
  data->ptr = color;

  luaL_getmetatable(L, "Color");
  lua_setmetatable(L, -2);
}

void lua_color_bind(lua_State *L) {
  luaL_newmetatable(L, "Color");

  lua_pushcfunction(L, lua_color_index);
  lua_setfield(L, -2, "__index");

  lua_pushcfunction(L, lua_color_new_index);
  lua_setfield(L, -2, "__newindex");

  lua_pop(L, 1);

  lua_newtable(L);
  lua_pushcfunction(L, lua_color_rgb);
  lua_setfield(L, -2, "FromRGB");

  lua_pushcfunction(L, lua_color_rgba);
  lua_setfield(L, -2, "FromRGBA");

  lua_setglobal(L, "Color");
}
