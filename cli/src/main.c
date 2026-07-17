#include <cb_engine/core/logger.h>

#include <cb_engine/core/application.h>
#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/assets.h>
#include <cb_runtime/core/node.h>
#include <cb_runtime/core/runtime.h>
#include <cb_runtime/core/scene.h>

#include <cJSON.h>
#include <stdio.h>
#include <stdlib.h>

static const char *read_json_file(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    CB_ERROR("Cannot open json file at: '%s'", path);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  u32 len = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(len + 1);
  if (buffer == NULL) {
    CB_ERROR("Cannot allocate buffer to read json source.");
    return NULL;
  }

  fread(buffer, 1, len, file);
  fclose(file);

  buffer[len] = '\0';

  return buffer;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    CB_FATAL("Missing project path.");
  }

  char *project_path = argv[1];
  const char *project_source = read_json_file(project_path);
  cJSON *project_json = cJSON_Parse(project_source);

  cJSON *project_name = cJSON_GetObjectItem(project_json, "name");
  cJSON *project_scene = cJSON_GetObjectItem(project_json, "scene");

  CB_INFO("Loading project %s...", project_name->valuestring);

  ApplicationConfig app_config = {.window_width = 800,
                                  .window_height = 600,
                                  .window_title = project_name->valuestring};

  Application app = application_new(app_config);
  application_init(&app);
  runtime_init(&app);

  Camera camera = camera_create(
      VEC2(0, 0), VEC2(app_config.window_width, app_config.window_height));
  Scene *scene =
      scene_from_json(runtime_get_assets(), camera, project_scene->valuestring);
  runtime_set_scene(scene);

  CB_INFO("Project %s has been loaded.", project_name->valuestring);

  while (!application_should_close(&app)) {
    application_begin_frame(&app);
    runtime_run();
    application_end_frame(&app);
  }

  application_destroy(&app);

  return 0;
}
