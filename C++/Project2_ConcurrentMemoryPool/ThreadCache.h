#pragma once

#include "Common.h"
//thread cache本质是由一个哈希映射的对象自由链表构成
class ThreadCache
{
public:
	// 申请和释放内存对象
	/*
	当内存申请size<=64k时在thread cache中申请内存，计算size在自由链表中的位置，如果自由链表中
	有内存对象时，直接从FistList[i]中Pop一下对象，时间复杂度是O(1)，且没有锁竞争。
	当FreeList[i]中没有对象时，则批量从central cache中获取一定数量的对象，插入到自由链表并返回一
	个对象。
	*/
	void* Allocate(size_t size);

	// 从中心缓存获取对象
	void* FetchFromCentralCache(size_t index, size_t size);

	/*
	当释放内存小于64k时将内存释放回thread cache，计算size在自由链表中的位置，将对象Push到
	FreeList[i].
	当链表的长度过长，则回收一部分内存对象到central cache
	*/
	void Deallocate(void* ptr, size_t size);

	// 释放对象时，链表过长时，回收内存回到中心缓存
	void ListTooLong(FreeList* list, size_t size);
private:
	FreeList _freelist[NLISTS];	//NLISTS由怎么对齐（对齐规则）决定的
	//线程如何获取Cache？
	//1，全局静态变量线程共享，将所有Threadcache对象用链表连接起来，然后每个存一个线程id，
	//		也就是开始链表为空，来一个线程，创建一个cache对象链接到链表，并记录tid(每个线程tid可以通过一个接口获取（比如：thread_self()）)
	//并且线程来了先查找，有相同tid使用，没有创建并挂链.....链表还好，线程一般情况下不太多
	//但是此处：每个线程获取cache，需要加锁，因为读不存在，但是同时有的在读数据，有的在写数据
	//方案可以，就是锁消耗太大
	/*
	int _tid;
	ThreadCache* _next;
	*/
	//2.多线程的时候，记得tls（thread local storage）：线程本地存储【每个线程独有一个全局变量，在任意函数访问这个变量都是该线程】
	//但这个最坏的地方在于：不兼容，不同平台可能需要多分代码
	//静态与动态区别：静态效率更高，更简洁
	
};
static _declspec(thread) ThreadCache* tls_threadcache = nullptr;//_declspec(thread) 静态tls全局变量，每个线程都能看到，看到的不是同一个