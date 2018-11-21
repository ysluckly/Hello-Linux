#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
void* pthread_run(void* arg)
{
   pthread_detach(pthread_self());
   cout<<(char*)arg<<endl;
   return NULL;
}
int main()
{
  pthread_t tid;
  if(pthread_create(&tid,NULL,pthread_run,(void*)"hello pthread")!=0){
    cout<<"error pthread_create"<<endl;
    return 1;
  }
        
  int ret = 0;
  sleep(1);
  
  if(pthread_join(tid,NULL) == 0)
  {
    cout<<"pthread is success"<<endl;
    ret=0;
  }
  else{
    cout<<"pthread is error"<<endl;
    ret =1;
  }

   
  return ret;

}
