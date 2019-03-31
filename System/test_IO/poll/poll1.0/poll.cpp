#include <iostream>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>

#define SIZE 1024
#define INIT -1

int StartListen(int port)
{
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    std::cerr << "socket error..." << std::endl;
    exit(1);
  }

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
  {
    std::cerr << "bind error..." << std::endl;
    exit(2);
  }

  if (listen(sock, 5) < 0)
  {
    std::cerr << "listen error..." << std::endl;
    exit(3);
  }
  std::cout << "listen success..." << std::endl;
  return sock;
}

void IintPollArray(struct pollfd poll_array[], int size)
{
  for (auto i = 0; i < size; i++)
  {
    poll_array[i].fd = -1;
    poll_array[i].events = 0;
    poll_array[i].revents = 0;
  }
}

void AddPollToArray(int fd, struct pollfd poll_array[], int& size)
{
  poll_array[size].fd = fd;
  poll_array[size].events = POLLIN;
  poll_array[size].revents = 0;
  size++;
}

void DelPollArray(struct pollfd poll_array[], int i, int& size)
{
  poll_array[i].fd = poll_array[size - 1].fd;
  poll_array[i].events = poll_array[size - 1].events;
  poll_array[i].revents = poll_array[size - 1].revents;
  size--;
}

int main()
{
  int listen_sock = StartListen(8888);
  int size = 0;//表示当前有多少数据
  struct pollfd poll_array[100];
  IintPollArray(poll_array, SIZE);
  AddPollToArray(listen_sock, poll_array, size);
  for (;;)
  {
    switch(poll(poll_array, SIZE, 1000))
    {
      case -1:
        std::cerr << "poll error..." << std::endl;
        break;
      case 0:
        std::cout << "timeout..." << std::endl;
        break;
      default:
        //revents ready
        for (auto i = 0; i < size; i++)
        {
          if (!(poll_array[i].revents & POLLIN))
          {
            continue;
          }
          if (poll_array[i].revents & POLLIN)
          {
            if (poll_array[i].fd == listen_sock)
            {
              struct sockaddr_in client;
              socklen_t len = sizeof(client);
              int client_sock = accept(listen_sock, (struct sockaddr*)&client, &len);
              if (client_sock < 0)
              {
                std::cerr << "accept error..." << std::endl;
                continue;
              }
              std::cout << "accept a new client..." << std::endl;
              AddPollToArray(client_sock, poll_array, size);
            }
            else 
            {
              char buffer[10240];
              int ret = read(poll_array[i].fd, buffer, sizeof(buffer));
              if (ret < 0)
              {
                std::cerr << "read error..." << std::endl;
                continue;
              }
              else if (ret == 0)
              {
                std::cout << "clinet close..." << std::endl;
                close(poll_array[i].fd);
                DelPollArray(poll_array, i, size);
                i--;//将最后替换过来的fd也要进行一次判断
              }
              else 
              {
                std::cout << "client# " << buffer << std::endl;
                std::string str = "HTTP/1.1 200 OK\r\n\r\n<html><h1>hello poll server</h1></html>";
                write(poll_array[i].fd, str.c_str(), str.size());
              }
            }
          }
        }
        break;
    }
    
  }
  return 0;
}

