#include "Transfer.h"

void TransferServer::ConnectEventHandle(int fd)
{
	//测试
	//TraceLog("connect socks5 server");
	int Socks5fd = socket(AF_INET, SOCK_STREAM, 0);
	if (Socks5fd < 0)
	{
		ErrorLog("socket");
		return;
	}
	if (connect(Socks5fd, (struct sockaddr*)&_socks5addr, sizeof(_socks5addr)) < 0)
	{
		ErrorLog("connet socks5 server");
		return;
	}
	
	//创建链接与客户端服务通道
	Connect* connect = new Connect();
	connect->_ClientChannel._fd = fd;
	connect->_ClientChannel._event = EPOLLIN;
	OpenEvent(fd, connect->_ClientChannel._event, EPOLL_ADD);

	connect->_ServerChannel._fd = Socks5fd;

	_connectMap[fd] = connect;
	_connectMap[Socks5fd] = connect;
}
void TransferServer::ReadEventHandle(int fd)
{
	//用于测试TraceLog("ReadEventHandle");
	map<int, Connect*>::iterator it = _connectMap.find(fd);
	if (it != _connectMap.end())
	{
		Connect* connect = it->second;
		Channel* clientChannel = &(connect->_ClientChannel);
		Channel* serverChannel = &(connect->_ServerChannel);

		if (fd == serverChannel->_fd)
		{
			swap(clientChannel, serverChannel);
		}
		Forwordind(clientChannel,serverChannel);


	}
}
void TransferServer::WriteEventHandle(int fd)
{
//	TraceLog("WriteEventHandle");
}

//测试服务启动
int main()
{
	TransferServer server("191.168.122.1",8001,8000);
	server.Start();
} 
