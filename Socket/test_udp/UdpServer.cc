#include "UdpServer.hpp"


void Usage(std::string _proc)
{
  std::cout<<"Usage"<<_proc<<"   ip   port"<<std::endl;
}
int main(int argc,char *argv[])
{
  if(argc!=3)
  {
    Usage(argv[0]);
  }
  UdpSever *p = new UdpSever(argv[1],atoi(argv[2]));
  p->InitServer();
  p->Start();

  delete p;
  return 0;
}

