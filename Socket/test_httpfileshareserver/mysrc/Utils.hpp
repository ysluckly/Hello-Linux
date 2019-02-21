#ifndef __UTILES_H__
#define __UTILES_H__ 

#include <iostream>
#include <unistd.h>
#include <queue>
#include <time.h>
#include <mutex>
#include <pthread.h> 
#include <stdio.h>
#include <unordered_map>
#include <string>
#include <string.h>
#include <vector>
#include <errno.h>
#include <stdlib.h>
#include <sstream>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/stat.h>
#define LOG(...) do{fprintf(stdout,__VA_ARGS__);fflush(stdout);}while(0) //指定写到某目录 

#define MAX_HEADER  4096
#define MAX_PATH 256
#define WWWROOT "www"

std::unordered_map<std::string,std::string> g_err_desc = {
  {"200", "OK"},
  {"400", "Bad Request"},
  {"403", "Forbidden"},
  {"404", "Not Find"},
  {"405", "Method Not Allowed"},
  {"413", "Requst Entity Too Large"},
  {"500", "Internal Server Error"}
};

//公用接口工具
class Utils
{
//提供一些公用的功能接口：字符串格式
public:
	static int Split(std::string &src,const std::string &seg,std::vector<std::string> &vec)
	{
		int num = 0; //分隔数量
    size_t idx = 0;//遍历计数
		size_t pos; //目标位置
		
		while(idx < src.size())
		{
			pos = src.find(seg,idx);
			if(pos == std::string::npos)
			{
				break;
			}
			
			vec.push_back(src.substr(idx,pos-idx));
			num++;
			idx = pos +seg.size();
    }
    
    //最后一个字段后面没有\r\n
		if(idx<src.size())
		{
			vec.push_back(src.substr(idx));
			num++;
		}
	
		return num;
	}

  //通过错误码获取错误信息
	static const std::string GetErrDesc(const std::string& code)
	{
		auto it = g_err_desc.find(code);
		if(it == g_err_desc.end())
		{
			return "Unknow Error Code";
		}

		return it->second;
	}
	
	static void TimeToGMT(time_t t,std::string &gmt)
	{

		struct tm *gm = gmtime(&t);//gmtime直接将当前时间转换为格林威治时间，并且转换出来的是一个结构体，有年月日，时分秒， 一周的第一天，一年的第几天等，
		char tmp[128] = {0};
		int len = strftime(tmp , 127,"%a %d %b %Y %H:%M:%S GMT",gm);//将结构体的时间按照一定格式，转换为特定时间,返回字符串实际长度
		gmt.assign(tmp,len);
	
	}	
	
	static void DigitToStr(int64_t num, std::string &str)
	{
    //stringstream 将放进的数字转换为C格式字符串
		std::stringstream ss;
		ss << num; 
		str = ss.str();
	}
	
  static int64_t StrToDigit(std::string &str)
  {
    int64_t num ;
    std::stringstream ss;
    ss << str;
    ss >> num; //内部模板实现的
    return num;
  }

  static void MakeETag(int64_t size,int64_t ino,int64_t mtime ,std::string &etag)
	{
		std::stringstream ss;

    //"ino-size-mtime"
		ss<<"\"";
		ss<<std::hex<<ino;
		ss<<"-";
		ss<<std::hex<<size;
		ss<<"-";
		ss<<std::hex<<mtime;
	
    ss<<"\"";
		etag = ss.str();
	
	}
};

//请求解析结果
class RequestInfo
{
//包含request解析出的的请求信息
public:
	std::string _method;//请求方法
	std::string _version;//协议版本
	std::string _path_info;//资源路径
	std::string _path_phys;//资源实际具体路径
	std::string _query_string;//客户端提供的查询字符串
	std::unordered_map<std::string,std::string> _hdr_pair; //解析出头部的键值对
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
		if((_method == "POST") || ((_method == "GET" ) && (_query_string.empty())))
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

	bool PathIsLegal(RequestInfo &info)
	{
    //?
		std::string file = WWWROOT + info._path_info;
		if(stat(file.c_str(),&info._st)<0)
		{
			info._err_code = "404";
			return false;
		}
		
    char tmp[MAX_PATH] = {0};
		//realpath:将一个路径转换()为绝对路径，若地址不存在，就会造成段错误，
    //char *realpath(const char *path, char *resolved_path)
		//成功则返回指向resolved_path的指针，失败返回NULL，错误代码存于errno
    realpath(info._path_info.c_str(),tmp);
		info._path_phys = tmp;
		
    //?
		if(info._path_phys.find(WWWROOT) == std::string::npos)
		{
			info._err_code = "403"; //服务器理解请求客户端的请求，但是拒绝执行此请求
			return false;
		}
		return true;
	}

	bool ParseFirstLine(std::string &first_line, RequestInfo &info)
	{
		std::vector<std::string> line_list;
		if(Utils::Split(first_line, " ", line_list) != 3)
		{
			info._err_code = "400"; //客户端请求错误，服务器无法理解
			return false;
		}
		
		std::string url;
		info._method = line_list[0];
		url = line_list[1];
		info._version = line_list[2];
		
		if(info._method !="GET" && info._method != "POST" && info._method != "HEAD")
		{
			
			info._err_code = "405"; //客户端请求中的方法被禁止
			return false;
		}
		
		if(info._version !="HTTP/0.9" && info._version != "HTTP/1.0" && info._version != "HTTP/1.1")
		{
			
			info._err_code = "400"; //客户端请求错误，服务端无法理解
			return false;
		}
		
		//url  www/load/../..?key=val&key=val
		//realpath:将一个路径转换为绝对路径，若地址不存在，就会造成段错误，
		size_t pos;
		pos = url.find("?");
		if(pos == std::string::npos)
		{
			info._path_info = url;
		}
		else{
			info._path_info = url.substr(0,pos);
			info._query_string = url.substr(pos+1);
		}
		
		return PathIsLegal(info);
	}

  //解析请求头部
	bool ParseHttpHeader(RequestInfo& info)
	{
		
		//请求方法 url 版本\r\n
		//键值对key: val\r\nkey: val
		
		//以\r\n进行分隔，取出字符串
		std::vector<std::string> hdr_vector;
		Utils::Split(_http_header,"\r\n",hdr_vector);
		
		//解析首行
		if(ParseFirstLine(hdr_vector[0],info) == false)
    {
			return false;
		}

		for(size_t i = 1; i<hdr_vector.size() ; ++i)
		{
			size_t pos = hdr_vector[i].find(": ");
			info._hdr_pair[hdr_vector[i].substr(0,pos)] = hdr_vector[i].substr(pos+2);
		}
	
		return true;
	}
	
};

//请求响应
class HttpResponse
{
//文件请求（完成文件下载，列表功能）接口
//CGI请求接口，调用外部程序上传功能
private: //信息表示文件唯一
	int _cli_sock;
	
	//ETag: "inode-fsize-mtime"\r\n
	std::string _etag;//表明文件是否是源文件，是否修改过，没修改过，再次下载就不会返回文件了，下载没意义，提高http效率
	std::string _mtime;//文件最后一次修改时间
	std::string _date; //系统响应时间

public:

	HttpResponse(int sock):_cli_sock(sock){}

  /*
  bool InitResponse(RequestInfo &req_info)//初始化一些响应信息
	{
		req_info._st.st_size;
		req_info._st.st_ino;  //节点号
		req_info._st.st_mtime;
    
    //Last-Modify:
		Utils::DigitToStr(req_info._st.st_mtime,_mtime);
    
		//Etag:数字转换字符串太长不美观，转换16进再转字符串
		Utils::MakeETag(req_info._st.st_size,req_info._st.st_ino,req_info._st.st_mtime,_etag);
		
    //Data:
		time_t t = time(NULL);
		Utils::TimeToGMT(t,_date);
		return ture;
		
	}

  //普通传输文件
  bool SendData(std::string &buf)
  {
    if(send(_cli_sock,buf.c_str(),buf.length(),0)<0)
    {
      return false;
    }
    return true;
  }

  //分块传输
  bool SendChunkDate(std::string &buf)
  {
  
  //  05\r\n
  //  hello
  //  \r\n
    
  //  最后一个分块特殊
  //  0\r\n\r\n
    
      if(buf.empty())
      {
        return SendDate("0\r\n\r\n");
      }

      std::stringstream ss;
      ss << std::hex << buf.length();
      ss << "\r\n";

      SendDate(ss.str()); //长度
      SendDate(buf);   //数据
      SendDate("\r\n");

      return true;
  }

	//文件下载(文件名称)
	bool ProcessFile(RequestInfo& info)
	{
		return ture;
	}

	//文件列表（文件目录即路径）
	bool ProcessList(RequestInfo& info)
	{
    //组织头部信息
    //首行 
    //Content-Type: text/html\r\n
    //Etag: \r\n
    //Data: \r\n
    //Connection: close\r\n\r\n   //就是接受完请求就关闭链接，因为是短链接
    //数据可能很大，不可能一次性传输，需要分块处理，Http 1.1版本中才有这个：
    //Transfer-Encoding: chunked\r\n  就是说只告诉这一块数据大小，不会知道响应总大小
    //不分块也可以，将正文全部发送，大不了失败，关闭链接就好 ，因为http是软连接，一旦对方接受到0，就认为接收完毕
    //正文：每一个目录下的文件都要组织一个html信息
   
    //头部
    std::string rsp_header;
    rsp_header = info._version + " 200 OK\r\n";

    rsp_header += "Content-Type: text/html\r\n"
    rsp_header += "Connection: close\r\n";
    if(info._version == "HTTP/1.1")
    {
      rsp_header += "Transfer-Encoding: chunked\r\n";
    }
    rsp_header += "ETag: "+ _etag + "\r\n";
    rsp_header += "Last-Modifyed: " + _mtime + "\r\n";
    rsp_header += "Data: "+ _date + "\r\n\r\n";
    
    //正常传输
    SendData(rsp_header);

    //正文数据可能比较大，所以采取分块传输
    std::string rsp_body;
    rsp_body = "<html><head>";
    rsp_body += "<title>" + info._path_info + "</title>";
    rsp_body += "<meta charset='UTF-8'>";
  
    rsp_body += </head><body>";
    rsp_body += "<h1>" + info._path_info + "</h1>";
    //横线
    rsp_body += "<hr />";

    _
    while(1)
    {
      //获取目录下的每一个文件，组织html信息，chunked传输 
      //应该先判断，但是一般都是1.1版本，所以此处不用
      std::string file_html;
      SendChunkDate(file_html);

    }

    rsp_body = "</body></html>";
    
    SendChunkData(rsp_body);
    SendDat("");
    
    return ture;
	}

	//CGI请求处理（文件名称）
	bool ProcessCGI(RequestInfo& info)
	{
		return ture;
	}

	bool CGIHandler(RequestInfo& info)
	{
		InitResponse(info);//初始化cgi响应信息
		ProcessCGI(info);//指向cgi响应
	}

  //st结构体中的mode，有比较多的的选项，有表示是否是常规文件以及目录等
  bool FileIsDir(RequestInfo &info)
  {
    if(info._st.st_mode & S_IFDIR)
    {
      return true;
    }
    
    return false; 

  }

	bool FileHandler(RequestInfo& info)
	{
		InitResponse(info);//初始化file响应信息
		if(FileIsDir(info))//判断请求文件是否是目录文件
		{
			ProcessList(info);//执行文件列表响应
		}
		else
		{
			ProcessFile(info);//执行文件下载响应
		}
	}*/

	bool ErrHandler(RequestInfo& info)//错误响应
	{
    //响应头信息
		std::string rsp_header;
	
    //首行 版本  状态码 状态描述\r\n
		//头部 长度： Content-Length    当前系统时间:Date
		//空行             
		//正文 rsp_body = "<html><body><h1> 404; <h1></body></html>"  //一般错误没有正文 有的话：html标签  正文标签 标题
		
    //响应正文 <html><body><h1> 404;<h1></body></html>
		std::string rsp_body;
		rsp_body = "<html><body><h1>"+info._err_code;
		rsp_body += "<h1></body></html>";
    
    //首行：版本 状态码 描述信息（code对应的描述信息）
		rsp_header = info._version + " " + info._err_code + " ";
		rsp_header += Utils::GetErrDesc(info._err_code)+"\r\n";
		
    //日期:Date:
		time_t t = time(NULL);//系统当前时间戳
		std::string gmt;
		Utils::TimeToGMT(t,gmt); //响应的都是格林威治时间,需要进行转换 （周，日 月 年 时：分：秒 GMT）
		rsp_header += "Date: "+gmt + "\r\n";
		
	
    //正文长度 :Content-Length
    std::string content_length;
    Utils::DigitToStr(rsp_body.size(),content_length);
    rsp_header += "Content-Length: " + content_length + "\r\n\r\n";
		
    //发送头部
    send(_cli_sock,rsp_header.c_str(),rsp_header.size(),0);
    //发送正文
    send(_cli_sock,rsp_body.c_str(),rsp_body.size(),0);
	  
    
    return true;
	}
/*

};

#endif
