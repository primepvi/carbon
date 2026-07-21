#ifndef CB_LUA_CAMERA_H
#define CB_LUA_CAMERA_H

#include <cb_runtime/core/camera.h>
#include <lua.h>

void lua_push_camera(lua_State *L, Camera *camera);
void lua_camera_bind(lua_State *L);

#endif
