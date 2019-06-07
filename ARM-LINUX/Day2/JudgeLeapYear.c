/*************************************************************************
	> File Name:    JudgeLeapYear.c
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: 2019年06月05日 星期三 01时42分52秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int year = 0;
    printf("请输入年份:");
    scanf("%d",&year);

    if(((year%4==0) && (year%100 != 0)) || year % 400 == 0)
    {
        printf("该年份是闰年\n");
    }
    else
    {
        printf("该年份不是闰年\n");
    }
    
    return 0;
}
