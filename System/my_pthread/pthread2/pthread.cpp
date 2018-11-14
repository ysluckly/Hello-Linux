#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <string.h>

using namespace std;

void* thread1(void* arg)
{
  cout<<"thread1 is return ..."<<endl;
  int *p = (int*)(malloc(sizeof(int)));
  *p = 1;
  return (void*)p;
}

void* thread2(void* arg)
{
  cout<<"thread2 is return ..."<<endl;
  int *p = (int*)(malloc(sizeof(int)));
  *p = 2;
  pthread_exit((void*)p);
}

void* thread3(void* arg)
{
  cout<<"thread3 is return ..."<<endl;
  while(1)
  {
    cout<<"thread3 is runing ,, "<<endl;
    sleep(1);
  }
  return NULL;
}


int main()
{
  pthread_t tid;
  void* ret;

  //return
  pthread_create(&tid,  NULL, thread1,  NULL);
  pthread_join(tid,&ret);
  cout<<"return thread is "<<tid<<"return code is"<<*(int*)ret<<endl;
  free(ret);

  //pthread_exit
  pthread_create(&tid,  NULL,thread2,NULL);
  pthread_join(tid,&ret);
  cout<<"return thread is "<<tid<<"return code is"<<*(int*)ret<<endl;
  free(ret);


  //pthread_cancal
  pthread_create(&tid,  NULL,thread3,NULL);
  sleep(3);
  pthread_cancel(tid);
  pthread_join(tid,&ret);
  if(ret == PTHREAD_CANCELED) 
    cout<<"return thread is "<<tid<<"return code is PTHREAD_CANCELED"<<endl;
  else 
    cout<<"return is not cancel"<<endl;

  return 0;

}
