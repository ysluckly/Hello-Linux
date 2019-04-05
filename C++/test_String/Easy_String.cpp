/*************************************************************************
    > File Name:    String.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Wed 03 Apr 2019 04:58:06 PM CST
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include <string.h>
using namespace std;

class String
{
public:
	//构造函数
	String(const char* pStr = "")
		:_pStr(new char[strlen(pStr) + 1])
	{
		if(*_pStr == nullptr)
			*_pStr = '\0';
		else
			strcpy(_pStr,pStr);
	}
	//拷贝构造函数
	String(String& s)
		:_pStr(NULL)//初始化_pStr
		//防止交换后pTemp指向随机空间
	{
		String pTemp(s._pStr);//给出临时空间，交换后s不为NULL
		std::swap(_pStr,pTemp._pStr);
	}
	//析构函数
	~String()
	{
		if(NULL == _pStr)
		{
			return;
		}
		delete[] _pStr;
		_pStr = NULL;
	}
	// 赋值运算符=号的重载
	String& operator=(const String& s)
	{
		if(_pStr != s._pStr)
		{
			String pTemp(s._pStr);//给出临时空间，交换后s不为NULL
			std::swap(_pStr,pTemp._pStr);
		}
		return *this;
	}
private:
	char *_pStr;
};
void FunTest()
{
	String s1("Hello world");
	String s2(s1);
	String s3 = s2;
}
int main()
{
	
	FunTest();
	return 0;
}
