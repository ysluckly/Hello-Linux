
#pragma once
#include<iostream>
using namespace std;
//用链表来实现内存池，每一个结点都挂有一块内存
template<typename T>
class ObjectPool
{
	struct BlockNode         //每一个结点类型
	{
		void* _memory;        //指向一块已经分配的内存
		BlockNode * _next;    //指向下一个结点
		size_t _objNum;       //记录这块内存中对象的个数
		BlockNode(size_t objNum)
			:_objNum(objNum)
			, _next(NULL)
		{
			_memory = malloc(_objNum*_itemSize);
		}
		~BlockNode()
		{
			free(_memory);
			_memory = NULL;
			_next = NULL;
			_objNum = 0;
		}
	};
protected:
	size_t _countIn;      //当前结点的在用的计数
	BlockNode* _frist;    //指向链表的头
	BlockNode* _last;     //指向链表的尾
	size_t _maxNum;        //记录内存块最大的容量
	static size_t _itemSize;   //单个对象的大小
	T* _lastDelete;        //指向最新释放的那个对象的空间
public:
	ObjectPool(size_t initNum = 32, size_t maxNum = 100000)  //默认最开始内存块有32个对象，一个内存块最大有maxNum个对象
		:_countIn(0)
		, _maxNum(maxNum)
		, _lastDelete(NULL)
	{
		_frist = _last = new BlockNode(initNum);   //先开辟一个结点，这个结点里面的内存块能够存放initNum个对象
	}
	~ObjectPool()
	{
		Destory();
	}
	T* New()                   //分配内存
	{
		if (_lastDelete)         //先到释放已经用完并且换回来的内存中去找
		{
			T* object = _lastDelete;
			_lastDelete = *((T**)_lastDelete);  //将_lastDelete转换成T**，*引用再取出来T*，也就是取出前T*类型大小的单元
			return new(object)T();        //把这块内存用从定位new初始化一下
		}
		//判断还有没有已经分配的内存且还未使用,如果没有内存的话就要再分配内存
		if (_countIn >= _last->_objNum)     //大于等于表示没有了，这时候就要分配内存了
		{
			size_t size = 2 * _countIn;
			if (size > _maxNum)            //块的最大大小不能超过maxNum，如果没超过就以二倍增长
				size = _maxNum;
			_last->_next = new BlockNode(size);
			_last = _last->_next;
			_countIn = 0;
		}
		//还有已经分配好的未被使用的内存
		T* object = (T*)（(char*)_last->_memory + _countIn*_itemSize）;
		_countIn++;
		return new(object)T();        //将这块空间用重定位new初始化一下
	}
	void Destory()
	{
		BlockNode *cur = _frist;
		while (cur)
		{
			BlockNode* del = cur;
			cur = cur->_next;
			delete del;            //会自动调用~BlockNode()
		}
		_frist = _last = NULL;
	}
	void Delete(T* object)          //释放内存
	{
		if (object)
		{
			object->~T();
			*((T**)object) = _lastDelete;      //将_lastDelete里面保存的地址存到tmp指向空间的前T*大小的空间里面
			_lastDelete = object;
		}
	}
protected:
	static size_t GetItemSize()
	{
		if (sizeof(T)>sizeof(T*))
		{
			return sizeof(T);
		}
		else
		{
			return sizeof(T*);
		}
	}
};
template<typename T>
size_t ObjectPool<T>::_itemSize = ObjectPool<T>::GetItemSize();          //类外初始化静态变量_itemSize
