/*************************************************************************
    > File Name:    test5.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Sat 20 Apr 2019 11:31:46 PM CST
 ************************************************************************/

#include<iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char* argv[])
{
    char* buf[] = {"test1",NULL};
    execvp("test1",buf);
    return 0;
}

