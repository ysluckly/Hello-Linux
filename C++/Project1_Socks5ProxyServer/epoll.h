#define __EPOLL_H__
#ifdef __EPOLL_H__

#include "common.h"
#include "encry.h"

class IgnoreSigPipe
{
public:
	IgnoreSigPipe()
	{
		::signal(SIGPIPE, SIG_IGN);
	}
};

static IgnoreSigPipe initPIPE_IGN;


class EpollServer
{
public:
	EpollServer(int port)
		:_port(port)
		,_listenfd(-1)
		,_eventfd(-1)
	{}

	virtual ~EpollServer()
	{
		if(_listenfd != -1)
			close(_listenfd);
	}

	void OPEvent(int fd, int events, int op)
	{
		struct epoll_event event;
		event.events = events;
		event.data.fd = fd;
		if(epoll_ctl(_eventfd, op, fd, &event) < 0)
		{
			ErrorLog("epoll_ctl(op:%d, fd:%d)", op, fd);
		}
	}

	void SetNonblocking(int fd)
	{
		{
			int flags, s;
			flags = fcntl (fd, F_GETFL, 0);
			if (flags == -1)
				ErrorLog("SetNonblocking:F_GETFL");

			flags |= O_NONBLOCK;
			s = fcntl (fd, F_SETFL, flags);
			if (s == -1)
				ErrorLog("SetNonblocking:F_SETFL");
		}
	}

	enum Socks5State
	{
		AUTH,				// 身份认证
		ESTABLISHMENT,		// 建立连接
		FORWARDING,			// 转发
	};

	struct Channel
	{
		int _fd;	   // 描述符
		string _buff;  // 写缓冲

		Channel()
			:_fd(-1)
		{}
	};

	struct Connect
	{
		Socks5State _state;		// 连接的状态
		Channel _clientChannel;
		Channel _serverChannel;
		int _ref;

		Connect()
			:_state(AUTH)
			,_ref(0)
		{}
	};

	void Start();
	void EventLoop();

	void SendInLoop(int fd, const char* buf, int len);
	void Forwarding(Channel* clientChannel, Channel* serverChannel,
		bool sendencry, bool recvdecrypt);
	void RemoveConnect(int fd);

	// 多态实现的虚函数
	virtual void ConnectEventHandle(int connectfd) = 0;
	virtual void ReadEventHandle(int connectfd) = 0;
	virtual void WriteEventHandle(int connectfd);

protected:
	int _port;	   // 端口
	int _listenfd; // 监听描述符
	int _eventfd;  // 事件描述符

	map<int, Connect*> _fdConnectMap; // fd映射连接的map容器
};

#endif //__EPOLL_H__
