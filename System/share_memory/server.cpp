#include "common.h"

int main()
{
  int shmid = CreatShm(4096);

  char* addr = (char*)shmat(shmid,NULL,0);
  sleep(2);
  int i = 0;
  while(i++<26)
  {
    cout<<"client# "<<addr<<endl;
    sleep(1);

  }

  shmdt(addr);
  sleep(2);
  DestroyShm(shmid);
  return 0;
}
