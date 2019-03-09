#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tree_node_t {
  char *key;
  char *val;
  struct tree_node_t *left;
  struct tree_node_t *right;
} tree_node_t;

void traverse(tree_node_t *node) {
  if (NULL == node)
    return;
  traverse(node->left);
  printf("%s -> %s\n", node->key, node->val);
  traverse(node->right);
}

tree_node_t * create_tree_node(char *key, char *val) {
  tree_node_t *tn = malloc(sizeof(tree_node_t));
  tn->key = strdup(key);
  tn->val = strdup(val);
  tn->left = NULL;
  tn->right = NULL;
  return tn;
}

char * get(tree_node_t *root, char *key) {
  if (NULL == root)
    return NULL;

  int rc = strcmp(root->key, key);

  if (rc < 0) {
    return get(root->right, key);
  } else if (rc > 0) {
    return get(root->left, key);
  } else {
    return root->val;
  }
}

tree_node_t * set(tree_node_t *root, char *key, char *val) {
  if (NULL == root)
    return create_tree_node(key, val);

  int rc = strcmp(root->key, key);

  if (rc < 0) {
    root->right = set(root->right, key, val);
  } else if (rc > 0) {
    root->left = set(root->left, key, val);
  } else {
    root->val = strdup(val);
  }
  return root;
}

//int main() {
//  char c[2];
//  tree_node_t *root = NULL;
//  for (int i = 0; i < 10; i++) {
//    c[0] = '0' + (i % 2 == 0 ? 1 : -1) * i; 
//    root = set(root, c, c);
//  }
//  traverse(root);
//}
