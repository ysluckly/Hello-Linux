/*************************************************************************
	> File Name:    shell.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: Fri 28 Sep 2018 08:17:19 PM PDT
 ************************************************************************/
//分析：

//1.获取命令行
//2.解析命令行
//3.建立一个子进程
//4.替换子进程
//5.父进程等待子进程退出

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<ctype.h>
char *argv[8];
int argc = 0;

void do_parse(char *buf)
{
    int i = 0;
    int status = 0;
    for(argc=i=0;buf[i];++i)
    {
        if(!isspace(buf[i])&&status == 0)
        {

            argv[argc++] = buf+i;
            status = 1;

        }else if(isspace(buf[i]))
        {
            status = 0;
            buf[i] = 0;
        }
    }
    argv[argc] = NULL;

}

void do_execute(void)
{
    pid_t pid = fork();

    switch(pid)
    {
        case -1:
            { 
                perror(" fork faild");
                exit(EXIT_FAILURE);
            }
        case 0:
            {
                execvp(argv[0],argv);
                perror("execvp");
                exit(EXIT_FAILURE);
             }
        default:
            {
                int st;
                while(wait(&st)!=pid)
                    ;
            }

    }
}


int main()
{
    char buf[1024] = {0};

    while(1)
    {
        printf("my shell >:");
        scanf("%[^\n]%*c",buf);
    
        do_parse(buf);
        do_execute();

    }

}
