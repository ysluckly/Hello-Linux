#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
using namespace std;

void mydaemon()
{
  umask(0);  //1.设置屏蔽字

  int i;
  int fd0;
  pid_t pid;
  struct sigaction sa;
  pid_t id = fork();//2.fork子进程，父进程退出

  if(id>0)
  {
    exit(0);
  }

  setsid(); //调用setsid创建一个会话

  sa.sa_handler = SIG_IGN; //忽略SIGCHLD
  sigemptyset(&sa.sa_mask);

  sa.sa_flags = 0;

  //子进程退出忽略此信号
  if(sigaction(SIGCHLD,&sa,NULL)<0)
  {
    return ;
  }

  chdir("/");

  //关闭不需要的文件描述符
 close(0); 

 close(1); 

 close(2); 
}

int main()
{
  mydaemon();
  while(1)
  {
    sleep(1);
  }
  return 0;
}
