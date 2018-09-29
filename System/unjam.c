/*************************************************************************
	> File Name:    unjam.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: Thu 27 Sep 2018 09:46:33 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork faild");
        exit(99);
    }
    else if( pid == 0)//child
    {

        printf("i am runing process %d\n",getpid());
        sleep(5);
        exit(1);
    }
    else //parent
    {
        int status = 0;
        int ret = 0;

        do {//rotate measure
            ret = waitpid(-1,&status,WNOHANG);//unjam wait 
            if(ret == 0)
            {
                printf("the child if runing\n");
            }

            sleep(1);


        }while(ret == 0);
        
        if(WIFEXITED(status) && ret == pid)
        {
            printf("wait child 5s sucess,child return code is %d\n",\
                   WEXITSTATUS(status));

        }
        else
        {
            printf("child faild return \n");
            return 1;
        }
    }
    return 0;
}
