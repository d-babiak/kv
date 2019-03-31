#include "list_map.h"
#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*
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
*/

Map *M_init() {
  Map *m = malloc(sizeof(Map));
  assert(0 == pthread_mutex_init(m->mutex, NULL));
  m->head = NULL;
  m->tail = NULL;
  return m;
}

void M_lock(Map *m) {
  assert(pthread_mutex_lock(m->mutex) == 0);
}

void M_unlock(Map *m) {
  assert(pthread_mutex_unlock(m->mutex) == 0);
}

M_node *M_get_node(Map *m, char *k) {
  M_lock(m);

  if (m->head == NULL) {
    M_unlock(m);
    return NULL;
  }

  for (M_node *N = m->head; N != NULL; N = N->next) {
    if (strcmp(N->k, k) == 0) {
      M_unlock(m);
      return N;
    }
  }
  M_unlock(m);
  return NULL;
}

void M_set(Map *m, char *k, char *v) {
  M_node *N = M_get_node(m, k);
  if (N !=  NULL) {
    N->v = strdup(v);
  }
  else {
    // AHHHHH - race condition
    M_lock(m);
    N = malloc(sizeof(M_node));
    N->k = strdup(k);
    N->v = strdup(v);
    N->next = m->head;
    m->head = N;
    M_unlock(m);
  }
}

char *M_get(Map *m, char *k) {
  M_lock(m);

  if (m->head == NULL) {
    M_unlock(m);
    return NULL;
  }

  for (M_node *N = m->head; N != NULL; N = N->next) {
    if (strcmp(N->k, k) == 0) {
      M_unlock(m);
      return N->v;
    }
  }
  M_unlock(m);
  return NULL;
}

bool M_has_key(Map *m, char *k) {
  M_lock(m);

  if (m->head == NULL) {
    M_unlock(m);
    return NULL;
  }

  for (M_node *N = m->head; N != NULL; N = N->next) {
    if (strcmp(N->k, k) == 0) {
      pthread_mutex_unlock(m->mutex);
      return true;
    }
  }
  M_unlock(m);
  return false;
}

void M_print_node(M_node *N) {
  printf("  %s: %s,\n", N->k, N->v);
}

void M_print(Map *m) {
  printf("\nMap(\n");
  for (M_node *N = m->head; N != NULL; N = N->next) {
    M_print_node(N);
  }
  printf(")\n");
}
