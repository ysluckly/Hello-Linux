/*************************************************************************
    > File Name:    seq_Inherit2.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Wed 03 Apr 2019 07:07:34 PM CST
 ************************************************************************/
#include <iostream>
using namespace std;
class Test1
{
public:
	Test1(int a = 1)
    {
        cout << a<< endl;
    }
    ~Test1()//基类析构函数
	{
		cout<<"1:Destructing base class"<<endl;
	}
};
class Test2:public Test1
{
public:
	~Test2()//派生类析构函数
	{
		cout<<"2:Destructing derived class"<<endl;
	}
};
class Test3:public Test2
{
public:
	Test3()
	{
		cout<<"3:Constructing derived class"<<endl;
	}
	~Test3()
	{
		cout<<"3:Destructing derived class"<<endl;
	}
};
int main()
{
	Test3 A;
	return 0;
}
