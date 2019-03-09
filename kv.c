#include <stdlib.h>
#include <stdio.h>
#define LINE_SIZE 255

char * get_input(char *line) {
  printf("kv> ");
  return fgets(line, LINE_SIZE, stdin);
}

void handle_input(char *s) {
  if (NULL == s) {
      printf("NULL input\n");
      exit(0);
  }
  switch (*s) {
    case 'q':
      printf("Quitting...\n");
      exit(0);
    case 'z':
      printf("LOL zzzzzz\n");
      break;
    default: 
      printf("You said: %s", s);
  }
}

int main(int argc, char *argv[]) {
  char *line = malloc(LINE_SIZE);

  while (1) {
    line = get_input(line);
    handle_input(line);
  }
}
