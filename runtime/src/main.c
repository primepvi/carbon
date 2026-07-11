#include <cb_engine/core/application.h>

int main(void) {
  ApplicationConfig app_config = {
      .window_width = 800, .window_height = 600, .window_title = "Carbon"};

  Application app = application_new(app_config);
  application_init(&app);

  while (!application_should_close(&app)) {
    application_begin_frame(&app);

    renderer_draw_quad(app.renderer, VEC2(100.0f, 100.0f), VEC2(50, 50),
                       COLOR_WHITE);

    application_end_frame(&app);
  }

  application_destroy(&app);

  return 0;
}
