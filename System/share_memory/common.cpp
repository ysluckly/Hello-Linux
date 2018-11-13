#include "common.h"

static int commonshm(int size,int flag)
{
  key_t key = ftok(PATHNAME,PROJ_ID);
  if(key<0)
  {
    cout<<"key is error"<<endl;
    return 1;

  }
  int shmid = shmget(key,size,flag);
  if(shmid<0)
  {
    cout<<"shimid is error"<<endl;
    return 1;

  }
  return shmid;

}

int CreatShm(int size)
{
  return commonshm(size,IPC_CREAT|IPC_EXCL|0666);

}
int GetShm(int size)
{

  return commonshm(size,IPC_CREAT);

}
int DestroyShm(int shmid)
{
  if(shmctl(shmid,IPC_RMID,NULL)<0)
  {
    cout<<"destroy is error"<<endl;
    return 1;
  }
  return 0;


}

