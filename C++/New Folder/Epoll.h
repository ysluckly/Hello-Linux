#ifndef __EPOLL__H__
#define __EPOLL__H__

#include "Header.h"
#include "TraceLog.h"
const size_t EpollServer::_MAX_EVENT = 1000;

class EpollServer
{
public:
	EpollServer(int port = 8000)	//socks5默认端口1080，容易被查，所以换了
		:_port(port)
		, _listenfd(-1)
		, _eventfd(-1)
	{}

	//来一个请求，就要读一下，//事件来了在处理（反应堆模式）
	void OpenEvent(int fd, int eventd, int how)	   //event 增删概事件，，how增删改操作
	{
		struct epoll_event event;
		event.events = events;
		event.data.fd = fd;		//用户数据，
		if (epoll_ctl(_eventfd, fd,how, &event) <0)	 //为什么传两次fd,
		{

			ErrorDebug("epoll_ctl.fd:%d+how:%d",fd,how);
			return;
		}
	}

	void SetNonBlocking(int fd)
	{
		{
			int flags, s;
			flags = fcntl(fd, F_GETFL, 0);
			if (flags == -1)
				ErrorLog("SetNonBlocking:F_GETFL");
			flags |= O_NONBLOCK;
			s = fcntl(fd, PCF_SETFL, flags);
			if (s == -1)
				ErrorLog("SetNonBlocking:F_SETFL");
		}
	}
	

	//启动服务，开始监听
	void Start();

	//事件循环
	void EventLoop();

	//处理读写事件
	virtual void ConnectEventHandle(int fd) = 0;  //纯虚函数，子类必须重写
	virtual void ReadEventHandle(int fd) = 0;
	virtual void WriteEventHandle(int fd) = 0;
	

	enum Socks5State
	{
		AUTH,//身份认证
		ESTABLISHMENT,//建立连接
		FORWARDING, //转发
	};

	//基于epoll水平触发，没收到，下次还会通知，通道：保存相关信息
	struct Channel
	{
		int _fd;//socket 描述符
		int _event;//事件
		string _buffer; //缓存区，对于部分消息的存储

		Channel()
			: _fd(-1)
			, _event(0)
		{}

	};


	//链接
	struct Connect
	{
		Connect()
		:_state(AUTH)
		, _ref(0)

		{}
		Socks5State _state;  //链接状态
		Channel _ClientChannel;
		Channel _ServerChannel;
		int _ref;
	};

	void Forwordind(Channel* clientChannel, Channel* serverChannel);

	// 当一个父类指针指向子类，没有多态，就会只调用父类，不调用子类
	//虚函数保证先调子类在掉父类	
	virtual ~EpollServer()
	{
		if (_listenfd == -1)
		{
			close(_listenfd);
		}
	}
private:
	//防拷贝
	EpollServer(const EpollServer& e);
	EpollServer& operator=(const EpollServer& e);

protected:
	int _listenfd; //监听套接字
	int _port;	//服务端口

	int _eventfd; //事件描述符
	static const size_t _MAX_EVENT;//事件最大数

	map<int, Connect*> _connectMap; //key 描述符，，val是通道类型
};

#endif //__EPOLL__H__