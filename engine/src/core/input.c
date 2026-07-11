#include "input.h"

Input input = {0};

void input_begin_frame(void) {
  for (i32 i = 0; i < INPUT_KEY_COUNT; i++) {
    input.keys[i].previous = input.keys[i].current;
  }

  for (i32 i = 0; i < INPUT_MOUSE_BUTTON_COUNT; i++) {
    input.mouse[i].previous = input.mouse[i].current;
  }

  input.mouse_delta = VEC2(0.0f, 0.0f);
}

Input *input_get_instance(void) { return &input; }
b8 input_key_down(InputKey key) { return input.keys[key].current; }
b8 input_key_pressed(InputKey key) {
  return input.keys[key].current && !input.keys[key].previous;
}
b8 input_key_released(InputKey key) {
  return !input.keys[key].current && input.keys[key].previous;
}

b8 input_mouse_btn_down(InputMouseButton btn) {
  return input.mouse[btn].current;
}
b8 input_mouse_btn_pressed(InputMouseButton btn) {
  return input.mouse[btn].current && !input.mouse[btn].previous;
}
b8 input_mouse_btn_released(InputMouseButton btn) {
  return !input.mouse[btn].current && input.mouse[btn].previous;
}

Vec2 input_mouse_get_pos(void) { return input.mouse_pos; }
Vec2 input_mouse_get_delta(void) { return input.mouse_delta; }
