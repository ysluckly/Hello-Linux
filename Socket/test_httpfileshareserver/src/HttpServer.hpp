#include "ThreadPool.hpp"
#include "Utils.hpp"

#define MAX_LISTEN 5
#define MAX_THREAD 5


class HttpServer
{
//建立一个tcp服务端程序，接受新链接
//为新链接组织一个线程池任务，添加到线程池中
private:
	int _ser_sock;
	ThreadPool* _tp;
private:
  //http任务处理函数
	static bool (HttpHandler)(int sock)//http任务处理函数
	{
		RequestInfo info;
		HttpRequest req(sock);
	//	HttpResponse rsp(sock);
		
    //接受http头部
		if(req.RecvHttpHeader(info) == false)
		{
			goto out;
		}
		
   /* //解析http头部
		if(req.ParseHttpHeader(info) == false)
		{
			goto out;
		}
    
    //判断请求释放cgi请求类型
		if(info.RequestIsCGI())
		{
      //若请求为cgi请求，则执行cgi响应
			rsp.CGIHandler()；
		}
		else
		{
      //若不是cgi请求，执行目录列表或者文件下载响应
			rsp.FileHandler();
		}*/
		
    close(sock);
    return true;
out:
	//	rsp.ErrHandler(info);//专门处理错误。拿错误编号组织响应头部，给客户端返回
		close(sock);
		return false;
	}
public:
	HttpServer():_ser_sock(-1),_tp(NULL){}
	//完成tcp服务端socket的初始化，线程初始化
	bool HttpServerInit(std::string ip,int port)
	{
		_ser_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
    //创建套接字的同时，会创建一个结构体，结构体有两个队列
    //一个是发送缓存区 一个是接收缓存区，这个缓冲区会有sip sport //监听地址 dip  dport//对端地址信息  proto 协议五元组标志
    //网卡根据发送数据的目的ip port，将数据放进对应套接字接收缓存区（）
    ////也就是fdsock 通过结构体找到队列，通过描述符读取信息就是在缓冲区读取信息
    //缓冲区在内核,结构体本身在内核创建
    if(_ser_sock)
    {

      LOG("sock error : %s\n",strerror(errno));
		  return false;
    }
		
		sockaddr_in lst_addr;
		lst_addr.sin_family= AF_INET;
		lst_addr.sin_port = htons(port);//htons/htonl区别
    lst_addr.sin_addr.s_addr = inet_addr(ip.c_str());
		socklen_t len = sizeof(sockaddr_in);
		
		
		if(bind(_ser_sock,(sockaddr*)&lst_addr,len)<0)
		{
			LOG("bind socket error:%s\n",strerror(errno));
			close(_ser_sock);
			return false;
		}
		if(listen(_ser_sock,MAX_LISTEN)<0)
		{
			LOG("listen socket error:%s\n",strerror(errno));
			close(_ser_sock);
			return false;
		}
		
		_tp = new ThreadPool(MAX_THREAD);
		if(_tp == NULL)
		{
			LOG("threadpool malloc error!!\n");
			return false;
		}
		if(_tp->ThreadPoolInit() == false)
		{
			LOG("threadpool init error!!\n");
			return false;
		}
		
		return true;
	}
	
  //开始获取客户端新链接-创建任务，任务入队
	bool Start()
	{
		while(1)
		{
			sockaddr_in addr;
			socklen_t len = sizeof(sockaddr_in);
			int sock = accept(_ser_sock,(sockaddr*)&addr,&len);
			if(sock<0)
			{
				LOG("listen socket error:%s\n",strerror(errno));
				continue;
				
			}
			HttpTask ht;
			ht.SetHttpTask(sock,HttpHandler);
      _tp->PushTaskQueue(ht);

		}
    return true;
	}
};

int main(int argc,char* argv[])
{

  std::string ip = argv[1];
  int port = atoi(argv[2]);

  HttpServer hs;
  hs.HttpServerInit(ip,port);
  hs.Start();
  return 0;
}

