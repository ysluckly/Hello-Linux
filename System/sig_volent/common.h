#ifndef __COMMON_H__
#define __COMMON_H__ 

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
using namespace std;

#define PATHNAME "HUTER"
#define PROJ_ID 8998

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};


int CreatSem(int num);
int InitSem(int semid,int num,int init_val);
int GetSem(int num);
int P(int semid,int who);
int V(int semid,int who);
int DestroySem(int semid);



#endif //__COMMON_H__
