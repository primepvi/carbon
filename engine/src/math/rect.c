#include <cb_engine/math/rect.h>

b8 rect_contains(Rect rect, Vec2 point) {
  f32 left = rect.position.x;
  f32 right = rect.position.x + rect.size.x;
  f32 top = rect.position.y;
  f32 bottom = rect.position.y - rect.size.y;

  return point.x >= left && point.x <= right && point.y <= top &&
         point.y >= bottom;
}

b8 rect_intersects(Rect a, Rect b) {
  f32 a_left = a.position.x;
  f32 b_left = b.position.x;

  f32 a_right = a.position.x + a.size.x;
  f32 b_right = b.position.x + b.size.x;

  f32 a_top = a.position.y;
  f32 b_top = b.position.y;

  f32 a_bottom = a.position.y - a.size.y;
  f32 b_bottom = b.position.y - b.size.y;

  return a_right >= b_left && a_left <= b_right && a_top >= b_bottom &&
         a_bottom <= b_top;
}
