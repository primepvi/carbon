#ifndef CB_RUNTIME_H
#define CB_RUNTIME_H

#include <cb_engine/core/application.h>
#include <cb_runtime/core/scene.h>
#include <cb_runtime/core/assets.h>
#include <lua.h>

CB_API void runtime_init(Application *app);
CB_API void runtime_set_scene(Scene *scene);
CB_API void runtime_run(void);

CB_API Assets *runtime_get_assets(void);
CB_API Scene *runtime_get_scene(void);
CB_API lua_State *runtime_get_luavm(void);
CB_API Application *runtime_get_application(void);

#endif
