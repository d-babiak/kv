#include <stdbool.h>
#include <assert.h>
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


int wail(char *line) { 
  FILE* fp = fopen("the_keys.log", "a");
  int rc = fputs(line, fp);
  if (rc == EOF)
    exit(21);
  fclose(fp);
  return rc;
}


char * get_input(char *line) {
  printf("kv> ");
  return fgets(line, LINE_SIZE, stdin);
}

tree_node_t * handle_input(char *line, tree_node_t *root, bool persist) {
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
    // HOW DO WE MAKE ATOMIC? 
    root = set(root, key, val);
    if (persist)
      wail(line);
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

tree_node_t * boot(tree_node_t *root) {
  FILE *fp = fopen("the_keys.log", "r");
  assert(fp != NULL);
  char *line = malloc(LINE_SIZE);
  while ((line = fgets(line, LINE_SIZE, fp)) != NULL) {
    root = handle_input(line, root, false);
  }
  fclose(fp);
  return root;
}

int main(int argc, char *argv[]) {
  char *line = malloc(LINE_SIZE);
  tree_node_t *root = boot(NULL); 
  while (1) {
    line = get_input(line);
    root = handle_input(line, root, true);
  }
}
