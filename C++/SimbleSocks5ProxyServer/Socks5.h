#ifndef __SOCKS5__H__
#define __SOCKS5__H__

#include "Epoll.h"

class Socks5Server:public EpollServer
{
public:
	Socks5Server()
	{}

	int  AuthHandle(int fd);
	int  Establishment(int fd);
	void Forwarding(Channel* clientChannel, Channel* serverChannel);
	void RemoveConnect(int fd);

	void ConnectEventHandle(int fd);
	void ReadEventHandle(int fd);
	void WriteEventHandle(int fd);

protected:


};

#endif //__SOCKS5__H__