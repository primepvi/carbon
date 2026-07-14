#include <cb_runtime/core/runtime.h>
#include <lauxlib.h>

struct {
  Application *app;
  Assets *assets;
  Scene *scene;
  lua_State *lua_vm;
} _state;

void runtime_init(Application *app, const char *scene_name) {
  _state.app = app;
  _state.assets = assets_new();
  _state.scene = scene_new(scene_name);
  _state.lua_vm = luaL_newstate();
}

void runtime_run(void) {
  scene_render(_state.scene, application_get_renderer(_state.app));
}

Assets *runtime_get_assets(void) { return _state.assets; }
Scene *runtime_get_scene(void) { return _state.scene; }
lua_State *runtime_get_luavm(void) { return _state.lua_vm; }
