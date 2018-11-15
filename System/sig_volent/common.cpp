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


static int commonPV(int semid,int who,int op)
{
  struct sembuf _sf;
  _sf.sem_num = who;
  _sf.sem_op= op;
  _sf.sem_flg = 0;
  if(semop(semid,&_sf,1)<0)
  {
    cout<<"semop id error"<<endl;
    return -1;
  }
  return 0;

}
int P(int semid,int who)
{
  return commonPV(semid,who,-1);

}
int V(int semid,int who)
{
  return commonPV(semid ,who,1);
}
