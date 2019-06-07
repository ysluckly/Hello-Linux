/*************************************************************************
	> File Name:    Day2.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: Fri 31 May 2019 11:54:40 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int status=0;
int choice = 0;
void Meau()
{
   printf("\t1.最小公倍数\n");
   printf("\t2.计算日期\n");
   printf("\t3.判断是否为闰年\n");
   printf("\t4.清屏\n");
   printf("\t0.退出\n");
   printf("\t请重新选择(0~4):");
}

bool Process(int choice, char *path[],char*  argv[])
{
   pid_t pid = fork();
   if(pid == 0)
    {
       execv(path[choice-1],argv+2*choice-2);
       exit(0);
    }
   else if(pid > 0)
   {
       waitpid(pid,&status,0);
       return true;
   }
   else if(pid < 0)
   {
       printf("create process1 erroe\n");
       exit(-1);
   } 
}

int main()
{
   char *path[]={"MaxGcd","GetDate","JudgeLeapYear"};
   char* argv[]={"./MaxGcd",NULL,"./GetDate",NULL,"./JudgeLeapYear",NULL};

   while(1)
  {
    
    Meau();
    while(scanf("%d",&choice) == EOF)
   {
        printf("\t输入有误，请重新输入：\n");
   }

    switch(choice)
   {
     case 0:
            _exit(0);
	    break;
     case 1:
	    Process(choice,path,argv);    
        break;
     case 2:
	    Process(choice,path,argv);
	    break;
     case 3: 
	    Process(choice,path,argv);
	    break;
     case 4:
	    printf("\033c");// \033  ==  \x1B == 27 == ESC
	    break;
   }
 }
     return 0;
}
