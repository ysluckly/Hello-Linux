/*************************************************************************
    > File Name:    main.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Wed 03 Apr 2019 05:31:17 PM CST
 ************************************************************************/

#include "String.h"
void FunTest()
{
	String s1("Hello world");
	String s2(s1);
	String s3 = s1 + s2;
	cout<<"s1 = "<<s1<<endl;
	cout<<"s2 = "<<s2<<endl;
	cout<<"s3 = "<<s3<<endl;
}
int main()
{
	FunTest();
	return 0;
}
