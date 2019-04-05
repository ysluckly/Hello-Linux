/*************************************************************************
    > File Name:    test_cast.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Thu 04 Apr 2019 06:53:29 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
//int main(int argc, char* argv[])
//{
    /*volatile const int a = 2;
    int *p = const_cast<int*>(&a);
    *p = 3;
    cout << a << endl;
    */
    //return 0;
//}
//
class A
{
public :
virtual void f(){}
};
class B : public A
{};
void fun (A* pa)
{
// dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回0
B* pb1 = static_cast<B*>(pa);
B* pb2 = dynamic_cast<B*>(pa);
cout<<"pb1:" <<pb1<< endl;
cout<<"pb2:" <<pb2<< endl;
}
int main ()
{
A a;
B b;
fun(&a);
fun(&b);
return 0;
} 
    
