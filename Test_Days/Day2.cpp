/*************************************************************************
	> File Name:    Day2.cpp
	> Author:       Hunter
	> Mail:         hunter.520@qq.com
	> Created Time: Wed 22 May 2019 11:44:31 PM PDT
 ************************************************************************/

//58541-进制转换
//https://www.nowcoder.com/practice/ac61207721a34b74b06597fe6eb67c52?tpId=85&&tqId=29862&r

 #include <iostream>
 #include<string>
 #include<algorithm>
 using namespace std;
 int main()
 {
 string s, table="0123456789ABCDEF";
 int m,n;
 cin>>m>>n;
 bool flag = false;

// 如果是负数，则转成正数，并标记一下
 if(m < 0)
 {
 m = 0 - m;
 flag = true;
 }
 // 按进制换算成对应的字符添加到s
 while(m)
 {
 s += table[m%n];
 m /= n;
 }
 if(flag)
 s += '-';
 reverse(s.begin(), s.end());
 cout<<s<<endl;
 return 0;
 }
