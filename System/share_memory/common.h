#ifndef __COMMON_H__
#define __COMMON_H__ 

#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

using namespace std;
#define PATHNAME "."
#define PROJ_ID 0X666


int CreatShm(int size);
int GetShm(int size);
int DestroyShm(int shmid);




#endif //__SHARE_H__
 
