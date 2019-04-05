/*************************************************************************
    > File Name:    String.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Wed 03 Apr 2019 05:33:24 PM CST
 ************************************************************************/

#include "String.h"
size_t String::Size()const
{
	size_t count = 0;
	char *p = _pStr;

	while(*p != '\0')
	{
		++count;
		p++;
	}
	return count;
}
size_t String::Lengh()const
{
	size_t count;
	char *p = _pStr;
	while(*p != '\0')
	{
		++count;
		p++;
	}
	return count;
}
char& String::operator[](size_t t)
{
	if(t >= 0 && t <= strlen(_pStr))
		return _pStr[t];
}
const char& String::operator[](size_t t)const
{
	return _pStr[t];
}
bool String::operator>(const String& s)
{
	char *pTemp1 = _pStr;
	char *pTemp2 = s._pStr;
	while(*pTemp1 == *pTemp2)
	{
		pTemp1++;
		pTemp2++;
	}
	if(*pTemp1 > *pTemp2)
		return true;
	else
		return false;
}
bool String::operator<(const String& s)
{
	char *pTemp1 = _pStr;
	char *pTemp2 = s._pStr;
	while (*pTemp1 == *pTemp2)
	{
		pTemp1++;
		pTemp2++;
		if(*pTemp1 < *pTemp2)
			return true;
		else
			return false;
	}
	return false;
}
bool String::operator==(const String& s)
{
	int ret = strcmp(_pStr,s._pStr);
	if(0 == ret)
		return true;
	return false;
}
bool String::operator!=(const String& s)
{
	return !(*this == s);
}
bool String::strstr(const String& s)
{
	char* pTemp1 = _pStr;
	char* pTemp2 = s._pStr;
	char pTemp = NULL;
	while(*pTemp1 != '\0' && *pTemp2 != '\0')
	{
		while(*pTemp1 == *pTemp2)
		{
			pTemp1++;
			pTemp2++;
		}
		pTemp1++;
	}
	if(*pTemp2 == '\0')
		return true;
	else
		return false;
}
String& String::operator=(const String& s)
{
	if(this != &s)
	{
		delete[] _pStr;
		_pStr = new char[strlen(s._pStr) + 1];
		strcpy(_pStr,s._pStr);
	}
	return *this;
}
ostream& operator<<(ostream& _cout,const String& s)
{
	_cout<<s._pStr;
	return _cout;
}
String String::operator+(const String& s) 
{  
	String s1;  
    if (!s._pStr)  
        s1 = *this;  
    else if (!_pStr)  
        s1 = s;  
    else {  
		s1._pStr = new char[strlen(_pStr) + strlen(s._pStr) + 1];  
		strcpy(s1._pStr, _pStr);  
        strcat(s1._pStr, s._pStr);  
    }  
    return s1;
}
 String& String::operator+=(const String& s)  
 {  
        char *Temp1 = (*this)._pStr;  
        char *Temp2 = s._pStr;  
        int len1 = strlen(Temp1);  
        int len2 = strlen(Temp2);  
        char *Buff = NULL;  
        char *end = NULL;  
        Buff = new char[len1 + len2 + 1];  
        strcpy(Buff, Temp1);  
        end = Buff + len1;  
        strcpy(end, Temp2);  
        delete[]_pStr;  
        _pStr = Buff;  
        return (*this);  
 }
 void String::Copy(const String& s)  
 {  
	 int idx = 0;  
	 char *pTemp1 = new char[strlen(s._pStr) + 1];  
	 char *pTemp2 = s._pStr;  
	 for (idx = 0; pTemp2[idx] != '\0'; idx++)  
	 {  
		 pTemp1[idx] = pTemp2[idx];  
	 }  
	 pTemp1[idx] = '\0';  
	 delete[]_pStr;  
	 _pStr = pTemp1;  
 }
