#include "Epoll.h"
#include "Header.h"

//启动服务，开始监听
void EpollServer::Start()
{
	_listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenfd == -1)
	{
		ErrorLog("create socket");
		return;
	}
	
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htonl(_port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//一个机器可能多个网卡，在每个网卡都为了监听

	if (bind(_listenfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		ErrorLog("bind socket");
		return;
	}
	
	if (listen(_listenfd, 100) < 0)
	{
		ErrorLog("listen socket");
		return;
	}

	//event
	_eventfd = epoll_create(_MAX_EVENT);
	if (_eventfd == -1)
	{
		ErrorLog("create epoll");
		return;
	}
	//添加一个读事件
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = _eventfd;

	if (epoll_ctl(_eventfd, EPOLL_CTL_ADD, _listenfd, event) < 0) //为什么_listenffd传两次
	{
		ErrorLog("EPOLL_CTL_ADD listenfd EPOLLIN");
		return;
	}

	//添加listenfd到epoll，监听链接事件
	OpenEvent(_listenfd, EPOLLIN, EPOLL_CTL_ADD);

	//事件循环，即epoll服务器循环监听
	EventLoop();
}
//事件循环
void EpollServer::EventLoop()
{
	struct epoll_event events[_MAX_EVENT];
	while (1)
	{
		int ret = epoll_wait(_eventfd, events, _MAX_EVENT, 0); //返回事件数
		if (ret == -1)
		{
			ErrorLog("epoll wait");
			return;
		}

		for (size_t i = 0; i < ret; ++i)
		{
			if (events[i].data.fd == _listenfd)
			{
				struct sockaddr addr;
				socklen_t len;
				int connectfd = accept(_listenfd, (struct sockaddr*)&addr, &len);
				if (connectfd < 0)
				{
					ErrorLog("accept error ");
					continue;
				}
				//看谁连过来的
				TraceLog("client connect");
				ConnectEventHandle(connectfd);
			}
			//可能还添加其他套接字读事件
			else if (events[i].events&EPOLLIN)
			{
				ReadEventHnadle(events[i].data.fd);
			}
			//可能还添加其他套接字写事件
			else if (events[i].events&EPOLLOUT)
			{
				WriteEventHandle(events[i].data.fd)
			}
			else
			{
				ErrorLog("events error");
			}
		}
	}


}
void EpollServer::Forwordind(Channel* clientChannel, Channel* serverChannel)
{
	const size_t BUF = 4096;
	char buffer[BUF];
	int rlen = recv(clientChannel->_fd, buffer, sizeof(buffer),0);
	if (rlen > 0)
	{
		int slen = send(serverChannel->_fd,buffer,rlen,0);
		if (slen < rlen)
		{
			SendInLoop() //交给时间循环，继续发送
		}
	}
	else if (rlen == 0)
}