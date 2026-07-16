#ifndef CB_LUA_NODE_H
#define CB_LUA_NODE_H

#include <cb_runtime/core/node.h>
#include <lua.h>

void lua_push_node(lua_State *L, Node *node);
void lua_node_bind(lua_State *L);

#endif
