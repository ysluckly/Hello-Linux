#pragma once

#include "Common.h"

// 1.central cache本质是由一个哈希映射的span对象自由链表构成
// 2.每个映射大小的empty span挂在一个链表中，nonempty span挂在一个链表中
// 3.为了保证全局只有唯一的central cache，这个类被设计成了单例模式
class CentralCache
{
public:
	static CentralCache* GetInstance(){
		return &_inst;
	}
	
	// 从中心缓存获取一定数量的对象给thread cache
	size_t FetchRangeObj(void*& start, void*& end, size_t n, size_t byte);

	// 将一定数量的对象释放到span跨度
	void ReleaseListToSpans(void* start, size_t byte_size);

	// 从page cache获取一个span
	Span* GetOneSpan(SpanList* spanlist, size_t bytes);
private:
	// 中心缓存自由链表
	SpanList _spanlist[NLISTS];
private:
	//防止别人创建，构造私有
	CentralCache() = default;//生成默认构造，编译生成对象调用默认
	CentralCache(const CentralCache&) = delete;
	CentralCache& operator=(const CentralCache&) = delete;

	static CentralCache _inst; //.h文件会本别的文件引用，所以在.cpp初始化，否则容易现问题。
};