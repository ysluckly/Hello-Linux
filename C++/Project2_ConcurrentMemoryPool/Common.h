#pragma once

#include <iostream>
#include <assert.h>
#include <thread>
#include <vector>
#include <mutex>

using std::cout;
using std::endl;

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

const size_t NLISTS = 184;  //管理对象自由链表的长度，由对齐规则决定，即array决定
const size_t MAXBYTES = 64 * 1024;	 //自定义规定小于64k，在threadcache申请，即threadcache最大64k；
const size_t PAGE_SHIFT = 12;		//移位数
const size_t NPAGES = 129;		//pagecache链表最大长度

typedef size_t PageID;
//页为单位，划分多个对象
struct Span
{
	PageID _pageid;			// 页号
	size_t _npage;		// 页的数量

	Span*  _next;
	Span*  _prev;

	void*  _objlist = nullptr;	// 对象自由链表
	size_t _objsize = 0;		// 对象大小
	size_t _usecount = 0;		// 使用计数
};

class SpanList
{
public:
	SpanList()
	{
		_head = new Span;	
		_head->_next = _head;
		_head->_prev = _head;
	}
	
	Span* begin()
	{
		return _head->_next;
	}

	Span* end()
	{
		return _head;
	}

	bool Empty()
	{
		return _head->_next == _head;
	}

	void Insert(Span* cur, Span* newspan)
	{
		assert(cur);
		Span* prev = cur->_prev;
		// prev newspan cur

		prev->_next = newspan;
		newspan->_prev = prev;
		newspan->_next = cur;
		cur->_prev = newspan;
	}

	void Erase(Span* cur)
	{
		assert(cur != nullptr && cur != _head);
		Span* prev = cur->_prev;
		Span* next = cur->_next;

		prev->_next = next;
		next->_prev = prev;
	}

	void PushFront(Span* span)
	{
		Insert(begin(), span);
	}

	Span* PopFront()
	{
		Span* span = begin();
		Erase(span);
		return span;
	}
private:
	Span* _head = nullptr;
};

//当前对象的下一个对象地址
static inline void*& NEXT_OBJ(void* obj)
{
	return *((void**)obj);
}

 //自由链表
class FreeList
{
public:
	bool Empty()
	{
		return _list == nullptr;
	}

	//头删
	void* Pop()
	{
		void* obj = _list;
		_list = NEXT_OBJ(obj);
		--_size;

		return obj;
	}

	//头插
	void Push(void* obj)
	{
		NEXT_OBJ(obj) = _list;
		_list = obj;
		++_size;
	}
	//将多个结点一次性插入
	void PushRange(void* start, void* end, size_t num)
	{
		NEXT_OBJ(end) = _list;
		_list = start;
		_size += num;
	}

	//获取结点个数
	size_t Size()
	{
		return _size;
	}

	//获取结点个数最大值
	size_t MaxSize()
	{
		return _maxsize;
	}	
	
private:
	void* _list = nullptr;
	size_t _size = 0;	  //链表结点个数
	size_t _maxsize = 0;  //链表结点个数最大值
};
//
// 管理对齐映射的规则
class ClassSize
{
	// 控制在12%左右的内碎片浪费
	// [1,128]				8byte对齐 freelist[0,16)
	// [129,1024]			16byte对齐 freelist[16,72)
	// [1025,8*1024]		128byte对齐 freelist[72,128)
	// [8*1024+1,64*1024]	512byte对齐 freelist[128,240)
public:
	//字节对齐到某对齐数 eg：对齐到8    （size+7）& ~（7）：size+对齐数-1，就是跃迁到下一个区域，
	//eg：按8对齐：7对齐到8，10对齐到16等
	static inline size_t _Roundup(size_t size, size_t align) 
	{
		return (size + align - 1) & ~(align - 1);
	}										   

	//根据字节向上取整：对齐
	static inline size_t Roundup(size_t size)
	{
		assert(size <= MAXBYTES);

		if (size <= 128) {
			return _Roundup(size, 8);
		}
		else if (size <= 1024){
			return _Roundup(size, 16);
		}
		else if (size <= 8192){
			return _Roundup(size, 128);
		}
		else if (size <= 65536){
			return _Roundup(size, 1024);
		}
		else {
			return -1;
		}
	}
	
	static inline size_t _Index(size_t bytes, size_t align_shift)
	{
		//eg:按8对齐：字节数+8-1，,跃迁到下一个区域，除以8（>>3），看有多少个8，最后减一就是下标
		//return (bytes+对齐数-1)/对齐数-1；此处用移位运算解决
		return ((bytes + (1 << align_shift) - 1) >> align_shift) - 1;
	}

	static inline size_t Index(size_t bytes)
	{
		assert(bytes <= MAXBYTES);

		// 每个区间有多少个自由链表
		static int group_array[4] = { 16, 56, 56, 56 };

		if (bytes <= 128){
			return _Index(bytes, 3);
		}
		else if (bytes <= 1024){
			return _Index(bytes - 128, 4) + group_array[0];
		}
		else if (bytes <= 8192){
			return _Index(bytes - 1024, 7) + group_array[1] + group_array[0];
		}
		else if (bytes <= 65536){
			return _Index(bytes - 8192, 10) + group_array[2] + group_array[1] +
				group_array[0];
		}
		else{
			return -1;
		}
	}

	static size_t BytesMoveNum(size_t size)
	{
		if (size == 0)
			return 0;

		//获取对象个数：大对象少申请点，小对象多申请。为什么MAXBYTES/byte？：首先是自定义的，也因为链表对象最大64k，
		int num = static_cast<int>(MAXBYTES / size);  //
		if (num < 2)
			num = 2;

		if (num > 512)
			num = 512;

		return num;
	}

	// 计算一次向系统获取几个页
	static size_t BytesMovePage(size_t bytes)
	{
		//控制对象个数上限下限
		size_t num = BytesMoveNum(bytes);
		size_t count_bytes= num*bytes;
		//（总的字节数/4k）就是页数,也就是右移12位
		 size_t npage = count_bytes >> 12;
		if (npage == 0)
			npage = 1;

		return npage;
	}
};
