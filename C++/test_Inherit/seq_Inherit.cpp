/*************************************************************************
    > File Name:    seq_Inherit.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Wed 03 Apr 2019 07:00:34 PM CST
 **********************************************************************/
#include <iostream>
using namespace std;

class Test1
{
public:
	Test1()//基类构造函数
	{
		cout<<"Constructing base class"<<endl;
	}
	~Test1()//基类析构函数
	{
		cout<<"Destructing base class"<<endl;
	}
};
class Test2:public Test1
{
public:
	Test2()//派生类构造函数
	{
		cout<<"Constructing derived class"<<endl;
	}
	~Test2()//派生类析构函数
	{
		cout<<"Destructing derived class"<<endl;
	}
};
int main()
{
	Test2 A;
	return 0;
}
