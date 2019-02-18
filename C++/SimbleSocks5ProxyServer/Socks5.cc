
#include "Socks5.h"

void Socks5Server::ConnectEventHandle(int connectfd)
{
	
	//添加connectfd到epoll,监听读事件
	SetNonBlocking(connectfd);	  //阻塞交给管理去工作
	OpenEvent(connectfd, EPOLLIN, EPOLL_CTL_ADD);

	Connect *con = new Connect();
	con->_state = AUTH;
	con->_ClientChannel._fd = connectfd;
	_connectMap[connectfd] = con;
	con->


}
//0,表示数据没到，继续等
//1，成功
//-1，失败
int Socks5Server::AuthHandle(int fd)
{
	char buf[260]; //256+7
	int rlen = recv(fd, buf, sizeof(buf),MSG_PEEK); //不把数据真实读走
	if (rlen == -1)
	{
		return -1;
	}
	else if (rlen < 3)
	{
		return 0;
	}	
	else
	{
		recv(fd, buf, rlen, 0);
		if (buf[0] != 0x05)
		{
			ErrorLog("not socks5");
			return -1;
		}
		return 1;
	}
}
//失败 -1
//数据没到， -2 //sock可能为0
//成功   serverfd
int Socks5Server::Establishment(int fd)
{
	char buf[256];
	int rlen = recv(fd, buf, 256, MSG_PEEK);
	if (rlen == 0)
	{
		return -2;
	}
	else if (rlen == -1)
	{
		return 	-1;
	}
	else  
	{
		char ip[4];
		char port[2];
		recv(fd, buf, 4, 0);
		char addresstype = buf[3];
		if (addresstype == 0x01)  //ipv4
		{
			recv(fd, ip, 4, 0);
			recv(fd, port, 2, 0);
		}
		else if (addresstype == 0x03)//domainname
		{

			char len = 0;
			recv(fd, &len, 1, 0);
			recv(fd, buf, len, 0);
			recv(fd, port, 2, 0);
			TraceLog("Domain:%s,", buf);

			//如何获取域名的  gethostbyname 
			buf[len] = '\0';
			struct hostent* hostptr = gethostbyname(buf);
			memcpy(ip, hostptr->h_addr, hostptr->h_length);
		}
		else if (addresstype == 0x04) //ipv6
		{
			ErrorLog("not support ipv6");
			return -1;
		}

		else
		{
			ErrorLog("inval address type");
				return -1;
		}
		struct sockaddr_in addr;
		bzero(&addr, sizeof(addr));

		addr.sin_family = AF_INET;
		memset(&addr.sin_addr.s_addr, ip, 4);
		addr.sin_port = *((uint16_t*)port);
		int serverfd = socket(AF_INET, SOCK_STREAM, 0);
		if (serverfd < 0)
		{
			ErrorLog("socket");
			return -1;
		}
		if (connect(serverfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		{
			ErrorLog("connet");
			close(serverfd);
			return -1;
		}

		return serverfd;
	}
}
void Socks5Server::RemoveConnect(int fd)
{

}

void Socks5Server::Forwarding(Channel* clientChannel, Channel* serverChannel)
{
	char buf[4096];
	int rlen = recv(clientChannel->_fd, buf, 4096, 0);
	if (rlen < 0)
	{
		ErrorLog("recv %d",clientChannel->_fd);
	}
	else if (rlen == 0)		  //shutdown,  close 区别
	{
		shutdown(serverChannel->_fd, SHUT_WR);
		RemoveConnect(clientChannel->_fd);
	}
	else
	{
		send(serverChannel->_fd, buf, rlen, 0);
	}

	send(serverChannel->_fd, buf, rlen, 0);
}

void Socks5Server::ReadEventHandle(int connectfd)
{
	TraceLog("read event:%d ", connectfd);
	map<int, Connect*>::iterator it = _connectMap.find(connectfd);
	if (it != _connectMap.end())
	{
		Connect* con = it->second;
		if (con->_state == AUTH)
		{
			char reply[2];
			reply[0] = 0x05;//版本
			int ret = AuthHandle(connectfd);
			if (ret == 0)
			{
				return;
			}
			else if (ret == 1)
			{
				reply[0] = 0x00;
			}
			else if (ret == -1)
			{
				reply[0] = 0xFF;
			}
			if (send(connectfd, reply, 2, 0) != 2)
			{
				ErrorLog("auth reply");
			}
		}
		else if (con->_state == ESTABLISHMENT)
		{
			//REPLY
			char reply[10] = { 0 };
			reply[0] = 0x05;

			int ret = Establishment(connectfd);//域名最多256字符
			if (serverfd == -1)
			{
				ErrorLog("EstablristmentHandle ");
				reply[1] = 0x01;
				rerturn 0;
			}
			else if (serverfd == -2)
			{

				return;
			}
			else
			{
				reply[1] = 0x00;
			}
			if (send(connectfd, reply, 10, 0) != 10)
			{
				ErrorLog("EstablristmentHandle reply ");
			}
			SetNonBlocking(serverfd);
			OpenEvent(serverfd, EPOLLIN, EPOLL_CTL_ADD);
			con->_state = FORWARDING;
			con->_ServerChannel._fd = serverfd;
			_connectMap[serverfd] = con;
			con->_state = FORWARDING;
		}
		else if (con->_state == FORWARDING)
		{
			Channel* clientChannel = &con->_ClientChannel;
			Channel* serverChannel = &con->_ServerChannel;
			if (connectfd == serverChannel->_fd)
			{
				swap(clientChannel, serverChannel);
			}

			Forwarding(clientChannel, serverChannel);
														  

		}
		else
		{
			assert(false);
		}
	}
}
void Socks5Server::WriteEventHandle(int connectfd)
{
	TraceLog("ReadEventHandle");

}
int main()
{
  Socks5Server server("192.168.122.1",8000,8000);
  server.Start();
}
