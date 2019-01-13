#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "comm.hpp"
using namespace std;

void Usage(string proc)
{
  cout<<"Usage"<<proc<<"ip  port"<<endl;
}
int main(int argc,char* argv[])
{
  if(argc!=3)
  {
    Usage(argv[0]);
  
    exit(3);
  }
  int sock = socket(AF_INET,SOCK_STREAM,0);
  if(sock<0)
  {
    cerr<<"sock error"<<endl;
    exit(4);
  }
  
  //客户端可绑定，不建议绑定，可能绑定的被其他服务器占用
  //不监听，监听让别人连我
  //链接
  struct sockaddr_in peer;
  socklen_t len = sizeof(peer);
  bzero(&peer,sizeof(peer));

  peer.sin_family = AF_INET;
  peer.sin_port=htons(atoi(argv[2]));
  peer.sin_addr.s_addr=inet_addr(argv[1]);

  if(connect(sock,(struct sockaddr*)&peer,len)<0)
  {
  cerr<<"connect"<<endl;
    exit(1);

  }

  string message;
  requst r;
  Qrequst q;
  char buf[1024];
  for(;;)
  {
    cout<<"Please Enter<x,y>";
    cin>>r.x>>r.y;
    cout<<"Please ente op";
    cin>>r.op;
    send(sock,&r,sizeof(r),0);

    recv(sock,&q,sizeof(q),0);
    cout<<q.result<<"     "<<q.status<<endl;

  }

  close(sock);
  return 0;
}
