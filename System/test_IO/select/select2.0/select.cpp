#include <iostream>
#include <string>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

//select可以监听的最大的文件描述符的最大值
#define SIZE 1024
#define INIT -1

int StartUp(int port)
{
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
    std::cerr << "socket error!" << std::endl;
    exit(1);
  }

  struct sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_port = htons(port);
  local.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  if (bind(sock, (struct sockaddr*)(&local), sizeof(local)) < 0)
  {
    std::cerr << "bind error!" << std::endl; 
    exit(2);
  }

  if (listen(sock, 5) < 0)
  {
    std::cerr << "listen error!" << std::endl;
    exit(3);
  }
  
  std::cout << "listen sock create success..." << std::endl;
  return sock;
}

void InitFdArray(int fd_array[], int size)
{
  for (auto i = 0; i < size; i++)
  {
    fd_array[i] = INIT;
  }
}

int ArrayFdToSet(int fd_array[], int size, fd_set& rfds)
{
  int max = fd_array[0];
  for (auto i = 00; i < size; i++)
  {
    if (fd_array[i] == INIT)
    {
      continue;
    }
    FD_SET(fd_array[i], &rfds);
    if (max < fd_array[i])
    {
      max = fd_array[i];
    }
  }

  return max;
}

void AddFdToArray(int fd_array[], int& size, const int& sock)
{
  if (size == SIZE)
  {
    std::cout << "socket is null..." << std::endl;
    close(sock);
  }
  fd_array[size++] = sock;
}

void DelFdToArray(int fd_array[], int& size, int index)
{
  fd_array[index] = fd_array[--size];
  fd_array[size] = INIT;
}

int main()
{
  int fd_array[SIZE];
  int size = 0;
  InitFdArray(fd_array, SIZE);
  int listen_sock = StartUp(8888);
  fd_array[size++] = listen_sock;

  for (;;)
  {
    fd_set rfds;
    FD_ZERO(&rfds);

    int max_fd = ArrayFdToSet(fd_array, size, rfds);
    struct timeval timeout = {5, 0};

    switch(select(max_fd + 1, &rfds, NULL, NULL, &timeout))
    {
      case -1:
        std::cerr << "select error..." << std::endl;
        break;
      case 0:
        //超时
        std::cout << "time out..." << std::endl;
        break;
      default:
        //read event ready!
        for (auto i = 0; i < size; i++)
        {
          int sock_ = fd_array[i];
          if (sock_ < 0)
          {
            continue;
          }
          if (FD_ISSET(sock_ , &rfds))
          {
            if (sock_ == listen_sock)
            {
              //读就绪说明完全连接队列中有新连接到来
              //accept
              struct sockaddr_in peer;
              socklen_t len = sizeof(peer);
              int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
              if (sock < 0)
              {
                //说明连接出错，但是一般不会出错，因为这个时候listen已经就绪了
                std::cerr << "accept error..." << std::endl;
              }
              AddFdToArray(fd_array, size, sock);
              std::cout << "accept new sock..." << std::endl;
            }
            else 
            {
              //read
              char buffer[10240];
              ssize_t s = read(sock_, buffer, sizeof(buffer));
              if (s > 0)
              {
                buffer[s] = 0;
                std::cout << "server# " << buffer << std::endl;
                std::string response = "HTTP/1.0 200 OK\r\n\r\n <html><h1>hello select server!</h1></html>\r\n";
                send(sock_, response.c_str(), response.size(), 0);
                close(sock_);
                DelFdToArray(fd_array, size, i);
                i--;
              }
              else if (s == 0)
              {
                close(sock_);
                DelFdToArray(fd_array, size, i);
                i--;
              }
              else 
              {
                close(sock_);
                DelFdToArray(fd_array, size, i);
                i--;
              }
            }
          }
        }


        break;
    }
  }


  return 0;
}
