#include <cb_runtime/bindings/lua_bindings.h>
#include <cb_runtime/core/runtime.h>
#include <lauxlib.h>
#include <lualib.h>

struct {
  Application *app;
  Assets *assets;
  Scene *scene;
  lua_State *lua_vm;
} _state;

void runtime_init(Application *app) {
  _state.app = app;
  _state.assets = assets_new();
  _state.scene = NULL;
  _state.lua_vm = luaL_newstate();

  luaL_openlibs(_state.lua_vm);
  lua_bind(_state.lua_vm);
}

void runtime_set_scene(Scene *scene) { _state.scene = scene; }

void runtime_run(void) {
  Platform *platform = _state.app->platform;
  Camera *camera = scene_get_camera(_state.scene);
  camera_set_viewport(camera, VEC2(platform->width, platform->height));

  scene_update(_state.scene);
  scene_physics_update(_state.scene);
  scene_draw(_state.scene, application_get_renderer(_state.app));
}

Assets *runtime_get_assets(void) { return _state.assets; }
Scene *runtime_get_scene(void) { return _state.scene; }
lua_State *runtime_get_luavm(void) { return _state.lua_vm; }
Application *runtime_get_application(void) { return _state.app; }
