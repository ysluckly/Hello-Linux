#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define FIFONAME "mypipe"

int main()
{
    // 创建命名管道
    mkfifo(FIFONAME, 0644);
    
    //打开管道
    int fd = open(FIFONAME,O_RDONLY);
    if(fd<0)
    {
        perror("fail to open");
        exit(1);
    }
    
    char buf[1024];
    //读取管道文件
    while(1)
    {
        printf("Please Waiting...\n");
        fflush(stdout);
        ssize_t s = read(fd,buf,sizeof(buf)-1);
        //读取失败
        if(s<0)
        {
            printf("reading faild!\n");
            exit(1);
        }
        //读取完毕
        else if(s == 0)
        {
            printf("client quit，server quit too！\n");
            exit(EXIT_SUCCESS);
        }
        //读取中,,,
        else
        {
            buf[s-1] = 0;
            printf("client# %s\n",buf);
        }
    }

    close(fd);
    return 0;

}
