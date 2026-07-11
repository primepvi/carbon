#ifndef CB_VEC2_H
#define CB_VEC2_H

#include "../types.h"

#define VEC2(x, y) ((Vec2){(x), (y)})
#define VEC2_ZERO ((Vec2){0.0f, 0.0f})
#define VEC2_ONE ((Vec2){1.0f, 1.0f})

typedef struct {
  f32 x, y;
} Vec2;

CB_API Vec2 vec2_negate(Vec2 vec);
CB_API Vec2 vec2_from_angle(f32 rad);
CB_API Vec2 vec2_normalize(Vec2 vec);
CB_API f32 vec2_magnitude(Vec2 vec);
CB_API f32 vec2_angle(Vec2 vec);

CB_API Vec2 vec2_add(Vec2 a, Vec2 b);
CB_API Vec2 vec2_sub(Vec2 a, Vec2 b);
CB_API Vec2 vec2_scale(Vec2 vec, f32 scalar);

// Projects b onto â. Assumed that a is normalized.
CB_API Vec2 vec2_vector_projection(Vec2 a, Vec2 b);

// Projects b onto â. Assumed that a is normalized.
CB_API f32 vec2_scalar_projection(Vec2 a, Vec2 b);

CB_API f32 vec2_dot(Vec2 a, Vec2 b);
CB_API f32 vec2_distance(Vec2 a, Vec2 b);

#endif
