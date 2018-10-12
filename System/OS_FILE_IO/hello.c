////////////////////////OS_IO
//
/////////////////////////open vs write
/*
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main()
{
    umask(0);
    int fd = open("myfile",O_WRONLY|O_CREAT,0644 );
    if(fd<0)
    {
        perror("open");
        return 1;
    }
    int count = 5;
    const char *p = "hello linux\n";
    int len = strlen(p);

    while(count--)
    {
        write(fd,p,len);//fd:文件描述符 p:缓冲区首地址 len:读取期望长度， 返回值为实际读取长度


    }

    close(fd);
    return 0;
}*/

/////////////////////////open vs read
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()

{
    int fd = open("myfile",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        return 1;
    }
    const char *p = "hello linux\n";
    char buf[1024];

    while(1)
    {
    
        size_t s= read(fd,buf,strlen(p));

        if(s>0)
        {
            printf("%s",buf);
        
        }
        else{
            break;
        }
    }


    close(fd);
    return 0;
}

*/

////////////////////文件描述符的分配规则
//总是分配最小的且没有被使用的系统描述符
//1.第一个文件描述符为3
/*
#include <stdio.>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("myfile",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        return 1;
    
    }

    printf("fd:%d",fd);//3

    close(fd);
    return 0;

}
/////////////////////////0/2可见

#include <stdio.>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    close(2);
   // close(0);//数字代表对应的文件描述符
    int fd = open("myfile",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        return 1;
    
    }

    printf("fd:%d",fd);
    close(fd);
    return 0;
}

*/

///////////////////////重定向
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl>
#include <stdlib.h>

int main()
{
    umask(0);//将掩码改为0
    close(1); //关闭标准输出
    int fd = open("myfile",O_WRONLY|O_CREAT, 0644);
    if(fd<0)
    {
        perror("open");
        return 1;
    }

    printf("fd:%d",fd);
    fflush(stdout);

    close(fd);
    return 0;


}


