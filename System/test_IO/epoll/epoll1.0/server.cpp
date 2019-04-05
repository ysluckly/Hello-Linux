#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

void Usage(char* proc)
{
  std::cout << proc << " port" << std::endl;
}

void SetNoBlock(int fd)
{
  int oldfl = fcntl(fd, F_GETFL);
  if (oldfl < 0)
  {
    std::cerr << "fcntl error!" << std::endl;
    exit(7);
  }

  fcntl(fd, F_SETFL, oldfl | O_NONBLOCK);
}

bool ReadNoBlock(int sockfd, char* buf, int len)
{
  int total_len = 0;
  int read_len = 0;
  for ( ; ; )
  {
    read_len = recv(sockfd, buf + total_len, len, 0);
      if (read_len < 0)
      {
        //接收的时候被信号打断了，也就是数据没有接收完毕，所以需要继续接收
        if (errno == EWOULDBLOCK || errno == EAGAIN)
        {
          continue;
        }
        std::cerr << "recv error!" << std::endl;
        return false;
      }
      
      if (read_len == 0)
      {
        //接收完毕，或者对端关闭
        return false;
      }

      //表示数据接收完毕了
      if (read_len < len)
      {
        break;
      }

      total_len += read_len;
  }
  buf[total_len] = '\0';
  return true;
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    Usage(argv[0]);
    exit(1);
  }
  int lst_fd, cli_fd;
  //用来存放所要bind结构体大小
  socklen_t len;
  //ep_fd是一个句柄，用来控制epoll的;nfds表示的是每次等待之后就绪的文件描述符的个数
  int ep_fd, nfds;
  struct sockaddr_in lst_addr, cli_addr;
  //evs用来存放的是每次准备就绪的文件描述符
  struct epoll_event evs[1024], ev;
  //创建监听套接字
  lst_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (lst_fd < 0)
  {
    std::cerr << "socket error!" <<std::endl;
    exit(2);
  }
  
  //设置服务器可以立即重启
  int opt = 1;
  setsockopt(lst_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

  //绑定套接字
  lst_addr.sin_family = AF_INET;
  lst_addr.sin_port = htons(atoi(argv[1]));
  //表示监听的是这个局域网上所有的IP地址
  lst_addr.sin_addr.s_addr = INADDR_ANY;
  len = sizeof(lst_addr);
  if (bind(lst_fd, (struct sockaddr*)&lst_addr, len) < 0)
  {
    std::cerr << "bind error!" << std::endl;
    exit(3);
  }

  //监听套接字
  if (listen(lst_fd, 5) < 0)
  {
    std::cerr << "listen error!" << std::endl;
    exit(4);
  }

  //创建epoll
  ep_fd = epoll_create(1024);
  if (ep_fd < 0)
  {
    std::cerr << "epoll_create error!" << std::endl;
    exit(5); 
  }
  //创建epoll结点
  ev.events = EPOLLIN;
  ev.data.fd = lst_fd;
  //将结点加入到epoll中，直接加到内核当中，也就是那个红黑树
  if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, lst_fd, &ev) < 0)
  {
    std::cerr << "epoll_ctl error!" << std::endl;
    exit(6);
  }

  for ( ; ; )
  {
    //1024表示最大可同时等待多少个事件，evs用来存放等待成功的事件的
    //对于evs是覆盖式的拷贝，每次都会把前面的都覆盖了
    nfds = epoll_wait(ep_fd, evs, 1024, 3000);
    if (nfds < 0)
    {
      std::cerr << "epoll_wait error!" << std::endl;
      continue;
    }

    else if (nfds == 0)
    {
      std::cout << "timeout!" << std::endl;
      continue;
    }

    //到这里表示等待成功了
    for (int i = 0; i < nfds; i++)
    {
      //表示等待的是监听描述符
      if (evs[i].data.fd == lst_fd)
      {
        //进行连接
        cli_fd = accept(lst_fd, (struct sockaddr*)&cli_addr, &len); 
        if (cli_fd < 0)
        {
          std::cerr << "accept error!" << std::endl;
          continue;
        }
        //创建客户端结点事件，并且加入到epoll中
        //EPOLLET 边缘触发
        //EPOLLLT 水平触发
        //EPOLLIN 关心可读事件
        //EPOLOUT 关心可写事件
        //因为边缘触发是每次新数据到来仅触发一次事件
        //因此我们必须保证一次能把数据全部读完
        
        //对于和客户端进行通信的文件描述符设置为边缘触发
        ev.events = EPOLLIN | EPOLLET;

        //对于边缘触发的话，必须将cli_fd文件描述符设置为非阻塞式的
        ev.data.fd = cli_fd;
        if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, cli_fd, &ev) < 0)
        {
          std::cerr << "epoll_ctl error!" << std::endl;
          continue;
        }
      }
      //表示等待的是可读事件
      else if (evs[i].events == EPOLLIN)
      {
        //接收消息并且发送消息给客户端
        char buf[1024] = { 0 };
        //对于处理和客户端进行通信的时候，当接收到的消息是0的话，表示客户端退出，小于0表示recv函数失败
        //if (recv(evs[i].data.fd, buf, 2, 0) <= 0)
        //对于边缘触发的话，必须每一次进行读取数据的时候一次将数据读取完毕
        if (ReadNoBlock(evs[i].data.fd, buf, 2) <= 0)
        {
          //接收失败就从epoll集合中取出这个事件，将这个时间放在ev中
          std::cout << "recv quit!" << std::endl;
          epoll_ctl(ep_fd, EPOLL_CTL_DEL, evs[i].data.fd, &ev);
          close(evs[i].data.fd);
          continue;
        }

        std::cout << "client say# " << buf << std::endl;
        send(evs[i].data.fd, "what???", 7, 0);
      }
    }
  }



  

  return 0;
}

