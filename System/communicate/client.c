#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("mypipe",O_WRONLY);
    if(fd<0)
    {
        perror("fail open");
        exit(1);
    }
     
    char buf[1024];
    //发送消息
    while(1)
    {
        printf("Please input # ");
        fflush(stdout);

        //scanf易出现错误，此处用read获取往信道发送的信息
        ssize_t s = read(0,buf,sizeof(buf)-1);
        if(s<0)
        {
            perror("fail read\n");
            exit(1);
        }
        else if(s==0)
        {
            printf("read over\n");
            exit(0);
        }
        else
        {
            buf[s] = 0;
            write(fd, buf,strlen(buf));
        }

    }



    close(fd);
    return 0;
}
