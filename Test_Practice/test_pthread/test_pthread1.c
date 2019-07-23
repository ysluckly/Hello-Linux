/*************************************************************************
    > File Name:    test_pthread1.c
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Tue 23 Jul 2019 10:25:54 AM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void *pthread_run(void *arg)
{
        pthread_detach(pthread_self());
        printf("new thread->pid:%d,tid:%ld\n",getpid(),pthread_self());
        return NULL;

}
int main()
{
        pthread_t tid;
        int err = pthread_create(&tid,NULL,pthread_run,NULL);
        if(err)
        {
              printf("%s\n",strerror(err));
              return -1;         
        }
              int ret = 0;
              sleep(2);
              if(0 == pthread_join(tid,NULL))
               {
                      printf("wait sucess\n");
                      ret = 0;
               }
              else             
              {
                      printf("wait failture\n");
                      ret = 1;
                                                        
              }
            return ret;
}
