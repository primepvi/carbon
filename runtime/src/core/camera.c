#include <cb_runtime/core/camera.h>

Camera camera_create(Vec2 position, Vec2 viewport) {
  Mat4 projection = mat4_ortho(0, viewport.x, 0, viewport.y);
  Mat4 view = mat4_view(position, 1.0f);

  return (Camera){.position = position,
                  .viewport = viewport,
                  .zoom = 1.0f,
                  .projection = projection,
                  .view = view};
}

void camera_set_viewport(Camera *camera, Vec2 viewport) {
  camera->projection = mat4_ortho(0, viewport.x, 0, viewport.y);
  camera->viewport = viewport;
}

void camera_set_position(Camera *camera, Vec2 position) {
  camera->view = mat4_view(position, camera->zoom);
  camera->position = position;
}

void camera_set_zoom(Camera *camera, f32 zoom) {
  camera->view = mat4_view(camera->position, zoom);
  camera->zoom = zoom;
}
