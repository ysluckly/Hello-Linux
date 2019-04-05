#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  //设置一个只读的文件描述符集合
  fd_set readfds;
  //最大的文件描述符
  int max_fd = 0;
  //设置超时时间
  struct timeval tv;

  while (1)
  {
    //清空这个文件描述符集合
    FD_ZERO(&readfds);
    //设置只读的文件描述符到这个集合
    FD_SET(0, &readfds);
    //设置超时时间
    tv.tv_sec = 3;//秒
    tv.tv_usec = 0;//毫秒
    //select参数
    //文件描述符的最大值加1
    //只读文件描述符集合
    //只写文件描述符集合
    //异常文件描述符集合
    //超时时间
    int ret = select(max_fd + 1, &readfds, NULL, NULL, &tv);
    if (ret < 0)
    {
      perror("select error!\n");
      continue;
    }
    else if (ret == 0)
    {
      //必须要加一个回车换行，这是为了刷新缓存区
      printf("3 secends ago no event!\n");
      continue;
    }
    printf("have data!\n");
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    read(0, buffer, sizeof(buffer));
    printf("buffer:[%s]\n", buffer);
  }

  return 0;
}
