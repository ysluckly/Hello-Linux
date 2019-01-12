#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class Sock{

  private:
    int listensock;
    int port;
    string ip;
  public:
    Sock(const string& _ip,const int& _port)
      :ip(_ip),port(_port),listensock(-1)
    {
      ; 
    }
  void Socket()
  {
    listensock = socket(AF_INET,SOCK_STREAM,0);
    if(listensock<0)
    {
      cerr<<"socket"<<endl;
      exit(1);
    }
  }
  void Bind()
  {
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr= inet_addr(ip.c_str());
    
    if(bind(listensock,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
        cerr<<"bind"<<endl;
        exit(3);
    }
    
  }

  void Listen()
  {
    if(listen(listensock,5)<0)
    {
      cerr<<"listen"<<endl;
      exit(4);
    }

  }

  int Accept()
  {
    struct sockaddr_in peer;
    socklen_t len = sizeof(peer);
    int sock =  accept(listensock,(struct sockaddr*)&peer,&len);
    if(sock<0)
    {
      cerr<<"accept "<<endl;
      return -1;
    }
    return sock;
    
  }

  ~Sock()
  {
      close(listensock);
  }
};



class Server
{
  private:
    Sock sock;
  public:
    Server(const string& _ip,const int& _port):sock(_ip,_port)
  {

  }
    void InitServer()
    {
      sock.Socket();
      sock.Bind();
      sock.Listen();

    }

    void Service(int sock)
    {
      //udp 面向数据报  规定:sendto   recvfrom
      //tcp  面向字节流 read /write
      char buf[1024];
      for(;;)
      {
        ssize_t s = read(sock,buf,sizeof(buf)-1);
        if(s>0)
        {
          buf[s]=0;
          cout<<buf<<endl;
          write(sock,buf,strlen(buf));

        }

        else if(s == 0)
        {
          cout<<"client is quite"<<endl;
          break;

        }
        else{
        cerr<<"read"<<endl;
        }

      }
      close(sock);
    }
    void Run()
    {
      for(;;)
      {
        int new_sock = sock.Accept();
        if(new_sock<0)
        {
          continue;
        }
        cout<<"Get a New Link "<<endl;;
        Service(new_sock);
      }
    }

   ~Server()
   {
    }

};
