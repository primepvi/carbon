#include <cb_engine/types.h>
#include <cb_runtime/bindings/lua_color.h>
#include <cb_runtime/bindings/lua_sprite.h>
#include <lauxlib.h>
#include <string.h>

static i32 lua_sprite_index(lua_State *L) {
  Sprite *sprite = *(Sprite **)luaL_checkudata(L, 1, "Sprite");
  const char *key = luaL_checkstring(L, 2);

  if (strcmp(key, "color") == 0) {
    lua_push_color_ptr(L, &sprite->color);
    return 1;
  }

  return 0;
}

static i32 lua_sprite_new_index(lua_State *L) {
  Sprite *sprite = *(Sprite **)luaL_checkudata(L, 1, "Sprite");
  const char *key = luaL_checkstring(L, 2);

  if (strcmp(key, "color") == 0) {
    LuaColor *color = luaL_checkudata(L, 3, "Color");
    sprite->color = *color->ptr;
  }

  return 0;
}

void lua_push_sprite(lua_State *L, Sprite *sprite) {
  Sprite **sprite_data = lua_newuserdatauv(L, sizeof(Sprite *), 0);
  *sprite_data = sprite;

  luaL_getmetatable(L, "Sprite");
  lua_setmetatable(L, -2);
}

void lua_sprite_bind(lua_State *L) {
  luaL_newmetatable(L, "Sprite");

  lua_pushcfunction(L, lua_sprite_index);
  lua_setfield(L, -2, "__index");

  lua_pushcfunction(L, lua_sprite_new_index);
  lua_setfield(L, -2, "__newindex");

  lua_pop(L, 1);
}
