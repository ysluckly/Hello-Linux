#pragma once

#include "HashTable.h"
#include "Common.h"

template<class K, class V, class Hash = __Hash<K>>
class UnorderedMap
{
public:
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& kv)
		{
			return kv.first;
		}
	};

	typedef typename HashTable<K, pair<K, V>, MapKeyOfValue, Hash>::iterator iterator;
	iterator begin()
	{
		return _ht.begin();
	}

	iterator end()
	{
		return _ht.end();
	}

	pair<iterator, bool> Insert(const pair<K, V>& kv)
	{
		return _ht.Insert(kv);
	}

	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
		return ret.first->second;
	}

private:
	HashTable<K, pair<K, V>, MapKeyOfValue, Hash> _ht;
};

//void TestMap()
//{
//	//UnorderedMap<string, string, __HashString> dict;
//	UnorderedMap<string, string> dict;
//	dict.Insert(make_pair("sort", "ÅÅÐò"));
//	dict["left"] = "×ó±ß";
//
//	for (auto e : dict)
//	{
//		cout << e.first << ":" << e.second << endl;
//	}
//	cout << endl;
//}