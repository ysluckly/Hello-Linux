题目：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
链接：https://www.nowcoder.com/practice/e8a1b01a2df14cb2b228b30ee6a92163?tpId=13&tqId=11181&tPage=2&rp=2&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking

#include<iostream>
using namespace std;
int main(){
    int a[1000]={0};//数组置0，然后输入n，则对应位置加1，最后遍历数组
    int n,num=0;  //找到大于等于一半次数的那个
    while(cin>>n){
        a[n]++;
        num++;
    }
    for(int i=0;i<num;i++){
        if(a[i]>=num/2)
            cout<<i<<endl;
    }
    return 0;
}
