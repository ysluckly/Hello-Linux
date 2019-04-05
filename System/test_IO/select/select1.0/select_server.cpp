/**这是一个简单的高并发服务器客户端
 * 实现多个客户端的连接与数据处理（聊天）
 * 这是一个tcp的服务器端程序
 */ 

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

void Usage(char* proc)
{
  printf("%s ip port\n", proc);
}

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  //监听描述符和客户端进行通信的描述符
  int lst_fd, cli_fd;
  int i, ret;
  socklen_t len;
  struct sockaddr_in lst_addr;
  struct sockaddr_in cli_addr;
  int fd_list[1024];
  fd_set readfds;
  struct timeval tv;

  lst_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (lst_fd < 0)
  {
    std::cerr << "sockct error!\n" << std::endl;
    exit(1);
  }
  lst_addr.sin_family = AF_INET;
  lst_addr.sin_port = htons(atoi(argv[2]));
  lst_addr.sin_addr.s_addr = inet_addr(argv[1]);
  len = sizeof(cli_addr);
  ret = bind(lst_fd, (struct sockaddr*)&lst_addr, len);
  if (ret < 0)
  {
    std::cerr << "bin error!" << std::endl; 
  }
  if (listen(lst_fd, 5) < 0)
  {
    std::cerr << "listen error!\n" << std::endl;
    exit(2);
  }
  
  //将所有的列表置为-1
  for (i = 0; i < 1024; i++)
  {
    fd_list[i] = -1;
  }
  fd_list[0] = lst_fd;
  int max_fd = lst_fd;
  while (1)
  {
    //清空描述符集合
    FD_ZERO(&readfds);
    FD_SET(lst_fd, &readfds);
    
    //将所有的描述符都添加到集合当中
    for (i = 0; i < 1024; i++)
    {
      //将存在的描述符都添加到集合中
      if (fd_list[i] != -1)
      {
        FD_SET(fd_list[i], &readfds);
      }
      //从所有的描述符中找到最大的描述符
      if (fd_list[i] > max_fd)
      {
        max_fd = fd_list[i];
      }
    }
   
    //设置超时时间
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    //select开始监控描述符中的集合是否就绪
    ret = select(max_fd + 1, &readfds, NULL, NULL, &tv);
    if (ret < 0)
    {
      printf("select error!\n");
      continue; 
    }
    else if (ret == 0)
    {
      printf("timeout!\n");
      continue;
    } 
    
    //走到这一步代表有描述符有数据到来了，但是我们不知道到底是哪个描述符可读，因此需要循环去判断fd数组中那一个可读
    for (i = 0; i < 1024; i++)
    {
      if (fd_list[i] < 0)
      {
        continue; 
      }
      //判断哪个描述符现在就绪了，因为一旦有描述符就绪，那么readfds中只保留就绪的描述符，其他的全部删除
      if (FD_ISSET(fd_list[i], &readfds))
      {
        //如果就绪的这个描述符是监听描述符
        if (fd_list[i] == lst_fd)
        {
          cli_fd = accept(lst_fd, (struct sockaddr*)&cli_addr, &len);
          if (cli_fd < 0)
          {
            perror("accept error!\n");
            continue;
          }
          //将和客户端进行通信的描述符保存起来
          for (i = 0; i < 1024; i++)
          {
            if (fd_list[i] == -1)
            {
              fd_list[i] = cli_fd;
              break;
            }
          }
        }
        else 
        {
          //如果就绪的这个描述符不是监听描述符
          //那么代表有客户端连接的数据到来了
          char buff[1024] = { 0 };  
          ret = recv(fd_list[i], buff, 1023, 0);
          if (ret <= 0)
          {
            close(fd_list[i]);
            fd_list[i] = -1;
          }
          printf("clinet say#%s\n", buff);
          send(fd_list[i], "what???", 7, 0);
        }
      }
    }
  }
}


