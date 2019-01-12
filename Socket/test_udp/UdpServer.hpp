#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Sock
{
public:
 
  //构造函数
  Sock(std::string& _ip,int& _port)
    :ip(_ip),port(_port)
  {
    ;
  }
  
  //创建套接字
  void Socket()
  {
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0)
    {
      std::cerr<<"socket error"<<std::endl;
      exit(1);
    }
  }

  void Bind()
  {
    struct sockaddr_in _local;
    _local.sin_family = AF_INET;
    _local.sin_port  = htons(port);
    _local.sin_addr.s_addr = inet_addr(ip.c_str());
    if(bind(sock,(struct sockaddr*)&_local,sizeof(_local))<0)
    {
      std::cerr<<" bind error "<<std::endl;
      exit(3);
    }
  }

  //接收
  void Recv(std::string &_str,struct sockaddr_in &peer,socklen_t &len)
  {
    char buf[1024];
    len = sizeof(sockaddr_in);
    ssize_t s = recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&peer,&len);
    if(s>0)
    {
      buf[s] = 0;
      _str = buf; 

    }


  }

  //发送
  void Send(std::string &_str,struct sockaddr_in &peer,socklen_t &len)
  {
    sendto(sock,_str.c_str(),_str.size(),0,(struct sockaddr*)&peer,len);


  }

  ~Sock()
  {
    ;
  }
private:
  int sock;
  std::string ip;
  int port;

};



class UdpSever
{
  public:
    UdpSever(std::string _ip,int _port):sock(_ip,_port)
    {

    }

    void InitServer()
    {
      sock.Socket();
      sock.Bind();
    }

    void Start()
    {
      struct sockaddr_in peer;
      socklen_t len;
      std::string message;

      for(; ;)
      {
        sock.Recv(message,peer,len);
        sock.Send(message,peer,len);
      }
    }

    ~UdpSever()
    {

    }

  private:
    Sock sock;


};
