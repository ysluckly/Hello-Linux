#pragma once

#include "Common.h"
#include "ThreadCache.h"
//
void* ConcurrentAlloc(size_t size)
{
	if (size > MAXBYTES)
	{
		return malloc(size);
	}
	else
	{
		// 通过tls，定义线程独有的全局变量，根据变量获取线程自己的threadcache
		if (tls_threadcache == nullptr)
		{
			tls_threadcache = new ThreadCache;
			//cout << "新创建的线程"<<std::this_thread::get_id() << "->" << tls_threadcache << endl;

		}

		return tls_threadcache->Allocate(size);
		
	}
}

void ConcurrentFree(void* ptr, size_t size)
{
	if (size > MAXBYTES)
	{
		return free(ptr);
	}
	else
	{
		tls_threadcache->Deallocate(ptr, size);
	}
}