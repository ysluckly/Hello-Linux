#pragma once
#include <string>

template<class K>
struct __Hash
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct __Hash<string>
{
	size_t BKDR(const char* str)
	{
		size_t hash = 0;
		while (*str)
		{
			hash *= 131;
			hash += *str;

			++str;
		}

		return hash;
	}
	size_t operator()(const string& key)
	{
		return BKDR(key.c_str());
	}
};


//struct __HashString
//{
//	size_t BKDR(const char* str)
//	{
//		size_t hash = 0;
//		while (*str)
//		{
//			hash *= 131;
//			hash += *str;
//
//			++str;
//		}
//
//		return hash;
//	}
//	size_t operator()(const string& key)
//	{
//		return BKDR(key.c_str());
//	}
//};