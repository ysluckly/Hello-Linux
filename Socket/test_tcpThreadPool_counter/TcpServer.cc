#include "TcpServer.hpp"

void Usage(string proc)
{
  cout<<"Usage" <<proc<<"ip port"<<endl;

}
int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  string ip = argv[1];
  int port = atoi(argv[2]);
  Server *sp = new Server(ip,port);
  sp->InitServer();
  sp->Run();


  return 0;
}
