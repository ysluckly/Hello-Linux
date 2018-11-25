
///////////////////【加互斥锁优化】抢票系统

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int ticket = 100;//100张票
pthread_mutex_t mutex;

void* pthread_route(void* arg)
{
  char* yao = (char*)arg;
  while(1)
  {
    pthread_mutex_lock(&mutex);
    if(ticket>0)
    {
      usleep(1000);
      cout<<yao<<"sell ticket:"<<ticket<<endl;
      ticket--;
      pthread_mutex_unlock(&mutex);
    }
    else{
      pthread_mutex_unlock((&mutex));
      break;
    }

  }

}
int main()
{
  pthread_t t1,t2,t3,t4;
  
  pthread_mutex_init(&mutex,NULL);
  pthread_create(&t1,NULL,pthread_route,(void*)"thread 1");
  pthread_create(&t2,NULL,pthread_route,(void*)"thread 2");
  pthread_create(&t3,NULL,pthread_route,(void*)"thread 3");
  pthread_create(&t4,NULL,pthread_route,(void*)"thread 4");

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  pthread_join(t4,NULL);

  pthread_mutex_destroy(&mutex);
  return 0;
}
