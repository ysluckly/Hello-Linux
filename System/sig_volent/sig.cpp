#include "common.h"

int main()
{

  int semid = CreatSem(1);
  InitSem(semid,0,1);
  pid_t id = fork();
  if(id == 0)//child
  {
    int _semid = GetSem(0);
    while(1)
    {
      P(_semid,0);
      cout<<"A";
      fflush(stdout);
      usleep(123456);
      cout<<"A";
      fflush(stdout);
      usleep(323243);
      V(_semid,0);
    }
  }
  else //parent
  {
    while(1)
    {
      P(semid,0);
      cout<<"B";
      fflush(stdout);
      usleep(323323);
      cout<<"B";
      fflush(stdout);
      usleep(123123);
      V(semid,0);
  }
  wait(NULL);
  }
  DestroySem(semid);

  return 0;

}
