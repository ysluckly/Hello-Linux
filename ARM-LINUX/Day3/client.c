/*************************************************************************
	> File Name:    client.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: 2019年06月07日 星期五 11时38分05秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc,const char* argv[])
{
	if(argc != 3)
	{
		printf("Usage:%s [ip] [port]\n",argv[0]);
		return 0;
	}

	//创建一个用来通讯的socket
	int sock = socket(AF_INET,SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return 1;
	}

	//需要connect的是对端的地址，因此这里定义服务器端的地址结构体
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
	socklen_t len = sizeof(struct sockaddr_in);

	if(connect(sock, (struct sockaddr*)&server, len) < 0 )
	{
		perror("connect");
		return 2;
	}
	//连接成功进行收数据
	while(1)
	{
	    char buf[1024]={0};
        char rbuf[1024]={0};
		
        
        printf("Please Enter#:");
        fflush(stdout);
        scanf("%s",buf); 
        
        write(sock, buf, sizeof(buf));

        printf("服务器响应#:");
        fflush(stdout);
        printf("%s\n",buf);
	}
	close(sock);

	return 0;
}

