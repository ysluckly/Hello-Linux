#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>

#define EVS_SIZE 126

int StartUp(int port)
{
  int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_sock < 0)
  {
    std::cerr << "socket error!" << std::endl;
    exit(1);
  }

  int opt = 1;
  setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in peer;
  peer.sin_family = AF_INET;
  peer.sin_port = htons(port);
  peer.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(listen_sock, (struct sockaddr*)&peer, sizeof(peer)) < 0)
  {
    std::cerr << "bind error!" << std::endl;
    exit(2);
  }

  if (listen(listen_sock, 5) < 0)
  {
    std::cerr << "listen error!" << std::endl;
    exit(3);
  }

  return listen_sock;
  std::cout << "listen start..." << std::endl;
}

void AddFdToEpoll(int epfd, int sock, uint32_t events)
{
  struct epoll_event ev;
  ev.events = events;
  ev.data.fd = sock;

  epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev);
  std::cout << "epoll add fd:" << sock << std::endl;
}

void DelFdFromEpoll(int epfd, int sock)
{
  epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
  std::cout << "epoll del fd:" << sock << std::endl;
}

void ModFdToEpoll(int epfd, int sock, uint32_t events)
{
  struct epoll_event ev;
  ev.data.fd = sock;
  ev.events = events;

  epoll_ctl(epfd, EPOLL_CTL_MOD, sock, &ev);
  std::cout << "epoll mod fd:" << sock << std::endl;
}

void Handler(int epfd, int num, struct epoll_event evs[], int listen_sock)
{
  for (auto i = 0; i < num; i++)
  {
    int sock = evs[i].data.fd;
    uint32_t events = evs[i].events;
    if (events & EPOLLIN)
    {
      if (sock == listen_sock)
      {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int new_sock = accept(sock, (struct sockaddr*)&peer, &len);
        if (new_sock < 0)
        {
          std::cerr << "accept error!" << std::endl;
          continue;
        }

        AddFdToEpoll(epfd, new_sock, EPOLLIN);
        std::cout << "a new client link !" << std::endl;
      }
      else 
      {
        char buffer[10240];
        int num = recv(sock, buffer, sizeof(buffer), 0);
        if (num == 0)
        {
          close(sock);
          DelFdFromEpoll(epfd, sock);
          std::cout << "peer close link..." << std::endl;
        }
        else if (num < 0)
        {
          close(sock);
          DelFdFromEpoll(epfd, sock);
          std::cout << "peer close link..." << std::endl;
        }
        else 
        {
          std::cout << "client#" << buffer << std::endl;
          //读取完之后要进行响应，等待写就绪
          //将这个fd的读事件改为写事件
          ModFdToEpoll(epfd, sock, EPOLLOUT);
        }
      }
    }
    else if (events & EPOLLOUT)
    {
      //写就绪之后，向对端写数据
      std::string response = "HTTP/1.1 301 REDIRECT\r\nLocation:https://www.taobao.com\r\n";
      send(sock, response.c_str(), response.size(), 0);
      close(sock);
      DelFdFromEpoll(epfd, sock);
      std::cout << "server close link!" << std::endl;
    }
    else 
    {
      //TODO
      //其他的事件就绪
    }
  }
}

int main()
{
  int listen_sock = StartUp(8888);
  int epfd = epoll_create(256);//256表示最大可以同时监听256个文件描述符
  if (epfd < 0)
  {
    std::cerr << "epoll create error!" << std::endl;
    exit(4);
  }
  std::cout << "epfd:" << epfd << std::endl;

  AddFdToEpoll(epfd, listen_sock, EPOLLIN);
  struct epoll_event evs[EVS_SIZE];//可以设置小于每次监听的最大值，只是因为底层是一个就绪队列，可以分多次拿
  for (;;)
  {
    int timeout = 5000;//5秒
    int num = epoll_wait(epfd, evs, EVS_SIZE, timeout);
    switch (num)
    {
      case -1:
        std::cerr << "epoll wait error!" << std::endl;
        break;
      case 0:
        std::cout << "timeout..." << std::endl;
        break;
      default:
        //要进行判定了
        Handler(epfd, num, evs, listen_sock);
        break;
    }
  }
  close(epfd);
  return 0;
}
