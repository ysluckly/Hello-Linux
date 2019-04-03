/*************************************************************************
    > File Name:    friend_Inherit.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Wed 03 Apr 2019 07:40:46 PM CST
 ************************************************************************/
#include <iostream>
using namespace std;
class Person
{
	friend void disp(Person& p,Student& s);
protected:
	string _name;//姓名
};
class Student:public Person
{
protected:
	int _stuNum;//学号
};
void disp(Person& p,Student& s)
{
	cout<<p._name<<endl;
	cout<<s._name<<endl;
	cout<<s._stuNum<<endl;
}
void FunTest()
{
	Person p;
	Student s;
	disp(p,s);
}
int main()
{
	FunTest();
	return 0;
}

