#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

void Usage()
{
  printf("usage : ./http ip port\n");
}

int main(int argc, char* argv[])
{
  if(argc!=3)
  {
    Usage();
    return 1;
  }
  int fd = socket(AF_INET,SOCK_STREAM,0);
  if(fd<0)
  {
    perror("socket");
    return 2;
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = inet_addr(argv[1]);

  int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
  if(ret<0)
  {
    perror("bind");
    return 3;

  }

  ret = listen(fd,10);
  if(fd<0)
  {
    perror("listen");
    return 4;
  }

  for(;;)
  {
    struct sockaddr_in client_addr;
    socklen_t len;
    int client_fd = accept(fd,(struct sockaddr*)&client_addr,&len);;
    if(client_fd<0)
    {
      perror("accept");
      continue;
    }

    char input_buf[1024*10] = {0};
    ssize_t read_size = read(client_fd,input_buf,sizeof(input_buf)-1);
    if(read_size<0)
    {
      return 1;
    }
    printf("[Reuest]%s",input_buf);
    char buf[1024] = {0};
    const char* hello = "<h1>Hello Linux<h1>";
    sprintf(buf,"HTTP/1.0 200 OK\nContent-Length:%lu\n\n%s",strlen(hello),hello);
    write(client_fd,buf,strlen(buf));

  }

  return 0;
}
