#include <cb_engine/core/logger.h>

#include <cb_engine/core/application.h>
#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/assets.h>
#include <cb_runtime/core/node.h>
#include <cb_runtime/core/runtime.h>
#include <cb_runtime/core/scene.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    CB_FATAL("Missing scene path.");
  }

  char *scene_path = argv[1];

  ApplicationConfig app_config = {
      .window_width = 800, .window_height = 600, .window_title = "Carbon"};

  Application app = application_new(app_config);
  application_init(&app);
  runtime_init(&app);
  
  Scene *scene = scene_from_json(runtime_get_assets(), scene_path);
  runtime_set_scene(scene);
  
  while (!application_should_close(&app)) {
    application_begin_frame(&app);
    runtime_run();
    application_end_frame(&app);
  }

  application_destroy(&app);

  return 0;
}
