#include <cb_runtime/components/component.h>
#include <cb_runtime/core/node.h>

#include <stdlib.h>
#include <string.h>

Node *node_new(Node *parent, const char *name) {
  Node *node = malloc(sizeof(Node));
  node->parent = parent;
  node->name = strdup(name);

  node->childrens = array_list_new(32, sizeof(Node));
  node->components = array_list_new(32, sizeof(Component));

  return node;
}

void node_destroy(Node *node) {
  for (u32 i = 0; i < array_list_length(node->childrens); i++) {
    Node *current = array_list_at(node->childrens, i);
    node_destroy(current);
  }

  array_list_destroy(node->childrens);
  array_list_destroy(node->components);
  free(node->name);
  free(node);
}

void node_push_children(Node *node, Node *children) {
  array_list_push(node->childrens, children);
}

void node_push_component(Node *node, ComponentKind kind,
                         ComponentHandle handle) {
  array_list_push(node->components, &(Component){kind, handle});
}
