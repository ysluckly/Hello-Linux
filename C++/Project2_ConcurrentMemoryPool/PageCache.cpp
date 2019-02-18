#include "PageCache.h"

PageCache PageCache::_inst;

Span* PageCache::NewSpan(size_t npage)
{
	if (!_pagelist[npage].Empty())
	{
		return _pagelist[npage].PopFront();
	}

	for (size_t i = npage + 1; i < NPAGES; ++i)
	{
		SpanList* pagelist = &_pagelist[i];
		if (!pagelist->Empty())
		{
			Span* span = pagelist->PopFront();
			Span* split = new Span;
			split->_pageid = span->_pageid + span->_npage - npage;	//尾切
			split->_npage = npage;
			span->_npage -= npage;

			_pagelist[span->_npage].PushFront(span);

			return split;
		}
	}

	// pagecache内存不足，需要向系统申请内存（windows用VirtualAlloc，Linux用brk/mmap）
	//1，指定位置：0（任意）2，字节大小  3,分配类型 4，属性（可读可写）
	void* ptr = VirtualAlloc(NULL, (NPAGES - 1) << PAGE_SHIFT, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
	if (ptr == nullptr)
	{
		throw std::bad_alloc();
	}

	Span* largespan = new Span;
	largespan->_pageid = (PageID)ptr >> PAGE_SHIFT;
	largespan->_npage = NPAGES - 1;

	_pagelist[NPAGES - 1].PushFront(largespan);

	return NewSpan(npage);
}