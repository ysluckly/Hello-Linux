#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
void SetNoBlock(int fd) {
  int fl = fcntl(fd, F_GETFL);
  if (fl < 0) {
    perror("fcntl");
    return;

  }
  fcntl(fd, F_SETFL, fl | O_NONBLOCK);

}
int main() {
  SetNoBlock(0);
  while (1) {
    char buf[1024] = {0};
    ssize_t read_size = read(0, buf, sizeof(buf) - 1);
    if (read_size < 0) {
      perror("read");
      sleep(1);
      continue;
    }
    printf("input:%s\n", buf);
  }
  return 0;
}
