#ifndef CB_COMPONENT_H
#define CB_COMPONENT_H

#include <cb_engine/types.h>

#define CB_INVALID_HANDLE -1

typedef enum {
  COMPONENT_INVALID = -1,
  COMPONENT_TEXTURE,
  COMPONENT_SPRITE,
  COMPONENT_SCRIPT,
} ComponentKind;

typedef i32 ComponentHandle;
typedef i32 TextureHandle;
typedef i32 ScriptHandle;
typedef i32 SpriteHandle;

typedef struct {
  ComponentKind kind;
  ComponentHandle handle;
} Component;

#endif
