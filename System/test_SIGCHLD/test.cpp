#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
void hander(int sig)
{
    pid_t id;
    while((id =waitpid(-1,NULL,WNOHANG))>0)
    {
        cout<<"wait id sucseed"<<id<<endl;
    }
    cout<<"chid di quit"<<getpid()<<endl;

}
int main()
{
    signal(SIGCHLD,hander);
    pid_t pid;
    if((pid = fork())==0)//chid
    {
        cout<<"chid ....."<<getpid()<<endl;
        sleep(3);
        exit(1);
    }
    while(1)
    {
        cout<<"father is busy"<<endl;
        sleep(1);   
    }
    return 0;
}
