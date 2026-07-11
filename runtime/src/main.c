#include <cb_runtime/core/application.h>

void update(f64 delta_time) {}
void draw(Renderer *renderer) {}

int main(void) {
  ApplicationConfig app_config = {.window_width = 800,
                                  .window_height = 600,
                                  .window_title = "Carbon",
                                  .update = update,
                                  .draw = draw};

  Application app = application_new(app_config);
  application_init(&app);
  application_run(&app);
  application_destroy(&app);

  return 0;
}
