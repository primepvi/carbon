#ifndef CB_CAMERA_H
#define CB_CAMERA_H

#include <cb_engine/math/vec2.h>
#include <cb_engine/math/mat4.h>

typedef struct {
  Vec2 position, viewport;
  f32 zoom;
  
  Mat4 view;
  Mat4 projection;
} Camera;

Camera camera_create(Vec2 position, Vec2 window_dimensions);

void camera_set_viewport(Camera *camera, Vec2 viewport);
void camera_set_position(Camera *camera, Vec2 position);
void camera_set_zoom(Camera *camera, f32 zoom);

#endif
