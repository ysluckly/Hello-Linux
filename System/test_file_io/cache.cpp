/*************************************************************************
    > File Name:    cache.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Sun 14 Apr 2019 10:27:27 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#define MAX 93

int main()
{
    char buf[] = "hello linux";
    int i = 0;
    while(i<MAX)
    {
        printf("%s",buf);
        ++i;
    }

    while(1);
    return 0;
}
