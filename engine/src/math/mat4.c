#include <cb_engine/math/mat4.h>

#include <math.h>
#include <stddef.h>

// clang-format off
Mat4 mat4_identity(void) {
  return (Mat4) {{
      1.0f, 0, 0, 0,
      0, 1.0f, 0, 0,
      0, 0, 1.0f, 0,
      0, 0, 0, 1.0f
     }};
}

Mat4 mat4_translate(Mat4 mat, Vec2 vec) {  
  Mat4 translation = {{
      1.0f, 0, 0, 0,
      0, 1.0f, 0, 0,
      0, 0, 1.0f, 0 ,
      vec.x, vec.y, 0, 1.0f
  }};

  return mat4_mul(mat, translation);
}

Mat4 mat4_scale(Mat4 mat, Vec2 scale) {
  Mat4 s = (Mat4){{
      scale.x, 0, 0, 0,
      0, scale.y, 0, 0,
      0, 0, 1.0f, 0,
      0, 0, 0, 1.0f
  }};

  return mat4_mul(mat, s);
}

Mat4 mat4_rotate_z(Mat4 mat, f32 angle) {
  Mat4 r = (Mat4){{
      cosf(angle), sinf(angle), 0, 0,
      -sinf(angle), cosf(angle), 0, 0,
      0, 0, 1.0f, 0,
      0, 0, 0, 1.0f
  }};

  return mat4_mul(mat, r);
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
  Mat4 c = {0};

  for (u32 i = 0; i < 4; i++) {
    for (u32 j = 0; j < 4; j++) {
      for (u32 k = 0; k < 4; k++) {
        mat4_index(c, i, j) += mat4_index(a, i, k) * mat4_index(b, k, j);
      }
    }
  }

  return c;
}

Mat4 mat4_ortho(f32 l, f32 r, f32 b, f32 t) {
  f32 n = -1.0f;
  f32 f = 1.0f;
  
  return (Mat4){{
      2/(r-l), 0, 0, 0,
      0, 2/(t-b), 0, 0,
      0, 0, (-2)/(f-n), 0,
      -((r+l)/(r-l)), -((t+b)/(t-b)), -((f+n)/(f-n)), 1
  }};
}

Mat4 mat4_view(Vec2 pos, f32 z) {
  return (Mat4){{
      z, 0, 0, 0,
      0, z, 0, 0,
      0, 0, 1, 0,
      -pos.x * z, -pos.y * z, 0, 1
  }};
}

const f32 *mat4_ptr(const Mat4 *mat) { return &mat->data[0]; }
