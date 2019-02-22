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

const size_t NLISTS = 184;  //�����������������ĳ��ȣ��ɶ�������������array����
const size_t MAXBYTES = 64 * 1024;	 //�Զ���涨С��64k����threadcache���룬��threadcache���64k��
const size_t PAGE_SHIFT = 12;		//��λ��
const size_t NPAGES = 129;		//pagecache������󳤶�

typedef size_t PageID;
//ҳΪ��λ�����ֶ������
struct Span
{
	PageID _pageid;			// ҳ��
	size_t _npage;		// ҳ������

	Span*  _next;
	Span*  _prev;

	void*  _objlist = nullptr;	// ������������
	size_t _objsize = 0;		// �����С
	size_t _usecount = 0;		// ʹ�ü���
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

//��ǰ�������һ�������ַ
static inline void*& NEXT_OBJ(void* obj)
{
	return *((void**)obj);
}

 //��������
class FreeList
{
public:
	bool Empty()
	{
		return _list == nullptr;
	}

	//ͷɾ
	void* Pop()
	{
		void* obj = _list;
		_list = NEXT_OBJ(obj);
		--_size;

		return obj;
	}

	//ͷ��
	void Push(void* obj)
	{
		NEXT_OBJ(obj) = _list;
		_list = obj;
		++_size;
	}
	//��������һ���Բ���
	void PushRange(void* start, void* end, size_t num)
	{
		NEXT_OBJ(end) = _list;
		_list = start;
		_size += num;
	}

	//��ȡ������
	size_t Size()
	{
		return _size;
	}

	//��ȡ���������ֵ
	size_t MaxSize()
	{
		return _maxsize;
	}	
	
private:
	void* _list = nullptr;
	size_t _size = 0;	  //����������
	size_t _maxsize = 0;  //�������������ֵ
};
//
// ��������ӳ��Ĺ���
class ClassSize
{
	// ������12%���ҵ�����Ƭ�˷�
	// [1,128]				8byte���� freelist[0,16)
	// [129,1024]			16byte���� freelist[16,72)
	// [1025,8*1024]		128byte���� freelist[72,128)
	// [8*1024+1,64*1024]	512byte���� freelist[128,240)
public:
	//�ֽڶ��뵽ĳ������ eg�����뵽8    ��size+7��& ~��7����size+������-1������ԾǨ����һ������
	//eg����8���룺7���뵽8��10���뵽16��
	static inline size_t _Roundup(size_t size, size_t align) 
	{
		return (size + align - 1) & ~(align - 1);
	}										   

	//�����ֽ�����ȡ��������
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
		//eg:��8���룺�ֽ���+8-1��,ԾǨ����һ�����򣬳���8��>>3�������ж��ٸ�8������һ�����±�
		//return (bytes+������-1)/������-1���˴�����λ������
		return ((bytes + (1 << align_shift) - 1) >> align_shift) - 1;
	}

	static inline size_t Index(size_t bytes)
	{
		assert(bytes <= MAXBYTES);

		// ÿ�������ж��ٸ���������
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

		//��ȡ��������������������㣬С��������롣ΪʲôMAXBYTES/byte�����������Զ���ģ�Ҳ��Ϊ�����������64k��
		int num = static_cast<int>(MAXBYTES / size);  //
		if (num < 2)
			num = 2;

		if (num > 512)
			num = 512;

		return num;
	}

	// ����һ����ϵͳ��ȡ����ҳ
	static size_t BytesMovePage(size_t bytes)
	{
		//���ƶ��������������
		size_t num = BytesMoveNum(bytes);
		size_t count_bytes= num*bytes;
		//���ܵ��ֽ���/4k������ҳ��,Ҳ��������12λ
		 size_t npage = count_bytes >> 12;
		if (npage == 0)
			npage = 1;

		return npage;
	}
};