/*************************************************************************
    > File Name:    Triangle0.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Tue 02 Apr 2019 11:26:45 PM PDT
 ************************************************************************/
#include <stdio.h>
#include<iostream>
using namespace std;
int main(int argc, char* argv[])
{
   int i,j,n=0,a[17][17]={0,1};
   while(n<1 || n>16)
   { printf("请输入杨辉三角形的行数:");
     scanf("%d",&n);
   }
   for(i=1;i<=n;i++)
   { for(j=1;j<=i;j++)
     { a[i][j]=a[i-1][j-1]+a[i-1][j];   /*每个数是上面两数之和*/
       printf("%5d",a[i][j]);    /*输出杨辉三角*/
     }
     printf("\n");
   } 
    return 0;
}

