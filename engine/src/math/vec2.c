#include <cb_engine/math/vec2.h>
#include <math.h>

Vec2 vec2_negate(Vec2 vec) { return VEC2(-vec.x, -vec.y); }
Vec2 vec2_from_angle(f32 rad) { return VEC2(cosf(rad), sinf(rad)); }
Vec2 vec2_normalize(Vec2 vec) {
  f32 mag = vec2_magnitude(vec);
  if (mag < 1e-6f) {
    return VEC2_ZERO;
  }

  return VEC2(vec.x / mag, vec.y / mag);
}

f32 vec2_magnitude(Vec2 vec) { return sqrtf(vec.x * vec.x + vec.y * vec.y); }
f32 vec2_angle(Vec2 vec) { return atan2f(vec.y, vec.x); }

Vec2 vec2_add(Vec2 a, Vec2 b) { return VEC2(a.x + b.x, a.y + b.y); }
Vec2 vec2_sub(Vec2 a, Vec2 b) { return VEC2(a.x - b.x, a.y - b.y); }
Vec2 vec2_scale(Vec2 vec, float scalar) {
  return VEC2(vec.x * scalar, vec.y * scalar);
}

// Projects b onto â. Assumed that a is normalized.
Vec2 vec2_vector_projection(Vec2 a, Vec2 b) {
  f32 scalar = vec2_dot(a, b);
  return vec2_scale(a, scalar);
}

// Projects b onto â. Assumed that a is normalized.
f32 vec2_scalar_projection(Vec2 a, Vec2 b) {
  return vec2_dot(a, b);
}

f32 vec2_dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }
f32 vec2_distance(Vec2 a, Vec2 b) {
  Vec2 diff = vec2_sub(b, a);
  return vec2_magnitude(diff);
}
