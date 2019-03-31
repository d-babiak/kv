#include <arpa/inet.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BACKLOG 5

void handle_request(int client_fd) {
  char buf[4096];
  ssize_t n;
  while ((n = read(client_fd, buf, 4096)) > 0) {
    ssize_t N = write(STDOUT_FILENO, buf, n);
    assert(N == n);
  }
}

void *f(void *client_fd_p) {
  int client_fd = *((int *) client_fd_p);
  assert(client_fd >= 0);

  int err = pthread_detach(pthread_self());
  assert(!err);

  handle_request(client_fd);
  close(client_fd);

  return NULL;
}

int main(int argc, char *argv[]) {
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  assert(listen_fd >= 0);

  struct sockaddr_in servaddr = {
    .sin_family = AF_INET,
    .sin_port = htons(atoi(argv[1])),
    .sin_addr = { .s_addr = INADDR_ANY } 
  };

  int err = bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  assert(!err);

  err = listen(listen_fd, BACKLOG);
  assert(!err);

  struct sockaddr_in client_addr = {.sin_family = AF_INET};
  socklen_t client_len = sizeof(client_addr);

  pthread_t tid;

  for (;;) {
    int *client_fd_p = malloc(sizeof(int));
    *client_fd_p = accept(listen_fd, (struct sockaddr *) &client_addr, &client_len);
    assert(*client_fd_p >= 0);
    err = pthread_create(&tid, NULL, f, (void *) client_fd_p);
    assert(!err);
  }
}
