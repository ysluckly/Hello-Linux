#include "common.h"

int main()
{
  int shmid = GetShm(4096);
  sleep(1);
  char* addr = (char*)shmat(shmid,NULL,0);
  sleep(2);
  int i = 0;
  while(i<26)
  {
    addr[i] = 'A'+i;
    ++i;
    addr[i] = 0;
    sleep(1);
  }

  shmdt(addr);
  sleep(2);
  return 0;

}
