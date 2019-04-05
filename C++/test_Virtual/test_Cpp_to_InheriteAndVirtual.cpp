/*************************************************************************
    > File Name:    test_C_to_InheriteAndVirtual.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Fri 05 Apr 2019 01:09:01 AM CST
 ************************************************************************/

#include <iostream>
#include <stdio.h>
using namespace std;

class A
{
public:
    virtual void fun()
    {
        printf("A::fun()\n");
    }
    int _a;
};

class B:public A
{
public:
    virtual void fun()
    {
        printf("B::fun()\n");
    }
    int _b;
};

int main()
{
    A a;
    B b;
    A* p = &a;
    p->fun();
    p = &b;
    p->fun();

    return 0;
}
