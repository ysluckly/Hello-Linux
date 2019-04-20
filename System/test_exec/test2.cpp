/*************************************************************************
    > File Name:    test2.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Sat 20 Apr 2019 11:14:57 PM CST
 ************************************************************************/

#include<iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char* argv[])
{
    cout << "exec before "<< endl;

    execl("./test1","./test1",NULL);

    cout << "EXEC AFTER"<< endl;


    return 0;
}

