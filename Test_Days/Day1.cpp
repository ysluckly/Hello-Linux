/*************************************************************************
	>//File//Name:////////Day1.cpp
	>//Author://////////////Hunter
	>//Mail://////////////////hunter.520@qq.com
	>//Created//Time://Wed//22//May//2019//11:19:44//PM//PDT
************************************************************************/

//题目ID：46579 --计算糖果
//链接：https://www.nowcoder.com/practice/02d8d42b197646a5bbd0a98785bb3a34?tpId=85&&tqId=2
#include<iostream>
using namespace std;
//  A - B = a
// // B - C = b
// // A + B = c
// // B + C = d
// // 这道题目的实质是：判断三元一次方程组是否有解及求解。
// // 这里是小学生都会的问题了^^
int main(){
 int a,b,c,d;
 cin>>a>>b>>c>>d;
 int A=(a+c)/2;
 int C=(d-b)/2;
 int B1=(c-a)/2;
 int B2=(b+d)/2;
 if(B1!=B2){
 cout<<"No";
 }
else{
 cout<<A<<" "<<B1<<" "<<C;
 }
 return 0;
}
