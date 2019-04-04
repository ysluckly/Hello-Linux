/*************************************************************************
    > File Name:    test1.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Fri 05 Apr 2019 12:55:33 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;
template<class T>
class MakeSealed
{
	friend class SealedClass;
private:
	MakeSealed()
	{}
	~MakeSealed()
	{}
};
class SealedClass :virtual public MakeSealed<SealedClass>
{
public:
	SealedClass()
	{}
	~SealedClass()
	{}
};


class Code :public SealedClass
{
public:
	Code()
	{}
	~Code()
	{}
};
int main()
{
	return 0;
}
