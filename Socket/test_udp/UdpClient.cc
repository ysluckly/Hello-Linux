#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void Usage(std::string proc)
{
  std::cout<<"Usage:"<<proc<<"ip port"<<std::endl;
}

int main(int argc ,char* argv[])
{
  if(argc!=3)
  {
    Usage(argv[0]);

  }


  for(;;)
  {
    

  }



  return 0;
}
