#include "ThreadCache.h"
#include "CentralCache.h"

//第一种方法：每次都是从CentralCache获取固定数量的对象：10
void* ThreadCache::FetchFromCentralCache(size_t index, size_t byte)
{
	FreeList* freelist = &_freelist[index];
	size_t num = 10;

	void* start, *end;
	//申请num，中心不一定有，需要获取实际申请的个数，但是至少保证有一个
	size_t fetchnum = CentralCache::GetInstance()->FetchRangeObj(start, end, num, byte);
	if (fetchnum == 1)
		return start;
	//多个的话，将第一个返回，其余的挂在自由链表上
	freelist->PushRange(NEXT_OBJ(start), end, fetchnum - 1);
	return start;
}
//方法二：每次获取时，获取数量呈现线性增长的过程
//void* ThreadCache::FetchFromCentralCache(size_t index, size_t byte)
//{
//	FreeList* freelist = &_freelist[index];
//	size_t num = 10;
//	void* start, *end;
//	size_t fetchnum = CentralCache::GetInstance()->FetchRangeObj(start, end, num, byte);
//	if (fetchnum == 1)
//		return start;
//
//	freelist->PushRange(NEXT_OBJ(start), end, fetchnum - 1);
//	return start;
//}

void* ThreadCache::Allocate(size_t size)
{
	assert(size <= MAXBYTES);

	//建立自定义的对齐规则
	// 根据对齐规则：size向上取整
	size = ClassSize::Roundup(size);
	//获取对齐数对应的下标
	size_t index = ClassSize::Index(size);
	FreeList* freelist = &_freelist[index];
	if (!freelist->Empty())
	{
		//链表头删一个节点并返回
		return freelist->Pop();
	}
	else
	{
		//链表为空，从Centralache中获取对象，
		//取一个不合理，每次都加锁增加消耗，可以多取一点，多的挂在链表上，以备下次使用
		return FetchFromCentralCache(index, size);
	}
}

void ThreadCache::Deallocate(void* ptr, size_t size)
{
	assert(size <= MAXBYTES);
	size_t index = ClassSize::Index(size);
	FreeList* freelist = &_freelist[index];
	freelist->Push(ptr);

	//当自由链表对象数量超过最大结点数量时开始进行回收
	if (freelist->Size() >= freelist->MaxSize())
	{
		//粗暴，将该链表全部回收
		//ListTooLong(freelist, freelist->Size());
	}
}
//void ThreadCache::ListTooLong(FreeList* list, size_t size)
//{
//
//
//}