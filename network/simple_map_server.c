#include "map/list_map.h"
#include <arpa/inet.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BACKLOG 5

void handle_request(int client_fd, Map *m) {
    char buf[4096];
    char k[256], v[256];
    ssize_t n;
    while ((n = read(client_fd, buf, 4096)) > 0) {
      ssize_t N = write(STDOUT_FILENO, buf, n);
      assert(N == n);
      sscanf(buf, "%s %s", k, v);
      M_set(m, k, v); 
    }
}

int main(int argc, char *argv[]) {
  Map *m = M_init();

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
  for (;;) {
    int client_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_len);
    assert(client_fd >= 0);
    handle_request(client_fd, m);
    close(client_fd);
    M_print(m);
  }
}
