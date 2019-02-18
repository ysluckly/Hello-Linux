#include "Common.h"
#include "ConcurrentMePool.h"

void TestThreadCache()
{
	//保证每个申请内存线程都有一个Cache？也就是每次申请时就创建并返回一个cache
	//线程如何获取Cache？
	//1，全局静态变量线程共享，将所有Threadcache对象用链表连接起来，然后每个存一个线程id，
	//		也就是开始链表为空，来一个线程，创建一个cache对象链接到链表，并记录tid(每个线程tid可以通过一个接口获取（比如：thread_self()）)
	//并且线程来了先查找，有相同tid使用，没有创建并挂链.....链表还好，线程一般情况下不太多
	//但是此处：每个线程获取cache，需要加锁，因为读不存在，但是同时有的在读数据，有的在写数据
	//方案可以，就是锁消耗太大
	/*
	int _tid;
	ThreadCache* _next;
	//2.多线程的时候，记得tls（thread local storage）：线程本地存储【每个线程独有一个全局变量，在任意函数访问这个变量都是该线程】
	//但这个最坏的地方在于：不兼容，不同平台可能需要多分代码
	//静态与动态区别：静态效率更高，更简洁		
	*/

	//验证每个线程一个cache（创建即获取）
	//参数：接口与接口的参数（线程后面是可变参数）
	/*std::thread t1(ConcurrentAlloc,10);
	std::thread t2(ConcurrentAlloc, 10);
	
	t1.join();
	t2.join();*/
	
	//验证如何从中心cache获取对象,且第一个对象为空创建链表申请内存挂链，第二个对象在此申请时，链表不为空，直接取用
	/*void* p1 = ConcurrentAlloc(10);
	void* p2 = ConcurrentAlloc(10);*/

	//验证内存重复利用，先申请，在释放，在申请，发现空间可以重复使用
	/*std::vector<void*> v;
	for (size_t i = 0; i < 10; ++i)
	{
		v.push_back(ConcurrentAlloc(10));
		cout << v.back() << endl;
	}
	cout << endl << endl;

	for (size_t i = 0; i < 10; ++i)
	{
		ConcurrentFree(v[i],10);
	}
	v.clear();

	for (size_t i = 0; i < 10; ++i)
	{
		v.push_back(ConcurrentAlloc(10));
		cout << v.back() << endl;
	}

	for (size_t i = 0; i < 10; ++i)
	{
		ConcurrentFree(v[i], 10);
	}
	v.clear();*/
}

//测试查看页号
void TestPageCache()
{
	//VirtualAlloc按页对齐可以的，但是malloc不是按页对齐就不可以（可能凑巧可以）
	void* ptr = VirtualAlloc(NULL, (NPAGES - 1) << PAGE_SHIFT, MEM_RESERVE, PAGE_READWRITE);
	cout << ptr << endl;
	if (ptr == nullptr)
	{
		throw std::bad_alloc();
	}

	PageID pageid = (PageID)ptr >> PAGE_SHIFT;
	cout << pageid << endl;

	void* shiftptr = (void*)(pageid << PAGE_SHIFT);
	cout << shiftptr << endl;
}

int main()
{
	//TestThreadCache();
	TestPageCache();

	return 0;
}