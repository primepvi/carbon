#ifndef CB_RUNTIME_H
#define CB_RUNTIME_H

#include <cb_engine/core/application.h>
#include <cb_runtime/core/scene.h>
#include <cb_runtime/core/assets.h>
#include <lua.h>

void runtime_init(Application *app, const char *scene_name);
void runtime_run(void);

Assets *runtime_get_assets(void);
Scene *runtime_get_scene(void);
lua_State *runtime_get_luavm(void);

#endif
