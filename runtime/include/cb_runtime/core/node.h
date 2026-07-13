#ifndef CB_NODE_H
#define CB_NODE_H

#include <cb_engine/core/array_list.h>
#include <cb_engine/types.h>
#include <cb_runtime/components/component.h>

typedef struct Node {
  char *name;

  struct Node *parent;

  ArrayList *childrens;
  ArrayList *components;
} Node;

Node *node_new(Node *parent, const char *name);
void node_destroy(Node *node);

void node_push_children(Node *node, Node *children);
void node_push_component(Node *node, ComponentKind kind,
                         ComponentHandle handle);

#endif
