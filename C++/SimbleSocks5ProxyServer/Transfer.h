#ifndef __TRANSFER__H__
#define __TRANSFER__H__

#include "Epoll.h"
//不用epoll的话，多打几个网页就不信了
//需要transfer的原因：在本地，进行直接转发，没有加密，会被抓包，所以加一个转发服务，起着加密，转发作用
class TransferServer:public EpollServer
{
public:
	TransferServer(const char* Socks5ServerIp,int Socks5ServerPort,int SelfPort = 8000)//不需要本地ip，自动识别地址获取
		:EpollServer(SelfPort)
	{
		bzero(&_socks5addr, sizeof(_socks5addr);
		_socks5addr.sin_family = AF_INET;
		_socks5addr.sin_port = htonl(Socks5ServerPort);
		_socks5addr.sin_addr.s_addr = inet_addr(Socks5ServerIp);
	}
	virtual void ConnectEventHandle(int fd);
	virtual void ReadEventHandle(int fd);
	virtual void WriteEventHandle(int fd);

	//子类不写也可以，是因为会继承父类析构，父类析构中先析构子类在析构父类
	virtual ~TransferServer()
	{}
protected:
	struct sockaddr_in _socks5addr; //Sock5Server的地址
};

#endif //__TRANSFER__H__