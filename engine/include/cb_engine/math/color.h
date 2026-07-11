#ifndef CB_COLOR_H
#define CB_COLOR_H

#include "../types.h"

typedef struct {
  f32 red, green, blue, alpha;
} Color;

#define RGB(r, g, b) ((Color){(r), (g), (b), 1.0f})
#define RGBA(r, g, b, a) ((Color){(r), (g), (b), (a)})

#define COLOR_WHITE   ((Color){1, 1, 1, 1})
#define COLOR_BLACK   ((Color){0, 0, 0, 1})
#define COLOR_RED     ((Color){1, 0, 0, 1})
#define COLOR_GREEN   ((Color){0, 1, 0, 1})
#define COLOR_BLUE    ((Color){0, 0, 1, 1})
#define COLOR_YELLOW  ((Color){1, 1, 0, 1})
#define COLOR_CLEAR   ((Color){0.1f, 0.1f, 0.1f, 1})
#define COLOR_NONE ((Color){0, 0, 0, 0})

CB_API Color color_lerp(Color a, Color b, f32 t);

#endif
