/*************************************************************************
	> File Name:    server.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: 2019年06月07日 星期五 11时33分49秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int startup(int _port,const char* _ip)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	int opt=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons( _port);
	local.sin_addr.s_addr = inet_addr(_ip);
	socklen_t len = sizeof(local);

	if(bind(sock,(struct sockaddr*)&local , len) < 0)
	{
		perror("bind");
		exit(2);
	}

	if(listen(sock, 5) < 0)	//允许连接的最大数量为5
	{
		perror("listen");
		exit(3);
	}

	return sock;
}

int main(int argc,const char* argv[])
{
	if(argc != 3)
	{
		printf("Usage:%s [loacl_ip] [loacl_port]\n",argv[0]);
		return 1;
	}

	int listen_sock = startup(atoi(argv[2]),argv[1]);//初始化

	//用来接收客户端的socket地址结构体
	struct sockaddr_in remote;
	socklen_t len = sizeof(struct sockaddr_in);

	while(1)
	{
		int sock = accept(listen_sock, (struct sockaddr*)&remote, &len);
		if(sock < 0)
		{
			perror("accept");
			continue;
		}

		//每次建立一个连接后fork出一个子进程进行收发数据
		pid_t id = fork();
		if(id > 0)
		{//father
		    waitpid(-1, NULL, WNOHANG);
			close(sock);
		}
		else if(id == 0)
		{//child
			printf("get a client, ip:%s, port:%d\n",inet_ntoa(remote.sin_addr),ntohs(remote.sin_port));
			
			char rbuf[1024]={0};
            while(1)
			{
                ssize_t _s = read(sock, rbuf, sizeof(rbuf)-1);
				if(_s > 0)
				{
					rbuf[_s] = 0;
					printf("client#: %s\n",rbuf);
                }
			}
		}
		else
		{
			perror("fork");
			return 2;
		}
	}
	return 0;
}
