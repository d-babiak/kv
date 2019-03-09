#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define LINE_SIZE 255

#include "tree_map.c"

bool starts_with(char *s, char *prefix) { 
  while (*s && *prefix && *s == *prefix) {
    s++;
    prefix++;
  }
  return *prefix == '\0';
}

char * get_input(char *line) {
  printf("kv> ");
  return fgets(line, LINE_SIZE, stdin);
}

tree_node_t * handle_input(char *line, tree_node_t *root) {
  if (NULL == line) {
      printf("NULL input\n");
      exit(0);
  }

  char *key = malloc(255); 

  if (starts_with(line, "get ")) {
    sscanf(line, "get %s", key);
    //printf("GET %s -> %s\n", key, get(root, key));
    printf("%s\n", get(root, key));
    return root;
  }

  if (starts_with(line, "set ")) {
    char *val = malloc(255); 
    sscanf(line, "set %s %s", key, val);
    root = set(root, key, val);
    printf("%s -> %s\n", key, get(root, key));
    return root;
  }

  if (starts_with(line, "quit")) {
    printf("Goodbye\n");
    exit(0);
  }

  printf("wtf\n");
  return root;
}

//int main() {
//  char *key = malloc(LINE_SIZE);
//  char *val = malloc(LINE_SIZE);
//  sscanf("set foo bar", "set %s %s", key, val);
//  printf("key: %s, val: %s\n", key, val);
//}

int main(int argc, char *argv[]) {
  char *line = malloc(LINE_SIZE);
  tree_node_t *root = NULL; 

  while (1) {
    line = get_input(line);
    root = handle_input(line, root);
  }
}
