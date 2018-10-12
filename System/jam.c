/*************************************************************************
	> File Name:    jam.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: Thu 27 Sep 2018 09:11:41 PM PDT
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()

{
    pid_t pid = fork();

    if(pid <0 )
    {
        perror("fork faild");
        exit(1);
    }
    else  if(pid == 0)//child
    {
        printf("i am runing pid id %d",getpid());
        sleep(5);
        exit(9);

    }
    else ///perent
    {
        int status = 0;
        pid_t ret = waitpid(-1,&status,0); //jam wait five second
        printf("this is test for wait \n");

        if(WIFEXITED(status)&&ret == pid)
        {
            printf("wait child 5s sucess,child return code id %d",\
                   WEXITSTATUS(status));
        }
        else
        {
            printf(" is wait faild ");
            return 1;
        }
    }
    return 0;
}
