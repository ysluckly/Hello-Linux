//僵尸进程
/*
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    pid_t id = fork();
    if(id<0)
    {
        perror("fail to fork");
        exit(1);
    }
    else if(id == 0) //child
    {
        printf("the pid is %d, parent is %d",getpid(),getppid());
        sleep(5);
        exit(1);
    }
    else //parent
    {
        while(1)
        {
        printf("the parent is %d\n",getpid());
        sleep(3);
        }
    }
    return 0;
}*/
//孤儿进程
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    pid_t id = fork();
    if(id<0)
    {
        perror("fail to fork");
        exit(1);
    }
    else if(id == 0) //child
    {
        printf("the pid is %d, parent is %d",getpid(),getppid());
        sleep(20);
    }
    else //parent
    {
        printf("the parent is %d\n",getpid());
        sleep(5);
        exit(1);
    }
    return 0;
}
