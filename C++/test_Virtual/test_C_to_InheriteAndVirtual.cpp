/*************************************************************************
    > File Name:    test_C_to_InheriteAndVirtual.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Fri 05 Apr 2019 01:09:01 AM CST
 ************************************************************************/
#include <stdio.h>

typedef void(*FUN) ();//定义函数指针

struct A
{
    FUN _f;//C语言的结构体不支持成员函数，只能用函数指针来实现“含有成员函数”
    int _a;
};

struct B
{
    struct A a;//C语言不支持继承，只能用嵌套结构体实现“B继承A”
    int _b;
};

void funA()
{
    printf("A::fun\n");
}
void funB()
{
    printf("B::fun\n");
}

int main()
{
    struct A a;
    struct B b;
    a._f = funA;
    b.a._f = funB;
    struct A* p = &a;
    p->_f();
    p = (struct A*)&b;
    p->_f();

    return 0;
}
