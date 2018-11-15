#include "common.h"

static int  commonSem(int num,int flag)
{
  key_t key = ftok(PATHNAME,PROJ_ID);
  if(key<0)
  {
    cout<<"ftok id error"<<endl;
    return -1;
  }
  int semid = semget(key,num,flag);
  if(semid<0)
  {
    cout<<"semid is error"<<endl;
    return -1;
  }

  return semid;
}
int CreatSem(int num)
{
  return commonSem(num,IPC_CREAT|IPC_EXCL|0666);

}
int InitSem(int semid,int num,int init_val)
{
  union semun _un;
  _un.val = init_val;
  if(semctl(semid,num,SETVAL,_un)<0)
  {
    cout<<"semctl id error"<<endl;
    return -1;
  }

  return 0;

}
int GetSem(int num)
{
  return commonSem(num,IPC_CREAT);
}
int P(int semid,int who);
int V(int semid,int who);
