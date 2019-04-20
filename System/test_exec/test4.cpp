/*************************************************************************
    > File Name:    test4.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Sat 20 Apr 2019 11:25:01 PM CST
 ************************************************************************/

#include<iostream>
#include<unistd.h>
using namespace std;
int main(int argc, char* argv[])
{

    cout << "before "<< endl;

    execlp("test1","test1",NULL);
    return 0;
}

