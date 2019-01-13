#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <strings.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <unordered_map>
#include "ThreadPool.h"

using namespace std;

struct data_t{

  int sp;
  int sock;
}data_t;
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
   


    //服务器端ip可为0,一个服务器可能两个网卡，即2ip，如果有多个ip，可以设置一个宏，即服务器可接收发送到本机任意ip的数据，客户端不可以省略
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
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
    ThreadPool pool;
  public:
    Server(const string& _ip,const int& _port):sock(_ip,_port),pool(5)
  {
  }
    void InitServer()
    {
      signal(SIGCHLD,SIG_IGN);//忽略
      sock.Socket();
      sock.Bind();
      sock.Listen();
      pool.InitThreadPool();
    }

   static void Service(int sock)
    {
      //udp 面向数据报  规定:sendto   recvfrom
      //tcp  面向字节流 read /write
      char buf[10240];
    
       recv(sock,buf,sizeof(buf)-1,0);
       printf("%s",buf);
       const char *status = "HTTP/1.0 302  REDIRECT\r\n";
       send(sock,status,strlen(status),0);
       const char *header = "Content-Type: text/html\r\nLocation:http://www.baidu.com\r\n";
       send(sock,header,strlen(header),0);
       const char *blank = "\r\n";
       send(sock,blank,strlen(blank),0);
       const char* text = "<html><h2>hello Linux!<h2><html>\r\n";
      send(sock,text,strlen(text),0);
       
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
        
        Task t(new_sock,Server::Service);
        pool.AddTask(t);
         
       //close(new_sock);
        
       /////////////////////////////

        
        
      }
    }

   ~Server()
   {
    }

};
