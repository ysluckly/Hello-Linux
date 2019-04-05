#include <iostream>
#include <sys/poll.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  struct pollfd pfd;

  for ( ; ; )
  {
    pfd.fd = 0;
    pfd.events = POLLIN;
    int ret = poll(&pfd, 1, 3000);
    if (ret < 0)
    {
      std::cerr << "poll error!" << std::endl;
      exit(1);
    }
    else if (ret == 0)
    {
      std::cout << "timeout!" << std::endl;
      continue;
    }
    char buf[1024];
    read(0, buf, 1023);
    std::cout << buf << std::endl;
  }
  return 0;
}

