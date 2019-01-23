#ifndef __SOCKS5_H__
#define __SOCKS5_H__

#include "epoll.h"

class Sock5Server : public EpollServer
{
public:
	Sock5Server(int port)
		:EpollServer(port)
	{}

	int AuthHandle(int fd);
	int EstablishmentHandle(int fd);

	virtual void ConnectEventHandle(int connectfd);
	virtual void ReadEventHandle(int connectfd);

	//virtual void WriteEventHandle(int connectfd);

protected:

};

#endif //__SOCKS5_H__
