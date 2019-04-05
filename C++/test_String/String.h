/*************************************************************************
    > File Name:    String.h
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Wed 03 Apr 2019 05:25:12 PM CST
 ************************************************************************/

#pragma once 
#include <iostream>
#include <string.h>
using namespace std;

class String
{
public:
	String(const char *pStr = "")
	{
		if(pStr == NULL)
		{
			_pStr = new char[1];
			*_pStr = '\0';
		}
		else
		{
			_pStr = new char[strlen(pStr) + 1];
			strcpy(_pStr,pStr);
		}
	}
	String(const String& s)
	{
		_pStr = new char[strlen(s._pStr) + 1];
		strcpy(_pStr,s._pStr);
	}
	~String()
	{
		if(_pStr)
		{
			delete[] _pStr;
			_pStr = NULL;
		}
	}
	size_t Size()const;//字符串的大小
	size_t Lengh()const;//字符串的长度
	char& operator[](const size_t index);//下标界定符
	const char& operator[](size_t index)const;
	bool operator>(const String& s);
	bool operator<(const String& s);
	bool operator==(const String& s);
	bool operator!=(const String& s);
	void Copy(const String& s);
	String operator+(const String& s);
	bool strstr(const String& s);
	String& operator=(const String& s);
	String& operator+=(const String& s);
	friend ostream& operator<<(ostream& _cout,const String& s);
private:
	char *_pStr;
};
