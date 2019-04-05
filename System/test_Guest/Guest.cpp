/*************************************************************************
    > File Name:    Guest.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Wed 03 Apr 2019 04:01:46 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#include <unistd.h>
#include <math.h>
#include <stdio.h>
int isPrime(int n)
{
	int j = 0;
	if(n <= 1)
		return 0;
	if(n == 2)
		return 1;
	if(!(n%2))
		return 0;
	for(j = 3;j <= sqrt(n);j += 2)//3到根号下n之间判断是否有因子
		if((n%j))
			return 0;
		return 1;
}
int main()
{
	int i = 0;
	int n = 0;
	int count = 0;
	for(i = 4;i <= 2000; i += 2)
	{
		for(n = 2;n < i;n++) //将偶数i分解为两个整数
		{
			if(isPrime(n))	//判断第一个数是否为素数
				if(isPrime(i-n)) //判断另一个数是否为素数
				{
					printf("%d=%d+%d  ",i,n,i-n);//两者均为素数
					break;
				}
		}
	}
	return 0;

}
