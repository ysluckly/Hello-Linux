#pragma once

#include "Common.h"

template<class K, class Hash = __Hash<K>>
class UnorderedSet
{
public:
	struct SetKeyOfValue
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

	typedef typename HashTable<K, K, SetKeyOfValue, Hash>::iterator iterator;
	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}

	pair<iterator, bool> Insert(const K& key)
	{
		return _ht.Insert(key);
	}

	void PrintBucketNum()
	{
		_ht.PrintBucketNum();
	}
private:
	HashTable<K, K, SetKeyOfValue, Hash> _ht;
};

//void TestSet()
//{
//	UnorderedSet<int> s;
//	for (size_t i = 0; i < 10; ++i)
//	{
//		s.Insert(rand());
//	}
//
//	UnorderedSet<int>::iterator it = s.begin();
//	while (it != s.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	for (auto e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	//s.PrintBucketNum();
//}