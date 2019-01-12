#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
using namespace std;
void Usage(std::string proc)
{
  std::cout<<"Usage:"<<proc<<"ip port"<<std::endl;
}

int main(int argc ,char* argv[])
{
  if(argc!=3)
  {
    Usage(argv[0]);
    exit(1);

  }

  int sock = socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0)
  {
    cout<<"sock error"<<endl;
    exit(2);
  }
  std::string message;
  struct sockaddr_in server;
  bzero(&server,sizeof(server));
  server.sin_family= AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  server.sin_addr.s_addr = inet_addr(argv[1]);
  char buf[1024];
  for(;;)
  {
    socklen_t len = sizeof(server);
    std::cout<<"Please Enter#";
    std::cin>>message;
    sendto(sock,message.c_str(),message.size(),0,(struct sockaddr*)&server,len);//0阻塞收
    recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,&len);//len,传入是传入大小，返回是返回大小
    cout<<"Server echo#"<<buf<<endl;
    

  }


  return 0;
}
