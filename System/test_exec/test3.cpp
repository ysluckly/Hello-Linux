/*************************************************************************
    > File Name:    test3.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Sat 20 Apr 2019 11:20:37 PM CST
 ************************************************************************/

#include<iostream>
#include<unistd.h>
using namespace std;
int main(int argc, char* argv[])
{
    char* buf[]={"./test1",NULL};
    cout << "before " << endl;
    execv("./test1",buf);
    cout << "end" << endl;
    return 0;
}

