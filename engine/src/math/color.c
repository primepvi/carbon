#include <cb_engine/math/color.h>
#include <cb_engine/math/utils.h>

Color color_lerp(Color a, Color b, f32 t) {
  return (Color){.red = LERP(a.red, b.red, t),
                 .blue = LERP(a.blue, b.blue, t),
                 .green = LERP(a.green, b.green, t),
                 .alpha = LERP(a.alpha, b.alpha, t)};
}
