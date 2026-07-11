#ifndef CB_MAT4_H
#define CB_MAT4_H

#include "vec2.h"
#include "../types.h"

#define mat4_index(mat, row, col) ((mat).data[(col) * 4 + (row)])

// linear column-major matrix
typedef struct {
  f32 data[16];
} Mat4;

CB_API Mat4 mat4_identity(void);
CB_API Mat4 mat4_translate(Mat4 mat, Vec2 vec);
CB_API Mat4 mat4_scale(Mat4 mat, Vec2 scale);
CB_API Mat4 mat4_rotate_z(Mat4 mat, f32 angle);
CB_API Mat4 mat4_mul(Mat4 a, Mat4 b);
CB_API Mat4 mat4_ortho(f32 left, f32 right, f32 bottom, f32 top);
CB_API Mat4 mat4_view(Vec2 pos, f32 zoom);

const f32* mat4_ptr(const Mat4 *mat);

#endif
