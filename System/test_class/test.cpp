/*************************************************************************
	> File Name:    test.cpp
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: Sat 20 Oct 2018 04:51:05 AM PDT
 ************************************************************************/

///////////////////////////C++类默认六种函数
#include<iostream>
using namespace std;

class Date
{
public:
    //对于默认构造时，自定义类型会进程初始化，而基本类型不会做任何处理，即为随机值

    //构造函数，1.无参构造(长采用缺省参数构造)
    Date(int year = 1997,int month = 11,int day = 4)
    {
        _year = year;
        _month = month;
        _day = day;
    }
    //构造函数，2.带参构造
    Date(int year,int month,int day)
    {
        _year = year;
        _month = month;
        _day = day;
    }
    //拷贝构造函数:用一个已经存在的类类型对象创建一个对象，并对其进行初始化
    //Date d3(d1);Date d3 = d1;
    Date(const Date& d)
    {
        _year = d.year;
        _month = d.month;
        _day = d.day;

    }
    //赋值操作符重载:连续赋值一定需要返回值
    Date& operator=(const Date& d)
    {
        //防止自己给自己赋值
        if(this!=&d)
        {
            _year = d.year;
            _month=d.month;
            _day = d.day;
        }
        return *this;
    }

    //取地址操作符重载
    Date* operator&()
    {
        return this;
    }
    //const修饰的操作符重载
    const Date* operator&()const
    {
        return this;
    }
    //析构函数,在main栈销毁前，即return语句执行时，调用析构，实际就是做对象删除前的资源清理与收尾工作
    ～Date()
    {}
private:
    int _year;
    int _month;
    int _day;

}

int main()
{
    Date d1(1997,11,4);
    Date d2(192,3,23);

    return 0;
}
