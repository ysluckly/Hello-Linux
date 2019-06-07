/*************************************************************************
	> File Name:    MaxGcd.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: 2019年06月05日 星期三 01时34分18秒
 ************************************************************************/

#include<stdio.h>

int main()
{
    int m = 0;
    int n = 0;
    printf("请输入两个整数：");
    scanf("%d%d",&m,&n);

    while(m % n)
    {
        int temp = m % n;
        m = n;
        n = temp;
    }
    printf("最大公约数是：%d\n",n);
    return 0;
}
