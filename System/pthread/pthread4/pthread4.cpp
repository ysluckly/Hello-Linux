
///////////////////抢票系统

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int ticket = 100;//100张票

void* pthread_route(void* arg)
{
  char* yao = (char*)arg;
  while(1)
  {
    if(ticket>0)
    {
      usleep(1000);
      cout<<yao<<"sell ticket:"<<ticket<<endl;
      ticket--;
    }
    else{
      break;
    }

  }

}
int main()
{
  pthread_t t1,t2,t3,t4;
  
  pthread_create(&t1,NULL,pthread_route,(void*)"thread 1");
  pthread_create(&t2,NULL,pthread_route,(void*)"thread 2");
  pthread_create(&t3,NULL,pthread_route,(void*)"thread 3");
  pthread_create(&t4,NULL,pthread_route,(void*)"thread 4");

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  pthread_join(t4,NULL);

  return 0;
}
