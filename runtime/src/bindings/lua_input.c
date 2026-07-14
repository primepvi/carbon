#include <cb_engine/core/input.h>
#include <cb_runtime/bindings/lua_bindings.h>
#include <cb_runtime/bindings/lua_input.h>

#include <lauxlib.h>
#include <lua.h>

static const LuaEnumValue LUA_INPUT_KEYS_ENUM[] = {
    {"Unknown", INPUT_KEY_UNKNOWN},

    // Letters
    {"A", INPUT_KEY_A},
    {"B", INPUT_KEY_B},
    {"C", INPUT_KEY_C},
    {"D", INPUT_KEY_D},
    {"E", INPUT_KEY_E},
    {"F", INPUT_KEY_F},
    {"G", INPUT_KEY_G},
    {"H", INPUT_KEY_H},
    {"I", INPUT_KEY_I},
    {"J", INPUT_KEY_J},
    {"K", INPUT_KEY_K},
    {"L", INPUT_KEY_L},
    {"M", INPUT_KEY_M},
    {"N", INPUT_KEY_N},
    {"O", INPUT_KEY_O},
    {"P", INPUT_KEY_P},
    {"Q", INPUT_KEY_Q},
    {"R", INPUT_KEY_R},
    {"S", INPUT_KEY_S},
    {"T", INPUT_KEY_T},
    {"U", INPUT_KEY_U},
    {"V", INPUT_KEY_V},
    {"W", INPUT_KEY_W},
    {"X", INPUT_KEY_X},
    {"Y", INPUT_KEY_Y},
    {"Z", INPUT_KEY_Z},

    // Numbers
    {"Num0", INPUT_KEY_0},
    {"Num1", INPUT_KEY_1},
    {"Num2", INPUT_KEY_2},
    {"Num3", INPUT_KEY_3},
    {"Num4", INPUT_KEY_4},
    {"Num5", INPUT_KEY_5},
    {"Num6", INPUT_KEY_6},
    {"Num7", INPUT_KEY_7},
    {"Num8", INPUT_KEY_8},
    {"Num9", INPUT_KEY_9},

    // Symbols
    {"Grave", INPUT_KEY_GRAVE},
    {"Minus", INPUT_KEY_MINUS},
    {"Equal", INPUT_KEY_EQUAL},
    {"LeftBracket", INPUT_KEY_LEFT_BRACKET},
    {"RightBracket", INPUT_KEY_RIGHT_BRACKET},
    {"Backslash", INPUT_KEY_BACKSLASH},
    {"Semicolon", INPUT_KEY_SEMICOLON},
    {"Apostrophe", INPUT_KEY_APOSTROPHE},
    {"Comma", INPUT_KEY_COMMA},
    {"Period", INPUT_KEY_PERIOD},
    {"Slash", INPUT_KEY_SLASH},

    // Control
    {"Escape", INPUT_KEY_ESCAPE},
    {"Enter", INPUT_KEY_ENTER},
    {"Tab", INPUT_KEY_TAB},
    {"Backspace", INPUT_KEY_BACKSPACE},
    {"Insert", INPUT_KEY_INSERT},
    {"Delete", INPUT_KEY_DELETE},
    {"Home", INPUT_KEY_HOME},
    {"End", INPUT_KEY_END},
    {"PageUp", INPUT_KEY_PAGE_UP},
    {"PageDown", INPUT_KEY_PAGE_DOWN},
    {"Space", INPUT_KEY_SPACE},

    // Arrows
    {"Left", INPUT_KEY_LEFT},
    {"Right", INPUT_KEY_RIGHT},
    {"Up", INPUT_KEY_UP},
    {"Down", INPUT_KEY_DOWN},

    // Mods
    {"LeftShift", INPUT_KEY_LEFT_SHIFT},
    {"RightShift", INPUT_KEY_RIGHT_SHIFT},
    {"LeftControl", INPUT_KEY_LEFT_CONTROL},
    {"RightControl", INPUT_KEY_RIGHT_CONTROL},
    {"LeftAlt", INPUT_KEY_LEFT_ALT},
    {"RightAlt", INPUT_KEY_RIGHT_ALT},
    {"LeftSuper", INPUT_KEY_LEFT_SUPER},
    {"RightSuper", INPUT_KEY_RIGHT_SUPER},
    {"Menu", INPUT_KEY_MENU},

    // Locks
    {"CapsLock", INPUT_KEY_CAPS_LOCK},
    {"NumLock", INPUT_KEY_NUM_LOCK},
    {"ScrollLock", INPUT_KEY_SCROLL_LOCK},

    // Functions
    {"F1", INPUT_KEY_F1},
    {"F2", INPUT_KEY_F2},
    {"F3", INPUT_KEY_F3},
    {"F4", INPUT_KEY_F4},
    {"F5", INPUT_KEY_F5},
    {"F6", INPUT_KEY_F6},
    {"F7", INPUT_KEY_F7},
    {"F8", INPUT_KEY_F8},
    {"F9", INPUT_KEY_F9},
    {"F10", INPUT_KEY_F10},
    {"F11", INPUT_KEY_F11},
    {"F12", INPUT_KEY_F12},

    // Numeric Keyboard
    {"KP0", INPUT_KEY_KP_0},
    {"KP1", INPUT_KEY_KP_1},
    {"KP2", INPUT_KEY_KP_2},
    {"KP3", INPUT_KEY_KP_3},
    {"KP4", INPUT_KEY_KP_4},
    {"KP5", INPUT_KEY_KP_5},
    {"KP6", INPUT_KEY_KP_6},
    {"KP7", INPUT_KEY_KP_7},
    {"KP8", INPUT_KEY_KP_8},
    {"KP9", INPUT_KEY_KP_9},

    {"KPDecimal", INPUT_KEY_KP_DECIMAL},
    {"KPDivide", INPUT_KEY_KP_DIVIDE},
    {"KPMultiply", INPUT_KEY_KP_MULTIPLY},
    {"KPSubtract", INPUT_KEY_KP_SUBTRACT},
    {"KPAdd", INPUT_KEY_KP_ADD},
    {"KPEnter", INPUT_KEY_KP_ENTER},
    {"KPEqual", INPUT_KEY_KP_EQUAL},

    {NULL, 0}};

static const LuaEnumValue LUA_INPUT_MOUSE_BUTTONS_ENUM[] = {
    {"Left", INPUT_MOUSE_BUTTON_LEFT},
    {"Right", INPUT_MOUSE_BUTTON_RIGHT},
    {"Middle", INPUT_MOUSE_BUTTON_MIDDLE},

    {"Button4", INPUT_MOUSE_BUTTON_4},
    {"Button5", INPUT_MOUSE_BUTTON_5},
    {"Button6", INPUT_MOUSE_BUTTON_6},
    {"Button7", INPUT_MOUSE_BUTTON_7},
    {"Button8", INPUT_MOUSE_BUTTON_8},

    {NULL, 0}};

static i32 lua_input_key_pressed(lua_State *L) {
  InputKey key = luaL_checkinteger(L, 1);
  b8 result = input_key_pressed(key);
  lua_pushboolean(L, result);

  return 1;
}

static i32 lua_input_key_down(lua_State *L) {
  InputKey key = luaL_checkinteger(L, 1);
  b8 result = input_key_down(key);
  lua_pushboolean(L, result);

  return 1;
}

static i32 lua_input_key_released(lua_State *L) {
  InputKey key = luaL_checkinteger(L, 1);
  b8 result = input_key_released(key);
  lua_pushboolean(L, result);

  return 1;
}

static i32 lua_input_mouse_btn_pressed(lua_State *L) {
  InputMouseButton btn = luaL_checkinteger(L, 1);
  b8 result = input_mouse_btn_pressed(btn);
  lua_pushboolean(L, result);

  return 1;
}

static i32 lua_input_mouse_btn_down(lua_State *L) {
  InputMouseButton btn = luaL_checkinteger(L, 1);
  b8 result = input_mouse_btn_down(btn);
  lua_pushboolean(L, result);

  return 1;
}

static i32 lua_input_mouse_btn_released(lua_State *L) {
  InputMouseButton btn = luaL_checkinteger(L, 1);
  b8 result = input_mouse_btn_released(btn);
  lua_pushboolean(L, result);

  return 1;
}

void lua_bind_input_table(lua_State *L) {
  lua_newtable(L);

  lua_pushcfunction(L, lua_input_key_pressed);
  lua_setfield(L, -2, "KeyPressed");

  lua_pushcfunction(L, lua_input_key_down);
  lua_setfield(L, -2, "KeyDown");

  lua_pushcfunction(L, lua_input_key_released);
  lua_setfield(L, -2, "KeyReleased");

  lua_pushcfunction(L, lua_input_mouse_btn_pressed);
  lua_setfield(L, -2, "MouseButtonPressed");

  lua_pushcfunction(L, lua_input_mouse_btn_down);
  lua_setfield(L, -2, "MouseButtonDown");

  lua_pushcfunction(L, lua_input_mouse_btn_released);
  lua_setfield(L, -2, "MouseButtonReleased");

  lua_setglobal(L, "Input");
}

void lua_input_bind(lua_State *L) {
  lua_bind_enum(L, "Keys", LUA_INPUT_KEYS_ENUM);
  lua_bind_enum(L, "MouseButton", LUA_INPUT_MOUSE_BUTTONS_ENUM);
  lua_bind_input_table(L);
}
