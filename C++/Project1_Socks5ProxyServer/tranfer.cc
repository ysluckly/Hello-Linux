#include "tranfer.h"

// 多态实现的虚函数
void TranferServer::ConnectEventHandle(int connectfd)
{	
	int serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverfd == -1)
	{
		ErrorLog("socket");
		return;
	}

	if (connect(serverfd, (struct sockaddr*)&_socks5addr, sizeof(_socks5addr)) < 0)
	{
		ErrorLog("connect socks5");
		return;
	}

	// 设置成非阻塞，并且添加到epoll
	SetNonblocking(connectfd);
	OPEvent(connectfd, EPOLLIN, EPOLL_CTL_ADD);

	SetNonblocking(serverfd);
	OPEvent(serverfd, EPOLLIN, EPOLL_CTL_ADD);

	Connect* con = new Connect;
	con->_state = FORWARDING;

	con->_clientChannel._fd = connectfd;
	con->_ref++;
	_fdConnectMap[connectfd] = con;

	con->_serverChannel._fd = serverfd;
	con->_ref++;
	_fdConnectMap[serverfd] = con;
}

void TranferServer::ReadEventHandle(int connectfd)
{
	map<int, Connect*>::iterator it = _fdConnectMap.find(connectfd);
	if (it != _fdConnectMap.end())
	{
		Connect* con = it->second;
		Channel* clientChannel = &con->_clientChannel;
		Channel* serverChannel = &con->_serverChannel;
		bool sendencry = true, recvdecrypt = false;
		if (connectfd == con->_serverChannel._fd)
		{
			swap(clientChannel, serverChannel);
			swap(sendencry, recvdecrypt);
		}
		
		Forwarding(clientChannel, serverChannel
			,sendencry, recvdecrypt);
	}
	else
	{
		assert(false);
	}
}

int main()
{
	TranferServer server(8000, "192.168.122.1", 8001);
	server.Start();
}
