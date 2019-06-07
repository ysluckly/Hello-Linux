/*************************************************************************
	> File Name:    GetDate.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: 2019年06月05日 星期三 01时48分06秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    printf("通过shell命令获取的时间为：\n");
    system("date");
    return 0;
}
