#ifndef LIST_MAP_H
#define LIST_MAP_H

#include <stdbool.h>
#include <pthread.h>

typedef struct M_node {
  char *k;
  char *v;
  struct M_node *next;
} M_node;

typedef struct list_map {
  pthread_mutex_t *mutex;
  M_node *head;
  M_node *tail;
} Map;

Map *M_init();

void M_lock(Map *m);

void M_unlock(Map *m);

M_node *M_get_node(Map *m, char *k);

void M_set(Map *m, char *k, char *v);

char *M_get(Map *m, char *k);

bool M_has_key(Map *m, char *k);

void M_print_node(M_node *N);

void M_print(Map *m);

#endif
