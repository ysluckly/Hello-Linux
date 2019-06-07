/*************************************************************************
	> File Name:    Day.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: Wed 29 May 2019 07:08:53 AM PDT
 ************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#define MAX_SIZE 1000  
int main(int argc,char* arg[])
{
        int fd;
        ssize_t length_w,length_r = MAX_SIZE,ret;
        char *testwrite ="Hello.text";
        char buffer_write2[] = "This is My Schoolnumber:16407010124\n";        
        char buffer_read[MAX_SIZE]={0};     
        if((fd = open(testwrite,O_CREAT | O_RDWR|O_APPEND,0777))<0)
        {  
            printf("open %s failed\n",testwrite); 
        } 
     
        write(fd,buffer_write2,strlen(buffer_write2));
        close(fd);
        if((fd = open(testwrite,O_RDWR|O_CREAT,0777))<0) 
            printf("open %s failed!\n",testwrite); 
        if((ret = read(fd,buffer_read,MAX_SIZE))<0)
        {
            printf("faild  open \n");
        }
        printf("Files Content is\n%s \n",buffer_read);
      close(fd);
      return 0;
}

