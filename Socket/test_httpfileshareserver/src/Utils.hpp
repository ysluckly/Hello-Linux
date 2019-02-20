#pragma once 

#include <iostream>
#include <unistd.h>
#include <queue>
#include <mutex>
#include <pthread.h> 
#include <stdio.h>
#include <unordered_map>
#include <string>
#include <string.h>
#include <vector>
#include <errno.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/stat.h>
#define LOG(...) do{fprintf(stdout,__VA_ARGS__);fflush(stdout);}while(0) //指定写到某目录 

#define MAX_HEADER  4096


//请求解析结果
class RequestInfo
{
//包含request解析出的的请求信息
private:
	std::string _method;//请求方法
	std::string _version;//协议版本
	std::string _path_info;//资源路径
	std::string _path_phys;//资源实际具体路径
	std::string _query_string;//客户端提供的查询字符串
	std::unordered_map<std::string,std::string> _har_list; //解析出的键值对组成的链表
	struct stat _st;//stat结构体，通过文件名获取文件详细信息
public:
	std::string _err_code;//错误码
	void SetErrCode(const std::string code)
	{
		_err_code = code;
	}

  //判断请求类型
	bool RequstIsCGI()
	{
		if((_method == "POST") || ((_method == "GET" && _query_string.empty())))
		{
			return false;
		}
		return true;
		
	}
	
};


//http请求
class HttpRequest
{
//http数据接收接口
//http数据解析接口
//对外提供能够获取处理结果的接口
private:
	int _cli_sock;
	std::string _http_header;
	
	
public:
	HttpRequest(int sock):_cli_sock(sock){}
	//接收http请求头
	bool RecvHttpHeader(RequestInfo& info)
	{
		char buf[MAX_HEADER];
		//接收在当前套接字缓冲区,MSG_PEEK指针指向缓冲区的指针
		while(1)
		{
			int ret = recv(_cli_sock,buf,sizeof(buf),MSG_PEEK);
      //接收数据放在套接字缓冲区，可能头部与正文大小在sizeof（buf）内，可能一次性把正文也取走了
      //所以需要探测\r\n\r\n,返回前面即可，所以通过MSG_PEEk探测性的查看缓冲区而不取走数据
      //可能会失败：recv=0就是对端关闭连接  【程序里怎样查看对端关闭连接？recv  = 0，send触发sigpad信号】
			if(ret <= 0)
			{
			  
				if(errno == EINTR || errno == EAGAIN) //此时是阻塞的，当数据就绪时才会读取，就绪与读取的过程有一段等待的时间
      //    ，这段等待时间是会被信号打断的，万一被信号打断就报EINTR，表示被信号打断，只需要重新读取就好，EAGAIN只是在非阻塞情况的错误，就是数据未就绪就读取就会报错，只有非阻塞情况会报EAGAIN错误
				{
          //认为这个错误可以原谅，重新读取就好
					continue;
				}
				info.SetErrCode("500");//读取数据失败，认为是服务端错误
				return false;
			}

			char *ptr = strstr(buf,"\r\n\r\n");
			if((ptr == NULL)&&(ret == MAX_HEADER))
			{
				info.SetErrCode("413");//由于请求的实体过大，服务器无法处理，因此拒绝请求
				return false;
				
			}
      else if((ptr == NULL) && ret < MAX_HEADER)
      {
        usleep(1000);
        continue; //可能数据没读取完
      }

			int hdr_len = ptr - buf;
			_http_header.assign(buf,hdr_len);
			recv(_cli_sock,buf,hdr_len+4,0); //将头部从缓冲区移除，只剩正文，0阻塞
	    LOG("header:[%s]\n",_http_header.c_str());
      break;
		}
			return true;
	}
};
/*	
	bool PathIsLegal(std::string &path,RequestInfo &info)
	{
		std::file = WWWROOT + path;
		if(stat(file.c_str(),&info._st)<0)
		{
			info._err_code = "404";
			return false;
		}
		char tmp[MAX_PATH] = {0};
		//realpath:将一个路径转换为绝对路径，若地址不存在，就会造成段错误，
		realpath(path.c_str(),tmp);
		info._path_phys = tmp;
		
		if(info._path_phys.find(WWWROOT) == std::string::npos)
		{
			info._err_code = "403";
			return false;
		}
		return true;
	}
	bool ParseFirstLine(std::string &list,RequestInfo &info)
	{
		std::vector<std::string> line_list ;
		if(Utils::Split(_http_header," ",line_list) != 3)
		{
			info._err_code = "400";
			return false;
		}
		
		std::string url;
		info._method = line_list[0];
		info.url = line_list[1];
		info._version = line_list[2];
		
		if(info._method!="GET" && info._method != "POST" && info._method != "HEAD")
		{
			
			info._err_code = "405";
			return false;
		}
		
		if(info._version!="HTTP/0.9" && info._version != "HTTP/1.0" && info._version != "HTTP/1.1")
		{
			
			info._err_code = "400";
			return false;
		}
		
		//url  www/load/../..?key=val&key=val
		//realpath:将一个路径转换为绝对路径，若地址不存在，就会造成段错误，
		size_t pos;
		pos = info.url,find("?");
		if(pos == std::string::npos)
		{
			info._path_info = url;
		}
		else{
			info._path_info = url.substr(0,pos);
			info._query_string = url.substr(pos+1);
		}
		
		
		return PathIsLegal(_path_info,_info);
		
	}
	bool ParseHttpHeader(RequestInfo& info)//解析http请求头
	{
		
		//请求方法 url 版本\r\n
		//键值对key: val\r\nkey: val
		
		//以\r\n进行分隔，取出字符串
		std::vector<std::string> hdr_list;
		Utils::Split(_http_header,"\r\n",hdr_list);
		
		//解析首行
		
		if(ParseFirstLine(hdr_list,info) == false)
		{
			return fasle;
		}
		hdr_list.erase(0);
		for(int i = 0;i<hdr_list.size();++i)
		{
			size_t pos = hdr_list[i]。find(": ");
			info._har_list[har_list[i].substr(0,pos)] = hdr_list[i].substr(pos+2);
		}
		
		for(auto it = info._har_list.begin();it != info._har_list.end();++it)
		{
			std::cout
		}
		return 
	}
	RequestInfo& GetRequestInfo();  //向外提供解析结果
	
}


class HttpResponse
{
//文件请求（完成文件下载，列表功能）接口
//CGI请求接口，调用外部程序上传功能
private:
	int _cli_sock;
	
	//ETag: "inode-fsize-mtime"\r\n
	std::string _etag;//表明文件是否是源文件，是否修改过
	std::string _mtime;//文件最后一次修改时间
	std::string _date; //系统响应时间
public:
	HttpResponse(int sock):_cli_sock(sock){}
	bool InitResponse(RequestInfo &req_info)//初始化一些响应信息
	{
		req_info._st.st_size;
		req_info._st.st_ino;
		req_info._st.st_mtime;
		Utils::DigitToStr(req_info._st.st_mtime,_mtime);
		
		Utils::MakeETag(req_info._st.st_size,req_info._st.st_ino,req_info._st.st_mtime);
		
		time_t t = time(NULL);
		Utils::TimeToGMT(t,_date);
		return ture;
		
	}
	//文件下载(文件名称)
	bool ProcessFile(RequestInfo& info)
	{
		return ture;
	}
	//文件列表（文件目录即路径）
	bool ProcessList(RequestInfo& info)
	{
		return ture;
	}
	//CGI请求处理（文件名称）
	bool ProcessCGI(RequestInfo& info)
	{
		return ture;
	}
	bool ErrHandler(RequestInfo& info)//处理错误响应
	{
		std::string rsp_hreader;
		//首行 版本  状态码 状态描述\r\n
		//头部 Content-Length Date
		//空行 
		//正文 rsp_body = "<html><body><h1>404;<h1></body></html>"
		
		rsp_hreader = info._version + " " + info._err_code + " ";
		rsp_hreader += Utils::GetErrDesc(info._err_code)+"\r\n";
		
		time_t t = time(NULL);
		sta::string gmt;
		Utils::TimeToGMT(t,gmt);
		
		rsp_header += "Date: "+gmt + "\r\n";
		
		std::string rsp_body;
		rsp_body = "<html><body><h1>"+info._err_code;
		rsp_body += "<h1></body></html>";
		
		std::string con_len;
		
		return true;
	}
	bool CGIHandler(RequestInfo& info)
	{
		InitResponse(info);//初始化cgi响应信息
		ProcessCGI(info);//指向cgi响应
	}
	bool FileHandler(RequestInfo& info)
	{
		InitResponse(info);//初始化file响应信息
		if(DIR)//判断请求文件是否是目录文件
		{
			ProcessList(info);//执行文件列表响应
		}
		else
		{
			ProcessFile(info);//执行文件下载响应
		}
	}

}
*/
