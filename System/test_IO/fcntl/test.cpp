#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void SetNoBlock(int fd)
{
  int oldfd = fcntl(fd, F_GETFL);
  if (oldfd < 0)
  {
    std::cerr << "fcntl error!" << std::endl;
    exit(1);
  }

  //使用oldfd和O_NONBLOCK相或是为了保留对于该描述符以前的特性，仅仅只是增加了非阻塞的属性
  fcntl(fd, F_SETFL, oldfd | O_NONBLOCK);
}

int main()
{
  SetNoBlock(0);
  while (1)
  {
    char buf[1024] = { 0 };
    ssize_t ret = read(0, buf, sizeof(buf) - 1);
    if (ret < 0)
    {
      std::cerr << "read error!" <<std::endl;
      sleep(1);
      continue;
    }

    std::cout << buf << std::endl;
  }
  return 0;
}

//int main()
//{
//  int fd  = creat("hello.c", 0440);
//  if (fd < 0)
//  {
//    std::cerr << "creat error!" << std::endl;
//    exit(2);
//  }
//  std::cout << fd << std::endl;
//  close(fd);
//  return 0;
//}
